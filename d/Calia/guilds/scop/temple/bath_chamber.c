
/*
 * bath_chamber.c
 *
 * Bathing chamber for the Spirit Circle of Psuchae Temple
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
    set_short("Bathing chamber");
    set_long("You have entered a bathing chamber just off of "+
        "the main temple entranceway. The walls of this chamber "+
        "are painted bright white, as is the roof above. The "+
        "floor is covered in a white marble tile. In the middle "+
        "of the chamber is a small bath. Light is filtering in "+
        "from the main entryway to the east as well as coming "+
        "from somewhere in the bath itself.\n");

    add_item(({"wall", "walls"}), "The walls in this small "+
        "chamber are bright white in colour and very smooth to "+
        "the touch. The light coming from in the bath shines "+
        "brightly off of the walls, making this chamber almost "+
        "glow.\n");
    add_item(({"roof", "ceiling"}), "The ceiling is painted with "+
        "the same bright white colour as that of the walls. The "+
        "light shining from inside the bath reflects off of it, "+
        "making it shine on everything below it.\n");
    add_item(({"floor","marble floor","white marble floor",
        "tile","marble tile","white marble tile"}), "The floor "+
        "is covered in a smooth, white marble tile. It is very "+
        "clean.\n");
    add_item("light", "Light shines in from not only the main "+
        "entryway to the east, but also from within the bath "+
        "itself.\n");
    add_item(({"entryway","main entryway"}), "The main entryway "+
        "is back to the east. Light filters into this chamber from "+
        "that direction.\n");
    add_item(({"bath", "small bath"}), "The small bath is made "+
        "from white marble, similar to the marble that tiles the "+
        "floor. It is very shallow and contains just enough water "+
        "to wash yourself with. At the bottom of the bath is a "+
        "small light covered in a glass hemisphere so it does not "+
        "get wet. The light shines brightly through the water, "+
        "illuminating the chamber nicely.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"entryway","east",0,1);
}

int
do_wash(string str)
{
    if (!str)
    {
        NF("Wash what? Yourself? <wash myself>\n");
        return 0;
    }

    if (str != "myself")
    {
        NF("Wash what? Yourself? <wash myself>\n");
        return 0;
    }

    if(TP->query_prop(BATHED_IN_TEMPLE_BATH))
    {
        NF("You have already washed in the temple bath. You "+
           "do not need to wash again.\n");
        return 0;
    }

    write("You dip your hands into the small bath, feeling the "+
        "cool water on them. Making a cupping motion with your "+
        "hands, you raise them out and use the water to wash "+
        "your face and neck.\n");
    
    if(TP->query_prop(PRAYED_AT_TEMPLE_ALTAR))
    {
        write("\nYou feel now that you have been purified "+
            "enough to enter the temple.\n");
    }
    
    else
    {
        write("\nYou feel you are one step closer to being purified "+
            "enough to enter the temple.\n");
    }
    
    TP->add_prop(BATHED_IN_TEMPLE_BATH,1);
    say(QCTNAME(TP)+" dips "+TP->query_possessive()+" hands into the "+
        "bath, cupping some water with them as "+TP->query_pronoun()+
        " raises them out of the bath. "+capitalize(TP->query_pronoun())+
        " washes "+TP->query_possessive()+" face and neck with the "+
        "water.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_wash,"wash");
}
