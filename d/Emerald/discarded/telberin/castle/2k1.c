/*
 * 2k1.c
 * First room on the second floor of Castle Telberin
 * Re-description by Alaron August 16, 1996
 */
#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Lamplit hallway");
    set_long("   The long, lamplit hallway stretches out throughout "+
        "the second floor of the castle to the south where it "+
        "turns a corner heading east. The thick, smooth walls are "+
        "an exquisite shade of emerald green stone. Their green color "+
        "seems to glow and radiate a green and orange tint throughout "+
        "the entire hall as the light flickers from the hanging "+
        "silver lamps. The effect is calming and reassuring, and "+
        "the hallway feels safe. There are trophies, plaques, paintings "+
        "and other decorations on the walls. This, in addition to "+
        "the luxurious dark carpet on the marble floor, creates a "+
        "dazzlingly rich effect. A set of stone stairs descends "+
        "out of the lamplight to a lower level.\n\n");
    
    add_item( ({"stairs", "down", "set of stairs"}),
             "The staircase descends down around a small bend in the "+
             "wall, out of the lamplight to the floor below.\n");

    add_item(({"lamp", "lamps", "silver lamps","hanging lamps",
	       "hanging silver lamps", "pegs"}),
	     "Ornate, carved lamps hang from pegs jutting out of the "+
	     "fabulous green stone walls. They provide a flickering yellow "+
	     "light which causes the walls to seem as if they are "+
	     "glowing. The effect of the lamplight is reassuring and "+
	     "comforting, making the entire hallway feel safe.\n");

    add_item("trophies","The trophies are things such as orc swords, "+
	     "artwork from other Kingdoms, hand-made sculptures, etc.\n");
    add_item("carpet","The rich carpet is made from the purest wool in the "+
	     "area.\n");

    add_item( ({"plaques", "paintings", "decorations"}),
	     "Plaques, paintings and other decorations adorn the "+
	     "walls, creating a warm, comforting feeling about the "+
	     "entire place.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
    
    add_exit(CASTLE_DIR + "1k10","down",0);
    add_exit(CASTLE_DIR + "2k2","south",0);
}

