#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void    reset_room();

static object *orcs = allocate(2 + random(3));

public void
create_morgul_room()
{
    set_extraline("Down here in the basement, heaps of straw are "
      + "covering the floor. From a corner a small garbage pile emits "
      + "the stench of decaying meat and vomit. This place must be "
      + "the perfect home for a pack of orcs.");
    add_item(({"flight","steps","stone steps","stairs"}), BSN(
        "A flight of steps hewn from dark rock is leading up to "
      + "the ground floor of the building."));
    add_item(({"corner","pile","garbage","meat","vomit"}),"@@exa_pile");
    add_item(({"straw","heap","heaps","heaps of straw"}), BSN(
        "The floor is covered with straw. Close to the walls, the "
      + "straw has been gathered into heaps. The orcs are probably "
      + "sleeping on those heaps."));
    set_road(5);
    set_side("west");
    add_exit(MORGUL_DIR + "city/barrack1","up","@@check_exit",1);
    add_prop(ROOM_I_LIGHT,-1);
    reset_room();
}

string
exa_pile()
{
  string  desc = "A wild mixture of mostly organic products is rotting "
               + "away in the corner. ",
          racename = QRACE(TP);

  if(racename == "goblin")
    desc += "You dig around in the heap of decaying meat, fresh vomit " +
      "and still damp orc manure, but you find nothing interesting. ";
  else 
  {
    desc += "Among still damp orc manure and fresh vomit you see the " +
      "half-decayed remains of burned meat. With horror you recognize " +
      "the gnawed bones once belonged to " + LANG_ADDART(racename) + ". ";
    TP->command("puke");
    TP->add_panic(MAX(120 - TP->query_stat(SS_DIS),20)*5);
    TP->add_fatigue(-MAX(120 - TP->query_stat(SS_DIS),20));
  }
  return BSN(desc);
}
      
public void
reset_room()
{
    set_alarm(10.0 + rnd() * 20.0, 0.0, &clone_npcs(orcs, MORGUL_DIR + "npc/ithil_orc", 60.0));
}

