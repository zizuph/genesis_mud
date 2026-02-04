inherit "/d/Terel/std/mystic";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO       this_object()
#define TP       this_player()
#define ETO      environment(TO)
#define ETP      environment(TP)

#define MO_PROP  "_blessed_by_talhurn"
#define CENSER   "/d/Terel/common/town/temple/censer"

public void
create_monster()
{
    object censer;

    ::create_monster();

    set_name("talhurn");
    add_name("priest");
    add_name("keeper");
    add_name("elder");
    set_adj(({"old", "formidable"}));
    set_race_name("human");
    set_gender(0);
    set_long("A formidable man, he is priest of the temple and its " +
             "guardian. He wears a long gold robe. He has long blonde " +
             "hair and a beard, both are set into braids. His eyes " +
             "are pale blue, luminous and searching.\n");

    set_alignment(834);
    set_stats(({ 35, 56, 45, 132, 124, 80}));
    set_hp(9000);
    set_mana(9000);

    set_rank(MYSTIC_CANTOR);
    set_skill(SS_DEFENCE, MYSTIC_MAX_DEFENCE);
    set_skill(SS_SPELLCRAFT, MYSTIC_MAX_SPELLCRAFT);
    set_skill(SS_LANGUAGE, MYSTIC_MAX_LANGUAGE);
    set_skill(SS_FORM_CONJURATION, MYSTIC_MAX_CONJURATION);
    set_skill(SS_ELEMENT_LIFE, MYSTIC_MAX_LIFE);
    set_piety(560);
    set_blessed(1);
    enable_auto_reverence();
    enable_intro();

    set_all_hitloc_unarmed(40);

    seteuid(getuid());
    censer = clone_object(CENSER);
    censer->move(TO);

    set_act_time(15);
    add_act("pray");
    add_act("light censer");
    add_act("reverence censer");
    add_act("sign");
    add_act("reverence statue");

    set_chat_time(5);
    add_chat("Seek Truth from Holy Ones.");
    add_chat("Revere the powers here.");
    add_chat("I am priest and guardian of this holy place.");
    add_chat("I will bless the result of defoliation.");

    add_ask(({"about high place", "high place"}), "@@high_place", 1);
    add_ask(({"to bless leaf", "bless leaf", "to bless my leaf",
              "bless my leaf"}), "@@bless_leaf", 1);
}

public string
high_place()
{
    command("whisper " + TP->query_real_name() + " " +
            "In the icy mountains shall ye find it.");
    return "smile";
}

public int
do_bless(string what)
{
    int i;
    object *obs, leaf;

    notify_fail("Bless what?\n");
    if (!what || !parse_command(what, TP, "%i", obs))
        return 0;

    if (sizeof(obs) <= 1) {
        command("say I cannot bless something you do not possess.");
        return 1;
    }

    for (i=1; i<sizeof(obs) ; i++) {
        if (obs[i]->query_prop(MO_PROP) >= 1) {
            leaf = obs[i];
            if (leaf->query_prop(MO_PROP) == 1)
                break;
        }
    }

    if (!leaf) {
        command("say I will not bless that.");
        return 1;
    }
    if (leaf->query_prop(MO_PROP) == 2) {
        command("say The " + leaf->short() + " is already blessed.");
        command("smile");
        return 1;
    }

    write("The priest puts his hands on your leaf and blesses it.\n");
    command("say It's now prepared to soften the Keeper " +
            "of the Key.");
    leaf->add_prop(MO_PROP, 2);
    return 1;
}

public string
bless_leaf()
{
    if (do_bless("leaf")) return "chant";
    return "ponder";
}

public void
init_living()
{
    ::init_living();
    add_action(do_bless, "bless");
}
