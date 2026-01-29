/* File:          /d/Khalakhor/area/cobhan/wep/axe.c
 * Creator:       Teth
 * Date:          January 5, 1998
 * Modifications:
 * Purpose:       This axe is wielded by the lumberjacks, who use it
 *                to cut down wood, oddly enough.
 * Related Files: /d/Khalakhor/area/cobhan/
 * Comments:      Evaluates axe skill.
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/std/weapon";

#include "../local.h"
#include "/d/Khalakhor/sys/properties.h"
#include <ss_types.h>
#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>

public void
create_khalakhor_weapon()
{
    set_name("axe");
    set_pname("axes");
    add_name(({"axe","weapon","hewer","tuagh"}));
    add_pname(({"axes","weapons","hewers","tuaghan"}));
    set_adj("iron");
    add_adj(({"metal","black","forged","lumberjack's","lumberjacks",
        "lumber jack's","lumber jacks"}));
    set_short("black iron axe");
    set_pshort("black iron axes");
    set_long("@@skill_long");
    add_item(({"blades","opposing blades","metal body"}),
        "The blades are made of forged iron, heavy and deadly.\n");
    add_item(({"forged iron blades","iron blades"}),"The forged iron " +
        "blades are heavy and deadly.\n");
    add_item(({"iron","black iron","forged black iron","matte black iron",
        "matte iron","forged iron"}),"@@iron_desc");
    add_item(({"hefty shaft of oak","shaft of oak","heavy shaft",
        "oaken shaft","heavy oaken shaft","oak shaft","heavy oak shaft"}),
        "The heavy oak shaft is sturdy and thick, to support the " +
        "weight of the forged iron blades.\n");
    set_default_weapon(25, 37, W_AXE, W_SLASH, W_BOTH);
    set_likely_dull(2);
    set_likely_break(5);
    add_prop(OBJ_I_VOLUME, 6000 + (random(400)));
    add_prop(OBJ_I_WEIGHT, 4400 + (random(350)));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(25,37) + (random(100)));

    add_prop(OBJ_AM_LORE_INFO, ({ "You recognize the iron of this axe " +
        "as special to Khalakhor.\n" , 5, "The iron is favoured by dwarven " +
        "smiths because of its matte black colour.\n", 15, "It is also " +
        "reputed to have a high ability to retain sharp edges.\n", 40 }));
}


public string
skill_long()
{
    string axe;
    int axeskill = this_player()->query_skill(SS_WEP_AXE);


    switch(axeskill)
    {
    case 0..10:
    axe = "";
    break;

    case 11..35:
    axe = " You are able to recogize that this axe is of premium " +
          "quality.";
    break;

    case 36..100:
    axe = " You are able to realize that even though this axe is " +
          "difficult to maneuver, it is devastating when it lands a blow.";
    break;

    default:
    axe = "";
    break;
    }

    return "This black iron axe consists of two opposing blades which " +
           "are molded from one piece of metal. The metal body of " +
           "the axe is wedged onto a hefty shaft of oak." +
           axe + "\n";
}

public string
iron_desc()
{
    int loreskill2 = this_player()->query_skill(SS_KHALAKHOR_LORE);

    switch(loreskill2)
    {
    case 0..10:
    return "The iron is black and heavy, of excellent quality.\n";
    break;

    case 11..35:
    return "The black iron is heavy, and a matte black colour. " +
           "You are unable to recall where such iron is found in " +
           "Khalakhor, however.\n";
    break;

    case 36..55:
    return "The black iron is special to the Meidh region of Khalakhor, " +
           "where it is famed for its appearance and ability to retain " +
           "an edge.\n";
    break;

    case 56..100:
    return "The black iron is special to the Meidh region of Khalakhor, " +
           "where it is famed for its appearance and ability to retain " +
           "an edge. The edge has the odd property of being serrated " +
           "when sharp, and thus quite dangerous in slashing movements.\n";
    break;

    default:
    return "";
    break;
    }
}
