/*
 *  concussions_way.c (cw.c)
 *
 *    A Channeling spell list called Concussion's Way.
 *
 */


#include "defs.h"

inherit SPELL_LIST_FILE;

int
init_list()
{
    ::init_list();

    set_list_name("Concussion's Way");
    set_list_short("cw");
    set_realm("channeling");

    add_spell_file(CW_DIR+"heal", "vinyacanta");// 'vinyakanta' -> In new body.
    add_spell_file(CW_DIR+"ease", "feamaar");   // "fea" spirit - "Maar" good
    add_spell_file(CW_DIR+"lift", "wanya-saura"); // "wanya" = depart, 
				                                  // "saura" = evil-smelling
    add_spell_file(CW_DIR+"regen", "voronwie");   // 'voronwie'   -> Endurance.

    /*            Lvl, Name,            Cls, Mana  */
    setup_list( ({  1, "feamaar",         1,   30 }),
	            ({  3, "feamaar",         5,   50 }),
	            ({  5, "vinyacanta",      1,   70 }),
	            ({  7, "wanya-saura",     1,  100 }),
	            ({  9, "feamaar",        10,  120 }),
	            ({ 10, "vinyacanta",      2,  140 }),
	            ({ 12, "wanya-saura",     5,  250 }),
                ({ 17, "vinyacanta",      5,  260 }),
	            ({ 20, "wanya-saura",    10,  280 }),
                ({ 25, "vinyacanta",     10,  400 }));
    return 1;
}

