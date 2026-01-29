// Library that defines general block functions
#define BLOCK_LIB  "/d/Genesis/specials/std/block_lib"

// Shadows for both the Blocker and Blockee
#define BLOCKER_SH ("/d/Genesis/specials/std/blocker_sh")
#define BLOCK_SH   ("/d/Genesis/specials/std/block_sh")

// Block Abliity File
#define BLOCK_ABILITY ("/d/Genesis/specials/std/block")

// Log file to store the block attempts
#define BLOCK_LOG  ("/d/Genesis/log/BLOCK_LOG")

// This is a global skill, so it may already be defined
#ifndef SS_BLOCK
#define SS_BLOCK 26
#endif

// Define the properties on the blocker
#define BLOCK_PROP      "_live_o_enemy_block"
#define BLOCK_EXIT      "block_exit"
#define BLOCK_ROOM      "block_room"
#define BLOCK_STR       "block_strength"
#define BLOCK_BLOCKEES  "block_blockees"
// Set this to change the duration of block globally
#define BLOCK_TIME_PER_10_SKILL    1.75
// Useful to prevent someone from blocking
#define  PLAYER_I_CANNOT_BLOCK    "_player_i_cannot_block"

// General Useful Macros
#ifndef TP
#define TP            this_player()
#endif
#ifndef TO
#define TO            this_object()
#endif
#ifndef QSW
#define QSW           query_shadow_who()
#endif
#define POSS(obj)     obj->query_possessive()
#define PRO(obj)      obj->query_pronoun()
#define OBJ(obj)      obj->query_objective()
#define SHORT(obj)    obj->short()
