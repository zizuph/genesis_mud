/**  DARGAARD OUTSIDE ROOM **/

#include "/d/Ansalon/dargaard/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>

inherit DARGAARD_OUT;

void
reset_dargaard_room()
{

}

void
create_dargaard_room()
{
    set_short("In a dry well");
    set_long("You are standing on the buttom of a dried well. "+
             "It looks like the water here disappeared years ago, "+
             "and now only dry vegetation exists here. The walls have "+
             "been made out of thick square granite stones that has "+
             "been placed in a circular pattern. The buttom of the well "+
             "is filled with dry dirt where only moss and grass grows. "+
             "To the north, part of the granite wall has collapsed "+
             "revealing a small opening.\n"); 

    add_exit(DROOM + "court5","up",0);

    add_cmd_item(({"opening", "hole"}), ({"enter"}), "@@into_lowerDargaard");

    add_prop(ROOM_I_LIGHT,0);

    add_item(({"vegetation", "grass", "moss"}),
      "The vegetation is almost completely dry, nothing seems to survive down "+
      "here.\n");

    add_item(({"wall", "granite wall"}),
      "The granite wall looks very well crafted, the square stones "+
      "fit perfectly ontop of eachother.\n");

    add_item(({"opening", "hole"}),
      "The opening is shrouded in darkness, it is impossible to see anything "+
      "beyond it.\n");

    reset_dargaard_room();
}


string
into_lowerDargaard()
{
    write("You enter the small opening.\n");
    TP->move_living("into the small opening in the wall.",
      DROOM + "room9.c", 1, 0);
    return "";
}


