
/* 
 * Common board room for the cadets.  
 */ 

inherit "/std/room"; 

#include "cadet.h"


void
create_room()
{
    set_short("Common board room"); 
    set_long("Common board room.\n"); 

    add_exit(GC_STARTROOM, "start"); 

    clone_object("/d/Genesis/obj/board")->move(this_object()); 
}

