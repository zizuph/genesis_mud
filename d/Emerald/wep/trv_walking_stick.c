inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("stick");
	add_name("walking-stick");
    set_short("knobbed walking-stick");
    add_adj( ({"knobbed", "walking"}) );
    set_long("The walking-stick seems to be an average weapon that one "+
	"might find a normal citizen carrying.\n");
    set_hit(11);
    set_pen(11);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
}
