/* gldchest.c: Gladiator chest room: Serpine, 12-04-96. */

#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"
#include <macros.h>

object chest;

void
reset_room()
{
 if (!present("chest", TO))
 { 
  chest = clone_object(PSION_OBJ+"chest.c");
  chest->move(TO); 
 }
}

create_room()
{
    set_short("equipment hall");
    set_long("This rather barren room is strewn with the debris left "
            +"behind by warriors both past and present. Since its only "
            +"purpose is to keep the pathway to the east clear of "
            +"refuse that might be tripped over, it has no shelves or "
            +"racks. Indeed it only has one permanent fixture.\n");
        
    add_exit(PSION_ROOM + "gldboard.c", "east", 0, 1);
    add_prop(ROOM_I_NO_CLEANUP,1);

    reset_room();
}



init()
{
 ::init();
 add_action("kick","kick");
}

public int
kick(string str)
{
 int num;
 string x = "";

 if((str != "chest") | (!present("chest", TO)) | !(chest)) return 0;
 
 num = chest->hooboo();
 
 if     (num < 1)  {x += "nothing falls out.\n";}
 else if(num == 1) {x += "something falls out.\n";}
 else              {x += "some equipment falls out.\n";}

 write("You kick the chest and "+x);
 say(QCTNAME(this_player()) + " kicks the chest and "+x);

 return 1;
}
