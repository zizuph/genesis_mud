#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

public void
create_morgul_room()
{
  set_road(9);
  set_short_desc("in Angmar Square in Minas Morgul");
    set_extraline("This wide square lies north of the Tower of Minas Morgul, "+
    "between the city wall to the west and the north and a large building "+
    "to the east. The square is empty, except for the ruined foundations "+
    "of a house in front of the northern wall and a large stone slab right in "+
    "the center of the square.");
    set_side("west");
 
    add_tower();
    add_walls();
  add_item(({"building","library"}), BSN(
    "Over the doorway leading into the building east of the square is written: "+
    "'Library of Minas Morgul' in thick black letters. "));
  add_item(({"stone","stone slab","slab"}), BSN(
    "The large black stone slab in the center of the square is about one meter " +
    "high and several meters in circumference. It must have cost a tremendous effort "+
    "to bring it here into this square which is surrounded by buildings on all sides. "+
    "On top of the slab, there are symbols chiseled into the surface."));
  add_item(({"symbol","symbols","inscription"}), BSN(
    "You can see a tree and a moon. The moon is disfigured by a death's head, and the "+
    "flames are devouring the tree. Suddenly you realize that this must be the place "+
    "where at the End of the Second Age Isildur planted the sapling he had rescued " +
    "from the Downfall of Numenor, the scion of Nimloth the Fair! The Lord of Morgul " +
    "probably ordered the slab to be placed where once the White Tree of Minas Ithil " +
    "stood, lasting memory of his conquest of Minas Ithil and the destruction of " +
    "the tree which followed. "));
  add_item(({"house","foundation","foundations","ruin","ruins"}), BSN(
    "There is almost nothing left of this once mighty building. From the foundations " +
    "it is clear that this must have been the residence of great Lord or Lady. But "+
    "with great force, everything has been leveled, no stone above ground was left " +
    "in its place. The remaining ruins look like a momument to the destruction " +
    "of the building, celebrating the demolition of the walls as a symbol of a " +
    "great conquest. "));
  add_exit(MORGUL_ROOM_DIR + "public_library","east","@@check_exit",1);
  add_exit(MORGUL_DIR + "tower/tower_0n","south","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/sec_entr","northwest", "@@check_exit",1);
}
      
