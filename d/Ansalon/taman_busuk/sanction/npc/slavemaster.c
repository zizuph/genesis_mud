
/*
 2007-07-07, Fixed a small problem with the slavemaster providing
 unlimited number of slaves. Only one slave / 15 min and player now.
 Cherek
 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"


inherit AM_FILE
inherit "/d/Ansalon/common/cheater";
inherit "/lib/unique";

#define MONEY 1 + random(2000)
#define WEP "/d/Ansalon/taman_busuk/neraka/wep/whip"
#define WEP2 "/d/Ansalon/taman_busuk/neraka/wep/weak_whip"
#define SLAVE_PROP "_garren_prop_asked_slaver"
#define SISTER_PROP "_garren_prop_asked_about_sister"
#define ALANNA_PROP "_garren_prop_asked_about_alanna"
#define KALEN_PROP "_garren_prop_asked_kalen"
#define MEETING_PROP "_garren_prop_asked_meeting"

// Prototypes
string alanna_response();
string kalen_response();
string meeting_response();

void
create_krynn_monster()
{
    set_name("slave-master");
    add_name("slavemaster");
    add_name("_sanction_slavemaster");
    set_race_name("human");
    set_adj("black-skinned");
    add_adj("cruel");
    set_long("This large, dark-skinned man from the isles of Ergoth " +
             "is a slave trader, one of the heartless member of a group that " +
             "sells flesh for a living. If you are after a slave to do with " +
             "as you wish, this is the man to see.\n");
    set_stats(({120,90,130,80,90,90}));
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_UNARM_COMBAT, 60);
    add_prop(OBJ_M_HAS_MONEY, MONEY);
    set_all_hitloc_unarmed(55);
    set_act_time(9);
    add_act("shout Slaves! Slaves for sale...");
    add_act("emote kicks a slave to the ground.");
    add_act("shout Only 2 gold coins! Elves from " +
            "Ergoth! Dwarves from the plains of Abanisinia...");
    add_act("say Ah, slaving will make me rich!");
    add_act("kick slave");
    add_act("growl");
    add_act("whip slave");

    add_ask(({"slave","slaves","price","list"}),
      "say You can buy a slave from me for a mere 2 gold coins! You " +
      "won't get a better price anywhere!", 1);

    add_ask("alanna", alanna_response, 1);

    add_ask("kalen", kalen_response, 1);

    add_ask("meeting", meeting_response, 1);
    
    add_prop(LIVE_I_NEVERKNOWN, 1);

    equip(({ clone_unique(WEP, 4, WEP2) }));

}

string alanna_response()
{
    if(TP->query_prop(SISTER_PROP) &&
       TP->query_prop(ALANNA_PROP))
    {
        TP->add_prop(SLAVE_PROP, 1);
        set_alarm(0.1, 0.0, &command("laugh loudly"));
        return "say That troublesome slave? I finally got rid of her. " +
               "Al though she did fetch a great price, she was hardly worth " +
               "the effort it took to bring her here. Now she is Kalen's problem.";
    }
    return "say Do you want to buy a slave?";
}

string meeting_response()
{
    if(TP->query_prop(MEETING_PROP))
    {
        return "say I have no idea what you are talking about.";
    }
    return "say Do you want to buy a slave?";
}

string kalen_response()
{
    if(TP->query_prop(SLAVE_PROP))
    {
        TP->add_prop(KALEN_PROP, 1);
        return "say Kalen? What do you want with him? He is a drunk that hangs around " +
               "taverns and is quick to hand out insults or pick a fight. Of course he does have a heavy purse " +
               "which makes it easier to overlook such flaws.";
    }
    return "say Do you want to buy a slave?";
}

void
init_living()
{
    ::init_living();
    ADA("buy");
}


buy(str)
{
    object pig,who; 
    int current_time, purchase_time;
       
    who = TP;
    current_time = time();  
    purchase_time = who->query_prop("_i_bought_slave");
  
    if (purchase_time+900 >= current_time)
    {
        NF("What?! I recently sold you a slave! I dont have unlimited you know!\n");
            return 0;
    }        

    NF("Buy what did you say?\n");
    if(!str || (str != "slave"))
	return 0;

    if (check_cheater(TP, TO))
	return 1;
    NF("The slave trader says: You cannot afford a slave! Begone!\n");
    if(!MONEY_ADD(TP, -288))
	return 0;

    write("The slave-master grins as you pass him his money. " +
      "He drags out a slave from the shadows by a chain and " +
      "passes it to you.\n");
    say("The slave-master grins greedily as " +QTNAME(TP) + " passes " +
      "him some money. The slave master drags out a slave from the " +
      "shadows by a chain and passes it to " +QTNAME(TP)+ ".\n");
      
    who->add_prop("_i_bought_slave", time());
    set_alarm(900.0, 0.0, &who->remove_prop("_i_bought_slave"));
    
    pig = clone_object(SNPC + "slave");
    pig->move(E(TO));
    pig->set_owner(TP);
    
    return 1;
}


public void
do_die(object killer)
{
    if(killer->query_prop(MEETING_PROP))
    {
        seteuid(getuid(TO));
        clone_object(SOBJ + "meeting_note")->move(this_object(), 1);
    }
    ::do_die(killer);
}

