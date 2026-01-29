#pragma save_binary

inherit "/d/Genesis/ship/ship";

#include "defs.h"

#define RMC_EMERALD "/d/Emerald/telberin/dock/rmc_dock"

object cap;

void
create_ship()
{
  FIXEUID;

  set_deck(RMCSHIP+"gdeck");
  cap=clone_object(RMCNPC+"gcaptain");
  cap->arm_me();
  set_captain(cap);

  set_places_to_go(({ RMCROOMS + "pier",
              RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
              RMC_EMERALD,
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",
		      RMCSHIP + "ocean",}));

  set_time_between_stops(({ 15,2,2,2,2,2,2,2,2,2,2,2,15,2,2,2,2,2,2,2,2,2,2,2}));

  set_ticket_id("rich_ticket"); 
  set_name("ship");
  add_name("boat");
  set_adj("golden");
  add_adj("large");
  
  set_short("large golden ship");
  set_long(break_string(
    "This is a very impressive ship. It i large and is covered with gold. "+
    "The elegance it shows, lying in the water, has no competitor in this "+
    "world. The owner of this ship is obviously very rich, since he can afford "+
    "it. You can also see the logo of the Rich Men's Club on the side of the "+
    "ship.\n",60));

  set_alarm( 300.0, 0.0, "check_captain");

}

check_captain()
{
  if(!cap)
  {
    cap = clone_object(RMCNPC+"gcaptain");
    set_captain(cap);
    cap->move_living("X",environment(TO));
  }

  set_alarm( 300.0, 0.0, "check_captain");
}
