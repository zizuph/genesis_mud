/*
 * Herbalist of Rivendell
 * Based on Daisy, Herbalist of Shire
 * Finwe, july 1999
 */

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include "/d/Shire/rivendell/npc/elfmaker.h"
#include "/sys/composite.h"

inherit KILL_LOGGER;
inherit "/d/Shire/rivendell/npc/elfmaker.c";
inherit "/d/Shire/lib/herbalist.c";

#define HERB_SAVE   RIVENDELL_DIR + "herb_save"

void
create_elf()
{
    set_type(CITIZEN);
    set_elf_average(110);
    set_name("maeryon");
    set_adj("golden-haired");
    set_adj("articulate");
    set_race_name("elf");
    set_gender(G_FEMALE);
    set_long("This elf has the look of " + 
        "wisdom in her eyes. She looks as if she spends a great " +
        "deal of time in the gardens and other outdoor places. " +
        "But here, in her shop, she busily keeps the herbs and " +
        "plants in order.\n");

    set_chat_time(120+random(60));
//    add_chat("Try my herb wraps. They keep herbs fresh and orderly in a nice bundle.");
    add_chat("I can identify almost any plant you have.");
    add_chat("If you can't identify a plant, I can do it for you.");
    add_chat("The benefits of athelas are known to me.");
    add_chat("Elrond can heal anything with my herbs.");
    add_chat("Have you got any extra herbs I can buy from you?");
    add_chat("Be sure you know what plants you have before using them.");

    set_act_time(120+random(60));
    add_act("@@announce_selling");
    add_act("emote hangs some plants up to dry.");
    add_act("emote cleans out some storage bins.");
    add_act("emote takes down some herbs and puts them into " +
        "bins and jars.");
    add_act("emote bundles some plants and hangs them up.");
    add_act("emote sorts some new plants into several piles.");
    add_act("emote opens up a book and identifies some plants.");
    add_act("emote hums quietly while sweeping the shop.");


    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"herbs","herb"}), VBFC_ME("ask_herbs"));
    add_ask(({"herblore","lore"}), VBFC_ME("ask_lore"));
  //  add_ask(({"herb wrap", "herb wraps", "wraps","wrap"}), VBFC_ME("ask_wraps"));

    set_max_herbs_kept(1500);
    set_herbalist_id_herbs();
    configure_herbalist(HERB_SAVE);



}

void
init_living()
{
    init_herbalist();
    ::init_living();
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
    str +="-Steward Finwe-\n";
    return str;
}

string
ask_herbs()
{
    command("say Herbs?");
    command("say Well, I know most of them!");
    command("say You can buy some from me, and I sell herbs, too!");
    command("say If you have an unknown herb, I can try to identify");
    command("say it for you, if you give it to me.");
    command("say If you want to learn about herblore, ask me about it.");
    return "";
}

string
ask_lore()
{
    command("say Herb lore?");
    command("say I know almost everything about herblore. It is " +
        "what I study the most.");
    command("say But even I do not know all the places where herbs grow!");
    return "";
}

string
ask_wraps()
{
    command("beam proudly");
    command("say Herb wraps are a piece of cloth that let you wrap 25 " +
        "of the same herbs together. They make saving and recovering " +
        "herbs much easier! The wraps also keep them fresh and can " +
        "be stored in an herb pouch or jar.");

    return "";
}

string
default_answer()
{
    command("say I don't know what you are talking about!");
    return "";
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
    TP->catch_msg(QTNAME(TO)+" hands you "+text+".\n");
}
/*void
introduce_hobbit(string str)
{
    str = LOW(str);
    if (!present(str, ENV(TO)))
	return;

    command("introduce myself to "+ str);
    command("say Hullo there "+CAP(str)+" nice to meet you! Would you like to try my wrap?");
}
*/
