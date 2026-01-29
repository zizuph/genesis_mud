#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Tight Street");
    set_long("This is a small street, tightly packed between the two "+
      "large buildings to the west and east. The cobblestones underfoot "+
      "are moist and covered with grime. The road continues north towards "+
      "a small square and winds its way southward, into the heart of the "+
      "district.\n");
    add_item(({"small street","street","road"}),"A narrow road paved "+
      "with cobblestones.\n");
    add_item(({"large buildings","large building","buildings","building"}),
      "Made of hardwood planks and being extremely large in size, they "+
      "appear to be warehouses. A big sign hangs on the side of the building "+
      "to your west.\n");
    add_item(({"big sign","sign"}),"It has lots of perfectly legible "+
      "words on it.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavemeny is slick with "+
      "a thin film of moisture and grime.\n");
    add_item(({"grime"}),"Clumps of moss and lichen are growing on the "+
      "cobblestones of the street.\n");
    add_item(({"small square","square"}),"It lies just north from here.\n");
    add_exit(PORT + "s23", "north");
    /*
       add_exit(PORT + "s35", "west");
    */
    add_exit(PORT + "s49", "south");
}

init()
{
    ::init();
    AA(read_sign,read);
}

string
sign()
{
    return "\n"+
    "#&#&#&#&#&#&#&#&#&#&#&#&#&#&\n"+
    "&#       Skeever's        &#\n"+
    "#&    Tattoo  Parlour     #&\n"+
    "&# ~~~~~~~~~~~~~~~~~~~~~~ &#\n"+
    "%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"+
    "^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
}

