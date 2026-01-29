/*
   Evil forest in Southwestern Territory of Argos
 
   Coder:    Zima
 
   Purpose:  Area with evil NPC's.  Eventually will hide path
             to an evil temple.
 
   History:  01.12.93   Created                         Zima
 
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
object wolf=0;
 
void
reset_room()
{
    if (wolf) return;
    wolf=clone_object(NPC_DIR+"wolf");
    wolf->move(THIS);
    tell_room(THIS, QCNAME(wolf)+" trots through the forest.\n");
}
 
/* room definition */
void
create_room()
{
   set_short("A dark forest");
   set_long(break_string(
       "You come to the end of a path through a dark forest, surrounded " +
       "by pine trees with needles as sharp as razors.  Dead pine needles " +
       "carpet the floor of the forest, softening your footsteps, though " +
       "you think you hear something moving nearby.  There is a cluster " +
       "of mushrooms on the ground at the base of some pines.  The path " +
       "leads back through the forest to the east.  There is a small "    +
       "opening in the sharp pine branches to the south which seems " +
       "to have been made by some creature.\n",70));
 
    add_item(({"opening","pine branches","branches"}), break_string(
       "There is a small hole which has been made by some creature through " +
       "the branches of the dark pines.  You think you might be able " +
       "to crawl through them, if you don't mind getting stuck by " +
       "the deadly needles.\n",70));
 
    add_item("mushrooms", break_string(
        "Growing around the base of the pines, these natural decayers " +
       "probably grow where a corpse recently lay. The mushrooms are "+
        "brown with black streaks, and look very poisonous.\n",70));
 
    add_item(({"forest","trees"}), break_string(
        "Towering pine trees, their bark as black as night and their " +
        "dark-green needles sharp enough to cut.\n",70));
 
    add_item("through branches", break_string( 
       "There is a small hole which has been made by some creature through " +
       "the branches of the dark pines.  You think you might be able " +
       "to crawl through them, if you don't mind getting stuck by " +
       "the deadly needles.\n",70));
 
    add_cmd_item("through branches","crawl","@@enter");
 
    /* exits */
    add_exit(ROOM_DIR+"for10","east",0);
    reset_room();
}
enter()
{
    write(break_string(
          "You crawl through the branches, sharp needles scratching " +
          "your hands and face painfully.\n",70));
   this_player()->move_living("into the sharp branches",
                              ROOM_DIR+"for14");
   return 1;
}
