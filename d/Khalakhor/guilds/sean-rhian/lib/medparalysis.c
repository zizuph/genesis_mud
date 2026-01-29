//
// Meditation Paralysis object - paralyze saggart while he's meditating
//
inherit  "/std/paralyze";
#include "../room/meditation.h"
 
void create_paralyze()
{
    add_name(MED_PARALYSIS_OBJID);
    set_remove_time(MED_PARALYSIS_TIME); // for emergency stop only
    set_stop_fun("stop_paralyze");
    set_stop_object(previous_object());
    set_stop_message("Your mind clears and you awaken from meditation.\n");
    set_fail_message("Your mind is locked in meditation.\n");
}
