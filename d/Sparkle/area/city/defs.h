/*
 *  /d/Sparkle/area/city/defs.h
 *
 *  These are definitions to be used in Sparkle City.
 *
 *  Created February 2008, by Cooper Sherry (Gorboth)
 */

#define CITY_DIR            ("/d/Sparkle/area/city/")
#define ROOMS_DIR           (CITY_DIR + "rooms/")
#define STREET_DIR          (ROOMS_DIR + "streets/")
#define INSIDE_DIR          (ROOMS_DIR + "inside/")
#define DATA_DIR            (CITY_DIR + "data/")
#define OBJ_DIR             (CITY_DIR + "obj/")
#define LOG_DIR             (CITY_DIR + "log/")
#define TEXT_DIR            (CITY_DIR + "text/")
#define LIB_DIR             (CITY_DIR + "lib/")
#define NPC_DIR             (CITY_DIR + "npc/")
#define LIBRARY_DIR         (CITY_DIR + "library/")
#define ROOFTOP_DIR         (CITY_DIR + "rooftop/")
#define SEWER_DIR           (CITY_DIR + "sewer/")
#define BANK_DIR            (CITY_DIR + "bank/")
#define SYS_DIR             (CITY_DIR + "sys/")

#define VENDOR_QUEST_LOG    ("/d/Sparkle/log/vendor")
#define VENDOR_FINAL_LOG    ("/d/Sparkle/log/vendor_finish")
#define VENDOR_ASSIGN_LOG   (LOG_DIR + "vendor_assignments")
#define HERB_QUEST_LOG      ("/d/Sparkle/log/herb")
#define HERB_FINAL_LOG      ("/d/Sparkle/log/herb_finish")
#define HERB_ASSIGN_LOG     (LOG_DIR + "herb_assignments")

#define BC_MODULE           (LIB_DIR + "broadcast_master")
#define MAP_MODULE          (LIB_DIR + "sparkle_map_module")
#define VENDOR              (OBJ_DIR + "vendor_master")
#define VENDORNAME          ("_sparkle_quest_vendor")
#define VENDORSIGN          ("_sparkle_vendor_sign")
#define H_VENDORNAME        ("_sparkle_herb_quest_vendor")
#define TOWN_CRIER          ("_sparkle_town_crier_npc")
#define CRIER_DOG           ("_sparkle_town_crier_pet")
#define RATING_FORM         ("_sparkle_sign_rating_form")
#define PUB_QUEST_ITEM      ("_sparkle_pub_quest_item")
#define LOCAL_QM_CHECKLIST  ("_sparkle_local_qm_checklist")
#define CADETS_CHECKLIST    ("_sparkle_cadets_checklist")
#define SCRUB_BRUSH         ("_sparkle_dock_scrub_brush")
#define FEATHER_DUSTER      ("_sparkle_quest_orb_duster")
#define SHIPLINE_SIGN       ("_sparkle_dock_shipline_sign")
#define DOCK_TOUR_PROP      ("_sparkle_dock_tour_prop")
#define ORBS_TOUR_PROP      ("_sparkle_orbs_tour_prop")
#define SPARKLE_TOUR_PROP   ("_sparkle_city_quest_tour_prop")
#define PUB_QUESTING_PROP   ("_sparkle_pub_quest_prop")
#define CURRENT_QUESTS      ("current")
#define QUEST_FAILURES      ("failures")
#define QUEST_SUCCESSES     ("successes")
#define QUEST_ASSIGNED      ("assigned")
#define CURRENT_H_QUESTS    ("herb_current")
#define QUEST_H_FAILURES    ("herb_failures")
#define QUEST_H_SUCCESSES   ("herb_successes")
#define QUEST_H_ASSIGNED    ("herb_assigned")
#define MARKETDAY            "Wednesday"
#define HERBDAY              "Saturday"
#define SPARKLE_NPC_DATA    (DATA_DIR + "master_time_data")
#define MASTER_TIME_ROOM    (ROOMS_DIR + "master_time_room")
#define PATHFIND_LIB        (LIB_DIR + "pathfind")
#define SPARKLE_NPC_BASE    (NPC_DIR + "sparkle_npc")
#define SPARKLE_ROOM_BASE   (ROOMS_DIR + "sparkle_room_base")

#define STREET_CENTER        "Old Sparkle Road"
#define STREET_EAST_1        "the northern pier"
#define STREET_EAST_2        "the southern pier"
#define STREET_EAST_3        "Founders Pier"
#define STREET_SOUTHEAST     "Platinum Street"
#define STREET_SOUTH_1       "Badger Street"
#define STREET_SOUTH_2       "Fishmonger Road"
#define STREET_SOUTHWEST_1   "Skylark Lane"
#define STREET_SOUTHWEST_2   "Juniper Street"
#define STREET_SOUTHWEST_3   "Cutthroat Alley"
#define STREET_WEST          "Hump Backed Road"
#define STREET_NORTHWEST     "Peddler Street"
#define STREET_NORTH         "Merchant Circle"
#define STREET_NORTHEAST_1   "Ethereal Street"
#define STREET_NORTHEAST_2   "South Lieges Avenue"
#define STREET_NORTHEAST_3   "North Lieges Avenue"
#define STREET_NORTHEAST_4   "White Sands Bouldevard"

#define QUEST_FILE(n)        (extract((n), 0, 0) + "/" + (n))
#define TELL_G(x)            find_living("gorboth")->catch_tell( \
                               "DEBUG: " + x + "\n")

/* Defines for Quest Control */
#define QUEST_CONTROL_ROOM  (ROOMS_DIR + "quest_control_room")
#define QUEST_DATA_DIR      (DATA_DIR + "questdb/")
#define QUEST_HINTS_DIR     (QUEST_DATA_DIR + "hints/")
#define QUEST_VALIDATION    (LIB_DIR + "quest_orb_validation") 
#define QUEST_ORB_LOG       ("quest_orb_requests")
#define QUEST_ORB_ERRORS    ("questdb_missing_bits")

/* Defines for Broadcast Room Types */
#define ROOM_TYPE_UNKNOWN   0
#define ROOM_TYPE_STREET    1
#define ROOM_TYPE_ROOF      2
#define ROOM_TYPE_DOCK      3
                              
/* Defines for Gayryn's Prodigal Pub */
#define GPUB_DIR         (CITY_DIR + "gpub/")
#define GPUB_ROOM_DIR    (GPUB_DIR + "room/")
#define GPUB_NPC_DIR     (GPUB_DIR + "npc/")
#define GPUB_OBJ_DIR     (GPUB_DIR + "obj/")

#define GPUB_ROOM_BASE   (GPUB_ROOM_DIR + "gpub_room_base")