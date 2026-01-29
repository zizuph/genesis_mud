/*
 *  /doc/examples/guild_library/advanced/library_scroll.c
 * 
 *  Custom book for use in the advanced example of the guild library.
 *
 *  Created by Eowul, May 10th, 2009
 */
 
inherit "/d/Calia/guilds/elementalists/temple/library/guild_library_book";

public void create_library_book()
{
    string *adjs = ({ "weathered", "dusty", "faded" });
    string adj = adjs[random(sizeof(adjs))];

    add_adj(adj);
    set_name("scroll");
    set_pname("scrolls");
    set_short(adj + " scroll");
    set_long("The " + adj + " scroll is made from the finest parchment.\n");
}
