
inherit "/std/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/d/Avenir/common/common.h"

create_weapon ()
{
	set_name("cinquedea");
	add_name("dagger");
	add_name("knife");
	set_short("cinquendea");
	set_adj("ornate");
	set_long("A very large, broad dagger.\n");
	set_hit(16);
	set_pen(14);

	set_wt(W_KNIFE);
  set_dt(W_SLASH);
	set_dt(W_IMPALE);
	set_hands(W_ANYH);
  set_likely_dull(18);
  set_likely_corr(0);
  set_likely_break(8);
}
