inherit "/std/paralyze";
#include "/sys/stdproperties.h"

void
create_paralyze()
{
    set_stop_verb("");
    set_stop_object(0);
    set_fail_message("You can't do that! One of the seamonster's "+
      "tendrils is wrapped around you.\n");
    set_stop_message("You manage to break free from the tendril.\n");
    set_remove_time(30);
}





