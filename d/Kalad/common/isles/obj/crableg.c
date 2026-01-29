 /*****************************************************************************
*  /d/Kalad/common/isles/npc/crableg.c
*
*  OBJ: Crab Leg
*
*  Created November 2020, Greneth
*
 *****************************************************************************/

 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include "../local.h"

 /*****************************************************************************
*  Inherits
 *****************************************************************************/
inherit "/std/leftover";

 /*****************************************************************************
*  Prototypes
 *****************************************************************************/
public int          crack_leg(string str);

void
create_leftover()
{
   set_name("crab leg");
   add_name("leg");
	add_name("_crab_leg");
   set_long("A large spiny leg from an oversized crab.\n");
   set_amount(50);
}

 /*****************************************************************************
*  Function name: init
*  Description  : Adds some actions
 *****************************************************************************/
public void
init()
{
   ::init();
   add_action(crack_leg, "crack");
}

 /*****************************************************************************
*  Function name: crack_leg
*  Description  : Cracks open a crab leg for meat
*  Arguments    : string str - what the player typed after the verb
*  Returns      : 1 - success, 0 - failure
 *****************************************************************************/
public int
crack_leg(string str)
{
   object cleg, cmeat;
    
   setuid();
   seteuid(getuid());
    
   if(!strlen(str))
   {
      notify_fail("Crack what?\n");
      return 0;
   }
   
   if (str != "crab leg")
   {
      notify_fail("Crack what exactly?\n");
      return 0;
   }     
    
   cleg = present("_crab_leg", this_player());
    
   if(!objectp(cleg))
   {
      notify_fail("You don't seem to have any crab legs on you.\n");
      return 0;
   }

   cmeat = clone_object(OBJ + "crabmeat.c");
   cmeat->move(TP); 
   cleg->remove_object();
   write("You grab hold of the crab leg with both hands and quickly "
	+ "crack it open. You find some crab meat inside!\n");
   say(QCTNAME(this_player()) + " cracks open a crab leg and finds some "
	+ "meat inside.\n");
	
   return 1;
}