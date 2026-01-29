/* Seal of the Hegemon, for the Registry 
 * Lilith, March 2004
 */
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

void 
create_object()
{
    set_name("seal");
    add_name(({"stamp", "av_registry_seal"}));
    set_short("gold-leaf seal");
    add_adj(({"gold", "gold-leaf"}));
    set_long("This is a beautiful gold-leaf seal stamped with the "+
        "image of a stern-looking elf. It is used to certify that "+
        "relationships have been correctly registered at the "+
        "Registry of Cynrede.\n");
    add_prop(OBJ_I_VALUE,  3800);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_WEIGHT, 250);
}
