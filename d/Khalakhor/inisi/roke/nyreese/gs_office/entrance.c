/*
 * Genesis ShipLines - Cadu office.
 * TAPAKAH, 10/2008
 */

#include <macros.h>
#include "/d/Sparkle/area/city/shiplines/lib/gs_office.h";

inherit GSL_OFFICE_BASE;

#define CADU_GSL_OFFICE_DIR "/d/Khalakhor/inisi/roke/nyreese/gs_office/"
#define EXIT_TO_PIER "/d/Khalakhor/inisi/roke/nyreese/cadu_b4"
// Defines
void
create_gsl_office() {

  set_short("Inside the Cadu Office of Genesis ShipLines");
  set_long("You are inside the Cadu Office of Genesis ShipLines Company. "+
           "A spacy wooden one-story building features long comfortable "+
           "benches and wide clean windows. A small table is next to the door "+
           "and a cardboard timetable is bolted to a wall.\n");

  add_exit(EXIT_TO_PIER, "east");

  add_item(({"windows", "window"}),
           "Through the window in the south wall you can see lifeguard " +
           "tower of Cadu. In the north you see the beaches of Cadu and to " +
           "the west ships and stalls are located.\n");
  add_item(({"doors", "door"}),
           "The door in the eastern wall is open and leads out.\n");
  remove_item("desk");
  add_item(({"table"}),
           "A low wooden table. A heap of leaflets is piled next to it.\n");
  set_timetable_file(CADU_GSL_OFFICE_DIR + "timetable");           
}

