/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define MANA_COST 15

#define TP  this_player()
#define ETP environment(TP)

nomask mixed
fervere(string str)
{
    int suc;
    object vessel, juice;

    if (!str)
        return "What are you calling this upon?\n";
    if (str != "chalice")
        return "That cannot be done.\n";

    vessel = present(MYSTIC_CHALICE, TP);
    if (!vessel)
        return "You do not possess the sacred chalice.\n";
    
    juice = present(MYSTIC_JUICE, vessel);

    if (!juice)
        return "The sacred chalice is empty.\n";

    suc  = TP->query_skill(SS_FORM_TRANSMUTATION);
    suc += random(TP->query_skill(SS_ELEMENT_LIFE));
    
    if (suc < 20 + random(30)) {
        return "You fail to summon the holy spirits of life and joy.\n";
    }

    if (TP->query_mana() < MANA_COST)
        return "You do not have the strength.\n";

    write("You summon the holy powers and place your hand over the chalice.\n");
    say(QCTNAME(TP)+" places " + TP->query_possessive() +
        " hand over a chalice and speaks arcane words.\n");
    
    juice->remove_object();
    vessel->remove_prop(CONT_M_NO_INS);
    seteuid(getuid());
    clone_object(GUILD_DIR + "obj/wine")->move(vessel);
    vessel->add_prop(CONT_M_NO_INS, "That may not be placed in the chalice.\n");
    TP->add_mana(-MANA_COST);
    return 1;
}
