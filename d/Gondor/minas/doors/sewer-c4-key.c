inherit "/std/key";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_key()
{
    add_name("MT_sewer_crc4");
    set_key("MT_sewer_crc4");

    set_long(BSN(
        "It is a small metal key. It shows hardly any traces of "
      + "wear, so it must be either rather new or it has hardly "
      + "been used. The bit is quite long compared to the rest of "
      + "the key and looks very intricated."));

    set_adj(({"small", "metal", }));
    add_prop(OBJ_I_VALUE, 0);
}
