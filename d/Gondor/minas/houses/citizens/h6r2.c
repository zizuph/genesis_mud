#pragma strict_types

inherit "/d/Gondor/minas/houses/citizens/house.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("living room");
    set_long(BSN("This large room is well furnished. A comfortable-looking " +
        "chair sits in one corner, a cushioned bench sits along the wall, " +
        "and a table and its chairs stand in the center of the room. " +
        "There is a small tapestry on the wall opposite the bench and " +
        "a bookshelf on another wall."));
    add_item(({"comfortable chair","large chair"}), BSN(
        "This large, comfortable-looking chair is padded with soft " +
        "cushions. It looks well used and seems to be the favourite " +
        "of this family's chairs."));
    add_item(({"chair","chairs"}), BSN(
        "Which chair? The large, comfortable chair, or the small wooden " +
        "chairs around the table?"));
    add_item(({"bench","cushioned bench"}), BSN(
        "This bench is made of a wooden frame covered by thin cloth " +
        "cushions. It looks as if it could seat three people easily."));
    add_item(({"cushion","cushions"}), BSN(
        "The cushions on the large chair are thick and plush, while the " +
        "ones on the bench are thin and worn."));
    add_item(({"table","dining table"}), BSN(
        "This large wooden table is the dining table of this house. Here " +
        "the family gathers and partakes of its meals. It is covered with " +
        "a fine table cloth."));
    add_item(({"table cloth","tablecloth"}), BSN(
        "This fine white cloth serves to cover the table and prevent " +
        "spills from damaging the wooden surface of the table."));
    add_item(({"wooden chair","small chair"}), BSN(
        "These six small chairs surround the dining table, providing " +
        "seats for the family when they eat. They are well crafted and " +
        "varnished."));
    add_item(({"tapestry","small tapestry"}), BSN(
        "This tapestry depicts the Leap of Beren at the moment of " +
        "success. Beren is portrayed in mid-flight, having just leapt " +
        "out of the elf-Lord Celegorm's path, his hand grabbing " +
        "Curufin's neck and pulling the ill-willed Son of Feanor " +
        "from his steed as he tried to capture Luthien Tinuviel, " +
        "the fairest of the Children of Iluvatar."));
    add_item(({"bookshelf","bookcase"}), BSN(
        "This bookshelf holds numerous books, old and new. It is " +
        "crafted of some white wood unknown to you and engraved " +
        "with designs of ivy."));
    add_item(({"books"}), BSN(
        "These books are mainly lore-books. It seems that the master of " +
        "this house is a scholar. The books include herbal texts, " +
        "treatises on law, and, interestingly, a book on poisons and " +
        "their cures."));
    add_cmd_item( ({ "books", "book", "book on poisons", "texts", 
		     "herbal texts","text", "herbal text", "treatise", }),
		 "read", "You leaf through the books quickly, and " +
		 "put them back onto the bookshelf.\n");

    add_prop(ROOM_I_INSIDE, 1);

    set_wealth(1);
    set_side("north");
    set_circle("Third Circle");

    add_window("The window is in the north wall.");
    add_walls("A tapestry adorns the west wall and a bookshelf " +
        "rests against the east wall.");
    add_ceiling("You notice that the bookshelf reaches all " +
        "the way to the ceiling.");
    add_floor("The floor is bare, but well worn and comfortable.");

    add_lamp();

    add_exit(MINAS_DIR + "houses/citizens/h6r1sn1crc3","south",0,0);
}
