/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Terel/mecien/valley/guild/spells/spells.h"

#define TP        this_player()
#define ETP       environment(TP)

/* Function name: ardere
 * Description:   Will light up a player using aura.c as object
 * Arguments:     str - living target to be ``enlightened'' ;)
 * Returns:       failure string or 1 (success)
 */
public nomask mixed
ardere(string str)
{
    int suc, dur;
    object who, ob;

    if (TP->query_mana() < ARDERE_MANA_COST)
        return "You do not have the strength.\n";

    if (!str || str == "me" || str == "myself")
       who = TP;
    else {
	if (!parse_command(str, ETP, " %o ", who))
	    return "Whom shall travel in light?\n";
	if (!living(who))
	    return "Whom shall travel in light?\n";
    }

    if (NPMAGIC(who))
	    return "Somehow you cannot cast this spell here.\n";

    if (who->query_alignment() < 100)
	    return "The sacred aura cannot be attached to evil beings.\n";

    suc  = random(TP->query_skill(SS_FORM_ENCHANTMENT));
    suc += random(TP->query_skill(SS_SPELLCRAFT));
    if (who != TP) suc -= random(who->query_skill(SS_FORM_ABJURATION));
    if (suc < random(ARDERE_CAST_LIMIT))
    {
        TP->add_mana(-ARDERE_MANA_COST/3);
        return "Your prayer is not heard.\n";
    }

    TP->add_mana(-ARDERE_MANA_COST);

    dur = 4*(TP->query_stat(SS_WIS)) + random(60);
    if (who == TP)
    {
	dur += 7*(TP->query_skill(SS_FORM_ENCHANTMENT));
        write("You summon the light of the heavens about you.\n");
        say(QCTNAME(TP) +
	        " raises a hand and is surrounded with a blazing light.\n");
    }
    else
    {
        TP->catch_msg("You summon the light of the heavens about " +
		              QTNAME(who) + ".\n");
	    who->catch_msg(QCTNAME(TP) +
	        " raises a hand and you are surrounded by a blazing light!\n");
	    say(QCTNAME(TP) + " raises a hand and " + QTNAME(who) +
	        " is surrounded by a blazing light.\n", ({TP, who}));
    }

    seteuid(getuid());

    ob = clone_object(SPELL_DIR + "aura");
    ob->add_prop(OBJ_M_NO_DROP, 1);
    ob->set_duration(dur);
    ob->move(who);
    environment(who)->update_light(1);

    return 1;
}
