
/*
 * altar_chamber.c
 *
 * Altar Chamber for the Spirit Circle of Psuchae Temple
 * 
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 24, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

void
create_room()
{
    set_short("Altar chamber");
    set_long("You have entered a bright white, well lit chamber "+
        "just off of the main entryway of the temple. The walls "+
        "of this chamber are painted bright white, as is the "+
        "ceiling above you. The floor is covered in a white marble "+
        "tile. In the centre of the room is a small white altar. "+
        "On the eastern wall, above the altar, hangs a lamp giving "+
        "off enough illumination to light this chamber.\n");

    add_item(({"wall","walls","east wall"}), "The walls here are bright "+
        "white in colour and very smooth to the touch. The light "+
        "from the lamp hanging on the eastern wall shines brightly "+
        "off of all of the walls and the ceiling, making this chamber "+
        "almost glow.\n");
    add_item(({"roof", "ceiling"}), "The ceiling is painted with "+
        "the same bright white colour as that of the walls. The "+
        "light shining from the lamp hanging on the wall reflects "+
        "off of it, making it shine on everything below it.\n");
    add_item(({"floor","marble floor","white marble floor",
        "tile","marble tile","white marble tile"}), "The floor "+
        "is covered in a smooth, white marble tile. It is very "+
        "clean.\n");
    add_item("light", "Light shines in from not only the lamp "+
        "hanging on the eastern wall, but also from the main "+
        "entryway to the west.\n");
    add_item(({"entryway","main entryway"}), "The main entryway "+
        "is back to the west. Light filters into this chamber from "+
        "that direction.\n");
    add_item(({"lamp", "hanging lamp"}), "It is a small brass lamp "+
        "hanging on the eastern wall of this chamber. It gives off "+
        "enough light to illuminate the entire room.\n");
    add_item(({"altar","white altar","small altar","small white altar"}),
        "This small white altar is sitting in the centre of the room. "+
        "It is made from white marble, much like the marble that the "+
        "floor is tiled with. Surrounding the base of the altar is "+
        "a red cushion. There is a small inscription on the top of "+
        "the altar.\n");
    add_item(({"cushion","red cushion"}),"This red cushion surrounds "+
        "the base of the altar on all sides. It is very comfortable "+
        "to the touch. It is most likely for one to kneel on while "+
        "praying at the altar.\n");
    add_item(({"inscription","small inscription"}),"The inscription "+
        "on the top of the altar reads:\n\nPray at the altar for "+
        "purity.\n\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"entryway","west",0,1);
}

int
do_pray(string str)
{
    if (!str)
    {
        NF("Pray where? At the altar? <pray at the altar>\n");
        return 0;
    }

    if (str != "at the altar")
    {
        NF("Pray where? At the altar? <pray at the altar>\n");
        return 0;
    }

    if(TP->query_prop(PRAYED_AT_TEMPLE_ALTAR))
    {
        NF("You have already prayed at the temple altar. You "+
           "do not need to pray again.\n");
        return 0;
    }

    write("You kneel on the red cushion briefly at the altar and pray.\n");
    
    if(TP->query_prop(BATHED_IN_TEMPLE_BATH))
    {
        write("\nYou feel now that you have been purified "+
            "enough to enter the temple.\n");
    }
    
    else
    {
        write("\nYou feel you are one step closer to being purified "+
            "enough to enter the temple.\n");
    }
    
    TP->add_prop(PRAYED_AT_TEMPLE_ALTAR,1);
    say(QCTNAME(TP)+" kneels briefly on the red cushion and prays "+
        "at the altar.\n");
    return 1;
}

int
do_read(string str)
{
    if (!str)
    {
        NF("Read what? The inscription? <read inscription>\n");
        return 0;
    }

    if (str != "inscription")
    {
        NF("Read what? The inscription? <read inscription>\n");
        return 0;
    }

    write("The inscription on the top of the altar reads:\n\n"+
        "Pray at the altar for purity.\n\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_read,"read");
    add_action(do_pray,"pray");
}

