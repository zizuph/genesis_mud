inherit "/std/room";
 
#include "/d/Emerald/defs.h";
 
 
void
create_room();
create_room()
{
    set_short("Ant cave");
    set_long( "You are standing in a cold, acrid smelling cave. "+
        "You are starting to get more than a little depressed by the cold, "+
        "dark surroundings.\n" );
 
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);
 
    add_exit(GRAVEYARD_DIR + "pass8","northwest",0,1);
    add_exit(GRAVEYARD_DIR + "pass9","south",0,1);
    add_exit(GRAVEYARD_DIR + "pass10","northeast",0,1);
 
    set_alarm( 1.0,0.0,"reset_room");
}
 
 
void
reset_room()
{
    object ant;
    int i;
 
    ant=present("ant");
 
    if (ant && ant->query_name()!="corpse")
        return;
 
    for (i=0 ;i<3 ;i++ )
    {
        ant=clone_object( GRAVEYARD_DIR + "npc/ant");
        ant->move(this_object());
        tell_room(this_object(),QCNAME(ant) + " scurries in.\n");
    }
}
