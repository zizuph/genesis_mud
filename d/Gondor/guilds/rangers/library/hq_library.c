/*
 *  /d/Gondor/guilds/rangers/library/hq_library.c
 *
 *  Originally coded by:  Gwyneth?
 *
 *    Modification Log:
 *        09 March 2002 -- Moved and slightly modified for new rangers.
 *
 *  TODO: CHANGE PATH IN set_lib_path() to domain directory
 *        ALSO CHANGE IN hq_library.o
 */

inherit "/std/room";
inherit "/d/Gondor/std/library/library";

#include <files.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include "../titles.h"

/* Prototypes */
public int ranger_check();
public string exa_poster();

object gScroll;

public void
reset_room()
{
    ::reset_room();

    if (!objectp(gScroll))
    {
        gScroll = clone_object(RANGERS_SPELL + "obj/pigeon_scroll");
        gScroll->move(this_object());
    }
}

public void
create_room()
{
    set_short("In the Library of the Rangers");
    set_long("You are in a large hall with a domed ceiling. Along "+
        "the walls and on the floor are shelves. All the shelves are " +
        "filled with books of varied colours, sizes and ages. At a desk " +
        "in the south-eastern corner of the room sits an aging man, " +
        "probably the librarian. A doorway leads out to the corridor south. " +
        "Your glance stops at a poster " +
        "by the open door, which reads: No talking! Further down on the " +
        "poster you see some instructions.\n");

    add_exit(RANGERS_HQ_DIR + "dcorridor1",   "south", 0, 1);

    add_item(({"floor", "wooden floor", "ground"}), "The floor here "
        + "is made from long sturdy planks of wood. Near the walls you "
        + "can still make out the lustrous varnish that once made this floor "
        + "shine like a mirror. In most places, however, the finish has "
        + "long been worn away by the passage of generations of booted "
        + "feet.\n");
    add_item(({"varnish", "finish", "stain"}), "The floor was once finished "
        + "with a deep red stain, protected by clear resin buffed to a shine. "
        + "Only those places out of the way of booted feet, however, have "
        + "survived the ages unscathed.\n");
    add_item(({"planks", "sturdy planks"}), "The floor is made up of long "
        + "planks of oak, milled from the trees of the Druedain forest.\n");
    add_item(({"wall", "walls", "panel", "panels", "oak panel", "oak panels"}), 
        "The walls, like most things in the "
        + "hideout, are constructed from wood. You feel a warm glow in this "
        + "place, rather unlike the cold stone rooms and dwellings in "
        + "so-called civilized regions.\n");
    add_item(({"ceiling"}), "The ceilings of the hideout arch above you, "
        + "supported by massive crossbeams.\n");
    add_item(({"crossbeams", "massive crossbeams", "beams", "beam", 
        "oak beams"}), "The crafting of the "
        + "ceiling must have required amazing labour and skill. The beams "
        + "supporting it look to be made of entire sections of tree.\n");
    add_item(({"hideout", "central headquarters", "headquarters"}), "It "
        + "is all around you. To take in the entire building, you would need "
        + "to step outside. Even then, much of it would be hidden from "
        + "casual view.\n");
    add_item(({"wood"}), "Almost everything in the hideout seems to be made "
        + "of sturdy hardwoods milled from the Druedain forest by the "
        + "men of Gondor.\n");
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

    set_lib_long("the Library of the Rangers");
    set_lib_id("hq_lib_id");
    set_lib_path("/d/Gondor/guilds/rangers/library");
    set_default_topics(([ "General" : 0, "New Arrivals" : 1,
        "Trash" : 1 ]));
    set_lib_type(4);
    set_search_delay(1.5);
    set_max_librarian_num(8);
    setup_library();

    reset_room();
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
      this_player()->query_is_officer())
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
            "       0: General Public+          1: Librarian Only\n" +
            "       2: Apprentices+             3: Full Rangers+\n" +
            "       4: Recruiters and Council   5: Council\n" +
            "       6: Ithilien Rangers         7: Rangers of the North\n" +
            "       8: Officers of Ithilien     9: Officers of the North\n" +
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

    if (RANGERS_MEMBER(this_player()))
        return 0;

    if (wiz_level)
        return 0;

    write("You are not allowed into that room.\n");
    return 1;
}

public void
add_vote_book(string company)
{
    string thebook;

    if (!strlen(company))
        return;

    company = capitalize(company);
    if (company == "Gondor")
    {
        thebook = "Votes_" + extract(ctime(time()), -4);

        /* If the book is already there, don't let it be added again. */
        if (member_array(thebook, m_indexes(gBooks)) != -1)
            return;

        add_new_book("A dark leather book with the " +
            "emblem of the Rangers of the Westlands on the cover.\n",
            "dark leather book", thebook + " - A recording of the Ranger " +
            "council votes.", "These are the votes of the Councils of " +
            "both companies.\n");

        /* The topic doesn't exist. */
        if (member_array("Reference", m_indexes(gTopics)) == -1)
            return;

        gBooks[lower_case(thebook)][1] = "Reference";
    }
    else
    {
        thebook = "Votes_" + capitalize(company) + "_" + 
            extract(ctime(time()), -4);

        /* If the book is already there, don't let it be added again. */
        if (member_array(thebook, m_indexes(gBooks)) != -1)
            return;

        add_new_book("A dark leather book with the " +
            "emblem of the Rangers of the Westlands on the cover.\n",
            "dark leather book", thebook + " - A recording of the Ranger " +
            "council votes.", "These are the votes of the " + company + 
            " Council.\n");

        /* The topic doesn't exist. */
        if (member_array(company, m_indexes(gTopics)) == -1)
            return;

        gBooks[lower_case(thebook)][1] = company;
    }

    save_object(MASTER);
    return;
}

public int
create_limit()
{
    if (m_sizeof(gTopics) > 35)
    {
        write("You have reached the maximum number of topics. No new " +
            "topic will be created.\n");
        return 1;
    }
}

public void
init()
{
    ::init();
    init_library();

    add_action(create_limit, "create");
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
    if (this_player()->query_is_officer() ||
        this_player()->query_wiz_level())
        return 1;

    return 0;
}

public int
hook_librarian_requirements()
{
    string name;

    name = this_player()->query_real_name();

    if (MANAGER->query_master_specialty(name) == "Scholar" ||
        MANAGER->query_master_specialty(name) == "Historian" ||
        MANAGER->query_specialist_specialty(name) == "Scholar" ||
        MANAGER->query_specialist_specialty(name) == "Historian")
        return 1;
    else if (this_player()->query_is_officer())
        return 1;
    else if (this_player()->query_wiz_level())
        return 1;
    else
        return 0;
}

public mixed
hook_can_access_catalog(int level)
{
    int wlevel = 0;
    string name = this_player()->query_real_name();
    
    if (SECURITY->query_wiz_dom(name) == "Gondor" ||
      SECURITY->query_wiz_rank(name) >= WIZ_ARCH)
      wlevel = 1;

    /*
     * 0: Free Access
     * 1: librarian only
     * 2: Pupils+
     * 3: Full Rangers+
     * 4: Recruiters+
     * 5: Council/Wizard
     * 6: Rangers of Ithilien
     * 7: Rangers of the North
     * 8: Officers of Ithilien
     * 9: Officers of the North
     */

     switch(level)
     {
     case 2:
         return(({ RANGERS_MEMBER(this_player()) || 
             wlevel, "All Rangers" }));
     case 3:
         return (({ wlevel ||
             (RANGERS_MEMBER(this_player()) && 
             this_player()->query_ranger_level() > 2), 
             "Full Rangers+" }));
     case 4:
         return(({ MANAGER->query_master_specialty(name) == "Recruiter" ||
             MANAGER->query_specialist_specialty(name) == "Recruiter" ||
             this_player()->query_is_officer() ||
             wlevel, "Recruiters and Council" }));
     case 5:
         return(({ this_player()->query_is_officer() ||
             wlevel, "Council Only" }));
     case 6:
         return(({ this_player()->query_ranger_level() == ITHILIEN_LEVEL ||
             wlevel, "Rangers of Ithilien" }));
     case 7:
         return(({ this_player()->query_ranger_level() == NORTH_LEVEL ||
             wlevel, "Rangers of the North" }));
     case 8:
         return(({ (this_player()->query_ranger_level() == ITHILIEN_LEVEL &&
           this_player()->query_is_officer()) || wlevel, 
           "Officers of Ithilien" }));
     case 9:
         return(({ (this_player()->query_ranger_level() == NORTH_LEVEL &&
           this_player()->query_is_officer()) || wlevel, 
           "Officers of the North" }));
     default:
         return (({ 0, "No Access" }));
     }
}

