/* Cabin for the ship from Calia to Terel,

   Coded by Maniac & Jaacar 27/11/95

   Typo corrected 10/12/95, Maniac
 */

#pragma save_binary

inherit "/d/Genesis/ship/cabin";

#include <stdproperties.h>
#include "ship.h"
#include <macros.h>

void
create_cabin()
{
    set_cabin_sound("Turbulent sea water speeds past you in a blur on " +
                    "every side.\n");
    set_short("The cabin of a crystalline ship");
    set_long("All around you is the sea, with occasional glimpses " +
             "of creatures swimming past, visible with such clarity that " +
             "you feel you can reach out and touch them. Far below you are " +
             "the murky, ominous depths, sinking from the barely visible " +
             "surface of the vastness into total darkness. The possibility " +
             "of giant sea monsters rearing up at you is unnerving, but the " +
             "crystal hull gives an impression of being far from fragile.\n");

     add_item(({"hull", "crystalline hull"}), "The crystal of the hull " +
               "seems to be very thick but maintains its appearance of " +
               "subtlety.\n");
     add_item("crystal", "The crystal that the ship is made of is perfectly " +
             "cut, and by its unusual light refraction it seems likely that " +
             "it is enchanted.\n");
     add_item("ship", "Well, you're on it.\n");

     add_prop(ROOM_I_INSIDE,1);
     add_prop(ROOM_I_LIGHT,1);
     add_prop(ROOM_I_IS,1);
     add_prop(ROOM_I_HIDE, -1);
     add_exit(SHIPS+"deck.c", "up", 0,0);
}

