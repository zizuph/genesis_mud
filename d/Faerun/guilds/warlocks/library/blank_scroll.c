/*
 * /d/Faerun/guilds/warlocks/library/blank_scroll.c
 * Blank scroll for players to write on to be added to the guild library.
 * Created by Eowul, May 10th, 2009
 * Copied over from example directory and modified by Finwe for Warlock guild
 * June 2017
 */
#include "/d/Faerun/defs.h"

inherit "/std/guild_library_book";

public void create_library_book()
{
    string *adjs = ({ "weathered", "dusty", "faded" });
    string adj = ONE_OF_LIST(({ "weathered", "dusty", "faded", "tattered", "rigid" }));

    add_adj(adj);
    set_name("scroll");
    set_pname("scrolls");
    set_short(adj + " scroll");
    set_long("The " + adj + " scroll is made from the finest parchment.\n");
}