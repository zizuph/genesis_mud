/* Modified clothe_store to conform new gizmo requirements about
 * reset inventories. 
 * Modified by Marisol for the clothes store in Ovejuno (02/19/99)
 */

inherit "/std/room";
inherit "/lib/store_support.c";
#include "/d/Emerald/sys/macros.h";

#include <stdproperties.h>
#include <defs.h>


#define BLOUSE OV_ITEMS + "f_blouse.c"
#define SKIRT  OV_ITEMS + "skirts.c"
#define SHIRT  OV_ITEMS + "m_shirt.c"
#define PANTS  OV_ITEMS + "pants.c"

void
create_room()
{
        

   set_short("The clothes shop's store room");
   set_long("This is the store room for the Clothes shop.\n");

    add_prop(ROOM_I_INSIDE, 1);

    set_default_stock( ({ BLOUSE, 4, SKIRT, 4, SHIRT, 4, PANTS, 4 }) );
    reset_store();

}                                                            
 
void
enter_inv(object obj, object from)
{
        ::enter_inv(obj, from);
        store_update(obj);
}

void
reset_room()
{
      
    reset_store();

}
                                                  
