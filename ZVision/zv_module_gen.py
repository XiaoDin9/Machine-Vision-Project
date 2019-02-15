# -*- coding: utf-8 -*-
"""
Created on Tue Jul  3 10:24:14 2018

@author: Administrator
"""

import re
import zv_module_templ 

is_write_declare = False  #是否生成函数声明

""" 0          1     2      3      4                         5
('ZV_TASK', 'void', 'cam', 'G', 'etInfo', 'int scanId, char *name, char *value, int maxValLen')
"""
def match_file():
    pat = re.compile(zv_module_templ.pat_src)
    pat_unfold = re.compile(zv_module_templ.pat_unfold_str)
    pat_cpp_def = re.compile(zv_module_templ.pat_cpp_def_str)

    with open(zv_module_templ.file_name, 'r', encoding='utf-8') as file:
        lines = file.readlines()

    print(len(lines))

    #连接分成两行的函数
    for i in range(len(lines)-1):
        if ('\n' == lines[i][0]):
            continue
        if (';' != lines[i][-2]):
            lines[i] = lines[i][:-1] + ' ' + lines[i+1].strip()
    #print(lines)

    count = 0
    match_list = []
    for line in lines:        
        if ('Z' != line[0]): #跳过无需匹配的行
            continue
    
        if ('zv_mod' in line or 'zv_test' in line):
            continue

        pat_cpp_def_rst = pat_cpp_def.findall(line)
        for item in pat_cpp_def_rst:
            line = line.replace(item, '')

        unfold_rst = pat_unfold.search(line)
        while (str(unfold_rst) != 'None'):
            line = line.replace(unfold_rst.group(), unfold_rst.group(1) + ' ')
            unfold_rst = pat_unfold.search(line)
        rst = pat.search(line)
        if (str(rst) == 'None'): #匹配失败，打印源内容
            print(line)
            continue
    
        #print(rst)
        count = count + 1
        match_list.append(rst.groups())
        #print(match_list[-1]) #分组捕获结果

    print(count)
    return match_list

"""
#return func_all_str[] 长度为2则为简单指令内部函数声明和接口函数实现
为4则为复杂指令内部函数声明、任务参数结构体、任务函数、接口函数实现
"""
def gen_function(match):
    ignore_str = ''#'\n#error 函数调用要求内部函数输出参数为最后一个参数，请检查确保无异常'
    func_all_str = []

    all_param_str = match[5]
    param_list = match[5].split(',')
    is_first = 0
    struct_value = ''
    zv_call_arg_list = ''
    out_param_name = ''
    unfold_num = 0
    for i in range(len(param_list)):
        param = param_list[i].strip()  #去首尾空格'int a'
        #print(param)
        param_name = param.replace('*', ' ').split(' ')[-1]  #分割参数名字'a'
        if ('ZV_TRAN_OUT' in param):  #返回值转输出参数
            out_param_name = param_name
            param = param.replace('ZV_TRAN_OUT', ' ').strip()
        #print(param_name)
        arg_unfold_param_name = param_name
        call_unfold_param_name = param_name
        temp_rst = re.search('^\d+', param) #指针展开
        if ('None' != str(temp_rst)):
            unfold_num = int(temp_rst.group())
            all_param_str = all_param_str.replace(','+str(unfold_num), ',') 
            param = param.replace(str(unfold_num) + ' ', '')
            for unfold_idx in range(1, unfold_num):
                call_unfold_param_name += ', ' + param_name + '+' + str(unfold_idx)
                arg_unfold_param_name += ', p->' + param_name + '+' + str(unfold_idx)

        if (0 == is_first):
            struct_param = '    ' + param + ';'
            arg_list = 'p->' + arg_unfold_param_name
            struct_value = param_name
            zv_call_arg_list = call_unfold_param_name
            is_first = 1
        else:
            struct_param = struct_param + '\n' + '    ' + param + ';' #'    int a;\n    int b;' #结构体元素
            if ('' == out_param_name):
                arg_list = arg_list + ', p->' + arg_unfold_param_name       #'p->scanId, p->name, p->value, p->maxValLen'
            struct_value = struct_value + ', ' + param_name  #'scanId, name, value, maxValLen'
            zv_call_arg_list = zv_call_arg_list + ', ' + call_unfold_param_name  #'scanId, name, value, maxValLen'

    if ('' != out_param_name):
        all_param_str = all_param_str.replace(' ZV_TRAN_OUT ', ' ')
        all_param_str = all_param_str.replace('ZV_TRAN_OUT ', ' ') #避免ZV_TRAN_OUT前没有空格时出错
    #all_param_str = match[5]
    
    struct_name_prefix = 'ZvTP'  #结构体类型前缀
    struct_name = struct_name_prefix + match[2].title() + match[3] + match[4] #'ZvTPTest'
    func_suffix = match[2] + '_' + match[3].lower() + match[4]  #'cam_getInfo'
    #func_line = 'void zv_camGetInfo(int scanId, char *name, char *value, int maxValLen)'
    func_line = match[1] + ' zv_' + match[2] + match[3] + match[4] + '(' +  all_param_str + ')'
    
    #接口函数 ZV_INCMPL
    zv_module_templ.incmpl_fun_demo #函数原型
    if ('ZV_INCMPL' == match[0]):  #仅输出程序框架
        func_incmpl_str = """%(line)s
{
    %(rst_type)s value = 0;%(ignore_str)s
    ZV_ERR_RUN(zv_%(suffix)s(%(param)s, &value));
    return value;
}
""" % {'line':func_line, 'rst_type':match[1], 'ignore_str':ignore_str,
       'suffix':func_suffix, 'param':zv_call_arg_list}
        func_declare = 'int zv_%s(%s, %s *outValue);\n' % (func_suffix, all_param_str, match[1])
        func_all_str.append(func_declare)  #函数声明，带输出参数
        func_all_str.append(func_incmpl_str)
        return func_all_str

    #接口函数ZV_CALL
    zv_module_templ.call_fun_demo #函数原型
    if ('ZV_CALL' == match[0]):
        if ('void' == match[1]):
            func_call_line = 'ZV_ERR_RUN(zv_%(suffix)s(%(param)s));' % {'suffix':func_suffix, 'param':zv_call_arg_list}
            func_declare1 = 'int zv_%s(%s);\n' % (func_suffix, all_param_str)
        else:
            func_call_line = 'return zv_%(suffix)s(%(param)s);' % {'suffix':func_suffix, 'param':zv_call_arg_list}
            func_declare1 = '%s zv_%s(%s);\n' % (match[1], func_suffix, all_param_str)
        func_call_str = """%(line)s
{
    %(call_line)s
}
""" % {'line':func_line, 'call_line':func_call_line}
        func_all_str.append(func_declare1)
        func_all_str.append(func_call_str)
        return func_all_str

    #结构体构造字符串
    zv_module_templ.param_struct_demo
    struct_str = """typedef struct
{
%(param)s
}%(name)s;
""" % {'param':struct_param,'name':struct_name}
    
    #任务函数构建
    zv_module_templ.func_task_demo

    if ('' == out_param_name):
        task_func_call_str = 'ZV_ERR_RUN(zv_%(func_s2)s(%(pplist)s));' % {'func_s2':func_suffix, 'pplist':arg_list}
        func_declare2 = 'int zv_%s(%s);\n' % (func_suffix, all_param_str)
    else:
        task_func_call_str = '*p->%(out_param_name)s = zv_%(func_s2)s(%(pplist)s);' % {
                'out_param_name':out_param_name, 'func_s2':func_suffix, 'pplist':arg_list}
        pos = match[5].find('ZV_TRAN_OUT')
        func_declare2_param =  match[5][0:match[5].rfind(',', 0, pos)]
        pos2 = match[5].find(',', pos)
        if (-1 != pos2):
            func_declare2_param +=  match[5][pos2+1:]
        if (-1 == pos2):
            pos2 = len(match[5])
        func_declare2_rst_type = match[5][pos:pos2].replace(
                'ZV_TRAN_OUT', ' ').replace('*', ' ').strip().split(' ')[0]
        func_declare2 = '%s zv_%s(%s);\n' % (func_declare2_rst_type, func_suffix, func_declare2_param)

    func_task_str = """void zv_task_%(suffix)s(void *param)
{
    %(s_name1)s *p = (%(s_name2)s *)param;
    %(task_func_call_str)s
}
""" % {'suffix':func_suffix, 's_name1':struct_name, 's_name2':struct_name,
        'task_func_call_str': task_func_call_str}

    #接口函数
    zv_module_templ.func_basic_demo
    func_line = 'int' + ' zv_' + match[2] + match[3] + match[4] + '(' +  all_param_str + ')'
    #避免局部结构体变量与函数参数重名
    func_basic_str = """%(line)s
{
    %(s_name)s taskParam_0 = {%(basic_p)s};
    return zv_task_registerRun(zv_task_%(suffix)s, &taskParam_0, sizeof(taskParam_0));
}
""" % {'line':func_line, 's_name': struct_name,
        'basic_p':struct_value, 'suffix':func_suffix}
    
    func_all_str.append(func_declare2)
    func_all_str.append(struct_str)
    func_all_str.append(func_task_str)
    func_all_str.append(func_basic_str)
        
    return func_all_str


mod_name = ''
mod_func_list = []  #模块函数实现
declare_func_list = [] #内部函数声明
task_func_list = [] #任务函数
task_func_h_list = [] #任务函数声明
task_param_list = [] #任务参数结构体
match_list = match_file()

for match in match_list:
    if (mod_name != match[2]):
        mod_name = match[2]
        mod_func_list.append(zv_module_templ.mod_comment_dict[mod_name]) #模块注释
        declare_func_list.append('\n//%s\n'%(mod_name))
    func_str = gen_function(match)
    mod_func_list.append(func_str[-1])
    if (4 == len(func_str)):
        task_func_list.append(func_str[2]+'\n')
        task_param_list.append(func_str[1]+'\n')
        task_func_h_list.append(func_str[2][:func_str[2].find('\n')] + ";\n")
    declare_func_list.append(func_str[0])
    mod_func_list.append('\n')
declare_func_list.append('\n')

with open(zv_module_templ.module_file, 'w') as save:
    save.write(zv_module_templ.file_comment)
    save.write(zv_module_templ.include_and_frame)
    save.writelines(mod_func_list)
    save.write(zv_module_templ.mod_function)
#system/zv_task.cpp
with open(zv_module_templ.task_cpp_file, 'w') as save:
    save.write(zv_module_templ.file_comment)
    save.write(zv_module_templ.task_cpp_file_head)
    if (is_write_declare):
        save.writelines(declare_func_list)   #声明函数
    save.writelines(task_func_list)

with open(zv_module_templ.task_param_h_file, 'w') as save:
    save.write(zv_module_templ.file_comment)
    save.write(zv_module_templ.task_param_file_head)
    save.writelines(task_param_list)
    save.write(zv_module_templ.task_param_file_tail)

with open(zv_module_templ.task_h_file, 'w') as save:
    save.write(zv_module_templ.file_comment)
    save.write(zv_module_templ.task_h_file_head)
    save.writelines(task_func_h_list)
    save.write(zv_module_templ.task_h_file_tail)
