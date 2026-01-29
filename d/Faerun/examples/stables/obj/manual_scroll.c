#pragma save_binary
#pragma strict_types

inherit "/std/object.c";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>


public string
read_message()
{


    return ("Its got lots of writing on it. How about reading it?\n\n" +
        "You can 'tear scroll' to dispose of it.\n\n");
}


public void
create_object()
{
    set_name("scroll");
    add_name("_horse_quest_scroll_");
    set_pname("scrolls");
    set_short("scroll");
    set_pshort("scrolls");
    set_long(read_message);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    setuid();
    seteuid(getuid());

}

public int
do_read(string str)
{
    object *ob;
    string text;
    if (strlen(str) &&
        parse_command(str, all_inventory(this_player()), "%i", ob) &&
        sizeof(ob = NORMAL_ACCESS(ob, 0, 0)) &&
        ob[0] == this_object())
    {
        setuid();
        seteuid(getuid());
        text = read_file("/d/Shire/bree/rooms/town/stable/obj/man_horse.txt");
        this_player()->more(text, 0);
        return 1;
    }
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
