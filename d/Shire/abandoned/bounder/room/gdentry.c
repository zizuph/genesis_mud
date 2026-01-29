/* 
 * This is gdentry.c, entrance to the Green Dragon Inn.
 * Jaypeg Brandybuck of the Shire, Oct 1997
 */

inherit "/std/room";
#include "/d/Shire/defs.h"
#include "/d/Shire/bounders/guild.h"


void create_room()
{

    add_prop(ROOM_I_INSIDE,1);
    set_short("A dim, musty, entrance parlour");
    set_long("The musty smell of beer and cedar are strong "+
      "here, in contrast to the fresh air outside. The rumble and "+
      "rattle of street noises are replaced with the low mumur of "+
      "voices split with the occasional outburst of laughter. An "+
      "odd-shaped door gives you access to the south, its shape "+
      "apparently to allow easy access to both the Shire and the "+
      "big folk into this most famous of watering holes.\nAlong "+
      "the west wall there are hooks at two different heights, "+
      "and a hat stand with a similar spacing of pegs.\n" );

    add_item(({"door","odd_shaped door","round door"}), "Opening "+
      "south out onto the busy Bywater road is an odd-shaped "+
      "door, seemingly originally a round door of about four "+
      "feet in height, but now with a three foot high extension "+
      "added to the top to allow easy access to the occasional "+
      "big folk that patronise this famous Inn.\n");
    add_item(({"stand","hat stand","pegs"}), "A rosewood hat stand "+
      "is perched in the corner, carved into an elegant yet "+
      "functional piece of furniture, with pegs ranging in height "+
      "so that all may find a place to hang their hat. There are "+
      "currently several hats hanging, most near the bottom, "+
      "proving that most of the customers here are still locals.\n");
    add_item(({"hooks","hook","coat hooks"}), "Several hooks of "+
      "two rows in height hang from the east wall.  From the "+
      "dozen or so coats on the lower row, you guess the majority "+
      "of the patronage is still hobbit.\n");
    add_item(({"street","bywater road","road"}), "Through the "+
      "door to the outside is the bustling Bywater road, with "+
      "all sorts of folk travelling to and from Hobbiton and "+
      "Bywater, and some beyond to Overhill or deep into the "+
      "West Farthing.\n");

    add_exit( HOB_DIR + "bywater1", "out", 0);
    add_exit( BOUND_ROOM_DIR + "gdhall1", "east", 0 );

}
