/* Undead wraith by percy*/

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <options.h>


inherit C_FILE
inherit "/std/act/attack.c";
inherit "/std/act/domove"; /* Include this if you want the creature to move */
inherit "/std/act/action"; /* Include this if you want your creature to act */


void
create_creature()
{
    int i;

    set_short("undead wraith");
    set_race_name("wraith");
    set_long("This is a horrific undead creature that feed of peoples"
      + " souls and past experiences to survive.\n");
    set_adj("undead");

    for (i = 0; i < 6; i++)
        set_base_stat(i, 50 + random(20));

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_UNARM_COMBAT, 40);

    set_knight_prestige(400);

    set_alignment(-600);


    set_attack_unarmed(0, 23, 23, W_SLASH, 100, "claw");

    set_hitloc_unarmed(0, 33, 20, "head");
    set_hitloc_unarmed(1, 33, 80, "body");
    set_aggressive(1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 40);
    add_prop(LIVE_I_SEE_DARK, 1000);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_VOLUME, 567900);
    add_prop(CONT_I_WEIGHT, 578400);
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

    int attacktype, j, penet, poisoned, xp;
    mixed* hitresult;
    string how;
    object me, *ob;

    me = this_object();
    poisoned = 0;
    ob =  FILTER_LIVE(all_inventory(environment(me))) - ({ me });


    penet = 50 + random(100);
    hitresult = enemy->hit_me(penet, W_SLASH, me, -1);

    how = "tickled";
    if (hitresult[0] > 0)                 
        how = "badly tickled";
    if (hitresult[0] > 10)
    {
        poisoned = 1;
        how = "slightly hurt and drained of experience";
    }
    if (hitresult[0] > 20)
        how = "hurt and drained of experience";
    if (hitresult[0] > 30)
        how = "hurt quite badly and drained of experience";
    if (hitresult[0] > 40)
        how = "hurt very badly and drained of experience";
    if (hitresult[0] > 60)
        how = "utterly devastated and drained of experience";

    enemy->catch_msg("You were " + how + " by the wraiths claws!\n");
    tell_watcher(QCTNAME(enemy) + " is " + how + " by the wraiths claws!\n", enemy);

    if (poisoned)
    {
        enemy->add_temp_stat(random(6), -random(3), random(50));
    }

    if (enemy->query_hp() <= 0)
        enemy->do_die(me);

    return 1;
}




