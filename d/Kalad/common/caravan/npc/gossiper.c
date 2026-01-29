#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("man");
    add_name("citizen");
    set_race_name("human");
    set_adj("gossipy");
    set_short("gossipy citizen");
    set_long("A typical citizen of Kabal, dark-haired and tanned in "+
      "complexion. This particular man seems to be engrossed in spreading "+
      "the latest gossip.\n");
    set_stats(({25, 20, 20, 30, 30, 20}));
    set_alignment(100);
    set_knight_prestige(-1);
    set_skill(SS_UNARM_COMBAT, 10);
    set_skill(SS_DEFENCE, 10);
    set_skill(SS_AWARENESS, 10);
    set_act_time(3);
    add_act("say I heard the great wasteland is populated by horrible beasts.");
    add_act("say Rumour has it that those Thanar people had a tower somewhere in the desert.");
    add_act("say I heard there's great magic in a ruined tower in the desert!");
    add_act("say I hear tell that the Council is going to start trade "+
      "talks with them desert nomads.");
    add_act("say I heard Thanar himself is coming to Kabal!");
    add_act("say Anthios the shopkeeper down the street is really an "+
      "agent of Thanar!");
    add_act("say There's supposed to be some lost city somewhere in the "+
      "desert...some people have even seen it!");
    add_act("say There are goblins in the mountains! Better watch out!");
    add_act("say There are brigands on the Caravan Route, better watch out!");
    add_act("say That watchmaker in the Port District is a highway "+
      "robberer! Someone should teach him a lesson or two!");
    add_act("say That Trading Company gives me the creeps...all those "+
      "armed guards.");
    add_act("say The slave market is great! If I had the money, I'd buy "+
      "myself a slave!");
    add_act("say I got to see the High Lord once! Kabal is really lucky "+
      "to have a leader like him.");
    add_act("say Have you ever been to the library in the Central District? "+
      "I so enjoy reading the books there.");
    add_act("say Don't tell anyone, but there's some sort of old dwarven citadel "+
      "somewhere in the mountains.");
    add_act("say I heard those drow raiders come from beneath the ground in some horrible city...but you didn't hear that from me.");
    set_cact_time(3);
    add_cact("ack");
    add_cact("scream");
    add_cact("sniff");
    add_cact("cringe");
    add_speak("I love gossiping and chatting, don't you?\n");
    set_default_answer("I'm sorry, I don't answer questions!\n");
    MONEY_MAKE_CC(random(50))->move(TO, 1);
    MONEY_MAKE_SC(random(10))->move(TO, 1);
}
