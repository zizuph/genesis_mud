/*
 * A beach in Roke by Ckrik, 9/2003
 */
#include "defs.h"

inherit ROKE_BEACH + "std/base_beach_sandy.c";
 
void
create_beach()
{ 
    add_my_desc("\n");
    add_exit(ROKE_BEACH+"rooms/beach09","northeast");
    add_exit(ROKE_BEACH+"rooms/beach07","south");
    reset_room();

    add_npc(THWIL + "monster/mercenary");
}

void
reset_room() {
    string file = THWIL + "monster/mercenary";
    if (!random(2))
        return;
    
    if (!find_object(file) || sizeof(object_clones(find_object(file))) < 1) {
        setuid();
        seteuid(getuid());

        object ob = clone_object(file);
        ob->move_living("", this_object());
    }
}
