/* A tournote to keep track of the tour the player is doing.
 * Elessar, May 92.
 */

inherit "/std/object";
#include "/sys/stdproperties.h"

int tour_no,tour_done;

create_object()
{
  set_name("note");
  add_name("Minas_Tirith_Tour_Note");
  set_short("note of tourism in Minas Tirith");
  set_pshort("notes of tourism");
  set_long("This note is given to you as a proof of your tourist-status.\n"+
    "That won't necessarily give you any advantages, but it will help\n"+
           "you to get to know the city of Minas Tirith.\n");
  add_prop(OBJ_I_VOLUME,0);
  add_prop(OBJ_I_WEIGHT,0);
}

set_tour_no(i)
{
  tour_no = i;
}

query_tour_no()
{
  return tour_no;
}

set_tour_done()
{
  tour_done = 1;
}

query_tour_done()
{
  return tour_done;
}
