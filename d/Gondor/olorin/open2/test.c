inherit "/std/object";

void
create_object()
{
    set_name("dummy object");
    set_long("Just a dummy object to test something.\n");
    add_name("object");
    set_adj("dummy");
}

void
init()
{
    ::init();

    add_action("do_something", "test");
}

int
do_something(string str)
{
    write("You just tried to do something!\n");
    return 1;
}
