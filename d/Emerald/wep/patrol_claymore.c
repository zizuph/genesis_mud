inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("claymore");
    set_short("shiny elvish claymore");
    add_adj( ({"shiny", "elvish"}) );
    set_long("The claymore seems to be the weapon of choice for the champion "+
	"members of the Elvish patrol. The blade is razor-sharp and "+
	"incredibly well balanced, even for an elvish weapon. It seems "+
	"to be lovingly polished, an indication of a treasured weapon.\n");
    set_hit(35);
    set_pen(35);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_BOTH);
}
