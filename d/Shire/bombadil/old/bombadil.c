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
    set_long("This is Tom Bombadill. He is a merry fellow with a " +
        "cheerful disposition. Unconcerned with the problems of " +
        "the world, he can often be found wandering around, dancing " +
        "and singing. Nonetheless, do not underestimate him, for " +
        "he is strong in his own right.\n");

    add_prop(CONT_I_WEIGHT,67000);   /*  67 Kg */
    add_prop(CONT_I_HEIGHT,169);     /* 169 cm */
    add_prop(LIVE_I_ALWAYSKNOWN,0);  /* Always known by people */

            /* STR DEX CON INT WIS DIS */
    set_stats(({ 190+random(25), 
                 210+random(25), 
                 190+random(25), 
                 200+random(25), 
                 170+random(25), 
                 150+random(25)} ));

    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);

    set_pick_up(75);
    clone_tobacco();

    set_aggressive(0);
    set_attack_chance(0);
    set_alignment(850);

    set_chat_time(5);
    set_act_time(5);
    add_chat("Hey merry dol! Derry dol!");
    add_chat("Lighten up, my friend!");
    add_chat("Don't fear old willow-man, he means you no harm!");
    add_chat("Hey diddle-dillo, I'm Tom Bombadillo!");
    add_act("emote dances around merrily.")
    add_act("emote starts sing a song about the birds in the " +
        "trees and the clouds in the sky.");
    add_act("emote sings about the lovely Goldberry.");


    set_cchat_time(5);
    add_cchat("It is not wise to fight an old man.");
    add_cchat("Did I do anything wrong?");
    add_cchat("Was it something I said?");
    add_stuff();

   /* Global sequence */
    set_act_time(5);
    seq_new("do_things");

   /* Triggers */
/*    trig_new("%s 'giggles' %s", "return_giggle");
}

    return_giggle(who,str)
{
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
*/
}
/*
return_to_normal() 
{
   set_act_time(5);
}
*/

void
add_stuff()
{
/*
    object hat, boots;

    hat = clone_object(BREE_DIR + "arm/bombhat")
    hat->move(this_object());
    boots = clone_object(BREE_DIR + "arm/bombboots");
    boots->move(this_object());
    command("wear armours");
*/
}

int
drink_withy_water()
{
    if (query_hp() * 3 < query_max_hp() || 
	(query_intoxicated() < 10 && query_hp() * 3  < 2 * query_max_hp()) || 
	random(44) == 0)
    {
	if (!present("_withy_water_", TO))
	    return 0;
	command("drink liquid");
	return 1;
    }
    return 0;
}

public int
special_attack(object enemy)
{
    switch (random(3))
    {
	    case 0:
            if (!present("_imladris_elf_paralyze_", enemy) && !random(10)) 
            { 
//	            clone_object(ROBJ_DIR + "stun.c")->move(enemy, 1); 
	            enemy->catch_tell("\nYou are hit on the head by " + short()+".\n"+
	            "You are knocked unconcious!\n\n");
                return 1;
            }  

    	case 1:
//            do_drink_water();
	        return 1;
	    case 2:
//            do_attack_player();
	        return 1;
    }

}
