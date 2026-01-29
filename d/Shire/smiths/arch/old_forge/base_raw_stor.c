/*
 *   The storage room for the raw material shop room in smiths guild
 *   items needed for forging is stored here
 *   Made by Morinir 1996 for the Shire
 */

inherit "/d/Shire/room";
inherit "/lib/store_support";

#include "/d/Shire/smiths/smiths.h"
#include "forge.h"
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

object *leath, *wood, *bar;
int nr;


void
create_room() 
{
    object obj;

    set_short("Raw material storage room");
    set_long("This is the storage room where items to be sold in the raw"+
     " shop are stored. Boxes with all kinds of different items are placed"+
     " all over the room.\n");

    set_max_values(30,10);

    add_prop(ROOM_I_INSIDE,1);

    nr = 5 + random(5);
    bar = allocate(nr);
    leath = allocate(nr);
    wood = allocate(nr);

    reset_room();
}


reset_room() 
{

    int i;
    for(i = 0; i < nr; i++)
    {
      if(!leath[i] || !present(leath[i],TO))
      {
        leath[i] = clone_object(SMITHSDIR_OBJ + "sm_leath");
        leath[i]->move(TO);
      }
      if(!bar[i] || !present(bar[i],TO))
      {
        bar[i] = clone_object(SMITHSDIR_OBJ + "ir_bar");
        bar[i]->move(TO);
      }
      if(!wood[i] || !present(wood[i],TO))
      {
        wood[i] = clone_object(SMITHSDIR_OBJ + "sm_wood");
        wood[i]->move(TO);
      }
    }
}

