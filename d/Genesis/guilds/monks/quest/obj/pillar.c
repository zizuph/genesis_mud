#include "defs.h"
inherit MONK_OBJ + "table";

public void
create_table ()
{
    remove_name ("table");
    add_name ("pillar");
    add_name (QUEST_PILLAR);
    set_short ("tall white pillar");
    set_long ("The pillar is tall and white, carved into fluted "
	+ "grooved from pure white marble. ");
}

public void
init_pillar (object to_room)
{
    move (to_room, 1);
    clone_object (QUEST_WATERCLOCK)->move (this_object (), 1);
}

