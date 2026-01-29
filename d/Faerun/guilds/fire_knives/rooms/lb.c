/* /d/Faerun/guilds/fire_knives/rooms/lb.c
 *
 * Library
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;
inherit "/lib/guild_library";
inherit "/d/Faerun/lib/tail.c";

#define JO_LOG "/d/Faerun/guilds/fire_knives/log/join_log"
#define FULLM_LOG "/d/Faerun/guilds/fire_knives/log/fullmember_log"
#define PROM_LOG "/d/Faerun/guilds/fire_knives/log/promote_log"
#define DEM_LOG "/d/Faerun/guilds/fire_knives/log/demote_log"
#define EXPE_LOG "/d/Faerun/guilds/fire_knives/log/expelled_log"
#define LEAV_LOG "/d/Faerun/guilds/fire_knives/log/leave_log"
#define JOINPER_LOG "/d/Faerun/guilds/fire_knives/log/join_per_log"
#define FULLMP_LOG "/d/Faerun/guilds/fire_knives/log/fullm_per_log"
#define EXE_LOG "/d/Faerun/guilds/fire_knives/log/execute_log"

object librarian;

public string join_log();
public string fullmember_log();
public string promote_log();
public string demote_log();
public string expelled_log();
public string leave_log();
public string execute_log();
public string join_per_log();
public string fullm_per_log();

#define NO  0
#define YES 1


public string execute_log()
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return "Only the High Table may read this record.\n";
    }
    
    write("You read the log containing the information "
    +"about members being executed as a punishment by "
    +"a Brotherhood council member:\n");
    
    seteuid(getuid());
    
    if (query_verb() == "tail")
    {
        tail_file(EXE_LOG);
    }
    else
    {
        this_player()->more(read_file(EXE_LOG, 1), 0);
    }

    tell_room(this_object(), QCTNAME(this_player())
        + " reads one of the records.\n", this_player());
        
    return "";
}


public string fullm_per_log()
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return "Only the High Table may read this record.\n";
    }
    
    write("You read the log containing the information "
    +"about when various Candidates received the permission to "
    +"become a full of the Brotherhood:\n");
    
    seteuid(getuid());
    
    if (query_verb() == "tail")
    {
        tail_file(FULLMP_LOG);
    }
    else
    {
        this_player()->more(read_file(FULLMP_LOG, 1), 0);
    }

    tell_room(this_object(), QCTNAME(this_player())
        + " reads one of the records.\n", this_player());
        
    return "";
}


public string join_per_log()
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return "Only the High Table may read this record.\n";
    }
    
    write("You read the log containing the information "
    +"about when various applicants received the permission to "
    +"joined the Brotherhood by a council member:\n");
    
    seteuid(getuid());
    
    if (query_verb() == "tail")
    {
        tail_file(JOINPER_LOG);
    }
    else
    {
        this_player()->more(read_file(JOINPER_LOG, 1), 0);
    }

    tell_room(this_object(), QCTNAME(this_player())
        + " reads one of the records.\n", this_player());
        
    return "";
}


public string join_log()
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return "Only the High Table may read this record.\n";
    }
    
    write("You read the log containing the information "
    +"about when various members joined the Brotherhood:\n");
    
    seteuid(getuid());
    
    if (query_verb() == "tail")
    {
        tail_file(JO_LOG);
    }
    else
    {
        this_player()->more(read_file(JO_LOG, 1), 0);
    }

    tell_room(this_object(), QCTNAME(this_player())
        + " reads one of the records.\n", this_player());
        
    return "";
}


public string fullmember_log()
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return "Only the High Table may read this record.\n";
    }
    
    write("You read the log containing the information "
    +"about when various members became full members of the Brotherhood:\n");
    
    seteuid(getuid());
    
    if (query_verb() == "tail")
    {
        tail_file(FULLM_LOG);
    }
    else
    {
        this_player()->more(read_file(FULLM_LOG, 1), 0);
    }

    tell_room(this_object(), QCTNAME(this_player())
        + " reads one of the records.\n", this_player());
        
    return "";
}


public string promote_log()
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return "Only the High Table may read this record.\n";
    }
    
    write("You read the log containing the information "
    +"about when various members received a promotion:\n");
    
    seteuid(getuid());
    
    if (query_verb() == "tail")
    {
        tail_file(PROM_LOG);
    }
    else
    {
        this_player()->more(read_file(PROM_LOG, 1), 0);
    }

    tell_room(this_object(), QCTNAME(this_player())
        + " reads one of the records.\n", this_player());
        
    return "";
}


public string demote_log()
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return "Only the High Table may read this record.\n";
    }
    
    write("You read the log containing the information "
    +"about when various members received a demotion:\n");
    
    seteuid(getuid());
    
    if (query_verb() == "tail")
    {
        tail_file(DEM_LOG);
    }
    else
    {
        this_player()->more(read_file(DEM_LOG, 1), 0);
    }

    tell_room(this_object(), QCTNAME(this_player())
        + " reads one of the records.\n", this_player());
        
    return "";
}


public string expelled_log()
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return "Only the High Table may read this record.\n";
    }
    
    write("You read the log containing the information "
    +"about when various members was expelled from the Brotherhood:\n");
    
    seteuid(getuid());
    
    if (query_verb() == "tail")
    {
        tail_file(EXPE_LOG);
    }
    else
    {
        this_player()->more(read_file(EXPE_LOG, 1), 0);
    }

    tell_room(this_object(), QCTNAME(this_player())
        + " reads one of the records.\n", this_player());
        
    return "";
}


public string leave_log()
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return "Only the High Table may read this record.\n";
    }
    
    write("You read the log containing the information "
    +"about when various members betrayed and left the Brotherhood:\n");
    
    seteuid(getuid());
    
    if (query_verb() == "tail")
    {
        tail_file(LEAV_LOG);
    }
    else
    {
        this_player()->more(read_file(LEAV_LOG, 1), 0);
    }

    tell_room(this_object(), QCTNAME(this_player())
        + " reads one of the records.\n", this_player());
        
    return "";
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

     set_short("Within the keeps' library");
    
    set_long("Rows upon rows of shelves full of books line up the walls of "
    +"this great hall, their various sections properly marked and sealed "
    +"by varifying degrees of rank and prestige. Towards the end of the room "
    +"up a few steps is a dome like section of archives which seems to be "
    +"out of bounds at first glance, from it extend two wings, one to each "
    +"side, each section separated by a burning torch hanging from a sconce "
    +"in the wall. The stone floor is bare, radiating cold, yet smooth and "
    +"clean which, when combined with the warmth of the torches "
    +"and the room's structure, maintains a proper level of "
    +"freshness for the tomes' maintenance. Next to a shelf containing "
    +"various records of the Brotherhood, you see a plaque is hanging on "
    +"the west wall for instructions.\n");
    
    add_item(({"shelves","rows","books"}),
    "Rows of shelves line up the entire walls "
    +"of this great hall. All full of books, "
    +"scrolls and tomes of various shapes and sizes.\n");

    add_item(({"walls","wall"}),
    "The walls are covered in shelves holding books, "
    +"scrolls and tomes of various "
    +"shapes and sizes as high as the eye can see. \n");

    add_item(({"hall","great hall","structure"}),
    "The hall is quite spacious with a hollow "
    +"center where a single long table "
    +"lined with chairs is placed.\n");

    add_item(({"table","long table"}),
    "The wooden table is long and rectangular, "
    +"with evenly placed chairs along its "
    +"length. It would seem this is the place "
    +"to sit if you'd like to read a book "
    +"rather than perusing the shelves, or even write one to submit.\n");
    
    add_item(({"chair","chairs"}),
    "The chairs are simple and wooden, placed "
    +"evenly along the length of the table "
    +"for anyone to sit on.\n");

    add_item(({"sections"}),
    "The shelves are divided into various sections. "
    +"The main division being the two "
    +"wings extending from the dome in the far end of the room.\n");
    
    add_item(({"steps","dome","archives"}),
    "The shelves past the steps upwards under a "
    +"dome-like structure seem to be out of "
    +"bounds at first glance. The books in them "
    +"looking similar to the rest filling the "
    +"library, and differing from the others only in content.\n");
    
    add_item(({"wings"}),
    "There are two wings you can examine: the one "
    +"to the left and the one to the right.\n");
    
    add_item(({"right wing"}),
    "The right wing contains the books marked for "
    +"full members of the guild. Each section "
    +"properly divided according to rank and prestige within it.\n");
    
    add_item(({"left wing"}),
    "The left wing contains the books marked for "
    +"trainees and candidates who still haven't "
    +"earned their place in full trust to the brotherhood.\n");

    add_item(({"torch","burning torch","sconce"}),
    "The torches are lit and burn slow, marking "
    +"the space between each section along the "
    +"line of shelves in the walls.\n");

    add_item(({"floor","stone floor"}),
    "The stone floor is bare, yet clean and polished. "
    +"From it emanates a cooling sensation "
    +"that serves to maintain the right temperature "
    +"within the hall.\n");
    
    add_item(({"record", "records"}),
    "There are several records in one of the "
    +"shelves: dusty record, fine record, golden record, "
    +"scorched record, dark record, red record, blue record, "
    +"green record and a beige record. Which "
    +"one do you want to read?\n");
    
    add_item(({ "dusty record" }), join_log);
    add_cmd_item(({ "dusty record" }), 
    ({ "read", "tail" }), join_log);
    
    add_item(({ "fine record" }), fullmember_log);
    add_cmd_item(({ "fine record" }), 
    ({ "read", "tail" }), fullmember_log);
    
    add_item(({ "golden record" }), promote_log);
    add_cmd_item(({ "golden record" }), 
    ({ "read", "tail" }), promote_log);
    
    add_item(({ "scorched record" }), demote_log);
    add_cmd_item(({ "scorched record" }), 
    ({ "read", "tail" }), demote_log);
    
    add_item(({ "dark record" }), expelled_log);
    add_cmd_item(({ "dark record" }), 
    ({ "read", "tail" }), expelled_log);
    
    add_item(({ "beige record" }), leave_log);
    add_cmd_item(({ "beige record" }), 
    ({ "read", "tail" }), leave_log);
    
    add_item(({ "red record" }), execute_log);
    add_cmd_item(({ "red record" }), 
    ({ "read", "tail" }), execute_log);
    
    add_item(({ "blue record" }), join_per_log);
    add_cmd_item(({ "blue record" }), 
    ({ "read", "tail" }), join_per_log);
    
    add_item(({ "green record" }), fullm_per_log);
    add_cmd_item(({ "green record" }), 
    ({ "read", "tail" }), fullm_per_log);

    add_exit(FIREKNIVES_ROOMS_DIR 
    + "o5", "east", "@@prevent_leave_with_books@@", NO);
    
    set_library_save_path(FIREKNIVES_LIBRARY_DIR + "fireknives/");
    set_library_save_file(FIREKNIVES_LIBRARY_DIR + "fireknives_library");
    set_library_allow_new_books(YES);
    set_library_book_type("scroll");
    set_library_book_object(FIREKNIVES_LIBRARY_DIR + "blank_scroll");
    set_library_log_file("fireknives_library_log");
    
    add_library_access_level("postulants", "Postulants+");
    add_library_access_level("initiates", "Initiates+");
    add_library_access_level("candidates", "Candidates+");
    add_library_access_level("shadows", "Dark Shadows+");
    add_library_access_level("shades", "Midnight Shades+");
    add_library_access_level("scythes", "Whispering Scythes+");
    add_library_access_level("asps", "Fearsome Asps+");
    add_library_access_level("enders", "Enders of Dreams+");
    
    add_library_access_level("council", "The Council");
    
	
	set_library_librarian_level("librarian");
    set_library_librarian_level("council");
 
    add_item(({"plaque", "instructions", }), library_help);
    add_cmd_item(({"plaque", "instructions", }), "read", library_help);
   
    create_library();

    reset_faerun_room();
}


/*
 * Function name: query_librarian
 * Description  : See if a person is a librarian
 * Arguments    : player - the player we want to check
 * Returns      : 0 on failure, 1 on success
 */
int query_librarian(object player)
{
	if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(player->query_name()) ||
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(player->query_name()) ||
        FIREKNIVES_MASTER->is_occ_boss_fireknife(player->query_name()) ||
		FIREKNIVES_MASTER->is_occ_librarian(player->query_name()) ||
        player->query_wiz_level())
    {
		return 1;
	}

    // Other members are no librarian.
    return 0;
}


void init()
{
    ::init();
    init_library();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
    
    if (!librarian)
    {
        librarian = clone_object(FIREKNIVES_GUILD_DIR + "npc/librarian");
        librarian->move(this_object(), 1);
    }
}


void leave_inv(object ob, object to)
{
    library_leave_inv(ob, to);
    ::leave_inv(ob, to);
}


/*
 * Function name: query_player_access
 * Description  : Return a list of the levels that the player have access to
 * Arguments    : player - the player we want to check
 * Returns      : an array with access levels
 */
string *query_player_access(object player)
{
    string  *access;
    int     rank;
    
    access = ({ "postulants" });
    
    rank = FIREKNIVES_MAPPINGS->query_assassin_rank(player->query_name());
        
    if(player->query_wiz_level()) 
    {
        rank = 100;
        access += ({ "council" });
    }
	
	/*if (FIREKNIVES_MASTER->is_occ_librarian(player->query_name()))
	{
		rank = 28;
		access += ({ "librarian" });
	}*/
    
    if(rank >= 2) access += ({ "initiates" });
    if(rank >= 5) access += ({ "candidates" });
    if(rank >= 10) access += ({ "shadows" });
    if(rank >= 15) access += ({ "shades" });
    if(rank >= 20) access += ({ "scythes" });
    if(rank >= 25) access += ({ "asps" });
    if(rank >= 28) access += ({ "enders" });
	
    
    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(player->query_name()) ||
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(player->query_name()) ||
        FIREKNIVES_MASTER->is_occ_boss_fireknife(player->query_name()) ||
		FIREKNIVES_MASTER->is_occ_librarian(player->query_name()) ||
        player->query_wiz_level())
    {
        access += ({ "council" });
    }
    
    // Return the shelves
    return access;
}


/*
 * Function name: library_help
 * Description  : Get the help based on this_player()'s permissions
 * Returns      : a string
 */
string library_help()
{
    string  result;
    string head_line = "\t+-------------------------------------------------------------+\n";
    string blank_line ="\t|                                                             |\n";
    // Header
        result = head_line;
        result += blank_line;
        result +="\t|  The following commands are available in this library:      |\n" +
           blank_line;

    // Regular commands
        result +="\t|    * list [shelf]       - list the available shelves, or    |\n" +
            "\t|                           scrolls on that shelf.            |\n" +
            "\t|    * catalog [shelf]    - same as the list command          |\n" +
            "\t|    * borrow [scroll ID] - borrow the scroll                 |\n" +
            blank_line;

    // Add text when we allow new books
    if(library_allow_new_books)
    {
        result +="\t|  To add to the library, get a [blank scroll]. When you have |\n" +
            "\t|  completed writing your scroll, [submit] it. It will be re- |\n" +
            "\t|  viewed by a librarian and added to the shelves.            |\n" +
            blank_line;
    }
	
	if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) ||
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) ||
        FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) ||
		FIREKNIVES_MASTER->is_occ_librarian(this_player()->query_name()) ||
        this_player()->query_wiz_level())
    {
   result +="\t|  As an editor, you can also do the following commands:      |\n" +
            "\t|    * renumber [old ID] to [new ID]                          |\n" +
            "\t|    * edit [scroll ID]                                       |\n" +
            "\t|    * assign  [scroll ID] to [shelf name]                    |\n" +
            "\t|    * create shelf [shelf name] with title [shelf title]     |\n" +
            "\t|    * rename [old shelf name] to [new shelf name]            |\n" +
            "\t|    * rename [scroll ID] to [new title]                      |\n" +
            "\t|    * change [shelf name] to [new title]                     |\n" +
            "\t|    * access [shelf name] for [level]                        |\n" +
            "\t|    * remove shelf [shelf name]                              |\n" +
            "\t|    * remove scroll [scroll ID]                              |\n" +
            blank_line;

    }

    result += head_line;

    // Gives more help for wizzes
    if(this_player()->query_wiz_level())
    {
        result += "\nImmortals can also 'lock' or 'unlock' "
        +"specific scrolls for editing.\n";
    }

    return result;
}


/*
 * Function name: library_hook_list_books
 * Description  : Called when a player lists the contents of a shelf
 * Arguments    : name - the name of the shelf being listed
 */
void library_hook_list_books(string shelf_name, 
mixed *shelf_data, mixed *books)
{
    int i;

    // Check for empty shelves
    if(sizeof(books) == 0)
    {
        write("The shelf '" + shelf_name + "' is empty.\n");
        return;
    }

    // Display the list
    write(shelf_data[0] + ":\n\n");
    write(sprintf("%-10s %s\n", "ID", "Title"));
    write(sprintf("%-10s %s\n", "----------",
        "-----------------------------------------------------------------"));
    for(i=0;i<sizeof(books);i++)
    {
        write(sprintf("%-10s %s\n",
            books[i],
            library_data["books"][books[i]][1]));
    }
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        if (ob->query_wiz_level())
        {
            WIZARD_ENTRY_LIBRARY_LOG("wizard_entry_library_log",
            "The immortal " +ob->query_name() 
            +" entered the Fire Knives the library.\n");
            
            ob->catch_tell(" >>> YOUR ENTRY HAS BEEN LOGGED. UNLESS YOU HAVE BUSINESS "
            +"HERE, PLEASE IMMEDATELY MOVE ELSEWHERE! <<<\n");
        } 
    }
}


/*
 * Function name: library_hook_stop_leave
 * Description  : Called when a player is stopped while carrying books,
 *              : redefine it to give your own message.
 * Arguments    : player - the player that's trying to leave
 *              : books - an array with the books that have not been returned
 */
void library_hook_stop_leave(object player, object *books)
{
    player->catch_msg("You can't leave the library while possessing "
    +COMPOSITE_DEAD(books) + ".\n");
}
