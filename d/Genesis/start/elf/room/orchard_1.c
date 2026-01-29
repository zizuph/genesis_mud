#include "../stddefs.h"
#include "/sys/stdproperties.h"

#pragma save_binary

inherit ELFROOM;

#define SOUTH   ROOMDIR + "trade_road_5"

#define SHORT  "In an apple orchard."

#define NAT_LONG \
  "You are in an orchard, filled with apple trees. Here apples grow all the "+\
  "year, so some trees are in bloom, some carry unripe fruit, while others "+\
  "have fresh, juicy, ripe apples.\n" + \
  "It is customary to make a small sacrifice to the spirits of the trees "+\
  "before picking any fruit.\n" +\
  "Through the trees you can glimpse the Trade Road in the south.\n"
#define FOR_LONG \
  "You are in an orchard, filled with apple trees. The odd thing is that "+\
  "not only are there trees carrying ripe, juicy apples, but also trees "+\
  "in bloom and trees carrying unripe fruit. They don't seem to follow "+\
  "proper seasons.\n" +\
  "Through the trees you can glimpse the a road in the south.\n"
  
#define WIZINFO \
  "Here you can pick apples, but they only give nourishment if you first " +\
  "have sacrificed some money by putting them into the \"altar\" stone.\n" +\
  "Elven players are given a clue to this in the room description, but " +\
  "not others."


#define TREE_ITEM ({"tree", "trees", "apple tree", "apple trees"})
#define TREE_DESC \
  "The apples trees are old and gnarly. " +\
  "Some have features that seem oddly humanoid in appearance, and now and "+\
  "then a branch moves in a way not entirely explainable by the wind.\n"

#define BLOOM_ITEM ({"bloom", "flower", "flowers", "apple flowers"})
#define BLOOM_DESC \
  "The flowers in some of the apple trees are pale pink and white.\n"

#define APPLE_ITEM ({"apple", "apples", "fruit", "fruits", \
		     "ripe apple", "unripe apple", "fresh apple", \
		     "juicy apple"})
#define APPLES_AVAILIABLE_DESC \
  "The trees are filled with apples, ready to be picked.\n"
#define APPLES_UNAVAILIABLE_DESC \
  "The trees are filled with apples, but all grow without your reach.\n"

#define APPLE_GOTTEN \
  "You pick an apple from a nearby tree.\n"
#define BAD_APPLE_GOTTEN \
  "You find that you have picked yourself an unripe apple. Weird, that "+\
  "was not what you intended to do.\n"
#define APPLE_NOT_GOTTEN \
  "You find no apple within reach.\n"

#define DONT_SACRIFICE \
  "Well, how are you going to do that?\n"


int    avail_bad_apples;
object altar = 0;
  
create_room()
{
  set_short(SHORT);
  set_long(N_KNOW(WRAP(NAT_LONG), WRAP(FOR_LONG)));
  
  add_item( TREE_ITEM, WRAP( TREE_DESC));
  add_item(BLOOM_ITEM, WRAP(BLOOM_DESC));
  add_item(APPLE_ITEM, "@@apple_desc@@");

  add_cmd_item(APPLE_ITEM, "pick", "@@get_apple@@");
  add_cmd_item(APPLE_ITEM, "take", "@@get_apple@@");
  add_cmd_item(APPLE_ITEM,  "get", "@@get_apple@@");

  STD_WIZINFO;

  add_exit(SOUTH, "south", 0);
  tie_to_map(CENTER_SQUARE, CENTER_X, 4, CENTER_Y, 2);

  stock();
}

reset_room()
{
  stock();
}


stock()
{
  avail_bad_apples = 30;

  if (!altar || !present(altar, this_object())) {

    if ((altar = clone_object(OBJDIR + "apple_altar")) == 0 ||
	altar->move(this_object(), 1) != 0) {
      notify(MAINTAINER,
	     "The orchard " + file_name(this_object()) + 
	     "could not load its altar.\n");
    }
  }

  restock_object(MONSTERDIR + "butterfly", 3, "butterfly");
}

init()
{
  ::init();
  add_action("do_sacrifice", "sacrifice");
  add_action("do_sacrifice", "make sacrifice");
}


wizinfo()
{
  return WRAP(WIZINFO);
}

string apple_desc()
{
  if (avail_bad_apples > 0 || altar->balance(this_player()) > 0)
    return WRAP(APPLES_AVAILIABLE_DESC);
  else
    return WRAP(APPLES_UNAVAILIABLE_DESC);
}

string get_apple()
{
  object obj;
  int amount;

  seteuid(getuid(this_object()));

  amount = altar->balance(this_player());
  if (amount > 0) {

    if((obj = clone_object(OBJDIR + "apple")) != 0 &&
       obj->move(this_player()) == 0) {
      obj->add_virtue(amount);
      altar->withdraw(this_player(), amount);
      
      return WRAP(APPLE_GOTTEN);
    } 
  } else {
    
    if (avail_bad_apples > 0 &&
	(obj = clone_object(OBJDIR + "bad_apple")) != 0 &&
	obj->move(this_player()) == 0) {

      avail_bad_apples--;

      return WRAP(BAD_APPLE_GOTTEN);
    } 
  }
  
  return WRAP(APPLE_NOT_GOTTEN);
}

int do_sacrifice(string arg)
{
  notify_fail(WRAP(DONT_SACRIFICE));
}