/*
 * - /d/Avenir/union/room/base.c
 *
 *   Base room for the Union Guildhall.
 *
 * Revisions:
 *   Lucius, May 2016: Created and modified rooms to use it.
 *
 */
#pragma strict_types
#include "../defs.h"

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

inherit "/std/room";


/*
 * VBFC Call to limit snooping.
 */
public int
anti_snoop(void)
{
    return !IS_MEMBER(TP);
}

/*
 * VBFC Call to restrict magic.
 */
public mixed
anti_magic(void)
{
    if (!objectp(TP) || !STATE || !environment(TP) ||
	!wildmatch("/d/Avenir/union/*", file_name(environment(TP))))
    {
	return 0;
    }

    if (time() - TP->query_prop("cast_spell_in_union") < 5)
	return 0;

    TP->add_prop("cast_spell_in_union", time());
    set_alarm(0.5, 0.0, &(HOME)->anti_magic_effect(TP));
    return 0;
}

/*
 * Function name: union_room
 * Description:   Used for Union rooms creation code.
 */
public void
union_room(void)
{
}

/*
 * Function name: update_vars
 * Description:   Used for Union rooms to delay assign variables.
 */
static void
update_vars(void)
{
}

public nomask void
create_room(void)
{
    /* Inside */
    add_prop(ROOM_I_INSIDE, 1);
    /* No hiding */
    add_prop(ROOM_I_HIDE, -1);
    /* No Scrying */
    add_prop(ROOM_M_NO_SCRY, anti_snoop);
    /* No Magic */
    add_prop(ROOM_M_NO_MAGIC, anti_magic);
    add_prop(ROOM_M_NO_TELEPORT, anti_magic);
    add_prop(ROOM_M_NO_TELEPORT_TO, anti_magic);

    union_room();

    set_alarm(0.0, 0.0, update_vars);
}

public object *
get_view(string *arr)
{
    object *inv = ({});

    foreach(string path: arr)
    {
	object room = find_object(path);
	if (objectp(room))
	    inv += all_inventory(room);
    }

    if (sizeof(inv))
	inv = FILTER_CAN_SEE(FILTER_LIVE(inv), TP);

    return inv;
}

public string
exa_chasm(void)
{
    TP->add_panic(85);
    TP->add_fatigue(4);

    say(QCTNAME(TP) +" looks down into the lake below "+
	"and sways slightly.\n");
    return "A hundred feet below, a bubbling mass of molten rock "+
	"seems to be swirling into itself. Superheated air rises up "+
	"from the lake below, and you feel dizzy just looking at it.\n";
}

#define WARNED	"_Union_warned_about_ledge"

public int
jump_ledge(string str)
{
    NF(CAP(query_verb())+" where?");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({ }),
	    "'off' / 'down' / 'ledge' [of] [the] [ledge]"))
	return 0;

    if (!TP->query_prop(WARNED))
    {
	TP->add_prop(WARNED, 1);
	write("You pause for a moment to reconsider suicide.\n");
	say(QCTNAME(TP)+" looks down over the ledge, pondering "+
	    "the situation.\n");
	return 1;
    }

    /* Idiot */
    LOG_EVENT(NM(TP) +" jumped off the ledge and died");
    write("You take a breath and leap off the ledge.\n"+
	"You land with a spash in the molten rock, your "+
	"body incinerated.\n");
    say(QCTNAME(TP) +" leaps off the ledge and falls a hundred "+
	"feet to "+ HIS(TP)+" death.\n");

    TP->move(VOID);
    TP->heal_hp(-(TP->query_max_hp()));
    TP->do_die(TO);
    return 1;
}

public void
remove_warned(object ob)	{ ob->remove_prop(WARNED); }
