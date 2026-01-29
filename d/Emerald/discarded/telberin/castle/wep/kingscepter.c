inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("sceptre");
    add_name("scepter");
    set_short("ornate, emerald-mounted great sceptre");
    add_adj( ({"ornate", "emerald-mounted", "mounted", "great"}) );
    set_long("This massive sceptre has a very large emerald mounted "+
	"at the top of it, upon it's solid gold, heavy shaft. Upon the "+
	"shaft is engraved the royal seal of Telberin, upon which is "+
	"the symbol of the lands of Emerald. The sceptre has gold "+
	"leaves running up the sides, holding the emerald in place."+
	"\n");
    set_hit(20);
    set_pen(30);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_RIGHT);
}
