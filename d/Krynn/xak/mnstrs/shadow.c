/* Undead shadow by percy*/

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

int heal;


void
create_creature()
{
    int i;

    set_short("undead shadow");
    set_race_name("shadow");
    set_long(BS("This creature seems to be made of the stuff of"
        + " shadows itself! It is hard to make it out even in"
        + " the light. The creature is notorious for draining"
        + " the strength of a victim temporarily.\n", 70));
    set_adj("undead");

    for (i = 0; i < 6; i++)
        set_base_stat(i, 50 + random(20));

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_UNARM_COMBAT, 40);
    set_aggressive(1);
    set_knight_prestige(200);

    set_alignment(-400);


    set_attack_unarmed(0, 23, 23, W_SLASH, 100, "claw");

    set_hitloc_unarmed(0, 33, 20, "head");
    set_hitloc_unarmed(1, 33, 80, "body");

    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 30);
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

    int attacktype, j, penet, poisoned;
    mixed* hitresult;
    string how;
    object me, *ob;

    me = this_object();

    ob =  FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    poisoned = 0;

    penet = 50 + random(100);
    penet -= penet * enemy->query_magic_res(MAGIC_I_RES_POISON) / 100;
    hitresult = enemy->hit_me(penet, W_SLASH, me, -1);

    how = "tickled";
    if (hitresult[0] > 0) 
    {
        poisoned = 1;                 
        how == "scratched and drained of strength";
    }
    if (hitresult[0] > 10)
        how = "slightly hurt and drained of strength";
    if (hitresult[0] > 20)
        how = "hurt and drained of strength";
    if (hitresult[0] > 30)
        how = "hurt quite badly and drained of strength";
    if (hitresult[0] > 40)
        how = "hurt very badly and drained of strength";
    if (hitresult[0] > 60)
        how = "utterly devastated and drained of strength";

    enemy->catch_msg("You were " + how + " by the shadows claws!\n");
    tell_watcher(QCTNAME(enemy) + " is " + how + " by the shadows claws!\n", enemy);

    if (poisoned)
    {
        enemy->add_tmp_stat(SS_STR, -3, 15);
    }

    if (enemy->query_hp() <= 0)
        enemy->do_die(me);

    return 1;
}




