/* mystic.c */

inherit "std/monster";
inherit "/d/Kalad/lib/intro";
#include <ss_types.h>
#include <stdproperties.h>
#include "../defs.h"


void
create_monster()
{
    set_name("gladmir");
    add_name("mystic");
    set_race_name("elf");
    set_adj("young");
    add_adj("strong");
    set_long( break_string(
"This still-proud Mystic is strapped to the rack.  Althoug he has been " +
"tortured repeatedly, he still has his strength and dignity.\n", 78));
    default_config_mobile(30);

    set_act_time(20);
    add_act("sigh");
    add_act("emote glares at you.");
    add_act("emote struggles vainly to break free.");

    set_chat_time(20);
    add_chat("When I get out of here, the Blackhands will pay!");
    add_chat("You'll never break my spirit!");
    add_chat("If I could only get my hands free....");

    add_prop(OBJ_I_NO_ATTACK, 1);
}

string
query_title()
{
    return "the Mystic of the Inner Circle";
}

