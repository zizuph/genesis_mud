inherit "/std/room";

#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Tomb");
    set_long( "As you enter this room, your eyes are drawn to " +
        "a dais at the far end. Upon this dias rests a row of four stone " +
        "tables, and each contains a mummified corpse.\n" );
 
    add_exit(GRAVEYARD_DIR + "cave10","south",0,1);
 
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);
 
    add_item("dias", "A simple raised platform at the far end " +
        "the room.\n" );
 
    add_item(({"corpse","corpses","mummy","mummies","mummified corpse",
        "mummified corpses"}), "A corpse wrapped in bandages " +
        "lies on each of the four stone tables. Although they were preserved " +
        "against decay, they have been here for some time, and are beginning " +
        "to smell rather bad.\n" );
 
    add_item(({"tables","table","stone tables","stone table"}),
         "These are simple heavy looking tables made from hard " +
        "stone.\n" );
 
    set_alarm( 1.0,0.0,"reset_room");
}
 
 
void
reset_room()
{
    object wight;
 
    wight = present("wight");
    if (wight && wight->query_name() != "corpse")
        return;
 
    wight = clone_object(GRAVEYARD_DIR + "npc/wight");
    wight->move(this_object());
    tell_room(this_object(), QCTNAME(wight) + " arrives.\n");
}
