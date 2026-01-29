/* Ashlar, 20 Oct 97 */
/* The storeroom for the guild shop in the temple
   It keeps a stock of standard items, which is refilled at intervals.
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "/d/Ansalon/common/defs.h"
#include "../defs.h"

#include <filter_funs.h>

/*    ({ "/d/Ansalon/guild/pot/obj/holywater", "_temple_shop_phial", 3 }),\*/
#define T_S_INV ({                                                      \
    ({ NWEP + "mace", "_temple_shop_mace_2h", 2 }),                     \
    ({ NWEP + "mace1h", "_temple_shop_mace_1h", 3 }),                   \
    ({ NARM + "crescent_shield", "_temple_shop_shield", 3 }),           \
    ({ NARM + "black_chain_shirt", "_temple_shop_chainshirt", 3 }),     \
    ({ NWEP + "knife", "_temple_shop_knife", 4 }),                      \
    ({ "/d/Ansalon/guild/pot/obj/sandals", "_temple_shop_sandals", 4 }),\
})

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);
}

void
create_room()
{
   set_short("store room for the temple shop");
   set_long("This is the store room for the temple shop.\n");
   
   add_exit(DUNGONE + "eqshop", "out");
   
   INSIDE;  /* This is an inside room */

   set_max_values(30,0);
   
   reset_room();
}

varargs int
check_id(string cid, object ob)
{
     return ob->id(cid);
}

void
reset_room()
{
   object ob, *p;
   mixed *obdef;
   int i,j,sz;
   
   setuid();
   seteuid(getuid());

   p = FILTER_DEAD(all_inventory(TO));

   sz = sizeof(T_S_INV);
   for (i = 0; i < sz; i++)
   {
   	obdef = T_S_INV[i];

   	for (j = sizeof(filter(p,&check_id(obdef[1],))); j < obdef[2]; j++)
   	{
   	    ob = clone_object(obdef[0]);
   	    ob->add_name(obdef[1]);
   	    ob->move(TO);
   	}
   }
}
