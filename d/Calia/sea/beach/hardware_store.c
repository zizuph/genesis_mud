
 /* 
  *  The store room for the Shark's Tooth Shack 
  *  Coded by:  Jaacar & Maniac Sept 1996 
  *  Bug fixed by Maniac 16/10/98 
  *  Updated palace refs, Maniac, 4/2/2001 
  */ 

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include CALIAN_GUILD_BASE_DEF

#define CLONE_OBJECT(s) clone_object(s)->move(this_object())

#define MINIMUM_INVENTORY        \
 ({ ({ CRPALACE_OBJECTS + "rope",2}),\
    ({ CRPALACE_OBJECTS + "sack",2}),\
    ({ CRPALACE_OBJECTS + "backpack",4}),\
    ({ "/d/Calia/mountain/obj/chisel",1}),\
    ({ "/d/Calia/mountain/obj/fine_cloth",5}),\
    ({ "/d/Calia/sea/objects/herbpouch",6}),\
    ({ "/d/Calia/sea/objects/herb_gloves",3}),\
    ({ "/d/Calia/sea/objects/corpse_cleaner",3}),\
    ({ "/d/Calia/sea/weapons/free_knife",1})\
 })

mixed to_check = MINIMUM_INVENTORY;

int
object_filter(object obj, string path)
{
    return (MASTER_OB(obj) == path);
}


void
reset_room()
{
    object *all_inv = all_inventory();
    int i, j, num_found; 

    for (i=0; i < sizeof(to_check); i++)
        if ((num_found = sizeof(filter(all_inv, 
                  &object_filter(, to_check[i][0])))) 
                                   < to_check[i][1])
        {
             for (j = num_found; j < to_check[i][1]; j++)
                 CLONE_OBJECT(to_check[i][0]);
        }
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}


void
create_room()
{
    set_short("Shark's Tooth Shack Storeroom");
    set_long("This is the storeroom for the Shark's Tooth Shack.  "+
        "How the hell did you get in here?! Get out! <grin>\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(BEACH+"village3","south",0,0);
    reset_room();
}
