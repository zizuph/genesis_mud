inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
   object door;
 
   add_prop(ROOM_I_INSIDE, 1);
   set_short("Entrance hall");
   set_long("   You have entered the Temple of the Doomed, "+
            "and find yourself standing in a cold, stonewalled entrance "+
            "hall. The temple itself lies to the east. The walls are "+
            "covered with uninterpretable signs and illustrations. There "+
            "is a constant humming in the air. It could be the humming of "+
            "the monks.\n\n");

   add_exit(TEMPLE_DIR + "hall", "east", "@@block");
   door=clone_object(TEMPLE_DIR + "doors/door1_b");
   door->move(this_object());
 
   add_item(({"wall","walls"}),"They are covered with uninterpretable "+
      "signs and illustrations.\n");
   add_item(({"uninterpretable signs","signs","sign","illustration",
            "illustrations"}),"The signs and illustrations are old, and look "+
      "strange to you, you don't bother\ntrying to work out what they are.\n");
}
 
int
block()
{
 write("Some monk stops you.\n" +
       "The monk says: Temple is currently closed. Come back later.\n");
 return 1;
}
