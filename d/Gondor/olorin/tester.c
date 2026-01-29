inherit "/std/object.c";

void
create_object()
{
    set_name("tester");
    set_short("tester");
    set_long("A tester.\n");
}

int
do_calculate(string str)
{
    this_player()->compute_skill_decay();
    return 1;
}

void
init()
{
    ::init();

    add_action(do_calculate, "calc", 1);
}

