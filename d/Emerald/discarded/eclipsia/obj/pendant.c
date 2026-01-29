inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("pendant");
    set_short("shell-studded emerald pendant");
    add_adj(({"shell-studded", "emerald"}));
    set_long("This striking piece of jewelry is a thin, "+
	"soft gold-wire rope with a shell-studded pendant "+
	"hanging from it. Inset into the base of the pendant "+
	"is an impressive emerald that gleams as you turn it. "+
	"The shells on the pendant are a lovely pattern of gold "+
	"and black"+
	".\n");
    add_prop(OBJ_I_VALUE, 600 + random(200));
    set_ac(2);
    set_at(A_NECK);
}
