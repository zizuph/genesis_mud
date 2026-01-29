// -*-C++-*-
// file name: 	  /d/Avenir/common/clubs/dance/mummer_soul.c
// creator(s):	  Lilith, October 1996
//                This is dedicated to all the clowns in my life ;)
// last update:	  
// purpose:       Minor guild for males. Street-performers.
// note:          emotes in /mummer/lib/* dir
// bug(s):
// to-do:         add ability to twist bladders and intestines into
//                balloon figures.

inherit "/cmd/std/command_driver";

#pragma save_binary
#include <const.h>
#include <filter_funs.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/common/clubs/mummer/mummer_club.h"
#include "/d/Avenir/common/clubs/mummer/lib/mum_emotes.h"
#include "/d/Avenir/common/clubs/mummer/lib/mime.h"

/********************************************************************
 * Soul identifying and autoloading
 ********************************************************************/
public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Mummer of Sybarus"; }

/********************************************************************
 * The list of verbs and functions. 
 *******************************************************************/
public mapping
query_cmdlist()
{
    seteuid(getuid());
    return ([
        "mcap"    : "mcap",         "mumcap"    : "mcap",
        "mcoin"   : "mcoin",        "mumcoin"   : "mcoin",
        "mfireat" : "mfire_eat",    "mumfireat" : "mfire_eat",
        "fireeat" : "mfire_eat",    "fireat"    : "mfire_eat",
        "mflip"   : "mflip",        "mumflip"   : "mflip", 
        "mime"    : "mime",         "pantomime" : "mime",
                                    "fmime"     : "fake_mime",    
        "mfake"   : "fake_mime",    "mumfake"   : "fake_mime", 
        "mlevi"   : "levitate",     "mumlevi"   :  "levitate", 
                                    "levitate"  : "levitate",
        "mpull"   : "mpull",        "mumpull"   : "mpull",        
        "mumhelp" : "mum_help",     "mummer"    : "mum_help",
        "mscarf"  : "mscarf",       "mumscarf"  : "mscarf",
        "mshow"   : "mshow",        "mumshow"   : "mshow",
        "mstand"  : "mstand",       "mumstand"  : "mstand",
        "mstop"   : "mstop",        "mumstop"   : "mstop",
        "mswallow" : "mswallow",    "mumswallow" : "mswallow",
        "mtaste"  : "mfire_taste",  "firetaste" : "mfire_taste",
                                    "mumtaste"  : "mfire_taste",
        "mtip"    : "mtip",         "mumtip"    : "mtip",
        "mtoes"   : "mtoe",         "mumtoes"   : "mtoe",  
        "mtoe"    : "mtoe",         "mumtoe"    : "mtoe",
        "mtwist"  : "mtwist",       "mumtwist"  : "mtwist",
        "mwall"   : "mwall",        "mumwall"   : "mwall",  

     /* "mwalk" In the guild obj */
	   ]);
}                   

/* 
 * Tests used by mummer emotes. 
 */
public int
boot_check(object ob)
{
    return (ob->id("boots") && ob->query_adj() == "worn" && 
        (ob->query_at() == A_FEET));
}        

public int
cap_check(object ob)
{
    return (ob->id(MUMMER_CAP) && ob->query_adj() == "worn");
}        

public int
torch_check(object ob)
{
    return (function_exists("create_object", ob) == "/std/torch" && 
           ob->query_lit());
}

public int 
gut_check(object ob)
{
    return (function_exists("create_leftover", ob) 
            && (ob->id("intestine") || ob->id("intestines")));
}    


/*****************************************************************
 *  Club emotes are in ~Avenir/common/clubs/mummer/lib/*
 *  New emotes should be added in alphabetic order in that file.
 *****************************************************************/

/*
 *	mumhelp 	Mummers Club help file
 */ 
public int
mum_help(string str)
{
    string filename, subject, text;

    if (!str)   
        subject = "list";

    else if (sscanf(str, "%s", subject) != 1)
    {
        notify_fail("There is no help section for that subject.\n");
        return 0;
    }
    filename = DOC_DIR + subject;
    if (file_size(filename) > 0) 
    {
        setuid();
        seteuid(getuid());
        text = read_file(filename);
        this_player()->more(text);
        return 1;
    }
    notify_fail("There is no help section for that subject.\n");
    return 0;
}
