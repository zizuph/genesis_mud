#pragma save_binary
#pragma strict_types

inherit "/std/object.c";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>


public string
read_message()
{


    return ("The scroll says:\n" +
        "---------------------------------------------------------"+
        "----------------------\n\n\n\n\n"+
        "The horse was delivered successfully. Reward this person if you so desire.\n\n\n\n"+
        "========================================================"+
        "=======================\n\n");
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
}

public int
do_read(string str)
{
    object *ob;
    if (strlen(str) &&
        parse_command(str, all_inventory(this_player()), "%i", ob) &&
        sizeof(ob = NORMAL_ACCESS(ob, 0, 0)) &&
        ob[0] == this_object())
    {
        write(read_message());
        return 1;
    }
}

public void
init()
{
    add_action(do_read, "read");
}
