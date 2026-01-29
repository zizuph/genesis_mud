/* Eil-Galaith Guild base_room
 * Created by Damaris 09/Y2K
 */

#include "../guild.h"
#include <macros.h> /* For the Q macros in messages.. */
#include <stdproperties.h> /* for room props */


inherit "/d/Khalakhor/std/room";

#include "/d/Khalakhor/sys/properties.h"

void
create_guild_room()
{
}

nomask void
create_khalakhor_room()
{
    /* To set the short desc. in the rooms. */
    set_short("Guild room of Eil-Galaith");
    /* To set the long desc. in room. */
    set_long("Guild room of Eil-Galaith.\n");

    /* To add items to be examined in rooms. */

    add_item(({"light", "light source"}),
      "The light that illuminates this hall seems to be glowing softly from "+
      "the walls and ceiling and even from the marble floor. It is most "+
      "mysterious but casts a warm inviting glow all around you.\n");

    add_item(({"wall", "walls"}),
      "The walls are made from a mysterious white marble with a spiral of "+
      "black intertwining in seamless patterns.\n");

    add_item(({"ceiling"}),
      "The ceiling is made from a mysterious white marble with a spiral of "+
      "black intertwining in seamless patterns.\n");

    add_item(({"floor", "flooring"}),
      "The floor is made from a mysterious white marble with a spiral of "+
      "black intertwining in seamless patterns.\n");

    add_item(({"marble"}),
      "The marble is beautifully mysterious, as it appears to almost be glowing.\n");

    add_item(({"pattern", "patterns"}),
      "The patterns in the marble are seamless as the black intertwining with "+
      "each other in spirals, twists and curves.\n");

    add_item(({"eil-galaith"}),
      "Perhaps if you'd like to know more about the Eil-Galaith you "+
      "might try to seek a library.\n");

    add_item(({"eilgalaith"}),
      "Do you mean: Eil-Gailaith?\n");


    create_guild_room();

}
