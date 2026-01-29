/* 
 * Barkeep of the Green Twitch Inn in the merchants quarter of
 * Palanthas.
 * 
 * Mortis 01.2006
 */

#include "../../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"


inherit CITIZEN;

#define MONEY 11 + random(300)

void
create_krynn_monster()
{
    seteuid(getuid(TO));

	set_name("twitch");
	set_living_name("twitch");
    set_race_name("human");
    set_adj("googly-eyed");
    add_adj("grey-haired");
	add_name(({"twitch", "innkeep", "barkeep", "carl", "innkeeper",
		"barkeeper"}));
	set_title("Aildredge, Innkeep of the Green Twitch Inn");
    set_long("The innkeep is missing quite a few teeth in his crazed grin.  "
	+ "His grey hair is thin and hangs off the sides of his head, and his "
	+ "large, round, bulging eyes spin googly in their sockets.\nHe is "
	+ "wearing a beige longshirt down to his knees.\nHe is wearing brown "
	+ "stockings beneath his longshirt.\nHe is wearing leather slippers that "
	+ "point up at the toes.\n");

    set_stats(({80, 100, 205, 70, 150, 100}));
    set_skill(SS_DEFENCE, 45);
    set_skill(SS_AWARENESS, 45);
    set_skill(SS_UNARM_COMBAT, 50);
	set_size_descs("short", "lean");
	set_appearance(1);
	set_alignment(450);
	set_knight_prestige(-70);

	set_all_hitloc_unarmed(25);

	add_prop(OBJ_M_HAS_MONEY, MONEY);
	set_introduce(1);
    set_act_time(12);
    add_act("say Who wants ta chug ale?");
    add_act("say Any wanna drink all night?");
    add_act("emote slowly breaks a crazed smile revealing a great many "
	+ "missing teeth.");
    add_act("emote gazes around bizarrely with his large, round, bulging "
	+ "googly eyes.");
	add_act("burp");
	add_act("We gots cots for rent in the common room.  Want one?");
	add_act("Man, oh man.  Love me that black meade, but lemme warn you "
	+ "against drinking less than one at a time.  Ha!");
	add_act("shout Drinksin time now!");
	add_act("emote looks around to see if anyone is watching and pretends "
	+ "he isn't passing large amounts of gas.\nHis beige longshirt billows "
	+ "out conspicuously behind him.");
	add_act("emote pulls at his scraggly, thin gray hair as he peers around "
	+ "with his bulging googly eyes.");
	add_act("emote scratches at his brown stockings with a crazed grin on "
	+ "his face.");
    add_act("time");
	add_act("smell");
   
    set_cact_time(10);
	add_cact("emote cries out:  Oh Paladine, no!!!");

    add_ask(({"coffee", "coffees"}), "say I likes the coffees of the "
	+ "Palatial Plaza.  They don't kill me buzz.", 1);
	add_ask(({"food", "meat", "chicken", "pheasant", "pork", "boar", "lamb"}),
	  "say Oh yeah, we cooks the meat on spits right over the fire.  Just "
	+ "have a look right now.  Juicy and succulent, mmmmm, mmm.", 1);
	add_ask(({"drink", "drinks", "beer", "sancristiovese"}), "say Oh "
	+ "yeah, we've some fine drinks what with our Harrmoor Dark beer and "
	+ "Sancristiovese wine from the slopes of Mt. Sancrist.  They're a-good "
	+ "for sippin and the such too if you like that kind of pace.  Me?  "
	+ "I prefer an ale or meade.", 1);
	add_ask(({"ale", "ales", "meade", "meades"}), "say Oh yeah, now that's "
	+ "what I like, a good chuggin drink.  I make the ales myself of course, "
	+ "and the meades?  Well, I make them, too, whaddaya know?  Why they're "
	+ "just the drinks you need for a good drinkin contest!", 1);
	add_ask(({"city", "palanthas"}), "say Oh yeah, now this is a right fine "
	+ "city, and I'll swear to that, yeah.  We've the best of everything "
	+ "here.  Just stay here for dinner and see what we've got to eat and "
	+ "drink.  Then take you a cot in the common room and enjoy our "
	+ "hospitality.", 1);
	add_ask(({"key", "keys", "cot", "cots"}), "say If you want a key to a "
	+ "cot in the common room, just <buy key> and I'll sell you one.  "
	+ "Then you're welcome to stay here for a rest.", 1);
	add_ask(({"inn"}), "say This is my own inn and a fine one at that, yeah.  "
	+ "We've the best spit roasted meats, wild game, and fresh-brewed "
	+ "drinks as well as nice cots for sleeping it off.", 1);

	set_default_answer("@@def_answer");

	set_alarm(1.0,0.0,"arm_me");

}

void
arm_me()
{
	MONEY_MAKE_GC(random(12))->move(TO);
	MONEY_MAKE_SC(25 + random(20))->move(TO);
}

string
def_answer()
{
	command("emote shrugs unknowingly as he stares with his bulging, googly "
	+ "eyes and crazed grin.");
    return "";
}
