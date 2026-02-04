/* 
 * std room for the Order of the White
 * 
 * Shinto 012800
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>
#include <stdproperties.h>

int ext_sconce = 0;

public void
create_terel_room()
{
    INSIDE;
    add_item(({"walls","wall","stone walls","stone wall","stones","stone",
               "white stone","white stones","white stone walls",
               "white stone wall"}), 
               "The whole keep is made from this white stone. It's seems "+
               "stronger then any other type of rock. It shines as if it "+
               "were white marble and is just as smooth. "+"@@sconce@@");
    add_item(({"floor","ground"}), "The floor is made from the same stone as "+
               "the rest of the keep. It's smooth and shines as if it were "+
               "white marble.\n");
    add_item(({"lantern","silver lantern"}),"@@sconce@@");

    add_cmd_item(({"lantern","light"}),
                 ({"get","take"}),
                   "You cant remove the lantern or the fire.\n");

    add_cmd_item(({"lantern","light"}),
                 ({"extinguish"}),
                   "@@extinguish");

    add_cmd_item(({"lantern","light"}),
                 ({"light"}),
                   "@@light_sconce");
}

string
sconce()
{
   if (ext_sconce == 1)
   {
     return "A silver lantern can be seen attached to the wall.\n";
   }
     return "A silver lantern can be seen attached to the wall, " +
            "which provides light.\n";
}
     

public int
extinguish()      // Extinguish the sconce.
{
   if (ext_sconce == 1)
   {
       NF("The lantern isn't lit.\n");
       return 0;
   }

   ext_sconce = 1;  // Extinguish the wall sconce.
   write("Using the iron lid, you snuff out the burning " +
         "flame within the lantern.\n");
   say(QCTNAME(TP) + " snuffs out the burning flame by closing " +
         "the iron lid on the lantern.\n");

   DARK;            // add darkness to the room.

   return 1;
}


public int
light_sconce()        // Light the sconce
{
    if (ext_sconce == 0)
    {
       NF("The lantern is already lit.\n");
       return 0;
    }
    if (ext_sconce == 1)   // The sconce is not lit.
    {
       write("You light the wick within the lantern.\n");
       say(QCTNAME(TP) + " lights the lantern.\n");

       add_prop(ROOM_I_LIGHT, 1);  // Add light to the room.
       ext_sconce = 0;    // add light to the room.
       return 1;
    }
    return 1;
}
