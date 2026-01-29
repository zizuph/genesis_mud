/* A tournote to keep track of the tour the player is doing.
 * Elessar, May 92.
 */

inherit "/std/object";
#include "/sys/stdproperties.h"

int tour_no,tour_done;

void
create_object()
{
  set_name("note");
  set_pname("notes");
  set_adj(({"Galian","Thranduil","galian","thranduil"}));
  add_name("Thranduil_Tour_Note");
  set_short("Thranduil note of tourism");
  set_pshort("Thranduil notes of tourism");
  set_long("This note is given to you as a proof of your tourist-status.\n"+
    "That won't necessarily give you any advantages, but it will help\n"+
    "you to get to know the Caverns of Thranduil.\nThe note is marked "+
    "@@text_solved@@"+".\n");
  add_prop(OBJ_I_VOLUME,0);
  add_prop(OBJ_I_WEIGHT,0);
}

string
text_solved()
{
  if(tour_done) return "solved";
  return "unsolved";
}

void
set_tour_no(int i)
{
  tour_no = i;
}

int
query_tour_no()
{
  return tour_no;
}

void
set_tour_done()
{
  tour_done = 1;
}

int
query_tour_done()
{
  return tour_done;
}
