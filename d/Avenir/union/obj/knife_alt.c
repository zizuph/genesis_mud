/* Just a guild knife, good for throwing 
 * Union npcs slash wasn't going off because the code checks for the 
 * presence of a knife and then tries to fling it even if its wielded.
 * Adding a name for the npc special to look for "_npc_flinging_knife"
 * and when there aren't any it will switch to slash.
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Avenir/inherit/weapon";
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
    add_name(({"knife","blade", "_npc_flinging_knife"}));
    set_pname(({"daggers","knives","blades","weapons"}));
    set_adj(myadj);
    add_adj("union");
    set_short(myadj + " dagger");
    set_long("It is a long and shiny dagger, suitable "
      +"for throwing. The blade of the dagger in "
      +"not very sharp, but the point is as thin "
      +"as a needle.\n");

    set_default_weapon(20, 20, W_KNIFE, W_IMPALE, W_NONE, TO);

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

    /* npcs have a better knife to wield only */
    if (interactive(TP)) 
	    set_default_weapon(20, 20, W_KNIFE, W_IMPALE, W_NONE, TO);
    else
	    set_default_weapon(35, 35, W_KNIFE, W_IMPALE, W_NONE, TO);	
	
    write("You wrap your hand around the hilt of "+
	LANG_THESHORT(to)+".\n");
    say(QCTNAME(TP) +" wraps "+ HIS(TP) +" hand around the "+
	"hilt of "+ LANG_ASHORT(TO) +".\n");
	TO->remove_name("_npc_flinging_knife"); // NPC fling checks for this name
                                            // and switches to slash if none left.
    return 1;
}
