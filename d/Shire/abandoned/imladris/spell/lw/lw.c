/*
 * lw.c
 *
 *    A Channeling spell list called Light's Way.
 *
 */

#include "defs.h"

inherit SPELL_LIST_FILE;
//inherit "/d/Shire/imladris/lib/spell_list";

int
init_list()
{
    ::init_list();

    set_list_name("Light's Way");
    set_list_short("lw");
    set_realm("channeling");

    add_spell_file(THIS_DIR + "proj",    "alka");    // Sunlight = aare
    add_spell_file(THIS_DIR + "light",   "silme") ;  // Lightray = alka
    add_spell_file(THIS_DIR + "aura",    "faina");   // Daylight   = aure 
    add_spell_file(THIS_DIR + "sudden",  "silma");   // Emit light = Faina- (phay-)
    add_spell_file(THIS_DIR + "shock",   "kalya");   // Starlight  = ilma {gil} silme
    add_spell_file(THIS_DIR + "utter",   "rilya");   // Moonlight  = isilme
    add_spell_file(THIS_DIR + "flare",   "rilma");   // Light      = kaale kala
    //add_spell_fle(THIS_DIR + "lghtcall","are");     // Illuminate = kalya
    
    // Glittering light = rilma; Brilliance = rilya, rille
    // Radience = "kalma"
                                          
    /*
    add_spell("waiting light", LW_DIR+"waiting");
    add_spell("alkar", LW_DIR+"alkar");
    */

    /*            Lvl, Name,   Cls, Mana  */
    setup_list( 
				({  1, "alka",   1,   10 }),
				({  2, "silme",  1,   20 }),
				({  3, "faina",  1,   30 }),
				({  4, "silme",  2,   40 }),
				({  6, "faina",  2,   60 }),
				({  7, "kalya",  2,   70 }),
				({  8, "silme",  3,   80 }),
				({  9, "rilya",  1,   90 }),
				({ 10, "faina",  3,  100 }),
				({ 12, "rilma",  1,  120 }),
				({ 13, "silme",  5,  130 }),
				({ 15, "silme", 10,  150 }),
				({ 16, "faina",  5,  160 }),
				({ 17, "rilya",  2,  170 }),
				({ 22, "rilya", 10,  220 }),
				({ 23, "silma", 10,  230 }),
				({ 25, "are",    10, 250 })); 

    return 1;
}
