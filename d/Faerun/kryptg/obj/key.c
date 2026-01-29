/*                         
 * Random object for citadel
 * Finwe, April 2008
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/key";
inherit "/lib/keep";

create_key()
{
    seteuid(getuid());

    set_name("key");
    set_adj(({"iron", "large"}));
    set_short("large iron key");
    set_pshort("large iron keys");
    set_long("The large iron key looks rusty and well used. The teeth are smooth from constant use.\n");
    set_key(9035768);
}
