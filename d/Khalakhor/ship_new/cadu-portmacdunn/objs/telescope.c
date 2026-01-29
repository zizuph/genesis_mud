/* File:          /d/Khalakhor/ship/macdunn/shire/telescope.c
 * Creator:       Teth
 * Date:          December 4, 1997
 * Modifications:
 * Purpose:       This is a telescope that allows a person to view
 *                the two different piers from the ship.
 * Related Files: /d/Khalakhor/ship/macdunn/shire/
 * Comments:
 * Should be globally coded later - Tapakah, 05/2009
 * Twelve years after ...
 * Not yet, but at least a cleanup - Tapakah, 07/2021
 */

#pragma strict_types

#include <stdproperties.h>

inherit "/std/object";

string
telescope_broken ()
{
  return "The glass in the telescope is broken right now. "+
    "You can't see anything.\n";
}

void
create_object ()
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
  
  add_cmd_item(({"forward", "fore", "ahead", "ahoy"}),
               ({"focus","view"}), telescope_broken);

  add_cmd_item(({"backwards", "back", "aback" }),
               ({"focus","view"}), telescope_broken);
  add_cmd_item(({"sea","ocean","cuan siorruidh","cuan","on sea",
                 "on water","water","on ocean","on cuan","on cuan siorruidh"}),
               ({"focus","view"}), telescope_broken);
  add_item(({"bolts","bolt"}),"The bolts firmly clinch the " +
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
