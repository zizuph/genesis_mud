// -*-C++-*- 
// file name:   ~Avenir/common/dark/mon/insane_ogre
// creator(s):  Boriska  Nov 1994
// last update: Feb 8 1995
// purpose:     Inhabitant of cavern in dark/l4
// note:        Helps his kin when attacked in nearby rooms.

#include "/d/Avenir/common/dark/dark.h"

inherit "/d/Avenir/inherit/helper";
inherit "/d/Avenir/inherit/insult";
inherit "/d/Avenir/inherit/wsmap";

void
create_monster ()
{
  set_name ("ogre");
  set_short ("insane ogre");
  set_race_name( "ogre");
  add_adj ("insane");
  set_long(
  	  "Trapped inside this cavern long time ago ogre tribe produced\n" +
	   "species like that one. The ogre is not normal, there's a clear\n"+
	   "look of insanity in his small eyes, which never stop moving and\n"+
	   "blinking. No muscle in his furry body stays still even for short\n"+
	   "time.\n" 
	    );

  set_stats ( ({80,80,100,40,40,80}) );

  set_random_move(10);
  
  set_chat_time (5);
  add_chat ("Me ogre, you're" + insult());

  set_act_time (5);
  add_act ("eeks");
  add_act ("yodel");
  add_act ("gag");
  add_act ("steam");
  
  set_helper_friends ( ({"ogre"}) );
  set_helper_actions ( ({
    "shout Everybody who wants to see completely insane person, come here!",
    "shout How interesting!",
    "emote stares at you in disbelief."
    }) );
  
  set_skill (SS_DEFENSE, 60);
  set_skill (SS_PARRY, 30);
  set_alignment (0);
}

void
equip_me ()
{
  object weap;
  weap = clone_object( OBJ + "rweap");
  set_skill (skill[weap->query_wt()], 60);
  weap->move(TO);
  command ("wield all");
  
  clone_object( OBJ + "rchain")->move(TO);
  clone_object( OBJ + "rhelmet")->move(TO);
  clone_object( OBJ + "rshield")->move(TO);
  clone_object( OBJ + "rleggings")->move(TO);
  command ("wear all");
}

