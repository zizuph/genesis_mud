// Last update: Tepisch, Jun 1995
// add_virtue function changed.
// Reason: value * value could result in a ridiculously
// large number.  Causing all sorts of nasty bugs in players.

#include <stdproperties.h>
#include "../stddefs.h"

#pragma save_binary

inherit "/std/food";
inherit STRINGLIB;


#define COLOURS \
  ({"pale red", "bright red", "yellow", "pale green", "bright green"})

string colour;

create_food()
{
  colour = COLOURS[random(sizeof(COLOURS))];

  set_name(({"fruit", "apple"}));
  set_adj(({"juicy", "ripe"}));
  set_long(WRAP("It is a " + colour + 
		" juicy apple, almost glowing " + 
		"from inner health and virtue.\n"));

  add_prop(OBJ_I_WEIGHT, 100); 
  add_prop(OBJ_I_VOLUME, 120);
}

add_virtue(int value)
{
  add_prop(OBJ_I_VALUE, value);
     if (value > 1000)
	value = 1000;
  set_amount(value + value);
}








