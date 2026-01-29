/* Tika in the Inn of last homes */

#include "/d/Roke/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"

inherit "/std/monster";

create_monster()
{
    int i;

    set_living_name("Unci");
    set_short("pub owner");
    set_long("She's working with something behind the bar.\n");
    set_race_name("human");
    set_gender(1);
    add_act(({"say Welcome","say What do you want to order?"}));
    add_act("emote starts working with something behind the bar.");
    add_act(({"say Lotsa weird people come here...","smile mysteriously"}));

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
