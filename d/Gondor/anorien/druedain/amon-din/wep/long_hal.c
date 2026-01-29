#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("halberd");
    add_adj(({"long-shafted","steel"}));
    set_short("long-shafted steel halberd");

    set_default_weapon(31,40,W_POLEARM,W_SLASH|W_IMPALE,W_BOTH,0);
    set_wf(TO);

    set_long(BSN("This is a very magnificent weapon to look upon."
      + " Having been cunningly crafted from many layers of"
      + " steel, it has a long and supple blade which makes"
      + " it a formidable weapon for an experienced soldier."
      + " Upon the back of the weapon is a heavy counterweight"
      + " bearing the emblem of Minas Tirith."));
    add_item(({"emblem","emblem of minas tirith","counterweight"}),
        BSN("The emblem on the counterweight of this halberd is"
      + " of a white tree crowned by seven stars."));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(40, W_POLEARM)
	     + 5000 + random(2001));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(31, 40) + random(501));
}

int
wield(object wep)
{
    int     min_str = 75 + random(11) - 5;

    if (TP->query_stat(SS_STR) < min_str)
    {
        write(BSN("You attempt to heft the " +short()+ " into a"
          + " battle-ready position, but realize that you are not"
          + " strong enough to handle it well."));
        say(QCTNAME(TP) + " attempts to wield the " +short()+ ", but"
          + " does not seem to be able to lift it properly.\n");
        return -1;
    }

    write("Mustering your strength, you heft the " +short()+ " into"
      + " a battle-ready position.\n");
    say(QCTNAME(TP) + " grunts as " +PRONOUN(TP)+ " wields the "
      +short()+ ".\n");
    return 1;
}
