/*
 * Generic Storeless item list
 *
 * This storeless item list will automatically handle things like generating and tracking
 * the contents of an item list from a stored map.
 * Instead, this storeless item list will allow one to filter the list, and when
 * purchasing objects, will actually clone the object from a map and give it to the
 * player.
 *
 * Created by Britanica, January 2016
 *
 * Changes:
 * 2019-05-02 - Cotillion
 * - Changed formatting of the list
 * 2020-05: Lucius
 * - Code cleanups
 * 2020-06: Lucius
 * - More code cleanups
 * - Added item usage descriptions
 * - Added reset_next_auction_number
 * - Added expire_auctions
 * - Added reversed output
 * - Added several output options for wizards
 * 2021-12: Zizuph
 * - grab pools of auction IDs, rather than one at a time, for randomness.
 * 2022-02: Zizuph
 * - show spell enhancer status in the usage line.
 * 2022-02: Zizuph
 * - on loading, remove items that aren't recoverable, if the game boot
 *   time differs from when they were added.
 * 2023-02: Zizuph
 * - fix issue with "x armour" queries, where x is not a body location.
 *
 */
#pragma strict_types;

inherit "/std/room";

#include <cmdparse.h>
#include <filter_funs.h>
#include <macros.h>
#include <language.h>
#include <files.h>
#include <time.h>
#include <wa_types.h>

#include "/d/Genesis/imbuement/imbuement.h"
#include "../defs.h"

#define A_NAMES ({ "body", "chest", "torso", "head", "arm", "hand", \
    		   "leg", "foot", "robe", "shield" })
#define AUCTION_TYPES ({ "weapons", "armours", "imbued" })

public mapping object_list = 0;
public mapping auctions_list = 0;
public mapping auction_settings = 0;
public mapping owed_list = 0;
public mapping ranking_list = 0;
public mapping prices_list = 0;

public static mapping save_alarms = ([ ]);

public int* auction_id_pool = ({});

// Prototypes
public int add_auction_item(string auction_id, object auction_item);
public object get_auction_item(string auction_id, int login_recovery);
public object create_auction_item(mapping object_details, int login_recovery);
public int view_auction(string text, int rev);
public int remove_auction(string text);
public int expire_auctions(void);
public int create_auction_cmdline(string text);
public int recreate_auction_item(string text);
public int price_item(string text);
public int add_auction_item_cmdline(string text);
public int cancel_auction(string text);

public void load();

public mapping create_auction(int is_public, object auction_item, int min_bid,
                              int max_bid, int hours, string seller,
                              int deposit);
public int *get_won_auctions(string name);

/*
 * Function name:  create_room
 * Description  :  Set basic room values
 */
public void
create_room()
{
    setuid();
    seteuid(getuid());

    ::create_room();

    set_name("datastore");
    set_short("Datastore for Auction House");
    set_long("@@mylong@@");

    load();

    /* Do some automatic cleanup after loading */
    set_alarm(300.0, 0.0, expire_auctions);
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

    add_action(view_auction, "view");
    add_action(remove_auction, "remove");
    add_action(create_auction_cmdline, "create");
    add_action(recreate_auction_item, "recreate");
    add_action(add_auction_item_cmdline, "add");
    add_action(cancel_auction, "cancel");
    add_action(price_item, "price");
}

/*
 * Function name: mylong
 * Description  : long description for the room
 */
public string
mylong()
{
    if (!this_player()->query_wiz_level())
        return "Do not look around mortal.\n";

    return "Wizard interface for the auction house data store.\n" +
        "Wizard commands:\n" +
        "    create [public|private] auction <item> <minbid> <maxbid> <hours>\n" +
        "           <seller name> <deposit amount>\n" +
        "    view auction <auction id/search text>\n" +
        "    view open auctions\n" +
        "    view closed auctions\n" +
        "    cancel auction <auction id>\n" +
        "    recreate auction item <auction id>\n" +
        "    add auction item <item> as [auction] <auction_id>\n" +
        "    add auction imbuements <auction id> <stone type> <stone quality>\n" +
        "    add won <item> <player>\n" +
        "    view auction history <auction id/search text>\n" +
        "    price <item>\n" +
        "";
}

/*
 * Function:    query_auction_items_filename
 * Description: Returns the location of the file that should store the object list
 *              data, which includes which objects are in the store and the
 *              actual quantities
 */
public string
query_auction_items_filename()
{
    return DATA_DIR + "/auctionitems";
}

/*
 * Function:    query_auction_items_filename
 * Description: Returns the location of the file that should store the object list
 *              data, which includes which objects are in the store and the
 *              actual quantities
 */
public string
query_auction_settings_filename()
{
    return DATA_DIR + "/auctionsettings";
}

/*
 * Function:    query_auctions_filename
 * Description: Returns the location of the file that should store the object list
 *              data, which includes which objects are in the store and the
 *              actual quantities
 */
public string
query_auctions_filename()
{
    return DATA_DIR + "/auctions";
}

/*
 * Function:    query_owed_filename
 * Description: Returns the location of the file that should store the owed list
 *              data, which includes which oweds are in the store and the
 *              actual quantities
 */
public string
query_owed_filename()
{
    return DATA_DIR + "/owed";
}

/*
 * Function:    query_ranking_filename
 * Description: Returns the location of the file that should store the ranking list
 *              data, which includes which rankings are in the store and the
 *              actual quantities
 */
public string
query_ranking_filename()
{
    return DATA_DIR + "/ranking";
}

/*
 * Function:    query_prices_filename
 * Description: Returns the location of the file that should store the prices list
 *              data, which includes which prices are in the store and the
 *              actual quantities
 */
public string
query_prices_filename()
{
    return DATA_DIR + "/prices";
}

/*
 * Function:    load_object_data
 * Description: Restores the map from disk
 */
public void
load_object_data()
{
    if (!mappingp(object_list))
    {
        object_list = ([]);
        if (file_time(query_auction_items_filename()))
            object_list = restore_map(query_auction_items_filename());
    }
}

/*
 * Function name: delayed_save
 * Description  : Call the specified save function after a delay
 */
static void
delayed_save(function save_fun)
{
    string fun_name = function_name(save_fun);
    int alarm = save_alarms[fun_name];

    // Already scheduled?
    if (alarm && get_alarm(alarm)) {
        return;
    }

    save_alarms[fun_name] = set_alarm(5.0, 0.0, save_fun);
}

/*
 * Function:    save_object_data
 * Description: Saves the current object_list to disk.
 */
public void
save_object_data()
{
    if (!mappingp(object_list)) {
        save_map(([ ]), query_auction_items_filename());
    } else {
        save_map(object_list, query_auction_items_filename());
    }
}

/*
 * Function:    alarmed_save_object_data
 * Description: cancels current alarm and sets it to fire in 1 second.
 */
public void
alarmed_save_object_data()
{
    delayed_save(save_object_data);
}

/*
 * Function:    load_owed_data
 * Description: Restores the map from disk
 */
public void
load_owed_data()
{
    if (!mappingp(owed_list))
    {
        owed_list = ([]);
        if (file_time(query_owed_filename()))
    	    owed_list = restore_map(query_owed_filename());
    }
}

/*
 * Function:    save_owed_data
 * Description: Saves the current owed_list to disk.
 */
public void
save_owed_data()
{
    if (!mappingp(owed_list)) {
        save_map(([ ]), query_owed_filename());
    } else {
        save_map(owed_list, query_owed_filename());
    }
}

/*
 * Function:    alarmed_save_owed_data
 * Description: cancels current alarm and sets it to fire in 1 second.
 */
public void
alarmed_save_owed_data()
{
    delayed_save(save_owed_data);
}

/*
 * Function:    load_ranking_data
 * Description: Restores the map from disk
 */
public void
load_ranking_data()
{
    if (!mappingp(ranking_list))
    {
        ranking_list = ([]);
        if (file_time(query_ranking_filename()))
    	    ranking_list = restore_map(query_ranking_filename());
    }
}

/*
 * Function:    save_ranking_data
 * Description: Saves the current ranking_list to disk.
 */
public void
save_ranking_data()
{
    if (!mappingp(ranking_list)) {
        save_map(([ ]), query_ranking_filename());
    } else {
        save_map(ranking_list, query_ranking_filename());
    }
}

/*
 * Function:    alarmed_save_ranking_data
 * Description: cancels current alarm and sets it to fire in 1 second.
 */
public void
alarmed_save_ranking_data()
{
    delayed_save(save_ranking_data);
}

/*
 * Function:    load_prices_data
 * Description: Restores the map from disk
 */
public void
load_prices_data()
{
    if (!mappingp(prices_list))
    {
        prices_list = ([]);
        if (file_time(query_prices_filename()))
  	    prices_list = restore_map(query_prices_filename());
    }
}

/*
 * Function:    save_prices_data
 * Description: Saves the current prices_list to disk.
 */
public void
save_prices_data()
{
    if (!mappingp(prices_list)) {
        save_map(([ ]), query_prices_filename());
    } else {
        save_map(prices_list, query_prices_filename());
    }
}

/*
 * Function:    alarmed_save_prices_data
 * Description: cancels current alarm and sets it to fire in 1 second.
 */
public void
alarmed_save_prices_data()
{
    delayed_save(save_prices_data);
}

/*
 * Function:    load_auction_settings_data
 * Description: Restores the map from disk
 */
public void
load_auction_settings_data()
{
    if (!mappingp(auction_settings))
    {
        auction_settings = ([]);
        if (file_time(query_auction_settings_filename()))
	    auction_settings = restore_map(query_auction_settings_filename());
    }
}

/*
 * Function:    save_auction_settings_data
 * Description: Saves the current auction_settings to disk.
 */
public void
save_auction_settings_data()
{
    if (!mappingp(auction_settings)) {
        save_map(([ ]), query_auction_settings_filename());
    } else {
        save_map(auction_settings, query_auction_settings_filename());
    }
}

/*
 * Function:    alarmed_save_auction_settings_data
 * Description: cancels current alarm and sets it to fire in 1 second.
 */
public void
alarmed_save_auction_settings_data()
{
    delayed_save(save_auction_settings_data);
}

public void delayed_clean_unrecoverable_items()
{
    foreach(string auction_id, mixed auction_data: auctions_list)
    {
        if (!auction_data["recoverable"]
            && auction_data["boot_time"] != SECURITY->query_start_time())
        {
            remove_auction("" + auction_id);

            write_file(LOG_DIR + "load_auctions",
	          sprintf("Unrecoverable item from prior boot removed: %s.\n",
		      auction_id));
        }
    }
}


/*
 * Function:    load_auctions_data
 * Description: Restores the map from disk
 */
public void
load_auctions_data()
{
    if (!mappingp(auctions_list))
    {
        auctions_list = ([]);
        if (file_time(query_auctions_filename()))
	    auctions_list = restore_map(query_auctions_filename());
    }

    // SECURITY->query_start_time() is not correctly set when this is loaded.
    // we need to defer the cleanup slightly.
    set_alarm(60.0, 0.0, delayed_clean_unrecoverable_items);
}

/*
 * Function:    save_auctions_data
 * Description: Saves the current auctions to disk.
 */
public void
save_auctions_data()
{
    if (!mappingp(auctions_list)) {
        save_map(([ ]), query_auctions_filename());
    } else {
        save_map(auctions_list, query_auctions_filename());
    }
}

/*
 * Function:    alarmed_save_auctions_data
 * Description: cancels current alarm and sets it to fire in 1 second.
 */
public void
alarmed_save_auctions_data()
{
    delayed_save(save_auctions_data);
}

/*
 * Function name: save
 * Description : Save all data NOW
 */
public void
save()
{
    save_object_data();
    save_ranking_data();
    save_owed_data();
    save_auctions_data();
    save_auction_settings_data();
    save_prices_data();
}

/*
 * Function name: load
 * Description  : Load all auction data.
 */
public void
load()
{
    load_object_data();
    load_ranking_data();
    load_owed_data();
    load_auctions_data();
    load_auction_settings_data();
    load_prices_data();
}

/*
 * Function name: get_owed
 * Description  : Returns the owed platinum for the player
 */
public int
get_owed(string name)
{
    return owed_list[name];
}

/*
 * Function name:        set_owed
 * Description  :        Set the owed platinum for the player
 */
public int
set_owed(string name, int platinum)
{
    if (platinum) {
        owed_list += ([ name: platinum ]);
    } else {
        owed_list[name] = 0;
    }

    alarmed_save_owed_data();
    return 1;
}

/*
 * Function name:        add_owed
 * Description  :        Change the owed amount for the player
 */
public int
add_owed(string name, int platinum)
{
    set_owed(name, get_owed(name) + platinum);
}

/*
 * Function name: get_price
 * Description  : Returns average price for an object
 */
public int
get_price(string name)
{
    return prices_list[name];
}

/*
 * Function name: set_prices
 * Description  : Set the average price
 */
public int
set_prices(string name, int platinum)
{
    prices_list[name] = platinum;
    alarmed_save_prices_data();
    return 1;
}

/*
 * Function name: get_next_auction_number
 * Description  : Returns the next auction number
 *                the player
 */
public int
get_next_auction_number()
{
    int auction_number;
    
    if (!sizeof(auction_id_pool))
    {
        auction_number = auction_settings["next_auction_number"];
        if (auction_number == 0) {
            auction_number = 10001;
        }
        for (int i = auction_number + 1; i <= auction_number + 100; i++)
        {
            auction_id_pool += ({ i });
        }
        auction_number += 100;
        auction_settings["next_auction_number"] = auction_number;
        alarmed_save_auction_settings_data();
    }
    
    auction_number = one_of_list(auction_id_pool);
    auction_id_pool -= ({ auction_number });
    return auction_number;
}

/*
 * Function name: reset_next_auction_number
 * Description  : Reset the auction counter.
 */
public int
reset_next_auction_number()
{
    auction_settings["next_auction_number"] = 10001;
    auction_id_pool = ({ });
    alarmed_save_auction_settings_data();

    return 10001;
}

#define IMBUE_OBJ(X)	"/d/Genesis/ateam/aod/imbuement/obj/X"
#define IMBUE_STONE	IMBUE_OBJ(imbuement_stone)
#define IMBUE_RAN_STONE	IMBUE_OBJ(specific_stones/random_ord_stone)

/*
 * Function name:   add_auction_item
 * Arguments    :   auction_id - the identifier of the auction
 *                  auction_item - the item to be auctioned
 * Description  :   Adds a listing for an auction.
 *                  Item filename, imbuement details and object condition
 *                  are stored in the auction list.
 *                  Returns 1 for success
 *                          0 for failure
 */
public int
add_auction_item(string auction_id, object auction_item)
{
    if (!objectp(auction_item) || !strlen(auction_id))
    {
        write_file(LOG_DIR + "add_auction_error",
	    sprintf("Invalid auction_item or auction_id %d.\n",
		auction_id));
        return 0;
    }

    if (object_list[auction_id])
    {
	write_file(LOG_DIR + "add_auction_error",
	    sprintf("Object already exists in auction house as ID %d.\n",
		auction_id));
        return 0;
    }

    mapping item_data = ([
	"recover" : auction_item->query_recover(),
	"master_filename" : MASTER_OB(auction_item),
	"imbuement1_master_file" : 0,
	"imbuement2_master_file" : 0,
	"imbuement3_master_file" : 0,
    ]);

    if (auction_item->has_imbue_shadow())
    {
        object imbue_shadow;

        if (objectp(imbue_shadow = auction_item->get_shadow(1)))
	{
            item_data["imbuement1_master_file"] =
		MASTER_OB(imbue_shadow);
            item_data["imbuement1_power_level"] =
		imbue_shadow->query_imbuement_power_level();
        }

        if (objectp(imbue_shadow = auction_item->get_shadow(2)))
	{
            item_data["imbuement2_master_file"] =
		MASTER_OB(imbue_shadow);
            item_data["imbuement2_power_level"] =
		imbue_shadow->query_imbuement_power_level();
        }

        if (objectp(imbue_shadow = auction_item->get_shadow(3)))
	{
            item_data["imbuement3_master_file"] =
		MASTER_OB(imbue_shadow);
            item_data["imbuement3_power_level"] =
		imbue_shadow->query_imbuement_power_level();
        }
    }

    if (IS_WEAPON_OBJECT(auction_item))
    {
        item_data["weapon_type"] = auction_item->query_wt();
        item_data["dull"] = auction_item->query_dull();
        item_data["dull_repair"] = auction_item->query_repair_dull();
        item_data["corroded"] = auction_item->query_corroded();
        item_data["corr_repair"] = auction_item->query_repair_corr();
    }
    else if (IS_ARMOUR_OBJECT(auction_item))
    {
        item_data["condition"] = auction_item->query_condition();
        item_data["condition_repair"] = auction_item->query_repair();
    }
    else if (MASTER_OB(auction_item) == IMBUE_STONE ||
	     MASTER_OB(auction_item) == IMBUE_RAN_STONE)
    {
        string *short_parts = explode(auction_item->query_short(), " ");

        if (sizeof(short_parts) == 2)
	{
            item_data["imbuement_type"] = short_parts[1];
            item_data["imbuement_quality"] = short_parts[0];
        }
    }

    object_list[auction_id] = item_data;
    save_object_data();
    return 1;
}

private void
add_imbuement_shadow(object shadow_who, string imbuement_filename,
    int imbuement_level = 1, int shadow_num = 1)
{
    object imbuement = clone_object(imbuement_filename);

    if (!objectp(imbuement))
    {
	write_file(LOG_DIR + "recreate_object_error",
	    sprintf("Failed to create imbuement %s\n",
		imbuement_filename));
    }
    else
    {
        imbuement->set_num(shadow_num);
        imbuement->set_target(shadow_who);

        int shadow_result = imbuement->shadow_me(shadow_who);

        if (shadow_result != 0)
	{
            string imbue_description = "unusual";

            shadow_who->add_adj("imbued");

            if (shadow_num == 1)
	    {
                shadow_who->add_adj("unusual");
            }
	    else if (shadow_num == 2)
	    {
                shadow_who->add_adj("peculiar");
                imbue_description = "peculiar";
            }
	    else if (shadow_num == 3)
	    {
                shadow_who->add_adj("exotic");
                imbue_description = "exotic";
            }

            shadow_who->add_prop(IMBUE_SHORT, imbue_description);
            imbuement->init_imbue_shadow(imbuement_level);
        }
	else
	{
            write_file(LOG_DIR + "recreate_object_error",
		sprintf("Failed to add Shadow %s\n",
		    imbuement_filename));
        }
    }
}

public mixed
get_imbuement_details(mapping object_details, int imbue)
{
    string mod, path = object_details["imbuement" + imbue + "_master_file"];

    if (!path) {
        return ({ 0, 0 });
    }

    if (sscanf(FILE_NAME(path), "%s_shadow", mod) != 1) {
        return ({ 0, 0 });
    }

    return ({ mod, object_details["imbuement" + imbue +
	"_power_level"] || 1 });
}

/*
 * This is for backwards compatability
 */
private object
add_cloned_item_imbuements(object ob, mapping object_details)
{
    mixed imbue1 = get_imbuement_details(object_details, 1);
    mixed imbue2 = get_imbuement_details(object_details, 2);
    mixed imbue3 = get_imbuement_details(object_details, 3);

    /* Not imbued */
    if (!imbue1[0])
        return ob;

    if (!IMBUE_GENERATOR->imbue(ob, imbue1[0], imbue1[1],  imbue2[0], imbue2[1],
                                imbue3[0], imbue3[1]))
    {
	write_file(LOG_DIR + "recreate_object_error",
	    sprintf("Failed to reapply imbues on object %s\n", file_name(ob)));
    }

    return ob;
}

private object
restore_cloned_weapon_properties(object result, mapping object_details)
{
    int value = object_details["dull"];
    if (intp(value))
        result->set_dull(value);

    value = object_details["dull_repair"];
    if (intp(value))
        result->set_repair_dull(value);

    value = object_details["corroded"];
    if (intp(value))
        result->set_corroded(value);

    value = object_details["corr_repair"];
    if (intp(value))
        result->set_repair_corr(value);

    return result;
}

private object
restore_cloned_armour_properties(object result, mapping object_details)
{
    int value = object_details["condition"];
    if (intp(value))
        result->set_condition(value);

    value = object_details["condition_repair"];
    if (intp(value))
        result->set_repair(value);

    return result;
}

/*
 * Function name:   old_create_auction_item
 * Arguments    :   object_details - a map of the objects properties
 * Description  :   Creates the object specified in the map.
 *                  Item is created from the filename,
 *                  imbuements are added to the object
 *                  the items condition is restored
 *                  Returns 1 for success
 *                          0 for failure
 */
public object
old_create_auction_item(mapping object_details, int login_recovery = 0)
{
    object result = 0;
    string master_filename = object_details["master_filename"];

    if (strlen(master_filename))
    {
        if (master_filename == IMBUE_RAN_STONE)
            master_filename = IMBUE_STONE;

        result = clone_object(master_filename);

        if (!objectp(result))
	{
	    write_file(LOG_DIR + "recreate_object_error",
		sprintf("Failed to create object %s\n",
		    master_filename));
        }
	else
	{
            result = add_cloned_item_imbuements(result, object_details);

            if (IS_WEAPON_OBJECT(result)) {
                result = restore_cloned_weapon_properties(result, object_details);
            } else if (IS_ARMOUR_OBJECT(result)) {
                result = restore_cloned_armour_properties(result, object_details);
            } else if (master_filename == IMBUE_STONE) {
                result->set_stone_type(object_details["imbuement_type"]);
                result->set_stone_quality(object_details["imbuement_quality"]);
            }

            result->move(this_object());
        }
    } else {
        write_file(LOG_DIR + "recreate_object_error",
	    "Failed to recover master_filename");
    }

    return result;
}

public object
create_auction_item(mapping object_details, int login_recovery = 0)
{
    object ob;
    string recover = object_details["recover"];

    /* If this is an old item we attempt to recreate the item from the saved data */
    if (!recover) {
        return old_create_auction_item(object_details, login_recovery);
    }

    string file, argument;

    if (sscanf(recover, "%s:%s", file, argument) != 2) {
        file = recover;
        argument = 0;
    }

    catch(ob = clone_object(file));

    if (!objectp(ob))
    {
	write_file(LOG_DIR + "recreate_object_error", sprintf(
		"Failed to recreate from recover string: %s\n", recover));
        return 0;
    }

    if (strlen(argument))
    {
        mixed ret;
        if (ret = ob->init_recover(argument))
	{
            ob->remove_object();

            if (objectp(ret))
                return ret;

            return 0;
        }
    }

    return ob;
}

/*
 * Function name:   get_auction
 * Arguments    :   auction_id - the auction identifier
 * Description  :   Returns the map of the auction details
 */
public mapping
get_auction(int auction_id)
{
    mapping result = auctions_list[""+ auction_id];

    if (mappingp(result)) {
        return ([ ]) + result;
    }

    write(sprintf("Failed to find details for auction %d.\n", auction_id));
    return 0;
}

/*
 * Function name:   update_auction_bid
 * Arguments    :   auction_id - the auction identifier
 *                  bidder - the name of the player making the bid
 *                  bid - the amount of the bid in platinum
 * Description  :   Sets the current bid for an auction
 *                  and set the alarm to save
 *                  Returns 1 for success
 *                          0 for failure
 */
public int
update_auction_bid(int auction_id, string bidder, int bid)
{
    int result = 0;
    mapping auction_data = auctions_list[""+ auction_id];

    if (m_sizeof(auction_data))
    {
        auction_data["bidder"] = bidder;
        auction_data["current_bid"] = bid;

        /* Bids push forward the end time atleast 90 seconds into the future */
        int min_end = time() + 90;

        if (auction_data["auction_end"] < min_end)
            auction_data["auction_end"] = min_end;

        result = 1;
        alarmed_save_auctions_data();
    }

    return result;
}

/*
 * Function name:   update_auction_end
 * Arguments    :   auction_id - the auction identifier
 *                  end_time - the time the auction ends
 * Description  :   Sets the auction end time for an auction
 *                  and set the alarm to save
 *                  Returns 1 for success
 *                          0 for failure
 */
public int
update_auction_end(int auction_id, int end_time)
{
    int result = 0;
    mapping auction_data = auctions_list[""+ auction_id];

    if (m_sizeof(auction_data))
    {
        result = 1;
        auction_data["auction_end"] = end_time;
        alarmed_save_auctions_data();
    }

    return result;
}

/*
 * Function name:   get_auction_item
 * Arguments    :   auction_id - auction identifier
 * Description  :   uses the id auction_id to get the objects map
 *                  returns the created object
 *                  Returns 1 for success
 *                          0 for failure
 */
public object
get_auction_item(string auction_id, int login_recovery = 0)
{
    object result = 0;

    if (strlen(auction_id))
    {
        mapping object_details = object_list[auction_id];
        if (m_sizeof(object_details))
            result = create_auction_item(object_details, login_recovery);
    }

    return result;
}

/*
 * Function name:   get_imbue_info
 * Arguments    :   auction_id - auction identifier
 * Description  :   returns the required information for
 *                  Karkadelt to transmogriphy an imbued item
 */
public mixed *
get_imbue_info(string auction_id)
{
    mixed *result = ({ atoi(auction_id) });

    if (strlen(auction_id)) {
        mapping object_details = object_list[auction_id];

        if (mappingp(object_details)) {
            string imbue_name = "";

            for (int i = 1; i <= 3; i++) {
                string filename = object_details["imbuement" + i + "_master_file"];

                if (strlen(filename)) {
                    int level = object_details["imbuement" + i + "_power_level"];

                    if (sscanf(filename, "/d/Genesis/imbuement/shadows/%s_shadow",
                               imbue_name) == 1) {
                        result += ({ imbue_name });
                        result += ({ level });
                    }
                }
            }
        }
    }

    while (sizeof(result) < 7)
	result += ({ 0 });

    return result;
}

public string
short_description(mixed item)
{
    if (item["is_heap"]) {
        return sprintf("%s (x%d)", capitalize(LANG_ADDART(item["short"])),
                       item["heap_size"]);
    }

    return capitalize(LANG_ADDART(item["short"]));
}

/*
 * Function name:   print_item
 * Arguments    :   id - auction identifier
 * Description  :   prints a single auction
 */
public string *
print_item(int id)
{
    string *result = ({});
    mapping auction_data = auctions_list["" + id];

    if (!mappingp(auction_data)) {
        return result;
    }

    string format = "%-12s %=-64s\n";

    write(sprintf(format, "Auction number", "" + id));

    write(sprintf(format, "Object", short_description(auction_data)));
    write(sprintf(format, "Description", auction_data["long"]));

    if (strlen(auction_data["usage"]))
	write(sprintf(format, "Usage", auction_data["usage"]));

    write(sprintf(format, "Weight", auction_data["weight"]));
    write(sprintf(format, "Volume", auction_data["volume"]));
    write(sprintf(format, "Store Price", auction_data["store_price"]));

    if (strlen(auction_data["light"]))
	write(sprintf(format, "Light", auction_data["light"]));

    if (auction_data["recoverable"]) {
	write(sprintf(format, "Recoverable",
		"It seems to be able to last a while."));
    }

    /* added with the expiration system */
    if (strlen(auction_data["expiration"])) {
	write(sprintf(format, "Expiration", auction_data["expiration"]));
    }

    string buyer = "-", seller = "-";

    if (auction_data["public"] || this_player()->query_wiz_level()) {
        seller = capitalize(auction_data["seller"]);

        if (seller != capitalize(auction_data["bidder"])) {
            buyer = capitalize(auction_data["bidder"]);
        }
    }

    if (auction_data["bidder"] == this_player()->query_real_name()) {
        buyer = "You";
    }

    if (auction_data["seller"] == this_player()->query_real_name()) {
        seller = "You";
    }

    write(sprintf(format, "High Bidder", buyer));
    write(sprintf(format, "Seller", seller));

    write(sprintf(format, "Current bid ", max(auction_data["minimum_bid"],
		auction_data["current_bid"]) + " platinum"));

    if (auction_data["maximum_bid"])
    {
	write(sprintf(format, "Maximum bid ",
		auction_data["maximum_bid"] + " platinum"));
    }

    string time_left = CONVTIME(auction_data["auction_end"] - time());
    write(sprintf(format, "Remaining", time_left)) ;
    return result;
}

/* Sort function for auction end */
public int
sort_auction_end(int a, int b)
{
    return auctions_list["" + b]["auction_end"] -
	   auctions_list["" + a]["auction_end"];
}

/* Sort function for auction end - reversed */
public int
rev_sort_auction_end(int a, int b)
{
    return auctions_list["" + a]["auction_end"] -
	   auctions_list["" + b]["auction_end"];
}

/*
 * Function name:   print_items
 * Arguments    :   auction_ids - arraay of auction ids
 * 		    reverse - reverse sorting
 * 		    show_seller - show seller instead of bidder
 * Description  :   Prints the summary of each auction item in the list
 */
public varargs void
print_items(int *auction_ids, int reverse, int show_seller)
{
    string *lines = ({});
    string hrule1 = ("-" * 79) + "\n";
    string hrule2 = ("=" * 79) + "\n";
    int id_size = sizeof(auction_ids);

    lines += ({ hrule1 });
    lines += ({ sprintf("%|79s", "----- Available auctions -----\n") });
    lines += ({ hrule1 });

    lines += ({ sprintf("%-6s %-39s %-11s %-9s %10s\n",
	    "Num", "Auction Item",
	    (show_seller ? "Seller" : "High bidder"),
	    "Bid (Max)", "Time Left") });

    if (reverse)
	sort_array(auction_ids, rev_sort_auction_end);
    else
	sort_array(auction_ids, sort_auction_end);

    foreach (int aid: auction_ids)
    {
        mapping auction_data = auctions_list["" + aid];

        if (mappingp(auction_data))
	{
            string name = short_description(auction_data);

            if (!stringp(name)) {
                name = "Mystery";
            }

            if (!auction_data["recoverable"]) {
                name = "*" + name;
            }

            string bidder = "-";
            string seller = "-";

            int current_bid = max(auction_data["minimum_bid"],
                                  auction_data["current_bid"]);

            if (auction_data["public"] || this_player()->query_wiz_level())
	    {
                seller = capitalize(auction_data["seller"]);
                if (seller != capitalize(auction_data["bidder"])) {
                    bidder = capitalize(auction_data["bidder"]);
                }
            }

            if (auction_data["bidder"] == this_player()->query_real_name()) {
                bidder = "You";
            }

            if (auction_data["seller"] == this_player()->query_real_name()) {
                seller = "You";
            }

            string time_left = TIME2STR(auction_data["auction_end"] - time(), 2);

            lines += ({ sprintf("%-6d %=-39s %-11s %-=9s %=-10s\n",
                                aid, name,
				(show_seller ? seller : bidder),
                                current_bid + " (" +
				   (auction_data["maximum_bid"] ?
				    auction_data["maximum_bid"] : "-") + ")",
                                time_left) });

            if (auction_data["allimbuements"])
	    {
                string *imbues = explode(auction_data["allimbuements"], "\n");
                lines += map(imbues, &sprintf("%-6s %=-73s\n", "", ));
            }

            lines += ({ "\n" });
        }
    }

    lines += ({ hrule2 });

    if (id_size) {
        lines += ({ sprintf("%|79s\n",
		"* = This item does not seem to last a while.") });
    }

    lines += ({ sprintf("%|79s\n",
	    "There " + (id_size == 1 ? "is" : "are" ) + " currently "
	    + id_size + (id_size == 1 ? " item" : " items" )
	    + " up for bid") });

    string player_name = this_player()->query_real_name();
    int *ids = get_won_auctions(player_name);

    if (sizeof(ids))
    {
	lines += ({ hrule1 });
        lines += ({ sprintf("%|79s\n",
		"There are items awaiting you at the auction house.") });
    }

    int credit = get_owed(this_player()->query_real_name());

    if (credit)
    {
	lines += ({ hrule1 });
        lines += ({ sprintf("%|79s\n",
		"You currently have " + credit + " platinum in credit at " +
		"the auction house.") });
    }

    lines += ({ hrule1 });
    this_player()->more(implode(lines, ""));
}

/*
 * Function name:   get_armour_slots
 * Arguments    :   armour_type - type of armour
 * Description  :   returns the armour bit mask for an armour location
 *
 * Note         : this method really belongs in wa_types.h
 */
private int
get_armour_slots(string armour_type)
{
    int result = 0;
    string slot_name = "";

    if (sscanf(armour_type, "%s armour", slot_name) == 1) {
        int index = member_array(slot_name, A_NAMES);

        switch(index) {
            case 0:
                result = A_BODY;
                break;

            case 1:
                result = A_CHEST;
                break;

            case 2:
                result = A_TORSO;
                break;

            case 3:
                result = A_HEAD;
                break;

            case 4:
                result = A_ARMS;
                break;

            case 5:
                result = A_HANDS;
                break;

            case 6:
                result = A_LEGS;
                break;

            case 7:
                result = A_FEET;
                break;

            case 8:
                result = A_ROBE;
                break;

            case 9:
                result = A_SHIELD;
                break;

            default:
                result = 0;
        }
    }

    return result;
}

/*
 * Function name:   search_auctions
 * Arguments    :   text - the search text
 * Description  :   Parses the text for the below information
 *                  aulist [imbued|unimbued] [type|#]
 *                         [with (imbue strength|imbue type) imbuments]
 *                         [(under|over) price] [between pricelow and pricehigh]
 *                  imbued/unimbued
 *                       - if present, only return items that are/aren't imbued
 *                  type
 *                    #  - auction item id
 *                       - a weapons type
 *                             sword
 *                             polearm
 *                             axe
 *                             club
 *                             missile weapon
 *                             javelin
 *                       - an armour type
 *                             body armour
 *                             chest armour
 *                             head armour
 *                             leg armour
 *                             arm armour
 *                             hand armour
 *                             foot armour
 *                        - imbuement stones
 *                             stones
 *
 *                  with (description) imbuements
 *                  ie    with sage imbuements
 *                        with faint imbuements
 *                        with silvery faint imbuements
 *                        with quartz imbuements
 *
 *                  over/under/between\n
 *                  ie    under 50
 *                        over 20
 *                        between 40 and 120
 *                          0 for failure
 *
 *                Returns the array of matching auction ids
 */
public int *
search_auctions(string text)
{
    int minBid = 1;
    int maxBid = 1000000;
    int show_only_weapons = 0;
    int desired_weapon_type = -1;
    int show_only_armour = 0;
    int desired_armour_type = -1;
    int show_only_imbued = 0;
    int show_only_unimbued = 0;

    string search_query = "";
    string desired_keyword_search = "";
    string *imbuement_desc_array = ({});

    string *lines = ({ });

    string imbuement_string = "";

    // Parse out special strings
    if (strlen(text))
    {
        if(text == "unimbued" || sscanf(text, "unimbued %s", search_query) == 1) {
            show_only_unimbued = 1;
            text = search_query;
            lines += ({ "Limiting search to unimbued auction items.\n" });
        } else if (text == "imbued" ||
                   sscanf(text, "imbued %s", search_query) == 1) {
            show_only_imbued = 1;
            text = search_query;
            lines += ({ "Limiting search to imbued auction items.\n" });
        } else if(sscanf(text, "imbuement stones %s", search_query) == 1) {
            text = sprintf("stones %s", search_query);
        }
    }

    // Parse out the over/under/between values
    if (strlen(text))
    {
//        lines += ({ sprintf("%s\n", text) });
        search_query = "";

        if (sscanf(text, "under %i", maxBid) == 1 ||
	    sscanf(text, "%s under %i", search_query, maxBid) == 2)
	{
            lines += ({ sprintf("Limiting list to auctions with a price up to %i.\n", maxBid) });
            text = search_query;
        }
	else if (sscanf(text, "over %i", minBid) == 1 ||
	    sscanf(text, "%s over %i", search_query, minBid) == 2)
	{
            lines += ({ sprintf("Limiting list to auctions with a price starting at %i.\n", minBid) });
            text = search_query;
        }
	else if (sscanf(text, "between %i and %i", minBid, maxBid) == 2 ||
	    sscanf(text, "%s between %i and %i", search_query, minBid, maxBid) == 3)
	{
            lines += ({ sprintf("Limiting list to auctions with a price starting at %i and up to and including %i.\n", minBid, maxBid) });
            text = search_query;
        }

        if (minBid == 0 || maxBid == 0) {
            lines += ( {"Auctions never have prices that are zero.\n" });
        }

        if (minBid < 0 || maxBid < 0) {
            lines += ({"Nobody gives the bidders money.  It works the other way around.\n" });
        }
    }

    imbuement_string = "";

    // Parse out imbue search strings
    if (strlen(text))
    {
        search_query = "";

        if (sscanf(text, "with %simbuements", imbuement_string) == 1 ||
	    sscanf(text, "%s with %simbuements", search_query, imbuement_string) == 2)
	{
            text = search_query;
            imbuement_desc_array = explode(imbuement_string, " ");
            lines += ({ sprintf("Limiting list to auctions with imbuements that are %s.\n",
		    implode(imbuement_desc_array, " and ")) });
        }
    }

    // Test search string search
    if (strlen(text))
    {
        int group_index = member_array(text, AUCTION_TYPES);

        if (group_index == 0)
	{
            show_only_weapons = 1;
            lines += ({ "Item Filter is weapons filter.\n" });
            text = "";
        }
	else if (group_index == 1)
	{
            show_only_armour = 1;
            lines += ({ "Item Filter is armour filter.\n" });
            text = "";
        }
	else if (group_index == 2)
	{
            show_only_imbued = 1;
            lines += ({ "imbued Filter is imbued filter.\n" });
            text = "";
        }
	else
	{
            string singular_text = LANG_SWORD(text);

            if (member_array(singular_text, W_NAMES) >= 0)
	    {
                desired_weapon_type = member_array(singular_text, W_NAMES);
                lines += ({ sprintf("Item Filter is weapons type filter: %s.\n",
			W_NAMES[desired_weapon_type]) });
            }
	    else if (singular_text == "missile weapon")
	    {
                desired_weapon_type = 5;
                lines += ({ sprintf("Item Filter is weapons type filter: %s.\n",
			W_NAMES[desired_weapon_type]) });
            }
	    else
	    {
                int armourType = get_armour_slots(text);

                if (armourType > 0)
		        {
                    desired_keyword_search = "";
                    desired_armour_type = armourType;
                    lines += ({ sprintf("Item Filter is armour type filter: %s.\n", text) });
                }
		else
		{
                    lines += ({ sprintf("Keyword search is %s.\n", text) });
                    desired_keyword_search = text;
                }
            }
        }
    }

    int *result = ({});
    int now = time();

    foreach(string key, mapping auction_data: auctions_list)
    {
        int auction_end = auction_data["auction_end"];

        if (auction_end > now)
	{
            int current_bid = max(auction_data["minimum_bid"],
                                  auction_data["current_bid"]);

            if (current_bid < minBid || current_bid > maxBid)
                continue;

            if (show_only_weapons && !auction_data["is_weapon"])
                continue;

            if (show_only_armour && !auction_data["is_armour"])
                continue;

            if (desired_weapon_type != -1 &&
		(auction_data["weapon_type"] != desired_weapon_type ||
		    !auction_data["is_weapon"] ))
	    {
                continue;
            }

            if (desired_armour_type != -1 &&
		((auction_data["armour_slots"] & desired_armour_type ) == 0 ||
		    !auction_data["is_armour"]))
	    {
                continue;
            }

            if (show_only_imbued && !auction_data["is_imbued"])
                continue;

            if (show_only_unimbued && auction_data["is_imbued"])
                continue;

            string short_description = auction_data["short"];

            if (strlen(desired_keyword_search) &&
		!wildmatch("*" + desired_keyword_search + "*", short_description))
	    {
                continue;
            }

            if (sizeof(imbuement_desc_array))
	    {
                string imbuement_description = auction_data["allimbuements"];
                int skip = 0;

                foreach(string imbuement : imbuement_desc_array)
		{
                    if (!wildmatch("*" + imbuement + "*", imbuement_description)) {
                        skip = 1;
                        break;
                    }
                }

                if (skip)
                    continue;
            }

            result += ({ atoi(key) });
        }
    }

    // Display filters being used
    write(implode(lines, ""));
    return result;
}

/*
 * Function name:   get_owner_auction_ids
 * Description  :   Returns an array of auction id
 *                  where the caller is the seller
 */
public int *
get_owner_auction_ids(string who)
{
    int *result = ({});

    if (!strlen(who))
	who = this_player()->query_real_name();

    foreach(string key, mapping auction_data: auctions_list)
    {
        if (mappingp(auction_data)) {
            if (who == auction_data["seller"]) {
                result += ({ atoi(key) });
            }
        }
    }

    return result;
}

/*
 * Function name:   get_open_auction_ids
 * Description  :   Returns an array of auction id
 *                  whose auction end time are in the
 *                  future
 */
public int *
get_open_auction_ids()
{
    int now = time();
    int *result = ({});

    foreach(string key, mapping auction_data: auctions_list)
    {
        if (mappingp(auction_data)) {
            int auction_end = auction_data["auction_end"];

            if (auction_end > now) {
                result += ({ atoi(key) });
            }
        }
    }

    return result;
}

/*
 * Function name:   get_closed_auction_ids
 * Description  :   Returns an array of auction id
 *                  whose auction end time are in the
 *                  past or right now
 */
public int *
get_closed_auction_ids()
{
    int now = time();
    int *result = ({});

    foreach(string key, mapping auction_data: auctions_list)
    {
        if (mappingp(auction_data)) {
            int auction_end = auction_data["auction_end"];

            if (auction_end <= now) {
                result += ({ atoi(key) });
            }
        }
    }

    return result;
}

/*
 * Function name:   view_auction
 * Arguments    :   text - command and arguments
 * 		    rev - reverse sort output
 * Description  :   Handles the view command
 *                  Returns 1 for success
 *                          0 for failure
 */
public int
view_auction(string text, int rev)
{
    int auction_id = 0;
    string search_text = "";

    if (sscanf(text, "auction %i", auction_id) == 1) {
        write(implode(print_item(auction_id), ""));
    } else if (text == "open auctions") {
        print_items(get_open_auction_ids(), rev);
    } else if (text == "owner auctions") {
        print_items(get_owner_auction_ids(search_text), rev);
    } else if (sscanf(text, "auction %s", search_text) == 1) {
        print_items(search_auctions(search_text), rev);
    } else if (text == "open seller auctions") {
        print_items(get_open_auction_ids(), rev, 1);
    } else if (text == "closed seller auctions") {
        print_items(get_closed_auction_ids(), rev, 1);
    } else if (text == "closed auctions") {
        print_items(get_closed_auction_ids(), rev);
    } else if (sscanf(text, "seller %s", search_text) == 1) {
        print_items(get_owner_auction_ids(search_text), rev);
    } else {
	return 0;
    }

    return 1;
}

/*
 * Function name:   remove_auction
 * Arguments    :   auction_id - auction identifier
 * Description  :   Removed the auction from the auction list and remove the auction item
 *                  Returns 1
 */
public int
remove_auction(string auction_id)
{
    mapping auction_data = auctions_list[auction_id];
    string short = "Item did not exist in map";

    if (mappingp(auction_data)) {
        short = auction_data["short"];
        
        if (auction_data["bidder"] && auction_data["bid_amount"])
        {
            write_file(LOG_DIR + "object_remove",
		        sprintf("%s refunded %d platinum\n",
                auction_data["bidder"], auction_data["bid_amount"]));
            AUCTION_HOUSE->add_platinum_due(
                auction_data["bidder"], auction_data["bid_amount"]);
        }
    }

    m_delkey(auctions_list, auction_id);
    write_file(LOG_DIR + "auction_remove",
	sprintf("%s %-14s removed %s from auction data\n",
	    ctime(time()), short, auction_id));

    mapping object_data = object_list[auction_id];
    short = "Item did not exist in map";

    if (mappingp(object_data))
    {
        short = object_data["master_filename"];

        if (object_data["imbuement1_master_file"] && object_data["recoverable"])
	{
            write_file(LOG_DIR + "object_remove",
		sprintf("%s %-14s kept %s as is recoverable with imbuements\n",
		    ctime(time()), short, auction_id));
        } else {
            //m_delkey(object_list, auction_id);
            write_file(LOG_DIR + "object_remove",
		sprintf("%s %-14s removed %s from object data\n",
		    ctime(time()), short, auction_id));
        }
    } else {
        m_delkey(object_list, auction_id);
        write_file(LOG_DIR + "object_remove",
	    sprintf("%s %-14s removed %s as object data invalid\n",
		ctime(time()), short, auction_id));
    }

    alarmed_save_auctions_data();
    alarmed_save_object_data();
    return 1;
}

/*
 * Do some cleanup to workaround some
 * unfortunate design decisions
 */
public int
expire_auctions(void)
{
    int aCount = 0, oCount = 0;
    int now = time(), expire = AUCTION_EXPIRE;

    /*
     * Prune auctions that are past expiration.
     */
    foreach(string key, mapping data: auctions_list)
    {
	int ended = data["auction_end"] - now;

	if (ended > expire)
	    continue;

	aCount++;
	m_delkey(auctions_list, key);
    }

    /*
     * Prune the object list with prejudice.
     */
    foreach (string key, mapping data: object_list)
    {
	if (mappingp(auctions_list[key]))
	    continue;

	oCount++;
	m_delkey(object_list, key);
    }

    /*
     * Prune the owed list with prejudice.
     */
    foreach (string key, int data: owed_list)
    {
	if (!data) m_delkey(owed_list, key);
    }

    write_file(LOG_DIR + "expire_log",
	sprintf("%s: Pruned %d auctions; %d object items.\n",
	    ctime(time()), aCount, oCount));

    alarmed_save_auctions_data();
    alarmed_save_object_data();
    alarmed_save_owed_data();
    return 1;
}

/*
 * Function name:   get_won_auctions
 * Arguments    :   name - players name
 * Description  :   Returns an array of auction items where the name matches the bidder
 *                  and the auction has ended.
 */
public int *
get_won_auctions(string name)
{
    int *result = ({});
    int now = time();

    foreach(string key, mapping auction_data: auctions_list)
    {
        if (auction_data && auction_data["auction_end"] <= (now - 60) &&
                auction_data["bidder"] == name)
	{
            result += ({ atoi(key) });
        }
    }

    return result;
}

/* Get the short description for an auction */
public string
auction_short(object item)
{
    if (item->query_prop(HEAP_I_IS))
        return item->singular_short();

    return LANG_SHORT(item);
}

/*
 * Function name:   create_auction
 * Arguments    :   is_public - 1 - Public Auction 0 - Private Auction
 *                  item      - item to be auctioned
 *                  minbid    - minimum bid for the auction
 *                  maxbid    - maximum bid for the auction
 *                  hours     - duration of auction in hours
 *                  seller    - name of player listing the auction
 *                  deposit   - deposit for auctions with a high minimum bid
 * Description  :
 *                  Returns copy of the mappings for the auction
 */
public mapping
create_auction(int is_public, object item, int minbid, int maxbid,
    int hours, string seller, int deposit)
{
    if (!objectp(item))
        return ([ ]);

    int auction_number = get_next_auction_number();
    mapping auction_data = ([ ]);

    auction_data["short"] = auction_short(item);
    auction_data["minimum_bid"] = minbid;
    auction_data["maximum_bid"] = maxbid;
    auction_data["hours"] = hours;
    auction_data["seller"] = seller;
    auction_data["public"] = is_public;
    auction_data["id"] = auction_number;
    auction_data["bidder"] = seller;
    auction_data["current_bid"] = deposit;
    auction_data["auction_end"] = time() + hours * 3600;

    auction_data["is_imbued"] = item->has_imbue_shadow();
    auction_data["allimbuements"] = item->query_all_imbued_indications();

    auction_data["is_weapon"] = IS_WEAPON_OBJECT(item);
    auction_data["weapon_type"] = item->query_wt();
    auction_data["is_armour"] = IS_ARMOUR_OBJECT(item);
    auction_data["armour_slots"] = item->query_at();

    auction_data["is_holdable"] = IS_HOLDABLE_OBJECT(item);
    auction_data["is_wearable"] = IS_WEARABLE_OBJECT(item);

    auction_data["long"] = item->long();
    auction_data["weight"] = item->appraise_weight(0);
    auction_data["volume"] = item->appraise_volume(0);
    auction_data["store_price"] = item->appraise_value(0);

    auction_data["light"] = item->appraise_light(0);

    auction_data["recoverable"] = (item->query_recover() &&
				  !item->may_not_recover());
                  
    auction_data["boot_time"] = SECURITY->query_start_time();

    auction_data["is_heap"] = item->query_prop(HEAP_I_IS);
    auction_data["heap_size"] = item->num_heap();

    auction_data["is_herb"] = IS_HERB_OBJECT(item);
    auction_data["herb_name"] = item->query_herb_name();

    string usage;
    if (auction_data["is_weapon"])
	    usage = item->wep_usage_desc();
    else if (auction_data["is_holdable"])
	    usage = item->holdable_item_usage_desc();
    else
	    usage = item->wearable_item_usage_desc();
    if (item->query_spellpower_enhancer())
    {
        usage += item->item_spellpower_desc();
    }
    auction_data["usage"] = usage;

    /* added with the expiration system */
    auction_data["expiration"] = item->appraise_item_expiration();

    auctions_list["" + auction_number] = auction_data;
    alarmed_save_auctions_data();

    add_auction_item("" + auction_number, item);

    return ([ ]) + auction_data;
}

/*
 * Function name:   create_auction_cmdline
 * Arguments    :   text - command line
 * Description  :   creates auction from command line
 *                  create (private|public) auction <item> <minbid> <maxbid> <hours> <lister> <deposit>
 *                  Returns 1 for success
 *                          0 for failure
 */
public int
create_auction_cmdline(string text)
{
    string public_private = "";
    object item;
    string item_string = "";
    int minbid = 0;
    int maxbid = 0;
    int hours = 0;
    string seller = "";
    int amount = 0;
    int deposit = 0;
    string details = "";

    write(sprintf("Create Auction [%s]\n", text));

    if (parse_command(text, this_player(), " %w [auction] %o %d %d %d %w %d ",
                      public_private, item, minbid, maxbid, hours, seller, deposit))
    {
        write("Command Parsed");
        write(sprintf("Command Parsed.\n%s auction for %s with a min bid of %d," +
                      " a max bid of %d," +
                      " for %d hours, by %s, with a deposit of %d\n",
                      public_private,
                      item->query_short(),
                      minbid,
                      maxbid,
                      hours,
                      seller,
                      deposit
                     ));
        create_auction(public_private != "private", item, minbid, maxbid, hours,
                       seller, deposit);
        return 1;
    }

    notify_fail("create [public|private] auction <item> <minbid> <maxbid> <hours>"
                + "       <seller name> <deposit amount>\n");
    return 0;
}

/*
 * Function name:   recreate_auction_item
 * Arguments    :   text - auction identifier
 * Description  :   command line method to re-create and auction item
 *                  from the objects list of auction item
 *                  Returns 1
 */
public int
recreate_auction_item(string text)
{
    string auctionid = "";

    if (sscanf(text, "auction item %s", text) == 1)
    {
        object ob = get_auction_item(text);
        return 1;
    }

    return 0;
}

public int
add_auction_item_cmdline(string text)
{
    int auction_id = 0;
    object item;

    if (parse_command(text, this_player(), " auction item %o as [auction] %i ",
                      item, auction_id) == 2)
    {
        if (objectp(item)) {
            add_auction_item("" + auction_id, item);
            return 1;
        }
    }

    string stone_type = "";
    string stone_quality = "";

    if (sscanf(text, "auction imbuements %i %s %s", auction_id, stone_type,
               stone_quality) == 3)
    {
        mapping object_details = object_list["" + auction_id];

        if (mappingp(object_details))
	{
            if (object_details["master_filename"] == IMBUE_STONE ||
		object_details["master_filename"] == IMBUE_RAN_STONE)
	    {
                object_details += (["imbuement_type": stone_type]);
                object_details += (["imbuement_quality": stone_quality]);
                save_object_data();
                return 1;
            } else {
                notify_fail(sprintf("Auction item %i is not an imbuement stone",
                                    auction_id));
            }
        }
    }

    string player = "";
    string item_desc = "";

    if (sscanf(text, "won %s %s", item_desc, player) == 2)
    {
        object *items = FIND_STR_IN_OBJECT(item_desc, this_player());

        if (sizeof(items))
	{
            mapping auction_details = create_auction(0, items[0],
		100, 100, 0, player, 0);

            if (mappingp(auction_details))
	    {
                write(sprintf("Created auction %i to return item %s.\n",
                              auction_details["id"], auction_details["short"]));
            } else {
                write("Failed to create auction.\n");
            }

            return 1;
        } else {
            write("Failed to find item.\n");
        }
    }

    write(text + "\n");
    return 0;
}

/*
 * Function name: ensure_ranking
 * Arguments    : name - The players query_real_name
 * Description  : Returns the ranking number for a player
 */
public int
ensure_ranking(string name)
{
    int result = ranking_list[name];

    if (!intp(result) || !result)
    {
        result = auction_settings["latest_ranking"];

        if (intp(result)) {
            result++;
        } else {
            result = 1;
        }

        auction_settings["latest_ranking"] = result;
        ranking_list[name] = result;
        alarmed_save_ranking_data();
        alarmed_save_auction_settings_data();
    }

    return result;
}

public int
get_last_auction_end()
{
    int result = auction_settings["last_auction_end"];

    if (!result) {
        result = time();
    }

    return result;
}

public int
set_last_auction_end(int auction_end)
{
    auction_settings += (["last_auction_end" : auction_end]);
    alarmed_save_auction_settings_data();
    return 1;
}

public int
cancel_auction(string text)
{
    int auction_id = 0;

    if (sscanf(text, "auction %i", auction_id) == 1) {
        return remove_auction("" + auction_id);
    }

    return 0;
}

public int
price_item(string text)
{
    object *items = FIND_STR_IN_OBJECT(text, this_player());

    if (sizeof(items))
    {
        string key = implode(explode(items[0]->short(), " "), "");
        write(sprintf("checking for average price of %s.\n", key));

        int price = get_price(key);

        if (price) {
            write(sprintf("The average price of %s [%s] is %i.\n",
		    items[0]->short(), key, price));
            return 1;
        }
    }

    write("No items match. Checking for string match.\n");
    int entry = get_price(text);

    if (entry) {
        write(sprintf("The average price of %s is %i.\n", text, entry));
        return 1;
    }

    return 0;
}

public void
remove_object()
{
    save();
    ::remove_object();
}
