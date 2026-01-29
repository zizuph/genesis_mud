// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

object obj;

void reset_room();

void
create_noble_room()
{
    set_short("At the top of a tower");
    set_long("You are now at the top of the tower. You can see "+
        "all of Kabal from this height. You see the streets, the "+
        "people and the forests, mountains and sea. It is all very "+
        "beautiful.\n");
  
    add_item("streets","The streets of Kabal, very dirty except in "+
        "the noble district.\n");
    add_item("people","So many people, mostly human, but a few "+
        "demi-humans about.\n");
    add_item("forest","Lush green forests that stretch on and on.\n");
    add_item("mountains","The mountains are so huge, that they seem "+
        "to rise into the heavens.\n");
    add_item("sea","The serene blue waves roll across the sea, and "+
        "the light of the eternal Kalad sun sparkles off it.\n");

    INSIDE;

    add_exit(NOBLE + "castle/c57", "down", 0);

    reset_room();
}

void
reset_room()
{
    obj = clone_npcs(obj, NOBLE + "npc/castle_guard");
}

