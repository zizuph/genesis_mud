/*
 * Alchemist of NoV
 * Based on Daisy from the Shire
 * -- Finwe, July 2007
 */

#pragma strict_types
#pragma save_binary

#include "/d/Faerun/defs.h"

inherit "/sys/global/money";
inherit "/std/monster";
inherit "/d/Faerun/lib/alchemist.c";

#define POTION_SAVE     "/d/Faerun/guilds/nov/npcs/potion_save"
#define NOBJ_DIR         "/d/Faerun/guilds/nov/obj/"
#define VIALS   ({"vial_bat", "vial_bell", "vial_bhead", "vial_demon", "vial_gskull", "vial_lbolt", "vial_spider"})
#define   IS_NOV_POTION         "_i_is necro_potion"

void
create_monster() 
{
    int i;

    add_name("alchemist");
    set_gender(G_FEMALE);
    set_race_name("human");
    set_long("This is a dark-skinned and wrinkled woman. Her eyes are red and her dirty hair is tied back over her shoulders. Her skill in alchemy is revered by those who know her.\n");
    set_adj(({"dark-skinned","wrinkled"}));
    remove_prop(LIVE_I_NEVERKNOWN);

    set_skill(SS_ALCHEMY, 75);

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
    add_ask(({"mortar", "bowl", "stone bowl", "black bowl", "black stone bowl"}), VBFC_ME("ask_mortar"));

    set_max_potions_kept(250);
    configure_alchemist(POTION_SAVE);
    set_alchemist_id_potions();

}

void
init_living()
{
    init_alchemist();
//    add_action("get_bowl", "request");
    ::init_living();
    add_action("buy_stuff", "pay");

}

void
enter_inv(object potion, object from)
{
    ::enter_inv(potion, from);
    init_alchemist_identify(potion,from);
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
    command("say Potions? I have studied alchemy for many years and know about them. They are useful in many situations, both to protect yourself and hurt enemies. You can buy some from me because I have many in stock, or I will buy them from you. However, I do not buy potions made here in the Temple. Any skilled Necromancer can brew them.");
    return "";
}

string ask_mortar()
{
    command("say Potions are a valuable part of any Necromancer. There are times when you probably need to brew one and won't have time to return here to do that. You can <request bowl> of me and I shall lend you one to take with you. This will free you from having to travel here when you need potions.");
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
        command("say I only deal in potions.");

    }
    else
    {
        command("say I am sorry, I do not buy potions brewed by the Necromancers of Valsharoon.");
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
	    return 1;

    if (!ob->query_potion_name() || !ob->query_potion_value()) 
	    return 0;

    if (ob->query_prop(OBJ_M_NO_SELL))
	    return 0;

    return 1;
}

int
buy_stuff(string str) 
{
    object ob;
    int price;
    string order, name, vial;

    switch(str)
    {
        case "for bowl":
        case "for black stone bowl":
        case "for stone bowl":
        case "for black bowl":
        case "for mortar":
            order = NOBJ_DIR + "bowl";
            price = 1296;
            name = "black stone bowl";
            break;
        case "for bat vial":
            order = NOBJ_DIR + "vial_bat";
            price = 72;
            name = "empty bat vial";
            break;
        case "for bell vial":
            order = NOBJ_DIR + "vial_bell";
            price = 72;
            name = "empty bell vial";
            break;
        case "for bloody-head vial":
            order = NOBJ_DIR + "vial_bhead";
            price = 72;
            name = "empty bloody-head vial";
            break;
        case "for demon-face vial":
            order = NOBJ_DIR + "vial_demon";
            price = 72;
            name = "empty demon-face vial";
            break;
        case "for lightning-bolt vial":
            order = NOBJ_DIR + "vial_lbolt";
            price = 72;
            name = "empty lightning-bolt vial";
            break;
        case "for skull vial":
            order = NOBJ_DIR + "vial_skull";
            price = 72;
            name = "empty skull vial";
            break;
        case "for spider vial":
            order = NOBJ_DIR + "vial_spider";
            price = 72;
            name = "empty spider vial";
            break;
        default:
            TO->command("say Pay for what?");
            return 1;
            break;
            
    }

    if (!take_money(TP,price)) 
    {
        TO->command("say You don't have enough money to buy the " + name + ".");
        return 1;
    }
    else 
    {
        ob=clone_object(order);
        if (ob->move(TP)!=0)
        {
            TO->command("say It seems you cannot carry the " + name + ". I will drop it on the floor for you.");
            ob->move(ENV(TP));
        }
        else 
        {
            TP->catch_msg("You pay " + price + " copper coins and get the " + 
                name + ".\n");
        }
        return 1;
    }
}
