/*
 * vest_base.c
 *
 * Base object for a variety of different vests to
 * save a bit of cut'n'pasting. Vests may be laced
 * and unlaced. Laced vests have a higher AC, but
 * must be unlaced to remove.
 *
 * Khail - August 12, 1997
 */
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

inherit "/std/armour";
inherit "/lib/keep";

int ac,
weight,
volume,
laced;

public string
laced_desc()
{
    if (!laced)
        return "The front of the vest can be laced up with " +
        "leather thongs, but currently hangs open.\n";
    return "The front of the vest is laced up with leather " +
    "thongs.\n";
}

public void
create_vest(string colour, string material)
{
    set_name("vest");
    set_at(A_BODY);
    set_keep(0); //nuisance for packing/selling
    set_af(TO);
    set_short(colour + " " + material + " vest");
    set_pshort(colour + " " + material + " vests");
    set_adj(colour);
    add_adj(material);
    set_long(query_long() + VBFC_ME("laced_desc"));

    if (material == "cloth")
    {
        ac = 1;
        weight = 400;
        volume = 1300;
    }
    else if (material == "wool")
    {
        ac = 2;
        weight = 650;
        volume = 1800;
    }
    else if (material == "leather")
    {
        ac = 3;
        weight = 650;
        volume = 2000;
    }
    else if (material == "hard leather")
    {
        ac = 6;
        weight = 1000;
        volume = 3000;
    }
    else
    {
        ac = 1;
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
    if (laced)
        return "You must unlace the " + short() + " before " +
        "you can wear it.\n";

    say(QCTNAME(TP) + " shrugs into " + LANG_ADDART(short()) + ".\n");
    write("You shrug into the " + short() + " and " +
      "settle it over your shoulders.\n");
    return 1;
}

public mixed
remove(object what)
{
    if (wearer->query_hp() <= 0)
    {
        return 1;
    }

    if (laced)
    {
        wearer->catch_tell("You must unlace the vest before " +
          "you can remove it.\n");
        return -1;
    }

    tell_room(environment(wearer), QCTNAME(wearer) + " slips " +
      HIS_HER(wearer) + " " + short() + " off " +
      HIS_HER(wearer) + " shoulders.\n", ({wearer}));
    wearer->catch_tell("You slip the " + short() + " off " +
      "your shoulders.\n");
    return 1;
}

public int
do_lace(string str)
{
    mixed vest;

    NF("Lace what up, a vest?\n");
    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "[the] %i [up]", vest))
        return 0;

    if (!vest[0])
    {
        if (sizeof(vest) > 2)
        {
            NF("You can't lace up more than one vest at a time.\n");
            return 0;
        }
        else
            vest = (object)vest[1];
    }

    else if (vest[0] > 0)
    {
        if (vest[0] > 1)
        {
            NF("You can't lace up more than one vest at a time.\n");
            return 0;
        }
        else
            vest = (object)vest[vest[0]];
    } 

    else
        vest = (object)vest[-vest[0]];

    if (vest != TO)
        return 0;

    if (!CAN_SEE_IN_ROOM(TP) || !CAN_SEE(TP, vest))
    {
        NF("You see no such vest.\n");
        return 0;
    }

    if (laced)
    {
        write("The " + short() + " is already laced up.\n");
        return 1;
    }

    say(QCTNAME(TP) + " deftly laces up " + LANG_ADDART(short()) +
      ".\n");
    write("You deftly lace up the " + short() + ".\n");
    laced = 1;
    set_ac(query_ac() + 2);
    if (query_worn())
        wearer->update_armour(TO);
    return 1;
}

public int
do_unlace(string str)
{
    mixed vest;

    NF("Unlace what, a vest?\n");
    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "[the] %i [up]", vest))
        return 0;

    if (!vest[0])
    {
        if (sizeof(vest) > 2)
        {
            NF("You can't unlace more than one vest at a time.\n");
            return 0;
        }
        else
            vest = (object)vest[1];
    }

    else if (vest[0] > 0)
    {
        if (vest[0] > 1)
        {
            NF("You can't unlace more than one vest at a time.\n");
            return 0;
        }
        else
            vest = (object)vest[vest[0]];
    } 

    else
        vest = (object)vest[-vest[0]];

    if (vest != TO)
        return 0;

    if (!CAN_SEE_IN_ROOM(TP) || !CAN_SEE(TP, vest))
    {
        NF("You see no such vest.\n");
        return 0;
    }

    if (!laced)
    {
        write("The " + short() + " is already unlaced.\n");
        return 1;
    }

    say(QCTNAME(TP) + " deftly unlaces " + LANG_ADDART(short()) +
      ".\n");
    write("You deftly unlace the " + short() + ".\n");
    laced = 0;
    set_ac(query_ac() - 2);
    if (query_worn())
        wearer->update_armour(TO);
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_lace, "lace");
    add_action(do_unlace, "unlace");
}
