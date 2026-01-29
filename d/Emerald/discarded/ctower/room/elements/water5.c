#include "../../ctower.h"

inherit WATERSTD;

#include <macros.h>
 
int firewall;

void fwall(int add)
{
  firewall = add;

  if (add)
  {
    add_item(({ "wall of fire" , "impenetrable wall of fire" }),
        "The wall burns with intense flames.\n");
    return;
  }

  remove_item("wall of fire");
}

void
ctower_reset()
{
    fwall(1);
}
 
void
create_water()
{
  set_long(query_long() + "@@firewall_long@@");

  add_exit(CTOWER_ROOM_ELEM + "fire2", "north",  "@@block");
  add_exit(CTOWER_ROOM_ELEM + "water3", "northwest");
  add_exit(CTOWER_ROOM_ELEM + "water4", "northeast");

  ctower_reset();
}

string firewall_long()
{
  if (!firewall)
  {
    return "";
  }
 
  return "An impenetrable wall of flames blocks your way north.\n";
}

void
set_exit_state(int state)
{
  if (state && !firewall)
  {
    tell_room(this_object(), "It starts raining, which quickly turns into "+
        "a torential downpour, but then stops just as quickly as it "+
        "began.\n" );
    return;
  }

  if (!state && firewall)
  {
    tell_room(this_object(), "The temperature in the area rises "+
        "dangerously high, but just when you feel faint it cools "+
        "down to normal.\n" );
    return;
  }

  if (state && firewall)
  {
    tell_room(this_object(), "It starts raining, which quickly turns into "+
        "a torential downpour.  The water is instantly vaporized, "+
        "but when the steam clears the wall of fire is gone.\n" );
    fwall(0);
    return;
  }

  tell_room(this_object(), "The temperature in the area rises "+
      "dangerously high, but just when you feel faint, a wall "+
      "of fire ignites, and the temperature cools somewhat.\n" );
  fwall(1);
}
 
int
block()
{
  if (!firewall || this_player()->query_wiz_level())
  {
    return 0;
  }

  write("The wall of fire is making it impossible "+
      "to go in that direction.  The heat is just too much.\n" );
  say(QCTNAME(this_player()) + " attempts to get thru the wall " +
      "of fire but falls back due to the incredible heat.\n");
  return 1;
}
 
string
query_open_gem()
{
  return "spinel";
}
 
string
query_close_gem()
{
  return "ruby";
}
