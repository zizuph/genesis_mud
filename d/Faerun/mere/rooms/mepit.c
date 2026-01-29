/*
 * Path in the Mere of Dead Men
 * -- Finwe, July 2006
 * Modified by Nerull 2018 for boss encounter.
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "/d/Faerun/guilds/fire_knives/guild.h";

#define VAMPIRES_OBJ_DIR  "/d/Faerun/guilds/vampires/obj/"

inherit BASE_MERE;

int searched_here = 0;
object found_item = 0;

//#define SIGNET_RING_QUEST_LASTSTEP
 
 
// A reasonable way to reset the quest. Every 2.5 minutes.
void
reset_quest()
{
    searched_here = 0;
}


string do_search(object searcher, string str)
{
    object remains;
    
    if (str == "ditch" || str == "shadowy ditch")
    {
        if (present("_quest_assassin_boss", this_object()))
        {
            return "The alert dark clad assassin is lurking "
            +"relatively close to it, so you don't dare to complete "
            +"the search.\n";    
        }
        
        if (searched_here > 0)
        {
            return ""; 
        }
        
        if (!this_player()->query_prop(FIREKNIVES_ON_GURUQUEST))
        {
            return ""; 
        }
        
        if (objectp(remains = present("_quest_token", this_player())))
        {
            return "";
        }
        
        // Fire Knives Guru quest
        if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 0)
        {
            return "";
        }
        
        if(this_player()->test_bit(DOMAIN, SIGNET_RING_QUEST_GROUP, 
        SIGNET_RING_QUEST_BIT))
        {
            return "";
        }
        
        searched_here++;
        
        string item = one_of_list(({
            "obj/quest_token",
        }));
        
        tell_room(this_object(), QCTNAME(this_player()) + " finds " 
        + "something in the shadowy ditch.\n", this_player());
            
        found_item = clone_object(FIREKNIVES_GUILD_DIR + item);
        
        found_item->move(this_player(), 1);
        
        set_alarm(150.0, 0.0, &reset_quest());
        
        return "You find a platinum signet ring among some discarded "
        +"clothing in the shadowy ditch. The ring has the letters "
        +"A.M engraved into it, suggesting it belonged Arnt Mittet, one "
        +"of the six nobles Kyri tasked you to retire. You believe Arnt "
        +"Mittet is dead, and you think the ring will sufficiently "
        +"be evidence enough that this noble or associate no "
        +"longer dreams.\n";    
    }
    
    return "";
}


void
create_faerun_room()
{
    setuid();
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 5);
    
    set_short("Somewhere at the bottom of a dark stinking pit");
    
    set_long("Somewhere at the bottom of a dark stinking pit. Sharp "
    +"rocks, pebbbles and old skeletal remains are littered "
    +"everywhere. A painting is hanging on the west wall. Swamp "
    +"water is trickling in from above and vanishes "
    +"into some fine cracks in the ground. There is some distance up "
    +"and out of this miserable reeking place.\n");
    
    add_item(({"wall", "walls"}),
    "The walls are of solid rock and is jagged and easily "
    +"scalable. There is a painting hanging on the west wall.\n");
    
    add_item(({"up", "roof", "ceiling"}),
    "About thirty feet above your head, you can see the exit of the "
    +"pit.\n");
    
    add_item(({"floor", "ground"}),
    "The ground is uneven and a natural part of the environment. There "
    +"are many sharp rocks littered about that would be quite "
    +"hazardous for anyone falling in from above. Old skeletal remains " 
    +"of animals and humanoids alike can also be seen about. There "
    +"are a few fine cracks aswell that allows drainage for the incoming "
    +"swamp water from above and a shadowy ditch near the west wall.\n");
    
    add_item(({"rocks", "sharp rocks"}),
    "They are the size of small boulders and is rather pointy. You "
    +"suspect several creatures and the occasional adventurer has "
    +"met their end on these rocks.\n");
    
    add_item(({"old skeletal remains", "skeletal remains", "remains"}),
    "Those sad remains are all what's left of unlucky creatures or "
    +"adventurers meeting their end by the fall. They don't look "
    +"particulary interesting though.\n");
    
    add_item(({"fine cracks", "crack", "cracks"}),
    "You see several of these fine cracks in the ground. They are "
    +"about an inch in width and maybe several feet in lenght. The "
    +"swamp water trickling in from above drains away in these "
    +"cracks.\n");
    
    add_item(({"swamp water", "water"}),
    "You notice some swamp water trickles in from above and "
    +"drains away in the fine cracks in the ground. The reek "
    +"is unbearable though.\n");
    
    add_item(({"ditch", "shadowy ditch"}),
    "It's a rough natural formation in the ground near the "
    +"west wall of the pit. You notice it contains something "
    +"that is probably discarded by someone on purpose.\n");
    
    room_add_object(VAMPIRES_OBJ_DIR  + "vamp_painting6");
    
    add_item(({"distance"}),
    "The distance out of this dark pit is about thirty feet up.\n");
    
    add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "mecave", "up");
	
	add_npc(NPC_DIR +"quest_assassin_boss", 1);
}


public void
init()
{
    ::init();
}


void
reset_faerun_room()
{
    searched_here = 0;
    found_item = 0;
}