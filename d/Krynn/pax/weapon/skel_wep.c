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
	set_long("It's a very old looking battered sword, you wonder how old it is.\n");
	set_default_weapon(10, 10, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
	add_prop(OBJ_I_VOLUME, 400);
	set_dull(1);
        set_corroded(2);
}
 
string
query_recover()
{
    return OBJ + "skel_wep.c:" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}

void
remove_broken()
{
    add_prop(OBJ_I_BROKEN, 1);
    if (!wielded || !wielder)
        return;

    tell_object(wielder, "The " + short(wielder) + " breaks!!!\n");
    say("The " + QSHORT(this_object()) + " wielded by " + QTNAME(wielder) +
	" breaks!!!\n", wielder);

    wielder->unwield(this_object());
    remove_adj("wielded");
    wielded = 0;
}

