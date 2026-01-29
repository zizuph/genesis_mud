/*  /d/Ravenloft/droptables/fos_drops/e_fos_set_helm.c
 *
 *  Epic armouritem. Drops from chest in the
 *  Forest of Shadows, tomb.
 *
 *
 *  Nerull, 2015
 *
 */

inherit "/std/armour";
#include "../defs.h";
#include "/d/Ravenloft/defs/magicalitems_stats.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

// Custom name.
string wname = "Jakredak";

void
create_armour()
{
    set_name("helm");
    set_adj(wname);
    add_adj("bone");

    set_short(wname +" bone helm");
    set_pshort(wname +" bone helms");

    set_long("Pulsing with necromantic powers this helm "
    +"fulfills " + wname + "'s prayer. " + wname + "'s skull has been "
    +"hollowed and cast in adamantine. The magics of this "
    +"skull keep it alive and feeling of flesh and if you wore "
    +"it would meld to your face creating an eerie view "
    +"as you gazed from " + wname + "s eyesockets. The helm pulses "
    +"inside, seemingly to embed itself into your skull "
    +"if worn. This helm is extremely cold.\n");

    set_default_armour(TOMB_E_HELM_AC, A_HEAD, 0, this_object());

	add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

	add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));

	add_prop(MAGIC_AM_ID_INFO, ({ "This armour is enchanted to give "
		+ "better protection.\n",1, }));

	add_prop(OBJ_S_WIZINFO, "This is a Rare armour dropping from monsters in "
		+ "the Forest of Shadows, Ravenloft. "
		+ "It is slightly enchanted to offer better ac.\n");

    add_prop(OBJ_I_VALUE, TOMB_E_HELM_VALUE);
    add_prop(OBJ_I_WEIGHT, TOMB_E_HELM_WEIGHT);
    add_prop(OBJ_I_VOLUME, TOMB_E_HELM_VOLUME);
}


