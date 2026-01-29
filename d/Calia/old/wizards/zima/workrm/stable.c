inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Dville/abbrev.h"

void
create_room()
{
    set_short("Zima's stable");
    set_long(BS(
       "This room made of black marble is fashioned in the form of a " +
       "triangle, and serves as the stable where Zima keeps his winged " +
       "horses.  A mysterious letter is detailed on the floor in " +
       "white ivory.  An arched passageway leads back into the chambers " +
       "through the northeastern corner of the triangular room.\n"));
    add_exit("/d/Calia/zima/workroom","northeast",0);
   add_item("letter", BS(
      "This mysterious letter is detailed into the floor in white " +
      "ivory and is in the form of the greek letter Kappa.\n"));
   
}
