inherit "/d/Emerald/std/dir_room";
 
#include "/d/Emerald/defs.h"
 
#define DP(LABEL) ("@@dir_phrase|" + LABEL + "@@")
 
#define WEST GRAVEYARD_DIR + "pass12"
#define NORTHEAST GRAVEYARD_DIR + "pass16"
 
 
void
create_room()
{
    set_short("Tunnel under graveyard");
    set_long( "This is a damp, dark tunnel that winds away to "+
        "the "+ DP("dir") + ".\n" );
 
    add_dir_phrase("dir", WEST, "northeast");
    add_dir_phrase("dir", NORTHEAST, "west");
    add_dir_phrase("dir", 0, "west");
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "pass16","northeast",0,1);
    add_exit(GRAVEYARD_DIR + "pass12","west",0,1);
 
    set_alarm( 1.0,0.0,"reset_room");
}
 
 
void
reset_room()
{
    object zombie;
 
    zombie = present("zombie");
    if (zombie && zombie->query_name()!="corpse")
        return;
 
    zombie=clone_object(GRAVEYARD_DIR + "npc/zombie");
    zombie->move(this_object());
    tell_room(this_object(), QCTNAME(zombie) + " arrives.\n");
}
