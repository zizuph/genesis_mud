inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("breastplate");
    set_short("leather-lined steel breastplate");
    add_adj(({"leather-lined", "steel"}));
    set_long("This breastplate seems to be a fairly light armour for it's "+
	"protection. The inside is lined with padded leather to give added "+
	"protection against blows.\n");
    set_ac(35);
    set_am( ({-1,0,1}) );
    set_at(A_BODY);
}
