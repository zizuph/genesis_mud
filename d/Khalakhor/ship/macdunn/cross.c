/* File:          /d/Khalakhor/ship/macdunn/cross.c
 * Creator:       Teth
 * Date:          December 8, 1997
 * Modifications:
 * Purpose:       This celtic cross welcomes people to Port Macdunn.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/pier1.c
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
#include "local.h"
#include <ss_types.h>
#include <stdproperties.h>

public void
create_object()
{
    set_name("cross");
    add_name("marker");
    set_adj("celtic");
    add_adj(({"stone","grey","braided","knotwork","granite"}));
    set_short("celtic cross");
    set_pshort("celtic crosses");
    set_long("This grey marker is a celtic cross. Made of highland " +
      "granite, the marker stands roughly 2 meters in height. " +
      "Its basic form is of two perpendicular rectangles, the " +
      "shorter one horizontal and intersecting at two-thirds of " +
      "the height of the other. Arcs of stone connect the " +
      "adjoining edges of the rectangles, forming a cross that " +
      "appears to have a circle centred over the intersection " +
      "of the two rectangular sections. Intricate designs " +
      "are carved into the surface of the cross.\n");
    add_item(({"granite","highland granite"}),"The rock is a " +
      "light grey, the colour of ash. It has a non-uniform " +
      "texture, but in most areas, it has been polished " +
      "smooth.\n");
    add_item(({"rectangles","perpendicular rectangles"}),"They form " +
      "the main bulk of the cross.\n");
    add_item(({"arcs","arcs of stone","arc-shaped pieces of stone",
        "pieces of stone"}),"They form an image of a circle " +
      "surrounding the intersection of the rectangular portions.\n");
    add_item(({"carvings","designs","intricate designs"}),"The " +
      "intricate carvings cover the face of the cross. " +
      "They consist of detailed knotwork and braidings, " +
      "arranged in a pattern where the size of the knots " +
      "increases toward the extremities. Runes decorate the " +
      "arc-shaped pieces of stone.\n");
    add_item(({"braidings","knotwork","detailed knotwork","pattern"}),
      "Obviously the work of a master carver, the detail of the " +
      "carvings would require months to complete. The shapes " +
      "seem to be a labour of love.\n");    
    add_item(({"runes","writings"}),"@@read_runes");
    add_cmd_item(({"runes","writings"}),"read","@@read_runes");
    add_cmd_item(({"marker","cross","celtic cross","celtic marker",
        "stone marker","grey marker","stone cross","grey cross"}),
      ({"break","destroy","smash","crumble"}),"The cross is " +
      "resistant to your every effort.\n");
    add_cmd_item(({"marker","cross","celtic cross","celtic marker",
        "stone marker","grey marker","stone cross","grey cross"}),
      ({"push","pull","move","tumble","slide"}),"As much as you " +
      "try to move the celtic cross, it remains standing in its " +
      "current location.\n");

    add_prop(OBJ_I_VALUE, 2250);
    add_prop(OBJ_I_WEIGHT, 311288);
    add_prop(OBJ_I_VOLUME, 200658);
    add_prop(OBJ_M_NO_GET, "The stone marker is too heavy for you " +
      "to lift.\n");

}

public string
read_runes()
{
    if (this_player()->query_skill(SS_LANGUAGE) <= 75)
    {
        write("You are unable to decipher the secrets of the " +
          "runes.\n");
        return "";
    }

    write("You decipher the runes:\n\n"+
      "In honour of the pioneers of Khalakhor,\n"+
      "Lord Khail, Sir Zima and Sir Teth.\n\n");
    return "";
}

