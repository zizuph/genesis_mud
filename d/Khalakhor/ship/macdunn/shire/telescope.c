/* File:          /d/Khalakhor/ship/macdunn/shire/telescope.c
 * Creator:       Teth
 * Date:          December 4, 1997
 * Modifications:
 * Purpose:       This is a telescope that allows a person to view
 *                the two different piers from the ship.
 * Related Files: /d/Khalakhor/ship/macdunn/shire/
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>

object room1, room2;
string port1, port2;

public void
create_object()
{
    set_name("telescope");
    set_adj("metal");
    add_adj(({"dull","black","iron","well-oiled"}));
    set_short("metal telescope");
    set_pshort("metal telescopes");
    set_long("This metal telescope is a dull black colour. It is made " +
      "from iron, and hence is well-oiled, to prevent corrosion. " +
      "Considering that it is found in the crow's nest of the boat, " +
      "it can certainly see quite a distance. You can use it to " +
      "focus on the destinations that this boat travels to.\n");

    add_cmd_item(({"khalakhor","macdunn","port macdunn","on macdunn",
        "on khalakhor","on port macdunn"}),({"focus","view"}),
      "@@see_khalakhor");
    add_cmd_item(({"shire","on shire","grey havens","greyhavens",
        "on greyhavens","on grey havens"}),({"focus","view"}),
      "@@see_shire");
    add_cmd_item(({"sea","ocean","cuan siorruidh","cuan","on sea",
        "on water","water","on ocean","on cuan","on cuan siorruidh"}),
      ({"focus","view"}),"The ocean stretches out before you, vast " +
      "and seemingly infinite.\n");
    add_item(({"bolts","bolt"}),"The bolts firmly cinch the " +
      "telescope to the platform.\n");
    add_cmd_item(({"telescope","scope","metal telescope","black telescope",
        "dull telescope","iron telescope"}),({"break","smash","destroy"}),
      "You try to break the telescope, but find the iron resistant " +
      "to your attempt at vandalism.\n");

    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5500);
    add_prop(OBJ_I_VALUE, 5345);

    add_prop(OBJ_M_NO_GET, "The telescope is bolted firmly to the " +
      "platform.\n");
}

public string
see_khalakhor()
{
    room1 = find_object("/d/Khalakhor/ship/macdunn/pier12");
    port1 = (capitalize(COMPOSITE_LIVE(all_inventory(room1)))) + ".\n";
    if (!sizeof(all_inventory(room1)))
    {
        port1 = "";
    }
    return (room1->query_long() + port1);
}

public string
see_shire()
{
    room2 = find_object("/d/Shire/common/greyhaven/pier7");
    port2 = (capitalize(COMPOSITE_LIVE(all_inventory(room2)))) + ".\n";
    if (!sizeof(all_inventory(room2)))
    {
        port2 = "";
    }
    return (room2->query_long() + port2);
}
