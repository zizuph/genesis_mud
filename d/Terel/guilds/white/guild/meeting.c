

#include "/d/Terel/include/Terel.h"
inherit WHITE + "guild/keep_room";
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

object door, board;

public void
create_terel_room()
{
    ::create_terel_room();
    set_short("grand meeting hall");
    set_long("@@sconce@@This is to test this.\n\n\n\n\n");
    INSIDE;

    door=clone_object(WHITE + "guild/meet_door")->move(TO);
    board=clone_object(WHITE + "scroll")->move(TO);
    reset_room();
}


