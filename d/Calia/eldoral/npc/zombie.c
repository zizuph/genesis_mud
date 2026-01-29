/*
 * zombie.c
 *
 * This is a rather intriguing npc that I'll probably be tinkering
 * with several times over the next few months. Basically, this
 * file is a 'template' of sorts. When a player dies in the caverns
 * on eldoral, their corpse is reanimated as a zombie after a few
 * seconds. A copy of this object is cloned, and the player's stats,
 * skills, adjectives, name, etc. are all used as values to set in
 * this object. After it is all set, the object is saved, using
 * the player's name as the name for a save file. The result being
 * a saved copy of a zombie identical to the player.
 * This saved copy arrives in the room the corpse is in, the corpse
 * is removed, and all objects on the corpse are moved to the zombie.
 * After this, the zombie is a permanent, wandering, auto-attacking
 * addition to the caverns due to the save file. It even saves beyond
 * reboot, autoloading into the area the first time any of the cavern
 * rooms are loaded.
 * Once killed, however, the zombie save file is removed, and the
 * zombie is gone for good.
 *
 * Khail - Feb 14/97
 */
#pragma strict_type

#include "defs.h"
#include <ss_types.h>
#define ZOMBIE_SAVE(x)  SPECIAL + "zombies/" + x

inherit "/std/monster";

string *my_names;
string *my_adjs;
mapping zombie_remembered;

/*
 * Function name: stats_to_acc_exp (MASK)
 * Description  : Simply a callback to the previous 
 *                stats_to_acc_exp. It is masked and redefined
 *                as public so we can update the zombie's stats
 *                based on it's exp.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
stats_to_acc_exp()
{
    ::stats_to_acc_exp();
}

/*
 * Function name: acc_exp_to_stats
 * Description  : Much the same as the above described stats_to_acc_exp.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
acc_exp_to_stats()
{
    ::acc_exp_to_stats();
}

/*
 * Function name: set_zombie_remembered
 * Description  : Sets the zombies 'artificial' memory of players
 *                it knows.
 * Arguments    : map - A mapping identical to the remembered mapping
 *                      of players.
 * Returns      : n/a
 */
public void
set_zombie_remembered(mapping map)
{
    zombie_remembered = map;
}

/*
 * Function name: query_zombie_remembered
 * Description  : Returns the zombies artificial remembered list.
 * Arguments    : n/a
 * Returns      : A mapping identical to that used by players for
 *                remembering names.
 */
public mapping
query_zombie_remembered()
{
    return zombie_remembered + ([]);
}

/*
 * Function name: create_monster
 * Description  : Turns this object into a monster.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_monster()
{
    add_prop(LIVE_I_UNDEAD, 50);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_SEE_INVIS, 5);
    add_prop(OBJ_I_RES_POISON, 100);
    add_prop(OBJ_I_RES_DEATH, 100);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_FEAR, 1);

    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENSE, 100);

    set_random_move(60);
    set_restrain_path(CAVERNS);
    set_monster_home(CAVERNS + "cav5");
}

/*
 * Function name: create_zombie
 * Description  : Generates a zombie based on the name supplied.
 *                This is only functional if the name supplied has
 *                been previously 'zombified' and a save file
 *                exists for it.
 * Arguments    : who - Name of zombie to create.
 * Returns      : -1 - Fail, no name given.
 *                 0 - Success.
 */
public int
create_zombie(string who)
{
    if (!who)
        return -1;

    seteuid(getuid());
    restore_object(ZOMBIE_SAVE(who));
    set_name(my_names);
    remove_adj(0);
    set_adj(my_adjs);
    acc_exp_to_stats();
    set_hp(query_max_hp());
    set_mana(query_max_mana());
}

/*
 * Function name: save_my_zombie
 * Description  : Saves this zombie object.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
save_my_zombie()
{
    seteuid(getuid());
    my_names = query_names();
    my_adjs = query_adjs();
    save_object(ZOMBIE_SAVE(query_name()));
}

public int
second_life(object killer)
{
    command("say Thank you....peace...\n");
    command("sigh");
    rm(ZOMBIE_SAVE(query_name()));
    return 1;
}

public void
remove_object()
{
    if (IS_CLONE)
        save_object(ZOMBIE_SAVE(query_name()));
    ::remove_object();
}

public void
init_living()
{
    ::init_living();
    if (!interactive(TP))
        return;

    if (mappingp(zombie_remembered) &&
        zombie_remembered[TP->query_real_name()] &&
        CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO, TP))
    {
        command("emote slurs: Ahh, " + 
            capitalize(TP->query_real_name()) +
            ", long time no see...I've missed you.");
        command("cackle");
        command("emote slurs: But I won't miss you this time! Die!");
    }
}
