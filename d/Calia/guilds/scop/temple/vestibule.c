/*
 * vestibule.c
 *
 * Vestibule for the Spirit Circle of Psuchae Temple
 * This is the entrance/exit of the temple to/from the garden out back
 * Players will have to wash themselves to re-enter the temple here 
 * (wizards do not need to wash, they are always "pure" <grin>)
 *
 * Copyright (C): Jaacar (Mike Phipps), July 30th, 2003
 *
 * Navarre September 18th 2006, Changed long description to have doorway
 * instead of door, per request from Anahita.
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
    set_short("Vestibule");
    set_long("You are standing in the vestibule of the temple. This "+
        "porch-like area contains a small bathing pool where you can "+
        "wash yourself after leaving the sanctity and purity of the "+
        "temple. There is a doorway leading back into the temple in the "+
        "eastern wall. To the west you see a small pathway leading off "+
        "through many different types of plants.\n");

    add_item(({"doorway","eastern wall"}),"There is a doorway in the eastern "+
        "wall leading back into the temple. It is decorated in a mosaic of "+
        "multicolored glass tiles. The tiles depict birds in flight over the "+
        "Silent Forest.\n");
    add_item(({"pathway","small pathway"}),"A small dirt pathway lies "+
        "west of here, winding its way through many different types of "+
        "plants.\n");
    add_item(({"plant","plants"}),"There are many types of plants "+
        "off to the west of here. Winding its way through the plants "+
        "lies a small pathway.\n");
    add_item(({"bath","small bath","pool","small pool","bathing pool",
        "small bathing pool"}), "The small bathing pool is made "+
        "from white marble. It is very shallow and contains just "+
        "enough water to wash yourself with. <wash myself>\n");
    add_item("temple","Rising seamlessly from the bosom of the earth, "+
      "the Temple of the Spirit Circle of Psuche stands towering "+
      "before you.\n");
    add_item(({"wall","walls"}),"The walls are very plain and made out "+
      "of grey stones placed together.\n");
    add_item("birds", "The birds are robins, busily gathering materials for "+
     "their nests.  One holds a bright purple ribbon, decorated in silver "+
     "paint.  Standing on your tiptoes, you can just read the words on "+
     "the ribbon:\n\n"+
     " Then I was standing on the highest mountain of them all, and round about "+
     "beneath me was the whole circle of the world.  And while I stood there I "+
     "saw more than I can tell and I understood more than I saw, for I was "+
     "seeing in a sacred manner the shapes of all things in the spirit, and the "+
     "shape of all shapes as they must live together like one being.\n\n"+
     "And I say the sacred mandala of my people was one of the many mandalas that "+
     "made one circle, wide as daylight and as starlight.  And I saw that it was "+
     "holy... But anywhere is the center of the world.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"pathway","west",0,1);
    add_exit(SPIRIT_TEMPLE+"refectory","east","@@did_wash",1);
}

int
did_wash()
{
    if (TP->query_wiz_level())
    {
        write("Normally if you left the sanctity of the temple "+
            "and wanted to return, you would have to purify yourself "+
            "once again, but since you are a wizard, you do not need "+
            "to worry about that.\n");
        return 0;
    }
    
    if (TP->query_prop(BATHED_IN_TEMPLE_BATH))
    {
        TP->remove_prop(BATHED_IN_TEMPLE_BATH);
        return 0;
    }
    
    write("\nYou hear a voice booming from above:\n"+
           "Only the purified may enter!\n\n");
    
    return 1;
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
        "your face and neck.\nYou feel you now that you have been "+
        "purified enough to enter the temple.\n");
    
    TP->add_prop(BATHED_IN_TEMPLE_BATH,1);
    say(QCTNAME(TP)+" dips "+TP->query_possessive()+" hands into the "+
        "small bathing pool, cupping some water with them as "+
        TP->query_pronoun()+" raises them out of the pool. "+
        capitalize(TP->query_pronoun())+" washes "+TP->query_possessive()+
        " face and neck with the water.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_wash,"wash");
}


