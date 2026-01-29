/*
 * The House of Tika Waylan
 *
 * By Rastlin
 * Add_items and descrip changes by Teth
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit  SOLINROOM;

object gDoor;

public void
create_solace_room()
{
    seteuid(getuid());

    set_short("A barmaid's house");
    set_long("@@my_desc@@");

    add_item(({"walls","wall","floor"}),"Typical for a house like " +
             "this.\n");
    add_item("painting", "This painting is of some illusionist " +
             "performing sleight of hand tricks. A small brass " +
             "engraving is attached to the frame.\n");

    add_item("frame", "Simple and unassuming, it makes the viewer " +
             "focus on the painting.\n");

    add_item(({"engraving", "brass engraving"}), "The engraving reads: " +
             "'For my lovely daughter, Tika, on her 10th birthday. " +
             "Love, your father'.\n");

    add_item("kitchen", "The kitchen is mostly bare. You suspect that " +
             "that the owner of this home works in some sort of food " +
             "establishment.\n");

    add_item(({"wood stove", "stove"}), "The wood stove is practical " +
             "and utilitarian, giving off as much heat as is needed in " +
             "the winter to warm this house.\n");

    add_item("bed", "Nothing fancy here, just a simple one-person bed. " +
             "The pillows and sheets seem freshly washed however.\n");

    add_item(({"pillow", "pillows"}), "Unadorned and monotone, they are " +
             "used to rest one's head.\n");

    add_item(({"sheet", "sheets"}), "One colour and no embroidery make " +
             "these average and simple bed linens.\n");

    add_item("ceiling", "The ceiling is quite low, perhaps two metres " +
             "high. Anyone taller than that would have to stoop to " +
             "move about this room.\n");

    add_item("dresser", "A simple wooden dresser, it looks like it has " +
             "well-used through the years. You note the many scratches " +
             "and bumps on the drawers caused by daily use.\n");

    add_item(({"drawer", "drawers"}), "The drawers are filled with " +
             "commoner's garments, and have little value to you.\n");

    add_item("rug", "The rug is the only bright spot in an otherwise " +
             "drab home. It is coloured a bright green, imbuing the " +
             "room with a hint of vigour.\n");

    gDoor = clone_object(OBJ + "d_tika");
    gDoor->move(TO);
}

public string
my_desc()
{
    string str;

    str = "This small and sparse abode appears to belong to someone " +
	  "who spends very little time here. Nestled in the east wall " +
	  "is a";

    if (gDoor->query_open())
        str += "n open";
    else
        str += " closed";

    str += " green door. The rest of the house is sparingly furnished, " +
           "containing a kitchen with a wood stove, a bed and dresser, " +
           "and an unimpressive rug. A small painting is hanging on " +
            "the north wall. The ceiling here is quite low.\n";

    return str;
}

