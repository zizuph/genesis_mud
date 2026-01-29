inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>


int
query_prevent_snoop()
{
   return 1;
}

void
create_room()
{
   
   set_short("A loft above Amelia's workroom");
   set_long("You are in a room that looks like a loft. There is "+
      "a carefully concealed runged ladder that goes down. "+
      "The walls here appear thick and sound-proof, except for the "+
      "west side, which is a large balcony overlooking the sea. "+
      "You can hear the rhythmic pounding of waves on the "+
      "shore...else it is very still here. It is light and clean "+
      "and the air feels fresh and invigorating. In one "+
      "corner is a futon, which appears very comfortable.\n");
   
   add_prop(ROOM_I_LIGHT, 1);
   add_prop(ROOM_I_IS, 1);
   add_prop(ROOM_I_INSIDE, 0);
   add_prop(ROOM_M_NO_TELEPORT, 1);

   add_exit("/d/Calia/amelia/workroom.c", "down", 0,0);
   
   
}
