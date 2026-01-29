inherit "/std/room";
inherit "/d/Gondor/std/library/library";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"
#include "/d/Gondor/common/guild/lib/titles.h"

/* Prototypes */
public int ranger_check();
public string exa_poster();

public void
create_room()
{
    set_short("In the Library of the Rangers of Gondor");
    set_long("You are in a large hall with a domed ceiling. Along "+
        "the walls and on the floor are shelves. All the shelves are " +
        "filled with books of varied colours, sizes and ages. At a desk " +
        "in the south-eastern corner of the room sits an aging man, " +
        "probably the librarian. A doorway leads out to the corridor east, " +
        "and to the west is the story room. Your glance stops at a poster " +
        "by the open door, which reads: No talking! Further down on the " +
        "poster you see some instructions.\n");

    add_exit(RANGER_GON_DIR + "upcorr1", "east");
    add_exit(RANGER_GON_DIR + "story_room", "west", &ranger_check(), 1);
//    add_exit(RANGER_GON_DIR + "lib_office", "south");

    add_item(({"shelf", "shelves", "books"}), "There are many books on " +
        "the shelves, you could 'catalog' or 'index' them to find " +
        "out the different shelves there are.\n");
    add_item(({"librarian", "man", "aging man", "desk"}), "The librarian is " +
        "a man of Dunadan origin, dedicated to keeping track of the books " +
        "and texts in the Library of the Rangers. He will probably not " +
        "let you leave with any books.\n");
    add_item(({"poster", "instructions"}), &exa_poster());
    add_cmd_item(({"poster", "instructions"}), "read", &exa_poster());

    add_prop(ROOM_I_INSIDE, 1);

    set_lib_long("the Library of the Rangers of Gondor");
    set_lib_id("rog_lib_id");
    set_lib_path("/d/Gondor/common/guild/library");
    set_default_topics(([ "General" : 0, "New Arrivals" : 1,
        "Trash" : 1 ]));
    set_lib_type(4);
    set_search_delay(2.0);
    set_max_librarian_num(8);
    setup_library();
}

public string
exa_poster()
{
    string text;
 
    text = (capitalize(query_lib_long()) + "\n\n" +
        "Check the 'index' for a list of the shelf names, and the " +
        "catalog of each shelf to see what books are available. When " +
        "you 'borrow' a book, please give the complete title (up to " +
        "any '-'). After you are done, please 'return' your books. " +
        "You may also write a new book by receiving a 'blank' book " +
        "from the librarian. You may fill the book with anything you " +
        "please, so long as it is appropriate for this library.\n\n");
 
    if (check_librarian(this_player()->query_real_name()) ||
      this_player()->query_wiz_level() || 
      COUNCIL->is_officer(this_player()->query_real_name()))
    {
        text += "Librarians have these commands available:\n" +
            " Beautify <bookname>\n" +
            "       Allows you to change the title, or align " +
            "the title neatly.\n" +
            " Edit <bookname>\n" +
            "       Allows you to edit a book or add to it.\n" +
            " Movebook <bookname> to topic <newtopic>\n" +
            "       To remove a book completely, use 'Movebook " +
            "<bookname> to topic trash'.\n" +
            " Erase <bookname> | '-all books in trash-'\n" +
            "       Destroy a book(s) (must be in the trash) " +
            "unrecoverably.\n" +
            " Create <new shelf-topic> <access level> Access level is:\n" +
            "       0: General Public+  1: Librarian Only\n" +
            "       2: Pupils+	        3: Full Rangers+\n" +
            "       4: Mentors, Recruiters and Council\n" +
            "       5: Recruiters and Council\n" + 
            "       6: Council\n" +
            " Uncreate <old shelf-topic>\n" +
            "       Removes an old shelf.\n" +
            " Retire as a librarian\n\n" +
            "Council members do not have these abilities, but they may:\n" +
            " Appoint <name> as librarian\n" +
            " Unappoint <name> as librarian\n";
    }
 
    return text;
}

public int
ranger_check()
{
    int wiz_level = this_player()->query_wiz_level();

    if (IS_RANGER(this_player()))
        return 0;

    if (wiz_level)
        return 0;

    write("You are not allowed into that room.\n");
    return 1;
}

public void
init()
{
    ::init();
    init_library();
}

public void
leave_inv(object player, object dest)
{
    library_leave_inv(player, dest);
    ::leave_inv(player, dest);

}

public int
hook_appoint_unappoint()
{
    if (COUNCIL->is_officer(this_player()->query_real_name()) ||
      this_player()->query_wiz_level())
        return 1;

    return 0;
}

public int
hook_librarian_requirements()
{
    int mtask = (this_player()->query_skill(SS_MASTER_TASK));

    if (MASTER_TITLES[mtask] == "Scholar" ||
      MASTER_TITLES[mtask] == "Historian")
        return 1;
    else if (COUNCIL->is_officer(this_player()->query_real_name()))
        return 1;
    else if (this_player()->query_wiz_level())
        return 1;
    else
        return 0;
}

public mixed
hook_can_access_catalog(int level)
{
    int mtask, wlevel = this_player()->query_wiz_level(); 

    /*
     * 0: Free Access
     * 1: librarian only
     * 2: Pupils+
     * 3: Full Rangers+
     * 4: Mentors+
     * 5: Recruiters+
     * 6: Council/Wizard
     */

     switch(level)
     {
     case 2:
         return(({ IS_RANGER(this_player()) || 
             wlevel, "All Rangers" }));
     case 3:
         return (({ wlevel ||
             (IS_RANGER(this_player()) && 
             !this_player()->query_is_ranger_pupil()), 
             "Full Rangers+" }));
     case 4:
         /* Is a mentor, recruiter, council or wizard */
         mtask = this_player()->query_skill(SS_MASTER_TASK);
         return(({ this_player()->query_ranger_mentor() ||
             MASTER_TITLES[mtask] == "Recruiter" ||
             COUNCIL->is_officer(this_player()->query_real_name()) ||
             wlevel, "Mentors, Recruiters and Council" }));
     case 5:
         mtask = this_player()->query_skill(SS_MASTER_TASK);
         return(({ MASTER_TITLES[mtask] == "Recruiter" ||
             COUNCIL->is_officer(this_player()->query_real_name()) ||
             wlevel, "Recruiters and Council" }));
     case 6:
         return(({ COUNCIL->is_officer(this_player()->query_real_name()) ||
             wlevel, "Council Only" }));
     default:
         return (({ 0, "No Access" }));
     }
}

