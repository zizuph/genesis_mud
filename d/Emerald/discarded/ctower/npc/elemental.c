inherit "/std/monster";

#include <stdproperties.h>
#include <const.h>
#include <ss_types.h>
#include <macros.h>

string opposing_element;
int strong_elemental;
int *strong_stats, *weak_stats;

void strengthen_elemental();

void
create_elemental()
{
}

nomask void
create_monster()
{
    set_name("elemental");
    set_race_name("elemental");

    set_gender(G_NEUTER);

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(LIVE_I_SEE_INVIS, 99);
    add_prop(LIVE_I_SEE_DARK, 99);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_POISON, 100);
    add_prop("_live_m_no_blood", 1);
    add_prop(LIVE_I_NO_CORPSE, 1);

    for_each(({ SS_UNARM_COMBAT, SS_DEFENSE, SS_AWARENESS,
        SS_SPELLCRAFT }), &set_skill(, 100));

    create_elemental();

    strengthen_elemental();
}

void
set_element(string elem)
{
    add_adj(elem);
    add_name(elem + "_elemental");
}

void
set_opposing_element(string elem)
{
    opposing_element = elem;
}

void
engulf_miss(object enemy)
{
    enemy->catch_tell(enemy->query_The_name(this_object()) +
        " lunges at you, but you deftly avoid its grasp.\n");
    tell_watcher_miss(QCTNAME(this_object()) + " lunges at " +
        QTNAME(enemy) + ", but " + enemy->query_pronoun() +
        "deftly avoids its grasp.\n", enemy);
}

void
engulf_hit(object enemy)
{
}

int
special_attack(object enemy)
{
    if (!strong_elemental || (random(8) > 0))
    {
        return 0;
    }

    if (query_combat_object()->cb_tohit(-1, 85, enemy) <= 0)
    {
        engulf_miss(enemy);
        return 1;
    }

    engulf_hit(enemy);
}

void
weaken_elemental()
{
    int hps;

    if (strong_elemental)
    {
    	set_stats(weak_stats);
    
    	if ((hps = query_hp() - query_max_hp()) > 0)
    	{
    	    heal_hp(-hps);
    	}
    
    	set_all_attack_unarmed(35, 35);
    	set_all_hitloc_unarmed(40);
    
    	strong_elemental = 0;
    
    }
    else
    {
        heal_hp(-100 - random(100));
    }

    if (environment())
    {
	tell_room(environment(), ({
	    "The " + short() + " looks visibly weakened!\n",
	    "The " + short() + " looks visibly weakened!\n",
	    "" }), this_object());
    }

    command("kill " + OB_NAME(this_player()));
}

void
strengthen_elemental()
{
    set_stats(strong_stats);

    refresh_living();

    set_all_attack_unarmed(70, 70);
    set_all_hitloc_unarmed(100);
    
    strong_elemental = 1;

    if (environment())
    {
        tell_room(environment(), ({
            "The " + short() + " seems to be strengthened!\n",
            "The " + short() + " seems to be strengthened!\n",
            "", this_object() }));
    }
}

void
set_weak_stats(int *stats)
{
    weak_stats = stats;
}

void
set_strong_stats(int *stats)
{
    strong_stats = stats;
}

varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id,
    int target_hitloc = -1)
{
    object weapon;
    mixed *magic;

    if (!strong_elemental)
    {
        return ::hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
    }

    if (attack_id == -1)
    {
        wcpen = 0;
    }
    else if (weapon = attacker->query_weapon(attack_id))
    {
        if (weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON))
	{
            if (strlen(opposing_element) &&
                pointerp(magic = weapon->query_prop(MAGIC_AM_MAGIC)))
	    {
                if (wildmatch("*" + opposing_element + "*", magic[0]))
		{
                    wcpen *= 5;
		}
	    }
	}
        else
	{
            wcpen = 0;
	}
    }
    else
    {
        wcpen /= 2;
    }

    return ::hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
}
