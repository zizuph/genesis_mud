/* A tent room. Mortricia 920927 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define CAMP_DIR        MORTRICIADIR + "camp/"
#define TENT_DIR        CAMP_DIR + "tent/"

void
reset_room()
{
    object acrobat;

    if (!present("acrobat", TO)) {
        acrobat = clone_object(TENT_DIR + "acrobat");
        acrobat -> move(TO);
    }
}

void
create_room()
{
    set_short("Rear part of big tent");
    set_long(BSN(
        "You are in the rear part of the big tent. " +
        "You notice a strange and intense smell. " +
	"To the southwest you notice a small opening in the canvas, " +
	"through which you can leave the tent. To the west and " +
	"east are rooms."
    ));
    
    add_item(({"smell"}), BSN(
        "The smell is considerable, and it seems as if it comes " +
        "from the room to the west."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TENT_DIR + "behind1", "north", 0);
    add_exit(TENT_DIR + "animals", "west" , 0);
    add_exit(TENT_DIR + "mag"    , "east" , 0);
    add_exit(TENT_DIR + "behind3", "southwest" , 0);

    reset_room();
}
