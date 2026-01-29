/*
 * Fog object
 *
 * CLoned into room to confuse exits
 */

#include <macros.h>
#include <stdproperties.h>
#include <tasks.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/object";
inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/d/Genesis/newmagic/resist";

static int    effect_alarm;

public int
confuse(string direct)
{
    if (interactive(this_player()) && (spell_resist_illusion(spell_caster,
        this_player(), spell_element, TASK_ROUTINE) <= 50))
    {
        string *exname = spell_target->query_exit_cmds(),
               *expath = spell_target->query_exit_rooms();
        int     number = random(sizeof(expath));

        write("You continue through the fog, quite unsure where you" +
            " are going.\n");

        return !(this_player()->move_living(exname[number], expath[number]));
    }

    return 0;
}

public void
confuse_exit(mixed exitar, mixed fatval, mixed nonobv)
{
    if (!exitar[2])
    {
        spell_target->remove_exit(exitar[1]);
        spell_target->add_exit(exitar[0], exitar[1], &confuse(exitar[1]),
            fatval, nonobv);
    }
}

public void
restore_exit(mixed exitar, mixed fatval, mixed nonobv)
{
    if (functionp(exitar[2]) &&
        (function_name(exitar[2]) == function_name(confuse)))
    {
        spell_target->remove_exit(exitar[1]);
        spell_target->add_exit(exitar[0], exitar[1], 0, fatval, nonobv);
    }
}

public int
start()
{
    mixed   exitar, fatval, nonobv;
    int     number;

    set_name("_wohs_fog");

    set_no_show();

    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);

    if (move(spell_target))
    {
        return 0;
    }

    exitar = spell_target->query_exit();
    fatval = spell_target->query_tired_exits();
    nonobv = spell_target->query_non_obvious_exits();
    number = sizeof(exitar) / 3;

    while (--number >= 0)
    {
        confuse_exit(exitar[(number * 3)..(number * 3) + 2],
            fatval[number], nonobv[number]);
    }

    /* think its ugly? look at room exit code, thats ugly! ;-) */

    spell_target->add_my_desc("A heavy fog covers the surroundings.\n",
        this_object());

    return 1;
}

public varargs int
dispel_spell_effect(object dispeler)
{
    mixed   exitar, fatval, nonobv;
    int     number;

    exitar = spell_target->query_exit();
    fatval = spell_target->query_tired_exits();
    nonobv = spell_target->query_non_obvious_exits();
    number = sizeof(exitar) / 3;

    while (--number >= 0)
    {
        restore_exit(exitar[(number * 3)..(number * 3) + 2],
            fatval[number], nonobv[number]);
    }

    spell_target->remove_my_desc(this_object());

    tell_room(environment(), "The fog around you disolves into nothing.\n");
    remove_spell_effect_object();
    return 1;
}

public void
set_spell_duration(int argval)
{
    if (effect_alarm)
    {
        remove_alarm(effect_alarm);
    }

    effect_alarm = set_alarm(itof(argval), 0.0, &dispel_spell_effect(0));
}

public int
query_spell_duration()
{
    mixed   values;

    if (pointerp(values = get_alarm(effect_alarm)))
    {
        return values[2];
    }

    return 0;
}

