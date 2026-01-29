/* 
 * /d/Kalad/common/central/arm/bocca_robe.c
 * Purpose    : The citycouncellors robe
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Korat */
create_armour()
{
    ::create_armour();
    set_name("robe");
    set_adj("silver");
    add_adj("decorated");
    set_pname("robes");
    set_short("silver decorated robe");
    set_pshort("silver decorated robes");
    set_long("This robe is decorated with long, thin silver threads that "+
      "curls together on the back, making out the form of a silver dragon. "+
	"You are struck by the beauty of it.\n");
    set_ac(5);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE, 900);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 1500);
}
