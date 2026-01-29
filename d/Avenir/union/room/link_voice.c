/*
 * File:     link_voice
 * Created:  Cirion, 1998.08.30
 * Purpose:  Room where the Rest of the world may communicate 
 *           with the Elders via a special board.
 *
 * Revisions:
 *   Lilith, Jun 2004: Implemented
 *
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

void 
union_room()
{
    set_short("Chamber of Voices");
    set_long("This is a low cavern of crystalline stone that "+
      "sparkles with moisture from an unknown source. It "+
      "looks more like a massive geode than anything else, "+
      "being lined as it is with large, compact crystal "+
      "formations. It has been left almost entirely in its "+
      "natural state, except for one wall. Against the west "+
      "wall is inset a shadowed board that "+
      "glimmers with dancing sparks of white light. "+
      "Echoing through the cavern is the barely discernable "+
      "murmur of soft voices. "+
      "A narrow stone stairwell spirals downward into "+
      "brightness.\n");
    add_item(({"stairwell", "stairs", "spiral"}),
      "From this shadowy place the post office beckons brightly.\n");
    add_item(({"geode"}),
      "This place resembles the hollow cavity of a massive "+
      "geode, one of those spherical rocks that, when cut "+
      "open, contain a delightful array of crystals.\n");
    add_item(({"crystal", "crystal formations", "crystals" }),
      "These are large, compact crystal formations such as "+
      "agate, jasper, and chalcedony. They glimmer gorgeously "+
      "in the shadowed light of the room.\n");       

    add_exit("post", "down");

    // clone the board object
    add_object(OBJ + "board_link");
}

int
query_prevent_snoop()
{
    return 1;
}
