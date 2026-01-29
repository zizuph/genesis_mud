/* SARR */
#include "defs.h"
inherit STD_MONSTER;
inherit "/d/Raumdor/lib/intro";

int sex;

string
random_male_name()
{
    return ({
      "korat", "murtaza", "ajaja", "gren", "rico", "zarr", "antharanos",
      "similirien", "wong", "uthangton", "ian", "smine", "retron", "bobak",
    })[random(14)];
}

string
random_male_desc()
{
    return ({
      "tall", "stout", "strong", "short",
    })[random(4)];
}

void
create_monster()
{
    ::create_monster();

    set_gender(G_MALE);
    set_short(random_male_desc() + " man");
    set_stats(STAT_ARRAY(90));
    set_name(({random_male_name(), "man"}));
    set_race_name("human");
    set_long(
      "This is one of the many citizens of Drakmere. He stares at you " +
      "suspiciously. He is strong and healthy looking.\n");
    set_title("of Drakmere");
    set_alignment(DRAKMERE_ALIGN);

    set_skill(SS_WEP_KNIFE, 60);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_UNARM_COMBAT, 40);

    add_act("emote peers around.");
    add_act("say What are you doing in my house?");
    add_act("emote fastens his boots.");
    add_act("emote mumbles a prayer.");

    equip(({
      DRAKMERE_ARM_DIR + "c_pants", DRAKMERE_ARM_DIR + "c_boots",
      DRAKMERE_ARM_DIR + "c_shirt.c", DRAKMERE_WEP_DIR + "c_dagger",
    }));
}

do_die(object who)
{
    who->add_prop(
      IS_ENEMY_OF_DRAKMERE, who->query_prop(IS_ENEMY_OF_DRAKMERE) + 1);

    ::do_die(who);
}
