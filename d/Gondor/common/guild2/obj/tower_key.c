#pragma save_binary

inherit "/std/key";

#include "/d/Gondor/defs.h"

void
create_key()
{
    add_name("_Morgul_Tower_Key");
    set_key("_Morgul_Tower_Key");

    set_long(BSN(
        "It is a large iron key. It shows the traces of daily "
      + "wear. The grip is formed in the shape of a moon and is "
      + "disfigured by a death's head etched into the metal. "
      + "The bit is long and very intricately shaped."));

    set_adj(({"large", "iron", }));
}