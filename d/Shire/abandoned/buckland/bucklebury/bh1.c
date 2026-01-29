inherit "/d/Shire/room";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"



#define EXIT1 BB_DIR + "bh2","south",0,1
#define EXIT2 BB_DIR + "bh4","east",0,1
#define EXIT3 BB_DIR + "bh4","north",0,1


void reset_room();


void
create_room()
{
object door;
   set_short("You are standing in the front entrance of Brandy Hall in "+
      "Bucklebury in the Shire");
    set_long("You are standing in the front entrance of Brandy Hall in "+
      "Bucklebury in the Shire.  The front hall is huge, extending "+
      "farther to the south, where there are other doors leading outside. "+
      "There are other rooms, of course, which can be found by going "+
      "either north or east.\n");




    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);

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
