inherit "/std/object";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
#define QUEST_RING "_quest_ring_"

void
create_object()
{
    ::create_object();
    set_name("ring");
    set_adj("jeweled");
    add_adj("gold");
    set_short("jeweled gold ring");
    set_long("This is an expensive ring, obviously belonging to a "
	+"noble.  You see an inscription inside the band with some "
	+"words on it.\n");
    add_item("words","In strange runic writing it appears to spell "
	+"Arman.\n");
    add_prop(OBJ_I_VALUE,1000);
    add_prop(QUEST_RING,1);

}


