/* 
 * Innkeep of the finest Palanthian inn, the Greystone.
 * Sells private room keys for 4pc.
 * Mortis 11.2005
 */

#include "../../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"


inherit CITIZEN;
inherit "/d/Ansalon/common/cheater";
inherit "/lib/unique";
string rentor1;

#define MONEY		3000 + random(3000)
#define KEYROOM		NOBLE + "grey_key_stall"
#define KEYROOM1	"/d/Krynn/solamn/palanthas/nobles/grey_key_stall"

void
create_krynn_monster()
{
    set_name("janne");
    set_race_name("human");
    set_adj("well-composed");
    add_adj("black-vested");
	set_short("well-composed black-vested innkeep");
	set_pshort("well-composed black-vested innkeeps");
	add_name(({"janne", "havecius", "innkeep", "innkeeper", "proprietor"}));
	set_title("Havecius, Innkeep of the Greystone Inn");
    set_long("The innkeep is a tall, elder gentleman wearing his still "
	+ "black hair combed tightly to his scalp and neck.  He wears a crisp, "
	+ "white shirt under his black, silk vest and pressed, black slacks.  "
	+ "A white linen towel is folded sharply over his shoulder.  He "
	+ "maintains a somber expression but is always amenable and courteous "
	+ "with the patrons.\n");

    set_stats(({40,55,60,100,110,40}));
	set_size_descs("of normal length", "lean");
	set_appearance(5);

    set_skill(SS_DEFENCE, 35);
    set_skill(SS_AWARENESS, 55);
    set_skill(SS_UNARM_COMBAT, 45);
    add_prop(OBJ_M_HAS_MONEY, MONEY);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

	set_alignment(800);
	set_knight_prestige(-9);
	set_introduce(1);
    set_act_time(10);
    add_act("say The finest rooms in the city are found here at the "
	+ "Greystone.");
    add_act("say The inn has been in my family for generations.  May it "
	+ "always be so.");
    add_act("emote nods respectfully at a patron.");
    add_act("say May we provide you with a room?  Our prices are "
	+ "appropriate for their quality.");
    add_act("emote acknowledges you with a curt, respectful nod.");
    add_act("smell");
	add_act("emote pulls a white linen towel off his shoulder and wipes "
	+ "down the counter before folding it properly and replacing it over "
	+ "the shoulder of his black, silk vest.");
    add_act("emote takes a wine glass hanging over the counter, places "
	+ "it under the tap of the middle cask behind him, and procures a "
	+ "small quantity of red wine which he swirls around in the glass "
	+ "and drinks in one gulp, nodding his head in satisfaction at the "
	+ "results.");
	add_act("say May we serve you in some way?  May I recommend something?");

	add_ask(({"inn", "greystone", "greystone inn"}), "He replies:  The "
	+ "Greystone Inn has been in my family for generations.  In fact it "
	+ "was my ancestor Denne Havecius who arranged its construction.\n"
	+ "He leans in close and says:  Though it was he who ordered the "
	+ "import of its distinctive granite from the south, they say it was "
	+ "actually his wife Feya's suggestion.\n");
//	add_ask(({"denne", "denne havecius"}), "
//	add_ask(({"feya", "feya havecius"}), "
	add_ask(({"tavern", "bar"}), "Frowning, he replies:  The Greystone is "
	+ "neither bar nor tavern.  It is an inn of the highest repute for "
	+ "those of refined tastes in Palanthas.  If a bar or tavern is your "
	+ "preferred venue, might I recommend you frequent the Merchant or "
	+ "Aesthetic districts?\nHe smiles tight-lipped and with a nod returns "
	+ "to going about his business.\n");
	add_ask(({"room", "rooms", "rent", "rent room"}), "He replies:  Ahh, "
	+ "yes.  You've come to the finest inn in the city.  For four platinum "
	+ "you may take one of our rooms for as long as the world remains, how "
	+ "are they putting it these days... \"unrefreshed?\"  Yes, I believe "
	+ "that's it.  Rest assured, you will find all the amenities a person "
	+ "of your stature is accustomed to and more.\n");
/*	add_ask(({"food", "meal" -Describe food. All hunted for, quest for
			players to bring corpses for payment
	add_ask(({"wine", "brew", "beer", "cherry"
	add_ask(({"recommend", "recommendation", "recommendations",
		"what do you recommend?", "what do you recommend",
		"recommend something", "recommend something?"}), "
    add_ask(({" Info about tapestry, ancestors, perhaps quest regarding
                  princess in tapestry. */

}

void
init_living()
{
    ::init_living();
    ADA("rent");
}

rent(str)
{
	object ob;
	object room = find_object(KEYROOM);
	string rentor1 = OB_NAME(TP);

	KEYROOM1->load();
	KEYROOM1->reset_palan_room();

    NF("Rent what?  May I get you a room?\n");
    if(!str || (str != "room"))
	return 0;

    if (check_cheater(TP, TO))
	return 1;

	NF("The innkeep says:  All rooms at the Greystone are taken.  "
	+ "I am sorry, but I cannot give you an estimate when any of our "
	+ "patrons will be checking out.\n");
	if (ob = !present("key", room))
	return 0;

    NF("I am sorry, but you need four platinum to rent a room.\n");
    if(!MONEY_ADD(TP, -6912))
	return 0;

	you_rented();
	command("crobb blat");
	command("give key to " + rentor1);
	return 1;

}

void
you_rented()
{
	write("The innkeep takes his payment and drops the coins with a 'ching' "
	+ "into a lockbox under the counter.  Reaching beneath the counter, he "
	+ "pulls out a copper key and hands it to you saying:  The room is yours "
	+ "for as long as you like until the world \"refreshes\".\n"
	+ "He pulls a cord above the counter and a bell rings in the kitchen.\n"
	+ "A maid hurries out of the double doors in in the southwest carrying "
	+ "a serving tray and goes up the stairs.\n"
	+ "The innkeep says:  You will find everything prepared for you "
	+ "upstairs.  Oh, yes, I suggest you read the note on the nightstand by "
	+ "your bed as soon as possible.  It will help you prevent the loss of "
	+ "your key which is one of a kind.  Not even I have a spare so please "
	+ "take care of it and return it if you are through with your room.  It "
	+ "could take days to have it replaced.\n");

    say("The innkeep nods courteously as " + QTNAME(TP) + " passes him some "
	+ "money which he drops into a lockbox beneath the counter with a "
	+ "'ching'.  From under the counter he pulls out an odd key and hands "
	+ "it to " + QTNAME(TP) + " saying:  The room is yours for as long as "
	+ "like until the world \"refreshes\"\n"
	+ "He pulls a cord above the counter and a bell rings in the kitchen.\n"
	+ "A maid hurries out of the double doors in in the southwest carrying "
	+ "a serving tray and goes up the stairs.\n"
	+ "The innkeep says:  You will find everything prepared for you "
	+ "upstairs.\n");
}

void
arm_me()
{
    seteuid(getuid(TO));

	MONEY_MAKE_PC(1 + random(3))->move(TO);
	MONEY_MAKE_GC(20 + random(38))->move(TO);
	MONEY_MAKE_SC(40 + random(90))->move(TO);
}
