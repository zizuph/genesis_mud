/*
 *   The storage room of the Gondorian Rangers shop
 *   2003-09-23--Tigerlily added herb wraps from the
 *      Shire, with permission from Finwe/Palmer
 */

#pragma save_binary

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define RANGER_OBJ_DIR "/d/Gondor/common/guild/obj/"

#define OIL_LAMP "/d/Gondor/common/obj/oil_lamp"
#define OILFLASK "/d/Gondor/common/obj/oilflask"
#define BACKPACK "/d/Gondor/common/guild/obj/backpack"
#define WRAP     "/d/Shire/common/herbs/obj/wrap"

void    reset_room();

object *oil;
int nr;

void
create_room() 
{
   set_short("The store-room of Gondorian Rangers Equipment Store");
   set_long("This is the store-room for the Gondorian Rangers Equipment Store.\n");

   add_exit("/d/Gondor/common/guild/gondor/shop", "south",0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
   nr = 3 + random(4);
   oil = allocate(nr);
   reset_room();
}

void
reset_room()
{
  int i;

  if (!present("torch")) clone_object(OBJ_DIR + "torch")->move(TO);
  for(i = 0; i < nr; i++)
  {
    if(!oil[i] || !present(oil[i],TO))
    {
      oil[i] = clone_object(OILFLASK);
      oil[i]->move(TO);
    }
  }
  if (!present("jar")) clone_object(RANGER_OBJ_DIR + "herbjar")->move(TO);
  if (!present("pouch")) clone_object(RANGER_OBJ_DIR + "herbpouch")->move(TO);
  if (!present("shortsword")) clone_object(WEP_DIR + "ssword")->move(TO);
  if (!present("armour")) clone_object(ARM_DIR + "studl")->move(TO);
  if (!present("oil-lamp")) clone_object(OIL_LAMP)->move(TO);
  if (!present("backpack")) {
    clone_object(BACKPACK)->move(TO);
    clone_object(BACKPACK)->move(TO);
    }
/*
  if (!present("wrap")) 
  {
    clone_object(WRAP)->move(TO);
    clone_object(WRAP)->move(TO);
  }
*/

}

void
enter_inv(object obj, object from)
{
  ::enter_inv(obj,from);
  store_update(obj);
}
