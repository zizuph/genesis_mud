#define THROWN_OUT     "_chapel_thrown_out"
#define M_MANAGER      "/d/Emerald/common/marriage/marriage_manager"
#define IS_GROOM       "_is_groom"
#define IS_BRIDE       "_is_bride"
#define PLAYER_I_IS_GETTING_MARRIED "_player_i_is_getting_married"
#define JUST_MARRIED   "_just_married"
#define IS_DRIVER      "_is_driver"
#define BLANK_ADVERB    "gently"
#define GUILD_SOUL_ID   "emerald wedding"
#define PLAYER_S_SPOUSE "_player_s_spouse"
#define NF(xxx)         notify_fail(xxx)
#define TP              this_player()
#define TO              this_object()
#define ENV_TP          environment(this_player())
#define SPOUSE          ({ spouse })
#define SP_OB           spouse->query_objective()
#define SP_PO           spouse->query_possessive()
#define TP_OB           this_player()->query_objective()
#define TP_PO           this_player()->query_possessive()
#define SOUL_PATH       "/d/Emerald/common/marriage/wedding_soul"
#define RING_SUBLOC     "_ring_desc"
#define RING_PATH       "/d/Emerald/common/marriage/ring"
#define RING_ID         "_emerald_marriage_ring_"
#define CHAPEL_DIR      "/d/Emerald/leah/chapel/"
#define VILLAGE_DIR     "/d/Emerald/leah/"

#define MATERIALS    ({ "gold", "white gold", "platinum", "mithril", "adamant", "onyx" })
#define CARRIAGECOST 10
#define DRIVERDELAY 10.0
#define INCARRIAGE CHAPEL_DIR + "incarriage"
#define IS_CARRIAGE_STOP "_is_carriage_stop_room"
