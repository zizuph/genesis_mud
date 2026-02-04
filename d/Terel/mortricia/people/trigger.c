/*
    A trigger. Mortricia 920729
 */

inherit "/std/monster";

inherit "/std/act/domove";


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>

#define ARM_DIR "/d/Terel/mortricia/armours/"
#define HARD_TO_FOLLOW 5

create_monster()
{
    if (!IS_CLONE)
        return;
    set_short("human");
    set_long("It's a tall and thin human.\n");
    set_adj(({"tall", "thin"}));

    set_race_name("human");
    set_gender(0);

    set_stats(({25, 25, 25, 25, 25, 25}));
    set_hp(9999);
    set_mana(9999);
    set_skill(SS_DEFENCE, random(10) + 20);

    MONEY_MAKE_CC(10) -> move(this_object());


    trig_new("%s 'bows' %s", "bowing");

    trig_new("%s 'introduces' %s", "intro");

    trig_new("%s 'strolls' %s", "follow");
}

bowing(str1, str2)
{
    command("say I see " + str1 + " bowing " + extract(str2, 0, strlen(str2) - 2
));
    command("smile " + lower_case(str1));
}

intro(str1, str2)
{
    set_name("knut");
    set_short("Knut");
    command("introduce myself");
}

follow(str1, str2)
{
    if (random(100) > HARD_TO_FOLLOW +
                      this_interactive() -> query_stats(SS_INT) ) {
        set_follow(lower_case(str1));
    } else {
        set_follow("");
    }
}
