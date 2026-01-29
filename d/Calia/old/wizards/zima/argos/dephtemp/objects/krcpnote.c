/* A note in the possession of a Dephonian Priestess in the Kretan
** military camp.
**/
inherit "/std/scroll";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <config.h>
#include <cmdparse.h>
#define LANG_LEVEL GAMMA_LANG_LEVEL
#include "defs.h"  /* includes scrolldefs.h with Argosian Lang support */
 
void
create_scroll()
{
    set_name("scroll");
    set_adj("parchment");
    set_long("It is a small scroll with Argosian writing on it.\n");
 
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 75);
 
    set_file(OBJ_DIR+"krcpnote.txt");
}
