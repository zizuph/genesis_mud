#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("This a dead end of of dark and narrow street running " +
        "south from here. The streets ends here at the foot of the northern " +
        "city wall. To both sides of the street, there are large houses.");
    set_road(3);
    set_side("north");

    add_walls();
    add_exit(MORGUL_DIR + "city/darkstr4","south","@@check_exit",1);

    clone_object(MORGUL_DIR+"city/doors/b3doorout")->move(TO);
    clone_object(MORGUL_DIR+"city/doors/b11doorout")->move(TO);
}
