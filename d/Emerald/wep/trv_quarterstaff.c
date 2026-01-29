inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("quarterstaff");
	add_name("staff");
    set_short("tall oaken quarterstaff");
    add_adj( ({"tall", "oaken", "oak"}) );
    set_long("The quarterstaff seems to be an average weapon that one "+
	"might find a normal citizen carrying.\n");
    set_hit(14);
    set_pen(12);
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
}
