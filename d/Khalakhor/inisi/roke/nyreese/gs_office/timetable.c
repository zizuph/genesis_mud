/*
 * Genesis ShipLines - Sparkle office.
 * Ship timetable
 * TAPAKAH, 10/2008
 * To be transferred later into /d/Sparkle
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Sparkle/area/city/shiplines/lib/gs_office.h";

inherit GSL_TIMETABLE_BASE;

void
create_timetable ()
{
  set_name("timetable");
  set_adj(({"large", "cardboard"}));
  set_long("A large green cardboard timetable, bolted into a wall. "+
           "Several bells and whistles are attached to the perimeter of the "+
           "cardboard.\n" +
           "You notice a narrow slit about a width of a coin at the right "+
           "lower corner of the timetable.\n" +
           "@@exa_timetable");
  add_item(({"bells", "whistles"}),
           "The bells and whistles do not seem to serve any purpose, but "+
           "show the gnomish design of the timetable.\n");
  add_item(({"slit"}),
           "Above the list there is a small plaque that reads:\n"+
           "LearnArrivalAndDepartureInformationForOnePlatinumCoin!\n");
  set_timetable_domain("Khalakhor");
  set_timetable_cost(1728);
  set_money_accept(({ 0, 0, 0, 1 })); // accept only platinums
  set_no_show_composite(1);
  setuid();
  seteuid(getuid());            

}
