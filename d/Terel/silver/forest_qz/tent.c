/* File         : /d/Terel/silver_new/forest_qz/tent.c
 * Creator      : Pasqua	
 * Date         : April 2000         
 * Purpose      : Bandit Tent
 * Related Files: 
 * Comments     : 
 * Modifications: Udana: added npcs and - USE CREATE_TEREL_ROOM!
 */

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>

#define CARAVAN_START ROAD + "road02"

inherit STDROOM;

object leader;

public object give_leader()
{
	if(!leader)
		return clone_object(NPC + "bandit_leader");
	tell_room(TO, QCTNAME(leader) + " suddenly leaves the tent, and runs into the forest.\n");
	return leader;
}

public void reset_terel_room()
{
	if(!leader)
	{
		leader = clone_object(NPC + "bandit_leader");
		leader->move_living("from the forest", TO);
	}
}

public void
create_terel_room()
{
   INSIDE;

   set_short("Inside a green ridge tent");
   set_long("The tent is about 10 metres high and could easily fit thirty people of human " +
        "size, a large campfire made out of wood and clay can be seen in the middle of this " + 
	    "tent. Next to most sides of the tent, blankets made out of fur can be seen.\n");

   add_exit(FOREST_QZ + "forest_t11", "out", 0, 0);

   add_item(({"large campfire","campfire"}),"The large campfire is made out of wood and clay " +
	    "and it sparkles and crackles wildly.\n");
   add_item(({"blanket","blankets","beds"}),"Its about 20 of the furmade blankets that can be " +
	    "seen in every direction and every corner against the tent walls. The bandits seem to " +
	    "rest and sleep on them when they have the time to do so.\n");
   add_item(({"ground","floor"}),"The ground inside this tent is very dirty.\n");
   add_npc(NPC + "bandit", 3);
	reset_room();
   
}

public void init()
{
	::init();
	(CARAVAN_START)->caravan_block();
}