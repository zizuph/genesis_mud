#include "defs.h"
inherit OUTPOST_INSIDE_ROOM;

void
create_outpost_inside_room()
{
    set_short("In the officer's barracks.");
    set_em_long("Significantly fewer cots decorate this room than the barracks from " +
        "whence you entered. Those higher quality furnishings due to ranking officers " +
        "abound, including a finely worked table and elegant footlockers. The cots " +
        "look to be more comfortable and of a much higher quality than those for the " +
        "regular soldiers. Dim light from the wall lamps dances across the wooden " +
        "walls. From here you can pass through the arch in the southern wall, back " +
        "to the general barracks.\n"); 


    add_item( ({"cots", "cot", "rows", "rows of cots"}),
        "These cots are much larger than the others you have seen. Upon each wooden " +
        "frame, a thick mattress covered by a warm blanket looks very inviting. An " +
        "elegant footlocker is positioned at the foot of each cot.\n");

    add_item( ({"footlocker", "footlockers", "elegant footlocker", "elegant footlockers"}),
        "At the foot of each cot, an elegant wooden footlocker holds the personal items " +
        "for each officer. Carved scenes depicting landscapes and animals are worked " +
        "into the lockers.\n");

    add_item( ({"table", "finely worked table", "worked table", "fine table"}),
        "A richly decorated table is pushed against the north wall. This fine piece of " +
        "furniture looks out of place considering the rough building in which it " +
        "stands. Various books and papers lie scattered across its surface.\n");

    add_item( ({"books", "book", "paper", "papers"}),
        "Mostly religeous and theological works, it is obvious that the officers who " +
        "live in this room are highly educated. The scattered papers contain " +
        "orders and decrees from the captain of the outpost.\n");

    add_item( ({"walls", "wooden walls", "rough walls", "rough wooden walls"}),
        "The walls of the room are made from the same wood as the rest of " +
        "the building. Large logs have been placed horrizontally, one on top " +
        "of the other to form a good barrier from the weather.\n"); 
   
    add_item( ({"lamp", "lamps", "iron lamps", "iron lamp", "wall lamp", 
                "wall lamps", "iron wall lamp", "iron wall lamps"}),
        "Iron wall lamps are attached to the walls. Fueled by oil, they cast " +
        "dim light throughout the large room.\n");

    add_exit("lbrcks.c","south");
}
