inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Dark passage");
    set_long( "You are standing in a cold, dark passage. Drips "+
        "of icy water fall from the roof, making puddles on the floor. High on"+
        " the eastern wall is a narrow ledge, which you might be able to "+
        "reach if you tried climbing the walls.\n" );
 
    add_item(({"puddles","puddle"}), "Puddles of murky water "+
        "that drips from the glistening walls.\n" );
 
    add_item("ledge", "A narrow ledge some way above you on the "+
        "eastern wall. You think you might ba able to climb up to it, but "+
        "it would be dangerous over these wet rocks.\n" );
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "cave3","southeast");
}
 
void
init()
{
    ::init();
    add_action("do_climb","climb");
    add_action("do_climb","up");
}
 
int
do_climb(string str)
{
 
    /* check players climb skill :) */
    if((this_player()->query_skill(104) + random(60) + 1) >=55)
    {
        write("You scale the wall with ease and pull yourself onto the ledge.\n");
        this_player()->move_living("climbing up to the ledge",
            GRAVEYARD_DIR + "ledge");
        return 1;
    }
 
        /* check acrobatics skill to avoid falling damage */
    if ((this_player()->query_skill(52) + random(50) + 1) >= 50)
    {
   write("You slip on the wet rocks, but manage to break your fall.\n");
        return 1;
    }
 
        /* time to hand out some falling damage <evil grin> */
 
    write( "You attempt to climb up to the ledge, but lose your "+
        "balance and painfully land in a heap on the floor.\n" );
 
    this_player()->heal_hp(-(this_player()->query_max_hp()) *
         (random(100) + 1) / 1000);
 
    if (this_player()->query_hp() <= 0)
        this_player()->do_die(this_object());
    return 1;
}
