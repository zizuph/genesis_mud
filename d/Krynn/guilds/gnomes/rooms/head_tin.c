/* Created by Dajala
 * Head Tinkers room
 * Allows:
   - Reading the member lists
   - Mailing
   - Reading the invention log
   - Gives a list of the available modules
   - Reading the concluded and titles log from the folderroom
   - Creation of new folders via the bell
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <composite.h>
#include "../guild.h"
#include "../modules.h" 

#define MAILCHECKER     "/secure/mail_checker"
#define MAILREADER_ID   "_reader_"

inherit "/d/Krynn/std/room";


/* Global variables */

int create_again = 0;
string name, title;


void
create_room()
{
    set_short("Head Tinkers workroom");

    set_long("The head tinkers room contains only functional furniture. " +
    "You spot a desk, cluttered with papers except for the top left corner " +
    "where a golden bell stands, a wooden stool and a red letterbox next to " +
    "it and a drawing board.\n" +
    "On the south wall you see a pinboard displaying several posters.\n");
                
    add_exit(ROOMS + "folderro", "east", 0);

    add_item(({"poster", "posters", "pinboard"}),
    "There are several posters on the pinboard. You see in detail:\n" +
    "A list of the <members> of the inventors guild,\n" +
    "a list of the <projects> currently worked on,\n" +
    "a list of the projects, already <concluded>\n" +
    "a list of the <duties> coming with the office of Head Tinker and\n" +
    "a list of the <modules> available to the members in the workshop.\n" +
    "Try <list>ing these.\n" +
    "A notice on the pinboard states that members can now be <promote>d " +
    "and <demote>d at the whim of the Head Tinker and Assistant Head.\n");
        
    add_item(({"desk", "stool", "drawing board"}),
    "Made from vallenwood trees it has been intended to nearly last " +
    "forever.\n");
        
    add_item(({"letterbox", "red letterbox"}),
    "The Head Tinkers personal letterbox.\n");
        
    add_item(({"letterbox", "red letterbox"}),
    "This is the head tinkers personal letterbox. You may: \n" +
    "    read          - read your mail\n" +
    "    mail <name>   - send a message to <name>\n" +
    "    from          - get a list of your messages\n");
                
    add_item(({"bell", "golden bell"}), "There's a label on it.\n");
        
    add_cmd_item(({"label", "label on bell"}), "read",
    "The label reads:\nProduct of gnomish industries. " +
    "This bell can 'create folder <title of the module> <name of the " +
    "inventor>'. \n" +
    "Exclusive use for the head tinker of the inventor guild.\n");
    
    add_cmd_item("members", "list", "@@list_members");
    add_cmd_item("projects", "list", "@@list_projects");
    add_cmd_item("concluded", "list", "@@list_concluded");
    add_cmd_item("duties", "list", "@@list_duties");
    add_cmd_item("modules", "list", 
    "Currently available are the following modules:\n@@modules");

    INSIDE
    LIGHT
}

void
init()
{
    object mr;
    string title;
	
    ::init();
    ADD("g_promote", "promote");
    ADD("g_demote", "demote");
    ADD("fol_create", "create");
        
    title = TP->query_guild_title_race();
	
    if (!title)
        return;
	
    if ((this_player()->query_guild_title_race()[..13] == "Assistant Head") ||
        TP->query_real_name() == MANAGER->query_headtin_name())
    {
        mr = clone_object("/secure/mail_reader");
        mr->set_alias("mastergnome", GUILDMASTERS);
        mr->move(TP, 1);
    }
}
   
void
leave_inv(object ob, object to)
{
    object reader;
    ::leave_inv(ob, to);
    
    reader = present(MAILREADER_ID, ob);
    if (reader)
        reader->remove_object();
}

string
list_projects()
{
    string *titles;
    int i;

    say(QCTNAME(TP) + " has a look at a poster.\n");
    write("The following projects are currently worked upon:\n");
    seteuid(getuid());
    titles = explode(read_file(FOLDER_DIR + "titles"), "\n");
    for (i = 0; i < sizeof(titles); i++)
        TP->catch_msg("The " + C(titles[i]) + ".\n");
    
    return "";
}

string
list_concluded()
{
    say(QCTNAME(TP) + " has a look at a poster.\n");
    write("The following projects are already concluded:\n");
    seteuid(getuid());
    cat(FOLDER_DIR + "concluded");
    return "";
}

string
list_duties()
{
    say(QCTNAME(TP) + " has a look at a poster.\n");
    seteuid(getuid());
    cat(HEAD_TIN_DUTIES);
    return "";
}

string
list_members()
{
    string *all_members = ({});
    int i, end;
	
    foreach(string member: get_dir(MEMBERS))
    {
        sscanf(member, "%s.o", member);
        
        all_members += ({ capitalize(member) });
    }
    
    say(QCTNAME(TP) + " has a look at a poster.\n");
    write("The following players are members of the inventors guild:\n" +
    COMPOSITE_WORDS(all_members) + ".\n");
    return "";
}

string
modules()
{
    string str = "";
    int i;

    for(i=0;i<sizeof(TYPES);i++)
        str = str + " - The " + capitalize(TYPES[i]) + "\n";
    
    return str;
}

int 
fol_create(string str)
{
    string *buffer;

    NF("Create what? A folder?\n");
    if(!str)
        return 0;

    buffer = explode(str, " ");
    if(buffer[0] != "folder")
        return 0;
	
    NF("Wrong number of arguments. Format: create folder <title> <name>.\n");
    if(sizeof(buffer) != 3)
        return 0;
	
    NF("You're not the Head Tinker!\n");
    if ((this_player()->query_guild_title_race()[0..13] != "Assistant Head") &&
        TP->query_real_name != MANAGER->query_headtin_name())
        return 0;
        
    if(!create_again)
    {
        title = buffer[1];
        name = buffer[2];
        create_again = 1;
        write("Please confirm by typing again.\n");
        return 1;
    }
    
    if(title != buffer[1] || name != buffer[2])
    {
        NF("Control mismatch.\n");
        name = title = "";
        create_again = 0;
        return 0;
    }
	
    if(read_file(FOLDER_DIR + title) != 0)
    {
        NF("Folder exists!\n");
        name = title = "";
        create_again = 0;
        return 0;
    }
	
    write_file(FOLDER_DIR + title, "Task of the named Comittee: Development "
        + "and Construction of the " + C(title) + ".\n\nHead of Comittee:\n" 
        + C(name) + "\nMaster of Construction:\n<vacant>\nMaster of "
        + "Development\n<vacant>\n\n");
    write_file(FOLDER_DIR + "titles", title + "\n");
    name = title = "";
    create_again = 0;
    write("You write down the information on a piece of paper and hit the bell "
        + "on your desk. A gnome wizzes in, gets the piece of paper and "
        + "leaves again.\n");
    return 1;
}

int
g_promote(string str)
{
    object player;
    
    str = lower_case(str);
    
    notify_fail("You must specify whom you wish to promote.\n");
    if (!strlen(str))
        return 0;
    
    notify_fail("Your attempts at promoting" + capitalize(str) +
    " has failed.\n");
    if (!MANAGER->load_member(str))
        return 0;
    
    if (!this_player()->query_wiz_level())
    {
        notify_fail("You're not the Head Tinker!\n");
        if (this_player()->query_real_name() != MANAGER->query_headtin_name() &&
           (this_player()->query_guild_title_race()[..13] != "Assistant Head"))
            return 0;
    
        if (str == MANAGER->query_headtin_name() &&
            str != this_player()->query_real_name())
            return 0;
        
        notify_fail("You do not have the authority to promote " + str + ".\n");
        if (this_player()->query_real_name() != MANAGER->query_headtin_name() &&
           (this_player()->query_skill(SS_PROMOTE) <= MANAGER->query_promote(str)))
           return 0;
    }
    
    notify_fail("You cannot promote " + str + " any further.\n");
    if (MANAGER->query_promote(str) > 99)
        return 0;
    
    this_player()->catch_msg("You have promoted " + str + ".\n");
    
    if (player = find_player(str))
    {
        player->set_skill(SS_PROMOTE, player->query_skill(SS_PROMOTE) + 1);
        MANAGER->set_promote(player, player->query_skill(SS_PROMOTE));
        
        player->catch_msg("You have been promoted by " +
        capitalize(this_player()->query_real_name()) + ", your " +
        "esteem in the Inventors society has risen.\n");
    }
    else
        MANAGER->set_promote(str, (MANAGER->query_promote(str) + 1));
    
    write_file(PROMOTELOG, ctime(time()) + " - " + str +
    " was promoted by " + this_player()->query_real_name() + "\n");
    
    return 1;
}

int
g_demote(string str)
{
    object player;
    
    str = lower_case(str);
    
    notify_fail("You must specify whom you wish to demote.\n");
    if (!strlen(str))
        return 0;
    
    notify_fail("Your attempts at demoting " + capitalize(str) +
    " has failed.\n");
    if (!MANAGER->load_member(str))
        return 0;
    
    if (!this_player()->query_wiz_level())
    {
        notify_fail("You're not the Head Tinker!\n");
        if (this_player()->query_real_name() != MANAGER->query_headtin_name() &&
           (this_player()->query_guild_title_race()[..13] != "Assistant Head"))
            return 0;
    
        if (str == MANAGER->query_headtin_name() &&
            str != this_player()->query_real_name())
            return 0;
        
        notify_fail("You do not have the authority to demote " + str + ".\n");
        if (this_player()->query_real_name() != MANAGER->query_headtin_name() &&
           (this_player()->query_skill(SS_PROMOTE) <= MANAGER->query_promote(str)))
           return 0;
    }
    
    notify_fail("You cannot demote " + str + " any further.\n");
    if (MANAGER->query_promote(str) < 1)
        return 0;
    
    this_player()->catch_msg("You have demoted " + str + ".\n");
    
    if (player = find_player(str))
    {
        player->set_skill(SS_PROMOTE, player->query_skill(SS_PROMOTE) - 1);
        MANAGER->set_promote(player, player->query_skill(SS_PROMOTE));
        
        player->catch_msg("You have been demoted by " +
        capitalize(this_player()->query_real_name()) + ", your " +
        "esteem in the Inventors society has fallen.\n");
    }
    else
        MANAGER->set_promote(str, (MANAGER->query_promote(str) - 1));
    
    write_file(PROMOTELOG, ctime(time()) + " - " + str +
    " was demoted by " + this_player()->query_real_name() + "\n");
    
    return 1;
}