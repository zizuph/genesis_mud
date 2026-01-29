/*
 *  Grey Barrow wight in the barrow downs
 *  Cloned by ~Shire/common/downs/stone3*.c
 */

inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/common/lib/evilkill.h"

create_monster()
{
   if (!IS_CLONE)
      return;

   set_name(({"grey barrow wight","wight","barrow wight","grey wight"}));
   set_title("grey");
   set_race_name("wight"); 
   set_adj(({"grey","barrow"}));
   set_pshort("grey barrow wights");
   set_long("This is a grey barrow wight, creepy, but not too dangerous."
          + "When alone, that is.\n");

   add_prop(CONT_I_WEIGHT,67000);   /*  10 Kg */
   add_prop(CONT_I_HEIGHT,169);     /* 150 cm */
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(NPC_I_NO_LOOKS, 1);     /*Does NOT look plesant*/
   add_prop(LIVE_I_UNDEAD, 25);      /*Is an undead*/
   add_prop(LIVE_I_NO_CORPSE, 1);   /*Leaves no corpse*/
   add_prop("_ranger_i_not_blind",1);

            /* STR DEX CON INT WIS DIS */
   set_stats(({ 50, 45, 55, 45, 27, 65}));
   set_alignment(-120);
   set_skill(SS_WEP_SWORD,60);
   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_DEFENCE, 50);
   set_skill(SS_PARRY, 60);

   set_aggressive(70);
   set_attack_chance(75);

   set_act_time(15);
   add_act("emote hisses at you.");
   add_act("emote eyes turn a deathly cold color.");
   add_act("emote looks you up and down as a potential enemy.");
   add_act("emote beckons you closer.");
   add_act("emote hisses: Come to me and I can make you wealthy...");
   add_act("emote hisses: Come, come to me...");
   
   set_cact_time(15);
   add_cact("emote hisses something evil at you.");
   add_cact("emote hisses: I shall feast on your corpse.");
   add_cact("emote turns to you with a deathly look.");
   add_cact("emote hisses: Only foolish mortals think they can win.");

   MAKE_MONEY;
   /* Global sequence */
   set_act_time(5);
   seq_new("do_things");
   set_alarm(0.5,0.0,"arm");
}

arm()
{
	object sword, plate;

	sword	= clone_object(DOWNS_DIR +"wep/m_sword");
	sword->move(this_object());

	plate = clone_object(DOWNS_DIR +"arm/m_plate");
	plate->move(this_object());	
	
	command ("wear all");
	command ("wield all");

}

return_to_normal()
{
   set_act_time(5);
}

