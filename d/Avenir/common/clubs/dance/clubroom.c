// -*-C++-*-
// file name: 	  /d/Avenir/common/clubs/dance/clubroom.c
// creator(s):	  Gracie&Tep	July 1995
// last update:   Lilith, attached to port now. True club room
//                 for joining is located at:
//                /d/Avenir/common/bazaar/intr/clubroom.c
//       	  Lilith, March 26 1997
// purpose:       Startroom for Dancer of Veils club
// note:  
// bug(s):
// to-do:

#include <const.h>
#include "/d/Avenir/common/clubs/dance/dance_club.h"
#include "/d/Avenir/include/relation.h"
#pragma save_binary
inherit "/std/room";

/* Prototypes */
static int start(string str);

void
create_room()
{
    set_short("A luxurious guest room");
    set_long("This guest room is large and well-appointed, intended "+
        "to accomodate the refined tastes of most sybarites. The dark "+
        "stone walls are covered in tapestries, and the floor in "+
        "carpets. Several large beds have been placed in a row along "+
        "the north wall. A small brazier burns in the southwest "+
        "corner of the room, emitting the scents of citrus and "+
        "sandalwood. A discreet sign framed in rare kesoit wood "+
        "has been placed near the door.\n");

    add_exit(PORT+ "landing", "south");

    add_item("sign", "@@read_sign");
    add_cmd_item("sign", "read", "@@read_sign");

    add_item(({"carpet", "carpets", "tapestry", "tapestries", "walls",
        "floors"}),
        "The floors and walls are covered in tapestries and carpets "+
        "that are woven from the hair of the sybarun goat, which "+
        "produces a fine, silky finish. They are in a variety of "+
        "muted colours, with repeating mandala-type patterns.\n"); 
    add_item(({"bed", "beds", "sheets", "blankets","mattresses", "mattress"}),
	"The beds are both lovely and sturdy. The mattresses are stuffed "+
	"with feathers. Silken sheets and wool blankets are piled at the "+
	"foot of each bed. And each bed is draped in an opaque curtain "+
        "which provides some semblance of privacy to each guest.\n");
    add_item(({"brazier", "small brazier" }), 
        "It is a small brazier used to warm the room and provide a "+
        "pleasing aroma at the same time. Presently, it is burning "+
        "something that smells of citrus and sandalwood.\n");

    IN
    seteuid(getuid(TO));
}


string
read_sign()
{
    return "Welcome to the Stormy Haven Inn.\n\n"+
        "This guest room has been provided specifically for sybarites "+
        "such as yourself, free of charge.\n"+
        "You can <start here> to make this your permanent place to rest.\n"+
        "Or you can use <start temp> to start here just one time.\n";    
}

void
init()
{
    ::init();

    if (IS_SYBARITE(this_player()) || IS_DANCER(this_player()) ||
        IS_MUMMER(this_player()))
    {
        add_action(start,"start");
    }
}

static int
start(string str)
{
    object veil;

    
    if (str == "temp") 
    {
        TP->set_temp_start_location(HERE + "clubroom");
        write("A sleeping space has been cleared for you. You "+
            "will awaken here just this next time.\n");
        return 1;
    }

    if (str == "here")
    {
        TP->set_default_start_location(HERE + "clubroom");
        write("A sleeping space has been cleared for you. You "+
            "will now start here each time you awaken.\n");
        return 1;
    }

    NF("Do you want to <start here> or <start temp>?\n"+
       "Using <start here> will make "+
       "this room your new start location. Using <start temp> will "+
       "make this your start place for just one time.\n");
    return 0;
}

