inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/d/Cirath/common/defs.h"

void create_weapon()
{
	set_name("mace");
	set_short("bone training mace");

   set_long("Slightly better than a wooden mace, this bone "
	+"mace still looks mainly like a training weapon.  "
	+"It could be used in a real fight, but would not be "	
	+"that effective.\n");
	
	set_adj  ("bone");
	set_adj  ("training");

	set_hit(20);
	set_pen(20);

	set_wt(W_CLUB);
	set_dt(W_IMPALE | W_BLUDGEON);
	set_hands(W_RIGHT);
	add_prop(OBJ_I_WEIGHT,1500);
	add_prop(OBJ_I_VOLUME,1000);
}
