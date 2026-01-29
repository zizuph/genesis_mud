#include "../stddefs.h"
#include "/sys/stdproperties.h"

#pragma save_binary

inherit ELFROOM;

#define SOUTH    SHOREDIR + "path_1"

#define SHORT  "On a hot, sunny beach"

#define LONG \
  "You are on a beach filled with pale, fine sand, glittering in the "+ \
  "sunlight. Around you steep and inaccessible cliff walls rise, except "+ \
  "to the north, where the deep greenish blue sea beckons invitingly.\n" + \
  "There is, however, a small path cutting through the south cliff wall, "+\
  "climbing upwards, providing the only visible way out of here.\n"



#define PATH_ITEM ({"path"})
#define PATH_DESC \
  "It is small, and it rises sharply, but it does not seem that hard to climb.\n"

#define SEA_ITEM ({"sea", "wave", "waves", "ocean"})
#define SEA_DESC "The waves are calm and gently rolling.\n"

#define BEACH_ITEM ({"beach"})
#define BEACH_DESC "It is covered with fine sand.\n"

#define VEGETATION_ITEM ({"vegetation"})
#define VEGETATION_DESC "It is tropically green.\n"

#define CLIFF_ITEM ({"cliff", "cliffs"})
#define CLIFF_DESC "It is a sheer wall of night-black, hard stone.\n"

#define WALL_ITEM ({"wall", "walls"})
#define WALL_DESC "The cliff consists of night-black, hard rock.\n"

#define SAND_ITEM ({"sand"})
#define SAND_DESC "It is fine-grained and soft.\n"

#define CLIMB_WALL_DESC "The cliff walls are unscalable.\n"
#define CLIMB_PATH_DESC \
  "That would be much easier to do by just walking south.\n"
#define ENTER_SEA_DESC "You cannot do that (yet!!).\n"
  
create_room()
{
  set_short(SHORT);
  set_long(WRAP(LONG));
  
  add_item(      PATH_ITEM, WRAP(      PATH_DESC));
  add_item(       SEA_ITEM, WRAP(       SEA_DESC));
  add_item(     BEACH_ITEM, WRAP(     BEACH_DESC));
  add_item(VEGETATION_ITEM, WRAP(VEGETATION_DESC));
  add_item(     CLIFF_ITEM, WRAP(     CLIFF_DESC));
  add_item(      SAND_ITEM, WRAP(      SAND_DESC));

  add_cmd_item(WALL_ITEM + CLIFF_ITEM, "climb", WRAP(CLIMB_WALL_DESC));
  add_cmd_item(PATH_ITEM,              "climb", WRAP(CLIMB_PATH_DESC));
  add_cmd_item(SEA_ITEM, "enter", WRAP(ENTER_SEA_DESC));
  add_cmd_item(SEA_ITEM, "swim",  WRAP(ENTER_SEA_DESC));

  add_exit(SOUTH, "south", 0);

  stock();
}

reset_room()
{
  stock();
}

stock() 
{
  restock_object(OBJDIR + "caravan", 1, "caravan");
  restock_object(OBJDIR + "palm", 3 + random(3), "palm");
}