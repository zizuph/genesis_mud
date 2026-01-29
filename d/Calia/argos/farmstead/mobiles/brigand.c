/* /d/Calia/argos/farmstead/mobiles/brigand.c
**   A brigand, appearing in a small band near the argosian farmstead
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   5/1/20    Brine      Created
**
*/

#pragma strict_types

inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include "defs.h"
#include "team_assist.c"

string *adjectives = ({
    "menacing", "mean-looking", "narrow-eyed", "alert", "nervous", "skulking",
    "quiet", "boisterous", "unkempt", "dirty", "disheveled", "loud"
});
int personality;

void react_ask();

void
create_monster()
{
    seteuid(getuid());
    if (!IS_CLONE) return;

    set_name("brigand");
    add_name("bandit");
    set_race_name("human");

    set_gender(random(2));

    string adj = one_of_list(adjectives);
    set_adj(adj);

    set_short(adj + " brigand");

    set_long(
        capitalize(TO->query_pronoun()) + " is " + LANG_ADDART(query_adj())
        + " " + TO->query_gender_string() + " human, making a living for "
        + TO->query_objective() + "self by robbing travelers.\n"
    );

    set_stats(({ 25, 25, 25, 15, 15, 25 }));

    set_skill(SS_WEP_SWORD, 25);
    set_skill(SS_WEP_POLEARM, 25);
    set_skill(SS_DEFENCE, 25);
    set_skill(SS_PARRY, 25);
    set_skill(SS_UNARM_COMBAT, 25);
    set_skill(SS_BLIND_COMBAT, 20);

    add_prop(CONT_I_HEIGHT, 170);
    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_VOLUME, 70000);

    add_prop(NPC_I_NO_UNARMED, 1);

    set_alignment(-200);

    set_act_time(6);

    set_default_answer("@@react_ask");
    add_ask(({ "boss", "leader", "the boss" }), "@@boss_response");

    equip(({
        WEAPON_DIR + "brigand_spear",
        ARMOUR_DIR + "brigand_britches",
        ARMOUR_DIR + "brigand_vest",
        ARMOUR_DIR + "brigand_shield"
    }));
}

void
set_personality(int which)
{
    personality = which;

    if (personality == 1)
    {
        add_act("hum local");
        add_act("twiddle");
        add_act("scratch");
        add_act("ponder the unbearable lightness of being.");

    } else {
        add_act("mumble");
        add_act("emote scans the forest edge.");
        add_act("cough");
        add_act("narrow");
    }
}

void
react_ask()
{
    if (CAN_SEE(TO, TP) && CAN_SEE_IN_ROOM(TO))
    {
        if (personality == 1)
        {
            command(
                "say to " + OB_NAME(TP) + " Oh, I don't know much about that. "
                + "Maybe you could ask the boss?"
            );
            command("smile " + OB_NAME(TP));
        } else {
            command("shrug");
            command(
                "say to " + OB_NAME(TP) + " Speak to the boss, I don't care."
            );
        }
        return;
    }

    if (personality == 1)
    {
        command("say Eeek! Who said that?!?");
        command("emote covers in fear.");
    } else {
        command("say Who said that?!?");
        command("peer");
    }
}

void
boss_response()
{
    if (CAN_SEE(TO, TP) && CAN_SEE_IN_ROOM(TO))
    {
        if (personality == 1)
        {
            command(
                "say to " + OB_NAME(TP) + " Yes, ask the boss. The boss would "
                + "know!"
            );
            command("smile eager");
        } else {
            command(
                "say to " + OB_NAME(TP) + " Yes, the boss. Are you slow or "
                + "something?"
            );
            command("scowl " + OB_NAME(TP));
        }
        return;
    }

    if (personality == 1)
    {
        command("say Eeek! Who said that?!?");
        command("emote covers in fear.");
    } else {
        command("say Who said that?!?");
        command("peer");
    }
}
