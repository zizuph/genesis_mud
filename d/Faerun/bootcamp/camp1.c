/*
 * Clyptas - August 2017
 */
 
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#define PATH    CAMP_DIR + "hidden_trail1"
 
inherit "std/room";
 
public void
create_room()
{
    
    //0 means outdoors, and 1 means indoors for this prop
    add_prop(ROOM_I_INSIDE, 0);
    
    set_short ("A small encampment inside a large clearing.");

    set_long("A clearing opens up before you. You see three tents, a rather " +
        "large one flanked by two smaller tents. There is a cookfire set in " +
        "the midst of the trifecta.\n");
    
    add_item(({"underbrush","undergrowth","briars","nettles","bushes"}),
        "The underbrush is thick and full of briars and nettles. Parts on " +
        "this side appear trampled, as if someone or something passes " +
        "through quite often.\n");
   
    add_item(({"clearing"}),
        "The clearing appears to be man-made and looks well used like the " +
        "camp has been here for quite some time. The paths are well worn " +
        "and the brush has been tamed back.\n");
    
    add_item(({"brush"}),
        "It has been cleared from the midst of the clearing. Sticks and " +
        "stones can break bones, after all.\n");
    
    add_item(({"tents"}),
        "There are three tents inside the clearing. One green, one brown " +
        "and one richly colored in deep shades of red.\n");
    
    add_item(({"first tent","green tent","smaller tent"}),
        "This is a small tent, lightly coloured and camouflaged to match " +
        "the forest around it. The flap is open.\n");
        
    add_item(({"second tent","brown tent","small tent"}),
        "This is a small tent, lightly coloured and camouflaged to match " +
        "the forest around it. The flap is open.\n");
        
    add_item(({"third tent","red tent","large tent"}),
        "This is a large tent, the largest of the three. There is a " +
        "colourful banner staked into the ground just outside, making " +
        "you think somone of importants resides within.\n");
    
    add_item(({"cookfire","fire"}),
        "This is a large smoldering cookfire, the fire looks like it was " +
        "recently extinguished, only faintly glowing embers remain.\n");
        
    add_exit(CAMP_DIR + "menzo_start","drow");
    add_exit(CAMP_DIR + "green_tent","northwest");
    add_exit(CAMP_DIR + "brown_tent","west");
    add_exit(CAMP_DIR + "red_tent","north");
    add_exit(CAMP_DIR + "hidden_trail1", "trail", 0, 1, 1);
}

void

init()
{
    ::init();
    add_action("do_enter","enter");
}

public string
do_search(object pl, string arg)
{
    if (IN_ARRAY(arg,
        ({ "path", 
           "trail", 
           "forest", 
           "forest trail",}) ) == 0)
    {
        return "Your search reveals nothing special.\n";
    }

        return "The forest is thick and dark, you think you you can see " +
             "something hidden in the bushes.\n";

}

public int
do_enter(string str)
{
    if(!strlen(str))
    {
        notify_fail("What did you wish to enter?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
        " [in] [through] [over] [the] [thick]"
      + " [green] 'bushes'"))
    {
        notify_fail("Enter what? The bushes?\n");
        return 0;
    }

    write("You enter the bushes and find your self on a hidden path.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " arrives on a hidden trail " +
        "through the thick bushes.\n");
    tell_room(PATH, QCTNAME(this_player()) + " arrives " +
        "through the thick bushes.\n");
    this_player()->move_living("M", PATH, 1, 0);
    return 1;
}