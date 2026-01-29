/* 
 *
 * Bossroom. Last room in the instance.
 *
 * Nerull, 2021
 *
 */

#include "/d/Gondor/rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit RHOVANION_DIR + "dolguldur/std/base";

object boss;


void
remove_instance()
{
    remove_object();
}


/*
 * Function name: create_rav_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_dg_room()
{
    setuid();
    seteuid(getuid());

    add_prop(ROOM_I_INSIDE, 0);

    //add_npc(RHOVANION_DIR +"dolguldur/npc/cenlintie", 1);
    
    // Clean the instance from memory.
    set_alarm(7200.0, 0.0, &remove_instance());

    reset_room();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
	int mage_str;
	int mage_dex;
	int mage_con;
	int mage_int;
	int mage_dis;
	int mage_wis;
	
	
    if (interactive(ob))
    {
		if (!boss)
		{
			mage_str = ob->query_stat(0);
			mage_dex = ob->query_stat(1);
			mage_con = ob->query_stat(2);
			mage_int = ob->query_stat(3);
			mage_wis = ob->query_stat(4);
			mage_dis = ob->query_stat(5);
			
			boss = clone_object(RHOVANION_DIR +"dolguldur/npc/cenlintie");
			
			boss->set_stats( ({ mage_str, mage_dex, mage_con, mage_int, mage_dis, mage_wis}) );
			
			boss->move(this_object(), 1);			
		}
    }
}


/*
 * Function name: reset_room
 * Description  : Resets the room/states/npc spawns.
 */
void
reset_room()
{
 
}

