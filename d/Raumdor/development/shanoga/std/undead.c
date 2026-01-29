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
    add_prop(M_PROP_LIVE_NO_SPECIAL + "plexus",
      "That would do nothing on something that doesn't breathe.\n");
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
    if (this_player()->query_prop(LIVE_I_UNDEAD) ||
        this_player()->query_prop(UNDEAD_I_NO_AUTO))
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
    /*
    * Charges can only be gained if the player is wearing the converted amulet
    *
    * 1 charge is 1 hp
    * Charges are gained according to the following formula:
    * (5 * ((enemy_max_hp / player_CON) * (max_charges - (player_CON / 
    *     (max_charges * player_max_hp)))))
    *
    * max_charges = 200% (of player_max_hp)
    */
    if(present(COMMON_DIR + "arm/artifact_light",
        killer)->query_worn())
    {
        float k_hp = itof(TO->query_max_hp());
        float k_con = itof(killer->query_stat(SS_CON));
        float charg = itof(present(COMMON_DIR + "arm/artifact_light",
            killer)->query_charges());
        
        charges = ftoi(5.0*((k_hp/k_con)*(2.0-((2.0*charg)/(2.0*k_hp)))));
        present(COMMON_DIR + "arm/artifact_light",
            killer)->update_charges(charges);
    }
    
    ::do_die(killer);
}