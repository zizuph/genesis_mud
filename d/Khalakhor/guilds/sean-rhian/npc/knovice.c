/* Novishagh (novice) roaming the kirk
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/5/98     Created
*/

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h" 
#define  VEST (({"robe","cincture","tonsure"}))

inherit  SR_NPC+"monkbase";
inherit  SR_NPC+"vowintro";

void
arm_me ()
{
  vest_me(VEST);
  (present("tonsure",TO))->set_color("white");
  (present("cincture",TO))->set_color("purple");
}
 
void create_khalakhor_human ()
{
  int     stat=(20+random(20));
  string* adj;
  ::create_khalakhor_human();
  setup_base_manach(stat, "novishagh");
  adj = query_adj(1); /* 1 means return list of all adjectives */
  set_long(
           "He is a "+adj[0]+" "+adj[1]+" "+(query_race_name())+", his habit "+
           "identifying him as a novice member of the Order of Sean-Rhian.\n");
  add_prop(NPC_M_NO_ACCEPT_GIVE,1);
  set_default_answer("@@defans");
  set_act_time(30);
  add_act("emote mumbles a silent prayer.");
  add_act("emote puts his hands together prayerfully.");
  add_act("emote bows his head prayerfully.");
  add_act("emote raises his hands and sings a quiet chant.");
  add_act("emote folds his arms into the sleeves of his robe.");
  add_act("emote nods at you hospitably.");
  add_act("emote chants in an ancient tounge.");
  add_act("emote traces three circles before his face.");
  add_act("emote genuflects on one knee and prays.");
}

