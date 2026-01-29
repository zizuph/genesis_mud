inherit "/std/object";

#define NL  write("\n");

create_object()
{
    set_name("t");
    set_long("t");
    set_short("t");
}

init()
{
    add_action("t", "t");
}

t()
{
    object o, pl;

    o = this_object();
    write(getuid()); write("   :   ");write(geteuid());NL

    setuid();
    write(getuid()); write("   :   ");write(geteuid());NL
    seteuid();
    write(getuid()); write("   :   ");write(geteuid());NL
    seteuid(getuid());
    write(getuid()); write("   :   ");write(geteuid());NL

    write(this_player()->query_name());NL
    this_player()->export_uid(o);
    set_trusted(1);
    write(getuid()); write("   :   ");write(geteuid());NL
    seteuid(getuid(environment(this_object())));
    write(getuid()); write("   :   ");write(geteuid());NL

    return 1;
}
