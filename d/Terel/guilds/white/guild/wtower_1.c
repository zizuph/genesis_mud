

#include "/d/Terel/include/Terel.h"
inherit WHITE + "guild/keep_room";
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

object door;

public void
create_terel_room()
{
    ::create_terel_room();
    set_short("western tower of the stronghold");
    set_long("\n\n\n\n\n");
    INSIDE;

    door=clone_object(WHITE + "guild/wtow_door")->move(TO);
    add_exit(WHITE + "guild/wtower_2", "up", 0, 0);

    reset_room();
}


