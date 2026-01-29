/* Guild symbol for the gnomish racial guild.
 * Format inspired by Nick's Solamnian medal.
 * Modified by Percy
 * Completed by Dajala
 */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/gnome/guild/guild.h"
#include "/d/Krynn/gnome/guild/modules.h"

string *module_desc;
static string *modules;

/* Prototypes */

void update_flags();


void
create_object()
{
    set_name("gizmo");
    add_name("k_gizmo");
    set_short("gnomish gizmo");
    set_long(   "This is the symbol of your proud heritage as a "+
		"Krynnish gnome.  It is a bewildering collection of gears "+
		"and springs that only a true gnome could love.  There is "+
		"room for additional pieces to be clipped on.  For a list "+
		"of the modules on your gizmo, type 'modules'. For general " +
		"information about the Inventors use 'help gnomes topics'.\n");
    
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP, "You don't dare to drop your precious gizmo!\n");
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_GIVE, "You could never give your gizmo away!\n");
    update_flags();
}


void
update_flags()
{
module_desc = MODULE_DESCR;
seteuid(getuid());
save_object("/d/Krynn/gnome/guild/test_var");
}
