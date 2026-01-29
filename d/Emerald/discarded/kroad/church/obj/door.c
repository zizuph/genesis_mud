inherit "/std/door";

#include "../defs.h"
#include <cmdparse.h>

void
create_door()
{
    set_name(({ "door", "doorway" }));
    set_door_name(({ "door", "doorway", "iron door" }));
    set_adj("iron");
    set_long("The iron door is several inches thick, and probably nearly " +
             "impenetrable.  It appears that it slides open and closed, " +
             "withdrawing into the wall when open.\n");
    set_door_id("vamp_sun_chamber_door");
    set_open_desc("An open doorway.\n");
    set_closed_desc("A closed doorway.\n");

    unset_no_show();
    set_no_show_composite(1);
}

void
auto_open()
{
    if (!open_status)
    {
        do_open_door("The door slides open.\n");
        query_other_door()->do_open_door("The door slides open.\n");
    }
}

void
auto_close()
{
    if (open_status)
    {
        do_close_door("The door slides shut.\n");
        query_other_door()->do_close_door("The door slides shut.\n");        
    }
}

int
open_door(string str)
{
    mixed *obs;

    if (!strlen(str) || 
       !parse_command(str, all_inventory(environment()), "[the] %i", obs) ||
       (sizeof(obs = NORMAL_ACCESS(obs, 0, 0)) != 1))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (open_status)
    {
        write("The door is already open.\n");
        return 1;
    }

    write("There is no place to grip the door.  There must be some other " +
        "mechanism to open it.\n");
    return 1;
}
       
int
close_door(string str)
{
    mixed *obs;

    if (!strlen(str) || 
       !parse_command(str, all_inventory(environment()), "[the] %i", obs) ||
       (sizeof(obs = NORMAL_ACCESS(obs, 0, 0)) != 1))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!open_status)
    {
        write("The door is already closed.\n");
        return 1;
    }

    write("There is no place to grip the door.  There must be some other " +
        "mechanism to close it.\n");
    return 1;
}
