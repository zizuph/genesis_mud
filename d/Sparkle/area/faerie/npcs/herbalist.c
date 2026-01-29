/*
 * Hebalist of Green Oaks
 * Based on the herbalist in Rivendell
 * By Finwe, December 2004
 */

inherit "/std/monster";
inherit "/d/Shire/lib/herbalist.c";

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>

#define HERB_SAVE   HERB_DATA_DIR + "herb_save"

void
create_monster()
{
    set_race_name("elf");

    set_name("toluca");
    set_adj("golden-haired");
    set_adj("knowledgeable");
    set_short("knowledgeable golden-haired elf");
    set_long("This elf has sparkling blue eyes that seem to look wise. She " +
        "has slightly green fingers from all the time she spends outdoors " +
        "in gardens and the forest. As the local herbalist, she seems " +
        "to know a lot about plants and herbs.\n");
    set_title("Tel-Kira, Master Herbalist of Green Oaks");

    set_skill(SS_DEFENCE,       100);
    set_skill(SS_UNARM_COMBAT,  100);
    set_skill(SS_AWARENESS,     100);
    set_skill(SS_PARRY,         100);

    add_prop(OBJ_M_NO_ATTACK, 1);   // non-killable

    set_chat_time(40+random(10));
    set_gender(G_FEMALE);
//    add_prop(NPC_I_NO_LOOKS,   1);
//    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_chat_time(120+random(60));
    add_chat("I can identify almost any plant you have.");
    add_chat("Herbs have many medicinal properties.");
    add_chat("Be careful what herbs you eat. Some are deadly.");
    add_chat("Have you got any extra herbs I can buy from you?");
    add_chat("Be sure you know what plants you have before using them.");

    set_act_time(120+random(60));
    add_act("@@announce_selling");
    add_act("emote hangs some plants up to dry.");
    add_act("emote cleans out some storage bins.");
    add_act("emote takes down some herbs and puts them into bins and jars.");
    add_act("emote bundles some plants and hangs them up.");
    add_act("emote sorts some new plants into several piles.");
    add_act("emote opens up a book and identifies some plants.");
    add_act("emote hums quietly while sweeping the shop.");

    set_max_herbs_kept(100);
    set_herbalist_id_herbs();
    configure_herbalist(HERB_SAVE);

}

void
enter_inv(object herb, object from)
{
    ::enter_inv(herb, from);
    init_herbalist_identify(herb,from);
}

string
announce_selling()
{
    if (query_herb_list_size()) 
	command("say I have herbs for sale too, would you like some?");
    else command("say I should go and search for more herbs.");
    return "";
}

string
wizinfo()
{
    string str;

    str = "This Herbalist stores up to "+query_herbs_max_kept()+
    " herbs of same type at one time.\n\n";

    if (!query_herb_list_size())
    {
	str += "The herbalist has no herbs for sale now.\n";
	return str;
    }
    str += "The herbalist has these herbs for sale:\n";
    str += query_herb_list();
    str +="-Finwe-\n";
    return str;
}

void 
herbalist_sold_hook(object *herbs)
{
    command("say Thank you for these herbs.");
    command("emote opens some drawers and places " + 
        COMPOSITE_DEAD(herbs)+ " in them.");
}

void 
herbalist_pay_hook(string text)
{
    TP->catch_msg(QCTNAME(TO)+" hands you "+text+".\n");
}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}

void
init_living()
{
    object  note;

    ::init_living();
    init_herbalist();

}
