/*
 * Some standard definitions for the rooms in the lair of the gibberers:
 */


#define GIBBER_LAIR_NAT_SHORT "In the lair of the gibberers"
#define GIBBER_LAIR_FOR_SHORT "Below the cairn"

#define GIBBER_LAIR_NAT_LONG \
  "You are in a small, dark, narrow passage below ground. The "+\
  "characteristic acrid stench of gibberers is everywhere.\n"

#define GIBBER_LAIR_FOR_LONG \
  "You are in a small, dark, narrow passage below ground. An acrid "+\
  "stench of gibberers fills the air everywhere.\n"


/*
 * Room items:
 */

#define WALL_ITEM ({"wall", "walls", "ceiling", "floor", "passage"})
#define WALL_DESC \
  "The passage is dug out of the fat, moist, black earth. Here and "+\
  "there it bends around huge rocks that projects into the passage, "+\
  "and smaller stones and bones may be seen in the earth.\n"

#define SMELL_ITEM ({"smell", "stench", "air"})
#define SMELL_DESC \
  "It is not nice. It helps if you don't think about it too much.\n"

#define STONE_ITEM ({"stone", "stones", "rock", "rocks"})
#define STONE_DESC \
  "The stones are round-edged pieces of grey or grey-pink granite.\n"

#define BONE_ITEM ({"bone", "bones", "skeleton"})
#define BONE_DESC \
  "The bones comes from something vaguely, but not very, humanoid. They "+\
  "seem to be very old.\n"

#define GIBBER_LAIR_STD_ITEMS \
  add_item(SMELL_ITEM, WRAP(SMELL_DESC));   \
  add_item(STONE_ITEM, WRAP(STONE_DESC));   \
  add_item( BONE_ITEM, WRAP( BONE_DESC));   \
  add_item( WALL_ITEM, WRAP( WALL_DESC))

/*
 * Room properties:
 */

#define GIBBER_LAIR_STD_PROPERTIES \
  add_prop(ROOM_I_INSIDE, 1);      \
  change_prop(ROOM_I_LIGHT, 0)
