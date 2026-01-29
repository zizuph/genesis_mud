/* Forest.h  - A file to include when you want a players tracking or
 * location sense skills to be tested before moving a direction.
 * Remember to set the forest_density - if the skill is higher than this
 * number, the move is a success. To call the skill-test functions, do
 * @@test_track  or @@test_loc from the add_exit.   Elessar, April '92.
 */
#include <macros.h>
int forest_density;

test_track()
{
  if (this_player()->query_skill(107) > random(forest_density)) {
     write("You succeed in following the path.\n");
     return 0;
  }
  else {
     write("You quickly lose track of the path, and return to where you were.\n");
     say(QCTNAME(this_player())+" lost track of the path, and returned here.\n",this_player());
     return 1;
  }
}

test_loc()
{
  if (!this_player() || this_player()->query_skill(106) >
	random(forest_density)) return 0;
  else {
    write("You feel disoriented as to what is the correct direction, so\n"+
          "you stop in fear of getting lost.\n");
    say(QCTNAME(this_player())+" can't decide which direction to go.\n");
    return 1;
    }
}

forest_density(int i)
{
  forest_density = i;
}


#define THICKET add_item(({"thicket","underbrush"}),\
    "The thicket of trees and underbrush is almost impenetrable.\n")
