#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

inherit "/lib/store_support";
inherit R_FILE

#define WEP "/d/Krynn/solamn/splains/obj/bmace"
#define ARM "/d/Krynn/solamn/splains/obj/barmour3"

object cutlass, bandana;

void
reset_krynn_room()
{
  reset_euid();

  if(!cutlass)
    (cutlass = clone_object(WEP))->move(TO);
  if(!bandana)
    (bandana = clone_object(ARM))->move(TO);

}

create_krynn_room()
{
    set_short("keep storeroom");
    set_long("keep storeroom.\n");

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 1);

    reset_krynn_room();
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);

}