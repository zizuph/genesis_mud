/*
 * Sample alchemist
 * Based on Daisy from the Shire
 * -- Finwe, July 2007
 */

#pragma strict_types
#pragma save_binary

#include "/d/Faerun/defs.h"

inherit "/std/monster";
inherit "/d/Faerun/lib/alchemist.c";

#define POTION_SAVE     "/d/Faerun/lib/potion_save"
#define IS_NOV_POTION   "_i_is necro_potion"

    void
create_monster() 
{
    int i;

    set_name("wydda");
    add_name("alchemist");
    set_living_name("wydda");
    set_gender(G_FEMALE);
    set_adj(({"wizened","elderly"}));
    remove_prop(LIVE_I_NEVERKNOWN);

    for (i = 0; i < 5; i++)
        set_base_stat(i, 120);

    set_chat_time(7);
    add_chat("You wouldn't happen to have any potions available, would you?");
    add_chat("Potions are dangerous when used by inexperienced fools.");
    add_chat("I have studied potions for many years, and always learn something new.");
    add_chat("The right potion can save you--or destroy you.");
    add_chat("If you have an extra potion, I'll buy it from you.");
    add_chat("Beware of any unknown potion.");

    set_act_time(4);
    add_act("@@announce_selling");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"potion","potions"}), VBFC_ME("ask_potions"));
    add_ask(({"potion lore","lore"}), VBFC_ME("ask_lore"));

    set_max_potions_kept(250);
    configure_alchemist(POTION_SAVE);
}


void
init_living()
{
    init_alchemist();
    ::init_living();
}


string
announce_selling()
{
    if (query_potion_list_size()) 
	command("say I have potions for sale too, would you like some?");
    else command("say I should brew more potions.");
    return "";
}

string
ask_potions()
{
    command("say Potions? Well, I know most of them. You can buy " +
        "some from me because I have many in stock. If you have " +
        "an unknown potion, I can try to identify it for you as " +
        "long as you give it to me. If you want to learn about " +
        "potion lore, ask me about it.");
    return "";
}



string
ask_lore()
{
    command("say Potion lore? Well, there are only a few who know " +
        "as much about then as I do. They are brewed by many skilled " +
        "alchemists and often used to extend the alchemists' magic.");
    return "";
}

string
default_answer()
{
    command("say I don't know what you are talking about!");
    return "";
}

void 
alchemist_no_potions_to_sell_hook(int intPotion)
{
    if (intPotion)
    {
        command("hmm");
        command("say This is useless to me");
        command("say I only want to buy potions from you.");

    }
    else
    {
        command("say I am sorry, I do not buy potions brewed in the Temple.");
        command("say If you want others to use them, feel free to leave " +
            "them in the cupboard.");
	}
}

/*
 * Function name : potion_filter
 * Arguments     : object ob: Some object
 * Description   : Filters non-potion objects from an array.
 * Returns       : 1 if a potion / 0 if not / 2 is NoV potion
 */
int potion_filter(object ob)
{
    if (!function_exists("create_potion",ob)) 
	    return 0;

// this alchemist does not buy NOV potions
    if (ob->query_prop(IS_NOV_POTION))
	    return 0;

    if (!ob->query_potion_name() || !ob->query_potion_value()) 
	    return 0;

    if (ob->query_prop(OBJ_M_NO_SELL))
	    return 0;

    return 1;
}
