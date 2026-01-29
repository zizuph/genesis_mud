
#ifndef WORSHIPPER_DEFS
#define WORSHIPPER_DEFS

#define GUILD_NAME "Elemental Worshippers of Calia"
#define GUILD_TYPE "layman"
#define GUILD_STYLE "cleric"

#define SS_CARVED 114050
#define SS_PUNISHMENT 114051
#define SS_PATRON_ELEMENTAL 114052

#define FIRE_FLAG 1
#define EARTH_FLAG 2
#define AIR_FLAG 4
#define WATER_FLAG 8

#define ALL_FLAGS (AIR_FLAG | FIRE_FLAG | EARTH_FLAG | WATER_FLAG)
#define IS_MEMBER(x)  ((x)->query_guild_name_lay() == GUILD_NAME)

#define GUILD_BASE_TAX 8
#define AIR_TAX_INC 0
#define FIRE_TAX_INC 2
#define WATER_TAX_INC 1
#define EARTH_TAX_INC 2

#define EARTH_OBJECT "worshipper_pentacle"
#define FIRE_OBJECT  "worshipper_wand"
#define AIR_OBJECT   "worshipper_dagger"
#define WATER_OBJECT "worshipper_chalice"

#define DEATH_OBJECT "/d/Calia/worshippers/objects/elemental_punishment"
#define PUNISHER ({"Lord Pyros","Lord Diabrecho","Lady Gu","Lady Aeria"})

#define GUILD_TAX(carved) \
        (GUILD_BASE_TAX + \
        ((carved & AIR_FLAG) ? AIR_TAX_INC : 0) + \
        ((carved & FIRE_FLAG) ? FIRE_TAX_INC : 0) + \
        ((carved & WATER_FLAG) ? WATER_TAX_INC : 0) + \
        ((carved & EARTH_FLAG) ? EARTH_TAX_INC : 0)) 
        

#define DEFAULT_TITLES ({ "Undecided Worshipper of the Elementals" })

#define LEADER_TITLES  ({ "Focus of the Elements" }) 
#define COUNCIL_PYROS_TITLES ({ "Close Servant of Pyros" })
#define COUNCIL_GU_TITLES ({ "Close Servant of Gu" }) 
#define COUNCIL_AERIA_TITLES ({ "Close Servant of Aeria" }) 
#define COUNCIL_DIABRECHO_TITLES ({ "Close Servant of Diabrecho" }) 
#define COUNCIL_DEFAULT_TITLES ({ "Close Servant of the Elementals" }) 

/* Titles by Maniac */ 
#define PYROS_TITLES  \
          ({ "Spark of the Elementals", \
             "Flickering Ember of the Elementals", \
             "Burning Hearth of the Elementals", \
             "Radiant Flare of the Elementals", \
             "Luminous Pyre of the Elementals",  \
             "Intense Fire of the Elementals", \
             "Raging Wildfire of the Elementals", \
             "Blazing Inferno of the Elementals",  \
             "Glorious Blaze of the Elementals", \
             "Devotee of Pyros" }) 

#define DIABRECHO_TITLES  \
          ({ "Raindrop of the Elementals", \
             "Light Rain of the Elementals", \
             "Mountain Stream of the Elementals", \
             "Flowing River of the Elementals", \
             "Crashing Wave of the Elementals", \
             "Whirlpool of the Elementals",  \
             "Monsoon of the Elementals", \
             "Tsunami of the Elementals", \
             "Great Sea of the Elementals", \
             "Devotee of Diabrecho" }) 

#define AERIA_TITLES \
          ({ "Breeze of the Elementals", \
             "Spring Air of the Elementals", \
             "Blue Sky of the Elementals", \
             "Gust of the Elementals", \
             "Gale of the Elementals", \
             "Whirlwind of the Elementals", \
             "Wildwind of the Elementals", \
             "Tornado of the Elementals", \
             "Hurricane of the Elementals", \
             "Devotee of Aeria" })

#define GU_TITLES \
          ({ "Pebble of the Elementals", \
             "Grey Stone of the Elementals", \
             "White Quartz of the Elementals", \
             "Icy Silver of the Elementals", \
             "Glittering Gold of the Elementals", \
             "Shining Platinum of the Elementals", \
             "Deep Sapphire of the Elementals", \
             "Red Ruby of the Elementals", \
             "Eternal Diamond of the Elementals", \
             "Devotee of Gu" }) 

#define OCCTITLE ""

#define WOR_VALID_CALL ([ "help" : "Help!", \
                          "greetings" :  "Greetings!", \
                          "welcome" : "Welcome!", \
                             "bye" : "Farewell!", \
                          "farewell" : "Farewell!" ]) 

#define MEMBER_LIST_UTILITY "/d/Calia/guilds/scop/specials/member_list_utility"

#endif
