#include "/d/Krynn/common/defs.h"
#include "../local.h"

/* Inherit the Krynn room */
inherit R_FILE

/*
 * Change these two XXX to the proper name
 */
#define CREATE "create_sewer_room"
#define RESET  "reset_sewer_room"

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

void
create_sewer_room()
{
   set_short("Sewers of Kalaman");
   set_long("You are in the tunnels of the sewers of Kalaman. Surprisingly, the " +
     "tunnels are lighted through several grates. There is a stream of water in " +
     "the middle of the sewer. Through the grates one can vaguely hear the mumbling " +
     "sounds of the people who are residing in the city. Occasionally a scurrying " +
     "sound of rats can be heard.\n");
    
   add_item(({"water"}), "The water is rather dirty. Also the smell is not pleasant either. " +
     "One could almost start to believe that these waters are used to dump all sort of trash " +
     "from the city.\n");
   add_item(({"stream"}), "The water streams downwards towards the center of the sewer. " +
     "The water looks rather filthy.\n");
   add_item(({"grate", "grates"}), "There are several grates in the ceiling of the tunnel. " +
     "The grates a just big enough to let some light down and shower the area with a " +
     "gloomy light.\n");
   add_item(({"wall", "walls"}), "The walls are damp and dirty, here and there some very green " +
     "moss seems to have found itself at home and grows on the huge stone blocks that form the " +
     "walls.\n");
   add_item(({"block", "blocks"}), "These huge stone blocks form the foundation of streets of " +
     "Kalaman and also the walls of the sewers, some of them are covered with a thick green " +
     "moss that seems to like it down here.\n");
   add_item(({"moss","green moss", "thick moss"}), "This thick green moss looks just like " +
     "ordinary moss except that it is much darker in the colour and that it smells like " +
     "sewage instead of fresh forest.\n");
   add_item(({"floor", "ground"}), "The ground is covered with filth that has been carried " +
     "with the sewage water down here. There are also small piles of rat droppings all over " +
     "the place.\n");
    
   INSIDE;
}

void
reset_sewer_room()
{
    
}
