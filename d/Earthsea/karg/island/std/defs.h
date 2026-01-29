#include "../defs.h"

#define MY_DIR "/w/shaitan"
#define ISL_DIR "/d/Earthsea/karg/island"
#define FROOMS "/d/Earthsea/karg/island/rooms/forest"
#define SROOMS "/d/Earthsea/karg/island/rooms/shore"

//#define BS(message)     break_string(message, 75)
#define GOBJ(who) who->query_objective()
#define GPOS(who) who->query_possessive()
#define GPRO(who) who->query_pronoun()
//#define TP this_player()
//#define TO this_object()
//#define ENV(x) environment(x)
//#define NF(x) notify_fail(x)
//#define C(x) capitalize(x)
//*******************
//Properties
//*******************
//docks
#define PLAYER_I_FOUND_WOOD "_player_i_found_wood"
#define PLAYER_I_GOT_IDEA "_player_i_got_idea"

//tricksters entrance
#define PLAYER_I_PEEKED_BLANKET "_player_i_peeked_blanked"
#define PLAYER_I_READ_DIARY "_player_i_read_diary"
#define PLAYER_I_OPENED_CHEST "_player_i_opened_chest"
#define PLAYER_I_UNLOCKED_CHEST "_player_i_unlocked_chest"
#define PLAYER_I_FOUND_DIARY "_player_i_found_diary"
