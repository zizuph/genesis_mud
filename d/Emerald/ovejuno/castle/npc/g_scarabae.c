/*Scarabae Bug for Castle's Garden
* Coded by Mccram and modified by 
* Marisol (9/12/97)
*/

#pragma save_binary

inherit "/d/Emerald/std/emerald_creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>  
#include <const.h>

void
create_earthsea_creature()
{
    int i;

    set_name("scarabae");
    set_adj("huge");
    set_race_name("scarabae");
    add_name("g_scarabae");
    set_gender(G_NEUTER);
    set_long("This is one of the hugest bugs that you have "+
         "ever seen in your life.\n");

    set_act_time(10);
    add_act("emote scratchs the ground looking for food"); 
    add_act(({"emote finds a tasty morsel.", "emote chews noisily."}));
    
    set_appearance(50);

    set_stats(({5,5,5,8,8,9}));

    set_alignment(0);

    set_skill(SS_DEFENCE,10);
    set_skill(SS_UNARM_COMBAT,5);


    set_attack_unarmed(1, 5, 5, W_SLASH, 5, "left leg");
    set_attack_unarmed(2, 5, 5, W_SLASH, 5, "right leg");
    set_attack_unarmed(4, 5, 5, W_SLASH, 5, "jaws");     

    set_hitloc_unarmed(1,  5, 20,"head");
    set_hitloc_unarmed(2,  8, 80,"thorax");
    set_hitloc_unarmed(4,  9, 10,"front leg");
    set_hitloc_unarmed(8,  9, 10,"middle leg");
    set_hitloc_unarmed(16, 9, 10,"hind leg");
  
    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
}                                                             

int
special_attack(object enemy)

{
    int pen;

    switch (random(15))
    {
        case 0:
            pen = 20 * (100 - enemy->query_magic_res(MAGIC_I_RES_ACID)) / 100;
            enemy->hit_me(pen, MAGIC_DT, this_object(), -1);
            enemy->add_fatigue(-1);

            command("emote spits out a sprinkle of acid.");          
            enemy->catch_tell("You are burnt at little.\n");   

            if (enemy->query_hp() <= 0)
	    {
                enemy->do_die(this_object());
	    }

            return 1;

        case 2:
            pen = 60 * (100 - enemy->query_magic_res(MAGIC_I_RES_ACID)) / 100;
            enemy->hit_me(pen, MAGIC_DT, this_object(), -1);
            enemy->add_fatigue(-1);

            command("emote spits out a scorching spray of acid.");
            enemy->catch_tell("You are burnt and it really hurts.\n");

            if (enemy->query_hp() <= 0)
	    {
                 enemy->do_die(this_object());
	    }

            return 1;
    }

    return 0;
}

