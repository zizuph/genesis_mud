#include "defs.h"
inherit STD_DIR + "monster";
inherit LIB_DIR + "despawn";

void
create_monster()
{
    ::create_monster();
    add_name("undead");
    set_gender(G_NEUTER);
    set_alignment(-700);
    set_aggressive(1, 100);

    add_prop(LIVE_I_UNDEAD, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(LIVE_I_NO_GENDER_DESC, 1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 1);

    // Prevent specials that don't make sense
    //add_prop(M_PROP_LIVE_NO_SPECIAL + "plexus",
      //"That would do nothing on something that doesn't breathe.\n");
    add_prop(RANGER_I_NOT_BLIND, 1);

    if (DAY)
        set_stats(STAT_ARRAY(90));
    else
        set_stats(STAT_ARRAY(120));
}

void
init_living()
{
    ::init_living();
    reset_despawn();
}

int
query_raumdor_undead()
{
    return 1;
}

public void
init_attack()
{
    if (!TP->check_call(monster_aggressive) || !UNDEAD_ENEMY(TP))
        return;
    if (!monster_attack_chance || (random(100) < monster_attack_chance))
    {
        float delay = itof(1 + random(2)) + rnd();
        set_alarm(delay, 0.0, &aggressive_attack(this_player()));
    }
}

public void
do_die(object killer)
{
    object lich;
    //if (E(TO)->query_shadows_forest())
    if (E(TO)->query_test_room())
    {
        killer->inc_prop(LIVE_I_KILLED_FOREST_UNDEAD);
        if (!killer->query_prop(LIVE_I_SUMMONED_FOREST_LICH) &&
          random(query_prop(LIVE_I_KILLED_FOREST_UNDEAD)) > SUMMON_LICH_CHANCE)
        {
            clone_object(COMMON_NPC_DIR + "lich");
            lich->move_living("xxx", E(TO));
            lich->follow(killer);
            lich->command("kill " + OB_NAME(killer));
        }
    }
    /* Charge amulet whenever bearer kills a Raumdor undead */
    object ob = killer->query_worn(TS_NECK);
    if (ob && MASTER_OB(ob) == COMMON_ARM_DIR + "life_amulet")
        ob->do_charge(TO);

    ::do_die(killer);
}
