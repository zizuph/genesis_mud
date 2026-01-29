/* 
 * Karath 10/6/96
 * Mundane Trident for the River Guide of Emerald.
 */

inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include <ss_types.h>
#include <options.h>
#include "/d/Emerald/defs.h"
#include <filter_funs.h>

void
create_weapon()
{
    set_name("trident");
    add_name("polearm");
    set_short("ornate blue-steel trident");
    add_adj( ({"ornate", "steel", "blue", "blue-steel"}) );
    set_long("This trident is made of strong, lightweight blue-steel. "+
	"The tines are rather wide and thick, making it a stronger weapon, "+
	"not likely to break. Two river-trout are riding a wake of foam "+
	"embossed into the outer-tines."+
	"\n\n");
    set_hit(35);
    set_pen(39);
    set_wt(W_POLEARM);
    set_dt(W_SLASH|W_IMPALE);
    set_hands(W_BOTH);
}
