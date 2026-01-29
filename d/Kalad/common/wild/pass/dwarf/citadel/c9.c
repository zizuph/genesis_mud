inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Bruno */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,1);
   set_short("On the inside of the courtyard's gates");
   set_long("Your walking between the courtyard's wall and the north"
           +"west corner of a building.  The wall turns here to the east" 
           +" and the soft glow from the courtyard casts your shadow upon"
           +" it.\n");
   add_item(({"building"}),
            "The building is made up of large marble blocks that have"
           +" been so highly polished you can see youself in them.\n"); 
   add_item(({"wall"}),        
            "The inside of the courtyards wall made up of granite"
           +" blocks cut to fit together so exact that they need"
           +" no cements.\n");
   add_item(({"shadow"}),
            "Out of the corner of your eye you notice your shadow is"
           +" not mimicing your every move as it should.\n");
   add_exit(CPASS(dwarf/citadel/c8),"east");
   add_exit(CPASS(dwarf/citadel/c10),"south");
}


