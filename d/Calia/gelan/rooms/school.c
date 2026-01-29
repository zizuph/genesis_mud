
/* 
       School of Gelan

       Coded by Maniac@Genesis, March 1997

       Copyright (C) Miguel Leith 1997
*/ 


#include "defs.h"
#include "room.h"
#include CADET_INCLUDE
#include <stdproperties.h>

inherit GELAN_BASE_ROOM;

#undef CLASSROOMS 

#define ELEMENTAL_ACADEMY "/d/Calia/guilds/academics/school/joinroom"

public void
create_gelan_room()
{
     set_short("School of Gelan");        

     set_long("You are in the foyer of the school of Gelan. " + 
       "Large windows open to the square are letting the " +
       "sunlight in, which reflects cleanly on the black-tiled " +
       "neatly swept floor. There are glass cabinets against " +
       "the walls displaying artwork and trophies of star " +
       "students. Corridors lead off to the classrooms on this " +
       "floor and a stairway leads up to those above. " + 
#ifndef CLASSROOMS 
       "It is not possible for you to visit the classrooms yet though. "  +
#endif
       "Occasionally young students pass through running errands. " + 
       "It's rather quiet around here so you guess that classes must " +
       "be in session right now. To the south is the training room of the " +
       GC_GUILD_NAME + ", where older students are prepared " +
       "for a warrior's life. To the north you notice a refurbished "
     + "marble doorway leading to the Academy of Elemental Arts.\n"); 

     add_prop(ROOM_I_INSIDE, 1);  

     add_item(({"cabinets", "display cabinets", "glass cabinets", 
                "trophies", "artwork", "cabinet"}), 
          "Among the trophies and artwork on display in the " +
          "cabinets are a Junior Fireball Golden Flame trophy, " + 
          "a `before and after' portrait of one of Raspatoon's guinea pigs " +
          "and a fine sketch of the old tree in the square before it was " +
          "cut down.\n");  

     add_item("square", "It's outside if you want a look.\n"); 

     add_item(({"training room", "train room", "cadet room"}), 
            "You can't see much from here. Why don't you go in " +
            "and have a look?\n"); 

     add_item(({"wall", "walls"}), "There are display cabinets " +
           "up against them.\n"); 

     add_item(({"tiles", "black tiles", "floor"}), 
           "The floor tiles themselves are as neat, clean and dull as a " +
           "school uniform.\n"); 

     add_item(({"corridor", "corridors"}), 
          "Who knows what horrors lurk behind the dull grey doors in " +
          "school corridors?\n"); 

     add_item("stairway", "It leads up to yet more classrooms. " +
          "This is not a small school.\n"); 

     add_item(({"windows", "large windows", "window"}), 
          "How nice, they are letting the sunlight in. " +
          "Students appreciate small mercies like these of course.\n"); 

     add_exit(GELAN_ROOMS+"square_eastend_n", "west"); 
     add_exit(GC_TRAINROOM, "south");
     add_exit(ELEMENTAL_ACADEMY, "north"); 
}


