/*
   Asmodean March 18, 1995
   BG - Property of Cirath Domain
*/

#include "almorel.h"
#include "Lakes.h"

inherit LAKE_MASTER;

void
create_lakeside()
{
  set_short("Bridge");
  set_long("This massive wood bridge leads from the shore of "+
	   "the Lake of Mist to the tower of Raumkreml. The bridge "+
	   "is covered with slick ice and patches of snow. There are "+
	   "hundreds of chains and poles for people to grab hold of to "+
	   "keep their balance. Before you towers the center of law "+
	   "and government of Almorel, a gigantic black tower extending "+
	   "up into the thicker, impenetrable fog.\n\n");

  remove_item("ground");
  add_item(({"ground","bridge"}),
	   "The bridge beneath you was constructed of giant trees and "+
	   "lashed together with mud, clay, mortar and other adhesives. "+
	   "Also holding the bridge together are iron bars and thick "+
	   "hide cables.\n");

  add_exit(ALMOREL+"lk4","northwest");
  add_exit(ALMOREL+"sp1","north");
  add_exit(ALMOREL+"rd3","south");
}
