/*
 *	/d/Gondor/common/arm/winghelm.c
 *
 *	Sep 1996, Olorin: Made it possible to keep the helm.
 */
#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep.c";

#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>

public void
create_armour()
{
    set_name("helm");
    add_name("helmet");
    set_pname("helms");
    add_pname("helmets");
    set_short("winged mithril helm");
    set_pshort("winged mithril helms");
    set_adj( ({ "mithril", "winged", "high-crowned" }) );
    set_long("This is a helm of strange shape: It is high-crowned, with long " +
      "cheek-guards close-fitting to the face of the wearer. Above the " +
      "cheek-guards white wings of sea-birds are set. The helm gleams with " +
      "a flame of silver, as it is indeed wrought of mithril.\n");
    set_default_armour(33,A_HEAD,({ 0, 0, 0}),0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(33, A_HEAD) + random(300));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4 );
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(33) + random(1000) );
}
