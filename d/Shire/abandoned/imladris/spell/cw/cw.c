/*
 *  concussions_way.c
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
    add_spell_file(CW_DIR+"lift", "saure-wania");   // "wanya" = depart, 
				// "saura" = evil-smelling
    add_spell_file(CW_DIR+"regen", "voronwie");  // 'voronwie'   -> Endurance. 

    /*            Lvl, Name,            Cls, Mana  */
    setup_list( ({  1, "feamaar",         1,   10 }),
		({  2, "vinyacanta",      1,   20 }),
		({  3, "feamaar",         2,   30 }),
		({  4, "vinyacanta",      2,   40 }),
		({  5, "voronwie",        1,   50 }),
		({  6, "feamaar",         5,   60 }),

		({  8, "vinyacanta",      3,   80 }),
		({  9, "feamaar",        10,   90 }),
		({ 10, "voronwie",        2,  100 }),
		({ 11, "vinyacanta",      4,  110 }),

		({ 15, "voronwie",        3,  150 }),
		({ 16, "saure-wania",     1,  160 }),
		({ 18, "vinyacanta",      5,  180 }),
		({ 20, "voronwie",        5,  200 }),
		({ 25, "vinyacanta",     10,  250 }),
		({ 30, "voronwie",       10,  300 })); 

    return 1;
}

