/*
 * Quest bits and info for Faerun quests
 * -- Finwe, August 2006
 */

#define DOMAIN              "faerun"
#define GROUP0              0
#define GROUP1              1
#define GROUP2              2
#define GROUP3              3
#define GROUP4              4

#define EGG_QUEST_GROUP     GROUP1
#define EGG_QUEST_BIT       1
#define EGG_QUEST_EXP       1200
#define EGG_QUEST_LNG       "Collect eggs for farmer"
#define EGG_QUEST_SHT       "Egg quest"

#define FLOWER_QUEST_GROUP  GROUP1
#define FLOWER_QUEST_BIT    2
#define FLOWER_QUEST_EXP    1100
#define FLOWER_QUEST_LNG    "Find flower for farmer"
#define FLOWER_QUEST_SHT    "Flower quest"

#define FRUIT_QUEST_GROUP   GROUP1  
#define FRUIT_QUEST_BIT     3
#define FRUIT_QUEST_EXP     2500
#define FRUIT_QUEST_LNG     "Get fruit for farmer's daughter"
#define FRUIT_QUEST_SHT     "Fruit quest"

#define CITADEL_QUEST_GROUP GROUP1  
#define CITADEL_QUEST_BIT   4
#define CITADEL_QUEST_EXP   30000 
#define CITADEL_QUEST_LNG   "Cleanse citadel of insects"
#define CITADEL_QUEST_SHT   "Cleanse citadel quest"

#define INFANT_QUEST_GROUP GROUP1  
#define INFANT_QUEST_BIT   5
#define INFANT_QUEST_EXP   1000 
#define INFANT_QUEST_LNG   "Find kidnapped infant"
#define INFANT_QUEST_SHT   "Find kidnapped infant quest"

// Quest implemented in /d/Faerun/thornhold/std/thornhold_return_quest.c
#define THORNHOLD_QUEST_GROUP GROUP1  
#define THORNHOLD_QUEST_BIT   5
#define THORNHOLD_QUEST_1_EXP 500
#define THORNHOLD_QUEST_2_EXP 500
#define THORNHOLD_QUEST_3_EXP 500
#define THORNHOLD_QUEST_4_EXP 500
#define THORNHOLD_QUEST_5_EXP 500
#define THORNHOLD_QUEST_EXP   1000
#define THORNHOLD_QUEST_LNG   "Recover missing items in Thornhold"
#define THORNHOLD_QUEST_SHT   "Recover Thornhold items"

#define JARLAXLE_QUEST_GROUP GROUP1  
#define JARLAXLE_QUEST_BIT   6
#define JARLAXLE_QUEST_EXP   500 
#define JARLAXLE_QUEST_LNG   "Find Jarlaxle his wine"
#define JARLAXLE_QUEST_SHT   "Find Jarlaxle some wine"

#define WATERDEEP_QUEST_GROUP       GROUP1  
#define WATERDEEP_QUEST_BIT         7
#define WATERDEEP_QUEST_EXP         3500
#define WATERDEEP_QUEST_LNG         "Rescue Crying Womans Baby"
#define WATERDEEP_QUEST_SHT         "Rescue Crying Womans Baby"

#define RUBFEET_QUEST_GROUP         GROUP1  
#define RUBFEET_QUEST_BIT           8
#define RUBFEET_QUEST_EXP           3500
#define RUBFEET_QUEST_LNG           "Rub an old woman's feet"
#define RUBFEET_QUEST_SHT           "Rub feet"

#define DANCING_QUEST_GROUP         GROUP1
#define DANCING_QUEST_BIT           9
#define DANCING_QUEST_EXP           150
#define DANCING_QUEST_SHT           "give a performance"
#define DANCING_QUEST_LNG           "perform on stage"

#define GENDER_QUEST_GROUP          GROUP2
#define GENDER_QUEST_BIT            1 
#define GENDER_QUEST_EXP            250
#define GENDER_QUEST_SHT            "lose your gender"
#define GENDER_QUEST_LNG            "visit a prosititue, become neuter"

#define RESTORE_GENDER_QUEST_GROUP  GROUP2
#define RESTORE_GENDER_QUEST_BIT    2
#define RESTORE_GENDER_QUEST_EXP    500
#define RESTORE_GENDER_QUEST_SHT    "get your gender back"
#define RESTORE_GENDER_QUEST_LNG    "visit the doctor, get your parts" 

#define JAIL_BREAK_GROUP            GROUP2
#define JAIL_BREAK_BIT              3
#define JAIL_BREAK_EXP              500
#define JAIL_BREAK_SHT              "break out of jail"
#define JAIL_BREAK_LNG              "break out of jail"

#define TRANS_QUEST_GROUP           GROUP2
#define TRANS_QUEST_BIT             4
#define TRANS_QUEST_EXP             500
#define TRANS_QUEST_SHT             "learn identity of prostitute"
#define TRANS_QUEST_LNG             "learn identity of prostitute"

#define RETURN_BADGE_GROUP          GROUP2
#define RETURN_BADGE_BIT            5
#define RETURN_BADGE_EXP            2000
#define RETURN_BADGE_SHT            "return the badge"
#define RETURN_BADGE_LNG            "give Druza back his badge"

#define JAHEEM_QUEST_GROUP          GROUP2
#define JAHEEM_QUEST_BIT            6
#define JAHEEM_QUEST_EXP            1500
#define JAHEEM_QUEST_SHT            "get jaheem's money"
#define JAHEEM_QUEST_LNG            "get jaheem's money"

#define CHAZ_QUEST_GROUP            GROUP2
#define CHAZ_QUEST_BIT              7
#define CHAZ_QUEST_EXP              1000
#define CHAZ_QUEST_SHT              "help Chaz"
#define CHAZ_QUEST_LNG              "help Chaz see invisible enemies"

// Fire Knives Guru Quest
#define SIGNET_RING_QUEST_GROUP     GROUP2
#define SIGNET_RING_QUEST_BIT       8
#define SIGNET_RING_QUEST_EXP       1000
#define SIGNET_RING_QUEST_SHT       "Collect proof of noble's demise"
#define SIGNET_RING_QUEST_LNG       "Collect proof of noble's demise for Kyri"

#define ANIMAL_FEED_QUEST_GROUP     GROUP2
#define ANIMAL_FEED_QUEST_BIT       9
#define ANIMAL_FEED_QUEST_EXP       10000
#define ANIMAL_FEED_QUEST_SHT       "Fix grain prices"
#define ANIMAL_FEED_QUEST_LNG       "Find and eliminate grain stealing bandits."

// Vampires entryquest
#define VAMP_ENTRY_QUEST_GROUP      GROUP2
#define VAMP_ENTRY_QUEST_BIT        10
#define VAMP_ENTRY_QUEST_EXP        5000
#define VAMP_ENTRY_QUEST_SHT        "Collect bloodsample"
#define VAMP_ENTRY_QUEST_LNG        "Collect bloodsample for Van Henriksen"

/*#define ANIMAL_FEED_QUEST_GROUP     GROUP2
#define ANIMAL_FEED_QUEST_BIT       11
#define ANIMAL_FEED_QUEST_EXP       10000
#define ANIMAL_FEED_QUEST_SHT       "Fix grain prices"
#define ANIMAL_FEED_QUEST_LNG       "Find and eliminate grain stealing bandits."*/

// Phlan tour quests
#define PHLAN_TOUR1_QUEST_GROUP     GROUP2
#define PHLAN_TOUR1_QUEST_BIT       12
#define PHLAN_TOUR1_QUEST_EXP       1000
#define PHLAN_TOUR1_QUEST_SHT       "Phlan Tour 1"
#define PHLAN_TOUR1_QUEST_LNG       "Phlan Tour 1 quest"

#define PHLAN_TOUR2_QUEST_GROUP     GROUP2
#define PHLAN_TOUR2_QUEST_BIT       13
#define PHLAN_TOUR2_QUEST_EXP       1000
#define PHLAN_TOUR2_QUEST_SHT       "Phlan Tour 2"
#define PHLAN_TOUR2_QUEST_LNG       "Phlan Tour 2 quest"

#define PHLAN_TOUR3_QUEST_GROUP     GROUP2
#define PHLAN_TOUR3_QUEST_BIT       14
#define PHLAN_TOUR3_QUEST_EXP       1000
#define PHLAN_TOUR3_QUEST_SHT       "Phlan Tour 3"
#define PHLAN_TOUR3_QUEST_LNG       "Phlan Tour 3 quest"

#define PHLAN_TOUR4_QUEST_GROUP     GROUP2
#define PHLAN_TOUR4_QUEST_BIT       15
#define PHLAN_TOUR4_QUEST_EXP       1000
#define PHLAN_TOUR4_QUEST_SHT       "Phlan Tour 4"
#define PHLAN_TOUR4_QUEST_LNG       "Phlan Tour 4 quest"

/* This quest is to show how to code a quest */
#define TEST_QUEST_GROUP    GROUP4
#define TEST_QUEST_BIT      1
#define TEST_QUEST_EXP      500
#define TEST_QUEST_LNG      "Test - Find Nerissa's Scarf"
#define TEST_QUEST_SHT      "Nerissa quest"



/*
#define _QUEST_GROUP
#define _QUEST_BIT  
#define _QUEST_EXP
#define _QUEST_LNG      ""
#define _QUEST_SHT      ""
*/