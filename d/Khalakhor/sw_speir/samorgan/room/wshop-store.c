/*********************************************************************
 * - wstore.c                                                      - *
 * - Created by Damaris 7/2005                                     - *
 * - optimized by Tapakah, 5/2021                                  - *
 *********************************************************************/
#pragma strict_types
#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

inherit "/d/Khalakhor/std/room";
inherit "/lib/store_support"; /* the default store-room support */

#define SUPPLY 3
#define CATALOG ({SM_SWORD, SM_DAGGER, SM_POLEARM, SM_AXE, SM_HAMMER})

void
reset_room()
{
	object  *all_inv = all_inventory();
  mapping weapon_counts = ([]);
	int     i, j, s;
	int     num_found;
  string  weapon_file;

  foreach (object weapon: all_inv) {
    weapon_file = MASTER_OB(weapon);
    if (weapon_counts[weapon_file])
      weapon_counts[weapon_file]++;
    else
      weapon_counts[weapon_file] = 1;
  }
	for (i=0, s=sizeof(CATALOG); i<s; i++) {
    weapon_file = CATALOG[i];
    if (! weapon_counts[weapon_file])
      weapon_counts[weapon_file] = 0;
    for (j=weapon_counts[weapon_file]; j<SUPPLY; j++)
      clone_object(weapon_file)->move(this_object(), 1);
  }
}

void
create_khalakhor_room() 
{
	set_short("Weaponry storeroom");
	set_long("   This is the store room for weapons.\n");
	
	add_exit("wshop", "north");
	reset_room();
}

/*********************************************************************
 * - You should always call store_update() if an object enters the - *
 * - storeroom to update it and let it be added to the stock.      - *
 *********************************************************************/
void
enter_inv(object obj, object from)
{
	::enter_inv(obj, from);
	store_update(obj);
}

