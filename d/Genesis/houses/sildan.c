/*
 * Sildan - Real Estate Agent
 *
 * Handles the buying and selling of houses
 *
 * Varian - July, 2021
 */

inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/lib/trade";

#include <composite.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include <const.h>
#include <language.h>
#include "/d/Gondor/met_defs.h"
#include "defs.h"

#define TO        this_object()
#define TP        this_player()
#define ENV(obj)  environment(obj)

void
create_monster()
{

    set_name(({"sildan", "_real_estate_agent", "agent"}));
    set_living_name("sildan");
    set_title("Legendary Agent of the Sparkle Real Estate Office");
    set_adj("slender");
    add_adj("beautiful");
    set_race_name("elf");
    set_long("This beautiful looking elf is the real estate " +
        "agent of Genesis. If you want to buy property in " +
        "Genesis, you will have to deal with her!\n");
    set_gender(G_FEMALE);

    set_base_stat(SS_STR, 50);
    set_base_stat(SS_DEX, 120);
    set_base_stat(SS_CON, 50);
    set_base_stat(SS_INT, 250);
    set_base_stat(SS_WIS, 250);
    set_base_stat(SS_DIS, 100);
    set_skill(SS_TRADING, 100);
    set_alignment(0);
    config_default_trade();

    add_ask( ({"help"}), VBFC_ME("ask_help") );
    add_ask( ({"task", "tasks", "quest", "quests"}), VBFC_ME("ask_task") );
    add_ask( ({"house", "houses", "home", "homes", "property",
            "properties", "land", "realty", "donut"}), VBFC_ME("ask_house") );
    add_ask( ({"buy", "purchase"}), VBFC_ME("ask_buy") );
    add_ask( ({"key", "keys", "ownership", "deed"}), VBFC_ME("ask_buy") );
    add_ask( ({"tax", "taxes", "wizards", "immortals"}), VBFC_ME("ask_tax") );
    add_ask( ({"cost", "price", "prices"}), VBFC_ME("ask_price") );
    add_ask( ({"auction", "auctions", "sell"}), VBFC_ME("ask_auction") );
    add_ask( ({"listing", "listings", "list", "poster",
        "posters"}), VBFC_ME("ask_list") );
    add_ask( ({"fee", "fees"}), VBFC_ME("ask_fee") );

    set_default_answer(VBFC_ME("default_answer"));

    set_act_time(25);

    add_act("emote scribbles some down some notes.");
    add_act("emote tidies up her desk.");
    add_act("emote yawns and stretches her back.");
    add_act("emote makes some notes about the last listing she sold.");
    add_act("emote works out the taxes due on Genesis housing.");

    set_chat_time(20);
    
    add_chat("These taxes are a nightmare!");
    add_chat("I sell homes, not houses!");
    add_chat("I love the look on a customers face when I hand them over " +
        "their keys for the first time!");
    add_chat("Do you want to purchase a house? I have reasonable fees!");
    add_chat("House prices keep on rising! That's great for me!");
    add_chat("I wonder when we will get more listings.");
    
    // Sildan receives the deed to trade ownership of the house.
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

}

string
ask_help()
{
    command("say I would love to help you out! This is the Sparkle Real " +
        "Estate Office, and we sell homes here. You can ask me about " +
        "houses and how to purchase them, in addition to a couple of " +
        "other things like fees or taxes!");
    return "";
}

string
ask_task()
{
    command("say I am far too busy selling real estate to worry about " +
        "handing out any quests!");
    command("smile bright");
    command("say Would you like to buy a house?");
    return "";
}

string
ask_house()
{
    command("say I sell houses in Genesis, that's my job! All of the " +
        "available homes across Genesis are listed here in the Sparkle " +
        "Real Estate Office!");
    return "";
}

string
ask_buy()
{
    command("say If there is a house available for immediate purchase, " +
        "then just let me know which listing you are interested in. " +
        "Otherwise, you may have to wait for an auction. Once you are " +
        "the proud owner of a house, you will be given your keys and " +
        "you can move in immediately!");
    return "";
}

string
ask_key()
{
    command("say The keys are the symbol of ownership to your home. " +
        "If you ever lose them, come back to the Sparkle Real Estate " +
        "Agency and I will return any missing keys back into your inventory!");
    return "";
}

string
ask_tax()
{
    command("say Well, those greedy immortals do expect all of us land " +
        "owners to pay taxes!");
    command("frown angrily");
    command("say But what can mere mortals like us do. They have a " +
        "set weekly tax rate for each house. You can find it on the " +
        "listing.");
    command("shrug");
    command("say All we can do is pay it, or else they will take the " +
        "house away and ask me to sell it to someone else who will " +
        "pay!");
    command("say Fortunately, you don't have to do much. They pay " +
        "the Gnomes of Genesis to take it right out of your bank " +
        "account.");
    return "";
}

string
ask_price()
{
    command("say The prices are printed right on the listing, unless " +
        "it goes to auction of course.");
    return "";
}

string
ask_auction()
{
    command("say If you already own a property and wish to sell it, " +
        "I can auction it for you.  Simply 'auction' your property, " +
        "and I will take care of the rest.  I will deduct my fee, of " +
        "course.");
    return "";
}

string
ask_list()
{
    command("say Any current listings will be put on the posters " +
        "in this room. Feel free to drop by any time and take a " +
        "look!");
    return "";
}

string
ask_fee()
{
    command("say Well, of course I charge a small fee for all " +
        "of the work I do here! But it's not much, only ten " +
        "percent. I wanted twenty, but the immortals told me " +
        "that was too much.");
    return "";
}

public string
default_answer()
{
   string  answer = one_of_list( ({
        "I'm too busy to talk about that right now.",
        "Oh, I hadn't really thought about that.",
        "If you want to ask me something, stick to business."}) );
    command("emote pauses for a moment.");
    command("say " + answer);
    return "";
}

public void
attacked_by(object attacker)
{
    this_object()->command("scream");
    this_object()->command("emote tries to defend herself!");
    attacker->stop_fight(this_object());
    this_object()->stop_fight(attacker);
}

void
add_introduced(string str)
{
    if (!interactive(this_player()) || this_player()->query_met(query_name()))
        return;

    command("introduce me to " + this_player()->query_real_name() + "");
}


/*
 * Function name: return_item
 * Description  : Give the player his money/purchased item
 */
void
return_item(object obj,string target)
{
    if (!objectp(obj))
        return;

    if (environment(obj)!=TO)
        return;

    command("say I'm not sure why you gave that to me.");

    string ob_name = OB_NAME(obj);

    if (obj->query_prop(HEAP_I_IS))
        ob_name = obj->query_pname();

    command("give " + ob_name + " to " + target);

    if (environment(obj) == TO)
    {
        command("shrug");
        command("drop " + ob_name);
    }

    if (environment(obj) == TO)
    {
        command("emote drops the "+ obj->short() + ".");
        obj->move(environment(TO),1);
    }
}

void check_keys()
{
    string* house_ids = HOUSE_MANAGER->get_all_house_ids();
    if (!sizeof(house_ids))
    {
        return;
    }
    foreach (string id : house_ids)
    {
        mapping details = HOUSE_MANAGER->get_house_details(id);
        string owner = details[KEY_OWNER];
        object player = find_player(owner);
        if (!objectp(player) || ENV(player) != ENV(TO))
        {
            continue;
        }

        if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, player))
        {
            continue;
        }
        string key_path = details[KEY_KEYPATH];
        int found_key = 0;
        foreach (object item : all_inventory(player))
        {
            if (MASTER_OB(item) == key_path)
            {
                found_key = 1;
                break;
            }
        }
        if (!found_key)
        {
            command("say " + capitalize(player->query_real_name()) + ", I " +
            "have a key for your home for you.");
            object key = clone_object(key_path);
            key->move(player, 1);
            tell_room(ENV(TO),  QCTNAME(TO) + " gives " + LANG_ASHORT(key)
               + " to " + QCTNAME(player) + ".\n", ({ player }));
            player->catch_tell(TO->query_The_name(player) + 
              " gives " + LANG_ASHORT(key) + " to you.\n");
            
            set_alarm(5.0, 0.0, check_keys);
            return;
        }
    }
}

void
enter_inv(object ob, object old)
{
    ::enter_inv(ob,old);

    if (!objectp(old) || !interactive(old))
        return;

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO,old))
    {
        set_alarm(0.1,0.0,&return_item(ob,old->query_real_name()));
        return;
    }
    if (!ob->is_valid_house_deed())
    {
        set_alarm(0.1,0.0,&return_item(ob,old->query_real_name()));
        return;
    }
    HOUSE_MANAGER->set_house_owner(ob->query_house_name(),
                                   old->query_real_name(),
                                   ob->query_auction_price());
    HOUSE_MANAGER->deed_removed(ob->query_house_name());                                   
    command("say Ahh, you have made a fine choice!");
    command("say The house is now officially yours.");
    ob->remove_object();
    set_alarm(0.1, 0.0, check_keys);
}

int request_auction(string str)
{
    string original_str = str;
    
    notify_fail("Auction what?\n");
    
    if (!str)
        return 0;
    
    str = lower_case(str);
    
    mapping house = 0;
    string house_name = 0;
    if (str == "house" || str == "property")
    {
        //Try to look up an owned house for the player.
        foreach (string id : HOUSE_MANAGER->get_all_house_ids())
        {
            mapping details = HOUSE_MANAGER->get_house_details(id);
            if (details[KEY_OWNER] == TP->query_real_name())
            {
                if (house)
                {
                    command("say You lucky devil, you own more than one " +
                        "house. Which one do you want to auction?");
                    return 1;
                }
                house = details;
                house_name = id;
            }
        }
    }
    else
    {
        //Try to look up an owned house for the player.
        foreach (string id : HOUSE_MANAGER->get_all_house_ids())
        {
            mapping details = HOUSE_MANAGER->get_house_details(id);
            if (details[KEY_OWNER] == TP->query_real_name() &&
                lower_case(details[KEY_SHORT]) == str)
            {
                house = details;
                house_name = id;
                break;
            }
        }
    }
    if (!house)
    {
        string* sellable_houses = ({});
        command("say I don't know which property you are trying to auction.");
        foreach (string id : HOUSE_MANAGER->get_all_house_ids())
        {
            mapping details = HOUSE_MANAGER->get_house_details(id);
            if (details[KEY_OWNER] == TP->query_real_name())
            {
                sellable_houses += ({ details[KEY_SHORT] });
            }
        }
        if (sizeof(sellable_houses))
        {
            command("say You currently own " + COMPOSITE_WORDS(sellable_houses) +
            ".");
        }
        return 1;
    }
    int is_final = query_verb() == "auction!" ? 1 : 0;
    if (!is_final)
    {
        command("say When you auction the property, I will immediately take " +
            "possession of it so I can sell it. You will no longer be able " +
            "to access it.");
        command("say The auction will begin immediately, and last for two " +
            "weeks. If it sells, I will pay you the sale amount, minus my " +
            "fee.");
        command("say If it does not sell, I will pay you " +
            house[KEY_PRICE] + " platinum, minus my fee, and will keep " +
            "possession of the house, for a future auction. If you want to " +
            "get the house back, you will need to bid on it.");
        command("say Your action cannot be undone. If you are certain you " +
            "want to sell, you can 'auction! " + original_str + "' to start.");
        return 1;
    }
    command("say I look forward to helping you sell the home!");
    // Need to - remove key, change ownership to sildan, create auction.
    // Ideally we should remove teleport destinations from the player as well.
    HOUSE_MANAGER->set_house_owner(house_name, "admin", house[KEY_PRICE]);
    foreach (object item : all_inventory(TP))
    {
        if (MASTER_OB(item) == house[KEY_KEYPATH])
        {
            command("emote takes the key.");
            item->remove_object();
        }
    }
    if (!HOUSE_MANAGER->auction_house(house_name, TP->query_real_name()))
    {
        command("say Hmm, I may need to talk with my manager first.");
    }
    return 1;
    
}


public void
init_living()
{
    ::init_living();
    add_action(request_auction, "auction");
    add_action(request_auction, "auction!");
    set_alarm(0.5, 0.0, check_keys);
}
