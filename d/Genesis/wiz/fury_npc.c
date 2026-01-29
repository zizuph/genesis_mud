/*
 * /d/Genesis/wiz/fury_npc.c
 *
 * This is the fury that will hunt and attack a player until it is killed.
 * The administration can call this wrath on someone if necessary.
 *
 * Copyright (C) Stas van der Schaaf - November 12 1995
 *               Mercade @ Genesis
 */

#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

/*
 * Global variables.
 */
static private string target;
static private int    will_stop;
static private string reason;
static private int    alarm_monitor_fight;

/*
 * Prototype.
 */
static void monitor_fight();

#define FURY_MASTER ("/d/Genesis/wiz/fury")
#define MAX_TRIES   (10)
#define HP_LIMIT    (15)

#define A_CLAW  0
#define A_TALON 1

/*
 * Function name: create_creature
 * Description  : This function call will create the creature.
 */
void
create_creature()
{
    /* 33% chance for some extra harassment *grin*/
    will_stop = (random(100) < 33);

    set_race_name("fury");
    add_name("avenger");
    set_adj("ghostly");

    set_gender(G_NEUTER);

    set_short("ghostly fury");
    set_long("@@long_description@@");

    set_base_stat(SS_STR, 140 + random(21));
    set_base_stat(SS_DEX, 190 + random(21));
    set_base_stat(SS_CON,  90 + random(21));
    set_base_stat(SS_INT,  90 + random(21));
    set_base_stat(SS_WIS,  90 + random(21));
    set_base_stat(SS_DIS,  90 + random(21));

    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE,       90 + random(11));
    set_skill(SS_AWARENESS,     80 + random(21));

    set_alignment(0);

    add_prop(LIVE_I_NON_REMEMBER,      1);
    add_prop(LIVE_I_NEVERKNOWN,        1);
    add_prop(LIVE_I_SEE_INVIS,        10);
    add_prop(LIVE_I_SEE_DARK,         10);
    add_prop(OBJ_M_NO_TELEPORT,        1);
    add_prop(NPC_I_NO_LOOKS,           1);
    add_prop(CONT_I_VOLUME,        30000 + random(10000));
    add_prop(CONT_I_WEIGHT,        30000 + random(10000));

    add_prop(MAGIC_I_RES_ACID,        75);
    add_prop(MAGIC_I_RES_COLD,        75);
    add_prop(MAGIC_I_RES_ELECTRICITY, 75);
    add_prop(MAGIC_I_RES_LIGHT,       75);
    add_prop(MAGIC_I_RES_MAGIC,       75);
    add_prop(MAGIC_I_RES_POISON,      75);
    add_prop(MAGIC_I_RES_AIR,         75);
    add_prop(MAGIC_I_RES_WATER,       75);
    add_prop(MAGIC_I_RES_EARTH,       75);
    add_prop(MAGIC_I_RES_FIRE,        75);
    add_prop(MAGIC_I_RES_DEATH,       75);

    add_prop(OBJ_M_NO_ATTACK, "@@obj_m_no_attack@@");

    set_attack_unarmed(A_CLAW,  random(41) + 40, random(41) + 40, W_IMPALE,
	50, "one of its claws");
    set_attack_unarmed(A_TALON, random(41) + 40, random(41) + 40, W_SLASH,
	50, "one of its talons");
}

/*
 * Function nane: long_description
 * Description  : We modify the long descripton so that the target will
 *                be able to see why he is being attacked.
 * Returns      : string - the long descripton.
 */
public string
long_description()
{
    string str = "This ghostly fury is the wrath of Genesis. It will haunt " +
	"people who misbehave in a very serious way and who have shown " +
	"themselves to be less than cooperative when addressed. Various " +
	"features of the anatomy of the fury are blurred and misty. " +
	"However, its talons are very visible. The end of each claw is " +
	"has some rather sharp hooks. Its eyes radiate evil and promise " +
	"woe over whoever they target to destroy.";

    if (this_player()->query_real_name() == target)
    {
	str += " You seem to be the target of the malice. " + reason;
    }
    else if (this_player()->query_wiz_level())
    {
	str += " The target of this fury is " + capitalize(target) + ".";
    }

    return break_string(str, 75) + "\n";
}

/*
 * Function name: fury_start
 * Description  : This function is called from the fury master to start the
 *                fury.
 * Arguments    : string player - the name of the target.
 *                string str    - the reason.
 */
void
fury_start(string player, string str)
{
    object victim;

    target = player;
    reason = str;
    victim = find_player(target);

    set_m_in("arrives out of nowhere.");
    set_m_out("vanishes");
    set_mm_in("arrives out of nowhere.");
    set_mm_out("vanishes into nothingness.");

    move_living("M", environment(victim));

    tell_room(environment(), "Out of nowhere, a ghostly fury arrives.\n");

    command("point " + OB_NAME(victim));

    tell_room(environment(), "The ghostly fury howls: YOU! Your day has " +
	"come! Your ill behaviour shall not stand as retribution is my goal " +
	"on behalf of the mighty Gods of Genesis. " + str + "\n",
	({ this_object() }) );

    attack_object(victim);
    add_prop(LIVE_O_ENEMY_CLING, victim);
    alarm_monitor_fight = set_alarm(30.0, 30.0, monitor_fight);
}

/*
 * Function name: query_not_attack_me
 * Description  : We do not allow anyone to hit on us, not even the target.
 * Arguments    : object attacker - the attacker.
 *                int attack_id   - the attack id.
 * Returns      : int 1 - always.
 */
int
query_not_attack_me(object attacker, int attack_id)
{
    return 1;
}

/*
 * Function name: remove_attacking_player
 * Description  : When someone has tried to attack us, we use this little
 *                alarm and then we try to toss him out of the room.
 * Arguments    : object player - the player that dared attack us.
 */
static void
remove_attacking_player(object player)
{
    object victim = find_player(target);
    string *exits;
    int    size;
    int    index;

    if (environment() != environment(player))
    {
	return;
    }

    if (objectp(victim))
    {
	tell_object(player, "The ghostly fury rasps to you: You dared " +
	    "attack me! My presence is none of your business as this is a " +
	    "matter between me and " + victim->query_the_name(player) +
	    ". Begone!\n");
	tell_room(environment(), "The ghostly fury rasps to " +
	    QTNAME(player) + ": You dared attack me! My presence is none of " +
	    "your business as this is a matter between me and " +
	    QTNAME(victim) + "! Begone!\n", ({ player, this_object() }) );
    }
    else
    {
	tell_object(player, "The ghostly fury rasps to you: You dared " +
	    "attack me! My presence is none of your business. Begone!\n");
	tell_room(environment(), "The ghostly fury rasps to " +
	    QTNAME(player) + ": You dared attack me! My presence if none of " +
	    "your business! Begone!\n", ({ player, this_object() }) );
    }

    exits = environment()->query_exit();
    size = sizeof(exits);
    while((size -= 3) >= 0)
    {
	if (exits[size + 2] != 0)
	{
	    exits = exclude_array(exits, size, (size + 2));
	}
    }

    if (!(size = sizeof(exits)))
    {
	return;
    }

    size = random(size / 3) * 3;

    tell_object(player, "The ghostly fury grabs you with its claws and " +
	"tosses you aside!\n");

    if (player->move_living("M", exits[size]))
    {
	tell_room(environment(), "The ghostly fury grabs " + QTNAME(player) +
	    " with its claws and tosses " + player->query_objective() +
	    " aside!\n", ({ player, this_object() }) );
	return;
    }

    tell_room(environment(), "The ghostly fury grabs " + QTNAME(player) +
	" with its claws and tosses " + player->query_objective() +
	" out of view!\n", ({ this_object() }) );
    tell_room(environment(player), "Suddenly " + QNAME(player) + " comes " +
	"flying, hits the ground and rolls over a few times.\n",
	({ player }) );
    tell_object(player, "After flying into the room, you hit the ground " +
	"and roll over a few times.\n");
}

/*
 * Function name: obj_m_no_attack
 * Description  : We do not allow mortals to attack the fury. If they try,
 *                they are thrown out of the room, if possible.
 * Returns      : mixed - the return argument.
 */
mixed
obj_m_no_attack()
{
    if (!objectp(this_player()))
    {
	return "It is not possible to attack the ghostly fury.\n";
    }

    if (this_player()->query_real_name() == target)
    {
	return "Attack the ghostly fury? " +
	    "That would be turning the world around!\n";
    }

    set_alarm(1.0, 0.0, &remove_attacking_player(this_player()));
    return "There is no reason for you to attack the ghostly fury.\n";
}

/*
 * Function name: search_for_enemy
 * Description  : When the victim looses its link or quits, we keep looking
 *                for MAX_TRIES minutes before we return operation to the
 *                FURY_MASTER again.
 */
static void
search_for_enemy(int times)
{
    object victim;

    if (!objectp(victim = find_player(target)))
    {
	if (++times >= MAX_TRIES)
	{
	    FURY_MASTER->fury_interrupted(target);
	    remove_object();
	    return;
	}

	set_alarm(60.0, 0.0, &search_for_enemy(times));
	return;
    }

    move_living("M", environment(victim));

    tell_room(environment(), "Out of sheer nothingness, the ghostly fury " +
	"emerges and shrieks: There is no escaping me!\n",
	({ this_object() }) );

    attack_object(victim);
    add_prop(LIVE_O_ENEMY_CLING, victim);

    if (!alarm_monitor_fight)
    {
	alarm_monitor_fight = set_alarm(30.0, 30.0, monitor_fight);
    }
}

/*
 * Function name: notify_enemy_gone
 * Description  : When our victim isn't there anymore, if it linkdies or
 *                quits, we will go into hiding until we find it again.
 * Arguments    : object enemy - the enemy that we were fighting.
 */
void
notify_enemy_gone(object enemy)
{
    tell_room(environment(), "As its target has disappeared, the ghostly " +
	"fury vanishes into nothingness.\n", ({ this_object() }) );
    move_living("M", FURY_MASTER);
    stop_heart();

    /* Enemy still is in the game. Seek him in a second. */
    if (objectp(enemy))
    {
	set_alarm(1.0, 0.0, &search_for_enemy(0));
	return;
    }

    remove_alarm(alarm_monitor_fight);
    alarm_monitor_fight = 0;
    set_alarm(60.0, 0.0, &search_for_enemy(0));
}

/*
 * Function name: monitor_fight
 * Description  : This alarm is a waste of time, but it seems that it is
 *                the easiest way to make sure the victim cannot escape
 *                the fury.
 */
static void
monitor_fight()
{
    object victim;

    if (!objectp(victim = find_player(target)))
    {
	notify_enemy_gone(victim);
	return;
    }

    if (environment(victim) != environment())
    {
	tell_room(environment(), "The ghostly fury vanishes into " +
	    "nothingness in search for its victim.\n", ({ this_object() }) );
	search_for_enemy(0);
	return;
    }

    if (query_attack() != victim)
    {
	attack_object(victim);
	add_prop(LIVE_O_ENEMY_CLING, victim);
	return;
    }
}

/*
 * Function name: special_attack
 * Description  : We use the special attack for some very nasty features,
 *                like retreating after we nearly slaughtered the target.
 * Arguments    : object enemy - the enemy we are fighting.
 * Returns      : int - true if this function succeeded in a 'hit'.
 */
int
special_attack(object enemy)
{
    if (!will_stop)
    {
	return 0;
    }

    /* This will be true if the enemy has more than HP_LIMIT% of his max hp */
    if ((100 * enemy->query_hp()) > (enemy->query_max_hp() * HP_LIMIT))
    {
	return 0;
    }

    tell_room(environment(), "The ghostly fury grumbles: Time for lunch! " +
	"I shall deal with you later.\nThen, the ghostly fury vanishes " +
	"into nothingness.\n", ({ this_object() }) );
    move_living("M", FURY_MASTER);

    enemy->stop_fight(this_object());
    stop_fight(enemy);
    stop_heart();

    FURY_MASTER->fury_to_lunch(target);
    will_stop = 0;

    set_alarm(900.0, 0.0, &search_for_enemy(0));
    return 1;
}

/*
 * Function name: do_die
 * Description  : The fury cannot die. If someone tries to kill us, we will
 *                heal ourselves.
 * Arguments    : object killer - the attacker.
 */
public void
do_die(object killer)
{
    heal_hp(random(query_max_hp()));
}

/*
 * Function name: notify_you_killed_me
 * Description  : When we have killed our target, we enjoy and leave after
 *                we have updated our fury master.
 * Arguments    : object victim - the victim we killed.
 */
void
notify_you_killed_me(object victim)
{
    if (victim->query_real_name() != target)
    {
	return;
    }

    tell_room(environment(), "With an evil grin on its face, the ghostly " +
	"fury welcomes the death of " + QTNAME(victim) + ". As The Avenger " +
	"has fulfilled its duty, the ghostly fury disintegrates into " +
	"eternity!\n", ({ this_object() }) );

    FURY_MASTER->fury_succeeded(target);

    remove_object();
}

/*
 * Function name: fury_removed
 * Description  : The fury is being withdrawn from the player.
 * Arguments    : string name - the player who got a pardon.
 */
void
fury_remove(string name)
{
    if (MASTER_OB(previous_object()) != FURY_MASTER)
    {
	return;
    }

    if (name == target)
    {
	tell_room(environment(), "The ghostly fury howls: It seems someone " +
	    "took pity on you! I shall leave you for now, but remember: " +
	    "Behave yourself or I shall be back!\nThen the ghostly fury " +
	    "vanishes into nothingness.\n", ({ this_object() }) );
	remove_object();
    }
}

/*
 * Function name: add_prop_live_i_attack_delay
 * Description  : We disallow adding of the property LIVE_I_ATTACK_DELAY.
 * Arguments    : mixed value - whichever value it tries to set.
 * Returns      : int 1 - always.
 */
int
add_prop_live_i_attack_delay(mixed value)
{
    return 1;
}

/*
 * Function name: add_prop_live_i_stunned
 * Description  : We disallow adding of the property LIVE_I_STUNNED.
 * Arguments    : mixed value - whichever value it tries to set.
 * Returns      : int 1 - always.
 */
int
add_prop_live_i_stunned(mixed value)
{
    return 1;
}

/*
 * Function name: add_prop_live_as_attack_fumble
 * Description  : We disallow adding of the property LIVE_AS_ATTACK_FUMBLE.
 * Arguments    : mixed value - whichever value it tries to set.
 * Returns      : int 1 - always.
 */
int
add_prop_live_as_attack_fumble(mixed value)
{
    return 1;
}

/*
 * Function name: query_prevent_shadow
 * Description  : We disallow anyone to shadow us.
 * Returns      : int 1 - always.
 */
nomask int
query_prevent_shadow()
{
    return 1;
}
