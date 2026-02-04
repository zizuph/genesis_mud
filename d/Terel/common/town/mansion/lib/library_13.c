#include "lib_defs.h"
inherit "/d/Terel/common/town/mansion/lib/library_room.c";

#include <ss_types.h>

int case_open = 0;

public void
create_room()
{
    set_short("Library");
    set_long("You are in a narrow alcove, formed by a damaged " +
             "bookcase to the west and a rotten set of bookshelves " +
             "that line the northern wall of the room. The air here is " +
             "musty and dry, thick with the smell of ancient parchment " +
             "and rotting wood.\n");
 
    add_exit(LIBRARY + "library_14", "south", 0, 1);

    add_item(({"books", "book"}), "There must be hundreds of tomes here, " +
             "ranging from small pamphlets to massive volumes. Many seem " +
             "to be in fine shape, but on closer inspection you realize " +
             "that most are in fact unreadable...time has faded the ink " +
             "as bookworms and mold have eaten the pages. You cannot even " +
             "make out the titles on the spines in most cases, but most " +
             "seem to begin with the letters 'S' and 'T'.\n");
    add_item(({"bookshelf", "damaged bookshelf", "bookcase",
               "damaged bookcase"}), "@@bookcase_long@@");
    add_item(({"bookcases", "shelves", "shelf","bookshelves"}),
             "These decaying bookshelves line the walls from floor " +
             "to ceiling, each filled with ancient texts of every kind.\n");
    
    add_prop(ROOM_I_INSIDE, 1);
}

public string
bookcase_long()
{
    string catch_on;
    
    if (case_open)
        return "Behind the open bookcase is a secret room. " +
               "You can enter it to the northwest.\n";

    if (TP()->query_skill(SS_AWARENESS) > 30)
        catch_on = " Maybe it's the faint breeze you feel on your " +
                   "face as you examine the bookcase, almost as if " +
                   "another room were hidden beyond!\n";
    else
        catch_on = "\n";
    
    return "Though the shelves have collapsed and their books litter " + 
           "the floor, this damaged bookcase certainly seems ordinary " +
           "enough. Still, something bothers you about it..." + catch_on;
}

public void
close_bookcase()
{
    if (!case_open) return;

    tell_room(this_object(), "The bookcase swings back and closes, " +
              "joining seamlessly with the wall.\n");
    remove_exit("northwest");
    remove_my_desc();
    case_open = 0;
}

public int
push_open(string str)
{
    notify_fail("Push what?\n");
    
    if (!str) return 0;
    
    if (str != "bookcase" && str != "case") return 0;

    if (case_open) {
        write("But it's already open!\n");
    }
    else
    {
        write("You set your hands against the damaged bookcase, and " +
              "shove with all your strength. At first nothing happens, " +
              "but soon you feel the bookcase shudder, and with a " +
              "tremendous creak the wall seems to part before you! You " +
              "feel a rush of air, dry and stale, from the secret " +
              "chamber, undisturbed these many long years.\n");
        write("The secret chamber may be entered to the northwest.\n");
        add_exit(LIBRARY + "index_room", "northwest");
        add_my_desc("An innocent-looking bookcase in the northwest " +
                "corner has been pushed back, revealing a secret passage!\n");
        say(QCTNAME(this_player()) + " pushes on the damaged bookcase, " +
            "which opens beneath " + this_player()->query_possessive() +
            " hands!\n");
        case_open = 1;
        set_alarm(30.0, -1.0, close_bookcase);
    }
    return 1;
}

public void
init()
{
    ::init();
    add_action(push_open, "push");
}
