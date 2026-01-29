/*
 * Genesis ShipLines Office Timetable in Sparkle
 *
 * This is the instance of the timetable in Sparkle's GSL office.
 *
 * Created by Petros, April 2009
 */

#pragma save_binary
#pragma strict_types

#include <std.h>
#include <stdproperties.h>
#include "../lib/gs_office.h"

inherit GSL_TIMETABLE_BASE;

/*
 * Function:    create_timetable
 * Description: Mask this function to set up the timetable object
 *              and customize it for the specific office.
 */
public void
create_timetable()
{
  set_name("timetable");
  set_adj(({"large", "cardboard"}));
  set_long("A large cardboard timetable, bolted into wall. Several "
        + "bells and whistles are attached to the perimeter of the "
        + "cardboard. You notice a narrow slit about a width of a coin at "
        + "the right lower corner of the timetable.\n\n" 
        + "@@exa_timetable@@\n");
  add_item(({"bells", "whistles"}),
           "The bells and whistles do not seem to serve any purpose, but "
           + "show the gnomish design of the timetable.\n");
  add_item(({"slit"}),
           "Above the list there is a small plaque that reads:\n"
           + "LearnArrivalAndDepartureInformationForOnePlatinumCoin!\n");
  
  // Set up the defaults for the Timetable
  set_timetable_domain("Sparkle");
  set_timetable_cost(1728);
  
  set_money_accept(({ 0, 0, 0, 1 })); // accept only platinums
  set_no_show_composite(1);
  
  setuid();
  seteuid(getuid());            
}

