/*
 *   The storage room of the Edoras general store
 */

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

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
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");

   add_exit(EDORAS_DIR + "shop", "east",0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
   nr = 3 + random(6);
   oil = allocate(nr);

   reset_room();
}

void
reset_room()
{
  int i;
  FIX_EUID
  if (!present("backpack",TO))
  {
    clone_object(EDORAS_DIR + "obj/backpack")->move(TO);
    clone_object(EDORAS_DIR + "obj/backpack")->move(TO);
  }
  if (!present("torch",TO))
  {
    clone_object(OBJ_DIR + "torch")->move(TO);
    clone_object(OBJ_DIR + "torch")->move(TO);
    clone_object(OBJ_DIR + "torch")->move(TO);
  }
  for(i = 0; i < nr; i++)
  {
    if(!oil[i] || !present(oil[i],TO))
    {
      oil[i] = clone_object(OBJ_DIR + "oilflask");
      oil[i]->move(TO);
    }
  }
  if (!present("lamp",TO))
  {
    clone_object(OBJ_DIR + "oil_lamp")->move(TO);
    clone_object(OBJ_DIR + "oil_lamp")->move(TO);
  }
}
