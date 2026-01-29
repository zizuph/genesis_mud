/* Ashlar, 20 Oct 97 */
/* The storeroom for the guild shop in the temple
   It keeps a stock of standard items, which is refilled at intervals.
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Ansalon/common/defs.h"

#include <filter_funs.h>

#define MARM "/d/Ansalon/taman_busuk/mountains/obj/"
#define NARM "/d/Ansalon/taman_busuk/neraka/arm/"

#define T_S_INV ({                                                      \
    ({ MARM + "mailshirt", "_sanction_shop_chainmail", 4 }),                      \
    ({ MARM + "chainhelm", "_sanction_shop_helm", 2 }),           \
    ({ NARM + "chaingreaves", "_sanction_shop_greaves", 2}),              \
    ({ MARM + "pike", "_sanction_shop_pike", 3 }),     \
    ({ MARM + "sword", "_sanction_shop_sword", 3 }),                      \
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
   set_short("armoury store room");
   set_long("This is the store room for the Sanction armoury.\n");
   
   add_exit(SCITY + "arms_store", "out");
   
   INSIDE;  /* This is an inside room */

   set_max_values(30,0);
   
   reset_room();
}

varargs int
check_id(string cid, object ob)
{
     return ob->id(cid);
}

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
