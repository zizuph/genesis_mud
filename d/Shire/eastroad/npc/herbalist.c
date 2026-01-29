#pragma strict_types
#pragma save_binary

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"

inherit "/d/Shire/lib/herbalist.c";
inherit HOBBITMAKER;

#define HERB_SAVE   WER_DIR + "herb_save"

void
create_hobbit() 
{
    set_power(180);
    set_type(ELDER);
    set_name("daisy");
    add_name("herbalist");
    set_gender(G_FEMALE);
    set_family_name("Proudfoot");
    set_title("Herbalist of the Shire");
    set_living_name("daisy");
    set_adj(({"wizened","elderly"}));
    add_prop(OBJ_S_WIZINFO,"@@wizinfo");
    remove_prop(LIVE_I_NEVERKNOWN);


    set_chat_time(7);
    add_chat("You would not have any unknown herbs, would you?");
/*
    add_chat("My wraps keep herbs fresh and orderly in a nice bundle.");
    add_chat("Have you tried my wraps yet?.");
    add_chat("Try my new wraps!");
*/
    add_chat("If you have an unknown herb, you can let me identify it for you.");
    add_chat("I still have not discovered the virtues of kingsfoil.");
    add_chat("You never know when a herb might come in handy.");
    add_chat("I've heard that the Rangers have books on herbs in their library.");
    add_chat("If you ask me, I can tell you about herbs and lore.");

    set_act_time(4);
    add_act("@@announce_selling");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"herbs","herb"}), VBFC_ME("ask_herbs"));
    add_ask(({"herblore","lore"}), VBFC_ME("ask_lore"));
  //  add_ask(({"wrap","wraps", "herb wrap", "herb wraps"}), VBFC_ME("ask_wraps"));

    set_max_herbs_kept(250);
    set_herbalist_id_herbs();
    configure_herbalist(HERB_SAVE);
}

void
introduce_hobbit(string str)
{
    str = LOW(str);
    if (!present(str, ENV(TO)))
	return;

    command("introduce myself to "+ str);
    command("say Hullo there "+CAP(str)+" nice to meet you! Would you like to try my wrap?");
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
    str +="-Lord Jaypeg-\n";
    return str;
}

string
ask_herbs()
{
    command("say Herbs? Well, I know most of them. You can buy " +
        "some from me because I have many in stock. If you have " +
        "an unknown herb, I can try to identify it for you as " +
        "long as you give it to me. If you want to learn about " +
        "herblore, ask me about it.");
    return "";
}


string
ask_wraps()
{
    command("beam proudly");
    command("say My herb wraps let you bundle up to 25 herbs in " +
        "a piece of cloth. Wraps make saving and recovering herbs much " +
        "easier! The wraps also keep them fresh and can be " +
        "stored in an herb pouch or jar.");

    return "";
}


string
ask_lore()
{
    command("say Herb lore? Well, there are only a few who know " +
        "as much about herbs as I do. Lothmir, the herb-master of " +
        "the Rangers knows a lot, too, but even I do not know all " +
        "the places where herbs grow.");
    return "";
}

string
default_answer()
{
    command("say I don't know what you are talking about!");
    return "";
}
