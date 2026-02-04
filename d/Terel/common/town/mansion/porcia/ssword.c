/*
    Modified: 5 May 2003, by Bleys
        - updated to use modern Terel defs and modern sys defs
        - added a set_short to get around the "He is wielding
            an unwielded silver longsword" issue.
*/
#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include "/d/Terel/include/recover.h"
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

create_weapon()
{
   set_name("longsword");
   add_name("sword");
   set_adj("silver");
   set_short("silver longsword");
   set_long("A silver longsword.\n");

   set_hit(30);
   set_pen(30);
   set_wt(W_SWORD);
   set_dt(W_IMPALE | W_SLASH);

}
