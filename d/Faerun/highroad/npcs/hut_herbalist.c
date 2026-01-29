/*
 * Herbalist of NoV
 * Based on Daisy from the Shire
 * -- Finwe, July 2007
 */

#pragma strict_types
#pragma save_binary

#include "/d/Faerun/defs.h"
#include "../nov.h"

inherit "/std/monster";
inherit "/d/Shire/lib/herbalist.c";

#define HERB_SAVE   NOV_DIR + "npcs/herb_save"
#define LOW(s)      lower_case(s)

void
create_monster() 
{
    int i;

//    set_name("shandri");
    add_name("herbalist");
    set_gender(G_FEMALE);
    set_living_name("shandri");
    set_race_name("human");
    set_adj(({"aged","serious"}));
    set_long("This is " + query_short() + ". She has long, black hair that is pulled back and held together with a gold cord. Her skin is tanned and she has dark eyes. Unlike most humans, she seems serious and knows much about plants and the earth.\n");
    remove_prop(LIVE_I_NEVERKNOWN, 0);
    for (i = 0; i < 5; i++)
        set_base_stat(i, 50);

    set_chat_time(7);
    add_chat("There are very few herbs I do not know.");
    add_chat("I will identify herbs you have found.");
    add_chat("The power of herbs is known only by a few.");
    add_chat("When properly prepared, herbs can become useful potions.");
    add_chat("If you ask me, I can tell you about herbs and lore.");

    set_act_time(4);
    add_act("@@announce_selling");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"herbs","herb"}), VBFC_ME("ask_herbs"));
    add_ask(({"herblore","lore"}), VBFC_ME("ask_lore"));

    set_max_herbs_kept(250);
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
	command("say I will sell you herbs if you need them.");
    else command("say I am currently out of herbs. I shall have to go get some.");
    return "";
}


string
ask_herbs()
{
    command("say Herbs are bits of plants that have useful properties. If you are unskilled, don't test the herb on yourself, test it on someone else until you're sure of its properties.");
    return "";
}



string
ask_lore()
{
    command("say Herbs are found everywhere, and in the most unlikely places sometimes. They can cure illneses, improve you senses, and even kill you when used by the unskilled. If you an herb you need identified, I can help you out.");
    return "";
}

string
default_answer()
{
    command("say I don't know what you are talking about!");
    return "";
}
