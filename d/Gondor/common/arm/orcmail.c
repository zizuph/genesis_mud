/*
 *	/d/Gondor/common/arm/orcmail.c
 *
 *	Cloned by:
 *	/d/Gondor/common/npc/reorc.c
 *	/d/Gondor/common/npc/reorc2.c
 *	/d/Gondor/common/npc/reuruk.c
 *	/d/Gondor/common/npc/whorc.c
 *
 * Typo fix and update December 2001 by Serif.
 */
#pragma strict_types

inherit "/std/armour.c";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

string  random_adj();     
string  random_adj2();  

public void
create_armour() 
{
    string adj = random_adj(),
        adj2 = adj,
        adja = random_adj2(),
        adja2 = adja;

    set_name("chainmail");
    add_name("mail");
    set_short(adj + " " + adja + " chainmail");
    set_pshort(adj2 + " " + adja2 + " chainmails");
    set_long(BSN("This " + adj2 + " " + adja2 + " chainmail is made "
         + "of small iron rings. It smells so bad that you would "
         + "guess it has been used by an orc or a goblin lately."));
    set_adj("smelly");
    set_adj(adj2);
    set_adj(adja2);
    set_adj("iron");
    set_adj("chain");
    set_default_armour(17, A_BODY, 0, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(17, A_BODY) + random(1201));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(17) + random(101));
}

string
random_adj() /* Random adjectives for the mail. */
{
    string *adj = ({"smelly", "smelly"});

    return ONE_OF_LIST(adj);
}

string
random_adj2() /* Random adjectives for the mail. */
{
    string *adj2 = ({"grey", "grey"});

    return ONE_OF_LIST(adj2);
}
