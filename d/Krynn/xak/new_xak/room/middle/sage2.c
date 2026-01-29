/* 
 * Xak Tsaroth - Lower level
 * Originally coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;

/* int botnum; */
object gScorpion;

public void
reset_xak_room()
{
    MOVE(gScorpion, NPC + "scorpion")
}

public void
create_xak_room()
{
    set_short("The shop storeroom");
    set_long("You are inside an old slightly ruined storeroom. The " +
	     "storeroom is quite bare except for some cupboards on " +
	     "the west wall.\n");
    
    add_exit(MIDDLE + "sage1", "north");
    
/*    add_item(({"cupboards", "cupboard"}), "@@cupboard");
    add_item(({"bottles", "bottle", "glass bottle", "glass bottles", "bottles in cupboard"}), "@@bottles"); */
    reset_xak_room();
}

/*
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
    if (botnum == 5)
      {
	  write("All the cupboards are bare.\n");
	  SAY(" looks through the cupboards.");
	  return "";
      }
    
    write(BS("The cupboards are mostly bare except for a few empty"
	     + " glass bottles.", 70));
    SAY(" looks through the cupboards.");
    return "";
}

string
bottles()
{
    if (botnum == 5)
      {
	  write("Examine what?\n");
	  return "";
      }
    write(BS("A few glass bottles have somehow remained unbroken here"
	     + " within the cupboard.", 70));
    SAY(" looks at the bottles in the cupboard.");
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
	  
	  if (botnum == 5)
	    {
		write("There are no more bottles in the cupboard.\n");
		return 1;
	    }
	  
	  clone_object(OBJ + "bottle.c")->move(TP);
	  prp = TP->query_prop("_player_i_black_dragon_quest");
	  TP->add_prop("_player_i_black_dragon_quest",prp | 1);
	  write("You get a glass bottle from the cupboard.\n");
	  SAY(" gets a bottle from the cupboard.\n");
	  botnum++;
	  return 1;
      }
    return 0;
}

*/





