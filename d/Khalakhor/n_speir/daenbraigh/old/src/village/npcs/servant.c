/*
 * Goblin village elder servant
 * TAPAKAH 04/2005
 */

#pragma strict_types

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h";

#include "../../daenbraigh.h"
#include "../../village/village.h"
#include "../../faction.h"

inherit "/d/Khalakhor/std/monster";
inherit DAENBRAIGH_NPC;

int room;

int bribe_me(string str);
void move_me();
void flee_me();
void equip_me();

void
create_khalakhor_monster()
{
  
  if(! IS_CLONE)
    return;
  ::create_khalakhor_monster();

  set_name("fryesk");
  add_name(({"servant","fryesk","goblin",V_OBJID + "_servant"}));
  add_adj("plump");
  set_long("This goblin does not look like a typical inhabitant of the "+
	   "village. Although he looks sleepy, he does not appear overworked "+
	   "and his tummy has some roundness. He is looking mockingly at his "+
	   "surroundings.\n");
  room = 0;
  set_alarm(10.0,40.0+40.0*rnd(),move_me);
  set_base_stat(SS_STR,40,10);
  set_base_stat(SS_DEX,30,10);
  set_base_stat(SS_CON,50,10);
  set_base_stat(SS_INT,20,10);
  set_base_stat(SS_WIS,20,10);
  set_base_stat(SS_DIS,40,10);

  set_skill(SS_WEP_KNIFE,30);
  set_skill(SS_DEFENSE,50);
  set_skill(SS_UNARM_COMBAT,40);

  set_alignment(0);
  set_alarm(0.5,0.0,equip_me);
  set_faction(FACTION_DAENBRAIGH,FCT_VALUE_VILLAGER);
}

void
init_living()
{

  ::init_living();

  add_action(bribe_me,"bribe");
}

int
bribe_me(string str)
{
  string who;
  
  if(!str) {
    notify_fail("Bribe who?\n");
    return 0;
  }
  if(sscanf(str,"%s",who) == 1) 
    if(who == "servant") {
      write("You try to bribe the servant, but fail.\n");
      return 1;
    }
  notify_fail("Bribe who?\n");
  return 0;
}

void
move_me()
{
  if(room)
    command("out");
  else
    command("tent");
  room = 1 - room;
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

  command("wield all");
  command("wear all");
  add_prop(OBJ_M_HAS_MONEY,V_GOBLIN_MON*10);
}
