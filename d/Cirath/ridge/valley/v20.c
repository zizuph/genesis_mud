/*
* Created by: Luther
* Date: 19 August 2001
*
* File: /d/Cirath/ridge/valley/v20.c
* Comments: Valley outside of Tyr
*/

#pragma strict_types
#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"
#include "/d/Cirath/desert/tyrsouth/defs.h"
#define COR RIDGE_OBJ+"v_corpse.c"

object cor;

void
reset_room()
{


    if(!cor)
    {
        cor = clone_object(COR);
        cor->move(this_object());
    }
}


void
create_room()
{

    set_short("Sand Valley");
    set_long("What was once the end of the valley, now looks to be almost "
    	+"the beginning.  A large cliff to the southwest has collapsed, "
    	+"and you can see that the valley now extends to the southwest "
    	+"further.  A large cross is planted firmly in the ground here, "
    	+"a reminder of the stark and fatal nature of the wild Athasian "
    	+"wastes.\n");

        cor = clone_object(COR);
        cor->move(this_object());
     add_item("cliff","Where it once was is now a clear path heading to "
     	+"the southwest.\n");
     	
        OUTSIDE
        LIGHT
        ADD_SUN_ITEM

        add_exit(RIDGE_VALLEY+"v18.c","northeast",0,8,0);
         add_exit(SOUTH + "p5","southeast");
        reset_room();

}

