#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "fir_forest.h"

#pragma save_binary

inherit ELFROOM;

#define WEST    ROOMDIR + "trade_road_1"

/*
#define MAGESTONE "/d/Genesis/obj/wizquest/mage_stone"
*/

#define SHORT  "In a small clearing in the forest"

#define NAT_LONG \
  "Here is a small clearing in the forest. The vegetation is low and " + \
  "yellowish dry, and here and there the limestone bedrock is visible " +\
  "between bushes and tufts of grass. The air is warm, and a smell of " +\
  "dry grass lingers in the air.\n"
#define FOR_LONG \
  "You are standing in a small clearing in the dark fir forest. There are " +\
  "low bushes and some grass here.\n"

#define BUSH_ITEM  ({"bush", "bushes"})
#define BUSH_FDESC "Oh, its just some kind of low bushes.\n"
#define BUSH_NDESC \
  "Whenever the fall comes, these bushes will be filled with sloes.\n"

#define ROCK_ITEM ({"rock", "bedrock", "bed-rock", "ground", "limestone"})
#define ROCK_DESC \
  "The bedrock that is visible in patches has the characteristic gray, " + \
  "brittle, pockmarked surface that limestone exposed to sun and rain " + \
  "gets, but the yellowish white of the untouched stone still shines in " + \
  "scratches and newly eroded places. Cracks and holes in the rock " + \
  "provide a footing for the bushes and grass that grows here.\n" 

#define GRASS_ITEM ({"grass", "tuft", "tufts"})
#define GRASS_DESC \
  "The grass is short, dry, and covered with limestone dust, giving it " +\
  "a pale greyish-yellow colour. Many of the straws carry small seeds.\n"
  
create_room()
{
  set_short(SHORT);
  set_long(N_KNOW(WRAP(NAT_LONG), WRAP(FOR_LONG)));
  
  FIR_FOREST_STD_ITEMS;
  add_item( BUSH_ITEM, N_KNOW(WRAP(BUSH_NDESC), WRAP(BUSH_FDESC)));
  add_item( ROCK_ITEM, WRAP(ROCK_DESC));
  add_item(GRASS_ITEM, WRAP(GRASS_DESC));

  add_exit(WEST, "west", 0);
  tie_to_map(CENTER_SQUARE, 186, 6, 554, 5);

/*
  stock();
*/
}

/*
stock()
{
  object obj;
  if (!present("stone", this_object()) &&
      (obj = clone_object(MAGESTONE)) != 0)
    obj->move(this_object());
}
*/