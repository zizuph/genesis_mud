/*
 *  A staff that is slightly enchanted.  Used by
 *  Tobold, Jaypeg's experimental Bounder NPC
 */

inherit "/std/weapon";

#include <macros.h>
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/sys/wa_types.h"
#include "/d/Shire/common/defs.h"

create_weapon() {
   int ran;

   set_name("staff");
   set_pname("staves");
   add_adj("oak");
   set_short("long oak staff");
   set_pshort("long oak staves");
   set_adj("long");
   set_long("This is a very old staff. It is cluttered with markings that.\n"
	    + "look like old runes. They are almost completely worn down\n"
	    + "however.\n"); 
   ran = random(9);
   set_hit(22 + ran);
   set_pen(21 + ran);
   set_wt(W_POLEARM);
   set_dt(W_BLUDGEON);
   set_hands(W_BOTH);

   add_prop(MAGIC_AM_MAGIC, ({ 44, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO , ({ "This staff is enchanted. It seems that "
			    + "most of it has worn out though." , 20 }));

   add_prop(OBJ_I_WEIGHT, 5000); /* 5 Kg */
   add_prop(OBJ_I_VALUE, ran*ran*ran/4 + 800);
    

}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
