inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include "/d/Krynn/solace/graves/local.h"

create_weapon()
{
	set_name("sword");
	set_adj("battered");
	set_short("battered sword");
    add_adj("metal");  /* it is, isn't it? -Gorboth */
	set_long("It's a very old looking battered sword, you wonder how old it is.\n");
	set_default_weapon(10, 10, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
	add_prop(OBJ_I_VOLUME, 400);
	set_dull(1);
        set_corroded(2);
}
 
