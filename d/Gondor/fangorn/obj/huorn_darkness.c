#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

#define WRAPPED_IN_SHADOWS "_wrapped_in_shadows"

static int     expand;

public int do_summon(string str);

public void
create_object()
{
    set_name("huorn_darkness");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_STEAL, 1);

    set_no_show();
}

int
stop_glooming()
{
    if (random(10) > 7)
    {
        remove_alarm(expand);
        expand = 0;
        TP->remove_prop(WRAPPED_IN_SHADOWS);
        TO->remove_prop(OBJ_I_LIGHT);
        write("The shadows you have summoned disappear.\n");
        say("The " +QTNAME(TP)+ "'s veil of shadows disappears.\n");
    return 1;
    }
    else
    {
        remove_alarm(expand);
        expand = 0;
        TP->remove_prop(WRAPPED_IN_SHADOWS);
        TO->remove_prop(OBJ_I_LIGHT);

    switch (random(3))
        {
    case 0:
        write("The shadows around you dissipate.\n");
        say("The shadows around " +QTNAME(TP)+ " dissipate.\n");
        break;
    case 1:
        write("You stop radiating darkness.\n");
        say("The darkness around " +QTNAME(TP)+ " diminishes.\n");
        break;
    case 2:
        write("Your shroud of darkness lifts.\n");
        say("The shroud of darkness around " +QTNAME(TP)+ " lifts.\n");
        break;
        }

    return 1;
    }
}

int
do_gloom()
{
    write("You summon shadows around yourself!\n");

    switch (random(3))
    {
    case 0:
        say("Darkness begins to gather around " +QTNAME(TP) + "!\n");
        break;
    case 1:
        say(QCTNAME(TP) + " starts to gather shadows around himself!\n");
        break;
    case 2:
        say("Shadows start to gather around " +QTNAME(TP) + "!\n");
        break;
    }
    TO->add_prop(OBJ_I_LIGHT, (-50 - (random(150))));
    TP->add_prop(WRAPPED_IN_SHADOWS, 1);
    set_alarm(200.0, 0.0, &stop_glooming());

    return 1;
}

public void
init()
{
  ::init();

  add_action(do_summon, "summon");
}

public int
do_summon(string str)
{

    if (!strlen(str))
    {
        NFN0("What do you want to summon?");
    }

    if (!parse_command(str, ({}), "'shadows'"))
    {
        NF("What do you want to summon?\n");
        return 0;
    }

    if (TP->query_prop(WRAPPED_IN_SHADOWS) == 1)
    {
        write("You have already summoned shadows.\n");
        return 1;
    }

        do_gloom();
        return 1;
}

