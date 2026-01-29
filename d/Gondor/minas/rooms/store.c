/*
 *   The storage room of the Minas Tirith shop
 */

inherit "/d/Gondor/common/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* prototype */
void reset_room();

object *oil;
int nr;

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room() 
{
   set_short("The store room of Minas Tirith General Store");
   set_long("This is the store room for the Minas Tirith General Store.\n");

   add_exit("/d/Gondor/minas/rooms/mtshop", "south",0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
   nr = 3 + random(6);
   oil = allocate(nr);
   reset_room();
}

void
reset_room()
{
  int i;

  if (!present("torch"))
    clone_object(OBJ_DIR + "torch")->move(TO);
  for(i = 0; i < nr; i++)
  {
    if(!oil[i] || !present(oil[i],TO))
    {
      oil[i] = clone_object("/d/Gondor/common/obj/oilflask");
      oil[i]->move(TO);
    }
  }
  if (!present("lamp"))
    clone_object("/d/Gondor/common/obj/oil_lamp")->move(TO);
}

