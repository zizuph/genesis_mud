/*
ROOM: Council of Lords debate chamber
BY:   Sebster
DATE: Aug 28, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

void
create_room()
{
    ::create_room();
    hear_bell = 2;
    
    add_prop(ROOM_I_INSIDE, 1);
    
    set_short("The Council of Lords Debate Chamber");
    set_long(
        "This is the Council of Lords Debate Chamber. Here all the debates "+
        "about important Lord business take place. "+
        "Several large portraits hang on the walls, decorating "+
        "the room along with a large soft carpet. "
    );
    set_time_desc(
        "The room is completely empty at the moment. Maybe there is nothing "+
        "to debate around here anymore.\n",
        "Lots of Lords were discussing something until you marched in. Now "+
        "they're all staring at you, and they don't look happy.\n"
    );
    
    add_item("carpet","Its large and soft, and probably very "+
        "expensive.\n");
    add_item(({"portrait","portraits"}),
        "They are excellent naturalistic paintings of the city and "+
        "the areas around it. Some shows a couple of sincere and "+
        "grave people, staring down at you.\n");
    
    add_exit(CENTRAL(plaza/cl_hall2), "southwest", 0, -1, -1);
}

make_note()
{
    object note;
    note = clone_object("/d/Kalad/common/central/obj/spy_note");
    note -> move(TO);
    return;
}

