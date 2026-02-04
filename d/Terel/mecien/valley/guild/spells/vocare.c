/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 * vocare.c
 */
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#define TP       this_player()
#define ETP      environment(TP)
#define TO       this_object()

#define SPIRITS  ({"the dead", "the forest", "the air", "the earth",\
                   "the stars", "the sea", "the waters"})
#define S_NAMES  ({"ghuindar", "aldrain", "ulthyra", "ossed",\
                   "liyalas", "olstos", "nuriya"})
#define S_FILES  ({"/d/Terel/mecien/valley/guild/dt",\
                   "/d/Terel/enchanted/monster/e_dryad",\
                   "/d/Terel/mecien/valley/guild/wh",\
                   "/d/Terel/mecien/valley/guild/gnome",\
                   "/d/Terel/mecien/valley/guild/celest",\
                   "/d/Terel/mecien/valley/guild/ship",\
                   "/d/Terel/mecien/valley/guild/courtyard/nymph"})
#define S_PROPS  ({"_can_summon_the_dead",\
                   "_can_summon_the_forest",\
                   "_can_summon_the_air",\
                   "_can_summon_the_earth",\
                   "_can_summon_the_stars",\
                   "_can_summon_the_sea",\
                   "_can_summon_the_waters"})

#define VOCARE_MIN_WIS    15
#define VOCARE_MANA_COST  10
#define VOCARE_CAST_LIMIT 70

/*
 * Function name: vocare
 * Description:   summons spirits at certain places
 */
nomask mixed
vocare(string str)
{
    int i, suc;
    object what;
    string name = TP->query_name();

    if (!str) return "Vocare what?\n";
    i = member_array(str, SPIRITS);
    if (i == -1) return "Vocare what?\n";
    if (TP->query_stat(SS_WIS) < VOCARE_MIN_WIS)
        return "You are not of high enough stature to attempt this yet.\n";

    what = find_living(S_NAMES[i]);
    if (what && environment(what) == ETP) {
        if (what->query_prop("summoner") != TP->query_name()) {
            return "A spirit is already here at someone elses call.\n";
        } else {
            return "A spirit is already here at your call.\n";
        }
    }

    if (S_PROPS[i] != "everywhere") {
        if (!(ETP->query_prop(S_PROPS[i])))
            return "The spirit cannot hear you here.\n";
    }

    if (TP->query_mana() < VOCARE_MANA_COST)
        return "You do not have the strength.\n";

    TP->add_mana(-VOCARE_MANA_COST);

    suc = random(TP->query_skill(SS_FORM_CONJURATION));
    suc += random(TP->query_skill(SS_ELEMENT_LIFE))/2;
    suc += random(TP->query_skill(SS_ELEMENT_DEATH))/2;
    if (suc < random(VOCARE_CAST_LIMIT))
    {
        write("Your call of summons to the spirit has failed.\n");
        return 1;
    }

    write("You invoke the spirit.\n");
    say(QCTNAME(TP) + " intones an ancient song.\n");

    seteuid(getuid(TO));

    what = clone_object(S_FILES[i]);
    what->move_living("M", ETP);
    what->set_duration(60 + TP->query_stat(SS_WIS));
    what->add_prop("summoner", name);
    tell_room(ETP, QCTNAME(what) + " comes into existence.\n", what);

    return 1;
}
