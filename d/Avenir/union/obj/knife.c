/* Just a guild knife, good for throwing */
#pragma strict_types
#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "../defs.h"
#include "/d/Avenir/include/deities.h"   /* Altar & diety-related defines */

public string *randadj = ({"long", "shiny", "slender", "light", "small"});


public void
create_weapon()
{
    string myadj = one_of_list(randadj);

    set_name("dagger");
    add_name(({"knife","blade"}));
    set_pname(({"daggers","knives","blades","weapons"}));
    set_adj(myadj);
    add_adj("union");
    set_short(myadj + " dagger");
    set_long("It is a long and shiny dagger, suitable "
      +"for throwing. The blade of the dagger in "
      +"not very sharp, but the point is as thin "
      +"as a needle.\n");

    set_default_weapon(12, 12, W_KNIFE, W_IMPALE, W_NONE, TO);

    set_likely_dull(6);
    set_likely_corr(8);
    set_likely_break(0);
    set_hands(W_ANYH);

    set_keep();

    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 210 + random(50));
    add_prop(JAZUR_OFFERING, 1);
}

public int
wield(object to)
{
    if (TP != ENV(TO))
	return 0;

    write("You wrap your hand around the hilt of "+
	LANG_THESHORT(to)+".\n");
    say(QCTNAME(TP) +" wraps "+ HIS(TP) +" hand around the "+
	"hilt of "+ LANG_ASHORT(TO) +".\n");

    return 1;
}
