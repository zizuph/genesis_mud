inherit "/std/monster";

#include <ss_types.h>    // needed for stats and skills

#include "examples.h"

#define ADJECTIVES ({"strong", "tall", "black-haired", "skinny", })

private string
random_adj()
{
    return ADJECTIVES[random(sizeof(ADJECTIVES))];
}
    

public void
create_monster()
{
    set_name("guard");
    add_name("_bridge_guard");           // unique name for use with present()
    set_adj(random_adj());

    default_config_npc(35);              // not too tough
    set_base_stat(SS_STR, 40);           // higher strength
    set_base_stat(SS_CON, 40 + random(11));  // even higher constitution

    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_DEFENCE,   40);
    set_skill(SS_PARRY,     20);
    set_skill(SS_AWARENESS, 30);

}

public void
arm_me()
{
    seteuid(getuid());

    clone_object(EX_WEP + "sword")->move(this_object());
    command("wield all");

    clone_object(EX_ARM + "helmet")->move(this_object());
    clone_object(EX_ARM + "ringmail")->move(this_object());
    command("wear all");
}
