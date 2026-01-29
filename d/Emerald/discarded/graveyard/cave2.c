inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Large cave");
    set_long( "You are standing in a large cave. The floor "+
       "here is littered with boulders and the walls are rough, full of cracks"+
        " and fissures.\n" );
 
    add_item(({"boulders","boulder"}), "The boulders are "+
        "composed of the light grey rock that seems to make up most of this "+
        "area. They are all much too heavy to lift.\n" );
 
    add_item(({"crack","cracks","fissure","fissures"}),
        "Most of the faults in the walls are quite small. However, there "+
        "is one fissure that you think you might be able to squeeze through"+
        ".\n" );
 
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);
 
    add_exit(GRAVEYARD_DIR + "pass4","north",0,1);
}
 
 
void
init()
{
    ::init();
    add_action("do_enter","enter");
}
 
int
do_enter(string str)
{
    if (str != "fissure")
    {
        write("Enter what?\n");
        return 1;
    }
    write("You manage to squeeze your body through the gap.\n");
    this_player()->move_living("into a fissure",GRAVEYARD_DIR + "ledge");
    return 1;
}
