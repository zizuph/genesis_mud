/**********************************************************************
 * - guild_room.c                                                   - *
 * - base room gor Thanar guild                                     - *
 * - Created by Damaris@Genesis 3/2004                              - *
 **********************************************************************/


#include "../guild.h"
#include <macros.h> /* For the Q macros in messages.. */
#include <stdproperties.h> /* for room props */


inherit "/d/Raumdor/std/room";

void
create_guild_room()
{
}

nomask void
create_room()
{
    /* To set the short desc. in the rooms. */
    set_short("Guild room of Thanar");
    /* To set the long desc. in room. */
    set_long("    Guild room of Thanar.\n");

    /* To add items to be examined in rooms. */

    add_item(({"light", "light source"}),
      "A dark light illuminates this hall. It seems to be glowing softly from "+
      "the walls and ceiling and even from the marble floor.\n");
    add_item(({"wall", "walls"}),
      "The walls are made from a strange black marble with a spiral of "+
      "red and white intertwining in seamless patterns.\n");
    add_item(({"ceiling"}),
      "The ceiling is made from a strange black marble with a spiral of "+
      "red and white intertwining in seamless patterns.\n");
    add_item(({"floor", "flooring"}),
      "The floor is made from a strange black marble with a spiral of "+
      "red and white intertwining in seamless patterns.\n");
    add_item(({"marble"}),
      "The marble is uniquely mysterious, as it appears to radiate a "+
      "soft glow with the intertwining patterns of red and white.\n");
    add_item(({"pattern", "patterns"}),
      "The patterns in the marble are seamless as the red and white "+
      "intertwining with each other in spirals, twists and curves.\n");
    add_item(({"thanar"}),
      "Perhaps if you'd like to know more about the Glorious Thanar you "+
      "might try to seek a library.\n");

    create_guild_room();

}
