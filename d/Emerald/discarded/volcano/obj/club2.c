
inherit "/std/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/d/Avenir/common/common.h"

create_weapon ()
{
	set_name("morningstar");
	set_short("morningstar");
	set_long("A rather large deadly looking weapon.\n");

	set_hit(24);
	set_pen(35);

	set_wt(W_CLUB);
	set_dt(W_BLUDGEON);
	set_hands(W_BOTH);
  set_likely_dull(18);
  set_likely_corr(0);
  set_likely_break(8);
}
