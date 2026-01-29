/* This is the door that leads to the room of the Nightlord/lady.
 */

#pragma strict_types

#include "../defs.h"

inherit "/std/door";

#include <stdproperties.h>
#include <macros.h>

string * gNames;

void
create_door()
{
    set_door_desc("This door is approximately six feet high, four feet wide " +
        "and arched. It is made of well-polished oak and on the centre of " +
        "the door is an inlay of onyx in the shape of a crescent.\n");
    set_door_id("priest_inquisitor_door");
    set_pass_command(({"w", "west"}));
    set_door_name(({"door", "oak door", "well-polished door"}));
    set_other_room( DUNGTWO + "inquisitor.c");
    set_open(0);
    set_fail_pass("You stop as you realize how silly it is to try to walk " +
        "through a closed door.\n");
    set_open_command(({"open", "push"}));
    set_open_mess(({"slowly pushes the door open.\n", 
        "The oak door opens slowly.\n"}));
    set_fail_open(({"But the door is already open.\n", "The door is locked " +
        "and probably for a good reason.\n"}));
    set_close_command(({"close", "pull"}));
    set_close_mess(({"pulls the oak door closed.\n", "The " +
        "oak door closes slowly.\n"}));
    set_fail_close("Why would you want to close an already closed door?\n");
    set_locked(0);
    set_lock_name("lock");
    set_lock_desc("The lock on this door is made of bronze and has a small " +
        "decore of silverthread in the form of a thorned vine which circles " +
        "the keyhole.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the oak door.\n", "A loud 'click' is heard as the " +
        "oak door is locked.\n"}));
    set_fail_lock(({"But the door is already locked.\n", "You cannot lock " +
        "this door when it is open.\n"})); 
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the oak door.\n", "A loud 'click' is " + 
        "heard as the oak door is unlocked.\n"}));
    set_fail_unlock("Why unlock an already unlocked door?\n");
    set_key("priest_inquisitor_key");
    set_pick(80);
    set_lock_name("priest_inquisitor_lock");

    set_open_desc("");
    set_closed_desc("");
}

void
make_me_known(object pl)
{
    if (!pointerp(gNames))
        gNames = ({ });
    
    if (member_array(pl->query_real_name(), gNames) < 0)
        gNames += ({ pl->query_real_name() });
}

int
query_known(object pl)
{
    if (pointerp(gNames) &&
        member_array(pl->query_real_name(), gNames) >= 0)
        return 1;
    
    return 0;
}
#ifdef 0
string
standard_open_desc()
{
    if (pointerp(gNames) &&
        member_array(this_player()->query_real_name(), gNames) >= 0)
        return ::standard_open_desc();
    
    return "";
}

string
standard_closed_desc()
{
    if (pointerp(gNames) &&
        member_array(this_player()->query_real_name(), gNames) >= 0)
        return ::standard_closed_desc();
    
    return "";
}

int
query_no_show()
{
    if (!pointerp(gNames))
        return ::query_no_show();

    if (member_array(this_player()->query_real_name(), gNames) >= 0)
        return 0;
    
    return ::query_no_show();
}
#endif
