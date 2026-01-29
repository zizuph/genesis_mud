/* 
 *	/d/Gondor/common/npc/redteamorc.c
 *
 * This orc will attack anyone attacking a member
 * of his team
 * copied in parts from /doc/examples/mobiles/troll.c
 *
 *	Modification log:
 *	 4-Feb-1997, Olorin:	General revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/npc/std_mordor_orc";

#include "/d/Gondor/defs.h"

public void
create_monster()
{
    ::create_monster();

    set_long(BS("A most evil creature. He is big and strong, and he "
        + "looks at you with death in his eyes..\n"));

    add_chat("Why can we never stop to eat?");
    add_chat("Come on, let's return....no humans dare enter Ithilien anyway!");
    add_chat("I hate these stupid patrols. Never any action!");
    add_chat("Why not go back to Minas Morgul again? I like it there!");
    add_cchat("You'll be dead soon!");
    add_cchat("Too bad that we don't have the time to put it to death properly!");  
    add_cchat("Let's not tell the Shrieker about this one! I want to eat it!");

}
