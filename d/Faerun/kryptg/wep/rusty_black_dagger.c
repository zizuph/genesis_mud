/* /d/Faerun/kryptg/wep/rusty_black_dagger.c
 *
 * Just a regular corroded dagger with 10/10 hit/pen.
 *
 * by Nerull, 2020
 */
#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;
inherit "/lib/keep";

void
create_faerun_weapon()
{
    seteuid(getuid());

    set_name("dagger");
    add_pname(({"daggers"}));
    
    set_adj("rusty");
    set_adj("black");
    
    set_short("rusty black dagger");
    set_pshort("rusty black daggers");
   
    set_long("The blade of this dagger about five fingers "
    +"wide at the guard and it probably used to be about "
    +"over 20 inches long but now it is broken in half "
    +"and corroded beyond recognotion. The hilt itself used "
    +"to be a wooden and leather grip which is now shriveled "
    +"and torn. The crossguard itself is in prime condition "
    +"though and made from a dull black metal with considerable "
    +"weight for it size.\n");
    
    set_default_weapon(10, 10, 
    W_KNIFE, W_SLASH | W_IMPALE, W_RIGHT, this_object());
    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(40, W_KNIFE));
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, 150);
    
    // Make it keepable by default.
    set_keep();
}
    

