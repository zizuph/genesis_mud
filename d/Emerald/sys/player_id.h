#ifndef EMERALD_PLAYER_ID
#define EMERALD_PLAYER_ID

#define PLAYER_ID_CODE ("/d/Emerald/sys/global/player_id")

#define PLAYER_ID(player)        (PLAYER_ID_CODE->query_player_id(player))
#define PLAYER_NAME_FROM_ID(id)  (PLAYER_ID_CODE->query_player_name_by_id(id))

#endif EMERALD_PLAYER_ID
