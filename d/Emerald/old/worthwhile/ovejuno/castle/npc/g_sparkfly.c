/*Spark fly for Castle's Garden
* Coded by Mccram and modified by 
* Marisol (9/12/97)
*/

#pragma save_binary

inherit "/d/Emerald/std/emerald_creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <const.h>      

void
create_emerald_creature()
{
    set_name("spark fly");
    set_adj("electric-blue");
    set_race_name("spark fly");
    add_name("g_sparkfly");
    set_gender(G_NEUTER);
    set_long("This is a big spark fly. Its huge wings are the "+
       "color of bolting lights. Its antenna seems to spark in the "+
       "light.\n");

    set_act_time(10);
    add_act("emote darts around your head with an angry buzz.");
    add_act("emote is busy inside a flower.");

    set_appearance(50);

    set_stats(({ 1, 1, 1, 1, 1, 1}));

    set_alignment(-10);

    set_skill(SS_DEFENCE,5);
    set_skill(SS_UNARM_COMBAT,5);


    set_attack_unarmed(1, 5, 5, W_SLASH, 5, "left leg");
    set_attack_unarmed(2, 5, 5, W_SLASH, 5, "right leg");
    set_attack_unarmed(4, 5, 5, W_SLASH, 5, "jaws");     

    set_hitloc_unarmed(1,  5, 20, "head");
    set_hitloc_unarmed(2,  8, 80, "abdomen");
    set_hitloc_unarmed(4,  9, 10, "front leg");
    set_hitloc_unarmed(8,  9, 10, "middle leg");
    set_hitloc_unarmed(16, 9, 10, "hind leg");
  
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
            pen = 20 *
                (100 - enemy->query_magic_res(MAGIC_I_RES_ELECTRICITY)) / 100;
            enemy->hit_me(pen, MAGIC_DT, this_object(), -1);
            enemy->add_fatigue(-1);

            command("emote throws some electric sparks at you.");          
            enemy->catch_tell("You are burnt at little.\n");   

            if (enemy->query_hp() <= 0)
	    {
                enemy->do_die(this_object());
	    }

            return 1;               

        case 2:
            pen = 60 *
                (100 - enemy->query_magic_res(MAGIC_I_RES_ELECTRICITY)) / 100;
            enemy->hit_me(pen, MAGIC_DT, this_object(), -1);
            enemy->add_fatigue(-1);

            command("emote throws a lighting bolt at you.");
            enemy->catch_tell("You are burnt and it really hurts.\n");

            if (enemy->query_hp() <= 0)
	    {
                 enemy->do_die(this_object());
	    }

            return 1;
    }

    return 0;
}

