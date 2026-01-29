
inherit "/std/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/d/Avenir/common/common.h"

create_weapon ()
{
	set_name("flail");
	set_adj("grey");
	add_adj("menacing");
	set_short("flail");
	set_long("A large, sinister looking flail.\n");
	set_hit(21);
	set_pen(21);

	set_wt(W_CLUB);
	set_dt(W_BLUDGEON);
	set_hands(W_BOTH);
  set_likely_dull(18);
  set_likely_corr(0);
  set_likely_break(8);
}
