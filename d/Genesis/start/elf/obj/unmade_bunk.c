#include <stdproperties.h>
#include <macros.h>
#include "../stddefs.h"

#pragma save_binary

inherit OBJECT;
inherit STRINGLIB;
inherit MISCLIB;

#define LONG \
  "The caravan's bunk is unmade, and the bedding is in a mess.\n"

#define BEDDING_ITEM "bedding"
#define BEDDING_DESC "It's just a lot of dirty laundry.\n"

#define LAUNDRY_ITEM "laundry"
#define LAUNDRY_DESC "It is wrinkled.\n"

#define WRINKLE_ITEM ({"wrinkle", "wrinkles"})
#define WRINKLE_DESC \
  "There is a lot of wrinkles in the dirty " + \
  "laundry, and it is very hard to look " + \
  "through them all when the bed isn't tidy.\n"


#define GET_FAIL_MSG \
  "It is inseparable from the wall.\n"

object key;
string messer;

see_key(object player);

create_object() {
  set_name(({"bed", "bunk"}));

  set_adj(({"unmade"}));
	   
  set_long(WRAP(LONG));

  add_item(BEDDING_ITEM, WRAP(BEDDING_DESC));
  add_item(LAUNDRY_ITEM, WRAP(LAUNDRY_DESC));
  add_item(WRINKLE_ITEM, WRAP(WRINKLE_DESC));

  add_cmd_item(({"down", "in bed", "in bunk"}), "lie",
	       "You don't want to do that when it is " +
	       "so messed up.\n");
  add_cmd_item(LAUNDRY_ITEM, "move", 
	       "Pushing the sheets around randomly won't " +
	       "accompish anything.\n");
  add_cmd_item(LAUNDRY_ITEM, "unwrinkle",
	       "That is beyond mortal ability to do.\n");
  add_cmd_item(({"bunk", "bed"}), "enter", 
	       "You find no secret door in the bed.\n");

  add_prop(OBJ_I_WEIGHT, 2000);
  add_prop(OBJ_I_VOLUME, 2000);
  add_prop(OBJ_M_NO_GET, GET_FAIL_MSG);
}

init()
{
  add_action("mess",  "mess");
  add_action("mess",  "unmake");
  add_action("make",  "make");
  add_action("make",  "tidy");
  add_action("make",  "clean");
}

void set_messer(string str)
{
  messer = str;
}

string query_messer()
{
  return messer;
}

void make_bunk()
{
  object replacement;

  replacement = make_object(OBJDIR + "made_bunk");
  replacement->move(environment());

  remove_object();
}

make(str)
{
  object player;

  player = this_player();
  
  if (str == "room") {
    write(WRAP("Well, the room seems neat enough, but perhaps " +
	       "the bed could do "+
	       "with some tidying up.\n"));
    return 1;
  } else if (str && id(str)) {
    if (MASTER->query_messer() == player->query_name()) {
      tell_object(player, "You clean up the mess you made.\n");
      tell_room(QCTNAME(player) +
		" cleans up the mess " + player->query_pronoun() +
		" made.\n", player);
      make_bunk();
      return 1;
    } else {
      tell_object(player,
		  "You clean up the mess, and feel proud of yourself.\n");
      tell_room(QCTNAME(player) + " makes the bed.\n", player);

      if (!key)
	MASTER->key_appearance(player);

      make_bunk();

      return 1;
    }
  }
  notify_fail(capitalize(query_verb()) + " what?\n");
}


void key_appearance(object player)
{
  set_alarm(3.0, 0.0, &see_key(player));
}

see_key(object player)
{

  key = make_object("/std/key");

  key->set_adj(({"engraved"}));

  key->set_long("It is a small key, engraved with an even " +
		"smaller picture of a priest.\n");
  key->set_key(CARAVAN_KEY_VALUE);
  key->move(environment(player));

  tell_object(player, "But wait, it looks like " +
	      "something fell out when you made the bed...\n");
}

mess(str)
{
  string s;
  object player;

  player = this_player();
  if (id(str) ||
      (str && sscanf(str, "up %s", s) && id(s))) {
    write("You cannot add to the mess already present!\n");
    tell_room(QCTNAME(player) +
	      " tries to mess up the bed even more, but frankly, " +
	      "you see no difference.\n", player);
    return 1;
  }
  notify_fail(capitalize(query_verb()) + " what?\n");
}
