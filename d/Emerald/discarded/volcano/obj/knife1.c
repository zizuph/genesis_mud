
inherit "/std/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/d/Avenir/common/common.h"

create_weapon ()
{
	set_name("hunting knife");
	add_name("knife");
	set_short("hunting knife");
	set_long("A rather sharp hunting knife.\n");

	add_prop(OBJ_I_VALUE, 255);
	add_prop(OBJ_I_WEIGHT, 1000);
	add_prop(OBJ_I_VOLUME, 600);

	set_hit(17);
	set_pen(15);

	set_wt(W_KNIFE);
  set_dt(W_SLASH);
	set_hands(W_ANYH);
  set_likely_dull(18);
  set_likely_corr(0);
  set_likely_break(8);
}
