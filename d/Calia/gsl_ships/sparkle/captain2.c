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

    set_name("sutec");
    add_name("captain");
    add_name("_sutec_");
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
    add_chat("Have you seen the mermaid?");
    add_chat("What a lovely day for a swim!");
    add_chat("I hear there is a great sea serpent off the shores of Calia!");
    add_chat("I think I should lay off the bottle.  I thought I just " +
             "saw a mermaid!");

    set_act_time(15);
    add_act("emote pulls out a spy glass and looks out to sea.",0);
    add_act("emote whistles a little sea ditty.", 0);
    add_act("emote looks at the sky with a weather eye.",0);
    add_act("emote drinks from a large bottle of rum.",0);

    set_title("the Legendary Sea-serpent Slayer");
}

public void
add_introduced(string who)
{
    set_alarm(2.0,0.0, &command("introduce me"));
}
