inherit "/d/Gondor/minas/houses/citizens/suspect_home";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"


void
create_suspect_room()
{
    add_exit(MINAS_DIR + "houses/citizens/h5r2","north",0,0);
    add_exit(MINAS_DIR + "houses/citizens/h5r3","west",0,0);

    set_door_id("MT_h5_n3crc2");
    set_door_command(({"s","south"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(MINAS_DIR + "n3crc2");
    set_door_desc(BSN(
        "The wooden door is made from massive oaken planks expertly " +
        "fitted together. On it is written in Numenorean letters:") +
        "\t\tOrleg Belecthor\n");

    set_suspect(4);
    set_wealth(1);
    set_side("north");
    set_circle("Second Circle");

    set_short("main room");
    set_long(BSN(
        "This room is the entry and sitting room of this house. " +
        "There is a broad bench against the wall and a nice " +
        "portrait on the wall. A round table stands amid the " +
        "room. The door leading outside is to the south of you, " +
        "and two corridors lead off to the north and west."));
    add_item(({"bench","sitting bench"}), BSN(
        "This sitting bench is made of hard oak. It is covered " +
        "with a knit cloth to cushion the hard seat. It looks as " +
        "if it could seat almost four people."));
    add_item(({"cloth","knit cloth","cushion","bench cushion"}), BSN(
        "This cushion is made of carefully knit cloth. It is not " +
        "elegant, but it is attractive. The colours are mainly " +
        "blues and greys with a border of white. It fits perfectly " +
        "on the seat of the bench."));
    add_item(({"portrait","painting","nice portrait"}), BSN(
        "This is a portrait of an old man, sitting at an elegant " +
        "desk. It seems to be an ancestor of the house's owner, " +
        "for the painting is very old."));
    add_item(({"table","round table"}), BSN(
        "This round table stands exactly in the middle of the " +
        "room. Upon it you see a vase with a charming arrangement " +
        "of flowers."));
    add_item(({"vase","flower vase"}), BSN(
        "This vase is a rather inelegant piece of pottery, " +
        "painted clumsily. The figures upon the vase seem to be " +
        "soldiers, though you cannot tell for sure."));
    add_item(({"figures"}), BSN(
        "The figures seem to be running toward one another. Your " +
        "first supposition is that they are fighting, but they " +
        "may be athletes of some sort."));
    add_item(({"flowers","flower arrangement"}), BSN(
        "This is a beautiful arrangement of seasonal flowers. It " +
        "looks as though somebody has made a trip into the " +
        "countryside recently."));

    add_window("The window illuminates this room nicely.");
    add_walls("Upon the east wall is a portrait.");
    add_ceiling("The ceiling is blackened in one spot, seemingly by smoke.");
    add_floor("A table rests in the middle of the floor.");

    add_lamp();

}
