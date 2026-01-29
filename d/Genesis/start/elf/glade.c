/*
 *  Glade 
 */

#include "stddefs.h"
#include <ss_types.h>
#include "defs.h"
#include "desc_include/trade_road.h"

#pragma save_binary

inherit ELFROOM;

#define SHORT "In a glade with a tall tree"

#define LONG \
  "You have entered a glade with beautiful flowers " + \
  "and bushes growing in strange and intricate patterns.\n" + \
  "In the middle of the glade stands a tall tree with silver leaves, and " + \
  "a road passes through the glade, going from south to northwest (or is " + \
  "it the opposite), inviting travel, while " + \
  "in all other directions " + \
  "the forest is thick and threatening.\n"

#define LEAF_ITEM ({"leaves", "leaf", "silver leaf", "silver leaves"})
#define LEAF_DESC \
  "The leaves of the tree are all covered with soft, "+ \
  "fine hairs, giving them their silver look. No, they "+ \
  "aren't metal, if that was what you thought...\n"

#define FLOWER_ITEM ({"flower", "flowers"})
#define FLOWER_DESC \
  "There are many different colours of flowers here. Almost too many " + \
  "to count. Most of the flowers have a pleasant smell, filling the " + \
  "air with a refreshing fragrance.\n"

#define TREE_ITEM ({"tree"})
#define TREE_DESC \
  "The tall tree doesn't look like any other tree you have seen. " + \
  "It has silver leaves and is twice as high as any other tree " + \
  "in the forest. Its shade isn't very deep because the sunlight is " + \
  "reflected in all the leaves.\n"

#define BUSH_ITEM ({"bush", "bushes"})
#define BUSH_DESC \
  "There are many low bushes in the glade that form intricate " + \
  "patterns with the flowers.\n"

#define PATTERN_ITEM ({"pattern", "patterns"})
#define PATTERN_DESC \
  "The patterns don't form anything you can recognize, they are just " + \
  "pretty to look at.\n"

void stock();

void create_room()
{
  set_short(SHORT);
  set_long(WRAP(LONG));

  add_item(   LEAF_ITEM, WRAP(   LEAF_DESC));
  add_item( FLOWER_ITEM, WRAP( FLOWER_DESC));
  add_item(   TREE_ITEM, WRAP(   TREE_DESC));
  add_item(   BUSH_ITEM, WRAP(   BUSH_DESC));
  add_item(PATTERN_ITEM, WRAP(PATTERN_DESC));
  TRADE_ROAD_STD_ITEMS;
  
  add_exit(ROOMDIR + "cove_1",   "northwest", 0);
  add_exit(ROOMDIR + "entrance", "south",     0);

#if USE_MAP
  add_exit("@@map_file|x186.6y554.7","east",0);
  add_exit("@@map_file|x186.4y554.7","west",0);
#endif  

  add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */

  stock();
}

void stock()
{
  object obj;
  restock_object(OBJDIR+"portal", 1, "portal");

  if ((obj = present("portal", this_object())) != 0)
  //   obj->set_destination("/d/Genesis/start/human/town/jetty2");
    obj->set_destination("/d/Krynn/solace/new_village/house/house7");
}

reset_room()
{
  stock();
}


void init()
{
  ::init();
    add_action("go_up", "climb");
}

int go_up(string str)
{
  notify_fail("Climb what?\n");
  if (!str ||
      !parse_command(str, this_object(), " [silver] / [tall] 'tree'"))
    return 0;
  
  if (this_player()->query_race() == "elf")
    write("You nimbly climb up the trunk of the tree.\n");
  else
    if ((random(100) - 10) < this_player()->query_skill(SS_CLIMB))
      /* We managed to climb safely */
      write("You manage to safely climb up the tree trunk.\n");
    else {
      /* Hit the player with the ground */
      say(QCTNAME(this_player()) + " tries to climb the tree, but looses\n" +
	  this_player()->query_possessive() +
	  " grip and falls to the ground with a mighty crash.\n");
      tell_room(STAND_DIR + "tree",
		"You hear a mighty crash from below.\n", this_player());
      write("You loose your grip when trying to climb up the trunk of the tree\n" +
	    "and fall to the ground with a mighty crash.\n");
      this_player()->reduce_hit_point(this_player()->query_prop(CONT_I_WEIGHT) / 100);
      return 1;
    }
  
  this_player()->move_living("up the tree", STAND_DIR + "tree");
  return 1;
}
