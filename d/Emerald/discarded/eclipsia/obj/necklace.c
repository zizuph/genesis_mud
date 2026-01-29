inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("necklace");
    set_short("soft gold necklace");
    add_adj(({"soft", "gold"}));
    set_long("This simple piece of jewelry is made of a thin, "+
	"soft woven golden cord. It would look beautiful adoring "+
	"any fair neck"+
	".\n");
    add_prop(OBJ_I_VALUE, 50 + random(100));
    set_ac(1);
    set_at(A_NECK);
}
