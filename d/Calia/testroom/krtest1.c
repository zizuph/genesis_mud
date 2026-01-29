
/* Kroug room test room */

#include "testroom.h"
inherit "/d/Calia/std/kr_room";


object *krougs = allocate(3);

void
bring_krougs()
{
     int i;

     for(i = 0; i < sizeof(krougs); i++) 
         if (!objectp(krougs[i])) {
            krougs[i] = clone_object("/d/Calia/mountain/monsters/kroug_tough1");
            krougs[i]->arm_me();
            krougs[i]->move_living("into the kroug test room", this_object());
         }
}


void
create_room()
{
    set_short("Kroug test room 1");
    set_long("This is kroug test room 1.\n");

    add_exit(TR+"krtest2", "east");

    bring_krougs();
}

