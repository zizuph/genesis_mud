inherit "/d/Raumdor/std/monster.c";
#include "/d/Raumdor/defs.h"
/* By SARR */



void
create_monster()
{
    ::create_monster();
    set_name("orvil");
    set_adj("pale");
    add_adj("tattered");
    set_race_name("human");
    set_short("pale tattered human");
    set_long("This man looks like he has been to hell and back. "+
    "He is deathly pale white, and is shaking visibly. He has "+
    "many bleeding wounds, and his clothes are in tatteres. He "+
    "occationaly coughs and vomits blood, but his eyes are as "+
    "alert and wide open.\n");
    set_stats(({30,30,30,30,30,30}));
    set_alignment(800);
    set_act_time(3);
    add_act("emote vomits up some blood.");
    add_act("emote wipes the blood from his mouth.");
    add_act("say Don't go in the forest! It is cursed! I warn you!!");
    add_act("say Don't travel at night! Heed the warning, or you shall "+
    "end up like me, or even worse!");
    add_act("cough");
    set_default_answer("The pale tattered human says: What?\n");
    add_ask(({"forest","undead","children","night"}),"The pale "+
    "tattered humans moans: Hoards of undead roam the forest, "+
    "looking for blood! If warm blood runs through your veins, run "+
    "while you can! Go back!\n");
    add_ask("road","The pale tattered human says: Stick to the road "+
    "and only travel during the day! Or you will die!\n");
}



