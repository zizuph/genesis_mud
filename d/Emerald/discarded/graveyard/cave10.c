inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
#define CTNONMET  "The " + TP->query_nonmet_name()
#define SAY(x) say(({TP->query_name() + x,CTNONMET + x}))
 
void
create_room()
{
    set_short("antechamber");
    set_long("@@long_desc");
 
    add_exit(GRAVEYARD_DIR + "tomb1","north","@@check_north",1);
    add_exit(GRAVEYARD_DIR + "pass19","south",0,1);
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    set_alarm( 1.0,0.0,"reset_room");
}
 
 
void
reset_room()
{
    object guard;
 
    guard = present("knight");
    if (guard && guard->query_name() != "corpse")
        return;
 
    guard = clone_object(GRAVEYARD_DIR + "npc/phantom_knight");
    guard->move(this_object());
 
    tell_room(this_object(), QCNAME(guard) + " arrives.\n");
}
 
 
string
long_desc()
{
    object guard;
 
    guard = present("knight");
    if (guard && guard->query_name() != "corpse")
        return  "You have entered a small room, with a " +
            "passageway leading north. Standing in the entrance to the " +
            "passage is a knight the likes of which you have not seen " +
            "before. He seems be guarding the exit north, and you imagine " +
            "he would be quite efficient at it.\n" ;
 
    return  "This is a small bare room, with passageways " +
        "leading north and south.\n" ;
}
 
 
int
check_north()
{
    object guard;
 
    if(this_player()->query_wiz_level()>=1)
        return 0;
    guard = present("knight");
    if (guard && guard->query_name() != "corpse")
    {
        write( "You try to enter the north passageway, but " +
        "the guard moves to block your way.\n" );
 
    SAY(" tries to go north but is stopped by the knight.\n");
 
        return 1;
    }
 
    return 0;
}
