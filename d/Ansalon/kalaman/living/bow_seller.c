#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"


inherit AM_FILE
inherit "/d/Ansalon/common/cheater";

string *gAdj1 = ({"noble","happy","sly"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    set_name("bowyer");
    set_race_name("human");
    set_adj("brawny");
    add_adj(ONE_OF(gAdj1));
    set_short(implode(query_adjs()," ") + " bowyer");
    set_long("This brawny craftsman is a maker and seller of the renown "+
       "Solamnian longbows, grey goose feathered arrows, and hemp bowstrings. "+
       "You could probably purchase them from him for a fair price.\n");
    set_stats(({140,70,75,55,55,60}));
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_UNARM_COMBAT, 60);
    set_all_hitloc_unarmed(10);
    set_act_time(9);
    add_act("shout Longbows! Arrows! Bowstrings! Get them here!");
    add_act("say The Solamnian Longbows are renown for their penetration!");
    add_act("say My arrows are fletched with grey goose feathers.");
    add_act("say I'd suggest you buy up on the bowstrings! You never know "+
       "when you may need one!");


    add_ask(({"bow", "longbow","solamnian longbow","arrow","arrows","bowstring"}),
      "Solamnian longbows are 14 gold coins. 20 silver for 12 arrows. And "+
      "12 copper for a bowstring!\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
}

void
init_living()
{
    ::init_living();
    ADA("buy");
}


buy(str)
{
    object pig, who;

    if (check_cheater(TP, TO))
        return 1;

    if (str == "longbow")
    {
        NF("The man says: You cannot afford a Solamnian longbow.\n");
        if(!MONEY_ADD(TP, -2016))
	    return 0;

        write("You pay the man, and he passes you a " +
          "solamnian longbow.\n");
        say(QCTNAME(TP) + " buys a solamnian longbow from the " +
          "brawny bowyer.\n");

        who = TP;
        pig = clone_object(KOBJ + "weapon/solamn_longbow");
        if (pig->move(who) != 0)
        {
              write("Noticing that you are too burdened to carry the longbow, the man " +
    	        "places it on the ground before you.\n");
    	      say("The man places the longbow on the ground before " + QTNAME(TP) + ".\n");
    	      /* pig?? */
    	      pig->move(environment(who));
         }
         return 1;
     }

    if (str == "arrows")
    {
        NF("The man says: You cannot afford a dozen arrows.\n");
        if(!MONEY_ADD(TP, -240))
	    return 0;

        write("You pay the man, and he passes you a " +
          "dozen arrows.\n");
        say(QCTNAME(TP) + " buys a dozen arrows from the " +
          "brawny bowyer.\n");

        who = TP;
        pig = clone_object(KOBJ + "weapon/solamn_arrow");
        if (pig->move(who) != 0)
        {
              write("Noticing that you are too burdened to carry the arrows, the man " +
    	        "places it on the ground before you.\n");
    	      say("The man places the arrows on the ground before " + QTNAME(TP) + ".\n");
    	      /* pig?? */
    	      pig->move(environment(who));
         }
         return 1;
     }

    if (str == "bowstring")
    {
        NF("The man says: You cannot afford a bowstring.\n");
        if(!MONEY_ADD(TP, -12))
	    return 0;

        write("You pay the man, and he passes you a " +
          "bowstring.\n");
        say(QCTNAME(TP) + " buys a bowstring from the " +
          "brawny bowyer.\n");

        who = TP;
        pig = clone_object(KOBJ + "weapon/bowstring");
        if (pig->move(who) != 0)
        {
              write("Noticing that you are too burdened to carry the bowstring, the man " +
    	        "places it on the ground before you.\n");
    	      say("The man places the bowstring on the ground before " + QTNAME(TP) + ".\n");
    	      /* pig?? */
    	      pig->move(environment(who));
         }

        return 1; 
     }

    NF("Buy what did you say you wanted to buy? A longbow, arrows, or bowstring?\n");
	return 0; 


}
