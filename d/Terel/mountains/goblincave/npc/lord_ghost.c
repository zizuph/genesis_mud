/*
 * lord_ghost.c
 *
 * The ghost of the goblin eldar.
 *
 * Modification log
 * Lilith July 2008
 * - Lowered natural ac because of mudlib armour changes
 * - Lowered magical resistances
 * - Lowered stats a bit
 *
 * Petros May 2009
 * - Use NPC_I_NO_UNARMED
 * - Remove most resistances. Remove most guild specific code
 * - Adjust exp factor to 125 to account for evade and hunting
 *
 * Lucius - Jan 2021
 *   Cleaned up and modernized.
 */
#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <options.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <language.h>
#include <filter_funs.h>

#include "/d/Terel/mountains/goblincave/spells/ghost_panic.c"

#define HUNT_SHADOW  "/d/Terel/std/follow.c"
#define ALIGN        -300
#define KILL_LOG     (TEREL_DIR + "log/eldar_ghost_kills")

/*
 * Global variables
 */
static object goblin_killer = 0, prey = 0;
static string goblin_killer_name = 0;
static int    shadowed = 0, hunt_alarm = 0;

mixed benice();
void start_hunting();
int query_disallow_mercy(object ob);

void
create_monster()
{
    FIX_EUID;
    ::create_monster();
    set_name("ghost");
    add_name("ghostly");
    add_name("apparition");
    set_long("The translucent looking ghostly apparition " +
      "resembles the shape of an old goblin. It doesn't look " +
      "happy to see you either.\n");
    set_race_name("ghostly apparition");
    set_gender(2);

    set_stats(({120, 120, 120, 80, 80, 120}));
    SET_MAX_HP;
    set_alignment(ALIGN);
    set_all_hitloc_unarmed(35);
    set_all_attack_unarmed(35, 40);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_WEP_SWORD, 75);

    add_prop(LIVE_I_SEE_INVIS,10);
    add_prop(LIVE_I_SEE_DARK, 99);
    add_prop(CONT_I_WEIGHT, 230000);
    add_prop(CONT_I_VOLUME, 230000);
    add_prop(CONT_I_MAX_WEIGHT, 330000);
    add_prop(CONT_I_MAX_VOLUME, 330000);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD,80);
    add_prop(NPC_I_NO_UNARMED, 1);

    add_prop(OBJ_I_RES_COLD, 100);
    add_prop("_ranger_m_no_disarm_drop", 1);
    add_prop("_terel_ghost", 1);
    /* Since he's hunting he doesn't need it.*/
    remove_prop(MONSTER_I_NOT_BOUNCED);

    set_aggressive("@@benice");

    set_m_in("floats into view");
    set_mm_in("floats into view");

    // Blocks 70+% of all hits and hunts
    set_exp_factor(125);
}

int
query_disallow_mercy(object ob)
{
    if (ob->query_merciful())
    {
	write_file(TEREL_DIR + "log/knight_mercy",
            TP->query_name()+" " + ctime(time()) + "\n");
	return 1;
    }
    return 0;
}

public int
special_attack(object enemy)
{
    if (random(10) >= 8)
	panic(enemy);
    return 1;
}

mixed
benice()
{
    if (TP->query_wiz_level())
	return 0;

    if (TP->query_average_stat() <= 90)
	return 0;

    start_hunting();
    return 1;
}

public void
notify_death(object killer)
{
    tell_room(environment(this_object()),
        QCTNAME(this_object()) + " disperses into nothingness.\n",
        this_object());

    if (!living(killer))
	return;

    /*
     * Give specific information about who killed this poor soul.
     */
    tell_object(killer, "You defeated " +
        this_object()->query_the_name(killer) + ".\n");
    tell_room(environment(this_object()),  QCTNAME(killer) +
        " defeated " + this_object()->query_objective() +
        ".\n", ({ this_object(), killer }));
}

public int
query_not_attack_me(object who, int attack_id)
{
    if (random(8) > 2)
	return 0;

    object *temp = who->query_weapon(-1);

    for(int i=0; i<sizeof(temp); i++)
    {
	// This is to fix special attacks that do not properly
        // return specific hit locations.
	if (attack_id == -1)
	{
	    tell_object(who, "You miss the translucent " + short() +
                " entirely!\n");
	    who->tell_watcher(QCTNAME(who) + " misses the translucent " +
                short() + " entirely!\n", who, 0);
	    return 0;
	}

	if (temp[i]->query_attack_id() == attack_id)
	{
	    tell_object(who, "Your " + temp[i]->short() +
                " passes harmlessly through the translucent " +
                short() + "!\n");
	    who->tell_watcher(QCTNAME(who) + "'s " +
                temp[i]->short() +
                " passes harmlessly through the translucent " +
                short() + "!\n", who, 0);
	    return 0;
	}
    }

    tell_object(who, "Your " + who->cr_attack_desc(attack_id) +
        " passes harmlessly through the translucent " + short() + "!\n");
    who->tell_watcher(QCTNAME(who) + "'s " +
        who->cr_attack_desc(attack_id) +
        " passes harmlessly through the translucent " + short() + "!\n",
        who, 0);

    return 1;
}

void
arise()
{
    command("emote arises from the dead body of the goblin eldar.");
    command("say " + goblin_killer_name + "!  You killed me!");
    command("say Prepare to die!");
}

void
set_killer(object k)
{
    goblin_killer = k;
    goblin_killer_name = k->query_name();
    set_random_move(0);
}

void
attack_killer(string s1, string s2)
{
    aggressive_attack(goblin_killer);
}

void
attack()
{
    aggressive_attack(goblin_killer);
}

void
do_die(object killer)
{
    if (query_hp() > 0)
        return;

    object *enemies = query_my_enemies();
    string str = killer->query_name() + "[" + killer->query_average_stat() + "]";

    for (int i=0; i<sizeof(enemies); i++)
    {
	if (enemies[i] != killer)
        {
	    str += ", " + enemies[i]->query_name() +
                "[" + enemies[i]->query_average_stat() + "]";
        }
    }
    write_file(KILL_LOG, str + " (" + ctime(time()) + ")\n");
    ::do_die(killer);
}

//  Here are the hunting functions :)
public void
attack_object(object ob)
{
    ::attack_object(ob);
    if (!prey && !shadowed && !hunt_alarm)
	hunt_alarm = set_alarm(itof(random(1) + 1), 0.0,&start_hunting());
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    if (!prey && !shadowed && !hunt_alarm)
	hunt_alarm = set_alarm(itof(1 + random(1)),0.0,&start_hunting());
}

void
start_hunting()
{
    if (hunt_alarm)
    {
	remove_alarm(hunt_alarm);
	hunt_alarm = 0;
    }

    //  Can't hunt if we aren't killing somene ;)
    if (!objectp(query_attack()))
	return;

    //  We already got our prey in our hunting sights
    if (objectp(prey) && shadowed)
	return;

    object *enemies = query_enemy(-1) & all_inventory(environment());
    //  Make sure there are no npcs in the array.
    enemies = FILTER_PLAYERS(enemies);
    if (!sizeof(enemies))
	return;

    prey = enemies[random(sizeof(enemies))];
    clone_object(HUNT_SHADOW)->follow(prey,TO);
    shadowed = 1;
}

//  Called from the follow shadow
void
notify_stopped_hunt()
{
    prey = 0;
    shadowed = 0;
}

string
query_hunting()
{
    return prey->query_real_name();
}

int
query_shadowed()
{
    return shadowed;
}
