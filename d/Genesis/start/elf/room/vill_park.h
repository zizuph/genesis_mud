/*
 * Some standard definitions for the rooms in the village park:
 */

#define VILL_PARK_NAT_SHORT "In the Greenoaks Park"
#define VILL_PARK_FOR_SHORT "In a park"

#define VILL_PARK_NAT_LONG \
  "You are standing in the park, surrounded by huge oaks, under which " + \
  "soft, green grass gently billows. Here and there are flowering " + \
  "bushes, and towards the center of the park " + \
  "you can glimpse the House of Meditation.\n"
#define VILL_PARK_FOR_LONG \
  "You are standing in the park, surrounded by huge oaks, under which " + \
  "soft, green grass gently billows. Here and there are " + \
  "bushes, and further into the park " + \
  "you can glimpse a white marble building.\n"

/*
 * Room items:
 */

#define HOUSE_ITEM ({"house", "building", "marble building", "temple", \
		     "meditation house", "house of meditation"})
#define HOUSE_NDESC \
  "The House of Meditation is a circular building of white marble. The " +\
  "red granite roof streches out to an outer circle of marble pillars " +\
  "surrounding the walls. Arched doorways leads to the interior hall, and " +\
  "high, narrow window-openings gives it air and light.\n"
#define HOUSE_FDESC \
  "It is a circular, temple-like building of white marble, with " +\
  "red granite roof and marble pillars. " +\
  "It has arched doorways and " +\
  "high, narrow window-openings.\n"

#define PARK_ITEM ({"park", "oaks", "oak"})
#define PARK_NDESC \
  "In the park thrives the oaks that has given the village its name. The " +\
  "current crop is reaching its most majestic and beautiful age, and the " +\
  "garderners have all reason to be satisfied with their work.\n"
#define PARK_FDESC \
  "The park is filled with ancient, huge oaks, their crowns rich and green.\n"
  
#define BUSH_ITEM ({"bush", "bushes", "flower", "flowers"})
#define BUSH_NDESC \
  "The bushes blooms with rich and colourful exotic flowers. The " +\
  "gardeners have selected each one " +\
  "from a faraway location according to what " +\
  "beneficial influence its precense has on the resting mind.\n"
#define BUSH_FDESC \
  "The bushes are filled with colourful flowers.\n"

#define HOUSE_FAR_DESC "You have to get closer to it first.\n"
#define HOUSE_FAR_STD_ITEM \
  add_cmd_item(HOUSE_ITEM, \
	       ({"enter", "go"}), \
	       ({HOUSE_FAR_DESC, HOUSE_FAR_DESC}))

#define VILL_PARK_STD_ITEMS \
  add_item( PARK_ITEM,  N_KNOW(WRAP( PARK_NDESC), WRAP( PARK_FDESC)));   \
  add_item( BUSH_ITEM,  N_KNOW(WRAP( BUSH_NDESC), WRAP( BUSH_FDESC)));   \
  add_item(HOUSE_ITEM,  N_KNOW(WRAP(HOUSE_NDESC), WRAP(HOUSE_FDESC)))
