/*
 * Master defines file for the auction house
 * Path: /d/Sparkle/area/city/auction/defs.h
 */
#ifndef _AUCTION_HOUSE_
#define _AUCTION_HOUSE

#include "/d/Sparkle/sys/defs.h"

#define AUCTION_DIR          ("/d/Sparkle/area/city/auction/")

#define OBJ_DIR              (AUCTION_DIR + "obj/")
#define NPC_DIR              (AUCTION_DIR + "npc/")
#define ROOM_DIR             (AUCTION_DIR + "room/")
#define DATA_DIR             (AUCTION_DIR + "data/")
#define LOG_DIR              (AUCTION_DIR + "log/")

#define SQUARE               ("/d/Genesis/start/human/town/square")

//#define AUCTION_MASTER       (OBJ_DIR + "auction_master")
#define AUCTION_DATA_STORE   (OBJ_DIR + "auction_data_store")
#define AUCTION_RECOVER      (OBJ_DIR + "auction_recovery") 
#define RECOVER_SHADOW       (OBJ_DIR + "recovery_shadow") 

#define AUCTION_HOUSE        (ROOM_DIR + "auction_house")
#define STORE_ROOM           (ROOM_DIR + "store_room")

#define AUCTIONS             ("auctions")
#define OWED                 ("owed")
#define RANKING              ("rankings")
#define PRICES               ("prices")

#define AUCTION_FEE_PERCENT  10
#define AUCTION_EXPIRE       -(60 * 86400)

#define PADDLE               (OBJ_DIR + "paddle")

#define BID_LOG              (LOG_DIR+"bids")
#define AUCTION_LOG          (LOG_DIR+"auction_log")
#define CASH_LOG             (LOG_DIR+"cash_log")
#define SELLER_LOG           (LOG_DIR+"sale_log")

#define QUEST_LOG_FILE       ("/d/Sparkle/log/quest_log/auction_quest")
#define QUEST_ATTEMPT_LOG    (LOG_DIR+"attempt_log")

#endif /* _AUCTION_HOUSE_ */
