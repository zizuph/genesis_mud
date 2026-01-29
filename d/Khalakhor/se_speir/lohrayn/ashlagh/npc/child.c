//
// a random child in the school
//
// Zima  - June 18, 1998
//
// Refactored - TAPKAH, 08/2021
//

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
 
inherit "/std/monster";
 
#define  ADJ (({"red-headed","pug-nosed","annoying","giggling", "shy",  \
                "black-haired","blue-eyed","blond-haired","well-behaved", \
                "brown-haired","green-eyed","brown-eyed","dirty"}))
 
int    has_armed=0;
string pro;
 
//
// arm_me
//
void arm_me ()
{
  if (has_armed) return;
  seteuid(getuid());
  if (query_gender())
    clone_object(COM_ARM+"dress")->move(TO);
  else {
    clone_object(COM_ARM+"shirt_cloth")->move(TO);
    clone_object(COM_ARM+"breeches")->move(TO);
  }
  command("wield all");
  command("wear all");
  has_armed = 1;
}
 
//
// create_monster
//
void create_monster()
{
  string adj=ADJ[(random(sizeof(ADJ)))];
  int    gender=random(2);
  set_gender(gender);
  set_name("kid");
  set_race_name("human");
  add_name(({"child","villager"}));
  set_adj(adj);
  if (query_gender()) {
    set_long(
             "She is a "+adj+" girl human, one of the children who should "+
             "probably be studying hard in school but isn't.\n");
    add_name("girl");
    add_adj("girl");
    set_short(adj+" girl human");
    pro="her";
  }
  else     {
    set_long(
             "He is a "+adj+" boy human, one of the children who should "+
             "probably be studying hard in school but isn't.\n");
    set_short(adj+" boy human");
    add_adj("boy");
    add_name("boy");
    pro="his";
  }
 
  default_config_npc(10);
  set_skill(SS_UNARM_COMBAT, 10);
  set_skill(SS_DEFENCE, 10);
  set_skill(SS_PARRY,   10);
 
  set_random_move(60);
  set_act_time(60);
  add_act("emote kicks a stone across the ground.");
  add_act("emote giggles inanely.");
  add_act("emote snickers at you.");
  add_act("emote pokes you in the ribs and giggles.");
  add_act("emote sticks "+HIS_HER(TO)+" tongue out at you.");
 
  set_default_answer("Ask the Marm! I'm not 'sposed to talk to strangers.");
 
  set_alignment(100);
  set_exp_factor(100);
  set_size_descs("short", "of normal width");
}
 
//
// my_intro
//
void
my_intro (string str)
{
  switch (random(5))
    {
    case 0: command("emote sticks "+pro+" tongue out at you.");    break;
    case 1: command("giggle");                                     break;
    case 2: command("snicker");                                    break;
    case 3: command("emote shies away.");                          break;
    default:command("say I'm not 'sposed to talk to strangers.");
    }
}

void
introduce (string name)
{
  my_intro(name);
}

void
add_introduced (string n)
{
  my_intro(n);
}
