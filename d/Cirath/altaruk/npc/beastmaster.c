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
    set_name("falkior");
    add_name("beastmaster");
    set_title("the beastmaster");
    set_race_name("human");
    set_adj("sun-burned");
    add_adj("determined");
    set_gender(0);
    set_long("He is the caravan driver. This type of caravan" +
        " neads a driver that has great knowledge in handling" +
   	" mekillots. He cant be no wimp either as the beasts" +
   	" have a habbit of eating their handlers.\n");
    set_alignment(50);
    set_stats(({60,80,50,55,45,80}));
    set_skill(SS_WEP_POLEARM,50);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_PARRY,50);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_ANI_HANDL,65);
    set_act_time(15);
    add_act("stare");
    add_act("calm mekillot");
    set_cact_time(6);
    add_cact("say Bring it on!");
    add_cact("curses");
    add_cact("say blasted fool!");

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE," dont nead your gifts.");

}
void
arm_me()
{
   clone_object(ALT_WEP + "staff1")->move(this_object());
   command("wield all");
   MONEY_MAKE_SC(random(50))->move(this_object(),1);
}
