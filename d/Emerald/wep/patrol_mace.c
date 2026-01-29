inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("mace");
    set_short("shiny elvish mace");
    add_adj( ({"shiny", "elvish"}) );
    set_long("The mace seems to be standard issue for the more senior "+
	"members of the Elvish patrol. The haft is strong and well balanced, "+
	"as should be expected of an elvish weapon. It seems to be well "+
	"polished, an indication of a well-cared for weapon.\n");
    set_hit(29);
    set_pen(23);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
}
