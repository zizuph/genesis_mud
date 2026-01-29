




inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>

#define ARMOURS "/d/Shire/common/armour/iarmour/"

create_monster() {
    set_name(({"rick","red-eyed elf","bouncy elf","red-eye bouncy elf"}));
    set_short("red-eyed bouncy elf");
   set_race_name("elf");
   set_long(
      "He is dressed in tattered clothes. He looks like he's been\n"+
      "on the run for a while.\n");
   add_prop(CONT_I_WEIGHT,300*1000);
   add_prop(CONT_I_HEIGHT,400);
   set_stats(({90,90,90,90,90,90}));
   set_hp(10000);

   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_WEP_SWORD,    50);
   set_skill(SS_DEFENCE,      55);
   set_skill(SS_PARRY,        50);
   set_skill(SS_WEP_JAVELIN, 100);
   set_pick_up(43);
   set_aggressive(1);
   set_attack_chance(87);

   set_alignment(-50);
   set_act_time(6);
   add_act("grin");
   add_act("growl");
   add_act(({"puke all", "laugh"}));
   add_act("emote sticks a wet finger in your right ear.");

   set_cact_time(7);
   add_cact("say Party!!!");
   add_cact("say Come on bastard!!?");
   add_cact("emote bitch slaps you!");
   add_cact("emote cuts your gut!");
   add_cact("emote hits you very hard, you feel very badly hurt.");
   add_cact("echo HAHAHAHAHAHHAHAHAHAHAAHAHAAHAHHAHHAHAHAHAH!!!");
   call_out("suit_up",1);
}

suit_up()
{
    object boots1, robe1, spear;

   boots1    = clone_object(ARMOURS+"boots1");
   robe1     = clone_object(ARMOURS+"robe1");
   spear     = clone_object("/d/Shire/common/weapon/diamond_spear.c");

   if ( objectp(boots1) )
      {
      boots1->move(this_object());
   }
   if ( objectp(robe1) )
      {
      robe1->move(this_object());
   }
    if ( objectp(spear) )
      {
      spear->move(this_object());
      }
    command("wear all");
    command("wield all");
}


