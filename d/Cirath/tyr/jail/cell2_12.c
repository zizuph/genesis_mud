/*
* Created by: Luther
* Date: 11 August 2001
*
* File: /d/Cirath/tyr/jail/cell2_12.c
* Comments: Standard cell in Tyr's Jail
*/

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"
#include <stdproperties.h>
#include <ss_types.h>
#define SL TYR + "/obj/corpse_key.c"
#define COR TYR_NPC+"jail_corpse.c"
#define C_HAS_NO_KEY "c_has_no_key"

int searched;
object cor, sl;

void
reset_room()
{	
    	object npc = present ("dale", TO);
    	searched=0;
    	if(!objectp(npc))
    	{
		bring_room_mob("dale", TYR_NPC+"q_pris.c", 1, 1);
    	}
}

void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 0);
	set_short("cell");
	set_long("The cell looks very plan, you see a body hanging from chains "
		+"along one wall. Chains hang from everywhere. You think this "
		+"room is well used, and a guard can be heard shouting from the "
		+"corridor. You better leave soon or they might catch you in "
		+"here and decide to chain you up!\n");

	cor = clone_object(COR);
        cor->move(this_object());
        searched=0;        
     	add_prop(OBJ_S_SEARCH_FUN, "search_fun");
     	add_prop(OBJ_I_SEARCH_TIME, 5);

	add_item("body", "Its a decomposing body hanging from chains.\n");

	add_item("chains", "There are chains everywhere on the walls and hanging "
		+"from the ceiling. Upon closer examination you notice that the "
		+"chains are covered in blood. Making you think that they where used "
		+"for more then just holding a prisoner.\n");

	add_item("blood", "There is blood everywhere... On the floor, walls, chains and "
		+"there is even fresh blood here and there. The slaves must be tortured "
		+"daily for this much blood the be here.\n");

	add_exit(TYR_JAIL + "jail2_4.c", "northwest", 0,1);
	reset_room();
}

string
search_fun(object player, string str)
{
    if( str=="body")
    {
        if (! searched)
        {
           clone_object(TYR + "/obj/corpse_key.c")->move(TP);
           searched = 1;
           return "You search the corpse carefully and find a piece of a bone...\n";
        }
        else
            return "There is nothing here but useless bones.\n";
    }
    return "";
}


