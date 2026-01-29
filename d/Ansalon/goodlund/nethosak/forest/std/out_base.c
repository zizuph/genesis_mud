/* Room base for the city of Nethosak 
 * ONLY OUTDOOR!
 * - Elmore.
 */

#include "/d/Ansalon/common/defs.h"
#include "/w/elmore/mithas/local.h"
#include <macros.h>
#include <stdproperties.h>
inherit MITHAS_OUT;

void
create_mithas_room()
{
    add_item(({"stone", "path", "rock", "road"}), "The road "+
      "is very orderly, nearly unblemished. The lane is "+
      "covered in stone, so that it almost looks like the "+
      "structures around it is melted into the road.\n");
    add_item(({"building", "buildings", "house", "houses"}), "The "+
        "buildings are very beautiful and they seem very clean and "+
        "new, though many might be centuries old.  Towering above "+
        "all the other buildings is a large house with a wide "+
        "edifice and an arched roof, this must be the palace of "+
        "the emperor.\n");

 //   set_tell_time(200);
 //   add_tell("You hear loud cheers coming from the Arena.\n");
 //   add_tell("A minotaur patrol passes you, looking suspiciously "+
 //            "at your weapons.\n");
 //   add_tell("A bunch gully dwarves runs away from you.\n");
 //   add_tell("You hear a loud laughter from nearby.\n"); 
 //   add_tell("A kender approches, he clumsily bumps into "+
 //           "you but quickly disappears down an alley.\n");
 //   add_tell("You notice a group of minotaurs pointing at you.\n"); 
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}
