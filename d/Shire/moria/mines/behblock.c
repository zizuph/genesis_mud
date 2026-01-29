#include "defs.h"

object lump;

CONSTRUCT_ROOM {
    set_short("You are behind a huge dirty block");
    set_long("You are behind a huge dirty block. Dwarves have made a "+
	     "fireplace here.\n");
    add_item("block","It is huge.");
    add_item(({"fire","fire-place","fireplace"}),
	     "It seems deserted long time ago.");
    EXIT("dirtrock","east");
    reset();
}

RESET_ROOM {
    if (!lump || !present(lump)) {
      lump =  clone_object(MORIA_OBJ+"lump");
      lump -> move(this_object());
    } 
} 
