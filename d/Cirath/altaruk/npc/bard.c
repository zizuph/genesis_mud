inherit "/std/monster";
#include "/d/Cirath/common/defs.h"
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include "/d/Cirath/common/introfnc.h"

create_monster()
{
    set_name("deaun");
    add_name("bard");
    set_title("Sixstrings");
    set_race_name("elf");
    set_adj("charming");
    set_gender(0);
    set_long("He is the house bard of the Dead Kank Inn." +
        " he is playing on some strange string instument." +
   	" He semes deeply occupied with his music.\n");
    set_alignment(-100);
    set_stats(({60,80,50,55,45,120}));
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_PARRY,50);
    set_skill(SS_AWARENESS,50);
    set_act_time(6);
    add_act("emote plays a cheerfull tune.");
    add_act("emote trails a long set of impossible tones" +
        " from his instrument.");
    add_act("emote grins as he plays a difficult part of" +
        " the song.");
    add_act("emote playes the balade of the broken blade.");
    add_act("emote plays a sour note and curses under his breath.");
    set_cact_time(6);
    add_cact("shout You have no understanding of the arts!");
    add_cact("say I'l write a song of your demise fool!");
    add_cact("curses");
    add_cact("say blasted fool!");

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE,"is already payd to perform" +
        " and dont nead your gifts.");

}
void
arm_me()
{
   clone_object(ALT_WEP + "bclub")->move(this_object());
   command("wield all");
   MONEY_MAKE_SC(random(50))->move(this_object(),1);
}
