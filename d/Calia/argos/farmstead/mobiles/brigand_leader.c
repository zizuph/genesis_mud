/* /d/Calia/argos/farmstead/mobiles/brigand_leader.c
**   The leader of a small band of brigands that operate near the farmstead
**   near Argos
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   5/2/20    Brine      Created
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
    "confident", "strong-looking", "dangerous-looking", "domineering"
});

void react_ask();

void
create_monster()
{
    seteuid(getuid());
    if (!IS_CLONE) return;

    set_name(({ "brigand", "bandit", "leader", "boss" }));
    set_race_name("human");

    set_gender(random(2));

    string adj = one_of_list(adjectives);
    set_adj(({ adj, "boss", "leader" }));

    set_short(adj + " brigand");

    set_long(
        capitalize(TO->query_pronoun()) + " is " + LANG_ADDART(query_adj())
        + " " + TO->query_gender_string() + " human. "
        + capitalize(TO->query_pronoun()) + " appears to be the leader of a "
        + "small band of forest brigands.\n"
    );

    set_stats(({ 35, 35, 35, 20, 25, 35 }));

    set_skill(SS_WEP_SWORD, 40);
    set_skill(SS_WEP_POLEARM, 40);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_PARRY, 40);
    set_skill(SS_UNARM_COMBAT, 40);
    set_skill(SS_BLIND_COMBAT, 30);

    add_prop(CONT_I_HEIGHT, 180);
    add_prop(CONT_I_WEIGHT, 80000);
    add_prop(CONT_I_VOLUME, 80000);

    add_prop(NPC_I_NO_UNARMED, 1);

    set_alignment(-250);

    set_act_time(5);
    add_act("pace");
    add_act("emote keeps a wary eye on the farmhouse.");
    add_act("say I'm not going into that damned farmhouse again!");

    set_default_answer("@@react_ask");
    add_ask(
        ({ "[about] [the] 'farm' / 'farmyard'" }),
        "say This farm is our base now!",
        1
    );
    add_ask(
        ({ "[about] [the] 'house' / 'farmhouse'" }),
        "say The farmhouse is haunted. Maybe we should just burn it...",
        1
    );

    equip(({
        WEAPON_DIR + "brigand_sword",
        ARMOUR_DIR + "brigand_britches",
        ARMOUR_DIR + "brigand_armour",
        ARMOUR_DIR + "brigand_shield"
    }));
}

void
react_ask()
{
    if (CAN_SEE(TO, TP) && CAN_SEE_IN_ROOM(TO))
    {
        command(
            "say to " + OB_NAME(TP) + " I don't have anything to say about "
            + "that. Now beat it!"
        );
        return;
    }

    command("say Who said that?!?");
    command("peer");
}
