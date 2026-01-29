/* File:          /d/Khalakhor/ship/macdunn/ansalon/cabin.c
 * Creator:       Teth
 * Date:          April 12, 1997
 * Modifications: /Teth April 18, 1997. Added chest.
 *              : Teth - Feb 10 2002
 *                Switched to new terrain types.
 * Purpose:       The cabin is a room on the Khalakhor to
 *                Ansalon ship. It contains a chest,
 *                /d/Khalakhor/ship/macdunn/chest.c
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ansalon/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/cabin";

#include <stdproperties.h>
#include "local.h"
#include "/d/Khalakhor/sys/terrain.h"

object chest;

public void
create_cabin()
{
    set_short("the cabin of the Bonnie Lass");
    set_long("   This is the cabin of the Bonnie Lass. The small den is " +
      "lit with an oil lantern, shadowing the wooden walls with " +
      "dark images. The cabin is spartan in its decoration, only " +
      "having a cot, a chair, and a table as large furniture. " +
      "An archway leads back out to the deck.\n");

    add_item(({"cabin","den","small den","spartan cabin"}),
      "@@query_long");
    add_item(({"lantern","oil lantern"}),"The oil lantern lights " +
      "the room with a diffuse glow. It is made of blackened iron, " +
      "with a glass bulb that contains the oil.\n");
    add_cmd_item(({"lantern","oil lantern"}),({"get","take"}),
      "The lantern is affixed to the ceiling, and you are not able " +
      "to take it.\n");
    add_item(({"iron","blackened iron"}),"The iron of the lantern " +
      "is expertly forged.\n");
    add_item(({"bulb","glass bulb","glass"}),"The glass bulb of the " +
      "lantern contains the oil used to keep the light of the " +
      "lantern burning.\n");
    add_item(({"diffuse glow","glow","light","diffuse light"}),"The " +
      "light of the lantern creates many shadows on the walls.\n");
    add_item("oil","The oil of the lantern is transparent and " +
      "viscuous.\n");
    add_item("ceiling","The ceiling is constructed of wooden beams.\n");
    add_item(({"beams","wooden beams"}),"The hefty beams of wood are " +
      "constructed of oak.\n");
    add_item("oak","The oak tree is a typical wood used for ship " +
      "construction.\n");
    add_item("floor","The floor is made of sturdy planks.\n");
    add_item(({"planks","sturdy planks"}),"The sturdy planks appear to " +
      "be constructed of oak.\n");
    add_item(({"walls","wooden walls","wall"}),"Each wall is made of " +
      "oak.\n");
    add_item(({"images","dark images","shadows"}),"The shadows " +
      "dance along the walls as the oil lamp flickers, coinciding " +
      "with the movement of the ship.\n");
    add_item("cot","The cot is used by the captain of the ship.\n");
    add_cmd_item(({"on cot","down on cot","cot"}),({"lie","rest"}),
      "You rest on the cot for a short while, then stand back up.\n");
    add_item("chair","The chair is untucked from beneath the table.\n");
    add_cmd_item(({"on chair","chair"}),"sit","You sit on the chair for a " +
      "few moments, but find it uncomfortable, so you stand again.\n");
    add_item("table","The table is covered with navigational charts.\n");
    add_item(({"charts","navigational charts"}),"They appear to only " +
      "be good for the Ansalon to Khalakhor ship route.\n");
    add_cmd_item(({"charts","navigational charts"}),({"get","take"}),
      "Taking the charts would only make sense if you were the " +
      "captain of a ship running between Khalakhor and Ansalon!\n");
    add_item("chart","Each chart appears similar. Perhaps looking " +
      "at all the charts may give you a better idea.\n");
    add_item(({"furniture","large furniture"}),"A cot, a chair and a " +
      "table are the only large pieces of furniture in the cabin.\n");
    add_item("archway","The archway surrounds the entrance to or exit " +
      "from the cabin.\n");
    add_item("deck","The main deck of the ship lies outside the cabin.\n");

    add_exit(THIS_DIR + "deck", "out", 0);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    set_terrain(TERRAIN_INSHIP);

    chest = clone_object(OBJ_DIR + "chest");
    chest->move(this_object(), 1);

    set_cabin_sound("@@sounds");
}

public string
sounds()
{
    if (random(2))
        return "The ship rolls to the port side for a moment, then " +
        "corrects itself, moving slightly starboard.\n";

    return "The ship rocks to and fro upon the waves.\n";
}
