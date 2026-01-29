/* Herb Room 1, Calia Room
 * Created for Proof of Concept
 * Leia, March 1 2017 
 */

#pragma save_binary
#pragma strict_types

inherit "/w/leia/InProgress/stdChanges/leia_room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/herbsearch.h"

void
reset_herb_room()
{
  set_searched(0);
}

void reset_room()
{
  reset_herb_room();
}

void
create_room()
{
   int athly = add_herb_file("/d/Calia/common/herbs/AODEXAMPLE/athly");
   int strim = add_herb_file("/d/Calia/common/herbs/AODEXAMPLE/strim");
   int strey = add_herb_file("/d/Calia/common/herbs/AODEXAMPLE/streyroot");
   int wild = add_herb_file("/d/Calia/common/herbs/AODEXAMPLE/wildfeather");
   set_short("CaliaRoom");
   set_long("This is an example of a Calia room which will spawn athly and all common herbs.\nAthly: " + athly + "\nStrim: " + strim + "\nStreyroot: " + strey + "\nWildfeather: " + wild + "\n");
   set_search_places(({"here"}));
   add_prop(OBJ_I_SEARCH_TIME, 2); 
   add_prop(OBJ_S_SEARCH_FUN, "herb_search");
   add_exit("/w/leia/InProgress/stdChanges/otherdomain","CommonHerbRoom");
}