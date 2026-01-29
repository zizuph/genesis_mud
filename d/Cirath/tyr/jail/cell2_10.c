/*
* Created by: Luther
* Date: 11 August 2001
*
* File: /d/Cirath/tyr/jail/cell2_10.c
* Comments: Standard cell in Tyr's Jail
*/

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    object npc = present ("prisoner", TO);
    if(!objectp(npc))
    {
	bring_room_mob("prisoner", TYR_NPC+"jailpris.c", (random(3)+1));
    }
}

void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 0);
	set_short("cell");
	set_long("The cell looks very plan, and judging from all the chains "
		+"in here this place can hold alot of prisoners. Your not "
		+"sure you belong, a guard could come along any minute now "
		+"and chain you up!\n");

	add_item("chains", "There are chains everywhere on the walls and hanging "
		+"from the ceiling.Upon closer examination you notice that the "
		+"chains are covered in blood. Making you think that they where used "
		+"for more then just holding a prisoner.\n");

	add_exit(TYR_JAIL + "jail2_3.c", "east", 0,1);
	reset_room();
}
