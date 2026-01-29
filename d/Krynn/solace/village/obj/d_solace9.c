/* A door in Solace, coded by Nick
 * adapted by Dorak 14-04-94
 * a door that looks and acts like a bush
 * it is for room solace9.c
 */

inherit "/std/door";
#include "/d/Krynn/common/defs.h"
#include "../local.h"

create_door()
{
    ::create_door();

    set_other_room(TDIR + "solace12");
    set_door_id("door_bush");
    set_door_desc("They are thick, but maybe not too thick to enter.\n");
    set_door_name(({"thick bushes", "bushes"}));
    set_open(0);
    set_open_desc("");
    set_closed_desc("");
    set_pass_command("enter");
    set_fail_pass("You must part the bushes before you can enter them.\n");
    set_open_command("part");
    set_open_mess(({"@@open_mess1", "@@open_mess2"})); /* here, other rm */
    set_fail_open("The " + door_name[0] + " are thin enough to enter.\n");
}

string
open_mess1() 
   { return "does something to thin the " + door_name[0] + ".\n"; }

string
open_mess2() 
   { return "The " + door_name[0] + " rustle and become thinner.\n"; }
