/*
 *  Tom Bombadil, the happy fellow
 *  Cloned by ~Shire/common/bree/tom
 */

inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/monster/tobacco.h"

create_monster()
{
   if (!IS_CLONE)
      return;

   set_name(({"tom","bombadil"}));
   set_title("Bombadil");
   set_race_name("man"); 
   set_adj(({"tall","happy"}));
   set_long("Tom is a very old and wise man. He is a happy old fellow,\n"
          + "jumping around and singing all kinds of happy songs.\n");

   add_prop(CONT_I_WEIGHT,67000);   /*  67 Kg */
   add_prop(CONT_I_HEIGHT,169);     /* 169 cm */
   add_prop(LIVE_I_ALWAYSKNOWN,0);  /* Always known by people */

            /* STR DEX CON INT WIS DIS */
   set_stats(({ 170, 150,150, 165, 177, 190}));

   set_skill(SS_UNARM_COMBAT, 100);
   set_skill(SS_DEFENCE, 100);
   set_pick_up(75);
    clone_tobacco();

   set_aggressive(0);
   set_attack_chance(0);
   set_alignment(850);

   set_chat_time(5);
   add_chat("Hey merry dol! Derry dol!");
   add_chat("Lighten up, my friend!");
   add_chat("Don't fear old willow-man, he means you no harm.");
   add_chat("Hey diddle-dillo, I'm Tom Bombadillo!");
   add_chat("Tom Bombadil and de Riverdaughter!");

   set_cchat_time(5);
   add_cchat("It is not wise to fight an old man.");
   add_cchat("Did I do anything wrong?");
   add_cchat("Was it something I said?");
   add_stuff();

   /* Global sequence */
   set_act_time(5);
   seq_new("do_things");

   /* Triggers */
   trig_new("%s 'giggles' %s", "return_giggle");
}

return_giggle(who,str) {
   if (who)
   {
      who = lower_case(who);
      set_act_time(1);
      seq_clear("do_things");
      seq_addfirst("do_things",
                     ({"smile " + who,
                       "@@return_to_normal"}));
      return 1;
   }
}

return_to_normal() {
   set_act_time(5);
}

void
add_stuff()
{
   object hat, boots;

   hat = clone_object(BREE_DIR + "arm/bombhat");
     hat->move(this_object());
     boots = clone_object(BREE_DIR + "arm/bombboots");
     boots->move(this_object());
     command("wear armours");

}
