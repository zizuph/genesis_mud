/* Street base file for Tantallon.
* By Teth, Jan 17 , 1996
*/

#include "../local.h"

inherit INROOM; 

public void
reset_tant_room()
{
}

public void
create_tent()
{
   
}

nomask void
create_tant_room()
{
   set_short("In an expansive tent");
   set_long("You are in an expansive tent. The walls of the tent are made " +
       "of canvas, suggesting a recent placement. ");
   AI(({"expansive tent","tent"}), "This expansive tent has been placed " +
       "here for military purposes.\n");
   AI(({"walls","walls of the tent", "canvas walls"}),"Although they are " +
       "not solid, the walls of the tent prevent escape for those within.\n");
   AI("canvas","The canvas of the tent appears to be of burlap.\n");
   AI("burlap","A useful material for making canvas, due to its thick and " +
       "heavy nature.\n");
   AI("ceiling", "The ceiling of tent is made of canvas.\n");
   AI("floor","The floor of the tent is bare ground and  cobblestones.\n");
   AI(({"ground","bare ground","cobblestones"}),"There is not much to look " +
       "at, as it is what you would expect of bare ground and " +
       "cobblestones.\n");
   AI("cobblestone","There are many cobblestones.\n");

   INSIDE;
   
   create_tent();
   reset_room();
   
}

