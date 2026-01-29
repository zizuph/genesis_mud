/*
 *  Barrow wight in the barrow downs
 *  Cloned by ~Shire/common/downs/stone2.c
 */

inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"

create_monster()
{
   if (!IS_CLONE)
      return;

   set_name(({"wight","barrow wight"}));
   set_title("Black Wight");
   set_race_name("human"); 
   set_long("This is a black barrow wight, the worst of them all,\n"
          + "What are you doing here....\n");

   add_prop(CONT_I_WEIGHT,67000);   /*  10 Kg */
   add_prop(CONT_I_HEIGHT,169);     /* 169 cm */
   add_prop(LIVE_I_ALWAYSKNOWN,1);  /* Always known by people */

            /* STR DEX CON INT WIS DIS */
   set_stats(({ 70, 50, 50, 65, 77, 90}));

   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_DEFENCE, 50);
   set_skill(SS_PARRY, 50);
   set_pick_up(99);
    

   set_aggressive(50);
   set_attack_chance(50);

   set_hp(query_max_hp()); /* Heal fully */

   set_chat_time(5);
   add_chat("Die, Mortal!");
   add_chat("Don't fear, just die.");
   add_chat("I smell flesh.");
   add_chat("Tom Bombadil is far away.");

   set_cchat_time(5);
   add_cchat("HEHEHEHEH.");
   add_cchat("AhhhUHHHHHH");
   add_cchat("I shall feast on your corpse.");

   /* Global sequence */
   set_act_time(5);
   seq_new("do_things");
   call_out("arm", 2);
}

arm() {
	object sword, money;

	sword	= clone_object(STAND_WEAPON + "w_sword");
	/*plate	= clone_object("~Shire/common/armour/w_plate");*/
	money	= clone_object("/std/coins");

	sword->move(this_object());
	
		money->set_coin_type("silver");
		money->set_heap_size(45);
		money->move(this_object());
	

	command ("wield all");
	
	command ("grin");

}


return_to_normal() {
   set_act_time(5);
}
