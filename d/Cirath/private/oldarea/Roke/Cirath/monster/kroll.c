/* Tika in the Inn of last homes */

#include "/d/Roke/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"

inherit "/std/monster";

create_monster()
{
    int i;

    set_living_name("Kroll");
    set_short("innkeeper");
    set_long("He's working with some wood behind the bar.\n");
    set_race_name("Kroll");
    set_gender(0);
    add_act(({"bow","say Welcome to my humble inn"}));
    add_act(({"smile","say I really like wood!","emote starts whittle some wood"}));
    add_act(({"hmm","say You propably know my younger brother, Krell..",
              "say He likes water, me wood."}));

    set_act_time(10);

    set_skill(SS_UNARM_COMBAT,100);

    set_gender(0);
    for (i = 0; i < 6; i++)
        set_base_stat(i, 130);
    set_alignment(170);


    add_prop(LIVE_I_ALWAYSKNOWN,1);

    set_hp(100000);

    ::create_monster();
}

init_living()
{

}
