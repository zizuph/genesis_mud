inherit "/d/Shire/eastroad/villagemaker";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "buroad2","north",0,1
#define EXIT2 BB_DIR + "buroad5","southwest",0,1



void
create_room()
{
object door;
   

   areaname = "Bucklebury";
   land = "Buckland";
   areatype = 2;
   areadesc = "road";
 

    extraline = "You are standing outside of the south entrance to "+
    "Brandy Hall. This entrance leads to a separate part of the hall, "+
    "for those who wish to use the great library here. The master of the "+
    "hall put in this door long ago, so that he wouldn't have other "+
    "hobbits traipsing through the entire hall when they just wanted to "+
    "read a book or two. There are still many windows in this part of the "+
    "hall.";
    add_item(({"road"}),"The road is dirt and a bit of gravel, and looks "+
      "very travelled.\n");
    add_item(({"windows","window"}),"The windows are so shiny and sparkling "+
      "that it is almost impossible to see through them.\n");

   add_exit(EXIT1);
   add_exit(EXIT2);
    door=clone_object(BUCK_DIR + "doors/bhdoor");
    door->set_door_id("brandy1");
    door->set_pass_command(({"e","east"}));
    door->set_other_room(BB_DIR + "bh1");
    door->move(this_object());

   
   make_the_room();
}





