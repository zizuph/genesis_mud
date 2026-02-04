/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <comb_mag.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define MANA_COST 200

#define TP   this_player()
#define ETP  environment(TP)

nomask mixed
caligo(string str)
{
    int suc;
    object who, co, soot;

    if (!str) return "Curse who?\n";

    if (TP->query_mana() < MANA_COST)
        return "You do not have the needed strength.\n";

    soot = present(MYSTIC_SOOT, TP);
    if (!soot) return "You will need some holy soot.\n";
    
    suc  = random(TP->query_skill(SS_FORM_ABJURATION));
    suc += random(TP->query_skill(SS_ELEMENT_DEATH));
    if (suc < 60 + random(20))
        return "You fail to invoke the curse.\n";

    who = present(str, ETP);
    if (!who) return "There is no one here with that name.\n";
    
    if (NPMAGIC(who)) return "Something blocks your curse.\n";
    
    TP->catch_msg("You pronounce the curse of the Ancients upon " +
                  QTNAME(who) + ".\n");
    tell_room(ETP, QCTNAME(TP) + " raises a hand and intones arcane words. " +
              "Suddenly " + TP->query_possessive() + " eyes become " +
              "black and a gloom overtakes this place.\n", ({who, TP}));
    tell_room(ETP, QCTNAME(TP) + " points at " + QTNAME(who) +
              ", who becomes shrouded in arcane darkness.\n", ({who, TP}));
    who->catch_msg(QCTNAME(TP) + " curses you with the full " +
                   "power of the Ancients.\n");
    seteuid(getuid());
    co = clone_object(SPELL_DIR + "curse");
    co->move(who);
    soot->remove_object();
    TP->add_mana(-MANA_COST);
    TP->catch_msg("You feel the darkness of the Ancients within you.\n");
    write_file(CURSED_LOG, TP->query_name() + " cursed " +
               who->query_name() + " (" + ctime(time()) + ")\n");
    return 1;
}
