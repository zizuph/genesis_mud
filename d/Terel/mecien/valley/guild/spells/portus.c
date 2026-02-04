/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#define TP            this_player()
#define ETP           environment(TP)
#define MANA_LIMIT    150  /* How much mana does it cost to cast this spell? */
#define CAST_LIMIT    90 /* How wise and skilled must the caster be? */

/* Function name: portus
 * Description:   return to the mystic hall
 * Arguments:     not used
 * Returns:       1/0 - or failure string
 */
nomask mixed
portus(string str)
{
    int suc;
    
    if (NPMAGIC(TP) || NPTELEPORT(TP))
        return "Somehow you fail to cast this spell here.\n";

    /*
     * Can't be cast during combat
     */

    if (TP->query_attack())
	return "You are too distracted by the combat to cast this spell.\n";
    
    if (TP->query_mana() < MANA_LIMIT)
        return "You do not have the strength.\n";

    TP->add_mana(-MANA_LIMIT);

    suc  = random(TP->query_skill(SS_FORM_ABJURATION));
    suc += random(TP->query_skill(SS_SPELLCRAFT));
    if (suc < random(CAST_LIMIT))
        return "Your prayer is not heard.\n";

    write("You cry out to the Ancients.\n");
    write("A mystical cloud envelopes you.\n");
    say(QCTNAME(TP) + " beckons to the divine powers.\n");
    say("A cloud appears and " + QTNAME(TP) + " disappears with it.\n");
    say("The cloud quickly dissipates.\n");
    TP->move_living("M", "/d/Terel/mecien/valley/guild/guild", 1);
    tell_room(ETP,  QCTNAME(TP) +
              " appears from the midst of a cloud.\n", TP);
    return 1;
}
