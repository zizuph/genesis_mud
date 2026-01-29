/* guard.c */

inherit "std/monster";
inherit "/d/Kalad/lib/intro";
#include <ss_types.h>
#include <stdproperties.h>
#include "../defs.h"

void
create_monster()
{
    set_name("guard");
    set_race_name("guard");
    set_adj("large");
    set_long(BS(
"This guard is very alert, and aware of his duties.  He keeps non-members " +
"out of the guild, and guards the door from intruders.\n"));
    default_config_mobile(75);
    set_skill(SS_PARRY, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_WEP_SWORD, 70);

    set_act_time(1);
    add_act("emote checks to make sure the door is locked.");
    add_act(({"say I hope you belong in here, or else...", 
"emote draws his index finger across his throat in a threating manner.",
               "grin"}));
    add_act("@@call_check");

    set_chat_time(20);
    add_chat("Well, it pays the rent...");
    add_chat("Watch your back in here, buddy.");

}

public void
introduce_me(string dummy)
{
    command("say I'm a little busy right now.  Go bug somone else.");
}

void
call_check()
{
    call_other(environment(), "check_players");
}
