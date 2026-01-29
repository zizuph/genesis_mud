/* A key for the storage shed atop Amon Din. Gorboth July '95 */

inherit "/std/key";

#include "/d/Gondor/defs.h"

create_key()
{
    ::create_key();

    set_name("key");
    add_name("amon_din_storage_key");
    set_pname("keys");
    set_short("shiny key");
    set_pshort("shiny keys");
    set_adj(({"shiny","small"}));
    set_long(BSN("This rather small key is quite shiny. It gleams"
	       + " when light falls upon it."));
    set_key("amon_din_storage_key");
}
