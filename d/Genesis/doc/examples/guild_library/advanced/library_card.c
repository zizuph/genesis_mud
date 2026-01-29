/*
 *  /doc/examples/guild_library/advanced/library_card.c
 *
 *  This card is used in the advanced guild library to allow
 *  access to the restricted shelves.
 *
 *  Created by Eowul, May 10th, 2009
 */
 
inherit "/std/object";

void create_object()
{
    set_name("card");
    add_name("_library_card");
    add_adj("library");
    set_short("library card");
    set_long("This is a library card, which grants you access to "
        + "the restricted shelves.\n");
}