inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Ledge");
    set_long( "You are standing on a narrow ledge above a tunnel "+
        "leading south. You could try to climb down here, but the rocks look "+
        "quite slippery. There is a fissure that you might be able to enter "+
        "in the north wall.\n" );
 
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);
 
 
    add_item("fissure","Its a deep fissure, that you could probably squeeze"+
        " through.\n");
 
}
 
void
init()
{
    ::init();
    add_action("do_enter","enter");
    add_action("climb_down","down");
    add_action("climb_down","climb");
}
 
 
int
do_enter(string str)
{
    if (str != "fissure")
        {
        write("Enter what?\n");
        return 1;
    }
 
    write("You squeeze through the small gap.\n");
    this_player()->move_living("into a fissure",GRAVEYARD_DIR + "cave2");
    return 1;
}
 
 
int
climb_down(string str)
{
            /* check climbing skill */
 
    if ((this_player()->query_skill(104) + random (60) +1 )>=55)
    {
       write("You climb down the tunnel wall.\n");
        this_player()->move_living("climbing down to the tunnel below",
            GRAVEYARD_DIR + "pass5");
        return 1;
    }
 
            /* check acrobatics to avoid damage */
 
    if ((this_player()->query_skill(52) + random(50) + 1 )>=50)
    {
        write("You slip on a wet rock, but land well.\n");
        this_player()->move_living("climbing down",GRAVEYARD_DIR + "pass5");
        return 1;
    }
 
            /* Damage time again (I enjoy this bit ;-) ) */
 
    write("You slip on the way down, and fall to the ground hitting your head.\n");
 
    this_player()->heal_hp(-(this_player()->query_max_hp())
        * (random(100) + 1) / 1000);
 
    if (this_player()->query_hp() <= 0)
        this_player()->do_die(this_object());
 
    this_player()->move_living("falling off the ledge",GRAVEYARD_DIR + "pass5");
    return 1;
}
