//-*-C++-*-
// file name:      library.c
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:
#include "../guild.h";

inherit ROOM_DIR+"vamp_room";
//inherit "/d/Genesis/lib/post";
//inherit "/lib/library";

#include <ss_types.h>
#include <math.h>
#include <composite.h>
#include <std.h>
#include <stdproperties.h>

/*
#define MAILCHECKER    "/secure/mail_checker"
#define DIARY_LOG    (LOG_DIR+"diary")
*/

string * Removed_books=({ });

public void create_vamp_room()
{

    set_short("Library");
    set_long("A small chamber, dry and smelling of old parchment.\n "+
        "Your eyes are captured by the tremendous accumulation of "+
        "books and scrolls overflowing the shelves carved directly "+
        "into the stone of the walls. The room itself is sparsely "+
        "furnished with a few tables and chairs that appear "+
        "to be refugees from an ancient time. Some carpets "+
        "are strewn about, faded and worn, but still beautiful.\n");

    add_prop(OBJ_S_SEARCH_FUN, "search_items");

    add_item(({"carpet", "carpets", "faded carpets", "worn carpets",
        "beautiful carpets"}), "These carpets are without a doubt "+
        "hundreds of years old, but their faded colours are still "+
        "striking and the craftsmanship as good, or better than, "+
        "the finest Sybarun carpets made today.\n");
    add_item(({"books", "scrolls"}), 
        "There are so many of them that they are overflowing the "+
        "shelves. You find yourself wondering what knowledge they "+
        "contain, and if you have the ability to read even a small "+
        "fraction of them.\n");
    add_item(({"floor"}), "The floor is level, covered by carpets in "+
        "some places, and the same stone material as the rest of the room.\n");
    add_item(({"ceiling"}), "The ceiling is the same "+
        "height as most of the other ceilings in this place.\n");
    add_item(({"wall", "walls", "stone", "natural stone"}), 
        "The walls are cut from the natural subterranean stone. They are "+
        "completely unadorned and unpolished.\n");
    add_cmd_item(({"book", "books","scrolls", "scroll"}), ({"get", "take"}), 
        "No matter how hard you try, it seems to evade your grasp.\n");
    add_item(({"table", "tables"}), 
        "There are a few tables here. They have a thick patina of age, "+
        "with crackled finishes and decorations so faded that it is "+
        "impossible to determine what they once represented.\n");
    add_item(({"chair", "chairs"}), 
        "A half dozen unmatching chairs are pulled up to the tables for "+
        "reading comfort. All are so old as to be ancient, and a few even "+
        "have scorch marks.\n");
    add_item(({"scorch marks", "marks"}),  "These marks indicate that "+
        "this piece of furniture was salvaged from a fire.\n");
    add_cmd_item(({"chair","chairs"}), ({"sit on", "sit"}), 
        "Pulling out a chair, you sit on it. It gives a protesting CREAK "+
        "but holds your weight all the same.\n");
    add_cmd_item(({"table","tables"}), ({"sit at", "sit"}), 
        "You pull out a chair and sit on it. It gives a protesting CREAK "+
        "but holds your weight all the same.\n");
    add_cmd_item(({"carpet","carpets"}), ({"sit on", "sit"}), 
        "You lower yourself to the floor and sit on one of the carpets. "+
        "It is thick enough that you are quite comfortable.\n");
    add_cmd_item(({"carpet","carpets"}), ({"lift", "move"}), 
        "You take a moment to lift each carpet and look under it. "+
        "but find nothing of interest.\n");
    add_item(({"darkness"}), 
        "Ebbing and flowing through the chamber, this darkness has a "+
        "substance to it that no amount of light can conquer.\n");
    add_cmd_item(({"air", "blood"}), ({"smell", "sniff", "breathe"}),
        "The air is ripe with the coppery scent of blood.\n");

//    add_prop(VAMP_CAN_START_HERE,1);
    
    add_exit("chamber","east");
//    add_exit("library_p", "west", "@@west_check@@", 1, 1);


    
    /* Indicate if we want players to have to "borrow" a book in
     * order to read it.
     */
//    set_borrow_required(1);

//    set_book_directory(BOOK_DIR);
//    set_book_approval_directory(BOOK_DIR+"pending/");
//    set_book_removal_directory(BOOK_DIR+"removed/");
  
//    add_book_shelf(({ "general", "maps",  }));
        
//    create_library();

    /* Add a sign that gives instructions on how to use the library */
//    add_item("sign", library_help());
//    add_cmd_item("sign","read", library_help());
//    add_item(({"bookshelves","bookshelf","stone bookshelves", "shelves",
//        "shelf"}),
//        "They appear to be carved into the stone.\nAbove the shelves is "+
//        "posted a sign that reads:\n\nYou do not have to borrow the books "+
//        "inorder to read them.\n@@library_help@@\n");

}

/*
public string 
search_items(object player, string str)
{      
     switch (str)
     {
        case "west wall":    
        case "shelves":  
        case "shelf":  
        case "west shelf":
        case "west shelves":
        if (IS_VAMP(TP))
        {
            player->add_prop("_vamp_i_found_peg", 1);
            return "Your fingers find a small peg cleverly hidden "+
                   "amongst the shelves.\n";
            break;
        }
        break;
        default:  return "";
    }
    return "";    
}

int
west_check()
{
    if (TP->query_prop("_vamp_i_found_peg") < 2)
    {
        TP->catch_msg("There is no obvious exit west.\n");
        return 1;  
    }
    else
    {
        TP->catch_msg("You slip through the space between the "+
           "shelves and into the room beyond.\n");
        TP->remove_prop("_vamp_i_found_peg");
//        write_file(DIARY_LOG,ctime(time())+" I noticed "+
//            capitalize(TP->query_real_name()) +" entering the private library.\n");
        return 0;
    }
    return 1;
}

int 
do_push(string str)
{

    if (!TP->query_prop("_vamp_i_found_peg"))
    {
        notify_fail("What?\n");
        return 0;
    }

    notify_fail("Are you trying to press the peg?\n");
    if (!parse_command(str, ({ }), "[the] 'peg'"))
        return 0;    

    write("You press on the peg.\nThere is a rush of air "+
        "and a section of the west shelves slides away from you, "+
        "opening just wide enough for you to slip though, if you "+
        "hurry.\n");
    TP->add_prop("_vamp_i_found_peg", 2);
    return 1;
}

public void init()
{
    ::init();

    add_action(do_push, "push");
    add_action(do_push, "press");

//    post_init();

//    init_library();    
}
*/

/*
int
query_mail(int silent) 
{
    string new,sp;
    int mail;

    mail = MAILCHECKER->query_mail();
    if (!mail)
        return 0;
    if (silent)
        return 1;
    new = ""; sp="      ";
// *  0  - there is no mail at all for the player;
// *  1  - there is mail for the player, though all read;
// *  2  - there is new mail for the player;
// *  3  - there is unread mail for the player, but there is no new mail.

    switch (mail)
    {
        case 2:
            new = " NEW";
            sp="   ";
            break;
        case 3:
            new = " UNREAD";
            sp="";
            break;
    }
    sp+="             ";
    write("\n\n\n");
    write(".---------------------------------------------------------.\n");
    write("| There is"+new+" mail for you in the library."+sp+"|\n");
    write("`---------------------------------------------------------'\n");
    write("\n\n\n");
    return 1;
}

void
add_aliases(object reader)
{
    reader->set_alias("coven", OCC_MANAGER->query_all_guild_members());
 
   if (IS_VAMP(TP))
    {
        reader->set_alias("bloodguards", LAY_MANAGER->query_all_guild_members());
    }

    return;
}

*/