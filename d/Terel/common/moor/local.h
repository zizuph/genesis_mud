/*

    The defs file for Sorgum's tomb area in Northern Terel.

    Modified: 13 June 2003, by Bleys
        - Changed TOMBDIR definition.
    Modified: Dec 2021, By Lilith
	    - Changed TOMBDIR def 
*/

#define TOMB_DOOR_KEY  3141592

#define TOMBLOG        "/d/Terel/log/tombdwell"

#define COFFIN_ROUTE   "_live_i_took_coffin_route"

#ifndef TOMBDIR
#define TOMBDIR "/d/Terel/common/moor/tomb/"
#endif

#ifndef OBJDIR
#define OBJDIR "/d/Terel/common/moor/obj/"
#endif

#ifndef MOBDIR
#define MOBDIR "/d/Terel/common/moor/monster/"
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
