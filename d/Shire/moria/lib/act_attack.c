/*  -*- LPC -*-  */

/* 
 * act_attack.c
 *
 * Module for selective attacking. Based on /std/act/attack.c
 *
 * Sir Rogon.
 *
 */

#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <cmdparse.h>
#include <language.h>
#include <formulas.h>

static int monster_attack_chance;
static int monster_aggressive;

public void agressive_attack(object ob);
public void set_aggressive(mixed i) { monster_aggressive = i; }
public void set_attack_chance(int i) { monster_attack_chance = i; }

public void
init_attack()
{
    if ((!monster_aggressive) || (this_player()->query_npc()))
	return;

    if ((monster_attack_chance == 0) || (random(100) < monster_attack_chance))
    set_alarm(2.0, 0.0, &agressive_attack(TP));
}

public void
aggressive_attack(object ob)
{
    if (!present(ob, environment(this_object())))
	return;

    if (!CAN_SEE_IN_ROOM(this_object()) ||
	!living(ob) ||
	ob == this_object() ||
	environment()->query_prop(ROOM_M_NO_ATTACK) ||
	ob->query_prop(OBJ_M_NO_ATTACK))
	return;

    this_object()->reveal_me();
    if (!F_DARE_ATTACK(this_object(), ob))
	return;
    
    attack_object(ob);
    add_prop(LIVE_O_LAST_KILL, ob);
}

