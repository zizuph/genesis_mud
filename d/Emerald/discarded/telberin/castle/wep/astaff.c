/*
 * ASTAFF.c 
 * This is Vilgurn's Adamantine Staff :)
 * Its a rather potent weapon.
 * - Alaron November 1996
 */

#include "/d/Emerald/defs.h"
#include "../default.h"
#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>

inherit "/std/weapon";

#define STAFF_HIT 39
#define STAFF_PEN 18

void
create_weapon()
{
  set_name("quarterstaff");
  add_name("staff");
  set_adj("adamantine");
  
  set_hit(STAFF_HIT);
  set_pen(STAFF_PEN);

  set_wt(W_POLEARM);
  set_dt(W_BLUDGEON);

  set_hands(W_BOTH);
  set_wf(this_object());

  add_prop(OBJ_I_WEIGHT, 4700);
  add_prop(OBJ_I_VOLUME, 1334);

  set_likely_break(2);  // Very low chance of this thing breaking ... adamantium is super strong.

  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(STAFF_HIT, STAFF_PEN)+100); // Adamantium is worth more money
    
  set_long("This quarterstaff is unlike any you have ever seen before. It is made of pure "+
	   "adamantium (or as close to pure as your eyes can discern) and nearly two meters "+
	   "in length. The entire length of the shaft is covered with intricate carvings of various "+
	   "shapes and pictures. Placed in the most common positions for the left and right hands "+
	   "are handles made of rigid leather wrapped around the adamantine shaft. This looks "+
	   "like an incredibly formidable weapon.\n");

  add_item( ({"shaft", "carvings", "intricate carvings"}),
	    "The shaft of the powerful weapon is covered with intricate carvings of "+
	    "pictures and shapes. The carving is amazing, and you wonder how anyone got "+
	    "such finite detail carved into a cylinder of adamantium, one of the hardest "+
	    "and strongest metals known to man.\n");
   add_item( ({"pictures", "shapes", "pictures and shapes"}),
             "The pictures and shapes depicted in the carvings on "+
              "the shaft of the quarterstaff are strange and alien "+
               "to you ... almost as if they were a part of a foreign, "+
                "hieroglyphic language,\n");
}

public int 
wield()
{
  if (TP->query_race() != "elf") {
    write("The adamantine staff quickly becomes incredibly hot to the touch. You drop "+
	  "it in order to avoid burning yourself!\n");
    say(QCTNAME(TP)+" drops the "+short()+" as the smell of near-burnt flesh wafts past your "+
	"nose.\n");
    set_alarm(0.0, 0.0, &move(environment(this_player())));
    return 0;
  } else {
    write("You swing the staff around in a circle and grip the handles, testing its weight and "+
	  "balance. It feels like an excellent weapon.\n"+
	  "You wield the "+short()+" in both hands.\n");
    say(QCTNAME(TP)+" swings the "+short()+" around in a circle, testing the grip and balance "+
	"of the shining weapon.\n"+QCTNAME(TP)+" wields the "+short()+" in both hands.\n");
    return 1;
  }
}
