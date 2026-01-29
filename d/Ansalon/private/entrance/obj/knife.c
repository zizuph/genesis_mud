/* Modified from std_knife in ~/common/wep/knife */
/* Knife found in the dungeons for the kender quest. */
/* Gwyneth, Auguest 1999 */

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

inherit "/std/weapon";
string *knifelooks=({"silvery","sleek","leaf-shaped","sharp"});
string *knifetype=({"dagger","knife"});

create_weapon()
{
    string type = knifetype[random(2)];
    string looks = knifelooks[random(4)];
    set_name(({type,"_knife_"}));
    set_adj("large");
    add_adj(looks);
    set_short("large" + " " + looks + " " + type);
    set_long("It's a " + short() + ". It looks like a decent enough weapon.\n");
    set_default_weapon(18, 18, W_KNIFE, W_SLASH, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1000);
}


