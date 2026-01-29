/*
a long knife used by the halflings of Esmirin.
*/

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
set_name("knife");
set_short("long knife");
set_pshort("long knives");
set_pname("knives");
set_long("This is one of the long hunting knives common to the small "+
     "folk of Esmirin.\n");
set_adj("long");

set_hit(15);
set_pen(15);
     set_wt(W_KNIFE);
     set_dt(W_SLASH | W_IMPALE);
     set_hands(W_ANYH);
}
