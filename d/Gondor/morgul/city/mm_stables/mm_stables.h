/*
 *  /d/Gondor/morgul/city/mm_stables/mm_stables.h
 *
 *  Header file for the stables of Minas Morgul.
 *
 *  Deagol, August 2002
 */

#define MM_STABLES_DIR		"/d/Gondor/morgul/city/mm_stables/"
#define MM_STABLES_OBJ_DIR	MM_STABLES_DIR + "obj/"
#define MM_STABLES_NPC_DIR	MM_STABLES_DIR + "npc/"
#define MM_STABLES_STEED_DIR	MM_STABLES_DIR + "steed/"
#define MM_STABLES_LOG_DIR	MM_STABLES_DIR + "log/"

#define MM_STABLES_NO_GET  	add_prop(OBJ_M_NO_GET, \
                           	"The Stable Master slaps you! " + \
                           	"The rack is his responsibility, and he " + \
                           	"seems reluctant to share it with you.\n");
                           	
#define MM_STABLE_MASTER	MM_STABLES_NPC_DIR + "stable_master.c"

#define HHELP_LEADER_MESSAGE \
   "\t\tCommands available for a leader of a horse\n \
    \t\t------------------------------------------\n\n \
    \t<hhelp> \tGet this text\n \
    \t<unlead horse> \tRelease a horse and leave it alone\n \
    \t<mount horse> \tRide a horse\n \
    \t<hhome> \tSend your horse back to Minas Morgul\n \
    \t\t\t(Available only in Middle Earth)\n\n \
    \t\tEmotes available for a leader of a horse\n \
    \t\t---------------------------------------\n\n \
    \t<hhalt> \tBring your horse to a halt\n \
    \t<hsnort> \tMake your horse snort\n\n"

#define HHELP_RIDER_MESSAGE \
   "\t\tCommands available for a rider of a horse\n \
    \t\t-----------------------------------------\n\n \
    \t<hhelp> \tGet this text\n \
    \t<hgallop on> \tMake your horse gallop\n \
    \t<hgallop off> \tMake your horse walk\n \
    \t<automount> \tEnable/disable automount function\n \
    \t<autodismount> \tEnable/disable autodismount function\n \
    \t<dismount> \tDismount a horse\n\n \
    \t\tEmotes available for a rider of a horse\n \
    \t\t---------------------------------------\n\n \
      Those emotes marked '*' may be used with adverbs\n \
      Those emotes marked '**' may or must be used with adverbs\n\n \
    \t<hhalt> \tBring your horse to a halt\n \
    \t<hsnort> \tMake your horse snort\n \
    \t<hscrape>* \tMake your horse scrape its hooves through the ground\n \
    \t<hneigh>** \tMake your horse neigh\n \
    \t<hrear>* \tForce your horse to rear up\n \
    \t<heyes>** \tMake your horse to look at somebody\n\n"

#define HHELP_BAG_MESSAGE \
   "\t\tHow to use a saddlebag\n \
    \t\t----------------------\n\n \
    \tYou can use  your horse for  carrying your equipment, if you\n \
    \thave a proper saddlebag. Undermentioned commands do not need\n \
    \tcommentary.\n\n \
    \t\t<drape saddlebag on horse> \n \
    \t\t<remove saddlebag from horse> \n \
    \t\t<open saddlebag on horse>\n \
    \t\t<close saddlebag on horse>\n \
    \t\t<fill saddlebag on horse>\n \
    \t\t<empty saddlebag on horse>\n\n"
