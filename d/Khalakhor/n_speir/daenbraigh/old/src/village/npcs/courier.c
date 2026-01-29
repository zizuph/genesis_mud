/*
 * Goblin village elder courier
 * TAPAKAH 03/2007
 */

#pragma strict_types

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../village/village.h"
#include "../../faction.h"

inherit "/d/Khalakhor/std/monster";
inherit DAENBRAIGH_NPC;

int remove_alarm_id;
object letter;

int offer_me(string str);
void flee_me();
void equip_me();
void wake_me();
void clear_alarm();

void
create_khalakhor_monster()
{
  
  if(! IS_CLONE)
    return;
  ::create_khalakhor_monster();

  set_name("snyggra");
  add_name(({"courier","snyggra","goblin",V_OBJID + "_courier"}));
  add_adj("plump");
  set_long("This goblin does not look like a typical inhabitant of the "+
	   "village. Although he looks sleepy, he does not appear overworked "+
	   "and his tummy has some roundness. He is looking mockingly at the "+
	   "large tent at the crossing. It seems that after all the drinks "+
	   "he've been consuming a couple more will topple him down.\n");

  set_base_stat(SS_STR,20,10);
  set_base_stat(SS_DEX,50,10);
  set_base_stat(SS_CON,50,10);
  set_base_stat(SS_INT,30,10);
  set_base_stat(SS_WIS,30,10);
  set_base_stat(SS_DIS,20,10);

  set_skill(SS_WEP_KNIFE,30);
  set_skill(SS_DEFENSE,40);
  set_skill(SS_UNARM_COMBAT,20);

  set_alignment(0);
  set_alarm(0.5,0.0,equip_me);
  set_faction(FACTION_DAENBRAIGH,FCT_VALUE_VILLAGER);
}

void
init_living()
{

  ::init_living();

  add_action(offer_me,"offer");
}

void
attacked_by(object enemy)
{
  ::attacked_by(enemy);
  set_alarm(1.0,0.0,flee_me);
}

void
flee_me()
{
  
  command("shout that was not part of my job!");
  tell_room(ENV(TO), QCTNAME(TO) + " runs off quickly.\n");
  if(present(letter, ENV(TO))) {
    tell_room(ENV(TO), QCTNAME(TO) + " picks something from the floor.\n");
    letter->remove_object();
  }
  remove_object();
}

void
equip_me()
{
  int i;
  int j = sizeof(V_GOBLIN_INV);
  
  setuid();
  seteuid(getuid());

  for(i=0;i<j;i++)
    clone_object(V_GOBLIN_INV[i])->move(TO);
  letter = clone_object(V_LETTER);
  letter->move(TO);
  command("wield all");
  command("wear all");
  add_prop(OBJ_M_HAS_MONEY,V_GOBLIN_MON*5);
}

int
offer_me(string str)
{
  int result;
  string ob_str, dest_str;
  object ob;

  if(str)
    if(
       sscanf(str,"%s",ob_str) == 1 ||
       ((sscanf(str,"%s to %s",ob_str,dest_str) == 2) &&
	(dest_str == "courier" || dest_str == "goblin" ||
	 dest_str == "snyggra")
	))
      if(ob = present(ob_str,TP)) {
	if(query_prop(V_IS_ASLEEP)) {
	  write("The courier doesn't seem to be in position to accept "+
		"any offers from anyone.\n");
	  return 1;
	}
	if(ob->query_alco_amount()) {
	  write("The courier hiccups and thanks you gratefully.\n");
	  write("The courier stares dreamingly at the drink.\n");
	  ob->move(TO,1);
	  result = drink_alco(ob->query_alco_amount(),0);
	  if(!result) {
	    command("say Sheesh, this is too strong even for me!");
	    write("The courier returns the drink to you.\n");
	    ob->move(TP,1);
	  }
	  else {
	    command("say Whee, that was quite in time!");
	    command("emote consumes the drink eagerly.");
	    if(query_intoxicated() > 50 + random(10)) {
	      write("It seems that your party had had too much...\n");
	      command("emote collapses on the floor");
	      write("As the courier falls down, a letter slips out of his "+
		    "pocket.\n");
	      add_prop(V_IS_ASLEEP,1);
	      letter->move(ENV(TO),1);
	      set_alarm(8.0,0.0,wake_me);
	    }
	  }
	}
	else {
	  command("emote sniffs disgustedly");
	  command("say who would drink THAT?\n");
	}
	return 1;
      }
  NF0("Offer what?\n");
}

void
wake_me()
{
  object elder;
  int result;
  
  command("emote suddenly sits up and rubs his eyes.");
  command("emote starts searching all his pockets anxiously.");
  if(present(letter,ENV(TO))) {
    command("emote sighs relieved.");
    command("pick letter");
    add_prop(V_IS_ASLEEP,0);
    set_intoxicated(0);
  }
  else {
    command("shout Where is it?? Where is it??");
    command("emote starts tearing his hair out in desperation.");
    command("say I've got to get to Aillin fast, very fast...");
    result = move(V_ROOM + "tent",1);
    write("Move resulted in " + result + "\n");
    command("say I've got ambushed on my way! The letter was stolen from me!");
    elder = present(V_ELDER, ENV(TO));
    if(! elder) {
      remove_object;
      return;
    }
    elder->add_prop(V_COURIER_REPORTED,1);
    elder->act_on_report();
    remove_alarm_id = set_alarm(60.0,0.0,remove_object);
  }
}

void
clear_alarm()
{
  remove_alarm(remove_alarm_id);
}

  
