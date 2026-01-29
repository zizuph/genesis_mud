/*
 * A normal house in Solace
 *
 * By Rastlin
 * Descrip and add_items changed by Teth
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit  SOLINROOM;

object gDoor;

public void
create_solace_room()
{
    seteuid(getuid());

    set_short("A lumberjack's house");
    set_long("@@my_desc@@");

    add_item(({"clothing", "plaid", "plaid clothing"}), "Tattered and " +
             "well-worn, none of this appeals to you. It could be the " +
             "smell of lumberjack sweat that is the real turn-off for " +
             "you, actually.\n");

    add_item("bed", "Bowed in the center, this bed looks like it has " +
             "supported quite a weight in recent years. The sheets look " +
             "unwashed and the pillows have feathers poking out of " +
             "them.\n");

    add_item(({"pillow", "pillows"}), "A closer look at the pillows " +
             "reveals the fact that the lumberjack should pay a bit " +
             "more attention to personal hygiene.\n");

    add_item(({"sheets", "sheet"}), "Dirty and sweaty-smelling, these " +
             "sheets are the bed linens of the common working person.\n");

    add_item("kitchen", "Little impresses you in this kitchen. It is " +
             "simply a kitchen of utility, nothing fancy, and entirely " +
             "practical.\n");

    add_item(({"wood stove", "stove"}), "This robust stove demands your " +
             "attention as you inspect it. It is clearly the stove of " +
             "one whose life has been devoted to wood, and it has a " +
             "proud quality about it, as if it was the 'baby' of the " +
             "home's owner. Certainly it is well-tended.\n");

    add_item("rug", "The fading rug is dyed purple and grey. It is " +
             "covered with sawdust and wood chips.\n");

    add_item(({"wood chips", "chips", "sawdust"}), "The sawdust and wood " +
             "chips are the most obvious clue that this house belongs " +
             "to a feller of trees. They come in shades of brown.\n");

    add_item("dresser", "A practical-looking piece of furniture, the " +
             "design is simple and utilitarian. Several drawers are " +
             "slightly open.\n");

    add_item(({"drawer", "drawers"}), "Examining the drawers closely, " +
             "you find nothing of interest for one such as you. Perhaps " +
             "if you took up logging, you'd appreciate sweat-stained " +
             "clothing more.\n");

    add_item("rack", "Carved somewhat haphazardly out of Crystalmir " +
             "pine, this rack stands empty. It does however have nicks " +
             "and scratches all over its surface, due to the placement " +
             "and removal of axes.\n");

    gDoor = clone_object(OBJ + "d_house5");
    gDoor->move(TO);
}

public string
my_desc()
{
    string str;

    str = "This house clearly belongs to a lumberjack. Plaid clothing " +
	  "lies everywhere! Set into the north wall, a green door rests ";

    if (gDoor->query_open())
        str += "open";
    else
        str += "closed";

    str += ". Facing the door from the other side of the room lies the " +
           "bed and dresser. In the east portion of the room, the kitchen " +
           "presents itself for all to see, showing off a robust-looking " +
           "wood stove. Huddled against the west wall is a rack that " +
           "appears to hold woodcutters' axes. The floor is covered with " +
           "a well-worn rug.\n";

    return str;
}

















