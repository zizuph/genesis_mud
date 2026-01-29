inherit "/std/door";
#include "/d/Kalad/defs.h"
/* by Korat with header from Aldarion */
create_door()
{
   set_door_id("highlord_door");
   set_pass_command(({"e","east"}));
   set_door_name(({"oak door","door"}));
   set_long("This is a solid door made of oak. "+
      "Along the edges you can see small, but elegant "+
      "engravings that tells a story of a mighty battle.\n");
   set_other_room("/d/Kalad/common/central/citadel/cit20");
   set_fail_pass("The door is closed, maybe you should open it?\n");
   set_open(0);
   set_locked(0);
}

/*
 * Function name: open_door
 * Description:   Open the door.
 * Arguments:     arg - arguments given
 */
int
open_door(string arg)
{
    if (!this_door(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n", 0);
        return 0;
    }
    
    if (this_player()->query_prop(LIVE_I_BLIND))
    {
        notify_fail("You can't expect to open a door while blind.\n",0);
        return 0;
    }
    
    return ::open_door(arg);
}