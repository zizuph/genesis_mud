/*
 * Based upon Liliths Mummer Club code. 
 *
 * Terelian Explorers of Arcanum Club
 * See /d/Terel/clubs/explorer/doc/explorers_club for history information
 * Tomas -- Dec 1999
 */


inherit "/cmd/std/command_driver";

#pragma save_binary
#include <const.h>
#include <filter_funs.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Terel/include/Terel.h"
#include "/d/Terel/clubs/explorer/include/explorer_club.h"
#include "/d/Terel/clubs/explorer/include/explorer_emotes.h"

/********************************************************************
 * Soul identifying and autoloading
 ********************************************************************/
public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Explorer of Arcanum"; }

/********************************************************************
 * The list of verbs and functions. 
 *******************************************************************/
public mapping
query_cmdlist()
{
    seteuid(getuid());
    return ([
        "echaos"    : "e_chaos",
        "ejourney"  : "e_journey",
        "enofind"   : "e_nofind",
        "eobserve"  : "e_observe",
        "equest"    : "e_quest",
        "esmell"    : "e_smell",
        "estare"    : "e_stare", 
        "esmile"    : "e_smile",
        "ethump"    : "e_thump",
        "ereel"     : "e_reel",
        "exphelp"   : "explorer_help",  "explorer"  : "explorer_help",
        "ewho"      : "e_who",
        "eaccept"   : "e_accept",
        "eretire"   : "e_retire",
           ]);
}                   


/*          
 
        "swonder"   : "s_wonder", 
        "slook"     : "s_look",     
        "sreel"     : "s_reel",                                       
        "srespect"  : "s_respect",   
        "soffer"    : "s_offer",  
*/

public int
ring_check(object ob)
{
    return (ob->id(EXPLORER_RING) && ob->query_adj() == "worn");
}        



/*****************************************************************
 *  Club emotes are in /d/Terel/clubs/explorer/include*
 *****************************************************************/

/*
 *      exphelp         explorer Club help file
 */ 
public int
explorer_help(string str)
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