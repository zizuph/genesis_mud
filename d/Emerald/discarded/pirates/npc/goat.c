inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/chat";
inherit "/std/act/action";
inherit "/std/act/action";
inherit "/cmd/std/command_driver";
#include "/sys/wa_types.h"

#include "defs.h"

#define A_TOOTH  0
#define A_RLEG 1
#define A_LLEG 2

#define H_HEAD  0
#define H_BODY  1

#define PIR_I_KILLED_GOAT "_pir_i_killed_goat"

void do_die(object killer);

void
create_creature()
{
   if (!IS_CLONE)
      return;
   
   set_name("goat");
   set_adj("scruffy");
   set_race_name("goat");
   set_short("scruffy goat");
   set_long("This is a scruffy white goat. His fur is a tangled mess.\n");
   
   set_base_stat(SS_STR, 32);
   set_base_stat(SS_DEX, 29);
   set_base_stat(SS_CON, 28);
   set_base_stat(SS_INT, 21);
   set_base_stat(SS_WIS, 20);
   set_base_stat(SS_DIS, 28);
   
   heal_hp(1649);
   
   set_skill(SS_DEFENCE, 25);
   set_skill(SS_UNARM_COMBAT, 23);
   set_skill(SS_BLIND_COMBAT, 24);
   set_skill(SS_ELEMENT_LIFE, 40);
   set_skill(SS_AWARENESS, 40);
   
   add_prop(OBJ_I_WEIGHT, 76000);
   add_prop(CONT_I_MAX_WEIGHT, 200000);
   add_prop(OBJ_I_VOLUME, 89000);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   add_prop(OBJ_M_NO_ATTACK,1);
   
   set_attack_unarmed(A_TOOTH, 25, 26, W_IMPALE, 20, "teeth");
   set_attack_unarmed(A_RLEG,21, 22, W_SLASH,  35, "right foreleg");
   set_attack_unarmed(A_LLEG,21, 22, W_SLASH,  35, "left foreleg");
   
   set_hitloc_unarmed(H_HEAD, ({ 14, 15, 18, 14 }), 25, "head");
   set_hitloc_unarmed(H_BODY, ({ 16, 21, 20, 19 }), 75, "body");
   
}


void
init_living()
{
   ::init_living();
   add_action("do_sacrifice","sacrifice");
   add_action("lead","lead");
}


lead(string arg)
{
   notify_fail("Lead what?\n");
   
   if(!(TP->query_prop("_cyclops_gift")))
      {
      write("You would be making a mistake to steal one of these goats!\n");
      return 1;
   }
   if(!arg)
      return 0;
   if(arg == "goat")
      write("Lead goat where?\n");
   if(arg == "goat north" || arg == "goat n")
      {
      write("You force the goat to go north.\n");
      allbb(" forces the goat to go north.");
      TO->command("north");
      TP->command("north");
   }
   if(arg == "goat east" || arg == "goat e")
      {
      write("You force the goat to go east.\n");
      allbb(" forces the goat to go east.");
      TO->command("east");
      TP->command("east");
   }
   if(arg == "goat south" || arg == "goat s")
      {
      write("You force the goat to go south.\n");
      allbb(" forces the goat to go south.");
      TO->command("south");
      TP->command("south");
   }
   if(arg == "goat west" || arg == "goat w")
      {
      write("You force the goat to go west.\n");
      allbb(" forces the goat to go west.");
      TO->command("west");
      TP->command("west");
   }
   if(arg == "goat up" || arg == "goat u")
      {
      write("You force the goat to go up.\n");
      allbb(" forces the goat to go up.");
      TO->command("up");
      TP->command("up");
   }
   if(arg == "goat down" || arg == "goat d")
      {
      write("You force the goat to go down.\n");
      allbb(" forces the goat to go down.");
      TO->command("down");
      TP->command("down");
   }
   return 1;
}


int
do_sacrifice(string arg)
   {
   notify_fail("Sacrifice what?\n");
   if(!TP->query_prop("_blew_the_horn"))
      {
      write("Do not sacrifice the animal in vain.\n");
      return 1;
   }
   if(!arg)
      return 0;
   if(arg != "goat")
      return 0;
   if(file_name(ENV(TO)) != PIRATES_DIR+"quest/is5")
      write("Perhaps you should find an altar.\n");
   else
      {
      TP->remove_prop("_blew_the_horn");
      TP->remove_prop("_cyclops_gift");
      write("You tie the goat to the altar.\n");
      allbb(" ties the goat to the altar.");
      write("You slide your hand between its ribs and through its flesh.\n");
      allbb(" slides "+TP->query_possessive()+" hand into the chest of the goat.");
      write("You rip the still-beating heart from the chest of the animal.\n");
      allbb(" rips the still-beating heart from the chest of the goat.");
      heal_hp(-5000);
      TO->do_die(this_player());
   }
   return 1;
}

void
do_die(object killer)
{
   if(query_hp() > 0) {return; }
   
   if(!killer) { killer = previous_object(); }
   
   killer->add_prop(PIR_I_KILLED_GOAT, 1);
   clone_object(PIRATES_DIR+"npc/clone_neptune.c")->move(environment(killer), 1);
   ::do_die(killer);
   
   return;
}
