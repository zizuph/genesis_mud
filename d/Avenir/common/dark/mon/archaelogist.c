// -*-C++-*-
// file name: /d/Avenir/common/dark/mon/archaelogist.c
// creator(s): Boriska, Nov 1994
// last update: minor chat revisions by Tepisch, Dec 94
//		Denis, Aug'96: Removed triggers from intro process.
// purpose: Magic Square quest
// note:
// bug(s): 
// to-do:                                         

inherit "/d/Avenir/common/dark/mon/give_get";

#include "/d/Avenir/common/dark/dark.h"

#include "/d/Avenir/include/magic_square.h"
// definitions for magic square quest

void
create_monster()
{
  set_name ("josen");
  set_long ("This scruffy human seems to be searching for something"+
	" important to him.  His pale skin doesn't seem to have seen" +
	" the light of day in a long while.\n");
  add_adj (({"dirty", "long-legged"}));
  set_race_name("human");
  set_title ("the Archaeologist Extraordinaire");
  set_gender (G_MALE);
  
  set_stats( ({40,40,40,60,60,40}) );
  set_skill(SS_WEP_POLEARM, 20);
  set_skill(SS_DEFENSE,20);
  set_skill(SS_AWARENESS, 50); // scholar types are smart
  add_prop (LIVE_I_SEE_DARK, 1);
  
  set_whimpy (30);

  set_alignment (500);
  set_race_name ("human");

  set_chat_time (5);
  add_chat ("I am an archaeologist, you know.");
  add_chat ("I've been searching this place for so long I've forgotten" +
	" what the Source looks like!");
  add_chat ("Something big moves down there.  Have you seen it?");
  add_chat ("I need that artifact, and I'll find it if its the last"+
	" thing I do.");
  add_chat ("It is said: Only in the depths shall you find that which"+
	" is high.");
  add_chat("It has no weight but cannot be carried in hands.");
  
  set_act_time (5);
  add_act(({"say It must be around here somewhere!", "despair"}));
  add_act("emote examines the ground closely.");
  add_act("emote starts to dig here.");
  add_act("emote gets a puzzled expression on his face.");
  add_act("starts to search here.");
  add_act("think");
  add_act("despair");
  
  add_ask( ({"help", "quest", "artifact"}), "@@give_quest_text", 1);
  add_ask ("for stones", "@@give_quest", 1);
  add_ask(({"slab", "about slab"}),
  "The ultimate horror of Avenir dwells under the black slab of stone.\n");
  // check for objects that are given is done in enter_inv
  remove_prop (NPC_M_NO_ACCEPT_GIVE);
}

void
equip_me ()
{
  seteuid(getuid());
  clone_object (OBJ + "shovel")->move(this_object());
  command ("wield all");
  clone_object(OBJ + "d_clothes")->move(this_object());
  clone_object(OBJ + "spectacles")->move(this_object());
  command ("wear all");
}
