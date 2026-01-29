#include "defs.h"
inherit CRYPT_ROOM;

/* SARR */

object chest;
object scrip;
void reset_room();


void
create_room()
{
    ::create_room();
    set_long("You are at a dead end in the tunnel. Here, it opens "+
    "up into a small chamber. It is dark and dank. Along the "+
    "walls you see blood. In the center, there is a stone altar.\n");
    add_item("blood","It is dried blood.\n");
    add_item("altar","It is made of stone.\n");
    add_exit(FOREST_DIR + "crypt3","north");
    reset_room();
}

void
reset_room()
{
       chest->remove_object();
       scrip = clone_object(COMMON_OBJ_DIR + "scripture");
       chest = clone_object(FOREST_DIR + "chest");
       chest->move(TO);
       scrip->move(chest,1);
}

