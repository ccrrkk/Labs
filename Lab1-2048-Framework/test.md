# LAB1 
BUGS：
1. 分数不增加 --return score误写成return 0，已解决
2. 随机位置不随机 --似已解决
3. DOWN逻辑似有误 --漏写一个break，已解决
4. U撤回会撤回两步，BUG触发条件：出现merge的话会撤销两步 
5. 撤销分数不撤销 --补写一个分数栈，已解决