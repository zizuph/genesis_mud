#include <stdproperties.h>
#include <macros.h>
#include "../stddefs.h"

#pragma save_binary

inherit OBJECT;
inherit STRINGLIB;
inherit MISCLIB;

#define LONG \
  "The bed in the bunk is nicely and tidily made.\n"

#define BEDDING_ITEM ({ "bedding", "laundry" })
#define BEDDING_DESC \
  "The bed is nicely and tidily made, and it easy to " + \
  "establish that it hides nothing.\n"


#define GET_FAIL_MSG \
  "It is inseparable from the wall.\n"

object key;
string messer;

create_object() {
  set_name(({"bed", "bunk"}));

  set_long(WRAP(LONG));

  add_item(BEDDING_ITEM, WRAP(BEDDING_DESC));

  add_cmd_item(({"down", "in bed", "in bunk"}), "lie",
	       "You don't want to do that when it is " +
	       "so nice and tidy.\n");
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
  (OBJDIR + "unmade_bunk")->set_messer(str);
}

string query_messer()
{
  return (OBJDIR + "unmade_bunk")->query_messer();
}

void unmake_bunk()
{
  object replacement;

  replacement = make_object(OBJDIR + "unmade_bunk");
  replacement->move(environment());

  remove_object();
}

make(str)
{
  object player;

  player = this_player();
  
  if (str == "room") {
      write("The room looks neat enough to you.\n");
    return 1;
  } else if (str && id(str)) {
    write(WRAP("Well, it looks like someone " +
	       "already has made the bed. It looks very " +
	       "nice and tidy.\n"));
    tell_room(environment(), 
	      QCTNAME(player) +
	      " tries to make the already made bed.\n",
	      player);
    return 1;
  }
  notify_fail(capitalize(query_verb()) + " what?\n");
}


mess(str)
{
  string s;
  object player;

  player = this_player();
  if (id(str) ||
      (str && sscanf(str, "up %s", s) && id(s))) {

    set_messer(player->query_name());

    tell_object(player, "Ok, you quickly make a mess of everything.\n");
    tell_room(environment(), 
	      QCTNAME(player) + " messes up the bed.\n", player);
      
    unmake_bunk();
    return 1;
  }
  notify_fail(capitalize(query_verb()) + " what?\n");
}