/* Deck on the ship from Calia to Terel 

   Coded by Maniac & Jaacar, 27/11/95
*/

#pragma save_binary

inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>
#include "ship.h"

void
create_deck()
{
    set_deck_sound("The ship cuts through the water like a dolphin.\n");
    set_short("The deck of a crystalline ship");
    set_long("You stand on the deck of a magical ship made almost entirely " +
            "of transparent, flawless crystal. The crystal is cut in such " +
            "a way that light refracts in unusual patterns, " + 
             "glittering around you and shifting with the movements " +
             "of the sea waves some ten feet below. " + 
             "Sometimes the vessel appears almost invisible, as if you are " +
             "suspended on a fancy of your imagination, then in the " +
             "blink of an eye you will find yourself standing within " +
             "a gigantic wave among the foam and slippery creatures of " +
             "the deeps. The vessel, it seems, blends wholly into the " +
             "nature of its environment. This gift is one of the works " +
             "of Caliana's powers of enchantment. You notice a small " +
             "transparent hatch that leads down into a cabin.\n");

    add_item(({"hatch", "small hatch", "small transparent hatch"}),
               "A small hatch, made of crystal of course, leads down " +
               "into a cabin.\n"); 
    add_item("cabin", "It is below the water line.\n");
    add_item(({"mast", "masts"}), "Like almost everything on the ship, " +
              "they are made of magical transparent crystal, with ropes " +
              "of silk.\n");
    add_item(({"sail", "sails"}), "The sails are made of thin but strong " +
               "transparent silk.\n");
    add_item("crystal", "The crystal that the ship is made of is perfectly " +
             "cut, and by its unusual light refraction it seems likely that " +
             "it is enchanted.\n");

    add_item("deck", "Like almost everything on the ship, the deck is made " +
            "of magical transparent crystal. You can see right through the " +
            "deck floor, then on through the cabin below, to the sea.\n");

    add_item("sea", "The sea is visible below the ship through the crystal, " +
             "you sometimes notice the shadow of shoals of fish or a larger " +
             "sea creature pass below.\n");
    add_item("ship", "Well, you're on it.\n");
     
    add_prop(ROOM_I_INSIDE,0);
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE,-1);
    add_prop(ROOM_M_NO_ATTACK,"You feel a divine force preventing you "+
        "from attacking.\n");

    add_exit(SHIPS+"cabin", "down", 0, 0);
}

