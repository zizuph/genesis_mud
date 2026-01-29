inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere1/"

create_cave()
{
  
  
  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(5);
  set_long("Just as you enter the tavern every person turns towards you and the "
         + "room is filled with silence. As the other guests see that you are just "
         + "another traveller who seeks company and comfort in the mug, they turn "
         + "theire back on you and starts talking loudly with eachother again.\n"
         + "As you look around the tavern you see that it is about half filled with "
         + "visitors sitting at the wooden tables, drinking ale. Standing against the "
         + "east wall you see a long oak bar, behind the bar a fat human is looking "
         + "interested at you. ");

  add_item("bar",BS(
    "Is is a long oak bar, everywhere on it you see greasy stains of old beer "
  + "and half-rotten food pieces. Standing at the far end of the bar you see "
  + "a humanoid figure clad in a long dark cloak.\n"
  + " "
  + "\n"));
  
  add_item("tables",BS(
    "Normal wooden tables large enough so that atleast eight dwarves can be sitting "
  + "at one at the time. "
  + "\n"
  + "\n"));
  
  add_item(({"figure"}), BS(
    "As you look closer at the figure, it turns its head and all you can see is "
  + "two small fires where the eyes once was. Maybe it is a good idea to leave "
  + "that stranger alone?.\n"
  + "\n"));
  
  add_item(({"human"}), BS(
    "This is probably the fattest bartender you've ever seen, it seems as if he "
  + "is stuck permanently behind the bar."
  + "\n"));
  
  
  add_exit(CAVE_DIR + "lm1c66","west",0,1);

}
