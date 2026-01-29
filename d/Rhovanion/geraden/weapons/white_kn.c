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
set_short("white knife");
set_pshort("white knives");
set_pname("knives");
set_long("This is a knife used by the Tallfellow warriors of "+
	"Esmirin.\n");
set_adj("white");

set_hit(20);
set_pen(20);
     set_wt(W_KNIFE);
     set_dt(W_SLASH | W_IMPALE);
     set_hands(W_ANYH);
}
