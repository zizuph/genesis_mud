#pragma save_binary

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIPROOM;

void
create_room()
{
  ::create_shiproom();
  set_short("A cramped and dark cabin inside the elegant ship");
  set_long("While built with the same craftsmanship and materials "+
    "as the rest of the ship, this long, low cabin contains nothing "+
    "in the way of amenities or creature comforts. Mingling with "+
    "the subtle scents of the wood are the sharper scents of oil and "+
    "sweat, indicating that this room is at times inhabited by a "+
    "large group of hard working sailors. It would seem then, that "+
    "these are the crews' quarters. "+
    "The center of the room forms a clear aisle extending the length "+
    "of the cabin, except for a single column near the bow end of the "+
    "room. A solitary door stands to the rear of the room. "+
    "Along the port, starboard, and fore walls, beds project outwards "+
    "like shelves in a cupboard. The beds are stacked in columns of "+
    "three, lining the entire length of the walls. Of course "+
    "this makes for cramped sleeping quarters, but it is doubtful "+
    "that the sailors spend much time in here.\n");

  add_exit(DECK, "aft",0,1);
  add_prop(ROOM_I_LIGHT, 0);

  add_item("door","The door is made of the same blend of timber "+
    "as the rest of the ship. It forms a tight seal in the doorway, "+
    "preventing water, air, and even light from getting through it.\n");
  add_item(({"central column","column"}),
    "The column is thick, and obviously the lower part of a mast.\n");
  add_item(({"bed","columns","columns of beds","beds"}),
    "These beds have just the bare minimum parts. In other words, "+
    "a strong flat place to lie on and a thin blanket to cover "+
    "oneself with or to roll up and use as a pillow if it is "+
    "warm enough to forgo the scant warmth it would provide.\n");
  add_item(({"wood","floor","ceiling","walls","wall"}),
    "All of the wooden components of the cabin are crafted from the "+
    "same expertly joined lengths of differing varieties of wood that "+
    "the deck, hull, and passenger cabin are built from. The strips "+
    "are joined so well that no seams are visible at all "+
    "and the shades blend from light to dark and back to light, "+
    "although the effect is somewhat spoiled by the darker tone and "+
    "light absorbing quality of the wood in this dark, musty cabin.\n");
}
void
init()
{
    ::init();
   write("You enter the darkened crewroom, noting aft is the way out.\n");

}
