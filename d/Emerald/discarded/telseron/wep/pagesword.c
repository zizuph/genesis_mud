inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Emerald/defs.h"

void
create_weapon()
{
    set_name("shortsword");
    set_short("light shortsword");
    add_adj( ({"light", "elvish"}) );
    set_long("This shortsword seems to be rather light for a warrior's "+
	"weapon. It bears many scars and appears to have been used for "+
	"years and years of novice practice. It looks like it's handed "+
	"down to training pages who graduate to a more suitible sword "+
	"after they have earned the right.\n");
    set_hit(20);
    set_pen(15);
    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
}
