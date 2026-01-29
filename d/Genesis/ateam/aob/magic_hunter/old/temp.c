int *first;

create()
{
    first = ({1,4,2,3});
}

sort_me(mixed arg1, mixed arg2)
{
    if (arg1 < arg2)
        return -1;
    if (arg1 == arg2)
        return 0;
    if (arg1 > arg2)
        return 1;
}

test_me()
{
return sort_array(first, sort_me);
}
