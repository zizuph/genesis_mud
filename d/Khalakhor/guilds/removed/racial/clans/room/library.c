/* Library for racial guild
 * Clans of Khalakhor
 * Created by Damaris 09/Y2K
 * Modified for use with the Clans of Khalakhor  -- Tomas 
 */
#pragma strict_types

#include "../guild.h"
#include <stdproperties.h>

inherit GUILD_ROOM;
inherit "/d/Khalakhor/lib/library";

#include "seated.c"

/*
 * Function name: library_exit_block
 * Description:   Check to see if the player is carrying a library
 *                scroll.  This is meant to be used as a block function
 *                for exits from the library so that scrolls cannot be
 *                removed.
 * Returns:       1/0 - scroll carried/not carried
 */
public int
library_exit_block()
{
    /* See if the player is carrying a scroll */
    if (::library_exit_block())
    {
        /* A scroll was found.  Give a warning and return 1 to block the exit */
        write("A magical force prevents you from leaving.\n" +
            "You must be carrying a scroll.\n");
        return 1;
    }

    /* No scroll present.  Return 0 to allow the player to exit */
    return 0;
}

void
create_guild_room()
{
    set_short("Within the Great Library of MacDunn");
    set_long("You are standing within the Great Library of MacDunn. " +
             "Its walls are white with long arched windows spaced " +
             "evenly along the west wall. The windows provide plenty " +
             "of natural light in which to read by. Long rows of " +
             "bookshelves containing various sized books and racks " +
             "of scrolls stand in perfect order leading " +
             "from the entrance to the far end of the hall. A large " +
             "staircase winds up along either side of large counter " +
             "where the librarian usually stands on duty.\n");

     add_item(("windows"),"The long arched windows stand several " +
              "spans high. They allow plenty of light for reading.\n");
     add_item(("light"),"Rays of sunshine seep through the windows " +
              "casting much needed reading light.\n");
     add_item(({"walls","wall"}),"You see nothing special about the " +
              "white washed walls.\n");
     add_item(({"book","books","parchment"}),
                "Several hundred dusty tomes, books and loose leaf " +
                "binders line the bookshelves. The books are maintained " +
                "by the Order of the Sean-Rhian.\n");
     add_item(({"bookshelves","bookshelf"}),
                "Several dark wood grained bookshelves stand in perfect " +
                "rows leading form the entrance to the counter along the " +
                "far wall.\n");
     add_item(({"counter"}),"A long counter lines the far wall opposite the " + 
                "main entrance. A small sign stands on top of the counter for " +
                "your reading pleasure. Several racks containing scrolls can be " +
                "seen behind the counter.\n");
     add_item(({"scroll","scrolls"}),
                "Several scrolls hang from tall racks behind the counter " +
                "along the eastern wall. Perhaps, you might read the sign " +
                "on the counter for further assistance.\n");
     add_item(({"rack","racks"}),
                "The wooden racks hold several rolls of scrolls.\n");
     add_item(({"chair","chairs"}), seat_desc);
     add_item(({"stairs","staircase"}),
                "The great staircase winds on eitherside of the counter then " +
                "connects leading to a second level above.\n");

    /* Add a sign that gives instructions on how to use the library */
     add_item("sign", library_help());

     add_cmd_item(({"sign","scroll", "tapestry", "chair", "table",}),
         (({"get","take","burn","climb"})),
         "You fail to do so and should be ashamed for even trying. Perhaps, "+
       "you might try listing then borrowing a scroll instead..\n");

    /* Add an exit using library_exit_block() to be sure that no-one
     * leaves the library with a scroll
     */
    add_exit("/d/Khalakhor/se_speir/port/room/th_2", "north", library_exit_block);
    add_exit("joinroom", "stairs");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);  
    /* Indicate that we want players to have to "borrow" a scroll in
     * order to read it.
     */
    set_borrow_required(1);

    /* This is the directory where approved scrolls are saved */
    set_scroll_directory(SCROLLS);

    /* This is the directory where scrolls that need approval are saved */
    set_scroll_approval_directory(SCROLLS + "approval/");

    /* This is the directory where scrolls that have been denied or discarded
     * are saved.
     */
    set_scroll_removal_directory(SCROLLS + "removed/");

    /* Add shelves to the library so that scrolls can be classified under
     * different categories.  Note that for each shelf you must add a
     * subdirectory with the same name under the base directory specified
     * with set_scroll_directory().
     */
    add_scroll_shelf(({ "general", "history", "lineage" }));
    create_library();


    add_cmd_item("sign","read", library_help());


    add_my_desc(seat_desc, this_object());
}

void
init()
{
    ::init();
    /* Add the library commands */
    init_library();
    init_seat();
}

/*
 * Function name: library_admin_access
 * Description:   Limit library administration abilities to certain
 *                people.
 * Returns:       1 - this_player() has administration powers
 *                0 - this_player() does not have administration powers
 */
public int
library_admin_access()
{
    /* We'll give admin access to wizards */
    if (this_player()->query_wiz_level())
    {
        return 1;
    }

    /* No-one else has admin access */
    write("You do not have permission to do that.\n");
    return 0;
}

/*
 * Function name: library_write_access
 * Description:   Limit permission to write scrolls to certain people
 * Returns:       1 - this_player() is allowed to write
 *                0 - this_player() is not allowed to write
 */
public int
library_write_access()
{
    /* We'll allow any member of the racial guild  to write scrolls
     */
    if (IS_MEMBER(this_player()))
    {
        return 1;
    }

    /* We'll allow wizards to write scrolls */
    if (this_player()->query_wiz_level())
    {
        return 1;
    }

    /* No-one else has permission to write scrolls */
    write("You do not have permission to do that.\n");
    return 0;
}
