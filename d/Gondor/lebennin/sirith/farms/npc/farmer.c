/*
 * /d/Gondor/lebennin/sirith/farms/npc/farmer
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * inherited by farmers to:
 *	+ id to "farmer" and SIRITH_FARMER
 * 	+ open doors/gates
 *	+ don't move into rooms with other farmers (since they all talk
 *	      about each other) or pig (since all farmers talk about the pig)
 *	+ respond to attacks on farm livestock
 */

#pragma strict_types

inherit "/d/Gondor/std/monster";

#include <macros.h>		/* for CAN_SEE, etc */
#include <stdproperties.h>	/* for OBJ_I_LIGHT, etc */
#include "/d/Gondor/defs.h"
#include "../defs.h"

public void	create_sirith_farmer();
public void	create_gondor_monster();
public string	open_it();
public void	queue_defend(object livestock, object attacker);
public void	do_defend(object livestock, object attacker);
public void	add_introduced(string name);
public void	react_intro(object tp);
public int	query_knight_prestige();


/*
 * Function name:	create_sirith_farmer
 * Description	:	configure your npc here
 */
public void
create_sirith_farmer()
{
} /* create_sirith_farmer */


/*
 * Function name:	create_gondor_monster
 * Description	:	set up farmer
 */
nomask void
create_gondor_monster()
{
    if (!IS_CLONE)
    {
	return;
    }
    FIX_EUID;
    create_sirith_farmer();
    add_name("farmer");
    add_name(SIRITH_FARMER);
    set_ask_log("sirith");
} /* create_gondor_monster */


/*
 * Function name:	open_it
 * Description	:	if there is a door or gate in the room, open it
 * 
 * nice action, and it lets npc wander
 */
public string
open_it()
{
    object door;
    if (objectp(door = present(SIRITH_DOOR, ENV())) &&
	!door->query_open())
    {
	if (ENV()->item_id("door"))
	{
	    command("open door");
	}
	else
	{
	    command("open gate");
	}
    }
    return "";
} /* open_it */


/*
 * Function name:	oke_to_move
 * Description	:	redefine so don't move into rooms with
 *			other farm npcs
 * Arguments	:	string exit -- the direction to try
 * Returns	:	0 -- don't move
 *			string exit -- move 
 *
 * do this because the npcs talk about each other and it looks
 * really stupid if they do that while in the same room.
 * don't wander into pigsty or rooms w pig for same reason.
 */
public mixed
oke_to_move(string exit)
{
    object	env = ENV(),
		dest;
    int		index;
    string	*exit_arr = env->query_exit();

    if (sizeof(exit_arr))
    {
        index = member_array(exit, exit_arr);
	if (index <= 0 ||
	    exit_arr[index-1] == PIGSTY)
	{
	    /* bad exit or goes to sty --- fail */
	    return 0;
	}
	FIX_EUID;
	exit_arr[index-1]->short();
	dest = find_object(exit_arr[index-1]);
	if (objectp(dest) &&
            (objectp(present(SIRITH_FARMER, dest)) ||
             objectp(present(PIGNAME, dest))))
	{
	    /* farmer or pig in next room -- fail */
	    return 0;
	}
    }
    return ::oke_to_move(exit);
} /* oke_to_move */


/*
 * Function name:	queue_defend
 * Description	:	do set_alarm for do_defend()
 * Arguments	:	object livestock -- the animal to defend
 *			object attacker -- its attacker
 * called by livestock when they're attacked
 */
public void
queue_defend(object livestock, object attacker)
{
    set_alarm(6.0, 0.0, &do_defend(livestock, attacker));
} /* queue_defend */


/*
 * Function name:	enter_env
 * Description	:	when enter new env, check for attacks on stock
 * Arguments	:	object destination, object old env
 *
 */
public void
enter_env(object dest, object old)
{
    object	*stock,
		att;
    int		s;

    ::enter_env(dest, old);
    stock = filter(all_inventory(ENV()), &->id(SIRITH_LIVESTOCK));
    if ((s = sizeof(stock)))
    {
	while (s-- > 0)
	{
	    if (objectp(att = stock[s]->query_attack()))
	    {
		set_alarm(4.0, 0.0, &do_defend(stock[s], att));
		return;	/* for now, only defend one */
	    }
	}
    }
} /* enter_env */


/*
 * Function name:	do_defend
 * Description	:	respond to attacks on our livestock
 * Arguments	:	object livestock -- the animal to defend
 *			object attacker -- its attacker
 */
public void
do_defend(object livestock, object attacker)
{
    object	env = ENV(),
		*enemies = TO->query_enemy(-1);
    string	attname,
		realname,
		stockname;

    if (!objectp(attacker) ||
	ENV(attacker) != env || 
        (sizeof(enemies) &&
	 member_array(attacker, enemies) >= 0))
    {
	return;
    }

    realname = attacker->query_real_name();
    if (attacker->query_met(TO))
    {
	attname = attacker->query_cap_name();
    }
    else
    {
	attname = attacker->query_nonmet_name();
    }
    if (objectp(livestock))
    {
	stockname = livestock->query_real_name();
    }
    else
    {
	stockname = "livestock";
    }

    command( ({
	"shout Hey! Don't mess with the "+stockname+"!",
	"shout "+attname+", you bully!",
	"kick "+realname,
	"slap "+realname,
	"shout Leave the "+stockname+" alone, you thug!" ,
	"say We don't like your kind, "+attname+"!",
	})[random(6)] );

    command("kill "+realname);
} /* do_defend */


/*
 * Function name:	add_introduced
 * Description	:	Add the name of a living who has introduced to us
 * Arguments	:	string name -- name of the introduced living
 */
public void
add_introduced(string name)
{
    /* wizards always know the npc name, so query_met() is true.
     * however, assume that if a wiz intro'd, we should respond
     */
    if (interactive(TP) &&
        CAN_SEE_IN_ROOM(TO) &&
	CAN_SEE(TO, TP) &&
        (!TP->query_met(query_name()) ||
	 TP->query_wiz_level()))
    {
	set_alarm(1.0 + (2.0 * rnd()), 0.0, &react_intro(TP));
    }
} /* add_introduced */


/*
 * Function name:	react_intro
 * Description	:	respond to introduction
 * Arguments	:	object tp -- the person who intro'd
 */
public void
react_intro(object tp)
{
    if (ENV(tp) != ENV())
    {
        command("shrug");
        return;
    }
    command("say Hello, " + tp->query_name() + ".");
    command("introduce me to "+tp->query_real_name());
} /* react_intro */


/* tsk,tsk ... attacking law-abiding farmers */
public int query_knight_prestige() { return -5; }
