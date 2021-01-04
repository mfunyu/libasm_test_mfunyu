rm -f actual.log expected.log exec

make check

./exec "hello world" | cat -e
if [ $? != 0 ]; then
    printf '\n\033[31m%s\033[m\n' "KO: [ error Found in executable ;) ]"
fi

# print
printf '\n\033[44m%s\033[m\n\n' "[ actual.log (ft_func) (left) : expected.log (func) (right) ] "

colordiff -y actual.log expected.log

# if diff exists
if [ $? = 1 ]; then
    printf '\n\033[32m%s\033[m\n' "OK: [ no diff :D ]"
else
    printf '\n\033[31m%s\033[m\n' "KO: [ error Found ;) ]"
fi