#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h";
#include "../ship.h"

inherit STDSHIPROOM;

object pirate;

/*
 * Function name: not_open
 * Description:   vbfc for the gallery exit
 * Returns:       1 to indicate the exit has been handled.
 */
public int
not_open()
{
    write("The hatch is closed and locked for the duration of the trip.\n");
    return 1;
}

void
reset_deck()
{
    int i, flagit;
    object room, *obs;

    if (!pirate)
    {
        pirate = clone_object(PIRATE);
        pirate->move(this_object());
        return;
    }

    flagit = 0;
    room = find_object(HOLD);

    if (!(objectp(room)))
     return;

    if (present(pirate, room))
    {
        obs = all_inventory(room);
        for (i=0; i<sizeof(obs); i++)
        {
            if (living(obs[i]) && !(obs[i]->query_npc())) 
              flagit = 1;
        }
        if (!flagit)
        {
          pirate->set_hp(9999);
          pirate->move(this_object());
          pirate->add_prop(OBJ_I_HIDE, 100);
        }

    }

}   

void
reset_room() {

  ::reset_room();
  reset_deck();
}


void
create_room()
{
  ::create_shiproom();
    set_short("On the deck");
    set_long("You are standing on the deck of a fine, well-kept ship.  " +
	     "All around you see the rich grain of well-oiled teak and " +
	     "the gleam of polished brass.  A small signal cannon, also " +
	     "of brass, looks out over the waves.  To the aft is the " +
	     "Captain's cabin; below decks you smell the tantalizing " +
	     "odour of fresh seafood.\n");
    
    add_item("cannon", "This signal gun seems to be strictly for show. It is "
       + "securely bolted to the deck.\n");
	     
    add_exit(GALLERY, "down", "@@not_open@@");
    add_exit(CABIN,   "aft",  0);
    set_is_deck(1);
    reset_room();
}
