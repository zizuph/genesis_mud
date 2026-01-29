/* This object enables more commands for working on the folders in the
 * folderroom.c
 * It is cloned into a player working on a folder.
 * Created by Dajala    30.09.94
 */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "../guild.h"

/* Prototypes */

void file_write();
void file_read();

/* Global variables */

int office, confirm_conclude;
int erase_flag;
string title, *buffer, name;
object editor;

void
create_object()
{
    set_name("fworker");
    set_no_show();
    confirm_conclude = 0;
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
}

void
init()
{
    if(interactive(TP) &&
      name != C(TP->query_name())) /* only for owner */
	TO->remove_object();

    if(office == 1)
    {
	ADA("appoint");
	ADA("remove");
	ADA("conclude");
	ADA("erase");
    }
    ADD("my_write", "write");
    ADA("conclude");
    ADD("fol_close", "close");
}

int
my_write(string str)
{
    NF("Write into what?\n");
    if(str != "into folder")
	return 0;       

    seteuid(getuid());
    editor = clone_object("/obj/edit");
    editor->edit("done_editing", "");
    say(QCTNAME(TP) + " writes something into " + POSSESSIVE(TP)
      + " folder.\n");
    return 1;
}

int
done_editing(string text)
{
    write_file(FOLDER_DIR + title, name + ":\n" + text + "\n");
    write("You finish writing for the moment.\n");
    say(QCTNAME(TP) + " finishes writing something into the folder.\n");
        return 1;
}       

int
appoint(string str)
{
    string *input;

    input = explode(str, " ");

    if(C(input[0]) == name)
    {
	NF("You cannot appoint yourself.\n");
	return 0;
    }

    NF("Appoint whom for what?");
    if(input[1] != "for" || C(input[2]) != "Master" || input[3] != "of")
	return 0;

    if(C(input[4]) == "Construction")
    {
	file_read();
	NF("This office is not vacant.\n");
	if (buffer[5] != "<vacant>")
	    return 0;
	buffer[5] = C(input[0]);
	file_write();
	write("Ok.\n");
	return 1;
    }
    if(C(input[4]) == "Development")
    {
	file_read();
	NF("This office is not vacant.\n");
	if (buffer[7] != "<vacant>")
	    return 0;
	buffer[7] = C(input[0]);
	file_write();
	write("Ok.\n");
	return 1;
    }
    return 0;
}

int
erase(string str)
{
    string total = "";
    int i;

    NF("Erase what? The folder?\n");
    if(str != "folder")
	return 0;
    if(!erase_flag)
    {
	write("Do you really want to erase everything you've "
	  + "written so far?\nPlease confirm.\n");
	erase_flag = 1;
	return 1;
    }
    seteuid(getuid());
    file_read();
    rm(FOLDER_DIR + title);
    for(i=0;i<9;i++)
	total = total + buffer[i] + "\n";
    write_file(FOLDER_DIR + title, total);
    erase_flag = 0;
    write("Ok.\n");
    return 1;
}	



int
remove(string str)
{
    string *input;

    input = explode(str, " ");
    NF("Remove whom from what?");
    if(input[1] != "from" || C(input[2]) != "Master" || input[3] != "of")
	return 0;
    if(C(input[4]) == "Construction")
    {
	file_read();
	NF("This office is already vacant.\n");
	if(buffer[5] == "<vacant>")
	    return 0;
	buffer[5] = "<vacant>";
	file_write();
	write("Ok.\n");
	return 1;
    }
    if(C(input[4]) == "Development ")
    {
	file_read();
	NF("This office is already vacant.\n");
	if(buffer[7] == "<vacant>")
	    return 0;
	buffer[7] = "<vacant>";
	file_write();
	write("Ok.\n");
	return 1;
    }
    return 0;
}

void
file_write()
{
    int i;
    string total = "";

    seteuid(getuid());
    rm(FOLDER_DIR + title);
    for(i=0;i<sizeof(buffer);i++)
	total = total + buffer[i] + "\n";
    write_file(FOLDER_DIR + title, total);
}

void
file_read()
{
    buffer = explode(read_file(FOLDER_DIR + title), "\n");
}

/* Called from folderroom.c */  

void
set_office(int number)
{
    office = number;
}

/* Called from folderroom.c */  

void
set_folder(string str)
{
    title = str;
}

/* Called from folderroom.c */  

void
fix_name(string str)
{
    name = str;
}

int
conclude(string str)
{
    int i;

    NF("Conclude what?\n");
    if (str != "folder")
	return 0;

    if(confirm_conclude == 0)
    {
	write("Do you really want to conclude the development of the "
	  + C(title) + "?\n");
	write("Type again to confirm.\n");
	confirm_conclude = 1;
    }
    else
    {
	seteuid(getuid());
	confirm_conclude = 0;
	write_file(FOLDER_DIR + "concluded", "The " + C(title) + " concluded "
	  + "by " + C(name) +  ".\n");
	write_file(FOLDER_DIR + title, name + " concluded the "
	  + "development.\n");
	write("You concluded the development of the " + C(title) + ".\n\n"
	  + "Then you put the folder into the shelf for concluded "
	  + "projects.\n");
	say(QCTNAME(TP) + " concludes the development of the " + C(title)
	  + " and puts the folder into the shelf for concluded "
	  + " projects.\n");
	buffer = explode(read_file(FOLDER_DIR + "titles"), "\n");
	rm(FOLDER_DIR + "titles");
	for (i=0;i<sizeof(buffer);i++)
	    if(buffer[i] != title)
		write_file(FOLDER_DIR + "titles", buffer[i] + "\n");
	TO->remove_object();
    }
    return 1;
}

int
fol_close(string str)
{
    NF("Close what? The folder?\n");
    if(str != "folder")
	return 0;
    write("You finish working on the " + C(title) + " for today and "
      + "put back the folder.\n");
    TO->remove_object();
    return 1;
}
