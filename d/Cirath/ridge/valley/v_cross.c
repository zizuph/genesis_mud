/*
* Created by: Luther
* Date: 19 August 2001
*
* File: /d/Cirath/ridge/valley/v20.c
* Comments: Valley outside of Tyr
*/

#pragma strict_types
#pragma save_binary

#include "defs.h"
#define COR RIDGE_OBJ+"h_corpse.c"
inherit BASE_VALLEY;

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
create_valley()
{

  	set_short("On top of cross");
  	set_long("You stand on the cross section high above the ground. Looking "
  		+"towards the north you can see the valley quite easily.\n");
 	
        cor = clone_object(COR);
        cor->move(this_object());
        
  	add_exit(RIDGE_VALLEY+"v20.c","down",0,5,0);
  	reset_room();
}
