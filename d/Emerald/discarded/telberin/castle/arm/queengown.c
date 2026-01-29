inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("gown");
    set_short("emerald-green, silk gown");
    add_adj(({"emerald-green", "silk" }));
    set_ac(8);
    set_at(A_ROBE);
    set_long("This lovely gown is made of the finest silk, dyed "+
	"a brilliant emerald-green. The neckline delicately dips "+
	"down in a gentle curve, and billows out into flared "+
	"sleeves that run all the way down to a point on the "+
	"wearers fingertips. The skirt softly falls to the ground, "+
	"flaring at the front to show off a soft-silver lining. "+
	"The back of the skirt trails behind in a long, flowing "+
	"train."+
	"\n");
}
