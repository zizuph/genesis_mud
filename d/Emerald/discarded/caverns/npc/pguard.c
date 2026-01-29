/*
 * PGUARD.c
 * This npc is cloned into the rooms 2guardrm and 1guardrm by
 * the clone handler /d/Emerald/mountains/caverns/caverns_clone_handler.c
 * Uses the new /d/Emerald/std/emerald_monster
 * - Alaron September 13, 1996
 */

#include "defs.h"

inherit EMERALD_MONSTER;

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>

void clone_key();

void
create_emerald_monster()
{
   set_name("guard");
   set_race_name("goblin");
   add_name("pirate");
   set_short("lazy squat guard");
   set_long("   This guard looks as though he would rather be doing "+
	    "anything else but this job. His uniform (whats left of it) "+
	    "is covered in filth, mud, and the rank smell of day-old "+
	    "alcohol.\n");

   set_pshort("guards");
   set_stats(({50,40,45,33,29,55}));
   set_hp(TO->query_max_hp());
   set_skill(SS_WEP_SWORD, 47);
   set_skill(SS_DEFENCE, 40);
   set_skill(SS_PARRY, 35);

   set_chat_time(8);

   add_chat("This job is horrible!");
   add_chat("I can't believe I got drafted into this duty.");
   add_chat("Why can't someone else guard these freaks, I've got "+
	    "better things to do.");
   add_chat("Well, at least it smells nice down here.");

   set_speak( ({"Look you, if I wanted to speak to you, I would have.",
		"Hey! Get back! Keep your distance or I'll toss ya "+
		"in your own cell!",
		"Can't you seem I'm on duty? Stop pestering me!",
		"Go away!",
		"Look, I'm not in the mood for chatting, I'm trying "+
                "to do a job here!"}));

   MONEY_MAKE_CC(10+random(10))->move(TO);
   MONEY_MAKE_SC(3+random(3))->move(TO);
   seteuid(getuid(this_object()));

   add_equipment( ({THIS_DIR +"arm/l_sword",
		    THIS_DIR +"arm/gjerkin",
		}));

   set_alarm(1.0,0.0, clone_key);

}


void
clone_key()
{
   object key;

   key = clone_object(THIS_DIR + "obj/g_key");
   key -> move(TO);

}




