/* Queen ant by Halgor 3/93 */
/* Melt armour routine from Tricky's spelltome */
/* Special attack from /doc/examples/mobiles/tiger */
 
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
 
#include <wa_types.h>
 
 
#include "/d/Emerald/defs.h"
#include <filter_funs.h>
#include <formulas.h>
 
 
#define A_BITE 0
 
#define H_HEAD 0
#define H_BODY 1
 
 
 
 
create_creature()
{
    set_race_name("ant");
    set_short("queen ant");
    set_adj("queen");
    set_long( "This is the largest ant you have ever seen in "+
        "your life. It moves towards you aggresively as you enter the room "+
        "- it might be a good time to leave.\n" );
 
    set_stats(({65,60,70,20,20,65}));
    set_hp(10000);
 
    set_skill(SS_DEFENCE,50);
    set_skill(SS_BLIND_COMBAT,50);
 
    set_attack_unarmed(A_BITE,30,35,W_BLUDGEON,100,"mandibles");
 
    set_hitloc_unarmed(H_HEAD,25,20,"head");
    set_hitloc_unarmed(H_BODY,35,80,"body");
 
    set_gender(G_FEMALE);
    add_prop(LIVE_I_NEVERKNOWN,1);
 
}
 
 
 
 
/* Filter the people without see_blood , so they dont see the special hits */
static void
tell_watcher(string str, object enemy)
{
    object me, *ob;
    int i;
 
    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}
 
 
 
 
int
filter_worn_armours(object obj)
{
    if ((function_exists("create_object",obj) == "/std/armour")
            && obj->query_worn())
        return 1;
    return 0;
}
 
 
 
 
/* select random armour for damage */
object *
select_armour(object enemy)
{
    object *arm_arr;
 
    arm_arr = filter(all_inventory(enemy),"filter_worn_armours",this_object());
 
    if (!sizeof(arm_arr))
        return 0;    /* if no armour worn */
 
    return arm_arr;
}
 
 
 
 
void
damage_armour(object enemy)
{
    int power, old_ac, new_ac, i;
    string tmp;
    object *arm_affected;
 
    arm_affected = select_armour(enemy);
    if (arm_affected == 0)
        return;
 
    for (i=0 ; i<sizeof(arm_affected) ; i++ )
    {
        /* check for resistance */
        if (arm_affected[i]->query_prop(MAGIC_I_RES_ACID)
            || arm_affected[i]->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
            return;
 
        enemy->catch_msg( "The acid starts eating into your "+
            arm_affected[i]->short() + ".\n" );
 
        tell_watcher(QTNAME(enemy)+"'s "+arm_affected[i]->short()+" is slowly"+
            " dissolved by the acid.\n",enemy);
 
        power = random(5) + 1; /* ac lost */
        old_ac = arm_affected[i]->query_ac();
 
        new_ac = old_ac - power;
        if (new_ac < 0)
            new_ac = 0;
 
        arm_affected[i]->set_ac(new_ac);
        arm_affected[i]->add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(new_ac));
 
        if (sscanf(arm_affected[i]->short(), "%s (acid damaged)",tmp) == 0)
            arm_affected[i]->set_short(arm_affected[i]->short() +
                " (acid damaged)");
    }
}
 
 
 
 
/* display the special attack results */
void
disp_att_results(string how, object me, object enemy)
{
    me->catch_msg("You spray acid at your opponent" + how + ".\n");
    enemy->catch_msg(QCTNAME(me)+" sprays acid at you"+how+".\n");
    tell_watcher(QCTNAME(me)+" sprays acid at "+QTNAME(enemy)+how+".\n",enemy);
}
 
 
 
 
/* Define the special attack here */
int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
 
    me = this_object();
    if (random(10))
        return 0;
 
    hitresult = enemy->hit_me(45, W_NO_DT, me, -1);
 
    if (hitresult[0] <= 0)
    {
        how = " without effect";
        disp_att_results(how, me, enemy);
        return 1;
    }
 
    how = "";
        disp_att_results(how, me, enemy);
    if (random(100) >= 25);
        damage_armour(enemy);
 
    if (enemy->query_hp() <= 0)
        enemy->do_die(me);
 
    return 1;
}
