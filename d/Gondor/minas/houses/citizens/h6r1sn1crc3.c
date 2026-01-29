inherit "/d/Gondor/minas/houses/citizens/suspect_home";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_suspect_room()
{
    add_exit(MINAS_DIR + "houses/citizens/h6r2","north",0,0);
    add_exit(MINAS_DIR + "houses/citizens/h6r3","west",0,0);

    set_door_id("MT_h6_n1crc3");
    set_door_command(({"s","south"}));
    set_door_name(({"door","wooden door"}));
    set_other_room(MINAS_DIR + "n1crc3");
    set_door_desc(BSN("This wooden door is made of a fine, hard "
      + "wood and is well varnished. It is old-fashioned but "
      + "bears little of the marks of age."));

    set_suspect(5);
    set_wealth(1);
    set_side("north");
    set_circle("Third Circle");

    set_short("entry room");
    set_long(BSN(
        "This room serves as both the entry room and the kitchen for " +
        "this modest house. It is apparently a middle class residence, " +
        "as evinced by the artwork on the walls and the carpet in the " +
        "room. The kitchen area is in a single corner of the room, " +
        "and the smell of cooked food lingers in the room."));
    add_item(({"kitchen","kitchen area","area"}), BSN(
        "This area holds a small stove, which also conveniently warms " +
        "the room, and a counter area for preparing the food."));
    add_item(({"stove","small stove"}), BSN(
        "This stove, though small, is well made and probably quite " +
        "expensive. It is crafted from steel with great skill and " +
        "produces a great amount of heat for its small size."));
    add_item(({"counter","counter area"}), BSN(
        "This flat surface bears the stains of copious meals prepared " +
        "upon it. It is made of hard, dense wood and is barely scored " +
        "by the knives which have been worked over it."));
    add_item(({"artwork","paintings","portraits"}), BSN(
        "The artwork consists of portraits of noble looking Dunedain, " +
        "presumably deceased members of this very family. The " +
        "paintings all show distinguished men who bear the characteristic " +
        "dark hair and grey eyes of the Dunedain of old."));
    add_item(({"carpet","rug"}), BSN(
        "This carpet is quite old and would seem to be a family " +
        "heirloom. The design is intricately detailed in dark reds, " +
        "blues and blacks. It seems to be quite valuable."));

    add_window("The window is in the west wall, near the door.");
    add_walls("There are portraits hanging on the walls.");
    add_ceiling("The ceiling is rather high.");
    add_floor("There is an old carpet on the floor.");

    add_lamp();
}
