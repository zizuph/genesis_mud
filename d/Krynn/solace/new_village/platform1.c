/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

/* This loads the main solace bulletin board */
static void
load_board()
{
    clone_object(OBJ + "city_board")->move(TO);
}


create_solace_room()
{
    set_place(PLATFORM);

    set_long_desc("This is a rather large platform with several " +
		  "bridge-walks connecting to it. There is a stairway " +
		  "leading down around the trunk onto a narrow path.");
    
    add_exit(TDIR + "bridge_walk01", "northeast");
    add_exit(TDIR + "bridge_walk13", "southeast");
    add_exit(TDIR + "bridge_walk17", "southwest");
    add_exit(TDIR + "bridge_walk18", "west");
    add_exit(TDIR + "bridge_walk06", "northwest");
    add_exit(TDIR + "small_road1", "down");

    seteuid(getuid(TO));
    load_board();
}


