/* Tika in the Inn of last homes */

#include "/d/Roke/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"

inherit "/std/monster";

create_monster()
{
    int i;

    set_living_name("Joshua");
    set_short("hotelowner");
    set_long("He's working with something behind the bar.\n");
    set_race_name("human");
    set_gender(0);
    add_act(({"bow","say Welcome to Ciuburi City Hotel!"}));
    add_act(({"smile","say I have so much to do nowadays!","emote sighs deeply"}));
    add_act(({"yawn","say I would like to have some holiday.",
              "say I mean, life isn't all just working."}));

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
