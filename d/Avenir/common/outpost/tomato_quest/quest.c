// file name:        /d/Avenir/common/outpost/tomato.c
// creator(s):       Denis, Jul'96
// purpose:          The tomato quest main object (SMIS).
#pragma strict_types

#include <cmdparse.h>
#include <macros.h>

#include "/d/Avenir/smis/smis.h"
#include "/d/Avenir/smis/sys/statserv.h"

#include "tomato_drop.h"

inherit SMIS_MODULE_QUEST;

int do_lean(string str);
int do_drop(string str);

void create_quest()
{
    set_module_id("tomatoq");
    set_module_description("The outpost tomato throw quest.");
    set_quest_long_description(
       "The quest is to help a young dwarf throw a tomato at an elf "+
       "wearing clean white clothing.\n");
    set_quest_bit(TOMATOQ_GROUP, TOMATOQ_BIT);

    add_quest_variant("The only variant to complete the quest.",
		      TOMATOQ_QUEST_XP, 0, 0);

    set_create_notification(({ TOMATOQ_TOWER }));

    set_location_npc(TOMATOQ_BRAT_LOC,
		     "/d/Avenir/common/outpost/tomato_quest/brat");
    set_location_npc(TOMATOQ_SNOB_LOC,
		     "/d/Avenir/common/outpost/tomato_quest/snob_elf");
    set_location_object(TOMATOQ_BRAT_LOC,
		        "/d/Avenir/common/outpost/tomato_quest/tomato_box");
    set_location_commands(TOMATOQ_TOWER,
		          ({ "lean", MASTER, "do_lean",
			     "drop", MASTER, "do_drop" }));
}

int do_lean(string str)
{
    object tp = this_player(),
	   target_npc;
    string target_room_text;

//    if(!query_module_enabled())
//	return 0;
    
    if (!strlen(str) || !parse_command(str, ({ }),
	    "'out' [of] [the] 'window'", str))
    {
	return notify_fail("Lean where?\n");
    }

    if(!find_object(TOMATOQ_SNOB_LOC))
	TOMATOQ_SNOB_LOC->teleledningsanka();

    target_npc = query_cloned_npc(TOMATOQ_SNOB_LOC);

    // 3 text possibilities:
    // target_npc is dead
    target_room_text = "nothing and nobody special right now";
    if (target_npc != 0)
    {
	// target_npc is in the fort, but not beneath the tower
	target_room_text =
	             "someone in the fort wearing bright white clothing";
	if(file_name(environment(target_npc)) == TOMATOQ_SNOB_LOC)
	{
	    // target_npc is beneath the tower
	    target_room_text = "someone dressed in bright white clothing "+
	    		       "standing directly below the window";
    	} 
    }

    write("You lean out the window and look at the ground beneath "+
	  "the tower.\nYou see " + target_room_text + ".\n");
    say(QCTNAME(tp) + " leans out the window and looks down.\n");

    STATSERV_LOG_EVENT("outpost", "Leaned out of the window");
    return 1;
}

int do_drop(string str)
{
    string target_text = "toward the ground.";
    object tomato_mush,
	   tomato,
	   tomato_stain,
	   target_npc;
    int    hit_target = 0;

//    if(!query_module_enabled())
//	return 0;
    
    if (!parse_command(str,
	    FIND_STR_IN_OBJECT(TOMATOQ_QUEST_ID, this_player()),
	    "[a] / [the] %o [out] [of] [the] 'window'", tomato))
    {
	return notify_fail("Drop what?\n");
    }
    
    STATSERV_LOG_EVENT("outpost", "Dropped tomato out of the window");

    if (!find_object(TOMATOQ_SNOB_LOC))
	TOMATOQ_SNOB_LOC->teleledningsanka();

    target_npc = query_cloned_npc(TOMATOQ_SNOB_LOC);
    
    // test if target_npc is dead, if not, see if in the target room
    if(target_npc)
    {
    	// test room of target_npc
    	if (file_name(environment( target_npc )) == TOMATOQ_SNOB_LOC)
        {
	    hit_target = 1;
	    target_text = "directly toward the person in white!";
    	}
    }

    // drop it and replace with tomato_mush
    write("You drop the tomato out the window and it plummets " +
	  target_text + "\n");
    say(QCTNAME(this_player()) + " drops something out the window.\n");

    // tell the room about the falling tomato
    if (hit_target)
    {
    	tell_room(TOMATOQ_SNOB_LOC,
	       "Something red plummets from the sky and splatters all over "+
	       QCTNAME(target_npc) + "'s clothes!\n" );
	
	// add the tomato description to snob_elf, stain his clothes
	tomato_stain = clone_object(TOMATOQ_DIR + "tomato_stain");
	tomato_stain->move( target_npc );
	tomato_stain->set_remove_timer();

	if(!this_player()->query_prop(TOMATOQ_QUEST_VERSION))
	{
	    STATSERV_LOG_EVENT("outpost",
			       "Hit snob elf without getting quest first");
	    tomato->remove_object();
	    return 1;
	}
	
	// Quest ending
	tell_room(TOMATOQ_TOWER,
		  "You hear a faint cheer through the window.\n");

        reward_quest(this_player(), 0);

	TOMATOQ_WRITE_LOG("Completed the quest and got "+
	    TOMATOQ_QUEST_XP +" XP!\n");
	STATSERV_LOG_EVENT("outpost", "Completed the tomato quest");
	// remove the quest-start subloc.
	this_player()->remove_prop(TOMATOQ_QUEST_VERSION);
    }
    else
    {
    	tell_room(TOMATOQ_SNOB_LOC,
	       "You are narrowly missed by a falling red object!\n" );
	// if not landing on quest person, replace with tomato_mush
	tomato_mush = clone_object(TOMATOQ_DIR + "tomato_mush");
	tomato_mush->move(TOMATOQ_SNOB_LOC);
    }

    tomato->remove_object();
    return 1;
}
