/* Neraka Tool
   Adds some useful commands, useful for people working
   on Neraka that is.
   12 Jun 97, Ashlar
*/

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <options.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#define WIZARD_S_LAST_DIR "_wizard_s_last_dir"

int ncd(string path);
int nhide(string arg);
int nwho(string ogel);

void
create_object()
{
    set_name("tool");
    set_adj("neraka");
    
    set_short("Neraka Tool");
    set_long("Available commands:\n" +
        "ncd - cd to a path relative to " +  NERAKA + "\n" +
    "nhide <n>\n" +
    "    Set the hide difficulty in the room to n.\n" +
    "nwho\n" +
    "    Show who are in Neraka at the moment.\n" +
    "--\nRemember! You must <trust> this object to make nhide work!\n");

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
}

void
init()
{
    ::init();
    add_action(nwho,"nwho");
    add_action(nhide,"nhide");
    add_action(ncd,"ncd");
}

int
nwho(string ogel)
{
    object *obs;
    int i;
    string s;

    NF("Nwho what?\n");
    if (ogel)
        return 0;

    obs = users();
    for(i=0;i<sizeof(obs);i++)
    {
        if(E(obs[i]))
        {
            if(sscanf(file_name(E(obs[i])),"/d/Ansalon/taman_busuk/%s/",s) &&
               (s == "neraka"))
            {
                write(sprintf("%-13s %3d %5d s idle %s\n",
                    obs[i]->query_name(), obs[i]->query_average_stat(),
                    query_idle(obs[i]), file_name(E(obs[i]))));
            }
        }
    }
    return 1;
}

int
nhide(string arg)
{
    object room = E(TP);
    string file;
    string fc, *lines;
    int i,lc;
    int marker=0;
    string hidearg;

    hidearg = arg;

    file = file_name(room) + ".c";
    if (file_size(file) <= 0)
    {
        notify_fail("File " + file + " does not exist.\n");
        return 0;
    }
    write("Reading file: " + file + "\n");
    fc = read_bytes(file,0,file_size(file));
    lines = explode(fc,"\n");
    lc = sizeof(lines);
    if(!write_file(file+".ntoolbak",fc))
    {
        write("Can't write backup file.\n");
        return 1;
    }
    for(i=0;i<lc;i++)
    {
        if(wildmatch("* set_neraka_hide(*",lines[i]))
        {
            marker = -1;
            lines[i] = "    set_neraka_hide("+hidearg+");";
       }
        else if(wildmatch("*create_neraka_room()*",lines[i]))
            marker=i+2;
    }

    if (marker > 0)
    {
    lines += ({ "" });
        for(i=lc;i>marker;i--)
            lines[i] = lines[i-1];
        lines[marker] = "    set_neraka_hide("+hidearg+");";
    }
    if (marker == 0)
    {
        write("No changes.\n");
        return 1;
    }
    fc = implode(lines,"\n");
    write("Removing...");
    if(rm(file)) write("Ok.\n");
    else { write("Fail!\nAborting.\n"); return 1; }
    write("Writing...");
    if(write_file(file,fc)) write("Ok.\n");
    else { write("Fail!\nBackup is in " + file + ".ntoolbak\n"); return 1; }
    rm(file+".ntoolbak");
    return 1;
}
int
ncd(string str)
{
    int    auto;
    string old_path;
    string path;

    auto = this_player()->query_option(OPT_AUTO_PWD);

    old_path = this_interactive()->query_path();
    
    if (!str)
    {
        path = NERAKA;
    }
    else
    {
        path = NERAKA + str;
    }

    if (file_size(path) != -2)
    {
        notify_fail("No such directory '" + path + "'.\n");
	    return 0;
    }

    if (auto)
	write(path + "\n");
    else
	write("Ok.\n");
    this_player()->add_prop(WIZARD_S_LAST_DIR, old_path);
    this_player()->set_path(path);
    return 1;
}

/*
 * Make the tool autoloading
 */

string query_auto_load()
{
    return MASTER;
}

void
init_arg(string arg)
{
}

string query_recover() { return 0; }
