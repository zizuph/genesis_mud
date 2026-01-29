/*
 * ink.c
 */

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <language.h>

inherit "/std/object";

int left;

create_object()
{
    set_name("ink");
    add_name("_ink_");

    set_short("black ink");
    add_adj("black");

    set_long("This is a black ink which you could wet quills with.\n");

    add_prop(OBJ_I_WEIGHT, 14);
    add_prop(OBJ_I_VALUE,  34);
    add_prop(OBJ_I_VOLUME, 20);

    left = 1000;
}

init()
{
    ::init();
    add_action("do_wet", "wet");
    add_action("do_wet", "dip");
    add_action("do_wet", "ink");
}

int
is_quill(object what)
{
    return what->id("_quill_");
}

int
do_wet(string arg)
{
    mixed *objs;
    object to;

    if (!strlen(arg) ||
	(!parse_command(arg, all_inventory(TP), "[the] %i", objs) &&
	 !parse_command(arg, all_inventory(TP), "[the] %i [using] [with] [into] [in] [the] %o", objs, to)))
	return notify_fail(CAP(query_verb()) + " what?\n");

    objs = NORMAL_ACCESS(objs, "is_quill", TO);

    if (objectp(to) && to != TO)
	return 0;

    if (!sizeof(objs))
	return notify_fail("What quill do you want to " + query_verb() + "?\n");

    left -= 10;

    TP->catch_msg("You wet the " + QSHORT(objs[0]) + " carefully.\n");
    say(QCTNAME(TP) + " wets " + HIS_HER(TP) + " " + QSHORT(objs[0]) + ".\n");

    objs[0]->set_wet();
    return 1;
}
