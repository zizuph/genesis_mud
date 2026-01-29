/* Lpidary shop storeroom
 * creator(s):   Lilith, Dec 20 1997
 *
 * Revisons:
 *	Lucius, Oct 2017: Limit gem cloning due to long uptimes.
 */
#pragma strict_types

inherit "/d/Avenir/inherit/storage";

#include "../bazaar.h"
#include "/d/Genesis/sys/gem.h"
#include <stdproperties.h>

public int size;

public void
hook_reset_store(void)
{
    if (!random(3))
	return;

    size = random(5);
    while(size--)
    {
	object gem = RANDOM_GEM_BY_RARITY(GEM_SLIGHTLY_RARE);
	gem->set_heap_size((random(3) ?: 1));
	gem->move(this_object());
    }
}

public void
create_room(void) 
{
    set_max_items(50);
    set_shop_room(INTR + "lapidary");

    set_short("The lapidary shop display case and store room");
    set_long("This is the store room and display cae for the "+
      "lapidary shop.\n");

    add_exit(INTR + "lapidary", "shop");

	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.

    enable_reset(200);

    size = 10;
    while(size--)
    {
	object gem = RANDOM_GEM(GEM_ALL);
	gem->set_heap_size((random(4) ?: 1));
	gem->move(this_object());
    }
}
