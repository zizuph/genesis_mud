/*
 * Some standard definitions for the rooms in the cove
 */


#define LOOKOUT ROOMDIR + "cove_1"

/*
 * Room items:
 */


#define WIND_ITEM ({"wind"})
#define WIND_DESC \
  "It is not blowing much, but it isn't calm either.\n"

#define COVE_ITEM ({"cove", "small cove", "sheltered cove"})
#define COVE_DESC \
  "The cove is a narrow, but deep inlet, cutting into the coastline here.\n"

#define LIMESTONE_ITEM ({"limestone", "stone", "bed-rock", "bedrock"})
#define LIMESTONE_DESC \
  "It is a relatively soft, pale grey sedimentary species of rock. It seems "+\
  "to be prevalent here.\n"

#define PIER_ITEM ({"pier", "small pier"})
#define PIER_DESC \
  "The piers are small, but sturdy, built out of wood by someone who clearly knew "+\
  "his business.\n"

#define WATER_ITEM ({"water", "waters"})
#define WATER_DESC \
  "The water is calm inside the cove, and seems to be rather deep.\n"
#define WATER_ADESC \
  "It is by far too salty for your taste.\n"


#define COVE_STD_ITEMS \
  add_item(LIMESTONE_ITEM, WRAP(LIMESTONE_DESC));   \
  add_item(     PIER_ITEM, WRAP(     PIER_DESC));   \
  add_item(    WATER_ITEM, WRAP(    WATER_DESC));   \
  add_item(     COVE_ITEM, WRAP(     COVE_DESC));   \
  add_item(     WIND_ITEM, WRAP(     WIND_DESC));   \
  add_cmd_item(WATER_ITEM, "drink", WRAP(WATER_ADESC))

