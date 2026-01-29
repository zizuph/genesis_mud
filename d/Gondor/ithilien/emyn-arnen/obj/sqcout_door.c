inherit "/std/door";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

void
create_door()
{
    ::create_door();
    set_other_room(ITH_DIR + "emyn-arnen/palace/pass1");
    set_door_id("Emyn-Arnen_SQCorr_Door");
    set_pass_command(({"s","south"}));
    set_door_name(({"door", "hidden door", "secret door", }));
    set_door_desc(VBFC_ME("long_desc"));
    set_closed_desc("");
    set_open_desc("There is an open door leading south.\n");
    set_open(0);         /* 1 if open, 0 if closed */

    set_str(10);
}

string
long_desc()
{
    if(query_open())
        return BSN(
            "The door is made from wood, but the outside of the door as been "
          + "expertly painted to look like the surrounding wall. If the door "
          + "were closed you would hardly be able to see it.");
    else
        return BSN(
            "The door merges in perfectly with the surrounding wall. "
          + "Even though you know that the door is there you can hardly "
          + "see it.");
}

void
reset_door()
{
    do_close_door("The door closes.\n");
    other_door->do_close_door("The door closes.\n");
    lock_door("");
    other_door->do_lock_door("");
}


int
pass_door(string arg)
{
    if ( !query_open() && query_verb() == "south" &&
    !TP->query_prop("_exa_s_wall") )
    {
        TP->add_prop("_exa_s_wall", 1);
        write(BSN("Ouch! You walk into the wall, where you "+
            "find a cleverly hidden secret door."));
    }
    return ::pass_door(arg);
}
