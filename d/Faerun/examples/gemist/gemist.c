/*
 * Based on Daisy from the Shire
 * -- Finwe, July 2007
 * Gems can be found at /d/Genesis/gems/obj
 */

#pragma strict_types
#pragma save_binary

#include "/d/Faerun/defs.h"

inherit "/std/monster";
inherit "/d/Faerun/examples/gemist/gemist_file.c";

// This path is where the gems are saved
#define GEMS_SAVE   "/d/Faerun/examples/gemist/gems_save"

#define LOW(s)      lower_case(s)

void
create_monster() 
{
    int i;

//    set_name("shandri");

    set_gender(G_MALE);
    set_race_name("dwarf");
    set_adj(({"short","weathered"}));
    set_short("short eathered dwarf");
    set_long("This local gemist. He buys and sells gems.\n");

    remove_prop(LIVE_I_NEVERKNOWN);
    for (i = 0; i < 5; i++)
        set_base_stat(i, 50);

    set_chat_time(7);
    add_chat("Gems are wonderful!.");
    add_chat("If you have any gems, I will buy them from you.");
    add_chat("I will sell you gems, if you have enough coin.");

    set_act_time(4);
    add_act("@@announce_selling");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"gem","gems"}), VBFC_ME("ask_gems"));

    set_max_gems_kept(250);
    set_gemist_id_gems();
    configure_gemist(GEMS_SAVE);
}

void
init_living()
{
    init_gemist();
    ::init_living();
}

void
enter_inv(object gem, object from)
{
    ::enter_inv(gem, from);
    init_gemist_identify(gem,from);
}

string
announce_selling()
{
    if (query_gem_list_size()) 
	command("say I will sell you gems if you want them.");
    else command("say I will have to go get more gems. I just sold my last one.");
    return "";
}


string
ask_gems()
{
    command("say Gems are wonderful. Some can be cut a myriad different ways, but all can be polished to a beautiful luster.");
    return "";
}


string
default_answer()
{
    command("say I don't know what you are talking about!");
    return "";
}
