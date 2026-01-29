// file name: d/Avenir/common/outpost/chasm_south.c
// creator(s):  Kazz    March '95
// purpose:     Southern side of the chasm.
// revision history:
//
// * Lucius May 2009: Cleaned and updated for code move of 
// 	/d/Terel/dark/ to Avenir.
//
#pragma strict_types

inherit "/std/room";

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/common/outpost/cave.h"
#include "/d/Avenir/include/relation.h"

public int
check_exit(void)
{
    /* Warn them they are wearing out their welcome */
    if (IS_INFIDEL(TP))
    {
	write("A feeling of uneasiness weighs upon you, making you "+
	  "feel unwelcome.\n");
    }

    return 0;
}

public void
create_room(void)
{
    set_short("South of chasm");
    set_long( "The forboding chasm lies open to the north. A stone bridge "+
      "stretches out over the darkness to the opposite side. "+
      "Two towering flames light a dark fort crouching against the "+
      "northeast cavern wall.\n");

    FLAME;

    add_item(({"fort"}),
      "The fort is black and crouches against the cavern, it's "+
      "tall tower brushes the sloping cavern wall.\n" );
    add_item(({"chasm"}),
      "The chasm is at least fifty feet wide. The bottom "+
      "is smothered in darkness.\n");
    add_item(({"bridge"}),
      "The bridge seems newly constructed of tunnel rock.\n" );
    add_item(({"cavern", "cavern wall"}),
      "The cavern wall slopes down toward the fort.\n");
    add_cmd_item(({"chasm", "across", "across chasm"}),
      ({"jump", "cross"}),
      "If you tried to jump, you might fall to your death.\n");

    IN; LIGHT;

    add_exit(L1 + "chasm", "west");
    add_exit(OUTPOST + "bridge", "north", check_exit);
}

