/* house_manager.c created by Zizuph
 * 
 * Modified from data_manager for houses, where all are loaded
 * at any time.
 * 
 * Some routines for persistent data storage, particularly suited for
 * storing player data.
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow

inherit "/std/room";

#include "./defs.h"

#include <composite.h>
#include <files.h>
#include <macros.h>
#include <money.h>

#define TP this_player()

#define FEE_PERCENT 10


// House long intervals is for testing only.
//#define TAX_INTERVAL (60 * 60)
#define TAX_INTERVAL (7 * 24 * 60 * 60)

// The auction will last two weeks.
#define AUCTION_HOURS (14 * 24)
// Short auction intervals for testing only.
//#define AUCTION_HOURS (1)

#define AUCTION_HOUSE "/d/Sparkle/area/city/auction/room/auction_house"


public mapping known_rooms = ([]);

public mapping data_map = 0;

public void collect_taxes();

public string query_house_detail_filename()
{
    return HOUSE_PATH + "house_details";
}

public void load_details() {
    if (!mappingp(data_map))
    {
        data_map = restore_map(query_house_detail_filename());
    }
}

public void save_details()
{
    if (!mappingp(data_map))
    {
        save_map(([ ]), query_house_detail_filename());
    }
    else
    {
        save_map(data_map, query_house_detail_filename());
    }
}

public mapping get_house_details(string house_name)
{
    if (member_array(house_name, m_indexes(data_map)) == -1)
    {
        return 0;
    }
	return data_map[house_name];
}

public void load()
{
    load_details();
}

public void save()
{
    save_details();
    find_object(DISPLAY_ROOM)->update_listings();
}

public int is_admin()
{
     if (member_array(
        this_interactive()->query_real_name(), ADMIN) == -1)
    {
        return 0;
    }
    return 1;
}

public void register_room(string house_name, string path)
{
    if (member_array(house_name, m_indexes(known_rooms)) == -1)
    {
        known_rooms[house_name] = ({ path });
    }
    else
    {   
        known_rooms[house_name] += ({ path });
    }
}

public void get_registered_rooms(string house_name)
{
    if (member_array(house_name, m_indexes(known_rooms)) == -1)
    {
        return 0;
    }
	return known_rooms[house_name];
}

public int add_invitee(string house_name, string player_name)
{
    mapping details = get_house_details(house_name);
    if (mappingp(details)) {
        if (!sizeof(details[KEY_INVITED]))
        {
            details[KEY_INVITED] = ({});
        }
        if (member_array(player_name, details[KEY_INVITED]) != -1)
        {
            return 0;
        }
        details[KEY_INVITED] += ({ player_name });
        save();
        return 1;
    }
    return 0;
}

public int remove_invitee(string house_name, string player_name)
{
    mapping details = get_house_details(house_name);
    if (mappingp(details)) {
        if (!sizeof(details[KEY_INVITED]))
        {
            return 0;
        }
        if (member_array(player_name, details[KEY_INVITED]) != -1)
        {
            details[KEY_INVITED] -= ({ player_name });
            save();
            return 1;
        }
    }
    return 0;
}

public string mylong()
{
    if (!this_player()->query_wiz_level())
	return "This is the house management room.  You should not be here.\n";
    
    return "This is the house management room.\n"
      + "Available commands: \n"
      + "  list - List all houses\n"
      + "  list <name> - Show all details for a house.\n"
      + (is_admin() ?
        "  create house <name> - Create a new house.\n"
      + "  edit <name> set complete (0|1) - Enable listing.\n"
      + "  edit <name> set for sale (0|1) - Allow listing to be sold.\n"
      + "  edit <name> set price <amount> - Set sale price in platinum.\n"
      + "  edit <name> set short <text> - Set listing short.\n"
      + "  edit <name> set long <text> - Set listing long.\n"
      + "  edit <name> set owner <name> - Name of owner (or admin).\n"
      + "  edit <name> set keypath <path> - Path to door key.\n"
      + "  edit <name> set taxes <amount> - Amount of weekly taxes.\n"
      + "  edit <name> add room <path> <desc> - Add a room to listing.\n"
      + "  edit <name> remove room <path> - Remove a room from listing.\n"
      + "  create deed <name> - Create a deed for the house for auction.\n"
      + "  remove <name> - Delete a house.\n"  
      + "  transfer <name> to <player> - Perform a full house sale.\n"
      + "      NOTE: This will affect the buyers and sellers bank accounts.\n"
      : "")      
      + " Allowed admin: " + COMPOSITE_WORDS(ADMIN) + "\n";
}

public void create_room()
{
    setuid();
    seteuid(getuid());
    
    set_name("datastore");
    set_short("Datastore for House Management");
    set_long("@@mylong@@");

    add_exit("/d/Genesis/houses/office", "west");


    load();
    
    // We want to know when auctions are complete.
    AUCTION_HOUSE->add_auction_event_listener(this_object());
    
    set_alarm(3600.0, 3600.0, collect_taxes);

}

static void 
manager_log(string text)
{

    setuid();
    seteuid(getuid());
    write_file(HOUSE_LOG_PATH + "manager_log", 
        ctime(time()) + " " + text + "\n");
}

public void 
ejection_log(string player, string room)
{

    setuid();
    seteuid(getuid());
    write_file(HOUSE_LOG_PATH + "ejection_log", 
        ctime(time()) + " " +
        sprintf("%s was ejected from %s.\n",
        player, room));
}

static void
transaction_log(string text)
{

    setuid();
    seteuid(getuid());
    write_file(HOUSE_LOG_PATH + "transaction_log", 
        ctime(time()) + " " + text + "\n");
}

public string sanitize_house_name(string text)
{
   return implode(explode(text, " "), "");
}


public void deed_created(string house_name)
{
    mapping details = get_house_details(house_name);
    if (mappingp(details)) {
        details[KEY_DEED_COUNT] = details[KEY_DEED_COUNT] + 1;
        save();
        manager_log(this_player()->query_real_name() +
            " created a deed for " + house_name + "\n");
    }
}

public void deed_removed(string house_name)
{
    mapping details = get_house_details(house_name);
    if (mappingp(details)) {
        details[KEY_DEED_COUNT] = details[KEY_DEED_COUNT] - 1;
        save();
        manager_log("Deed for " + house_name + " removed from game.\n");
    }
}

public int completed(mapping details)
{
    return details[KEY_COMPLETE] == 1;
}

public int house_exists(string key)
{
    return mappingp(data_map[key]);
}

public string get_owner_name(mapping details)
{
    return details[KEY_OWNER] == "admin" ? 
            "Sparkle Housing" : capitalize(details[KEY_OWNER]);
}

public string house_long(string key)
{
    if (!house_exists(key))
    {
        return "No such house.\n";
    }
    mapping details = data_map[key];
    string result = "House: " + key + " " + (completed(details) ? "(available)" : "(incomplete)") + "\n";
    if (stringp(details[KEY_SHORT]))
    {
        result += "  " + details[KEY_SHORT] + "\n";
    }        
    else
    {
        result += "  No Short Description\n";
    }
    if (stringp(details[KEY_LONG]))
    {
        result += "  " + details[KEY_LONG] + "\n";
    }        
    else
    {
        result += "  No Long Description\n";
    }
    if (stringp(details[KEY_OWNER]))
    {
        result += "  Owner: " + get_owner_name(details) + "\n";
    }
    else
    {
        result += "  No Owner\n";
    }
    if (stringp(details[KEY_KEYPATH]))
    {
        result += "  Path to key for door: " + details[KEY_KEYPATH] + "\n";
    }
    if (intp(details[KEY_PRICE]))
    {
        result += "  Sale Price: " + details[KEY_PRICE] + 
        (details[KEY_FORSALE] ? " (for sale)" : "") + "\n";
    }
    else
    {
        result += "  No Price Set\n";
    }
    if (intp(details[KEY_WEEKLY_TAX]))
    {
        result += "  Weekly Tax: " + details[KEY_WEEKLY_TAX] + "\n";
    }
    if (mappingp(details[KEY_ROOMS]))
    {
        result += "  Listed rooms:\n";
        foreach (string path, string description: details[KEY_ROOMS])
        {
          result += "    " + path + ": " + description + "\n";
        }
    }
    else
    {
        result += "  No rooms listed\n";
    }
    return result;
}

public string house_short(string key)
{
    if (!house_exists(key))
    {
        return "No such house.\n";
    }
    mapping details = data_map[key];
    return key + ": " + (strlen(details[KEY_SHORT]) ? 
        details[KEY_SHORT] : "(No short description) ") + 
        (details[KEY_PRICE] ? " " + details[KEY_PRICE] + " platinum" : "")
        + (details[KEY_FORSALE] ? ", for sale," : "")
        + (completed(details) ? " (complete)" : " (incomplete)") + "\n";
}


public void set_house_owner(string house_name, string new_owner, int price)
{
    transaction_log(
        sprintf("Ownership of %s has changed to %s for a price of %d",
        house_name, capitalize(new_owner), price));
    data_map[house_name][KEY_FORSALE] = 0;
    data_map[house_name][KEY_OWNER] = new_owner;
    data_map[house_name][KEY_INVITED] = ({});
    data_map[house_name][KEY_LAST_TAX_PAID_TIME] = time();
    if (!sizeof(data_map[house_name][KEY_PRIORSALE]))
    {
        data_map[house_name][KEY_PRIORSALE] = ({});
    }
    if (sizeof(data_map[house_name][KEY_PRIORSALE]) > 50)
    {
        data_map[house_name][KEY_PRIORSALE] = 
          data_map[house_name][KEY_PRIORSALE][-50 .. -1];
    }
    data_map[house_name][KEY_PRIORSALE] += ({ ({price, new_owner, time()}) });
    save();
}

public string* get_all_house_ids()
{
    return m_indexes(data_map);
}

/*
 *  Transfer house from current owner to new owner.
 *  Payments will be taking directly from bank accounts
 *  Returns: 0 if transaction is successful
 *           string error message if transaction failed
 *
 */
public string transfer_house(string house_name, string new_owner)
{
    if (!house_exists(house_name))
    {
        return "No such house.\n";
    }
    mapping details = data_map[house_name];
    if (!details[KEY_FORSALE])
    {
        return "That house is not for sale.\n";
    }
    if (!details[KEY_COMPLETE])
    {
        return "That house is not available.\n";
    }
    if (details[KEY_OWNER] == new_owner)
    {
        return "That house is already owned by that person.\n";
    }
    int price = details[KEY_PRICE];
    if (new_owner != "admin")
    {
        if (!GOG_ACCOUNTS->load_account(new_owner))
        {
            return "There is no bank account to pay for the house.\n";
        }
        int* coins = GOG_ACCOUNTS->query_account_coins(new_owner);

        if (coins[MONEY_PC_INDEX] < price)
        {
            return "You need " + (price - coins[MONEY_PC_INDEX])
               + " more platinum in the bank for this purchase.\n";
        }
        GOG_ACCOUNTS->remove_money(new_owner, MONEY_PC_INDEX, price);
        transaction_log(sprintf("%s paid %d platinum for house %s",
                             capitalize(new_owner), price, house_name));
    }
    else
    {
        transaction_log(sprintf("Admin paid 0 for house %s",
                             house_name));
    }
    
    if (details[KEY_OWNER] != "admin")
    {
        int recv_price = price * (100 - FEE_PERCENT) / 100;
        GOG_ACCOUNTS->add_money(details[KEY_OWNER],
            MONEY_PC_INDEX, recv_price);
        transaction_log(sprintf("%s received %d platinum for house %s",
                    capitalize(details[KEY_OWNER]), recv_price, house_name));
    }
    else
    {
        transaction_log(sprintf("Admin received 0 for house %s",
                             house_name));
    }
    set_house_owner(house_name, new_owner, price);
    return 0;
    
}

public int do_transfer(string text)
{
    notify_fail("Transfer which property to which owner?");
    string house_name, new_owner;
    if (!strlen(text)) {
        return 0;
    }
    if (!sscanf(text, "%s to %s", house_name, new_owner))
    {
        return 0;
    }
    string result = transfer_house(house_name, new_owner);
    if (strlen(result))
    {
        write(result);
        return 1;
    }
    write("House " + house_name + " has been transferred to " +
        get_owner_name(data_map[house_name]) + ".\n");
    manager_log(this_player()->query_real_name() +
            " forced a transfer of " + house_name + 
            " to " + new_owner + "\n");
    return 1;
}


/* Put the house up for auction.  The recipient will
 * receive payment by the house manager upon sale.  Note
 * that the seller in the auction will be "Sildan", the NPC.
 * Returns: 1 if the auction was created, 0 if not.
 */

public int auction_house(string house_name, string recipient)
{

    mapping details = get_house_details(house_name);
    if (!details)
    {
        return 0;
    }

    object deed = clone_object(HOUSE_DEED);
    deed->set_house_name(house_name);
    deed_created(house_name);


    mapping auction = AUCTION_HOUSE->create_auction(deed,
      details[KEY_PRICE] /* starting price */, 
      0 /* no maximum */, 1 /* public */, AUCTION_HOURS, "sildan",
      details[KEY_PRICE] /* deposit of starting price */);

    transaction_log(sprintf("%s offered up for auction at price of %d, ID %d",
        house_name, details[KEY_PRICE], auction["id"]));

    if (recipient)
    {
        details[KEY_AUCTION_ID] = auction["id"];
        details[KEY_AUCTION_RECIPIENT] = recipient;
        save();
        transaction_log(sprintf("%s was set as the auction recipient",
            recipient));
    }
    return 1;
}

public int
create_house(string text)
{
    notify_fail("Usage: create house <name> or create deed <name>.\n");
    if (!is_admin())
    {
        return 0;
    }
    if (!strlen(text))
        return 0;
    string house_name = 0;

    if (sscanf(text, "house %s", house_name) == 1) {
        string key = sanitize_house_name(house_name);
        if (key != house_name)
        {
            write("House names should not have any spaces.\n");
            return 1;
        }
        if (mappingp(data_map[key]))
        {
            write("The house name " + key + " already exists.\n");
            return 1;
        }
        data_map[key] = ([ ]);
        save();
        write("House " + key + " has been created.\n");
        manager_log(this_player()->query_real_name() +
            " created house " + key + "\n");
        return 1;
    }
    if (sscanf(text, "deed %s", house_name) == 1) {
        mapping house = get_house_details(house_name);
        if (!mappingp(house))
        {
            write("House " + house_name + " does not exist.\n");
            return 1;
        }
        if (house[KEY_COMPLETE] != 1)
        {
            write("House " + house_name + " is not yet complete.\n");
            return 1;
        }
        if (house[KEY_DEED_COUNT] > 0)
        {
            write("There is already an outstanding deed for " + house_name + ".\n");
            write("If the deed was actually destroyed, \"Call here deed_removed " +
              house_name + "\".\n");
            return 1;
        }
        object deed = clone_object(HOUSE_DEED);
        deed->set_house_name(house_name);
        deed->move(TP, 1);
        write("Deed for house " + house_name + " moved to inventory.\n");
        write("The possessor of this deed can give it to Sildan to " +
            "transfer, cost free, ownership of the house to themselves.\n");
        write("An auction for this deed can be created in the auction data" +
            "store: /d/Sparkle/area/city/auction/obj/auction_data_store.\n");
        deed_created(house_name);
        return 1;
        
    }
    return 0;
}

public int
list_house(string text)
{   
    int num_houses = 0; 
    if (!strlen(text))
    {
        write("All registered houses:\n");
        foreach (string key, mapping details: data_map)
        {
            write("  " + house_short(key));
            num_houses ++;
        }
        write("Number of houses: " + num_houses + ".\n");
        return 1;
    }

    write(house_long(text));
    return 1;
}

public int remove_house(string text)
{
    notify_fail("Usage: remove house <name>.\n");
    if (!is_admin())
    {
        return 0;
    }
    if (!strlen(text))
        return 0;
    string house_name = 0;

    if (sscanf(text, "house %s", house_name) == 1) {
        string key = sanitize_house_name(house_name);
        if (key != house_name)
        {
            write("House names should not have any spaces.\n");
            return 1;
        }
        if (!mappingp(data_map[key]))
        {
            write("The house name " + key + " does not exist.\n");
            return 1;
        }
        m_delkey(data_map, key);
        save();
        write("House " + key + " has been deleted.\n");
        manager_log(this_player()->query_real_name() +
            " deleted the house " + key + "\n");
        return 1;
    }
    return 0;
}

public int edit_house(string text)
{
    notify_fail("Edit which house?\n");
    if (!is_admin())
    {
        return 0;
    }
    if (!strlen(text))
        return 0;
    string key, subcommand;
    if (!sscanf(text, "%s %s", key, subcommand))
    {
        return 0;
    }
    if (!house_exists(key))
    {
        write("That house does not exist.\n");
        return 1;
    }
    string short_desc;
    if (sscanf(subcommand, "set short %s", short_desc))
    {
        data_map[key][KEY_SHORT] = short_desc;
        write("House updated with short description: " + short_desc + "\n");
        manager_log(this_player()->query_real_name() +
            " updated the short for " + key + "\n");
        save();
        return 1;
    }
    int price;
    if (sscanf(subcommand, "set price %d", price))
    {
        data_map[key][KEY_PRICE] = price;
        write("House updated with price: " + price + " platinum.\n");
        save();
        manager_log(this_player()->query_real_name() +
            " updated the price for " + key + "\n");
        return 1;
    }
    int taxes;
    if (sscanf(subcommand, "set taxes %d", taxes))
    {
        data_map[key][KEY_WEEKLY_TAX] = taxes;
        write("House updated with taxes: " + taxes + " platinum.\n");
        save();
        manager_log(this_player()->query_real_name() +
            " updated the taxes for " + key + "\n");
        return 1;
    }
    int forsale;
    if (sscanf(subcommand, "set for sale %d", forsale))
    {
        if (forsale && !data_map[key][KEY_PRICE])
        {
            write("Cannot set for sale, there is no price.\n");
            return 1;
        }
        data_map[key][KEY_FORSALE] = forsale;
        write("House updated with forsale: " + forsale + ".\n");
        save();
        manager_log(this_player()->query_real_name() +
            " updated the forsale for " + key + "\n");
        return 1;
    }
    string long_desc;
    if (sscanf(subcommand, "set long %s", long_desc))
    {
        data_map[key][KEY_LONG] = long_desc;
        write("House updated with long description: \n" + long_desc + "\n");
        save();
        manager_log(this_player()->query_real_name() +
            " updated the long for " + key + "\n");
        return 1;
    }
    string key_path;
    if (sscanf(subcommand, "set keypath %s", key_path))
    {
        data_map[key][KEY_KEYPATH] = key_path;
        object key_obj = find_object(key_path);
        if (!objectp(key_obj))
            {
                key_path->teleledningsanka();
                key_obj = find_object(key_path);
            }
        if (!objectp(key_obj))
        {
            write("File path " + key_path + " does not exist.\n");
            return 1;
        }
        write("House updated with key file: \n" + key_path + "\n");
        save();
        manager_log(this_player()->query_real_name() +
            " updated the keypath for " + key + "\n");
        return 1;
    }
    string owner;
    if (sscanf(subcommand, "set owner %s", owner))
    {
        data_map[key][KEY_OWNER] = owner;
        data_map[key][KEY_LAST_TAX_PAID_TIME] = time();
        write("House updated with owner: " + get_owner_name(data_map[key]) + "\n");
        save();
        manager_log(this_player()->query_real_name() +
            " updated the owner for " + key + " to " + owner + "\n");
        return 1;
    }
    string room_path, room_desc;
    if (sscanf(subcommand, "add room %s %s", room_path, room_desc))
    {
        object room = find_object(room_path);
        if (!objectp(room))
            {
                room_path->teleledningsanka();
                room = find_object(room_path);
            }
        if (!objectp(room))
        {
            write("File path " + room_path + " does not exist.\n");
            return 1;
        }
        if (!IS_ROOM_OBJECT(room))
        {
            write("File path " + room_path + " is not a room.\n");
            return 1;
        }
        if (!mappingp(data_map[key][KEY_ROOMS]))
            data_map[key][KEY_ROOMS] = ([ ]);
        
        foreach (string desc : m_values(data_map[key][KEY_ROOMS]))
        {
           if (desc == room_desc)
           {
               write("That description already exists for the listing.\n");
               return 1;
           }
        }           
        data_map[key][KEY_ROOMS][room_path] = room_desc;
        write("Room " + room_path + " added to " + key + " with description "
         + room_desc + ".\n");
        save();
        manager_log(this_player()->query_real_name() +
            " added a room for " + key + "\n");
        return 1;
    }
    if (sscanf(subcommand, "remove room %s", room_path))
    {
        if (!stringp(data_map[key][KEY_ROOMS][room_path]))
        {
            write("House does not have a room with path " + room_path + ".\n");
            return 1;
        }
        m_delkey(data_map[key][KEY_ROOMS], room_path);
        write("Removed room " + room_path + " from house " + key + ".\n");
        save();
        manager_log(this_player()->query_real_name() +
            " removed a room for " + key + "\n");
        return 1;
    }
    
    int complete;
    if (sscanf(subcommand, "set complete %d", complete))
    {
        // These are the validation checks to make sure everything is set.
        if (complete) {
          if (!stringp(data_map[key][KEY_SHORT]))
           {
              write("House is missing a short, cannot mark as available.\n");
              return 1;
          }
          if (!stringp(data_map[key][KEY_LONG]))
          {
              write("House is missing a long, cannot mark as available.\n");
              return 1;
          }
          if (!stringp(data_map[key][KEY_OWNER]))
          {
              write("House is missing an owner, cannot mark as available.\n");
              return 1;
          }
          if (!intp(data_map[key][KEY_PRICE]))
          {
              write("House is missing a price, cannot mark as available.\n");
              return 1;
          }
          if (!intp(data_map[key][KEY_WEEKLY_TAX]))
          {
              write("House is missing a tax, cannot mark as available.\n");
              return 1;
          }
          if (!stringp(data_map[key][KEY_KEYPATH]))
          {
              write("House does not have a key, cannot mark as available.\n");
              return 1;
          }          
        }
        data_map[key][KEY_COMPLETE] = complete;
        write("House marked as complete: " + (complete ? "Yes" : "No") + "\n");
        save();
        manager_log(this_player()->query_real_name() +
            " changed the complete flag for " + key + "\n");
        return 1;
    }
    write("Could not determine what to change in the house.\n");
    return 1;
}

public mapping get_all_listings()
{
    return data_map;
}


public void collect_taxes()
{
    mapping listings = get_all_listings();
    foreach (string name, mapping details : listings)
    {
        if (!details[KEY_COMPLETE])
        {
            continue;
        }
        if (details[KEY_OWNER] == "admin")
        {
            continue;
        }
        string owner = details[KEY_OWNER];
        object player = find_player(owner);
        //TAX_INTERVAL
        int owed = (time() - details[KEY_LAST_TAX_PAID_TIME]) / TAX_INTERVAL;
        int amount_owed = owed * details[KEY_WEEKLY_TAX];
        // Make sure the tax is positive.
        amount_owed = max(0, amount_owed);
        if (!amount_owed)
        {
            continue;
        }
        int* coins = GOG_ACCOUNTS->query_account_coins(owner);
        int platinum_available = sizeof(coins) ? coins[MONEY_PC_INDEX] : 0;
        if (platinum_available >= amount_owed)
        {
            //Paying up in full.
               
            GOG_ACCOUNTS->remove_money(owner, MONEY_PC_INDEX, amount_owed);
            details[KEY_LAST_TAX_PAID_TIME] += TAX_INTERVAL * owed;
            transaction_log(sprintf("%s full paid %d in taxes for house %s",
                         owner, amount_owed, name));
            save();
            if (objectp(player))
            {
                player->catch_msg("You have made a full payment of " +
                    amount_owed + " platinum for the taxes on " +
                    details[KEY_SHORT] + ".\n");
            }
            continue;
        }
        else if (platinum_available >= details[KEY_WEEKLY_TAX])
        {
            // At least one payment can be made, but still delinquent.
            int pay_num = platinum_available / details[KEY_WEEKLY_TAX];
            int pay_amount = details[KEY_WEEKLY_TAX] * pay_num;
            GOG_ACCOUNTS->remove_money(owner, MONEY_PC_INDEX, 
                pay_amount);
            details[KEY_LAST_TAX_PAID_TIME] += TAX_INTERVAL * pay_num;
            transaction_log(sprintf("%s partial paid %d in taxes for house %s",
                         owner, pay_amount, name));
            save();
            amount_owed -= pay_amount;
            owed -= pay_num;
            if (objectp(player))
            {
                player->catch_msg("You have made a partial payment of " +
                    pay_amount + " platinum for the taxes on your " +
                    details[KEY_SHORT] + ".\n");
            }
        }
        if (owed >= 4)
        {
            if (objectp(player))
            {
                player->catch_msg("\nYou are overdue on taxes for " +
                    details[KEY_SHORT] + 
                    ", and lose possession of the house!\n\n");
            }
            // Repossession due to 4 weeks of tax bills due.
            set_house_owner(name, "admin", 0);
        }
        else
        {
            if (objectp(player))
            {
                player->catch_msg("You are overdue on taxes for " +
                details[KEY_SHORT] + ".  You need at least " +
                amount_owed + " platinum coins in your bank account to pay " +
                "the bill.\n");
            }
        }
    }
}


// This gets called in the room when an auction is created.
// Nothing needs to be done here, but this does get called by the auction house
// on every auction.
void notify_auction_created(mapping auction_data)
{
}

// This gets called in the room when an auction is completed.
// Since the NPC is the seller in the auction, we need to
// transfer the proceeds to the actual seller.
void notify_auction_ended(mapping auction_data)
{
    if (!mappingp(data_map))
    {
        return;
    }
    foreach (string id, mapping details: data_map)
    {
        if (auction_data["id"] == details[KEY_AUCTION_ID])
        {
            string owner = details[KEY_AUCTION_RECIPIENT];
            // We have a match!
            int bid = max(auction_data["current_bid"] * 
                 (100 - FEE_PERCENT) / 100, 1);
            GOG_ACCOUNTS->add_money(owner, MONEY_PC_INDEX, 
                bid);
            transaction_log(sprintf("%s received %d platinum for house %s",
                    capitalize(owner), bid, id));
            // The house may not have sold, but the original seller
            // has been reimbursed the minimum price minus fee.
            details[KEY_AUCTION_ID] = 0;
            details[KEY_AUCTION_RECIPIENT] = 0;
            save();
            return;
        }
    }
}


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    if (!this_player()->query_wiz_level())
	return;

    add_action(list_house, "list");

    if (!is_admin())
        return;

    add_action(create_house, "create");
    add_action(edit_house, "edit");
    add_action(remove_house, "remove");
    add_action(do_transfer, "transfer");
}


public void
remove_object()
{
    save();
    ::remove_object();
}
