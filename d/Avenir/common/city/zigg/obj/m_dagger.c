// pruning knife
// creator(s):           Zielia 2006 (combination Sachluph's amulet and
//			    noble daggers created by Lilith)
// purpose:              Ritual blade for Maree
// last update:
// note:
// bug(s):
// to-do:
// ====== ========= ========= ========= ========= ========= ========= =====
#pragma strict_types

inherit "/d/Avenir/inherit/weapon";
inherit "/lib/keep";

#include "zigg.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>

public static string sigil;

public string
query_sigil(void)		{ return sigil; }

public void
set_sigil(string str)		{ sigil = str; }

public void
configure_it(void)
{
    add_adj(({"ensorcelled", "black", "pruning", "noble", "shadow-elf"}));
    set_sigil("Contrae'ree");
    set_short("ensorcelled black pruning knife");
    set_long("@@my_long");
}

public void
create_weapon(void)
{
    set_name(({"knife", "blade", "dagger"}));
    set_hit(13 + random(3));
    set_pen(20);
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);

    add_prop(OBJ_M_NO_STEAL, "That which is given by the Gods cannot "+
	"be taken by another.\n");

    add_item(({"hilt", "handle"}),
        "The hilt is as long again as the blade, and made of the same "+
	"black metal, but ornamented with silver.\n");
    add_item(({"pommel", "ornament", "enamel", "symbol", "sigil"}),
        "@@exa_pommel");

    add_item(({"snake","snakes","serpent","serpents","relief","center"}),
         "Two snakes intertwine sinuously around the hilt of the "
        +"pruning knife. Their bodies are made of real silver, and each of "
        +"their eyes is a tiny sparkling emerald.\n");

    configure_it();
}

public string
my_long(void)
{
    string str;

    if (TP->query_prop(LIVE_I_UNDEAD))
        str = " Something about the knife infuses you with a sense of "+
              "dread.";
    else
        str = " Something about the knife infuses you with a sense of "+
              "well-being, as though it somehow protects you.";

    if ( (IS_SYBARITE(TP)) ||
            (TP->query_skill(SS_LANGUAGE) > 29 + random(30)) )
        str += " You aren't certain, but you think that this knife "+
               "harnesses the power of Sachluph, the Sybarite Goddess "+
               "of the Eleventh Hour, who governs all plants, and thus "+
               "both healing and poisoning.";

    return  "This "+ short() +" has been crafted from some strange black "+
            "metal. Around the hilt are twined two serpent." + str + "\n";
}

public string
exa_pommel(void)
{
    string str;

    if (query_sigil())
    {
        str = "It is the sigil of a Sybarite House: "+
              query_sigil() +".\n";
    }
    else
        str = "It appears to have been broken recently, and you "+
              "can no longer discern what it was.\n";

    return "There is a silver and enamel symbol on the pommel.\n"+ str;
}

