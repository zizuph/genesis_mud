/* Dragon by percy*/

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <options.h>


inherit C_FILE

inherit "/std/act/domove"; /* Include this if you want the creature to move */
inherit "/std/act/action"; /* Include this if you want your creature to act */

int heal;


void
create_creature()
{
    int i;

    set_living_name("sleet");
    set_short("white dragon");
    set_race_name("dragon");
    set_long(BS("A huge deadly dragon. It looks powerful and you can feel its evil."
        + " The dragon is white all over and almost seems to relish the cold.\n", 70));
    set_adj("white");

    for (i = 0; i < 6; i++)
        set_base_stat(i, 50 + random(20));

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 50);
    set_knight_prestige(500);

    set_alignment(-400);


    set_attack_unarmed(0, 45, 40, W_IMPALE, 50, "bite");
    set_attack_unarmed(1, 35, 30, W_BLUDGEON, 20, "wing");
    set_attack_unarmed(2, 35, 30, W_SLASH, 30, "claw");

    set_hitloc_unarmed(0, 30, 10, "head");
    set_hitloc_unarmed(1, 40, 60, "body");
    set_hitloc_unarmed(2, 20, 30, "tail");

    add_leftover("/d/Roke/common/carisca/obj/skin","skin",1,"",1,1);

    add_prop(LIVE_I_SEE_DARK, 1000);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_VOLUME, 5679000);
    add_prop(CONT_I_WEIGHT, 5784000);
}

tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_option(OPT_BLOOD) == 0)
            ob[i]->catch_msg(str);
}


int
special_attack(object enemy)
{

    int attacktype, i, penet;
    mixed* hitresult;
    string how;
    object me, *ob;
    me = this_object();

    attacktype = random(10);
    if (attacktype == 1)
    {
        say(BS("You hear a sharp intake of breath and then a chilling"
            + " cone of frost flows from the dragons mouth at you!", 70));

        ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });

        for (i = 0; i < sizeof(ob); i++)
        {
            penet = 250 + random(300);
            penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_COLD) / 100;
            hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);

            how = "not harmed";
            if (hitresult[0] > 0)                  
                how == "barely chilled";
            if (hitresult[0] > 10)
                how = "slightly chilled";
            if (hitresult[0] > 20)
                how = "frozen quite badly";
            if (hitresult[0] > 40)
                how = "frozen very badly";
            if (hitresult[0] > 60)
                how = "utterly devastated";

            ob[i]->catch_msg("You were " + how + " by the dragon breath!\n");
            tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the dragon breath!\n", ob[i]);


            if (ob[i]->query_hp() <= 0)
                ob[i]->do_die(me);
        }
        return 1;
    }

    return 0;
}




