
inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include <ss_types.h>
#include "/sys/macros.h"


void
create_shire_room()
{
    object mbundle;

    set_short("Master bundle control room.");
    set_long("A small room.\n");

    add_prop(ROOM_I_NO_CLEANUP,1);

    mbundle = clone_object("/d/Shire/common/herbs/obj/master_bundle");
    mbundle->move(this_object());
}
