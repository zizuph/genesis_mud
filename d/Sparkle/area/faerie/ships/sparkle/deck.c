/*
 * The deck of the ship between Faerie and Sparkle.
 * Tapakah, 10/2008
 */

#pragma save_binary

#include "../../rooms/forest/_defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDSHIPROOM;

void
create_room()
{
  ::create_shiproom();
    set_short("On a white oblong ship");
    set_long("You're standing on a white oblong ship. It is a medium-sized " +
             "vessel used for cabotage travel to. The deck is uncluttered " +
             "and probably cleaned regularly by sailors. There is a " +
             "tall mast supporting sails. A set of stairs leads down from " +
             "the deck to a cabin below.\n"+
             "It belongs to the Genesis ShipLines Company fleet.\n");
    add_item(({"mast", "masts"}),
             "There is one tall mast secured to the deck. "+
             "It supports two large sails and several smaller sails. "+
             "A bowsprit extends out from front of the ship.\n");
    add_item(({"bowsprit"}),
             "This is a long pole that extends out from the front of "+
             "the ship. It points upwards slightly and is used to secure "+
             "sails to it.\n");
    add_item(({"sail", "sails"}), 
             "The sails are made from thick, incredibly strong canvas. "+
             "The main sail is tall, triangular shaped, and connects "+
             "to the main mast and bowsprit.\n");
    add_item(({"ship"}), 
             "You are standing on a white oblong ship with a great mast. "+
             "A set of stairs lead down from the deck to the cabin below.\n");
    add_item(({"stairs"}),
             "They are narrow and lead down to a cabin.\n");
    
    add_exit("cabin", "down");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    return;
}
