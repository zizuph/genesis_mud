/* created by Aridor 06/19/93 */


#include "/ss_types.h"
#include "../../local.h"
#include <macros.h>

inherit CITIZEN;
inherit "/lib/pub.c";

string ran_price();

void
create_krynn_monster()
{
    set_name("farley");
    set_living_name("barkeeper");
    set_race_name("kender");
    set_adj("busy");
    add_name("barkeeper");
    add_name("bartender");

    set_short("barkeeper");
    set_long("The barkeeper is busy serving his guests.\n");

    set_stats(({30, 34, 25, 40, 31, 92}));
    set_hp(2000);

    set_chat_time(0);
    add_chat("Who had the beer?");
    add_chat("What would you like, please?");
    add_chat("You're not looking for a job, are you?");
    add_chat("@@ran_price");
    add_chat("Thanks, and welcome back.");

    set_act_time(1);
    add_act("close door");

    set_default_answer(VBFC_ME("imbusy"));
    add_ask(({"proprietor","job","help","work","quest","task"}),VBFC_ME("pointwest"));
    /*add_ask(({"task","quest"}),VBFC_ME("know_nothing"));*/
    add_ask(({"kustennebel","schnapps"}),VBFC_ME("sorry_out"));

    add_cmd_item(({"kustennebel","schnapps"}),"buy",VBFC_ME("sorry_out"));

    add_drink(({"wine","wines","small","small wine"}),
          "wine", "small", 100, 10, 20, 0, 0,
         "It is a small and rather tasteless wine.\n", 0);
    add_drink(({"beer","beers","Pfusch","Pfusch beer","Pfuschbeer"}),
          "beer","Pfusch", 200, 4, 12, 0, 0,
         "This is one of the specialities of Palanthas: Pfusch beer, brewed"
        +"from homegrown hop and malt!\n", 0);
/* formula is 10 + alco*alco/10*/
/*    add_drink(({"schnapps","kustennebel"}),"Kustennebel",
          "",100,40,170,"Kustennebel","Kustennebel",
          "This is another of Palanthas' specialities: homemade "
          + "Kustennebel!\n", 0);
   *   Kustennebel is ONLY sold for 5 resets  *
   *   after quest 2 AND 3 have been solved. */

    add_food(({"roll","bread","Roll","Bread"}),"roll","",50,13,"roll","rolls",
         "An ordinary roll, it looks like a small bread.\n", 0);
    add_food(({"egg","Egg","hardboiled egg"}),"egg","hardboiled",75,50,"harboiled egg",
    "hardboiled eggs","A hardboiled peeled egg, fresh and ready to eat!\n", 0);
    add_food(({"pancake","Pancake"}),"pancake","",240,100,"pancake","pancakes",
         "A round piece of fried dough, it looks very tasty!\n", 0);
    add_food(({"dinner","Dinner","special dinner","Special Dinner"}),"dinner","special",
         500,360,"special dinner","special dinners",
         "This is a combination of foods, making up a full meal. You find a " +
         "piece of roll, two pancakes, some fish and a salad in the pack.\n",0);
}


imbusy()
{
  command("say I'm sorry but I'm very busy.\n");
  return "";
}


pointwest()
{
  command("point west");
  return "";
}


know_nothing()
{
  command("say Don't bother me with that, I know of nothing.\n");
  return "";
}

init_living()
{
    init_pub();
}


ran_price()
{
    return ("That'll be " + (random(112) + 8) + " coppers.");
}


sorry_out()
{
  command("say Sorry, we're out!");
  command("say If you want to get some, ask the proprietor for a job.");
  return "";
}
