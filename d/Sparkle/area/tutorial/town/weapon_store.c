/*
 *  /d/Sparkle/area/tutorial/silverdell/weapon_storage.c
 *
 *  The storage room of the Silverdell General Store.
 *
 *  Supports store file:
 *    /d/Genesis/login/new/silverdell/rooms/weapon_shop.c
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;
inherit "/lib/store_support";

#include <stdproperties.h>

/* prototypes */
public void        reset_room();

/* global variables */
public object     *Oil,
                  *Torch,
                  *Lamp,
                  *Pack;       
public int         Num = 8;


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell() 
{
   set_short("The store room of the Weapon Shop of Telberin");
   set_long("This is the store room for the Weapon Shop of Silverdell.\n");

    add_exit("weapon_shop", "west");

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

   Oil = allocate(Num);
   Torch = allocate(Num);
   Lamp = allocate(Num);
   Pack = allocate(Num);

   reset_room();
} /* silverdell_room */


/*
 * Function name:        reset_room
 * Description  :        make sure the store room has
 *                       adequate supplies
 */
public void
reset_room()
{
    int     i;
            
    setuid();
    seteuid(getuid());

    for(i = 0; i < Num; i++)
    {
        if(!Torch[i] || !present(Torch[i],this_object()))
        {
            Torch[i] = clone_object(OBJ_DIR + "torch");
            Torch[i]->move(this_object());
        }
    }

    for(i = 0; i < Num; i++)
    {
        if(!Pack[i] || !present(Pack[i],this_object()))
        {
            Pack[i] = clone_object(OBJ_DIR + "backpack");
            Pack[i]->move(this_object());
        }
    }

    for(i = 0; i < Num; i++)
    {
        if(!Lamp[i] || !present(Lamp[i],this_object()))
        {
            Lamp[i] = clone_object(OBJ_DIR + "oil_lamp");
            Lamp[i]->move(this_object());
        }
    }

    for(i = 0; i < Num; i++)
    {
        if(!Oil[i] || !present(Oil[i],this_object()))
        {
            Oil[i] = clone_object(OBJ_DIR + "oilflask");
            Oil[i]->move(this_object());
        }
    }
} /* reset_room */