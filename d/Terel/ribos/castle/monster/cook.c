/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * c_guard.c
 *
 * Vader
 * Modified by Sorgum 950602
 *
 *  Modified: 3 May 2003, by Bleys
 *      - fixed a typo
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
create_monster()
{
    ::create_monster();
    set_name("cook");
    set_race_name("gnome");
    set_adj("FAT");
    set_alignment(50);
    set_long("This gnome is HUGE!  He cooks all of the king's meals, " +
	     "and also\neats all of the leftovers.\n");

    default_config_npc(10);

    SET_MAX_HP;
}
