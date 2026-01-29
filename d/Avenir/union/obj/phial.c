/*
 * The object that summons the ship for the Union guru
 * quest.
 *
 *   Cirion, april 16th, 1997
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#define HOOK	"union_guru_summon_ship"


public void
create_object()
{
    set_name("phial");
    set_short("slender phial");
    set_adj(({"slender","thing"}));

    set_long("Is it a long, narrow phial of viscous liquid.\n"+
	"Etched along the glass are tiny, runic letters.\n");

    add_item(({"letter","letters","rune","runes"}),
	"The runes on the phial are too small to be made out.\n");

    add_cmd_item(({"letter","letters","rune","runes"}), "read",
	"The runes on the phial are too small to be made out.\n");

    add_item("liquid", "The liquid is clear and viscous. It moves "+
	"slowly when the phial is moved, and ripples inexplicably "+
	"appear and disappear along its surface.\n");

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_I_VALUE, 5);
    add_prop(OBJ_I_VALUE, 5);
}

public int
do_throw(string str)
{
    NF("Throw what?\n");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({}), "[the] 'phial' %s", str))
	return 0;

    NF("Throw what where?\n");
    if (!parse_command(str, ({}), "'into' [the] 'sea' / 'water'"))
	return 0;

    NF("You are not near any water.\n");
    if (ENV(TP)->query_prop(ROOM_I_TYPE) != ROOM_BEACH &&
	!function_exists("create_deck", ENV(TP)))
	return 0;

    NF("It somehow seems wrong to do that here.\n");
    if (!function_exists(HOOK, ENV(TP)))
	return 0;

    /* The ship summoning function in the room */
    if (!call_other(ENV(TP), HOOK, TP))
	return 0;

    write("With all your might, you fling the phial into the sea.\n");
    say(QCTNAME(TP) +" fings a phial into the sea.\n");
    set_alarm(0.0, 0.0, remove_object);
    return 1;
}

public void
init(void)
{
    ::init();

    if (environment() == TP)
	add_action(do_throw, "throw");
}

/* Auto load if we are eligable for the quest */
public string
query_auto_load(void)
{
    object who;

    if (!(who=ENV(TO)))
	return 0;

    if (VALID_GURU(who) != 1)
	return 0;

    return MASTER + ":";
}
