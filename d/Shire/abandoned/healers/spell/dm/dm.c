/*
 * dm.c
 *
 *    A Channeling spell list called Detection Mastery.
 *
 */

#include "defs.h"

inherit SPELL_LIST_FILE;

init_list()
{
    ::init_list();

    set_list_name("Detection Mastery");
    set_list_short("dm");
    set_realm("channeling");

    add_spell_file(THIS_DIR+"detect",   "kuru");    // 'kurungol' -> 'Kuru': Magic, wizardry. 
    add_spell_file(THIS_DIR+"identify", "ingole");  // 'ingole' -> Lore, deep, magic (archaic/poetic) -ngol.
    add_spell_file(THIS_DIR+"lifetype", "kuile");  // 'kuruni' -> Witch of the good magic. 'Kuile' -> Life.
    add_spell_file(THIS_DIR+"detgood",  "voronda");   // 'voronda' -> Faithful.
    add_spell_file(THIS_DIR+"detevil",  "ulka");   // 'ulka' -> Evil.
    add_spell_file(THIS_DIR+"detalign", "waina");  // 'waina' -> Robe.
    add_spell_file(THIS_DIR+"detinvis", "maur");  // 'maur' ->vision (umaur?)
    add_spell_file(THIS_DIR+"percieve", "veela");  // 'veela' -> see  (kuruvela?)

	/*				Lvl, Name, 		       Cls, Mana */
	setup_list(
				({	 1, "ulka",		1,	 10  }),
				({   3, "voronda",		1,	 30  }),
				({	 4, "waina",	1,	 50  }),
				({	 6, "kuru",	  	1,	 80  }),
				({	 7, "maur",	1,	 90  }),
				({	12, "veela",	1,	100  }),
				({ 	13, "ingole",	1,	190  }),
				({  18, "maur",	5,	200  }),
				({  20, "kuile",		1,	300  }),
				({	25, "maur", 10,	400  })
			   );
	return 1;
}
