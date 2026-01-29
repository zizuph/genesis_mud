/*
 *  /doc/examples/guild_library/advanced/owner_card.c
 *
 *  This card is used in the advanced guild library to indicate
 *  the carrier as owner of the library, enabling librarian functions.
 *
 *  Created by Eowul, May 10th, 2009
 */
 
inherit "/std/object";

void create_object()
{
    set_name("card");
    add_name("_library_owner_card");
    add_adj("library");
    add_adj("owner");
    set_short("library owner card");
    set_long("This is a library own card, which grants you access to "
        + "the librarian functions.\n");
}