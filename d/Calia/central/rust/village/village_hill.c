/* Created 29/9/98 by Bishop, of Calia. This is a room in the
gnome village of Rust. */

inherit "/std/room";

#include <defs.h>
#include <stdproperties.h>


create_room()
{
    set_short("Hill in the gnome village");

    set_long("You are standing on a hill in the great forest." +
        " West of you, a small village stretches out. The great" +
        " oak trees tower far above you even as you are standing" +
        " on this hill. A long rope is hanging down here, probably" +
        " attached to a tree limb far above.\n");

    add_item("village","You can step down and explore it further" +
        " if you go west.\n");
    add_item(({"trees", "oak tree", "oak trees", "oaks"}), "The" +
        " great oak trees tower above you and have been stripped of" +
        " limbs close to the ground.\n"); 
    add_item("hill", "You're standing on it, perhaps 30 meters above" +
        " ground level in the village.\n");
    add_item("rope","It doesn't look possible to climb, but you could" +
        " probably grab it and swing yourself out over the village.\n");

    add_prop(ROOM_I_HIDE, 40);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VILLAGE+"village_path14","west",0,1);
}


int
grab_rope(string str)
{
    int i;
    i = random(3);

    notify_fail("Grab what?\n");
    if (str == "rope")
    {
        TP->catch_msg("You grab the rope, and recklessly throw" +
            " yourself out over the village, trying to dodge as" +
            " many branches as you can. In midflight you let" +
            " go and pray for a safe landing.\n");
 
        if (i==0)
        {
            TP->move_living("flailing and clinging to a rope",
                VILLAGE + "village_path2",1);
        }
        
        else
        if (i==1)
        {
            TP->move_living("flailing and clinging to a rope",
                VILLAGE + "village_path9",1);
        }
        
        else
        if (i==2)
        {
            TP->move_living("flailing and clinging to a rope",
                VILLAGE + "village_path16",1);
        }

        TP->catch_msg("Whew! You manage to land safely, slightly" +
            " shaken by the experience.\n");
        
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(grab_rope,"grab");
}
