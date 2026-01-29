

/* defs to go with Amelia's pond */

#define FQ_DOMAIN "Calia"
#define FQ_GROUP 2
#define FQ_BIT 2
#define FQ_XP 475
#define TP this_player()
#define TO this_object()
#ifdef FPATH
#undef FPATH
#endif
#define FPATH "/d/Calia/pond/"
#define OBJ FPATH+"objects/"
#define ZIMA "/d/Calia/argos/nwterr/rooms/"
#define CROAKER OBJ+"frog_croaker.c"
#define NET OBJ+"net.c"
#define FROG OBJ+"frog.c"
#define FROG_SHADOW OBJ+"frog_shadow.c"
#define PLAYER_I_FOUND_NET "_player_i_found_net"
#define PLAYER_I_FOUND_FROG "_player_i_found_frog"
#define PLAYER_I_CAUGHT_FROG "_player_i_caught_frog"

/* Elemental area defines */

#define GQ_DOMAIN "Calia"
#define GQ_GROUP 2
#define GQ_BIT 6
#define GQ_XP 500
#define CALIA_I_MANA_GAIN "_calia_i_mana_gain"
#define CALIA_I_PATH_BLOCKED "_calia_i_path_blocked"
#define CALIA_I_TALK_WANDERER "_calia_i_talk_wanderer"
#define GQ_I_PATH_BLOCKED "_gq_i_path_blocked"
#define GQ_I_TALK_WANDERER "_gq_i_talk_wanderer"

