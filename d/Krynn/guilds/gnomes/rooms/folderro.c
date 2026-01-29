/* Here members drop more concrete suggestions for the modules
 * into folders. The guildmaster creates a folder, then the inventor
 * may assign two more members who may help him.
 * Created by Dajala.   30.09.94
 */

inherit "/d/Krynn/std/room.c";

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "../guild.h"

/* Prototypes */

int name_check(object player);
int title_check(string str);


/* Global variables */

string *buffer;

void
create_room()
{
    INSIDE;
    LIGHT;
    set_short("Comittee chamber");
    set_long("The spirit of a thousand inventive minds is present in this room. "
	+ "Floating images of machines and devices having been built long "
	+ "ago still form vividly before your eyes.\nThe sparse furniture "
	+ "stands in sharp contrast to the importance of this chamber. You "
	+ "see a huge round table, wooden stools and, lined on the walls, "
	+ "long shelves containing folders for each project currently "
	+ "discussed. There is another shelf for concluded projects.\n"
	+ "A door leads west.\n");
    add_item(({"stool", "stools", "wooden stools"}), "These three-legged "
	+ "stools stand around the table. You count six of them.\n");
    add_item("table", "The round table measures about two meters in "
	+ "diameter. Six stools stand around it.\n");
    add_item(({"spirit", "minds", "mind"}), "You cannot grab hold of it "
	+ "but it is present, that is sure.\n");
    add_item(({"shelf", "shelves"}), "There are many of them. They contain "
	+ "folders for all the current projects of the Inventor Guild.\n");
    add_item(({"plaque", "silver plaque"}), "About 10x20 cm in size. There is "
	+ "something written on it.\n");
    add_item("door", "About 1.5x1 m in size. There is a silver plaque nailed "
	+ "to it.\n");
    add_item(({"folder", "folders"}), "There is one folder for each current "
	+ "project plus a sample folder. Try <help folders> now for more "
	+ "information on their usage.\n");
    add_cmd_item("door", "open", "The door is locked.\n");
    add_cmd_item("door", "unlock", "You don't hold the key.\n.");
    add_cmd_item("projects", "list", "@@list_projects");
    add_cmd_item("concluded", "list", "@@list_concluded");
    add_prop(ROOM_M_NO_TELEPORT, "You cannot concentrate with "
	+ "these pictures in your mind.\n");
    add_prop(ROOM_M_NO_MAGIC, "You cannot concentrate with "
	+ "these pictures in your mind.\n");

    add_exit(ROOMS + "planner", "north", "@@fworker_check");
    add_exit(ROOMS + "head_tin", "west", "@@head_tin_check");
    reset_room();
}

void
reset_room()
{
    int gender,i;
    string buffer = "", title = "", name = "", line = "", empty = "";
	
    seteuid(getuid());
    gender = MANAGER->query_headtin_gender();
    if(!gender)
	title = GNOME_TITLES[14];
    else
	title = GNOME_TITLES_F[14];
    name = MANAGER->query_headtin_name();
    if(strlen(title) > strlen(name))
    {
	for(i=0;i<(strlen(title)-strlen(name))/2;i++)
	    buffer = " " + buffer;
	name = buffer + name + buffer;
	if(itof(strlen(title)-strlen(name)) / 2.0 -
	    itof((strlen(title)-strlen(name))/2) > 0.01)
	    name = name + " ";
	for(i=0;i<strlen(title);i++)
	{
	    empty = " " + empty;
	    line = "-" + line;
	}
    }
    else if(strlen(name) > strlen(title))
    {
	for(i=0;i<(strlen(name)-strlen(title))/2;i++)
	    buffer = " " + buffer;	
	title = buffer + title + buffer;
	if(itof(strlen(title)-strlen(name)) / 2.0 -
	    itof((strlen(title)-strlen(name))/2) > 0.01)
	    title = title + " ";
	for(i=0;i<strlen(name);i++)
	{
	    empty = " " + empty;
	    line = "-" + line;
	}
    }
    else
	for(i=0;i<strlen(name);i++)
	{
	    empty = " " + empty;
	    line = "-" + line;
	}
    add_cmd_item(({"plaque", "silver plaque"}), "read","\n"
	+ "/----" + line + "----/\n"
	+ "/    " + empty + "    /\n"
	+ "/    " + name + "    /\n"
	+ "/    " + title + "    /\n"
	+ "/    " + empty + "    /\n"
	+ "/----" + line + "----/\n\n");
}

int
fworker_check()
{
    if(P("fworker", TP))
    {        
        write("Please close the folder and put it back before "
	    + "leaving. Others might want to work on it as "
	    + "well.\n");
        return 1;
    }
    return 0;
}

int
head_tin_check()
{
    string title;
    
    if  (fworker_check())
        return 1;

    title = TP->query_guild_title_race();

    if (TP->query_wiz_level() || 
        TP->query_real_name() == MANAGER->query_headtin_name() ||
       (this_player()->query_guild_title_race()[..13] == "Assistant Head"))
    {
	write("You open the door.\nWelcome, " + TP->query_name() + ". "
	    + "Work awaits you.\n");
	return 0;
    }
    write("The door is locked.\n");
    return 1;
}

void
init()
{
    ::init();
    ADD("check_it", "check");
    ADA("work");
    ADA("help");
}

int
help(string str)
{
    if(str != "folders")
	return 0;
    seteuid(getuid(TO));
    cat(GGUILD + "log/help_dir/folder.hlp");
    return 1;
}

string
list_projects()
{
    string *titles;
    int i;

    say(QCTNAME(TP) + " has a look at the shelves.\n");
    write("The following projects are currently worked upon:\n");
    seteuid(getuid());
    titles = explode(read_file(FOLDER_DIR + "titles"), "\n");
    for (i=0;i<sizeof(titles);i++)
	TP->catch_msg("The " + C(titles[i]) + ".\n");
    return "";
}

string
list_concluded()
{
    say(QCTNAME(TP) + " has a look at the shelves.\n");
    write("The following projects are concluded:\n");
    seteuid(getuid());
    cat(FOLDER_DIR + "concluded");
    return "";
}

/* Returns 1 if the title is present in the title-file */

int
title_check(string str)
{
    int i;
    string *array, s;

    buffer = explode(read_file(FOLDER_DIR + "titles"), "\n");
    array  = explode(read_file(FOLDER_DIR + "concluded"), "\n");
	
    foreach(string title: array) {
        if (sscanf(title, "The %s concluded", s))
        {
	        buffer += ({ s });
        }
    }
    
	if (member_array(str, buffer) > -1)
	    return 1;
	
    return 0;
}

int
check_it(string str)
{
    int i;
	string name;

    if(str == "example" || str == "sample" || str == "sample folder")
    {
	write("You have a look at the sample folder.\n"
	    + "It covers the project of the GnomishGestureMaker "
	    + "invented by Dante.\n\n");
	say(QCTNAME(TP) + " has a look at the sample folder.\n");
	cat(FOLDER_DIR + "Samplefolder");
	return 1;
    }

    NF("You cannot find anything under that title.\n");
    if (!title_check(str))
	return 0;
	
	name = str;
	
	if (member_array(str, get_dir(FOLDER_DIR + "coded_folders/")) > -1)
		str = "coded_folders/" + str;
	
    buffer = explode(read_file(FOLDER_DIR + str), "\n");
    say(QCTNAME(TP) + " has a closer look at a single folder.\n");
    write("You have a brief look at the folder titled " + C(name) + " and read the "
	+ "following:\n\n");
    if (name_check(TP))               /* Member of comittee */
    {
	seteuid(getuid());
	cat(FOLDER_DIR + str);    
    }
    else                              /* No member of comittee */
    {
	for(i=0;i<8;i++)
	    write(buffer[i] + "\n");
	write("\nThe following pages are for the eyes of comittee-members "
	    + "only.\n");
    }
    return 1;
}

/* returns 1 if the player is head of the comittee
 *         2 if the player is master of construction or development
 */

int
name_check(object player)
{
    string name;

    if(player->query_wiz_level())
    {        
	write("Since you are a wizard, you are allowed to have a "
	    + "look into the folder.\n");
	return 1;
    }
    name = C(player->query_name());
    if(name == buffer[3])	/* Head of Comittee */
	return 1;
    if(name == buffer[5] || name == buffer[7])
	return 2;

    if(TP->query_guild_title_race()[0..20] == "Assistant Head Tinker"
	|| TP->query_guild_title_race()[0..10] == "Head Tinker")
    {
	write("Since you are " + TP->query_guild_title_race()
	    + " you are allowed to have a look at that folder.\n");
	return 1;
    }
    return 0;
}

/* Clones the work-object in the player */

int
work(string str)
{
    string *word;
    object worker;
    int office;
    object tp = TP;

    NF("It's fine if you want to become busy but: Work on what?\n");
    if (!str)
	return 0;
    word = explode(str, " ");
    if(word[0] != "on")
	return 0;
    NF("You cannot find that folder.\n");
    if(!title_check(word[1]))
	return 0;
    NF("You are not a member of the comittee working on the " 
	+ C(word[1]) + "!\n");
    buffer = explode(read_file(FOLDER_DIR + word[1]), "\n");
    if(!(office = name_check(TP)))
	return 0;

    NF("You are already working on a project.\n");
    if(P("fworker", tp))
	return 0;

    seteuid(getuid(TO));
    worker = clone_object(GOBJ + "fworker");
    worker->set_folder(word[1]);
    worker->set_office(office);
    worker->fix_name(C(tp->query_name()));
    worker->move(tp,1);
    write("You sit down at the table, the folder about the " + C(word[1])
	+ " in front of you.\n");
    say(QCTNAME(tp) + " starts working on a project.\n");
    return 1;
}
