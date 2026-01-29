/* Castle_room08-The Dinning Room.
 * Coded by Marisol (09/09/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types

#include "../defs.h"

inherit CASTLE_OV;

void
create_castle_room()
{
    set_short("The Dinning Room");
    set_em_long("This is a sumptuous dinning room.  A long oblong "+
        "rosewood table is surrounded with one hundred carved chairs "+
        "made with the same wood. The rosy color of the wood "+
        "makes a beautiful constrast with the golden dinner plates. "+
        "Gold and silver silverware are paired with each plate.  "+
        "Crystal glasses for water and wine complete the plate setting. "+
        "On the walls, the ever present tapestries hang together "+
        "with paintings. A beautiful stained-glass window stands tall "+
        "on the far wall in the room. Soft colored light illuminate "+
        "the table.\n");
                                                                 
    add_item(({"table", "rosewood table"}),
        "This long oblong table is made with rare rosewood. The grain "+
        "of the wood is extremely fine and its pink color is quite "+
        "beautiful. Also the table has being treated with a kind of "+
        "lacquer so the table reflect the light on its surface.\n");

    add_item(({"chairs", "carved chairs"}),
        "Carved wooden chairs are set around the table to sit "+
        "ninety nine guest. A bigger and more ornate chair is reserved "+
        "to Lord Maldebroot at the top of the table under the "+
        "stained-glass window. The carvings are roses and ivy vines "+
        "interwined creating beautiful designs for the regular chairs. "+
        "The Lord's chair carving are even more complicate including "+
        "carving of birds and deers and a lion head at the top of his "+
        "chair's back.\n");

    add_item(({"plates", "golden plates"}),
        "The plates decorating the table are solid gold. They are not "+
        "for eating, just for show.\n");

    add_item(({"gold and silver silverware", "silverware"}),
        "The silverware is solid silver with lines of gold in the "+
        "form of different geometrical designs: circles, triangles, "+
        "spirals, squares and many others.\n");

    add_item(({"crystal glasses", "glasses"}),
        "These glasses are carved from rock crystal. They are one "+
        "solid piece of crystal. They are wide mouth ones for water "+
        "and flute-like ones for wine.\n");

    add_item(({"stained-glass window", "window"}),
        "A tall stained-glass window is set in the wall behind the "+
        "lord's carved chair. This window looks like the ones set "+
        "in the walls of the foyer. The design for this one though "+
        "is not a mythological beats but a natural animal, in this "+
        "case a majestic lion.\n");

    add_item(({"majestic lion", "lion"}),
        "A sand-colored majestic lion stand tall and fierce in the "+
        "stained-glass window. His claws are extended and he is "+
        "roaring dangerously. Its teeth are wicked and its tongue "+
        "is bright red. The lion looks imposing as a lord of Telbarin "+
        "should look too.\n");

    add_exit("castle1_03", "east");
}                
