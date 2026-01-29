/*
 * proofer.c
 *
 * Coded by Khail, Feb 12/96
 *
 * This object is used for proofing areas for opening. It adds a message
 * at the top of the file saying who proofed it and when, as well as logging
 * the proof, which includes the proofer, the time/date, and what room was
 * proofed. Note this only works for rooms currently.
 */

#include "/d/Immortal/std/domain.h"
#include <std.h>

#define PROOF_LOG "/d/"+domain(environment(this_player()))+"/log/"+proof_log

inherit "/std/object";

int proofwho(string str);
int prooflog(string str);
int proofhere(string str);
int proofset(string str);
int proofcheck(string str);
int proofwipe(string str);
int proofhelp(string str);

string proof_log;

void
create_object()
{
    set_name("proofer");
    set_short("Khail's room proofer");
    set_long("This proofer is used for faster recording of approval of " +
        "rooms for opening. 'proofhelp' will provide a list of commands " +
        "along with some info on what they do.\n" +
        "This item uses read_file for the header placement, so you may " +
        "experience problems with extremely large rooms, depending on " +
        "the game driver is allowing for max size of read_file, check " +
        "the man pages on that efun, currently the size is approx 50 kb.\n");


    if (!proof_log || !strlen(proof_log))
        proof_log = "PROOF_LOG";

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
}

string
query_auto_load()
{
    return MASTER + ":" + proof_log;
}

void
init_arg(string str)
{
    if (!strlen(str))
        proof_log = "PROOF_LOG";
    else
        proof_log = str;
}

void
init()
{
    FIXEUID;

    ::init();
    add_action(prooflog, "prooflog");
    add_action(proofhere, "proofhere");
    add_action(proofwho, "proofwho");
    add_action(proofset, "proofset");
    add_action(proofcheck, "proofcheck");
    add_action(proofwipe, "proofwipe");
    add_action(proofhelp, "proofhelp");
}

int
prooflog(string str)
{
    write("These are the most recently logged proofs using this object:\n");
    tail(PROOF_LOG);
    return 1;
}

int
proofwho(string str)
{
    int i;
    string filename,
           line,
           proofer,
           time_date,
           logged_where,
           str1,
           str2,
           str3,
           str4,
           temp;

    FIXEUID;
    filename = file_name(environment(TP)) + ".c";

    for (i = 0; i < 5; i++)
    {
        line = read_file(filename, i, 1);
        if (!strlen(line) || i == 5)
        {
            write("Unable to read " + filename + ", line " + i + ".\n");
            return 1;
        }
        sscanf(line, "%sPROOFED BY: %s\n", str1, str2);
        if (strlen(str2))
            proofer = str2;
        sscanf(line, "%sON: %s\n", str1, str3);
        if (strlen(str3))
            time_date = str3;
        sscanf(line, "%sLOGGED IN: %s\n", str1, str4);
        if (strlen(str4))
            logged_where = str4;
    }
    if (strlen(proofer) && strlen(time_date))
    {
        temp = filename + " last proofed by " + proofer + " on " + 
            time_date + ".";
        if (strlen(logged_where))
            temp += "\nLogged in " + logged_where + ".\n";
        else
            temp += "\nNo log info available.\n";

    }
    else
        temp = filename + " has not been proofed.\n";

    write(temp);

    return 1;
}

int
proofhere(string str)
{
    string filename,
           oldfile,
           newfile,
           proofer,
           time_date;

    proofer = TP->query_name();
    proofer += " (" + SECURITY->query_wiz_level(TP->query_real_name())+") ";

    time_date = ctime(time());

    filename = file_name(environment(TP)) + ".c";
    oldfile = read_file(filename);
    if (!strlen(oldfile))
    {
        write("Unable to read " + filename + ".\n");
        return 1;
    }

    rm(filename);
    newfile = "/*\n" +
              " * PROOFED BY: " + proofer + "\n" +
              " * ON: " + time_date + "\n" +
              " * LOGGED IN: " + PROOF_LOG + "\n" +
              " */\n";

    newfile += oldfile;

    if (!write_file(filename, newfile))
    {
        write("Unable to write to " + filename + ".\n");
        return 1;
    }

    write_file(PROOF_LOG, filename + " proofed by " + proofer + 
        "on " + time_date + ".\n");

    write(filename + " proofed by " + proofer + " on " + time_date + ".\n");
    return 1;
}

int
proofset(string str)
{
    if (!str || !strlen(str))
    {
        NF("Specify a name for the file in which proofs are to be logged.\n");
        return 0;
    }

    proof_log = str;
    write("Proofs will be logged in " + PROOF_LOG + " now.\n");
    return 1;
}

int
proofcheck(string str)
{
    write(PROOF_LOG + " is the current log for proofs with this proofer.\n");
    return 1;
}
    
int
proofwipe(string str)
{
    write("When function will remove the top proof header from a file.\n");
    return 1;
}

int
proofhelp(string str)
{
    string ret;

    ret = "The following commands are possible with the proofer:\n";
    ret += "\n";
    ret += "Proofhere: Executing this command in a room will have two\n";
    ret += "\teffects. First, a header will be added to the room file\n";
    ret += "\twhich contains your name, wizlevel, time, and the current\n";
    ret += "\tproof log name. Secondly, it logs the room path and your\n";
    ret += "\tname, wizlevel and time in the current proof log.\n\n";
    ret += "Proofwho: This command will tell you if the room you're in\n";
    ret += "\thas been proofed, and if so, when and by who.\n\n";
    ret += "Prooflog: Tails the end of the current proof log.\n\n";
    ret += "Proofset: Sets the current proof log file. This file will\n";
    ret += "\tbe located in /d/Domain/log/, but the file name is\n";
    ret += "\tcompletely up to you, but most logically includes the name\n";
    ret += "\tof the area you are proofing. The proofer will remember\n";
    ret += "\tthe current log file until you change it or lose your\n";
    ret += "\tproofer somehow. The default is /d/Domain/log/PROOF_LOG.\n";
    ret += "\n";
    ret += "Proofcheck: This command returns the current proof log.\n";
    ret += "\n";
    ret += "Proofwipe: Removes the top proof header from a room that\n";
    ret += "\tcontains one.\n";
    ret += "\tCurrently non-functional.\n";

    write(ret);
    return 1;
}

