/*
 *   The storage room of the Telberin General Store
 */

inherit "/d/Emerald/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>

/* prototypes */
public void        reset_room();

/* global variables */
public object     *Oil,
                  *Torch,
                  *Lamp,
                  *Pack,
                  *Rope,
                  *Shovel;
public int         Nr;        
public int         Num = 3;


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room() 
{
   set_short("The store room of the General Store of Telberin");
   set_em_long("This is the store room for the General Store of Telberin.\n");

   add_exit("/d/Emerald/telberin/mercantile/general_store", "east",0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

   Nr = 3 + random(6);
   Oil = allocate(Nr);
   Torch = allocate(Num);
   Lamp = allocate(Num);
   Pack = allocate(Num);
   Rope = allocate(Num);
   Shovel = allocate(Num);

   enable_reset(200); /* fast resets */
   reset_room();
} /* create_emerald_room */


/*
 * Function name:        reset_room
 * Description  :        make sure the store room has
 *                       adequate supplies
 */
public void
reset_room()
{
    object  shovel;
    int     i;
            

    setuid();
    seteuid(getuid());

    for(i = 0; i < Num; i++)
    {
        if(!Shovel[i] || !present(Shovel[i],this_object()))
        {
            Shovel[i] = clone_object("/d/Emerald/obj/shovel");
            Shovel[i]->move(this_object());
        }
    }

    for(i = 0; i < Num; i++)
    {
        if(!Torch[i] || !present(Torch[i],this_object()))
        {
            Torch[i] = clone_object("/d/Emerald/obj/torch");
            Torch[i]->move(this_object());
        }
    }

    for(i = 0; i < Num; i++)
    {
        if(!Pack[i] || !present(Pack[i],this_object()))
        {
            Pack[i] = clone_object("/d/Emerald/obj/backpack");
            Pack[i]->move(this_object());
        }
    }

    for(i = 0; i < Num; i++)
    {
        if(!Lamp[i] || !present(Lamp[i],this_object()))
        {
            Lamp[i] = clone_object("/d/Emerald/obj/oil_lamp");
            Lamp[i]->move(this_object());
        }
    }

    for(i = 0; i < Nr; i++)
    {
        if(!Oil[i] || !present(Oil[i],this_object()))
        {
            Oil[i] = clone_object("/d/Emerald/obj/oilflask");
            Oil[i]->move(this_object());
        }
    }

    for(i = 0; i < Num; i++)
    {
        if(!Rope[i] || !present(Rope[i],this_object()))
        {
            Rope[i] = clone_object(
                "/d/Emerald/blackwall/delrimmon/obj/rope");
            Rope[i]->move(this_object());
        }
    }
} /* reset_room */
