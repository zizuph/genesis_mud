inherit "/d/Shire/room";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"



#define EXIT1 BB_DIR + "bh17","east",0,1


void reset_room();


void
create_room()
{
object door;
   set_short("You are standing in the front entrance of Brandy Hall in "+
      "Bucklebury in the Shire");
    set_long("You are standing in the front entrance of Brandy Hall in "+
      "Bucklebury in the Shire.  This entrance leads to the parlour that "+
      "the Master uses for entertaining when he doesn't want his visitors "+
      "to go traipsing through the entire burrow.\n");




    add_exit(EXIT1);

    door=clone_object(BUCK_DIR + "doors/bhdoor");
    door->set_door_id("brandy1");
    door->set_pass_command(({"w","west"}));
    door->set_other_room(BB_DIR + "buroad2");
    door->set_inside();
    door->move(this_object());


    reset_room();
}

void
reset_room()
{
}
