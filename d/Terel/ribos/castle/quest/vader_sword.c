/* A weapon should always begin with these statements: */

inherit "/std/weapon";
#include <stdproperties.h>
#include <macros.h>
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */

create_weapon()
{
    ::create_weapon();
    set_name("sword");
    set_adj("vader's");
    set_short("Vader's sword");
    set_long("This sword was the very first sword ever wielded by Vader.  " +
	     "It took quite a bit of work to track it down.  I'm sure your " +
	     "wondering 'Why Bother?', especially considering that its " +
	     "not a very good sword.\n");

    set_hit(3);
    set_pen(3);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
}
