/*      
 *      Created by:     Korat, Feb 14. 1995   
 *      Purpose:        Different humans in the Citadel.
 *      Modified:       Toby, 971014 (fixed a typo plus added random stats and a bit 
 *				      more random unarmed combat.)
 */
/* 2017-06-04 Malus: Removed names, set LIVE_I_NEVERKNOWN */

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
#include <stdproperties.h>

void
create_monster()
{
    ::create_monster();
    if (random(2))
	    set_gender(G_FEMALE);
    switch(random(9))
    {
    case 0:
	set_adj("holy");
	add_adj("priest");
	set_alignment(250);
	set_knight_prestige(-10);
	break;
    case 1:
	set_adj("pious");
	add_adj("cleric");
	set_alignment(200);
	set_knight_prestige(-5);
	break;
    case 2:
	set_adj("fanatic");
	add_adj("moralist");
	set_alignment(150);
	set_knight_prestige(-2);
	break;
    case 3:
	set_adj("dedicated");
	add_adj("merchant");
	set_alignment(100);
	set_knight_prestige(-1);
	break;
    case 4:
	set_adj("faithful");
	add_adj("accountant");
	set_alignment(50);
	set_knight_prestige(-1);
	break;
    case 5:
	set_adj("plain");
	add_adj("worker");
	set_alignment(10);
	set_knight_prestige(-10);
	break;
    case 6:
	set_adj("silent");
	add_adj("stranger");
	set_alignment(-150);
	set_knight_prestige(150);
	break;
    case 7:
	set_adj("cunning");
	add_adj("trader");
	set_alignment(-100);
	set_knight_prestige(3);
	break;
    case 8:
	set_adj("smart");
	add_adj("librarian");
	set_alignment(50);
	set_knight_prestige(0);
	break;
    case 9:
	set_adj("tough");
	add_adj("warrior");
	set_alignment(10);
	set_knight_prestige(0);
	break;
    }
    set_race_name("human");
    set_long("This human has decided to try to get an audience with the Lord "+
      "himself, in the hope of getting something out of it. What it is, you "+
      "have no idea of, but the person seems to practise on what to say in the "+
      "short time the Lord might sacrifice.\n");

    set_stats(({20+random(6),35+random(6),25+random(6),35+random(4),30,10}));
    set_skill(SS_UNARM_COMBAT, 30+random(6));
    set_skill(SS_DEFENCE,60);
    set_skill(SS_AWARENESS,40);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_random_move(random(20));
    set_act_time(3);
    add_act(({"emote smiles at you.","say Greetings stranger."}));
    add_act(({"emote ponders yet another one in the queue.","sigh"}));
    add_act(({"bow .","say Are you soon leaving?","smile hopefully"}));
    add_act(({"say He is a busy man, our Lord. But soon I will be called!",
	"smile proudly"}));
    set_cact_time(1);
    add_cact("say Why? What have I done to you?");
    add_cact("shout Heeeelp!");
    add_cact(({"scream","say Please stop this senseless act!"}));
    add_cact(({"say I am unarmed and unarmoured! This is unfair!","fume"}));
    set_title("citizen of Kabal");
    add_speak("I don't think I will get to see HIM today. I will probably "+
      "have to wait until tomorrow. Again...\n");
    set_default_answer("I am certain that your question is important, but "+
      "please ask someone else. I cannot help you.\n");
    add_ask(({"help","task","quest"}),"Hmmm...well if you are a magician, maybe "+
      "you can magically make the High Lord understand how "+
      "important it is that he gives me an audience!\n");
}
void
arm_me()
{
    object arm;
    seteuid(getuid(TO));
    arm = clone_object("/d/Kalad/common/central/arm/cit_human_robe");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/central/arm/cit_human_sandal");
    arm -> move(TO);
    command("wear all");
    MONEY_MAKE_SC(random(20)+10)->move(TO,1);
}   
