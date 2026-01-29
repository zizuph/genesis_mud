/*
 *  /d/Gondor/rohan/fangorn/fangorn20.c
 *
 *  The rock wall in the center of Fangorn Forest
 *
 *  Alto, 12 May 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/drink_water.c";
inherit "/d/Gondor/minas/lib/f_funcs2.c";


#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"


#define INNER_MINAS "/d/Gondor/minas"
#define FANGORN_DIR "/d/Gondor/fangorn/"

public void
create_gondor()
{
    set_short("A rock wall in the center of the forest");
    set_long("There is a rock wall before you here, the side of a hill, "
        + "or perhaps the abrupt end of some long root thrust out by the "
        + "distant mountains. No trees grow on its stony face. A small "
        + "stream flows around the wall from the northwest.\n");

    add_exit(FANGORN_DIR + "fangorn20a", "up", 0, 10, 1);
    add_exit(FANGORN_DIR + "fangorn14", "northwest", 0, 0, 0);
    add_exit(FANGORN_DIR + "fangorn15", "northeast", 0, 0, 0);
    add_exit(FANGORN_DIR + "fangorn34", "southwest", 0, 0, 0);
    add_exit(FANGORN_DIR + "fangorn23", "southeast", 0, 0, 0);
    add_exit(FANGORN_DIR + "fangornq", "north", 0, 0, 0);

    set_drink_from("stream");

    add_prop(OBJ_I_CONTAIN_WATER, -1);


    add_item(({"water", "stream"}), "The small stream runs past, with "
        + "little noise, on its way east. The water looks cool and "
        + "inviting.\n");
    add_item(({"tree", "trees", "forest", "fangorn forest", "wood", "bark"}), 
        "Where all had looked so shabby and grey before, the wood now "
        + "gleams with rich browns, and with the smooth black-greys of "
        + "bark like polished leather.\n");
    add_item(({"wall", "rock wall", "root"}), "This is a large wall of rock. "
        + "Its face rises high above you.\n");
    add_item(({"face", "face of wall", "wall face", "stony face"}), "The "
        + "face of the rock wall has something like a stair leading up.\n");
    add_item(({"stair", "stair on face", "stair on wall"}), "The stair "
        + "leads up the face of the rock wall. Natural perhaps, and made "
        + "by the weathering and splitting of the rock, for it is rough and "
        + "uneven.\n");
    add_item(({"mountain", "mountains", "misty mountains"}), "Distant "
        + "and almost unseen, "
        + "the Misty Mountains stretch away into the east and north.\n");

    setuid();
    seteuid(getuid());
    clone_object("/d/Gondor/fangorn/npc/torchless_object.c")->move(TO);

    reset_room();

} 


public void
init()
{
    ::init();
    init_drink();
}
  

