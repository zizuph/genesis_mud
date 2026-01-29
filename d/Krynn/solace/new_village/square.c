/*
 * The village Solace
 *
 * By Rastlin
 *
 * This room contains a donation column (/d/Genesis/obj/donation/column)
 */

#include "local.h"
#include "/d/Krynn/common/defs.h"
#include CLOCKH

#define MERCHANT "/d/Krynn/solamn/thief/guild/obj/recruiter2"


inherit SOLOUTROOM2;

object merchant;
object column = 0;


void
reset_solace_room()
{
    if (!column)
    {
	column = clone_object("/d/Genesis/obj/donation/column");
	column->move(TO);
    }
}

void
create_solace_room()
{
    set_place(SQUARE);

    set_long_desc("The square is a large clearing that is " +
		  "surrounded on all sides by huge vallenwood trees. " +
		  "These trees stretch far above the ground and their " +
		  "limbs provide cover and shelter to the inhabitants " +
		  "of Solace. The clearing here rises slightly towards " +
		  "the center of the square, providing a high spot in " +
		  "the center. Small roads have been cut into the dense " +
		  "forest to the north, southeast, west and southwest.");

    add_exit(TDIR + "west_road1", "north");
    add_exit(TDIR + "main_road7", "southeast");
    add_exit(TDIR + "clearing2", "west");
    add_exit(TDIR + "ns_path1", "southwest");
    reset_room();
}


void
enter_inv(object ob, object from)
{
    int *the_time = GET_TIME;
    
    if (!merchant)
      (merchant = clone_object(MERCHANT))->move_living("xxx",VOID);

    if (the_time[HOUR] > 6 && the_time[HOUR] < 20)
      {
	  if (E(merchant) == TO)
	    {
	      merchant->command("emote leaves.");
	      merchant->move_living("M",VOID);
	    }
      }
    else if (E(merchant) != TO)
      merchant->move_living("",TO);

    ::enter_inv(ob,from);
}
