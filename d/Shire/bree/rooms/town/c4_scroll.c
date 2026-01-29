#pragma save_binary
#pragma strict_types

inherit "/std/object.c";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>

// int Being_destructed = 0;
string Scroll_text = "Someone is offering you a game of Connect Four at the Prancing Pony in Bree.\n";

public string
read_message()
{


    return ("Its got some writing on it. How about reading it?\n\n" +
        "You can 'tear scroll' to dispose of it.\n\n");
}

/*
public void
dest_scroll()
{
    write("The scroll crumbles away.\n");
    this_object()->remove_object();
}


public void
leave_env(object dest, object old)
{
    ::leave_env(dest, old);

    if (!Being_destructed)
    {
        Being_destructed = 1;
        set_alarm(1.0, 0.0, dest_scroll);
    }
}
*/

public void
create_object()
{
    set_name("scroll");
    set_pname("scrolls");
    set_short("scroll");
    set_pshort("scrolls");
    set_long(read_message);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    setuid();
    seteuid(getuid());

}

public int
do_read(string str)
{
    if (str!="scroll")
       return 0;
    write(Scroll_text);
    return 1;
}

public void
set_text(string str)
{
    Scroll_text = str;

}


public int
do_tear(string str)
{
    if (stringp(str))
    {
        write("The scroll crumbles away.\n");
        this_object()->remove_object();
        return 1;
    }
    write ("Tear what? The scroll?\n");
    return 1;
}

public void
init()
{
    add_action(do_read, "read");
    add_action(do_tear, "tear");
}
