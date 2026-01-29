/*
 *  The hallway above the Sleeping Stallion
 *  Added for the expansion of the Dunlending area
 *  /d/Gondor/rohan/farm/farm/camp/
 *  Raymundo, Spring 2020   
 */

inherit "/d/Gondor/common/room";
#include "/d/Gondor/common/lib/gs_include.c"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

void
create_room()
{
  set_short("Hallway above the Sleeping Stallion");
  set_long(BS("You are in a hallway above the Sleeping Stallion inn. "
    + "The walls have been painted and stenciled in an equestrian "
    + "theme, while the floor itself is just simple hard wood. "
    + "You see rooms to the east and west, while a staircase will lead "
    + "downstairs to the inn itself.\n"));
    
add_item( ({"wall", "walls"}), "The walls have been plastered and "
    + "painted with a white base coat. Stenciled horses create an "
    + "equestrian theme here, paying homage to the Riders of Rohan.\n");
add_item("floor", "The floor is made of hard wood. It has a worn "
    + "pattern down the middle.\n");
add_item( ({"pattern", "worn pattern", "worn", "tracks", "prints", "scuffs", "marks", "scuff marks", "marks"}),
    "The floor has some scuff marks and a worn pattern down the middle "
    + "of it, where  boots have scratched and worn the floor over the "
    + "decades.\n");
add_item("ceiling", "The ceiling looks to be made of some sort of copper "
    + "ceiling tiles.\n");
add_item( ({"tile", "ceiling tile", "copper", "copper tile", "copper ceiling tile"}),
    "The ceiling tiles look to be about two hands square. Each one is "
    + "decorative, with repeating geometric patterns.\n");
add_item( ({"pattern", "patterns", "geometric patterns", "repeating patterns"}),
    "The patterns are a series of triangles and lines that seem to repeat "
    + "forever. It's quite pleasing to look at.\n");
add_item( ({"theme", "equestrian", "horse", "stencil", "stencils", "equestrian theme"}),
    "@@exa_theme@@");

  add_exit(EDORAS_DIR + "stallion", "stairs", 0, 2);
  add_exit(EDORAS_DIR + "stallion", "down", 0,0,1);
  add_exit(EDORAS_DIR + "hotelr", "west");
  add_exit(EDORAS_DIR + "hotelr2", "east");

  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
}

init()
{
  ::init();

    
}

//Gives the description of the stencils on the wall.
string
exa_theme()
{
    string *stencil;
    stencil = ({"You see a stencil depicting a stallion running through the "
        + "open plains of grass.\n",
        "This stencil depicts a mounted warrior, with sword and shield, "
        + "charging invading orcs.\n",
        "The stencil depicts colts frolicking in tall grass.\n",
    "This stencil shows weary travelers riding horses toward Edoras.\n"});
    return ONE_OF_LIST(stencil);
}