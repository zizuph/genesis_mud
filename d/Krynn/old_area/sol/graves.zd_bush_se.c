/* A door in the Solace Graveyard
 * zd_bush_se.c
 * Dorak 07-04-95
 * a door that looks and acts like a bush
 */

inherit "/std/door";
#include "/d/Krynn/common/defs.h"
#include "../zlocal.h"

create_door()
{
    ::create_door();

    set_other_room(TDIR + "zvwood0");
    set_door_id("bush_door");
    set_door_desc("There is a bit of a trail under them.");
    set_door_name("bushes");
    set_open(0);
    set_open_desc("");
    set_closed_desc("");
    set_pass_command("enter");
    set_fail_pass("You must kneel to enter the bushes.\n");
    set_open_command("kneel");
    set_open_mess(({"@@open_mess1", "@@open_mess2"})); /* here, other rm */
    set_fail_open("You are already kneeling.");
}

string
open_mess1() 
   { return "kneels down in front of the" + door_name[0] + ".\n"; }

string
open_mess2() 
   { return "You hear something from beyond the" + door_name[0] + ".\n"; }
