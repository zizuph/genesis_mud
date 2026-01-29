#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

void
create_krynn_monster()
{
   if (!IS_CLONE)
      return;
   
   set_name("innkeeper");
   set_short("balding innkeeper");
   set_long("This is the Innkeeper of the Jetties Inn. " +
      "His clothes are greasy and unkept. He obviously cares " +
      "little for appearances. He eyes you suspiciously. \n");
   
   set_act_time(5);
   add_act("yawn");
   add_act("grin cunn");
   set_stats(({40,40,40,40,40,40}));
   set_hp(10000);
}
