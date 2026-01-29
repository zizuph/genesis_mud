/* /d/Faerun/guilds/fire_knives/rooms/spawm_room.c
 *
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;

object quest_npc1;
object quest_npc2;
object quest_npc3;
object quest_npc4;
object quest_npc5;

//string query_qnpcs_status(string str);


// Spawn locations
string *spawn_locations = ({
    "/w/nerull/idle",
    "/w/nerull/workroom",
    "/w/nerull/testing_50",
});


void
reset_quest_spawns()
{
    setuid();
    seteuid(getuid());
    
    if (!quest_npc1)
    {
        quest_npc1 = clone_object(FIREKNIVES_GUILD_DIR + "npc/quest_npc1");
        quest_npc1->move(this_object(), 1);
    }
    
    if (!quest_npc2)
    {
        quest_npc2 = clone_object(FIREKNIVES_GUILD_DIR + "npc/quest_npc2");
        quest_npc2->move(this_object(), 1);
    }
    
    if (!quest_npc3)
    {
        quest_npc3 = clone_object(FIREKNIVES_GUILD_DIR + "npc/quest_npc3");
        quest_npc3->move(this_object(), 1);
    }
    
    if (!quest_npc4)
    {
        quest_npc4 = clone_object(FIREKNIVES_GUILD_DIR + "npc/quest_npc4");
        quest_npc4->move(this_object(), 1);
    }
    
    if (!quest_npc5)
    {
        quest_npc5 = clone_object(FIREKNIVES_GUILD_DIR + "npc/quest_npc5");
        quest_npc5->move(this_object(), 1);
    }
    
    return;
}


int
locationnpcs()
{
	write(" | --------------------------------------------------------------\n");
	
	if (quest_npc1 != 0)
    {
		write(" | Location qnpc1: "+MASTER_OB(environment(quest_npc1))+"\n");
	}
	
	if (quest_npc2 != 0)
    {
		write(" | Location qnpc2: "+MASTER_OB(environment(quest_npc2))+"\n");
	}
	
	if (quest_npc3 != 0)
    {
		write(" | Location qnpc3: "+MASTER_OB(environment(quest_npc3))+"\n");
	}
	
	if (quest_npc4 != 0)
    {
		write(" | Location qnpc4: "+MASTER_OB(environment(quest_npc4))+"\n");
	}
	
	if (quest_npc5 != 0)
    {
		write(" | Location qnpc5: "+MASTER_OB(environment(quest_npc5))+"\n");
	}
   
   
    write(" | --------------------------------------------------------------\n");
    
    return 1;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    setuid();
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Quest_npc spawnroom");
    
    set_long("This room exist for the sole purpose of "
    +"You can 'monitor npcs' to see the locations of "
    +"the spawns.\n"); 
    
    set_alarm(10.0, 900.0, &reset_quest_spawns());
    
    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


/*
 * Function name: init
 * Description  : Add functions to the room
 */
void
init()
{
    ::init();

    add_action(locationnpcs, "monitor");
}
