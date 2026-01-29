/* Created by Dajala 
 * He sells the kits for the modules of the gizmo.
 * Standard-Gnome made by Grrrr.
 * Latest update: 20.03.1995
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>   /* This is needed to be able to use the macros, IS_CLONE */
#include "../guild/guild.h"     /* needed for GNOME_TITLES */
#include "../guild/modules.h"
#include <cmdparse.h>           /* for FIND_STR_IN_OBJECT */
#include <ss_types.h>

inherit M_FILE
inherit "/lib/shop";

#define STORE_ROOM GGUILD + "store.c"

//Prototypes
string namer();
string brain();

void
create_krynn_monster()
{
    int i;
    string name, *word;

    set_name("gnome");
    add_name("emong");
    set_living_name("gnome");
    name = namer();
    set_short(name);
    word = explode(name, " ");
    set_adj(word[0]);
    set_long("He is in charge of running the workshop and will sell the "
	+ "necessary parts for building the modules of the gizmo to "
	+ "members of the Inventor guild. You could probably ask him for help "
    + "if you need it.\n");
    set_race_name("gnome");

    set_default_answer("say What?DoYouNeedSomeHelp?", 1);
    add_ask("[for] 'help'", "@@ask_help", 1);

    if (!IS_CLONE) /* Added by Nick, to get rid of some possible errors. */
	return;

    set_gender(0);
    add_act(brain);
    add_cact("say HeyHaveYouLostYourMind?");
    add_cact("say WhereWasThatFlameThrower?");
    set_act_time(10);
    set_cact_time(5);
    for (i = 0; i < 6; i++)
	set_base_stat(i, 15 + random(25));
    set_hp(10000);
    set_alignment(200);
    set_all_hitloc_unarmed(30);
    set_all_attack_unarmed(30,30);
    set_skill(SS_DEFENSE, 50);
    set_knight_prestige(-2);

    config_default_trade();
    set_money_greed_sell(100);
    set_money_greed_buy(100);
    set_store_room(STORE_ROOM);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);

    set_alarm(1.0, -1.0, "equipme");
}

string
namer()
{
    string *desc1, *desc2;
    string name;
    int a, b;
 
    desc1 = ({"small", "stout", "fat", "short", "clever" });
    desc2 = ({"red-bearded", "blue-eyed", "elderly", "white-haired" });
    a = random(4);
    b = random(4);
    name = desc1[a] + " " + desc2[b] + " gnome";
    return name;
}

string
brain()
{
    int i;
    string *stuff;

    stuff = ({"a hammer", "a spring-loaded whatsit",
	"several large balls of string", "a smoking pair of shoes"});
    i = random(5);
    if ((!i) || i == 1)
    {
	command("say IHopeEverythingYouNeedIsPresent.");
	command("say IfNot,IWillTryToOrderIt.");
    }
    else if (i == 2)
    {
	command("say NeedsMoreBellsAndWhistlesAndStuff.");
    }
    else if (i == 3)
    {
	command("say IfYouNeedHelp,Inquire.");
	command("smile helpfully all");
    }
    else
    {
	tell_room(environment(), "A gnome runs by carrying " +
	    stuff[random(sizeof(stuff))] + ".\n");
    }
    return "";
}

/********************* Here the new code starts **************************/

void
init_living()
{
   ADD("do_buy_check", "buy");
   ADA("inquire");
}

void
ask_help()
{
   command("say ICouldTellYouALotAboutThePricesOfTheModules");
   command("say AndTheLevelsNeededToBeAllowedToBuySome.");
   command("say FeelFreeTo'InquireAboutThePriceOfThe<Module>'" +
           "Or'InquireAboutTheLevelOfThe<Module>'");
   command("say HaveALookAtThePosterHereForAnIdeaOfWhatIsAvailable.");
   command("point poster");
   command("say OnceYouHaveDecidedWhichOneYouWouldLikeToBuy,"
           +"IWillSellThePartsToYou.");
   command("smile helpfully");
}

/* Returns the level needed to build a module. 
 */
string
answer_level(string module)
{
   int i;
   for (i=0;i<sizeof(TYPES);i++)
	if (module == TYPES[i]) return LEVELS[i];
   return "x";
}

/* Returns the title needed to build a module. 
 */
string
answer_title(string module)
{
   string *title = GNOME_TITLES;
   string level;

   if((level = answer_level(module)) == "x")
	return "";
   return title[atoi(level[1..1])];
}

/* returns the price of a module */
string
answer_price(string module)
{
   int i;
   for (i=0;i<sizeof(TYPES);i++)
	if (module == TYPES[i]) return PRICES[i];
   return "";
}

int
inquire(string str)
{
    string what, item;

    NF("Inquire about what?\n");
    if (!str)
        return 0;
    NF("Inquire about the price/level of a what?\n");
    if (!parse_command(lower_case(str), ({}),
                "[about] [the] %w 'of' [the] %s", what, item))
        return 0;
    NF("You can only inquire about the price or level.\n");
    if (what != "price" && what != "level")
        return 0;
    write(what + "|" + item);
    set_alarm(1.0, -1.0, "inquire_2", what, item);
    return 1;
}

void
inquire_2(string what, string item)
{
    string answer;

    if (strlen(item))
    {
        if (what == "level")
        {
            answer = implode(explode(answer_title(item), " "), "");
            if (strlen(answer))
            {
                command("say YouNeedToBeAtLeastA" + 
                        answer + "ToBuyThatModule.");
                return;
            }
        } else {
            answer = answer_price(item);
            if (strlen(answer))
            {
                command("say ThePriceForThePartsForThatModuleIs" + answer + ".");
                return;
            }
        }
    }
    command("say WeDoNotCarryPartsForThat.");
}

/* We want to check for level before we let anybody buy something */
int
do_buy_check(string str)
{
   int i;
   object gizmo;
   string answer, who = implode(explode(TP->query_nonmet_name(), " "), "");

   if(!GMEMBER(TP))
   {
	command("say OnlyInventorsMayBuyModules," + who + ".");
	command("frown");
	return 1;
   }
   gizmo = P("k_gizmo", TP);
   if(!gizmo)
   {
	command("say YouWillNeedAGizmo.GoAndGetOneFirst," + who + ".");
	command("smile helpfully");
	return 1;
   }
   answer = answer_level(str);
   if(((gizmo->query_gnome_level()) < atoi(answer[1..1])) || 
	(E(gizmo)->query_skill(SS_PROMOTE) < atoi(answer[0..0])))
   {
	command("say IAmNotAllowedToSellThatToYou," + who + ".");
	command("say YouHaven'tReachedTheNecessaryLevelYet.");
	command("comfort " + (TP->query_real_name()));
	return 1;
   }

   for (i=0;i<sizeof(TYPES);i++)
	if (str == TYPES[i]) return do_buy(str);
   command("say WeDoNotSellThat" + who + ".");
   return 1;

}


/* We want fixed prices - no haggling */

int
query_buy_price(object ob)
{
	return 2 * ob->query_prop(OBJ_I_VALUE);
}
