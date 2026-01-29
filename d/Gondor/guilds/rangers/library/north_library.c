/*
 *  /d/Gondor/guilds/rangers/north/library.c
 *
 *  A library for the North Company
 *
 */
inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/std/library/library";

#include "../rangers.h"

inherit RANGERS_NOR_DIR + "north_funcs.c";

#include <files.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include "../titles.h"
#include "../north/check_exit.c"

public void leave_inv(object ob, object dest);

static object parazir;

/* Prototypes */
public string exa_poster();

public string long_desc();

string
long_desc()
{

    return "You have entered a small room lined with sturdy wooden shelves, " +
        "each holding dozens of books. The shelves have been mounted on " +
        "the same dark grey stone that covers the walls, floors and ceiling " +
        "of the northern hideout. In the middle of this little library, " +
        "a wide table is surrounded by several chairs, providing a " +
        "comfortable place to study. A poster has been tacked up on " +
        "the southern wall, providing instructions for anyone who wants " +
        "to make use of the library. A wide opening in the western wall " +
        "opens up into the meeting room and the rest of the hideout.\n";
}

public void
create_gondor()
{
    set_short("Library");
    set_long(&long_desc());

    north_add_items();

    add_item(({"room", "library", "here"}), &long_desc());
    add_item(({"northern wall", "north wall"}), 
        "The northern wall of the library is filled with shelves of books!\n");
    add_item(({"eastern wall", "east wall"}), 
        "The easthern wall of the library is filled with shelves of books!\n");
    add_item(({"southern wall", "south wall"}), 
        "The southern wall of the library is filled with shelves of books! " +
        "You also notice a lengthy poster with instructions on how to best " +
        "use the library.\n");
    add_item(({"western wall", "west wall"}), 
        "The western wall of the library has a wide opening leading into " +
        "the meeting room and the rest of the northern hideout. A burning " +
        "torch hangs in a stand beside the arch.\n");
    add_item(({"ceiling", "up"}),
        "Much like the rest of the hideout, the ceiling has been crafted " +
        "from a dark grey stone.\n");
    add_item(({"down", "floor"}),
        "The dark grey of the stone here is slightly uneven, but still " +
        "smooth enough to walk comfortably upon.\n");
    add_item(({"stone", "grey stone"}),
        "This dark grey stone seems to have been the primary building " +
        "material for the foundation of this hideout.\n");
    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");
    add_item(({"torch", "stand", "iron stand", "iron torch stand",
            "torch stand"}),
        "This iron stand holds a torch to provide a little bit of " +
        "light in the library.\n");
    add_item(({"arch", "opening", "wide arch", "stone arch", "wide opening"}),
        "This wide opening in the western wall arches up almost to the " +
        "ceiling and provides access into the meeting room.\n");
    add_item(({"shelf", "shelves", "wooden shelf", "wooden shelves",
            "wood shelf", "wood shelves"}),
        "Dozens of wooden shelves have been mounted on every bit of " +
        "wall space to be found within this library.\n");
    add_item(({"table", "wooden table", "wood table", "wide table"}),
        "This wide table looks like a perfect place to study in peace.\n");
    add_item(({"chair", "wooden chair", "wood chair", "sturdy chair",
            "chairs", "wooden chairs", "wood chairs", "sturdy chairs"}),
        "There are six sturdy wooden chairs here, clearly for the " +
        "comfort of any rangers who might wish to use the library.\n");


    add_item(({"poster", "instructions"}), &exa_poster());
    add_cmd_item(({"poster", "instructions"}), "read", &exa_poster());

    set_lib_id("north_lib_id");
    set_lib_path("/d/Gondor/guilds/rangers/north");
    set_default_topics(([ "Arnor" : 0, "New Arrivals" : 1,
        "Trash" : 1 ]));
    set_lib_type(4);
    set_search_delay(6.7);
    set_max_librarian_num(5);
    setup_library();

    add_exit(RANGERS_NOR_DIR + "meeting_room", "west");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_M_NO_SCRY, 1);

    reset_room();
}

reset_room() 
{
    if(!parazir) parazir = clone_object(RANGERS_NPC + "parazir.c");
    if (!present(parazir)) parazir->move_living("somewhere", this_object());
}

void
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
            "\n" +
            " New books will be placed under New Arrivals. Librarians \n" +
            "       should check that shelf with 'catalog new arrivals' \n" +
            "       on a regular basis.\n\n " +
            " Retire as a librarian\n\n" +
            "Council members do not have these abilities, but they may:\n" +
            " Appoint <name> as librarian\n" +
            " Unappoint <name> as librarian\n";
    }
 
    return text;
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
