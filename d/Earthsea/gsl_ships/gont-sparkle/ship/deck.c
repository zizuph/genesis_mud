#pragma strict_types
#pragma no_clone

#include <macros.h>
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDSHIPROOM;

string sounds();
void
create_room()
{
  ::create_shiproom();
  set_short("Black wooden deck");
  set_long(break_string("You are standing on a deck painted "+
                        "black as pitch. The rails are carved from ebony. There "+
                        "is something a bit magical about this ship, possibly due "+
                        "to the captain's spells of binding, which hold it "+
                        "together. When the silver and blue sails fill with "+
                        "sea breeze, this ship fairly flies across the waves.\n",70));
  
  add_item((({"sails", "silver sail", "blue sail" })),
           "The ship has a large triangular silver mainsail "+
           "and a billowing blue spinnaker sail set on a spar.\n");
  add_item("rails",
           "The ebony rails are black as night.\n");
  add_item("deck", 
           "The hard wooden deck is painted black as pitch and "+
           "lends to the mysterious feeling of this ship.\n");
  
  
  set_deck_sound(sounds());
  set_bump_sound("The ship slows and eases into dock.\n");
  add_prop(ROOM_M_NO_ATTACK, 1);
  set_is_deck(1);
}

string
sounds()
{
  object cap = present("yorlis", this_object());
    int i = random(4);
    /*
    if (start)
    {
	cap->command("emote raises his staff and invokes a "+
	  "wind spell.");
	tell_room(this_object(), "A strong gust of sea wind suddenly "+
	  "fills the sails, and the ship bucks like a stallion.\n",
	  ({}));
	start = 0;
	return "You are underway.\n";
    }
    */
    switch(i)
    {
    case 0:
	return "You see dolphins leaping off the starboard bow, "+
	"racing the ship.\n";
	break;

    case 1:
	return QCTNAME(cap) + " sets the sails to tack against the "+
	"wind. You duck just in time as the mainsail swings across "+
	"your head.\n";
	break;

    case 2:
	return "The blue spinnaker fills up and billows out "+
	"before the wind.\n";
	break;

    default:
	return "The ship flies across the high waves, the wind "+
	"filling its sails.\n";
	break;
    }
}

/*void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (ob->id("_yorlis_"))
	start = 1;
}
*/
