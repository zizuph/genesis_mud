inherit "/std/object";

void
create_object()
{
    set_name("dummy");
    set_long("This is a dummy object!\n");
    set_short("dummy object");
}

void
init()
{
    write("DEBUG: init() in dummy object called for player " + this_player()->query_name() + "\n");
    ::init();
    add_action("do_test", "test");
}

int
do_test(string str)
{
    write("DEBUG: do_test in dummy object called with str = " + str + 
        " for player " + this_player()->query_name() + "\n");
    return 1;
}

void fun(int *array) {
    array[0] = 2;
}

void fun2()
{
    int *a = ({1,2});
    fun(a);
    dump_array(a);
}

