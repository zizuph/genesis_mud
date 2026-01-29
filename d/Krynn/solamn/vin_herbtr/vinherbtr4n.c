/* 
   created by Vitwitch 08/2021 
   based closely on work of by Aridor 06/1993
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

#define PALANTHAS_EXTERIOR "/d/Krynn/solamn/palanthas/nobles/er6"
#define VINGAARD_HIGHROAD "/d/Krynn/solamn/vin_mount/room/road3"
#define ROOM "/d/Krynn/solamn/vin_herbtr/"

#define CLIMBER_HAS_FOUND_REFUGE "_climber_found_refuge"

inherit "/d/Krynn/solamn/vin_herbtr/vinherbtr_base";

string *herbs = HERB_MASTER->query_herbs(({"mountains",}));

/* FUNCTIONS */

string
find_refuge()
{
    TP->add_prop(CLIMBER_HAS_FOUND_REFUGE,1);
    return "Searching the openings at the base of the outcrop, "+
          "you find that one leads a ways inside out of sight. "+
          "You could use this opening to go <inside>.\n";
}

block_if_not_found()
{
  if (TP->query_prop(CLIMBER_HAS_FOUND_REFUGE))
    return 0;
  write("There is no obvious exit inside.\n");
  return 1;
}

unseen_if_not_found()
{
  if (TP->query_prop(CLIMBER_HAS_FOUND_REFUGE))
    return 0;
  return 1;
}

void
create_vin_herb_trail_room()
{
    add_exit(ROOM + "vinherbtr3","downward",0,5);
    add_exit(ROOM + "vinherbtr4s","south",0);

    set_skeleton_here();

    add_item(({"bones","bleached bones","skeleton","dismembered skeleton"}), 
               "These remains are a solemn reminder of how quickly "+
               "the weather can turn here. "+
               "Examining the bones of the skeleton, it seems to you "+
               "that their positioning is unnatural.\n");

    add_item( ({"positioning","positioning of bones"}), 
               "The long bones of the skeleton have been arranged to "+
               "point in a single direction like a compass needle. "+
               "Aligning yourself with that direction, you see a "+
               "curious rocky outcrop to one side of the trail.\n");

    add_item(({ "outcrop", "rocky outcrop", "curious rocky outcrop" }), 
                "Stepping off the trail, you note that the rocky "+
                "outcrop is a complex shape with some large openings "+
                "in its surface.\n");

    add_item(({ "openings", "large openings" }), 
                "The large openings in the outcrop "+
                "could be worth searching.\n");

    add_search(({ "openings", "outcrop" }), 
                    3, "find_refuge",1);

    add_exit(ROOM + "vinherbtr_refuge","inside",
         "@@block_if_not_found",0,"@@unseen_if_not_found");

    set_climb_skill_min( 0 );
}

