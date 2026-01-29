/*
 * Stone #4, Entered from road13.c
 * By Finwe, December 2001
 */
 

#include "/d/Shire/sys/defs.h"
#include "../local.h"

inherit STONE_BASE;
//void string pit_exit = "/d/Shire/downs/barrows/bar09";


void
create_stone_room()
{
    set_pit_exit("/d/Shire/downs/barrows/bar04_01");
    NO_STEEDS;
}

