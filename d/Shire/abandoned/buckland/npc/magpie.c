/*
 * A magpie for newbies
 * original code from the common sea gull
 * Can be cloned by ~Shire/common/buckland/buck*.*
 */

inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/combat/unarmed";

#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

object target;
string name;

create_creature()
{


   if (!IS_CLONE)
      return;
   seteuid(getuid(this_object()));
   set_name("bird");
   add_name("magpie");
   set_pname("s");
   set_living_name("magpie");
   set_race_name("bird");
   set_gender(G_NEUTER);

   set_long("This is a Magpie. A beautiful blue-black bird.\n");

   add_prop(LIVE_I_NEVERKNOWN, 1);

   set_stats(({ 5, 10, 2, 15, 15, 25 }));

   set_attack_unarmed(0,  8, 8,W_IMPALE, 100, "beak");
   set_hitloc_unarmed(0, ({ 8, 8, 8, 8 }), 100, "body");

   set_act_time(3);
   add_act("@@drop");

   add_prop(CONT_I_WEIGHT, 50);   /* 0.05 Kg  */
   add_prop(CONT_I_VOLUME, 100);   /* 0.10 Ltr */

   trig_new("%s 'leaves' %s","follow");
   money_me();
}

drop() {
  int ran;
  ran = random(3);

  switch(ran) {
  case 0:
    tell_room(environment(), "The bird leaves a remainder of its presence on"
	      + " your shoulder.\n");
    break;
  case 1:
    tell_room(environment(), "The bird cackles.\n");
    break;
  case 2:
    tell_room(environment(), "The bird flaps it's wings.\n");
    break;
  }
}

money_me(){
        object money;
        if(random(2) < 2){
        money = clone_object("/std/coins");
	money->set_coin_type("gold");
	money->set_heap_size(1);
	money->move(this_object());
        }
}