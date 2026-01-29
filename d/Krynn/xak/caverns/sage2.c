/* Xak Tsorath coded by Percy */

/**
 * Navarre March 20th 2009, Fixed the bottle so that it isn't only 5 bottles per armageddon.
 * They now reset with the room.
 */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

object scorpion;
int bottle_taken = 0;


void
reset_xak_room()
{
    if (!scorpion)
    {
	  scorpion = clone_object(MONSTER + "scorpion.c");
          scorpion->move(TO, 1);
    }
    bottle_taken = 0;
}

void
create_xak_room()
{
    set_short("The shop storeroom");
    set_long("You are inside an old slightly ruined storeroom." +
	     " The storeroom is quite bare except for some " +
	     "cupboards on the west wall.\n");
    
    add_exit(DDIR + "sage1.c", "north", 0);
    
    add_item(({"cupboards", "cupboard"}), "@@cupboard");
    add_item(({"bottles", "bottle", "glass bottle", "glass bottles", "bottles in cupboard"}), "@@bottles");
    DARK;
    INSIDE;
    reset_room();
}

void
init()
{
    ::init();
    ADA("get");
    ADD("get","take");
}

string
cupboard()
{
    if (bottle_taken)
    {
	  write("All the cupboards are bare.\n");
	  SAY(" looks through the cupboards.");
    }
    else
    {
        write(BS("The cupboards are mostly bare except for a few empty"
	         + " glass bottles.", 70));
        SAY(" looks through the cupboards.");
    }
    return "";
}

string
bottles()
{
    if (bottle_taken)
    {
        write("Examine what?\n");
    }
    else
    {
        write(BS("A few glass bottles have somehow remained unbroken here"
	      + " within the cupboard.", 70));
        SAY(" looks at the bottles in the cupboard.");
    }
    return "";
}

int
get(string str)
{
    int prp;
    NF("Get what?\n");
    if ((str == "bottle") || (str == "bottle from cupboard") || 
	(str == "glass bottle")	|| (str == "glass bottle from cupboard"))
    {
        if (bottle_taken)
        {
	    write("There are no more bottles in the cupboard.\n");
	    return 1;
        }
	  
        clone_object(OBJ + "bottle.c")->move(TP);
	prp = TP->query_prop("_player_i_black_dragon_quest");
        TP->add_prop("_player_i_black_dragon_quest",prp | 1);
	write("You get a glass bottle from the cupboard.\n");
	SAY(" gets a bottle from the cupboard.\n");
	bottle_taken = 1;
	return 1;
    }
    return 0;
}


