#include "defs.h"
inherit KEEP_ROOM;
#define DRAKMERE_I_COWARD "_drakmere_i_coward"

/* The Drakmere Keep, by Sarr */
/* Made the npc unbouncable by alternative means. Blocking
   function obsolete.  - Nerull.*/

// Prototypes.
//int block();

void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You are now in the south part of a huge chamber. All "+
    "along the walls, you see paintings, statues, weapons, tapestries "+
    "and many other decorative things. Two large braziers burn near "+
    "the center of the room. To the north, you see a short dais, and "+
    "upon it, the Throne of Drakmere.\n");
    add_item("paintings","They are pictures of many wonderes and night"+
    "marish things. They are very beautiful.\n");
    add_item("statues","Beautiful sculptures of men and women.\n");
    add_item("weapons","They hang off the wall as treasures.\n");
    add_item("tapestries","They are beautifully woven, depciting many "+
    "wonderous scenes.\n");
    add_item("dais","A short, five-step dais that holds the throne.\n");
    add_item("braziers","Large iron pots that burn to make heat and light.\n");
    add_item("throne","The Golden Throne of Drakmere, where the Lord "+
    "himself sits.\n");
    add_item("torches","They light up this dim place.\n");
    //add_exit(KEEP_DIR + "keep16","north","@@block");
    add_exit(KEEP_DIR + "keep16","north",0);
    add_exit(KEEP_DIR + "keep20","east",0);
}

/*
int
block()
{
    if(TP->query_prop(DRAKMERE_I_COWARD))
    {
        write("You are much too afraid of the wrath of the Creator to go back "+
        "there.\n");
        say(QCTNAME(TP)+" is too scared to go north.\n");
        return 1;
    }
    else
        return 0;
}*/
