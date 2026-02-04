/*

    The defs file for Sorgum's tomb area in Northern Terel.

    Modified: 13 June 2003, by Bleys
        - Changed TOMBDIR definition.

*/
#ifndef TOMBDIR
#define TOMBDIR "/d/Terel/sorgum/tomb/"
#endif

#ifndef BSN
#define BSN(message)    break_string(message + "\n", 70)
#endif

#ifndef TP
#define TP              this_player()
#endif

#ifndef TO
#define TO              this_object()
#endif

#ifndef SET_MAX_HP
#define SET_MAX_HP set_hp(query_max_hp())
#endif

#define TOMB_DOOR_KEY  3141592
