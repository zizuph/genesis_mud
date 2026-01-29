/*
 * bladesmith_rack.c
 *
 * This object is a rack for the weapons in the bladesmith's
 * forge. Weapons contained within it cannot be taken by players
 * unless they've paid for it, but can be appraised using a
 * special syntax so they can see if it reboots.
 *
 * Khail - April 11/97
 */
#pragma strict_types

#include <composite.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Khalakhor/sys/defs.h"
#include "defs.h"

inherit "/std/container";

object remove_called_once;

/*
 * Function name: reset_object
 * Description  : Resets the rack contents.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_container()
{
    int i;
    object *weapons;
    reset_euid();

    weapons = FIND_STR_IN_OBJECT("claymores", TO);
    for (i = sizeof(weapons); i < 4; i++)
        clone_object("/d/Khalakhor/common/wep/claymore")->move(TO);

    weapons = FIND_STR_IN_OBJECT("dirks", TO);
    for (i = sizeof(weapons); i < 6; i++)
        clone_object("/d/Khalakhor/common/wep/dirk")->move(TO);

    weapons = FIND_STR_IN_OBJECT("axes", TO);
    for (i = sizeof(weapons); i < 4; i++)
        clone_object("/d/Khalakhor/common/wep/axe")->move(TO);
}

public mixed
check_remove()
{
    int i;
    object temp,
           weapon,
           taker;
    string incoming;

    while (temp = previous_object(i))
    {
        if (temp->check_weapon())
            weapon = temp;
        i--;
    }

    if (weapon->query_prop("_obj_i_weapon_paid_for"))
        return 0;

    if (remove_called_once)
    {
        TP->catch_msg("The " + remove_called_once->short() + " is " +
            "securely locked to the " + short() + ", you'll have " +
            "to buy it if you want it.\n");
        remove_called_once = 0;
        return "";
    }
    remove_called_once = weapon;
    return 1;
}

/*
 * Function name: create_container
 * Description  : Turns this object into a container
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_container()
{
    set_name("rack");
    add_name("bladesmith_weapons_rack");
    set_adj("heavy");
    add_adj("weapons");
    set_long("The heavy weapons rack stands against the wall, " +
        "and contains weapons available for sale by the " +
        "bladesmith. It appears they are locked in place somehow, " +
        "but the nature of the lock eludes you. You can probably " +
        "get a closer look at available weapons by 'appraise " +
        "<weapon> in rack'.\n");

    add_prop(CONT_I_HEIGHT, 100);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_VOLUME, 15700);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    add_prop(CONT_I_WEIGHT, 250000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(OBJ_M_NO_GET, "The " + short() + " is firmly placed " +
        "on the floor.\n");
    add_prop(CONT_M_NO_REM, VBFC_ME("check_remove"));

    set_alarm(0.0, 0.0, reset_container);
}

/*
 * Function name: enter_inv (MASK)
 * Description  : Called when an object enters our inventory.
 * Arguments    : ob - Object pointer to the object entering the
 *                     inventory.
 *                from - Object pointer to the object's previous
 *                       environment.
 * Returns      : n/a
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (objectp(from) || !ob->check_weapon())
    {
        tell_room(environment(), "The " + short() + " falls back " +
            "out of the " + short() + ".\n");
        ob->move(environment());
        return;
    }
}

/*
 * Function name: do_appraise
 * Description  : ALlows players to appraise weapons in the rack
 *                without actually picking them up.
 * Arguments    : str - Arguments to the 'appraise' command.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
public int
do_appraise(string str)
{
    int index;
    mixed *weparr;

    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TO, "%i 'in' 'rack'", weparr))
        return 0;

    if (!sizeof(weparr))
        return 0;

    index = (int)weparr[0];

    if (!index)
        weparr = weparr[1..];

    if (index > 0)
        weparr = weparr[1..index];

    if (index < 0)
        weparr = ({weparr[-index]});

    for (index = 0; index < sizeof(weparr); index++)
    {
        write("You stoop over the " + short() + " and examine " +
            LANG_ADDART(weparr[index]->short()) + " closely.\n");
        say(QCTNAME(TP) + " stoops over the " + short() + 
            " and examines a weapon closely.\n");
        weparr[index]->appraise_object(100);
    }

    return 1;
}
          
/*
 * Function name: init
 * Description  : Called when another object meets this one. Used
 *                here to add the rack appraise command.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    ::init();
    add_action(do_appraise, "appraise");
}
