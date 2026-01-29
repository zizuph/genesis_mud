/* gldchest.c: Gladiator chest room: Serpine, 12-04-96. */
/* comments: 14 Juli 2001 - fixed the room desc some to fit in with the new rack. */
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
  chest = clone_object(PSION_OBJ+"chest2.c");
  chest->move(TO); 
  chest = clone_object(PSION_OBJ+"chest3.c");
  chest->move(TO); 
 }
}

create_room()
{
    set_short("equipment cavern");
    set_long("This is a small cavern designed to store equipment. "
            +"The walls have been carved into racks and the middle of "
            +"cavern is set up to hold armours.\n");
        
    add_exit(PSION_ROOM + "hallway1.c", "east", 0, 1, 1);
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
 
 num = chest->kick_chest();
 
 if     (num < 1)  {x += "nothing falls out.\n";}
 else if(num == 1) {x += "something falls out.\n";}
 else              {x += "some equipment falls out.\n";}

 write("You kick the chest and "+x);
 say(QCTNAME(this_player()) + " kicks the chest and "+x);

 return 1;
}
