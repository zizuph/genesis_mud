/* Created by Dajala
 * Guildmaster's room
 * Do you want to promote a member? Then come in!
 * Besides most of the head_tinker routines are coded here.
 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/gnome/local.h"
#include "guild.h"
#include "modules_neu.h" 

inherit "/d/Krynn/std/room";

string player ="0", head_tinker_name = "0";
int stored_max_level, gender, create_again = 0;

/* Global variables */

string name, title;


void
create_room()
{
    set_short("Guildmasters chamber");

    set_long("The guildmaster's room contains only functional furni"
      + "ture. You spot a desk, a wooden stool next to it and a "
      + "drawing board. A lot more interesting are the many "
      + "breathtaking inventions assembled here which enriched "
      + "the inhabitant's life. But only some of the hundreds of "
      + "levers and gears are labeled. These labels read:\n"
      + "'gpromote <player>'\n'read log/promoted_log'\n"
      + "'create folder <title> <name>'\n'list concluded'\n"
      + "'upgrade gizmo'\n'upgrade desc'riptions by including another "
      + "new_desc.h\n");
    add_exit(GGUILD + "planner", "east", 0);

    restore_object(GMASTER_SAVE);
    LIGHT
}

void
init()
{
    ::init();
    ADA("gpromote");
    ADA("read");
    ADD("fol_create", "create");
    ADA("list");
    ADD("pat", "upgrade");
}

int
pat(string str)
{
    object gizmo;
    int i;

    if(str != "gizmo" && str != "desc") 
	return 0;
    NF("Only wizards may do that.\n");
    if(!TP->query_wiz_level())
	return 0;
    if(str == "desc")
    {
	seteuid(getuid());
	"/d/Krynn/gnome/guild/obj/upgrade_desc.c"->upgrade();
	return 1;
    }
    NF("You'll need a gizmo first.\n");
    if(!(gizmo = P("k_gizmo", TP)))
	return 0;
    gizmo->config();
    gizmo->refill_water(100);
    gizmo->refill_flour();
    gizmo->set_wood(20);
    for(i=0; i<sizeof(TYPES);i++)
	gizmo->add_module("0" + C(TYPES[i]));
    write("Ok. Gizmo patched.\n");
    return 1;
}

int
list(string str)
{
    string *titles;
    int i;

    NF("List what?\n");
    if(str != "concluded")
	return 0;
    write("The following projects are already concluded:\n");
    seteuid(getuid());
    titles = explode(read_file(FOLDER_DIR + "concluded"), "\n");
    for (i=0;i<sizeof(titles);i++)
	TP->catch_msg(C(titles[i]) + ".\n");
    return 1;
}

int 
fol_create(string str)
{
    string *buffer;

    buffer = explode(str, " ");
    NF("Create what? A folder?\n");
    if(buffer[0] != "folder")
	return 0;

    NF("Wrong number of arguments. Format: create folder <title> <name>.\n");
    if(sizeof(buffer) != 3)
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
    write("Ok. Created a folder for " + C(title) + " with " + C(name) 
      + " as head of the comittee.\n");
    name = title = "";
    return 1;
}

int
gpromote(string str)
{
    if(player == "0")
    {
	player = str;
	write("Please confirm by typing again.\n");
	return 1;
    }
    if (player != str)
    {
	write("Control mismatch. Try again.\n");
	player = "0";
	return 1;
    }
    NF("Upper case, please.\n");
    if(player != C(player))
    {
	player = "0";
	return 0;
    }

    write_file(PROMOTELOG, player + " - " + extract(ctime(time()), 4, 15)
      + "\n");
    write_file(ALL_PROMOTE_LOG, player + " - " 
      + extract(ctime(time()), 4, 15) + "\n");
    write("Ok.\nWe promoted " + player + ".\n");
    player = "0";
    return 1;
}

int
read(string str)
{
    NF("Read what? The log?\n");
    if(str != "log" && str != "promoted_log")
	return 0;

    if(str == "log")
	cat(ALL_PROMOTE_LOG);
    if(str == "promoted_log")
	cat(GOT_PROMOTED);
    return 1;
}

int
highest_level(object member, int level, int promoted)
{
    string who;

    who = (member->query_name());
    if((promoted < 3) && (head_tinker_name == who))
    {
	head_tinker_name = "0";
	stored_max_level = 0;
	gender = 0;
	seteuid(getuid());
	rm(GMASTER_SAVE + ".o");
	save_object(GMASTER_SAVE);
    }
    if ((level > stored_max_level) && (promoted >= 3))
    {
	gender = member->query_gender();
	stored_max_level = level;
	head_tinker_name = who;
	seteuid(getuid());
	rm(GMASTER_SAVE + ".o");
	save_object(GMASTER_SAVE);
    }
    if (who == head_tinker_name)
	return 1;
    return 0;
}

string
query_headtin_name()
{
    return head_tinker_name;
}

int
query_headtin_gender()
{
    return gender;
}
