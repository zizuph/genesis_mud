
/* made by Korat 16.02 1995 */
inherit "/std/receptacle";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>



void
create_receptacle()
{
   set_name("shrine");
   set_adj("golden");
   set_long("This is the shrine of Rahxvan! "+
      "It is the receptacle of His sacred relics, and what "+
      "a sight it is: Made of pure gold with gems inserted into it in "+
      "delicate patterns. You gasp at the sight of it.\n");
   add_prop(CONT_I_WEIGHT, 40000);
   add_prop(CONT_I_MAX_WEIGHT, 100000);
   add_prop(CONT_I_VOLUME, 10000);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   add_prop(OBJ_I_VALUE,100000);
   add_prop(OBJ_M_NO_SELL,1);
   add_prop(CONT_I_TRANSP, 0);
   add_prop(CONT_I_RIGID,1);
   add_prop(OBJ_I_NO_GET,"You cannot move it an inch. It is as it gets heavier "+
      "the more force you put into lifting it.\n");
   set_alarm(0.0,0.0,"add_scroll");
}
add_scroll()
{
   object scroll;
   seteuid(getuid(this_object()));
   scroll=clone_object(CPASS(dwarf/obj/quest_scroll))->move(TO);
   change_prop(CONT_I_CLOSED, 1);
}

