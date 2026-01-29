/*
 * /d/Ansalon/guild/society/room/kstoreroom.c
 *
 * Borrowed from Ashlar by Gwyneth sometime in 1999.
 */
inherit "/std/room";
inherit "/lib/store_support";

#include "../guild.h"
#include "/d/Ansalon/common/defs.h"

#include <filter_funs.h>

#define BLOUSE    KOBJ + "blouse"
#define LEGGINGS  KOBJ + "leggings"
#define VEST      KOBJ + "vest"
#define SHIRT     KOBJ + "shirt"
#define CAPE      KOBJ + "cape"
#define CLOAK     KOBJ + "cloak"
#define HAT       KOBJ + "hat"
#define BOOTS     KOBJ + "boots"

#define T_S_INV ({                                  \
    ({ BLOUSE, "_kender_store_blouse_", 2  }),      \
    ({ LEGGINGS, "_kender_store_leggings_", 3 }),   \
    ({ VEST, "_kender_store_vest_", 3}),            \
    ({ SHIRT, "_kender_store_shirt_", 2 }),         \
    ({ CAPE, "_kender_store_cape_", 3 }),           \
    ({ CLOAK, "_kender_store_cloak_", 3 }),         \
    ({ HAT, "_kender_store_hat_", 2 }),             \
    ({ BOOTS, "_kender_store_boots_", 2 }),         \
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
   set_short("Kender Store Room");
   set_long("This is the store room for the Kender guildhouse.\n");
   
   add_exit(KGROOM + "courtyard", "out");
   
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
