 
inherit "/std/room";

#include "./defs.h"
#include <composite.h> 
#include <language.h> 
#include <stdproperties.h>
 
static mapping added_items = ([]);


public mapping get_items()
{
   return added_items;
}   
 
public string listing_description(mapping details)
{
    string result = "You look at the listing for " + details[KEY_SHORT] + ".\n";
    result += details[KEY_LONG] + "\n\n";
    result += "Asking price: " + details[KEY_PRICE] + " platinum.\n";
    result += "Weekly taxes: " + details[KEY_WEEKLY_TAX] + " platinum.\n";
    result += "Seller: " + HOUSE_MANAGER->get_owner_name(details) + "\n";
    if (m_sizeof(details[KEY_ROOMS]))
    {
        result += "The finest artists have been commissioned to paint "
          + "pictures detailing the house to you to peruse in advance!\n\n";
        foreach (string path, string name: details[KEY_ROOMS]) 
        {
            result += "/* " + name + " picture */\n";
            object room = find_object(path);
            if (!objectp(room))
            {
                path->teleledningsanka();
            }
            result += find_object(path)->long() + "\n"; 
        }
    }
    return result;
}

public void update_listings()
{ 
    mapping new_added_items = ([]);
    mapping listings = find_object(HOUSE_MANAGER)->get_all_listings();
    if (mappingp(listings))
    {   
        int listing_index = 1;
        string* shorts = ({});    
        foreach (string key, mapping details: listings) {
            if (!details[KEY_FORSALE] && !details[KEY_AUCTION_ID])
                continue;
            if (!details[KEY_COMPLETE])
                continue;
            if (details[KEY_OWNER] != "admin")
                continue;
            shorts += ({ details[KEY_SHORT]});
            string listing_desc = listing_description(details);
            // Create various ways to find the specific listing.
            new_added_items[LANG_STRIPART(lower_case(details[KEY_SHORT])) + " listing"] = 
            new_added_items[LANG_ORD2WORD(listing_index) + " listing"] = 
            new_added_items[LANG_STRIPART(lower_case(details[KEY_SHORT])) + " poster"] = 
            new_added_items[LANG_ORD2WORD(listing_index) + " poster"] = listing_desc;
            if (listing_index == 1)
            {
                new_added_items["listing"] = 
                new_added_items["poster"] = listing_desc;
            }
            listing_index++;
            
        }
        if (sizeof(shorts)) {
            string listing_desc = "You see various posters for "
                + COMPOSITE_WORDS(shorts) +".\n";
            new_added_items["listings"] = listing_desc;
            new_added_items["posters"] = listing_desc;
        }
    }
    int changed = 0;
    foreach (string key, string value: new_added_items)
    {
        if (added_items[key] != value)
        {
            remove_item(key);
            add_item(key, value);
            changed = 1;
        }
    }
    foreach (string key, string value: added_items)
    {
        if (!stringp(added_items[key]))
        {
            remove_item(key);
            changed = 1;
        }
    }    
    if (changed)
    {
        tell_room(this_object(), "A bunch of gnomes run in and change the " 
            + "listings on the wall.\n");
    }
    added_items = new_added_items;
 }
 
 public string has_listings()
 {
     if (!m_sizeof(added_items))
         return "";
   return "There are listings on the walls for the various properties for sale.\n";
    
}
     
public void create_room()
 {
    setuid();
    seteuid(getuid());

    set_short("Real estate office");
    set_long("You are standing in the middle of a tidy real estate office " +
        "in Sparkle. A large desk has been pushed up against the southern " +
        "wall, clearly the working space of the real estate agent who " +
        "works here. A silvery haze hangs over an open passage to the " +
        "north with a plaque hanging on the wall beside it. An open " +
        "doorway in the western wall spills out into the middle of " +
        "Sparkle. There is also a notice here that you can read to " +
        "get a better understanding of this office. @@has_listings@@\n");
    set_alarm(1.0, 0.0, update_listings);

    add_exit("/d/Genesis/houses/office", "north", "@@block@@");
    add_exit("/d/Sparkle/area/city/rooms/streets/center_d", "west");

    add_npc(HOUSE_PATH + "sildan");

    add_prop(ROOM_I_INSIDE, 1);

    add_cmd_item("plaque", "read", "@@plaque_desc@@");
    add_cmd_item("notice", "read", "@@notice_desc@@");

    add_item("plaque", "@@plaque_desc@@");
    add_item("notice", "@@notice_desc@@");
    add_item( ({"desk", "large desk", "wooden desk", "wood desk",
            "large wooden desk", "large wood desk"}),
        "There is a large wooden desk nestled up against the southern " +
        "wall, with a comfortable leather chair positioned in such a " +
        "way that the agent who works here can keep an eye on both the " +
        "northern and western entrances. There are tons of papers " +
        "scattered around the table, the details of housing all around " +
        "the donut.\n");
    add_item( ({"chair", "leather chair", "comfortable leather chair",
            "comfortable chair"}),
        "This chair looks quite comfortable, but it is clearly for the " +
        "real estate agent only!\n");
    add_item( ({"paper", "papers", "details", "note", "notes"}),
        "A quick glance is enough to see that the papers on the desk " +
        "keep detailed notes of all the housing in Genesis. You might " +
        "want to ask the agent to see if she can help you out.\n");
    add_item( ({"floor", "ground", "down", "marble", "polished marble"}),
        "A polished marble of white and gold covers the floor of this " +
        "office, with letters fashioned from a dark green stone " +
        "spelling 'Sparkle Real Estate, Established 33 AF'.\n");
    add_item( ({"up", "ceiling", "dome", "domed ceiling", "mosaic"}),
        "The ceiling of this office is domed, with an intricate " +
        "mosaic decorating it with a splash of vibrant colours.\n");
    add_item( ({"wall", "walls"}),
        "The walls of this office have been covered with various " +
        "posters representing house listings. Most of them are old, but " +
        "you might be able to find some current ones if you look.\n");
    add_item( ({"haze", "silvery haze", "silver haze", "north", "passage",
            "north passage", "open passage"}),
        "A silvery haze blocks you from seeing clearly into the open " +
        "passage to the north. From what you can tell, it appears to " +
        "be the private office of some powerful wizard! There is a " +
        "plaque beside the passage that you can read.\n");
    add_item( ({"doorway", "open doorway", "sparkle", "west"}),
        "The village of Sparkle is just a step away!\n");

    room_add_object("/d/Genesis/houses/rboard");
}

string
plaque_desc()
{
    return "\nImmortal Housing Commission\n\n"+
        "Invited guests only! Intruders will be zapped!\n";
}

string
notice_desc()
{
    return
        "Donut Realty\n"+
        "------------\n"+
        "This is the office where houses are listed and sold.\n"+
        "Deeds will be sold to the highest bidder through the\n"+
        "auction house, and when brought to this realtor here\n"+
        "a key will be given for possession.\n\n"+
        "There will be different features for each house. All\n"+
        "of them will have a start room and a secure place to\n"+
        "store a small amount of your possessions. Each house\n"+
        "also has a maid or butler to clean up any items that\n"+
        "are dropped on the floor, so be careful!\n\n"+
        "Guests may be invited in, or even uninvited, only by\n"+
        "the owner of the home. Coffins cannot be stored here\n"+
        "nor can anyone except the owner (or someone in their\n"+
        "team) teleport into the home.\n\n"+
        "A player may own multiple homes, but it is important\n"+
        "to remember that the weekly taxes are cumulative. No\n"+
        "discounts! Taxes will be withdrawn directly from the\n"+
        "bank account of the owner, although, if there is not\n"+
        "enough money to pay the taxes, the home may be taken\n"+
        "away and repossessed.\n\n"+
        "We hope you enjoy home ownership!\n"+
        "Sincerely, the Immortal Housing Commission.\n";
}

int
block()
{
    if (this_player()->query_wiz_level()) return 0;
    write("Only immortals allowed! You can't just go there!\n");
    return 1;
}