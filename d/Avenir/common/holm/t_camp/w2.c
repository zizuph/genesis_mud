/* file name:        /d/Avenir/common/holm/t_camp/w2.c
 *  creator(s):      (Rangorn , Feb 97)
 *  revisions:
 *          Manat, Sep 2001, Removed enter_inv
 *  purpose:
 *  note:
 *  bug(s):
 *  to-do:
 */

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/t_camp/camp_base";

/* Include the local area defines, etc */
#include "../holm.h"

/* Now create the room.  */
void
create_camp_room()
{
    set_short("inside the windshed");
    set_long("This is indeed a simple structure. A dark cloth has been "+
             "secured to the cliffwall by some sort of unguent, and " + 
             "laid out on wooden poles. The awning casts a very dark "+
             "shadow against east wall, creating a deep pool of "+
             "blackness which seems to absorb all light. There is a "+
             "sleeping pallet on the ground here.\n");
    add_exit(T_CAMP +"w1", "out", 0);
    add_exit(T_CAMP +"w3", "east", 0, 1, 1);

    add_item(({"awning", "cloth", "windshed", "shed", "structure"}),
        "The awning of the windshed is made of a dark fabric, possibly "+
        "webcloth. It provides a rudimentary form of shelter.\n");
    add_item(({"poles", "pole", "wooden pole"}),
        "Wooden poles, likely made from trees felled in the jungle "+
        "north of here, as the thornbushes in this area don't grow "+
        "tall enough nor straight enough for this use.\n");
    add_item(({"unguent" }),
        "A thick, dark substance with an acrid scent. It is rather "+
        "sticky, and is being used to glue the cloth to the cliff "+
        "wall.\n");
    add_item(({"wall", "cliffwall", "cliff", "east wall", "pool",
        "blackness"}), "You aren't sure, but that dark area in "+
        "the cliff wall just might be an opening.\n");
    add_item(({"opening", "dark area", "east face"}), 
        "Yep, there sure is an opening in the east face of the cliff "+
        "wall.\n");      
    add_item(({"pallet", "sleeping pallet"}),
        "It is a simple straw pallet.\n");
}

/* Removed due to Torqual request since it appears to block
 * Knights horses. (Removed for testing mostly.)
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob))
        ob->command("out");
}
*/
