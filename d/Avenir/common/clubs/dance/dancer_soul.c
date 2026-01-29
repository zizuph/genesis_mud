// -*-C++-*-
// file name: 	  /d/Avenir/common/clubs/dance/dancer_soul.c
// creator(s):	  Gracie&Tep	July 995
// Thanks go to Kanga for inspiration. This club is dedicated to 
// Eowyn, who left us all bereft, but is in a better place (we hope).
// purpose:       Soul for seductive dancers
// note:          actual emotes moved to /dance/lib/* dir
/*
 * Revisions:
 * 	Lilith, Jul 1997: Added new emotes
 * 	Lucius, Sep 2017: Misc cleanups. Added daspeak/dspa
 */
#pragma strict_types

inherit "/cmd/std/command_driver";

#include "dance_club.h"

#include <const.h>
#include <cmdparse.h>
#include <options.h>

#define SOULDESC(x)	(this_player()->add_prop(LIVE_S_SOULEXTRA, x))

#include "lib/dancer_emotes1.h"
#include "lib/dancer_emotes2.h"
#include "lib/new_emotes.h"
#include "lib/temple_dance.h"


/********************************************************************
 * Soul identifying and autoloading
 ********************************************************************/
public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Dancer of Veils"; }

/********************************************************************
 * The list of verbs and functions. 
 *******************************************************************/
public mapping
query_cmdlist()
{
  seteuid(getuid());
  return ([
         "dbeam"   : "dbeam", 
         "dbeck"   : "dbeck", "dbeckon":"dbeck",
         "dblow"   : "dblow",
         "dbo"     : "dbo",   
         "dbored"  : "dbored",
         "dchew"   : "dchew",
         "ddance"  : "ddance",   
  //     dexpose is in the qskirt code
         "dflash"  : "dflash",
	 "dglow"   : "dglow",
	 "dhair"   : "dhair",
	 "dhelp"   : "dhelp", "danhelp":"dhelp", "dancehelp":"dhelp", 
         "dhelp1"  : "dhelp1",
         "dhold"   : "dhold",
         "dhug"    : "dhug",
	 "dhum"    : "dhum",
         "dhuff"   : "dhuff",    "dhuf" : "dhuff",
	 "dimmune" : "dimmune", "dimm":"dimmune", "dimmu":"dimmune",
	 "dinsult" : "dinsult",
   //    djingle is in the anklet code
         "dkill"   : "dkill", 
         "dkiss"   : "dkiss",
	 "dlean"   : "dlean",		
   //    dlower is in the veil code
	 "dlook"   : "dlook",
         "dmark"   : "dmark",
	 "dmouth"  : "dmouth",
         "doffer"  : "doffer",
         "dpir"    : "dpir", 
         "dperf"   : "dperf",    "dperfume" : "dperf",
	 "dpoke"   : "dpoke",
	 "dpout"   : "dpout",
         "drub"    : "drub",
         "dansm"   : "dsmile",   "dsmi" : "dsmile", "dansmile" : "dsmile",      
	 "dsigh"   : "dsigh",
         "dsmoo"   : "dsmooth",  "dsmooth" : "dsmooth",
         "dspeak"  : "dspeak",    "dsp" : "dspeak",
         "daspeak" : "daspeak",  "dspa" : "daspeak",
	 "dstick"  : "dstick",
         "dstretch": "dstretch", "dstr" : "dstretch",
         "dstrut"  : "dstrut",
	 "dstop"   : "dstop",
         "dswoon"  : "dswoon",
         "dthigh"  : "dthigh",   "dthi" : "dthigh", 
         "dthink"  : "dthink",   
         "dthrow"  : "dthrow",   "dthro" : "dthrow",
         "dtrace"  : "dtrace",
   //    dtwirl is in the qskirt code
	   ]);
}

/*****************************************************************
 *  Club emotes are in ~Avenir/common/clubs/dance/lib/*
 *  da-dk is in dancer_emotes1.h; dl-dz is in dancer_emotes2.h 
 *  New emotes should be added in alphabetic order in that file.
 *  dhelp (below) should be updated whenever the emotes are.
 *****************************************************************/

/*
 *	dhelp 	Dancer Club help file
 *                The files that dhelp accesses can be found in
 *                the ~Avenir/common/clubs/dance/doc/* dir.
 *                They should be updated when new emotes are added.
 */ 

int
dhelp(string str)
{
    string filename, subject, text;

    if (!str)   
        subject = "emotes";

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

int
dhelp1()
{
    write("Try using <dhelp short> instead.\n");
    return 1;
}
