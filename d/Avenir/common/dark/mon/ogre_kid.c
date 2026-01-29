// -*-C++-*-
// file name: ~Avenir/common/dark/mon/ogre_kid.c
// creator(s):  Boriska
// last update: Jan 25 1995
// purpose:     Inhabitant of Avenir tunnels
// note:        Scans room for corpses during combat and eats leftovers.
// bug(s):
// to-do:     

#include "/d/Avenir/common/dark/dark.h"

inherit "/d/Avenir/inherit/corpse_eater"; 
inherit "/d/Avenir/inherit/insult";
inherit "/d/Avenir/inherit/wsmap";  // helps to set right weapon skill

void
create_monster()
{
  if (!IS_CLONE)
    return;
  
  set_name ("ogre");
  add_name ("kid");
  set_short ("funny ogre kid");
  set_race_name( "ogre kid");

  add_adj ("funny");

  set_long (
	   "This offspring of ogre family is hanging out here, picking in\n"
	   + "his nose and playing with some toys. As you look closer you\n"
	   + "realize with astonishment that he is building a castle from\n"
	   + "skulls and bones!\n" );

  set_stats ( ({60,60,80,30,30,50}) );
  set_skill (SS_DEFENCE, 20);
  set_skill (SS_PARRY, 20);

  set_alignment (0);  
  
  add_prop (LIVE_I_SEE_DARK, 1);
  
  set_chat_time (15);
  add_chat ("You@@insult@@!");
  
  set_cchat_time(2);
  add_cchat ("Get out before my mom and dad come!");
  add_cchat ("I'll place your skull in the basement of my castle.");
  add_cchat ("Oboronosposobnost!");
  // Russian word meaning "ability to self-defence"
  // famous for 7 'o's
}

void
equip_me()
{
  object weap;
  object to = this_object();

  seteuid(getuid());
  weap = clone_object( OBJ + "rweap");
  set_skill (skill[weap->query_wt()], 30);
  weap->move(to, 1);
  command ("wield all");
  
  clone_object( OBJ + "rchain")->move(to, 1);
  clone_object( OBJ + "rhelmet")->move(to, 1);
  clone_object( OBJ + "skull")->move(to, 1);
  command ("wear all");
}
