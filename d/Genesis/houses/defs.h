/*
 * Housing definitions file
 *
 * Varian, July 2021
 *
 */

#ifndef HOUSE_DEFS
#define HOUSE_DEFS
#define HOUSE_PATH         "/d/Genesis/houses/"

#define HOUSE_DOOR          HOUSE_PATH + "house_door"
#define HOUSE_KEY           HOUSE_PATH + "house_key"

#define HOUSE_DEED          HOUSE_PATH + "house_deed"

#define HOUSE_BASE          HOUSE_PATH + "housebase"

#define ADMIN         ({ "varian", "zizuph", "arman", "cherek" })


#define HOUSE_LOG_PATH (HOUSE_PATH + "log/")
#define HOUSE_MANAGER (HOUSE_PATH + "house_manager")

#define DISPLAY_ROOM  (HOUSE_PATH + "display_room")

// The owner of the house
#define KEY_OWNER "owner"
// Whether the house has been fully configured in the house manager
#define KEY_COMPLETE "complete"
// Asking price for the house
#define KEY_PRICE "price"
// List of paths to the rooms that are visible in the sale poster.
#define KEY_ROOMS "rooms"
// Short description of the room, used by players
#define KEY_SHORT "short"
// Long description of the house shown in the sale poster
#define KEY_LONG "long"
// Whether the property is listed for sale
#define KEY_FORSALE "forsale"
// The last sale price and time of the house
#define KEY_PRIORSALE "priorsale"
// The list of names of players that can automatically enter the house.
#define KEY_INVITED "invited"
// The path to the key for the house door.
#define KEY_KEYPATH "path"
// The amount of taxes charged each week.
#define KEY_WEEKLY_TAX "weeklytax"
// The last time that the current owner paid their taxes.
#define KEY_LAST_TAX_PAID_TIME "last_paid_time"
// How many deeds for the house exist.
#define KEY_DEED_COUNT "deed_count"
// The auction ID created to sell the house
#define KEY_AUCTION_ID "auction_id"
// The recipient of the auction proceeds
#define KEY_AUCTION_RECIPIENT "auction_recipient"


// Add this property if you want to avoid an item being expelled
// from the house.
#define ALLOWED_IN_HOUSE "_allowed_in_house"


#endif HOUSE_DEFS
