
inherit "/std/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>

create_weapon ()
{
	set_name("halberd");
	set_short("large halberd");
	set_long("A rather large halberd.  It has a large, sharp axe blade on the end.\n");

	add_prop(OBJ_I_VALUE, 300);

	set_hit(26);
	set_pen(39);

	set_wt(W_POLEARM);
	set_dt(W_IMPALE);
	set_dt(W_SLASH);
	set_hands(W_BOTH);
  set_likely_dull(18);
  set_likely_corr(0);
  set_likely_break(8);
}
