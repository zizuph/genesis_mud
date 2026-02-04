inherit "/d/Terel/std/monster";

#include <ss_types.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define PORDIR TOWNDIR + "mansion/porcia/"

#define WEP    PORDIR + "ssword"
#define ARM    PORDIR + "s_armour"
#define HAT    PORDIR + "helmet"
#define SHOES  PORDIR + "boots"

int frust_mode;

public void
create_monster()
{
    set_name("guard");
    set_race_name("human");
    set_adj("bored");
    set_long("He is very bored. However, he also looks very strong!!\n");

    default_config_npc(50);

    set_skill(SS_DEFENCE, 60);
    set_skill(SS_PARRY, 58);
    set_skill(SS_WEP_SWORD, 90);

    set_chat_time(4);
    add_chat("Damn I'm so bored... like to play a NIM game?");
    add_chat("Type 'nim' to start a new NIM game.");
    add_chat("Type 'remove 2 stones from heap 2' or 'rem 2 2'" +
        " to remove stones.");
    add_chat("Each of us can remove any number of stones from one heap.");
    add_chat("Whoever removes the last stone at all wins the game.");

    set_alignment(0);
    frust_mode = 0;

    seq_new("do_things");
    seq_addfirst("do_things", ({"@@arm_me"}));
}

public void
unfrustrate()
{
    frust_mode = 0;
    command("think");
    tell_room(environment(this_object()), QCTNAME(this_object()) +
              " seems to return to " + this_object()->query_possessive() +
              " attentive mode and looks at you carefully.\n");
}

public void
frustrate()
{
    frust_mode = 1;
    tell_room(environment(this_object()), QCTNAME(this_object()) +
              " looks terribly frustrated and distracted he was beaten.\n");
    set_alarm(12.0, -1.0, unfrustrate);
}

public void
happy()
{
    frust_mode = 1;
    command("cheer");
    tell_room(environment(this_object()), QCTNAME(this_object()) +
              " looks very happy over his victory.\n");
    command("smile");
    set_alarm(10.0, -1.0, unfrustrate);
}

public int
getfrust()
{
    return frust_mode;
}

public void
arm_me()
{
    object wep, arm, hat, shoe, money;

    seteuid(getuid(this_object()));

    wep = clone_object(WEP);
    wep->move(this_object());
    command("wield sword");

    arm = clone_object(ARM);
    arm->move(this_object());
    command("wear armour");

    hat = clone_object(HAT);
    hat->move(this_object());
    command("wear helmet");

    shoe = clone_object(SHOES);
    shoe->move(this_object());
    command("wear boots");
}
