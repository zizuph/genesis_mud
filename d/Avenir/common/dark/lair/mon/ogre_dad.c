// Ogre dad for Avenir tunnels
// Made by Boriska@Genesis
// July 1994

#include "/d/Avenir/common/dark/dark.h"

inherit "/d/Avenir/inherit/helper";
inherit "/d/Avenir/inherit/insult";
inherit "/d/Avenir/inherit/wsmap";

void
create_monster ()
{
  if (!IS_CLONE)
    return;
  
  set_name ("ogre");
  add_name ("dad");
  set_short ("insane ogre dad");

  set_race_name( "ogre dad");
  add_adj ("insane");
  set_long (
       "This huge ogre looks is wandering around looking for some poor\n" +
       "adventurer to trap between his hands. His small angry eyes \n" +
       "under low jutting eyebrows and heavy jaws promise nothing\n" +
       "good to you.\n"
	    );

  set_stats ( ({80,80,100,50,50,80}) );

  add_prop (LIVE_I_SEE_DARK, 1);
  
  set_chat_time (10);
  add_chat ("Get lost, you" + insult());
  set_helper_friends ( ({"ogre"}) );
  // set helper actions here too
    
  set_skill (SS_DEFENSE, 60);
  set_skill (SS_PARRY, 30);
  
  set_alignment (0);
  seteuid(getuid());
}

void
equip_me()
{
  object weap;
  weap = clone_object( OBJ + "rweap");
  set_skill (skill[weap->query_wt()], 50);
  weap->move(this_object());
  command ("wield all");
  
  clone_object( OBJ + "rchain")->move(this_object());
  clone_object( OBJ + "rhelmet")->move(this_object());
  clone_object( OBJ + "rshield")->move(this_object());
  clone_object( OBJ + "rbracers")->move(this_object());
  clone_object( OBJ + "bones")->move(this_object());
  command ("wear all");
}

