#pragma strict_types

#include "defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    ::create_temple_room();

    set_short("Standard guardroom");
    set_long("Room with basic items for guardrooms.\n");

    add_item(({"rack", "racks", "weapon rack", "weapon racks"}),
        "Several large weapon racks stand along the walls. Each containing " +
        "well-maintained weapons for the guards. They are made of heavy " +
        "oak wood with carvings along the sides.\n");

    add_cmd_item(({"rack", "racks", "weapon rack", "weapon racks"}),
        ({"push", "pull", "move"}), "You try to move the weapon racks but " +
        "they will not budge. They are clearly securely bolted to the " +
        "floor.\n");

    add_cmd_item(({"rack", "racks", "weapon rack", "weapon racks"}),
        ({"touch", "feel"}), "The wood of the weapon racks feels smooth.\n");

    add_item(({"carving", "carvings"}),
        "The carvings up the sides of the racks are made on the pattern of " +
        "dragons in flight and a the top of each rack is a large dragon " +
        "heads baring its long sharp teeth.\n");

    add_cmd_item(({"carving", "carvings", "pattern"}),
        ({"trace", "touch", "feel", "follow"}), "You trace your fingers up " +
        "along the pattern of tiny dragons flying in a row up along the " +
        "sides of the rack. The wood is smooth and the carvings are " +
        "extremely detailed.\n");

    add_item(({"dragons"}),
        "You see tiny dragons up along the sides of the racks and a large " +
        "dragon head at the top of each rack.\n");

    add_item(({"tiny dragons"}),
        "The tiny dragons are carved with such detail that the texture of " +
        "their leathery wings is evident. They fly in perfect formation up " +
        "along the sides of the racks.\n");

    add_item(({"large dragon", "dragon head", "large dragon head"}),
        "This is a large carved dragon head. Its eyes seem to watch you " +
        "from its high position on top of the rack and its mouth is " +
        "slightly open revealing a row of sharp wicked teeth.\n");

    add_item(({"table", "round table"}),
        "This is a sturdy table made of hard wood. It has no ornamentations " +
        "and its surface is covered with scratches. It is large enough for " +
        "six people to sit around.\n");

    add_item(({"scratches"}),
        "The scratches on the table are probably made from harder objects " +
        "being pulled across its surface. Perhaps coins, weapons, or mugs.\n");

    add_item(({"chair", "chairs"}),
        "The chairs are made of hard wood and are of a sturdy design made " +
        "to last through the rough handling of weary guards on duty.\n");

    add_cmd_item(({"chair", "chairs", "table", "round table"}),
        ({"move", "push"}), "You move the furniture around a little but " +
        "finally decide to put it all back in place.\n");
}
