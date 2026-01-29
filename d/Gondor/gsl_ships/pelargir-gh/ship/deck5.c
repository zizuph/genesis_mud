#pragma save_binary

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIPROOM;

#include "/d/Gondor/common/lib/time.h"
#define BS(X) break_string(X, 75)
#define BSN(X) (break_string(X, 75) + "\n")

void
create_room()
{
  ::create_shiproom();
    set_short("On the ship");
    set_long(break_string("You're standing on a large merchant ship, your hair "+
             "rustling in the wind. The large sail above is filled by the wind, "+
             "the embroidered emblem of Gondor shown fully. One great mast "+
             "supports the sail. From both of the strongly crafted sides you "+
             "see oars sticking out, probably used for maneuvering in the "+
        "shallows and up rivers. A cabin sits on the aft portion of the deck, "+
        "and a closed hatch leads down to the cargo bays.\n",75));
    add_item(({"mast", "masts"}), break_string("There is one great mast "+
	     "supporting the enormous sail, made of the strongest "+
             "Gondorian lebethron wood. You can see people high up in the "+
	     "mast, climbing about.\n",76));
    add_item("hatch", BS("The large hatch is bolted shut, blocking the entrance "+
        "to the cargo bay.\n"));
    add_item("oars","You notice oars sticking out from each side of the ship,\n"+
             "and you guess there are rowers aboard maneuvering the vessel\n"+
             "up rivers and through shallows.\n");
    add_item(({"sail", "sails"}), break_string("The sail is made out of "+
	     "thick, incredibly strong canvas. On its center is painted "+
             "a single black circle, within which the emblem of Gondor is "+
             "embroidered. The sail is square shaped, and "+
	     "each time a gust of wind fills it, you feel a "+
             "shrug going through the ship and notice the mast swaying "+
             "slightly to the enormous pressure.\n",76));
    add_item("emblem","The emblem is the well-known White Tree surrounded by\n"+
             "the Seven Stars, all on a black background.\n");
    add_item(({"ship"}), BSN(
        "You are standing on a large sailing ship with a single great mast. "+
        "On both sides of the ship you can see oars sticking out, probably " +
        "used for maneuvring in the shallows and up rivers. "));
    add_item(({"cabin","cabins"}), BSN(
        "The cabin aft of here looks like a perfect place to weather"
      + " harsh seas when the fierce winds blow. A warm light can"
      + " be seen coming from within its sturdy frame."));
    add_cmd_item("mast", "climb", BSN("You are not working at the ship " +
        "so you have no business high up in the mast."));
    add_cmd_item("hatch","open", BSN("You have no business down there anyway, "+
        "so you don't find much reason to protest when a sailor "+
        "tells you to leave the hatch alone."));
    add_exit(CABIN, "aft", 0);

    add_prop(ROOM_I_HIDE, 50);
    set_is_deck(1);
}

