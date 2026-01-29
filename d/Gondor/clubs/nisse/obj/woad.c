/*
 *  /d/Gondor/clubs/nisse/obj/woad.c
 *
 *  The packed of woad. The Nisse use it for painting themselves patterns
 *  on their skin.
 *
 *  Deagol, April 2003
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

void
create_object()
{
    ::create_object();
    
    set_name("woad");
    add_name(NISSE_WOAD_ID);
    set_adj("packet");
    add_adj("of");
    set_short("packet of woad");
    set_long("This " + short() + " contains a brilliant blue paste which " +
        "can be used to paint patterns on your skin. The pigment is made " +
        "from the leaves of wild indigo plants. Only the Nisse Ohtar may " +
        "paint patterns on themselves since they inherit this knowledge " +
        "and keep it in secret.\n");

    add_prop(OBJ_I_VALUE, 30);
}
