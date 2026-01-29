
/* 
   The wolfhelm sign, describes details of wolfhelms.

   Coded by Maniac, 4/1/96.

*/

#pragma save_binary

inherit "/std/scroll";
#include <stdproperties.h>
#include "defs.h"

void
read_it(string str)
{
    ::read_it("mread");
}

void
create_scroll()
{
    set_name("sign");
    set_adj("steel");
    set_short("steel sign");
    set_long("A steel sign with a large header that reads:\n" +
             "    DON'T LOSE YOUR HEAD!\n");
    set_file(GLYKRON_TEXTS+"wolfhelm");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_M_NO_GET, 1);
}

