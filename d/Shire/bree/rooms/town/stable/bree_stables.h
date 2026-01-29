/*
 *  /d/Shire/bree/rooms/town/stable/bree_stables.h
 *
 *  Header file for the stables of Bree
 *
 * By,  Palmer
 * Date December 2002
 */

#define BREE_STABLES_DIR		"/d/Shire/bree/rooms/town/stable/"
#define BREE_STABLES_OBJ_DIR	BREE_STABLES_DIR + "obj/"
#define BREE_STABLES_NPC_DIR	BREE_STABLES_DIR + "npc/"
#define BREE_STABLES_STEED_DIR	BREE_STABLES_DIR + "steed/"
#define BREE_STABLES_LOG_DIR	BREE_STABLES_DIR + "log/"


#define BREE_STABLE_MASTER	BREE_STABLES_NPC_DIR + "stable_master.c"

#define HHELP_LEADER_MESSAGE \
   "\t\tCommands available for a leader of a steed\n \
    \t\t------------------------------------------\n\n \
    \t<hhelp> \tGet this text.\n \
    \t<unlead horse/pony> \tRelease a steed and leave it alone.\n \
    \t<lead horse/pony> \tLead the steed. What you're doing now.\n \
    \t<mount horse/pony> \tGet on the steed.\n \
    \t<hpack> \t See contents of horse's saddlebag.\n \
    \t<hhome> \tSend your steed back to Bree.\n \
    \t<hdrink>* \tMake your steed drink.\n\n \
    \t\tEmotes available for a leader of a steed\n \
    \t\t---------------------------------------\n\n \
    \t<hsnort> \tMake your steed snort.\n\n"

#define HHELP_RIDER_MESSAGE \
   "\t\tCommands available for a rider of a steed\n \
    \t\t-----------------------------------------\n\n \
    \t<hgallop on/off>  Make your steed gallop/walk.\n \
    \t<hglance>         See your steed's vitals.\n \
    \t<hboard>          Buy tickets for you and steed and board ship.\n \
    \t<automount>       Enable/disable automount function.\n \
    \t<autodismount>    Enable/disable autodismount function.\n \
    \t<dismount>        Dismount a steed.\n \
    \t<hpack>           See contents of horse's saddlebag.\n \
    \t<hnice on/off>    Make your steed react when people touch it.\n \
    \t<hdrink>          Make your steed drink. (hrdink from river etc.)\n\n \
    \t\tEmotes available for a rider of a steed\n \
    \t\t---------------------------------------\n\n \
      Those emotes marked '*' may be used with adverbs.\n \
    \t<hsnort>          Make your steed snort.\n \
    \t<hscrape>*        Make your steed scrape its hooves through the ground.\n \
    \t<hnuzzle>*        Make your steed nuzzle someone.\n\n"
