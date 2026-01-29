/* pitchfork from farm
 *  Ten Alders 
 *  Amelia 5/3/97
*/

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon()
{
    set_name("pitchfork");
    set_pname("pitchforks");
    set_adj("sharp");
    set_short("sharp pitchfork");
    set_pshort("sharp pitchforks");
    set_long("This pitchfork is a farming implement, "+
        "used to pile hay and manure. However, if wielded "+
        "by someone with skill, it could be a rather "+
        "lethal weapon.\n");
    set_default_weapon(15, 16, W_POLEARM, W_SLASH | W_IMPALE, W_BOTH);
    add_prop(OBJ_I_WEIGHT, 5500);
    add_prop(OBJ_I_VALUE, 400);
}
