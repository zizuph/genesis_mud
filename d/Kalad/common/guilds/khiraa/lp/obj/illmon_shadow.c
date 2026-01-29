inherit "/std/shadow";
#include "/d/Kalad/defs.h"

object *monster_cobj = ({});
object *kmonster_cobj = ({}); // known as an illusion
int v_hit;
int hp_time;
int last_con;
int last_intox;

int
illmon_check(object ob)
{
    if(member_array(ob->query_combat_object(),monster_cobj) != -1)
        return 1;
    if(member_array(ob->query_combat_object(),kmonster_cobj) != -1)
        return 2;
    return 0;
}

void
add_to_cobj(object me, int i)
{
    if(i == 0)
        monster_cobj += ({ me->query_combat_object() });
    else
        kmonster_cobj += ({ me->query_combat_object() });
}

void
set_cobj(object me, int i)
{
    v_hit = shadow_who->query_hp();
    hp_time = time();
    if(i == 0)
        monster_cobj +=  ({ me->query_combat_object() });
    else
        kmonster_cobj += ({ me->query_combat_object() });

    last_con = shadow_who->query_stat(SS_CON);
    last_intox = shadow_who->query_intoxicated();
}

void
calculate_vhp()
{
    int n, con, intox;
    int tmpcon, tmpintox;
 
    n = (time() - hp_time) / F_INTERVAL_BETWEEN_HP_HEALING;
    if (n > 0)
    {
        con = shadow_who->query_stat(SS_CON);
        intox = shadow_who->query_intoxicated();
        tmpcon = (con + last_con) / 2;
        tmpintox = (intox + last_intox) / 2;
        v_hit += n * F_HEAL_FORMULA(tmpcon, tmpintox);
        if(v_hit > shadow_who->query_max_hp())
            v_hit = shadow_who->query_max_hp();
        last_con = con;
        last_intox = intox;
        hp_time += n * F_INTERVAL_BETWEEN_HP_HEALING;
    }
}

void
do_panic()
{
    if(!shadow_who->query_prop(NPC_I_NO_RUN_AWAY))
        shadow_who->run_away();
    shadow_who->add_panic(50);
}

void
heal_vhp(int i)
{
    int res = MAX(shadow_who->query_magic_res(MAGIC_I_RES_DEATH),
              shadow_who->query_magic_res(MAGIC_I_RES_MAGIC));

    if(member_array(previous_object(-2), monster_cobj) != -1)
    {
        v_hit += i;
        v_hit += (res * v_hit ) / 100;
        if(v_hit <= 0)
            do_panic();
    }
    else
    {
        if(member_array(previous_object(-2), kmonster_cobj) != -1)
            return;
        v_hit += i;
    }
}

int
query_vhp()
{
    calculate_vhp();
    return v_hit;
}

int
query_hp()
{
    calculate_vhp();
    if(!sizeof(monster_cobj))
        return shadow_who->query_hp();
    if(file_name(previous_object()) == "/cmd/live/state")
    {
        return v_hit;
    }
    return shadow_who->query_hp();
}

int
query_illmon_shadow()
{
    return 1;
}

void
remove_ill_shadow()
{
    remove_shadow();
}
