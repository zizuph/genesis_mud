
/* 	Major Zone of Thalassia
        Mural Room

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

inherit "/d/Calia/std/water_room";

#include "defs.h"

void
create_water_room()
{
    set_short("Major Zone of Water");
    set_long("You are in a huge circular section of the city known as "+
        "the Major Zone. There are many gardens that you can "+
        "see here, each beautifully arranged. White marble columns rise "+
        "from the ground right up to the top of the walls. A few statues "+
        "surround a fountain placed right in the centre of the columns. "+
        "The walls here are coated in bronze, from floor to ceiling, "+
        "making this area shine very brightly in the light. On the "+
        "wall you notice a colourful mural.\n");

    add_item(({"statue","statues","few statues"}),"The statues are "+
        "expertly carved from white marble and decorated with gold, "+
        "silver, orichalcum, and gemstones. They depict sea-creatures "+
        "like a sea-elephant and a sea-lion swimming after each other "+
        "around the top of the fountain.\n");

    add_item("fountain","This fountain is as all others you have seen "+
        "in this city, upside-down and spouting air instead of water. "+
        "There are statues around the top of this fountain.\n");

    add_item(({"flower","flowers","plant","plants"}),"There are "+
        "many beautiful and colourful plants and flowers here, "+
        "but you do not recognize any of them.\n");

    add_item(({"column","columns","marble column","marble columns",
        "white marble column","white marble columns"}),"These columns "+
        "are constructed from white marble. They are placed around "+
        "the mural, one on each side, and appear to have no functional "+
        "purpose other than decoration. They are plain cylindrical "+
        "columns approximately fifteen feet high and two feet wide at "+
        "the bottom tapering to one foot wide at the top.\n");

    add_item(({"mural","colourful mural"}),"The mural is a depiction "+
        "of the life and history of the Thalassians, the inhabitants "+
        "of this underwater city. This particular mural depicts "+
        "women underwater being transformed into beautiful creatures with "+
        "fishlike nether regions, and men being transformed into handsome "+
        "creatures with webbed fingers, long claws, scales on their torsos "+
        "and a fishlike tail where their legs once were. There appear to "+
        "be other murals to the northwest and southeast of here.\n");

    add_item(({"garden","gardens"}),"The gardens have many varieties of "+
        "plants that you do not recognize. They are very colourful "+
        "and plentiful.\n");

    add_swim_exit(THALM+"major33","northeast",0,1);
    add_swim_exit(THALM+"mural11","northwest",0,1);
    add_swim_exit(THALM+"mural13","southeast",0,1);

}
