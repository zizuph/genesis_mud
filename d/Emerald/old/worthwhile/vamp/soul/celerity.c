#include "../guild.h"
#include "abilities.h"
#include <ss_types.h>

#define CELERITY_MANA_COST     50
#define CELERITY_THIRST_COST   30
#define CELERITY_FATIGUE_COST  30

void celerity2();
void celerity3();

static mixed
celerity(string str)
{
    if (strlen(str))
    {
        return CMD_SYNTAX_FAILURE;
    }

    if (this_player()->query_celerity())
    {
        write("You are already in a hastened state.\n");
        return CMD_FAIL_WITHOUT_COST;
    }

    write("You try to focus your power.\n");
    return celerity2;
}

int
celerity2()
{
    int lvl;

    if ((this_player()->power_check(140) <= 0) &&
        !IS_WIZ(this_player()))
    {
        write("You can't focus enough power to move " +
            "any faster.\n");

        this_player()->add_mana(-CELERITY_MANA_COST / 3);
        this_player()->add_fatigue(-CELERITY_FATIGUE_COST / 3);
        this_player()->add_thirst(CELERITY_THIRST_COST / 3);

        return 0;
    }

    lvl = this_player()->query_vamp_stat();
    lvl = MAX(25, lvl / 12 + random(lvl / 10)) *
        this_player()->query_skill(SS_DEFENSE) / 100;

    this_player()->set_celerity(lvl);

    write("You focus your power and instantly you begin " +
         "to move at an amazing rate.\n");
    allbb(" begins to move with blinding speed.\n");

    set_alarm(300.0, 0.0, celerity3);
    return 1;
}

void celerity3()
{
    write("Your hastened state subsides.\n");
    this_player()->set_celerity(0);
    this_player()->add_thirst(CELERITY_THIRST_COST);
    this_player()->add_fatigue(-CELERITY_FATIGUE_COST);
    this_player()->add_mana(-CELERITY_MANA_COST);
}
