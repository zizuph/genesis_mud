/*
 * Captain for the Ship between Sparkle and Gelan in Calia
 * 
 * Created by Petros, April 2009
 */
 
#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include "ship.h"

inherit STDCAPTAIN;

static void
create_captain()
{
    ::create_captain();

    set_name("cetus");
    add_name("captain");
    add_name("_cetus_");
    set_race_name("human");
    add_adj("massive");
    add_adj("muscular");
    add_adj("sea-faring");
    set_stats(({ 60, 60, 60, 65, 82, 120}));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENSE, 60);
    set_skill(SS_AWARENESS, 70); 
    heal_hp(10000);
    set_chat_time(15);
    add_chat("Hmmm...maybe we're in for a storm later.");
    add_chat("They say the great white whale has been seen nearby.");
    add_chat("Har, matey!");

    set_act_time(15);
    add_act("emote pulls out a spy glass and looks out to sea.",0);
    add_act("emote whistles a little sea ditty.", 0);
    add_act("emote looks at the sky with a weather eye.",0);
    
    set_title("the Old Seadog");
}

public void
add_introduced(string who)
{
    set_alarm(2.0,0.0, &command("introduce me"));
}
