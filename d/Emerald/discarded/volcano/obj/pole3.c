
inherit "/std/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>

create_weapon ()
{
	set_name("gisarme");
	set_short("gisarme");
	set_long("A gisarme with a shar convave edge to it.\n");

	set_hit(27);
	set_pen(32);

	set_wt(W_POLEARM);
	set_dt(W_IMPALE);
	set_dt(W_SLASH);
	set_hands(W_BOTH);
  set_likely_dull(18);
  set_likely_corr(0);
  set_likely_break(8);
}
