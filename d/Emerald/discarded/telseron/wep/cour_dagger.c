inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("dagger");
    set_short("long engraved dagger");
    add_adj( ({"long", "engraved"}) );
    set_long("This weapon appears very functional, even with it's ornate "+
	"engravings and workmanship. The blade is about a fingerlength "+
	"longer than most daggers it's size, and the blade is covered with "+
	"inscriptions of the Telseron Royal Family and various scenery of "+
	"the prowess of some of the more famous members in action.\n");
    set_hit(16);
    set_pen(14);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
}
