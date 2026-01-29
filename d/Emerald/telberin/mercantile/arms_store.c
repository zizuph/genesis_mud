/*
 *   The storage room of the Telberin Arms Shop
 */

inherit "/d/Emerald/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>

/* prototypes */
public void        reset_room();

/* global variables */
public object     *Sword,
                  *Mace,
                  *Axe,
                  *Polearm,
                  *Knife;
public int         Nr;        
public int         Num = 2;


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
   set_short("The store room of the Arms Dealer of Telberin");
   set_em_long("This is the store room for the Telberin Arms Dealer.\n");

   add_exit("/d/Emerald/telberin/mercantile/arms_shop", "east",0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

   Nr = 2 + random(3);
   Sword = allocate(Nr);
   Mace = allocate(Num);
   Axe = allocate(Num);
   Polearm = allocate(Num);
   Knife = allocate(Num);

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
    int     i;
            
    setuid();
    seteuid(getuid());

    for(i = 0; i < Num; i++)
    {
        if(!Mace[i] || !present(Mace[i],this_object()))
        {
            Mace[i] = clone_object("/d/Emerald/telberin/obj/wep/mace");
            Mace[i]->move(this_object());
        }
    }

    for(i = 0; i < Num; i++)
    {
        if(!Polearm[i] || !present(Polearm[i],this_object()))
        {
            Polearm[i] = clone_object("/d/Emerald/telberin/obj/wep/halberd");
            Polearm[i]->move(this_object());
        }
    }

    for(i = 0; i < Num; i++)
    {
        if(!Axe[i] || !present(Axe[i],this_object()))
        {
            Axe[i] = clone_object("/d/Emerald/telberin/obj/wep/battleaxe");
            Axe[i]->move(this_object());
        }
    }

    for(i = 0; i < Nr; i++)
    {
        if(!Sword[i] || !present(Sword[i],this_object()))
        {
            Sword[i] = clone_object("/d/Emerald/telberin/obj/wep/longsword");
            Sword[i]->move(this_object());
        }
    }

    for(i = 0; i < Num; i++)
    {
        if(!Knife[i] || !present(Knife[i],this_object()))
        {
            Knife[i] = clone_object(
                "/d/Emerald/telberin/obj/wep/dagger");
            Knife[i]->move(this_object());
        }
    }
} /* reset_room */
