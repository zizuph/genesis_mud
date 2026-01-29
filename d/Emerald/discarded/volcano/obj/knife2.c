
inherit "/std/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/d/Avenir/common/common.h"

create_weapon ()
{
	set_name("stilleto");
	set_short("stilleto");
	set_adj("long");
	add_adj("sharp");
	set_long("A long thin knife that looks really sharp.\n");
	set_hit(12);
	set_pen(16);

	set_wt(W_KNIFE);
	set_dt(W_IMPALE);
	set_hands(W_ANYH);
  set_likely_dull(18);
  set_likely_corr(0);
  set_likely_break(8);
}
