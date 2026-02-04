/*
 * base_shirt.c
 *
 * Base object for a variety of different shirts to
 * save a bit of cut'n'pasting.
 *
 * Khail - August 12, 1997
 */
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Khalakhor/sys/defs.h"

inherit "/std/armour";
inherit "/lib/keep";

int ac,
weight,
volume;

public void
create_shirt(string colour, string material)
{
    set_name("shirt");
    set_at(A_BODY | A_ARMS);
    set_keep(1);
    set_af(TO);
    set_adj(colour);
    add_adj(material);

    if (material == "cloth")
    {
        ac = 2;
        weight = 400;
        volume = 1500;
    }
    else if (material == "wool")
    {
        ac = 3;
        weight = 650;
        volume = 2000;
    }
    else if (material == "leather")
    {
        ac = 5;
        weight = 650;
        volume = 2200;
    }
    else
    {
        ac = 5;
        weight = 1000;
        volume = 2000;
    }

    set_ac(ac);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac));
    add_prop(OBJ_I_WEIGHT, weight);
    add_prop(OBJ_I_VOLUME, volume);
}

public mixed
wear(object what)
{
    say(QCTNAME(TP) + " pulls the " + short() + " on over " +
      HIS_HER(TP) + " head.\n");
    write("You pull the " + short() + " over your head and " +
      "settle it over your shoulders.\n");
    return 1;
}

public mixed
remove(object what)
{
    if (wearer->query_hp() <=0)
    {
        return 1;
    }

    tell_room(environment(wearer), QCTNAME(wearer) + " slips " +
      HIS_HER(wearer) + " " + short() + " off over " +
      HIS_HER(wearer) + " head.\n", ({wearer}));
    wearer->catch_tell("You slip the " + short() + " off " +
      "over your head.\n");
}
