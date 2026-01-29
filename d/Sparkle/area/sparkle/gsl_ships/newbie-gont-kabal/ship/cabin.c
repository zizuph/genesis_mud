/*********************************************************************
 * - cabin.c                                                       - *
 * - shipline Gont-Kabal                                           - *
 * - Recoded by Damaris 5/2003                                     - *
 *********************************************************************/
#pragma save_binary
#pragma strict_types
 
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h";
#include "../ship.h"

inherit STDSHIPROOM;

public string sounds();

public void
create_room()
{
  ::create_shiproom();
  set_short("The captain's cabin");
  set_long("This must be the captain's cabin. Inside there "+
           "are many navigational instruments, such as compasses and "+
           "sextants mounted on the walls. To the far side of the "+
           "cabin is a large mahogany desk along with several portholes "+
           "to look outside.\n");
  add_item(({"cabin","quarters","cramped quarters"}), query_long);
  add_item(({"instruments","instrument"}),
           "All manner of navigational tools can be seen, carefully mounted on "+
           "the cabin walls.\n");
  add_item(({"large mahogany desk","mahogany desk","desk","large desk"}),
           "A simple wooden desk with several maps spread out on top.\n");
  add_item(({"maps","map"}),
           "Nautical maps of the routes between Kalad and Roke.\n");
  add_item(({"portholes","porthole"}),
           "Looking out the holes you see the rolling waves of the sea.\n");
  add_exit(DECK, "out");
  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_I_LIGHT, 1);
  
  set_cabin_sound(sounds());

}
 
public string sounds()
{
  switch(random(5))
    {
    case 0:
      return "You can hear the ship creak as it continues to move through "+
        "the icy waters.\n";
    case 1:
      return "You can feel the ship rise slightly.\n";
    case 2:
      return "You hear shouts and laughter from the working crew upon the deck.\n";
    case 3:
      return "The room creaks around you.\n";
    default:
      return "A large crash and shouts are heard.\n";
    }
}




