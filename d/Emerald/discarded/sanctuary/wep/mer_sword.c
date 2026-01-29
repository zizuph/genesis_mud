inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("longsword");
    set_short("shiny elvish longsword");
    add_adj( ({"shiny", "elvish"}) );
    set_long("The longsword seems to be standard issue for the more senior "+
	"members of the Elvish patrol. The blade is sharp and well balanced, "+
	"as should be expected of an elvish weapon. It seems to be well "+
	"polished, an indication of a well-cared for weapon.\n");
    set_hit(29);
    set_pen(24);
    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
}
