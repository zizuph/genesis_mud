
inherit "/std/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/d/Avenir/common/common.h"

create_weapon ()
{
	set_name("spiked club");
	add_name("club");
	set_short("spiked club");
	set_long("A large club with spiked points that the tribesman uses for catching his dinner.\n");


	set_hit(20);
	set_pen(17);

	set_wt(W_CLUB);
	set_dt(W_BLUDGEON);
	set_wt(W_IMPALE);
	set_hands(W_ANYH);
  set_likely_dull(18);
  set_likely_corr(0);
  set_likely_break(8);
}
