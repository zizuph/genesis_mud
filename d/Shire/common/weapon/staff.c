/*
 *  A staff that is slightly enchanted.  Cloned by
 *  ~Shire/common/hobbiton/npc/quest_hobbit.c
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
   set_short("long staff");
   set_pshort("long staves");
   set_adj("long");
   set_long("This is a very old staff. It is cluttered with markings that.\n"
	    + "look like old runes. They are almost completely worn down\n"
	    + "however.\n"); 
   ran = random(4);
   set_hit(12 + ran);
   set_pen(11 + ran);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_BOTH);

   add_prop(MAGIC_AM_MAGIC, ({ 22, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO , ({ "This staff is enchanted. It seems that "
			    + "most of it has worn out though." , 20 }));

   add_prop(OBJ_I_WEIGHT, 3000); /* 3 Kg */
   add_prop(OBJ_I_VALUE, ran*ran*ran/4 + 100);
    

}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
