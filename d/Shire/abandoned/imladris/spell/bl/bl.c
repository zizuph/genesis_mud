/*
 * bl.c
 *
 *    A Channeling spell list called Barrier Law.
 *
waterfall = aksa kalpa
airy = wilin {vili]
air = wilya {wil}
air as substance = wista
earth = keen (hemen)
 */

#include "defs.h"

inherit SPELL_LIST_FILE;

init_list()
{
    ::init_list();

    set_list_name("Barrier Law");
    set_list_short("bl");
    set_realm("channeling");

    /*
    add_spell_file(THIS_DIR+"detect");
    add_spell_file(THIS_DIR+"identify");
    add_spell_file(THIS_DIR+"lifetype");
    add_spell_file(THIS_DIR+"detgood");
    add_spell_file(THIS_DIR+"detevil");
    add_spell_file(THIS_DIR+"detalign");
    add_spell_file(THIS_DIR+"detinvis");
    add_spell_file(THIS_DIR+"percieve");
    */
}
