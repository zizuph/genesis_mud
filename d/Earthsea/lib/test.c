public int gt(mixed a, mixed b)
{
    if(a < b)
    {
        return -1;
    }

    if(a > b)
    {
        return 1;
    }

    return 0;
}

public void create() {
 int *foo = ({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });

 foo = sort_array(foo, gt);
}
