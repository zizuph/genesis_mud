/* 
 * The Minstrel Performance Manager Object
 *
 * This manager will take care of the member data. It will only return info
 * for real players, not npcs.
 *
 * Created by Arman October 2019
 *
 * Revisions:
 *     Lilith May 2022: Added more establishments to the list.
 */

#pragma strict_types

#include <files.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include <time.h>
#include "/d/Terel/common/terel_defs.h"
#include "../guild_defs.h"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public mapping      cached_player_info = ([ ]);
public mapping      cached_song_info = ([ ]);
public mapping      cached_venue_info = ([ ]);

// Ranking decays after not being performed or decayed for a week
#define RANKING_DECAY_TIME 604800

#define PERFORMANCE_LOG (MINSTREL_LOG + "performance_log")

 
// Prototypes


// The create function is called for every object. We mask it here
// to do some basic initialization for the handler

void
create()
{
    setuid();
    seteuid(getuid());
}

/*
 * Function:    get_id
 * Description: Get the real name of the player string or object passed.
 *              It's just a convenience function so that the right answer
 *              is given without checking object types in the calling
 *              code.
 */
public string
get_id(mixed player)
{
    string name;
    
    if (stringp(player) && strlen(player))
    {
        name = player;
    }
    else if (objectp(player) && IS_PLAYER_OBJECT(player))
    {
        name = player->query_real_name();
    }    
    
    return name;
}

/* 
 * Function:    load_player_info
 * Description: This loads the player info from their specific file
 *              and returns the mapping of it.
 */
public mapping
load_player_info(mixed player)
{
    string name;
    mapping player_info;
    
    name = get_id(player);
    if (!strlen(name))
    {
        return ([ ]);
    }
    
    if (cached_player_info[name])
    {
        return cached_player_info[name];
    }
    
    if (!SECURITY->exist_player(name))
    {
        return ([ ]);
    }
    
    player_info = ([ ]);
        
    // Look for the file
    if (file_size(MINSTREL_DATA + name + ".o") >= 0)
    {
        player_info = restore_map(MINSTREL_DATA + name);
    }

    // Add the value to the cache
    cached_player_info[name] = player_info;
    return player_info;
}

/* 
 * Function:    query_player_property
 * Description: Generic function to return values from the
 *              manager mapping. This will be used by all
 *              customized getters
 */
public mixed
query_player_property(mixed player, string prop)
{
    mapping player_info = load_player_info(player);
    
    return player_info[prop];    
}

/*
 * Function:    set_player_property
 * Description: Generic function to set the values for a player in
 *              the manager mapping. This will be used by all customized
 *              setters
 */
public string
set_player_property(mixed player, string prop, mixed value)
{
    mapping player_info = load_player_info(player);
    string name = get_id(player);
    
    if (value)
    {
        player_info[prop] = value;
    }
    else
    {
        m_delkey(player_info, prop);
    }
    
    cached_player_info[name] = player_info;
    save_map(player_info, MINSTREL_DATA + name);    
    return name;
}

/* 
 * Function:    load_song_info
 * Description: This loads the song info from their specific file
 *              and returns the mapping of it.
 */
public mapping
load_song_info()
{
    mapping song_info;    
        
    song_info = ([ ]);
        
    // Look for the file
    if (file_size(MINSTREL_DATA + "minstrel_song_data.o") >= 0)
    {
        song_info = restore_map(MINSTREL_DATA + "minstrel_song_data");
    }

    // Add the value to the cache
    cached_song_info["minstrel_song_data"] = song_info;
    return song_info;
}

/* 
 * Function:    query_song_property
 * Description: Generic function to return values from the
 *              manager mapping. This will be used by all
 *              customized getters
 */
public mixed
query_song_property(string prop)
{
    mapping song_info = load_song_info();
    
    return song_info[prop];    
}

/*
 * Function:    set_song_property
 * Description: Generic function to set the values in
 *              the manager mapping. This will be used by all customized
 *              setters
 */
public string
set_song_property(string prop, mixed value)
{
    mapping song_info = load_song_info();
    
    if (value)
    {
        song_info[prop] = value;
    }
    else
    {
        m_delkey(song_info, prop);
    }
    
    cached_song_info["minstrel_song_data"] = song_info;
    save_map(song_info, MINSTREL_DATA + "minstrel_song_data");    
    return "minstrel_song_data";
}

/* 
 * Function:    load_venue_info
 * Description: This loads the venue info from their specific file
 *              and returns the mapping of it.
 */
public mapping
load_venue_info()
{
    mapping venue_info;    
        
    venue_info = ([ ]);
        
    // Look for the file
    if (file_size(MINSTREL_DATA + "minstrel_venue_data.o") >= 0)
    {
        venue_info = restore_map(MINSTREL_DATA + "minstrel_venue_data");
    }

    // Add the value to the cache
    cached_venue_info["minstrel_venue_data"] = venue_info;
    return venue_info;
}

/* 
 * Function:    query_venue_property
 * Description: Generic function to return values from the
 *              manager mapping. This will be used by all
 *              customized getters
 */
public mixed
query_venue_property(string prop)
{
    mapping venue_info = load_venue_info();
    
    return venue_info[prop];    
}

/*
 * Function:    set_venue_property
 * Description: Generic function to set the values in
 *              the manager mapping. This will be used by all customized
 *              setters
 */
public string
set_venue_property(string prop, mixed value)
{
    mapping venue_info = load_venue_info();
    
    if (value)
    {
        venue_info[prop] = value;
    }
    else
    {
        m_delkey(venue_info, prop);
    }
    
    cached_venue_info["minstrel_venue_data"] = venue_info;
    save_map(venue_info, MINSTREL_DATA + "minstrel_venue_data");    
    return "minstrel_venue_data";
}


/*=====================
 * MEMBERSHIP FUNCTIONS
 ======================*/
public void
add_member(mixed player)
{
    if(player->query_npc())
        return;

    string player_name = set_player_property(player, "is_member", 1);
    send_debug_message("minclub", capitalize(player_name)
        + " has become a performer.", PERFORMANCE_LOG);
}

public int
query_is_member(mixed player)
{    
    return query_player_property(player, "is_member");
}

public void
remove_member(mixed player)
{
    string player_name = set_player_property(player, "is_member", 0);
    send_debug_message("minclub", capitalize(player_name)
        + " is no longer a performer.", PERFORMANCE_LOG);    
}


public string *
query_members()
{
    string * files = get_dir(MINSTREL_DATA);
    string * members = ({ });
    
    foreach (string file : files)
    {
        if (!wildmatch("*.o", file))
        {
            continue;
        }
        
        string name = file[..-3];
        if (query_is_member(name))
        {
            members += ({ name });
        }
    }
    
    return members;
}

/*===========================================
 *          MOOD FUNCTIONS
 ============================================*/

public string *
query_mood_excluded_verbs(mixed player)
{   
    string * list = query_player_property(player, "mood_excluded_verbs");

    if(!sizeof(list))
        list = ({ });

    return list;
}

public void
add_mood_excluded_verbs(object player, string verb)
{
    string * list = query_mood_excluded_verbs(player);
    verb = lower_case(verb);

    if(member_array(verb, list) != -1)
        return 0;

    list += ({ verb });

    set_player_property(player, "mood_excluded_verbs", list);
}

public void
remove_mood_excluded_verbs(object player, string verb)
{
    string * list = query_mood_excluded_verbs(player);
    verb = lower_case(verb);

    if(member_array(verb, list) == -1)
        return 0;

    list -= ({ verb });

    set_player_property(player, "mood_excluded_verbs", list);
}

public void
clear_mood_excluded_verbs(object player)
{
    string * list = ({  });

    set_player_property(player, "mood_excluded_verbs", list);
}


/*===========================================
 *          REPUTATION TITLE FUNCTIONS
 ============================================*/

public void
set_reputation_level(object player, int level)
{
    set_player_property(player, "reputation_level", level);
}

public void
increase_reputation_level(object player, int inc)
{
    int level = query_player_property(player, "reputation_level");

    if(level)
    {
        level = level + inc;
        set_player_property(player, "reputation_level", level);
        return;
    }

    set_player_property(player, "reputation_level", inc);    
}

public void
decrease_reputation_level(object player, int dec)
{
    int level = query_player_property(player, "reputation_level");

    if(level)
    {
        level = level - dec;

        if(level < 0)
            level = 0;

        set_player_property(player, "reputation_level", level);
        return;
    }

    set_player_property(player, "reputation_level", 0);    
}

public int
query_reputation_level(mixed player)
{    
    int level = query_player_property(player, "reputation_level");
    if(level)
        return level;
    
    return 0;
}

public void
remove_reputation_level(object player)
{
    set_player_property(player, "reputation_level", 0);
}

public string
query_reputation_level_desc(mixed player)
{    
    int level = query_player_property(player, "reputation_level");

    if(level > 20)
        level = 20;
    if(level < 0)
        level = 0;

    switch (level)
    {
    case 0:
        return "unsung";
        break;
    case 1:
        return "accepted";
        break;
    case 2:
        return "known";
        break;
    case 3:
        return "noted";
        break;
    case 4:
        return "established";
        break;
    case 5:
        return "liked";
        break;
    case 6:
        return "well-known";
        break;
    case 7:
        return "admired";
        break;
    case 8:
        return "prominent";
        break;
    case 9:
        return "distinguished";
        break;
    case 10:
        return "popular";
        break;
    case 11:
        return "reputable";
        break;
    case 12:
        return "honored";
        break;
    case 13:
        return "celebrated";
        break;
    case 14:
        return "illustrious";
        break;
    case 15:
        return "eminent";
        break;
    case 16:
        return "acclaimed";
        break;
    case 17:
        return "prestigious";
        break;
    case 18:
/*
        if(player->query_alignment() < 0)
            return "infamous";
        else
*/
            return "famous";
        break;
    case 19:
        return "renowned";
        break;
    case 20:
        return "revered";
        break;
    }   
 
    return 0;
}

/*===========================================
 *          CROWD REACTIONS
 ============================================*/

public void
damage_instrument(mixed player)
{
    object instrument = present("minstrel_instrument", player);
    string inst_str;

    if(!objectp(instrument))
        return;

    inst_str = instrument->short();

    player->catch_tell("You notice you've damaged your " +inst_str+
        " during your performance!\n");
    instrument->set_damage(1);

}

public string *
query_crowd_reaction(mixed player)
{   
    string * reaction; 

    int level = (player->query_skill(SG_VOCAL) + 
        player->query_skill(SG_INSTRUMENTAL)) / 2;

    // For club members the reaction range is random
    if(!MEMBER(player))
    {

        // Branchalla is the Krynn god of music, so members
        // get a reaction bonus
        if(player->query_guild_member("Holy Order of the Stars") &&
            (player->query_oots_god() == "Branchalla"))
        {
            level = 20 + random(50);
        }
        else
        {
            level = random(60);
        }
        // DEBUG("Performance level: " +level+ ".");

    }

    int instrument_damage;
    instrument_damage = present("minstrel_instrument", 
        player)->query_damage();

    if(instrument_damage)
        level = level / instrument_damage;

    switch (level)
    {
    case 0..15: 
        reaction = ({ " boo your performance loudly!", 
                      " boo " +player->query_the_possessive_name(player)+
                      " performance loudly!" });
        break;
    case 16..30:
        reaction = ({ " barely acknowledge your performance.", 
                      " barely acknowledge " +QTPNAME(player)+
                      " performance." });
        break;
    case 31..50:
        reaction = ({ " politely clap your performance.", 
                      " politely clap " 
                      +player->query_the_possessive_name(player)+
                      " performance." });
        break;
    case 51..70:
        reaction = ({ " heartily cheer your performance!", 
                      " heartily cheer " 
                      +player->query_the_possessive_name(player)+
                      " performance!" });
        break;
    case 71..90:
        reaction = ({ " applaud your performance loudly!", 
                      " applaud " 
                      +player->query_the_possessive_name(player)+
                      " performance loudly!" });
        break;
    default: 
        reaction = ({ " erupt to their feet in roaring " +
                      "applause, calling for an encore!", 
                      " erupt to their feet in roaring " +
                      "applause, calling for an encore!" });
        break;
    } 

    // 5% chance of damaging your instrument per performance
    if(random(100) < 5)
        damage_instrument(player);  

    return reaction;
}

public int
query_crowd_score(mixed player)
{   
    int reaction; 

    int level = (player->query_skill(SG_VOCAL) + 
        player->query_skill(SG_INSTRUMENTAL)) / 2;

    // For club members the reaction range is random
    if(!MEMBER(player))
    {
        int rep_level = query_player_property(player, "reputation_level");

        // Branchalla is the Krynn god of music, so members
        // get a reaction bonus
        if(player->query_guild_member("Holy Order of the Stars") &&
            (player->query_oots_god() == "Branchalla"))
        {
            level = max(rep_level, (20 + random(50)));
        }
        else
        {
            level = max(rep_level, random(60));
        }
        // DEBUG("Performance level: " +level+ ".");

    }

    int instrument_damage;
    instrument_damage = present("minstrel_instrument", 
        player)->query_damage();

    if(instrument_damage)
        level = level / instrument_damage;

    switch (level)
    {
    case 0..15: 
        reaction = 1;
        break;
    case 16..30:
        reaction = 2;
        break;
    case 31..50:
        reaction = 3;
        break;
    case 51..70:
        reaction = 4;
        break;
    case 71..90:
        reaction = 5;
        break;
    default: 
        reaction = 6;
        break;
    }   

    return reaction;
}

public void
set_visited_telberin_guild(object player, int level)
{
    set_player_property(player, "visited_telberin_guild", level);
}

public int
query_visited_telberin_guild(object player)
{
    int level = query_player_property(player, "visited_telberin_guild");

    if(level)
        return level;
    
    return 0;
}

/*===========================================
 *     PERFORMANCE LOCATION FUNCTIONS
 ============================================*/

public int
query_perform_location(mixed player)
{ 
    string location = file_name(environment(player));

    switch(location)
    {

    // Drinking Holes
    case "/d/Ansalon/balifor/flotsam/room/tavern01":
    case "/d/Ansalon/balifor/flotsam/room/tavern02":
    case "/d/Ansalon/kalaman/caravan/inside":
    case "/d/Ansalon/taman_busuk/sanction/room/city/tavern":
    case "/d/Ansalon/taman_busuk/neraka/outer/blue/pub1":
    case "/d/Ansalon/taman_busuk/neraka/outer/red/pub1":
    case "/d/Ansalon/taman_busuk/neraka/outer/green/bar1":
    case "/d/Ansalon/taman_busuk/neraka/outer/black/inn":
    case "/d/Calia/sea/beach/village2":
    case "/d/Earthsea/gont/tenalders/village/pub_room":
    case "/d/Earthsea/gont/gont_city/rooms/tavern":
    case "/d/Earthsea/roke/thwil/pub":
    case "/d/Faerun/halflings/rooms/inn":
    case "/d/Genesis/start/dwarf/lvl3/pub":
    case "/d/Genesis/start/hobbit/v/pub":
    case "/d/Gondor/rohan/edoras/stallion":
    case "/d/Gondor/rohan/edoras/pspub":
    case "/d/Gondor/morgul/city/rooms/inn":
    case "/d/Gondor/morgul/city/rooms/pub":
    case "/d/Kalad/common/port/s60":
    case "/d/Khalakhor/inisi/roke/nyreese/cadu_inn":
    case "/d/Khalakhor/inisi/roke/nyreese/red_pub":
    case "/d/Khalakhor/se_speir/claryn/tabor/room/pub":
    case "/d/Khalakhor/sw_speir/samorgan/room/pub":
    case "/d/Krynn/turbidus_ocean/room/tavern":
    case "/d/Terel/mortricia/camp/tent_pub":
    case "/d/Terel/last/snowhouse":
    case "/d/Terel/ribos/inn":
    case "/d/Terel/dabaay/town/stumble":
    case "/d/Terel/last/whdragon":
    case "/d/Shire/guild/AA/rooms/pub":
    case "/d/Shire/longbottom/rooms/inn":
    case "/d/Sparkle/area/goblin_caves/rooms/level2/roomf4":
        return 1;
        break;

    // Small Pubs or Small Inns
    case "/d/Ansalon/goodlund/kendermore/room/inn01":
    case "/d/Ansalon/balifor/flotsam/room/inn02":
    case "/d/Ansalon/balifor/port_balifor/room/inn":
    case "/d/Ansalon/taman_busuk/sanction/room/city/inn":
    case "/d/Ansalon/taman_busuk/neraka/inner/inn1":
    case "/d/Ansalon/taman_busuk/neraka/inner/pub1":
    case "/d/Ansalon/estwilde/iron_delving/tavern":
    case "/d/Avenir/common/port/pub":
    case "/d/Avenir/common/outpost/fort4":
    case "/d/Calia/argos/metro/rooms/pub":
    case "/d/Calia/argos/metro/rooms/inn":
    case "/d/Cirath/tyr/market/hhh":
    case "/d/Cirath/tyr/caravan/innlobby":
    case "/d/Gondor/minas/rooms/wtpub":
    case "/d/Gondor/lebennin/thornlin/tavern":
    case "/d/Gondor/pelargir/misc/sailor_pub":
    case "/d/Gondor/minas/rooms/old_guesthouse":
    case "/d/Gondor/minas/rooms/mttavern":
    case "/d/Khalakhor/se_speir/port/room/pub":
    case "/d/Kalad/common/caravan/shop/jeinn":
    case "/d/Krynn/solamn/palanthas/merchants/green_twitch":
    case "/d/Krynn/solamn/palanthas/nobles/best_cafe":
    case "/d/Krynn/neraka/tent4":
    case "/d/Krynn/solace/new_village/inn":
    case "/d/Shire/frogmorton/inn":
    case "/d/Shire/eastroad/western/villages/greenholm/inn":
    case "/d/Shire/eastroad/western/foam_mug":
    case "/d/Shire/eastroad/western/stone_inn":
    case "/d/Shire/sarnford/inn":
    case "/d/Sparkle/area/faerie/rooms/greenoaks/pub":
    case "/d/Sparkle/area/city/rooms/inside/inn":
    case "/d/Shire/eastroad/western/foam_mug_2020":
    case "/d/Terel/calathin/pubs/big_pub":
    case "/d/Terel/calathin/inns/inn_main":
    case "/d/Terel/calathin/pubs/cal_inn":
    case "/d/Terel/calathin/pubs/drag_pub":
        return 2;
        break;

    // Large Pubs, Large Inns, prominent establishments
    case "/d/Avenir/common/bazaar/intr/pub":
    case "/d/Avenir/common/bazaar/museum/center":
    case "/d/Calia/gelan/rooms/inn":
    case "/d/Gondor/minas/rooms/wtpub":
    case "/d/Gondor/minas/rooms/wtpub":
    case "/d/Kalad/common/noble/pub":
    case "/d/Kalad/common/wild/pass/drow/shop/pub":
    case "/d/Khalakhor/se_speir/lohrayn/ashlagh/room/pub":
    case "/d/Krynn/guilds/knights/guildhall/rooms/inn":
    case "/d/Krynn/neraka/tent9":
    case "/d/Krynn/solamn/palanthas/merchants/inn1":
    case "/d/Raumdor/common/drakmere/shop/inn":
    case "/d/Shire/bree/rooms/town/innfront":
    case "/d/Sparkle/area/city/rooms/inside/sparkle_pub":
    case "/d/Shire/bree/rooms/town/innfront":
    case "/d/Terel/calathin/playhouse":
        return 3;
        break;

    default: 
        return 0;
        break;
    }
    
    return 0;
}

public string
query_perform_location_name(mixed player)
{ 
    string location = file_name(environment(player));
    string alt_loc;

    switch(location)
    {
    case "/d/Krynn/turbidus_ocean/room/tavern": 
        return "Reefcutter's Tavern";
        break;
    case "/d/Ansalon/balifor/flotsam/room/tavern01": 
        return "Hawkstone's Taproom";
        break;
    case "/d/Ansalon/kalaman/caravan/inside": 
        return "the Giant Skull Tavern";
        break;
    case "/d/Ansalon/balifor/flotsam/room/tavern02": 
        return "the Tanked Troll";
        break;
    case "/d/Ansalon/taman_busuk/sanction/room/city/tavern": 
        return "the Lords of Doom Tavern";
        break;
    case "/d/Ansalon/taman_busuk/neraka/outer/blue/pub1": 
        return "the Hanged Knight Pub";
        break;
    case "/d/Ansalon/taman_busuk/neraka/outer/red/pub1": 
        return "the Little Red Rooster";
        break;
    case "/d/Ansalon/taman_busuk/neraka/outer/green/bar1": 
        return "the Queen's Heads Bar";
        break;
    case "/d/Ansalon/taman_busuk/neraka/outer/black/inn":
        return "the Black Ship Inn";
        break;
    case "/d/Krynn/solamn/palanthas/merchants/green_twitch":
        return "the Green Twitch Inn";
        break;
    case "/d/Ansalon/estwilde/iron_delving/tavern":
        return "the Tavern of Iron Delving";
        break;
    case "/d/Krynn/solamn/palanthas/nobles/best_cafe":
        return "the Mer-Cantile cafe";
        break;
    case "/d/Krynn/neraka/tent4":
        return "the Guardians Pub";
        break;
    case "/d/Krynn/solace/new_village/inn":
        return "the Inn of The Last Home";
        break;
    case "/d/Ansalon/goodlund/kendermore/room/inn01":
        return "the Scorched Scorpion Inn";
        break;
    case "/d/Ansalon/balifor/flotsam/room/inn02":
        return "the Saltbreeze Inn";
        break;
    case "/d/Ansalon/balifor/port_balifor/room/inn":
        return "the Pig and Whistle Inn";
        break;
    case "/d/Ansalon/taman_busuk/neraka/inner/inn1":
        return "the Swan and Hedgehog Inn";
        break;
    case "/d/Ansalon/taman_busuk/neraka/inner/pub1":
        return "the Red Dragon Tavern";
        break;
    case "/d/Krynn/guilds/knights/guildhall/rooms/inn":
        return "the Bronze Dragon Inn";
        break;
    case "/d/Krynn/neraka/tent9":
        return "the Templar Bar";
        break;
    case "/d/Krynn/solamn/palanthas/merchants/inn1":
        return "the Silver Dragon Inn";
        break;
    case "/d/Gondor/rohan/edoras/pspub":
        return "the Proud Stag Pub";
        break;
    case "/d/Gondor/minas/rooms/wtpub":
        return "the White Tree Pub";
        break;
    case "/d/Gondor/lebennin/thornlin/tavern":
        return "the Man in the Moon Public House";
        break;
    case "/d/Gondor/pelargir/misc/sailor_pub":
        return "the Broken Oar Tavern";
        break;
    case "/d/Shire/frogmorton/inn":
        return "the Floating Log Inn";
        break;
    case "/d/Shire/eastroad/western/villages/greenholm/inn":
        return "the Bounder Inn";
        break;
    case "/d/Shire/eastroad/western/foam_mug":
        return "the Foaming Mug Inn";
        break;
    case "/d/Shire/eastroad/western/foam_mug_2020":
        return "the Foaming Mug Inn";
        break;
    case "/d/Genesis/start/hobbit/v/pub":
        return "the Green Dragon";
        break;
    case "/d/Shire/eastroad/western/stone_inn":
        return "Stonebows Inn";
        break;
    case "/d/Gondor/minas/rooms/mttavern":
        return "the Sword and Shield Tavern";
        break;
    case "/d/Gondor/minas/rooms/wtpub":
        return "the White Tree Pub";
        break;
    case "/d/Shire/bree/rooms/town/innfront":
        return "the Prancing Pony";
        break;
    case "/d/Shire/sarnford/inn":
        return "the Sleeping Fisherman";
        break;
    case "/d/Gondor/morgul/city/rooms/inn":
        return "the Red Eye Inn";
        break;
    case "/d/Gondor/morgul/city/rooms/pub":
        return "the Dead Tark Pub";
        break;
    case "/d/Shire/guild/AA/rooms/pub":
        return "the Army Pub";
        break;
    case "/d/Shire/longbottom/rooms/inn":
        return "the Silver Tree Inn";
        break;
    case "/d/Sparkle/area/faerie/rooms/greenoaks/pub":
        return "the Pub of Green Oaks";
        break;
    case "/d/Sparkle/area/city/rooms/inside/sparkle_pub":
        return "the Boar's Head Tavern";
        break;
    case "/d/Sparkle/area/city/rooms/inside/inn":
        return "the Silver Swan Inn";
        break;
    case "/d/Genesis/start/dwarf/lvl3/pub":
        return "the Staggering Dwarf";
        break;
    case "/d/Sparkle/area/goblin_caves/rooms/level2/roomf4":
        return "the Broken Mug Tavern";
        break;
    case "/d/Terel/mortricia/camp/tent_pub":
        return "the Gypsy Pub";
        break;
    case "/d/Terel/calathin/pubs/big_pub":
        return "the Big Rock Pub";
        break;
    case "/d/Terel/calathin/inns/inn_main":
        return "the Silver Tree Inn";
        break;
    case "/d/Terel/calathin/pubs/cal_inn":
        return "the Inn of Calathin";
        break;
    case "/d/Terel/last/snowhouse":
        return "Snowhouse Tavern";
        break;
    case "/d/Terel/ribos/inn":
        return "the Ribos Inn";
        break;
    case "/d/Terel/dabaay/town/stumble":
        return "Stumble Inn";
        break;
    case "/d/Terel/last/whdragon":
        return "the White Dragon Inn";
        break;
    case "/d/Avenir/common/port/pub":
        return "the Stormy Haven Inn and Pub";
        break;
    case "/d/Terel/calathin/pubs/drag_pub":
        return "the Dragon Claw Pub";
        break;
    case "/d/Avenir/common/bazaar/museum/center":
        return "Goatfeather's Cafe";
        break;
    case "/d/Avenir/common/bazaar/intr/pub":
        return "Icky Bod's Pub and Club";
        break;
    case "/d/Calia/argos/metro/rooms/pub":
        return "the Ouzophilos Pub";
        break;
    case "/d/Calia/argos/metro/rooms/inn":
        return "Theros Inn";
        break;
    case "/d/Calia/gelan/rooms/inn":
        return "the Calian Inn of Gelan";
        break;
    case "/d/Calia/sea/beach/village2":
        return "the Leaping Dolphin Tavern";
        break;
    case "/d/Earthsea/gont/tenalders/village/pub_room":
        return "the Randy Goat Pub";
        break;
    case "/d/Earthsea/gont/gont_city/rooms/tavern":
        return "the Seaside Tavern";
        break;
    case "/d/Faerun/halflings/rooms/inn":
        return "the Jolly Rancher Inn";
        break;
    case "/d/Kalad/common/noble/pub":
        return "the Royal Pub";
        break;
    case "/d/Kalad/common/caravan/shop/jeinn":
        return "Journey's End Inn";
        break;
    case "/d/Kalad/common/port/s60":
        return "the Liquid Booty Tavern";
        break;
    case "/d/Kalad/common/wild/pass/drow/shop/pub":
        return "the Drow Drinking Pit";
        break;
    case "/d/Cirath/tyr/market/hhh":
        return "the Inn of the Hungry Hungry Halfling";
        break;
    case "/d/Cirath/tyr/caravan/innlobby":
        return "the Golden Inix Inn";
        break;
    case "/d/Raumdor/common/drakmere/shop/inn":
        return "the Bloody Skull Inn";
        break;
    case "/d/Earthsea/roke/thwil/pub":
        return "the Wizard's Pub";
        break;
    case "/d/Khalakhor/inisi/roke/nyreese/cadu_inn":
        return "the Fisherman's Friend Inn";
        break;
    case "/d/Khalakhor/inisi/roke/nyreese/red_pub":
        return "Sloppy Joe's Pub";
        break;
    case "/d/Khalakhor/se_speir/port/room/pub":
        return "the Wild Rover";
        break;
    case "/d/Khalakhor/se_speir/claryn/tabor/room/pub":
        return "the Summer Squall";
        break;
    case "/d/Khalakhor/sw_speir/samorgan/room/pub":
        return "SaKeller's Tavern";
        break;
    case "/d/Khalakhor/se_speir/lohrayn/ashlagh/room/pub":
        return "the Taigh Leann";
        break;
    }

    alt_loc = lower_case(environment(player)->short());
    
    return alt_loc;
}

public string
query_patron_familiarity(mixed player)
{ 
    string location = file_name(environment(player));
    int local_rep = PERFORM_MANAGER->query_venue_level(player, location);

    switch(local_rep)
    {
    case 0: 
        return "unfamiliar";
        break;
    case 1..5:
        return "new";
        break;
    case 6..15:
        return "regular";
        break;
    case 16..25:
        return "frequent";
        break;
    case 26..49:
        return "very frequent";
        break;
    default:
        return "established local";
        break;
    }
    
    return "buggy";
}

/*===========================================
 *          MINSTREL STATS FUNCTIONS
 ============================================*/

public void
set_venue_level(object player, string location, int level)
{
    set_player_property(player, location, level);
}

public int
query_venue_level(mixed player, string location)
{    
    int level = query_player_property(player, location);

    if(level)
        return level;
    
    return 0;
}

public void
increase_venue_level(object player, string location, int inc)
{
    int level = query_player_property(player, location);

    if(level)
    {
        level = level + inc;
        set_player_property(player, location, level);
        return;
    }

    set_player_property(player, location, inc);    
}

public void
decrease_venue_level(object player, string location, int dec)
{
    int level = query_player_property(player, location);

    if(level)
    {
        level = level - dec;

        if(level < 0)
            level = 0;

        set_player_property(player, location, level);
        return;
    }

    set_player_property(player, location, 0);    
}

public void
remove_venue_level(object player, string location)
{
    set_player_property(player, location, 0);
}


/*===========================================
 *          PERFORMANCE FORMULAS
 ============================================*/
/*
 * Chance based on:
 *     current reputation title 
 *     Establishment level
 *     singing and playing skills, and 
 *     local reputation (number of times performed
 *     there before).
 *
 * Location sizes are an int between 1 and 3:
 *    1. Drinking Hole (MINOR_LOC)
 *    2. Small Pub / Small Inn (AVERAGE_LOC)
 *    3. Large Pub / Large Inn (PROMINENT_LOC)
 *
 * INCREASE IF:
 *    random(100 * establishment level) + singing + 
 *    performing  >  
 *    (current title * 10) + (random 300)
 *
 */

public int
check_performance_chance(mixed player, int loc_size)
{
    int chance;
    string location = file_name(environment(player));
    int local_rep = min(50, query_venue_level(player, location));

    int level = query_player_property(player, "reputation_level");

    chance = ((random(100) * loc_size) + player->query_skill(SG_VOCAL) +
        player->query_skill(SG_INSTRUMENTAL) + local_rep);

    // DEBUG("Chance for " +player->query_real_name()+ ": " +chance+ ".");

    return chance;   
}

public int
check_performance_difficulty(mixed player)
{
    int difficulty;

    int level = query_player_property(player, "reputation_level");

    difficulty = (level * 10) + random(300);

    // DEBUG("Difficulty for " +player->query_real_name()+ ": " +difficulty+ ".");

    return difficulty;   
}

public int
check_reputation_increase(mixed player, int loc_size, int chance, int difficulty)
{    
    int level = query_player_property(player, "reputation_level");

    if(level == 20)
        return 0;
    
    if(chance > difficulty)
    {
        increase_reputation_level(player, 1);
        player->catch_tell("Your reputation as a performer has " +
            "increased!\n");
        tell_room(environment(player), QCTPNAME(player)+ 
            " reputation as a performer has increased!\n", ({ player }));
        return 1;
    }
    
    return 0;
}


/*===========================================
 *          MINSTREL SONG FUNCTIONS
 ============================================*/

public mapping
query_top_minstrel_mundanes()
{ 
    mixed list = query_song_property("top_minstrel_mundanes");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_minstrel_mundane(string song, int score, int last_performed)
{
    mapping list = query_top_minstrel_mundanes();
    
    if (!m_sizeof(list) || !member_array(song, m_indexes(list)) > -1)
        list += ([ song : ({ score, last_performed }) ]);
    
    set_song_property("top_minstrel_mundanes", list);
}

public void
remove_minstrel_mundane(string song)
{
    mapping list = query_top_minstrel_mundanes();
    
    if (m_sizeof(list) && member_array(song, m_indexes(list)) > -1)
        m_delkey(list, song);
    
    set_song_property("top_minstrel_mundanes", list);
}

public void
increase_minstrel_mundane(string song, int score, int last_performed)
{
    mapping list = query_top_minstrel_mundanes();
    
    if (!m_sizeof(list))
    {
        list += ([ song : ({ score, last_performed }) ]);
    }
    else if (member_array(song, m_indexes(list)) == -1)
    {
        list += ([ song : ({ score, last_performed }) ]);
    }
    else
    {
        int new_score = list[song][0] + score;        
        list += ([ song : ({ new_score, last_performed }) ]);
    }

    set_song_property("top_minstrel_mundanes", list);
}

public string
check_song_last_performed(string type, string song)
{
    mapping list;
    int last_performed;

    if(type == "mundane")
        list = query_top_minstrel_mundanes();
    else
        return "No such song type to check.\n";

    if (member_array(song, m_indexes(list)) == -1)
        return "No " +type+ " of that name has been performed.\n";

    last_performed = list[song][1];

    return TIME2FORMAT(last_performed, "d mmm yyyy");
}

// This function checks whether a song's ranking should decay or
// not due to lack of performance.
public int
check_for_song_ranking_decay(string song)
{
    mapping list = query_top_minstrel_mundanes();
    int last_performed;

    if (member_array(song, m_indexes(list)) == -1)
        return 0;

    last_performed = list[song][1];

    if(time() > (last_performed + RANKING_DECAY_TIME))
        return 1;
    else
        return 0;    

}

// Checks whether a song hasn't been played recently and decays
// in public rankings. This function is called in ~performance_obj.c

public void
master_song_ranking_decay()
{
    mapping list = query_top_minstrel_mundanes();

    if (!m_sizeof(list))
    {
        return;
    }

    foreach(string song, int * array: list)
    {
        if(check_for_song_ranking_decay(song))
        {
            // DEBUG("Decay called in master for " +song+ ".");
            // Every week of non-performance a song decays in
            // ranking points by 20%
            int score = ftoi(itof(array[0]) * 0.8);
            // DEBUG("Old score: " +array[0]+ ", new score: " +score+ ".");
            int last_performed = time();
            list += ([ song : ({ score, last_performed }) ]);
            set_song_property("top_minstrel_mundanes", list);

            // If the song decays to single digit score, remove it.
            if(array[0] == 1)
            {
                remove_minstrel_mundane(song);
                // DEBUG("Remove song called in master for " +song+ ".");
                set_song_property("top_minstrel_mundanes", list);                
            }
        }
    }

    return;
}


/*===========================================
 *          JOIN RESTRICTION FUNCTIONS
 ============================================*/

public void
add_join_restricted(object player)
{
    // By default, restricts for 3 days
    int last_ban = query_player_property(player, "join_restricted");
    int new_ban;
    if (last_ban <= time())
    {
        new_ban = time() + (3 * 86400);
    }
    else
    {
        new_ban = last_ban + (3 * 86400);
    }
    string player_name = set_player_property(player, "join_restricted", new_ban);
    send_debug_message("minclub", capitalize(player_name)
        + " has been restricted from joining until " + ctime(new_ban), PERFORMANCE_LOG);        
}

public int
is_join_restricted(object player)
{
    int ban_expiration = query_player_property(player, "join_restricted");
    if (ban_expiration >= time())
    {
        return 1;
    }
    
    return 0;
}

public void
remove_join_restricted(object player)
{
    set_player_property(player, "join_restricted", 0);
}
