/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>
inherit "/sys/global/money.c";

inherit  XAKINROOM

int mcan = 2;
object wraith, wraith2;

void
reset_xak_room()
{
    int mcan = 2;
}

void
create_xak_room()
{
    set_short("The North Crypt");
    set_long(BS(
		"You are in at the end of the north corridor of the crypt beneath"
		+ " the temple of Mishakal. Coffins line the walls here"
		+ " and the stench of death assails your nostrils. You"
		+ " feel danger here, this is a place for the DEAD!", 70));
    
    add_exit(CDIR + "northcrypt3.c", "west", 0);
    
    /*      add_cmd_item("button","push","@@button");
     *      add_cmd_item("button","pull","@@pull");
     */
    add_item(({"crypt", "coffin", "coffins"}), "@@coffin");
    INSIDE
      DARK
}

/*
button()
{
    object drac;
    drac=clone_object("/d/Krynn/solace/graves/mnstrs/skeletal_possum.c");
    drac->move_living("xxx",TO);
}

pull()
{
    move_coins("platinum",42,0,TP);
}
*/

string
coffin()
{
    if (!mcan)
      {
	  write(BS("You examine the surrounding crypt and coffins."
		   + " Everything seems normal. Well as normal as can be"
		   + " expected for such a gloomy place as this.", 70));
	  return "";
      }
    if (mcan == 2)
      {
	  write(BS("You examine the crypt and the coffins when suddenly"
		   + " two ghostly forms emerges from the coffins!", 70));
	  SAY(" is poking around the coffins examining them"
	      + " when suddenly two ghostly figures emerge from the coffins!");
      } 
    else /* mcan == 1 */
      {
	  write(BS("You examine the crypt and the coffins when suddenly"
		   + " a ghostly figure emerges from a coffin!", 70));
	  say(BS(QCTNAME(TP) + " is poking around the coffins examining them"
		 + " when suddenly a ghostly figure emerges from a coffin!", 70));
      }
    seteuid(getuid(this_object()));
    if (mcan)
      {
	  mcan--;
	  wraith = clone_object(MONSTER + "wraith.c");
	  wraith->move(TO);
      }
    if (mcan)
      {
	  mcan--;
	  wraith2 = clone_object(MONSTER + "wraith.c");
	  wraith2->move(TO);
      }
    return "";
}


