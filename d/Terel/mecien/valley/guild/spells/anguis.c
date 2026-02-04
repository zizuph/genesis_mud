/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* The ANGUIS mystic spell. It turns the dagger into a snake. */
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <comb_mag.h>

#define TO         this_object()
#define TP         this_player()
#define ETP        environment(TP)
#define ETO        environment(TO)
#define SERPENT    "/d/Terel/mecien/valley/guild/spells/angserp"

#define SPELL_COST 100
#define CAST_LIMIT 80

nomask mixed
anguis(string str)
{
    object dagger;
   
    if (str != "dagger") return "Anguis what?\n";

    dagger = present("arcane_dagger", TP);
    if (!dagger) {
        return "You must possess the arcane dagger.\n";
    }

    if (NPMAGIC(TP)) {
        return "Somehow your spell fails.\n";
    }

    if (TP->query_mana() < SPELL_COST) {
        return "You do not have the strength.\n";
    }
   
    if (TP->query_skill(SS_FORM_CONJURATION) +
        random(TP->query_skill(SS_ELEMENT_DEATH)) < CAST_LIMIT) {
        return "You fail to summon the powers of darkness.\n";
    }
   
    TP->catch_msg("You hold aloft your arcane blade as it is " +
                  "raptured in darkness.\n");
    tell_room(ETP, QCTNAME(TP) + " holds aloft an arcane dagger.\n", TP);

    dagger->move(ETP);

    TP->catch_msg("You place the arcane dagger upon the ground.\n");
    tell_room(ETP, QCTNAME(TP) + " places the arcane dagger on the ground.\n", TP);
    dagger->add_prop(OBJ_M_NO_GET, "The dagger hisses!\n");
    set_alarm(3.0, -1.0, "transform", dagger);
   
    TP->add_mana(-SPELL_COST);

    return 1;
}

public void
transform(object dagger)
{
   object serpent, here;

   if (!dagger) return;

   seteuid(getuid(TO));

   here = environment(dagger);

   tell_room(here, "The dagger turns into blackened soot.\n");

   serpent = clone_object(SERPENT);
   serpent->set_gender(2);
   serpent->set_duration((TP->query_skill(SS_SPELLCRAFT) /3) +
                         random(TP->query_stat(SS_WIS)) + 10);
   dagger->remove_object();
   serpent->move_living("M", here);

   tell_room(here, "A spectral serpent arises from the " +
             "soot and takes shape!\n");
}

