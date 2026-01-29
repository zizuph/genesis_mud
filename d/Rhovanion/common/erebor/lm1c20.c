inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

create_cave()
{
  object door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(2);
  set_long("You are standing in eastern parts of the Great Hall. "
         + "The hall is huge, and lit by oil-lamps leaving "
         + "you with a nice cosy feeling. There is a broad stairway "
         + "leading down here. Alas, there is a sign barring the access "
         + "to the latter. Flanking the sign there are two Dvarwen "
         + "Guards, fully armed and wearing that typical grim look. The "
         + "vast hall continues west, northwest and southwest. "
         + "Through an opening in the east wall you can see "
         + "a well-lit corridor leading towards the East Gate.");

  add_item("sign","The sign reads:\n\nClosed until further notice.\n\n"
         + "Dwimil, Captain of the Guards.\n");

  add_exit(ERE_DIR + "lm1c18","west",0,1);
  add_exit(ERE_DIR + "lm1c21","east",0,1);  
  add_exit(ERE_DIR + "lm1c19","northwest",0,1);
  add_exit(ERE_DIR + "lm1c17","southwest",0,1);
  add_exit(ERE_DIR + "lm1c20","down","@@down_move",1);
}

down_move()
{
  tell_object(TP,"As you try to descend the guards moves to bar the way. "
          + "Obviously they don't want you down there.\n");
  tell_room(ERE_DIR + "lm1c20",QCTNAME(TP)+" tries to go down the "
          + "stairs but is stopped by the guards.\n",TP);
  return 1;
}
