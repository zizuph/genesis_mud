/*
 * Hammerhands guildmaster npc
 * TAPAKAH, 10/2005
 */

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h";

#include "../../daenbraigh.h"
#include "../../hhands/hhands.h"
#include "../../faction.h"

inherit "/d/Khalakhor/std/monster";
inherit "/d/Genesis/lib/intro";
inherit DAENBRAIGH_NPC;

void equip_me();
string join_reply();
string ways_reply();

void
create_khalakhor_monster()
{
  if(! IS_CLONE)
    return;
  ::create_khalakhor_monster();

  set_name("Basamhach");
  add_name(({"Basamhach","guildmaster",HH_OBJID + "_guildmaster"}));
  add_adj(({"intense","muscular"}));
  set_race_name("goblin");
  set_long("This intense goblin is sitting behind a large table, stroking "+
	   "lovingly his beloved weapon - a polished iron club. It looks "+
	   "like he is awaiting your questions.\n");
  set_gender(G_MALE);

  set_base_stat(SS_STR,190,10);
  set_base_stat(SS_DEX,160,10);
  set_base_stat(SS_CON,190,10);
  set_base_stat(SS_INT,140,10);
  set_base_stat(SS_WIS,140,10);
  set_base_stat(SS_DIS,170,10);

  set_skill(SS_WEP_CLUB,100);
  set_skill(SS_DEFENSE,100);
  set_skill(SS_PARRY,100);
  set_skill(SS_AWARENESS,100);

  add_prop(HH_MEMBER,HH_ACCESS_COUNCIL);
  add_prop(OBJ_M_NO_ATTACK,"You feel yourself unable to do that.\n");
  add_prop(OBJ_M_NO_MAGIC_ATTACK,"You feel yourself unable to do that.\n");
  
  set_faction(FACTION_DAENBRAIGH,FCT_VALUE_HH_NPC);
  set_default_answer("say Do you want to learn about guild of Hammerhands?",1);

  add_ask(({"guild","hammerhands"}),
	  "say the guild helps good bludgeon fighters reach the mastery of "+
	  "their weapon.",
	  1);
  add_ask(({"club","mastery","weapon","bludgeon"}),
	  "say one who joins hammerhands can learn new ways of using the "+
	  "bludgeon.",
	  1);
  add_ask(({"join"}),
	  &join_reply(),
	  0);
  add_ask(({"ways","abilities"}),
	  &ways_reply(),
	  0);
  add_ask(({"tax"}),
	  "say the tax is moderate.",
	  1);
  add_ask(({"leave","leaving","price"}),
	  "say you may leave, but you have to pay with money or experience.",
	  1);
	  
}

string
join_reply()
{
  command("say only confident veterans of a bludgeon weapon, like club, "+
	  "polearm or axe may join.");
  command("say only ones who are stand for Daenbraigh may join.");
  command("say any race but weak elves may join, but you must be strong "+
	  "enough.");
  command("say you can leave later, but at a price.");
  return "";
}

string
ways_reply()
{
  command("say you will learn new attacks with a bludgeon weapon.");
  command("say you will learn to mend your weapons a bit.");
  command("say you will learn to become a more successfull traveller.");
  command("say you will pay a tax, of course.");
  return "";
}

void
equip_me()
{
  setuid();
  seteuid(getuid());

  clone_object(HH_HELMET)->move(TO);
  clone_object(HH_CHAINMAIL)->move(TO);
  clone_object(HH_SHIELD)->move(TO);
  clone_object(HH_CLUB)->move(TO);

  command("wear helmet");
  command("wear chainmail");
  MONEY_MAKE_SC(120+random(60))->move(TO);
}

