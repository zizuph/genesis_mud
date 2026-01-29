// Head on Nochipa
// Used in the Gate of Cahor quest
//   -Ilyian, October 15, 1995
inherit "/std/leftover";
#include "/d/Avenir/common/common.h"

create_leftover()
{
   set_name("head");
   add_name("_head_of_nochipa");
   add_prop("_is_head_of_nochipa",1);
   set_short("blonde-haired head");
   set_long("This is the torn remains of what was once "
           +"a beautiful head. Long blonde hair, stained "
           +"with dark blood, is matted to the the back of "
           +"the head, and tangles in the ragged mess that was "
           +"once the neck.\n");
   set_decay_time(2000);
}
