/*
 *  /d/Gondor/rohan/fangorn/fangorn20b.c
 *
 *  The rock wall in the center of Fangorn Forest
 *
 *  Alto, 12 May 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/minas/lib/dinen_funcs.c";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/d/Gondor/minas/lib/f_funcs2.c";


#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/minas/lib/porter_defs.h"


#define INNER_MINAS "/d/Gondor/minas"
#define FANGORN_DIR "/d/Gondor/fangorn/"

public void
create_gondor()
{
    set_short("A stair in the rock wall");
    set_long("You are climbing the stony face of the rock wall. The "
        + "stair is steep and difficult to climb.\n");

    add_exit(FANGORN_DIR + "fangorn20c", "up", 0, 10, 1);
    add_exit(FANGORN_DIR + "fangorn20a", "down", 0, 0, 0);

    add_item(({"tree", "trees", "forest", "fangorn forest"}), 
        "Where all had looked so shabby and grey before, the wood now "
        + "gleams with rich browns, and with the smooth black-greys of "
        + "bark like polished leather.\n");
    add_item(({"wall", "rock wall", "root"}), "This is a large wall of rock. "
        + "Its face rises high above the forest.\n");
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

