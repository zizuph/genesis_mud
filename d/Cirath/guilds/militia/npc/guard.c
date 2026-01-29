inherit "/std/monster";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include "defs.h"
#include "/d/Cirath/common/introfnc.h"

mixed attackers;

create_monster()
{
   set_race_name("mul");
    set_name("hercule");
    set_title("the Scouring Wind of the Tyrian Militia");
   set_adj("scarred");
   add_adj("stocky");
   set_long("Mul's are a race unique to Athas.  Born from a dwarven "
   +"father and a human mother, they possess the advantages of "
   +"both races.  Standing around six feet tall and possessing "
   +"the broadness and sturdiness of dwarves, this mul looks "
   +"to be the gate guard for the Tyrian Militia.  He is wearing "
   +"simple dusty clothes, but the hard look in his eye lets you "
   +"know that he is more than just a simple peasant.\n");
   set_alignment(700);
   set_stats(({200,215,205,120,120,120}));
   set_skill(SS_WEP_POLEARM,90);
   set_skill(SS_PARRY,70);
   set_skill(SS_AWARENESS,70);
   set_skill(SS_DEFENCE,80);
    add_ask("join","@@join");
    add_ask("guild","@@guild");
   set_act_time(9);
   add_act("say Would you like to join the Tyrian Militia?");
   add_act("emote peers at you quizically.");
   add_act("smile happ");
   add_act("say We are the defenders of Tyr.  We ensure its safety.");
   add_act("smile grimly");

   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(OBJ_M_NO_ATTACK,1);
}

void
arm_me()
{
    clone_object(MILITIA_WEP + "pole1")->move(TO);
   command("wield all");
   clone_object(MILITIA_OBJ + "baldric")->move(TO);
   clone_object(MILITIA_ARM + "shield")->move(TO);
   command("wear all");
}

join()
{
    write("To become a member of the Tyrian Militia, you need "
    +"to speak with one of the lesser nobility that are "
    +"scattered about Tyr.  They should be able to help "
    +"you and sponsor you as a member of the Militia.\n");
    return ">";
}

guild()
{
    write("You want some info about the Tyrian Militia?  Well "
    +"let me give you a quick breakdown of the guild.  We "
    +"grant knowledge of polearms, defence, parry, and some "
    +"assorted other skills.  We will also train you in "
    +"special techniques using polearms and shields.  And "
    +"all this is only a paltry 9% tax.\n");
    return ">";
}

