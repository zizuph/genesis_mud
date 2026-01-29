/*
 *  Include file for The Gellirs of Lars 
 *
 *  Vitwitch 2022
 */

// info about 'death_chamber'
#include "/d/Genesis/login/login.h"

#ifndef _LGELLIR_
#define _LGELLIR_

#define LGELLIR "/d/Sparkle/clubs/lgellirs/"
#define LGELLIR_OPENING_LOC "/d/Genesis/start/dwarf/lvl2/edge3"

// testing regimen is active 
#define LGELLIR_BETA_TEST_01 1
#define LGELLIR_MORTAL_BETAS ({})

#define LGELLIR_WIZ_DEFAULT_ADMIN ({"vitwitch","cherek"})

#define LGELLIRDAEMON    ( LGELLIR + "daemon" ) 
#define LGELLIRPRINPC    ( LGELLIR + "prinpc" ) 
#define LGELLIRMEMOBJ    ( LGELLIR + "mbrobj" ) 
#define LGELLIRDATA      ( LGELLIR + "data/" )
#define LGELLIRDAEMOND   ( LGELLIR + "data/daemond/" )
#define LGELLIRWORDREF   ( LGELLIR + "data/wordref/" )
#define LGELLIRGALDRAR   ( LGELLIR + "data/galdrar/" )
#define LGELLIRGELLIRS   ( LGELLIR + "data/gellirs/" )
#define LGELLIRROOM      ( LGELLIR + "room/" )
#define LGELLIRLOGS      ( LGELLIR + "logs/" )

#define LGELLIRSOULID "LARSGELLIRS"

#define LARSETHER_BASEFILE ( LGELLIRROOM + "larsether_base" )
#define LARSETHER_FILESTUB ( LGELLIRROOM + "larsether" )
#define LARSETHER_STARTLOC ( LGELLIRROOM + "club_lilgap" )
#define LARSETHER_ENDLOCST "/d/Genesis/start/human/town/pier"
#define LARSETHER_NUMENDLOC 18
#define LARSETHER_ENDLOCMIN 1
#define LARSETHER_ENDLOCDEF "/d/Genesis/start/human/town/church"
#define LARSETHER_STTINGIDX 19
#define LARSETHER_ENDINGIDX 18
#define LARSETHER_MAXNUMIDX 36
#define LARSETHER_AWARDSDIV 9
#define LARSETHER_SECSPERST 1
#define LGELLIR_LARSETHER_INDEX        "_lgellirs_ether_stage" 
#define LARSETHER_DOMAINLIST ({ "ether", "ansalon", "krynn", "terel", \
     "avenir", "faerun", "raumdor", "earthsea", "sparkle", "genesis", \
     "shire", "gondor", "khalakhor", "liwitch", "cirath", "kalad", \
     "emerald", "calia" })

#define LGELLIR_NPC_NAME      "volvaskr"
#define LGELLIR_NPC_RACENAME  "sparkling"
#define LGELLIR_NPC_ADJ0      "darkened"
#define LGELLIR_NPC_ADJ1      "ancient"
#define LGELLIR_NPC_MORTALADDR  ({"ungr","elskr"})
#define LGELLIR_NPC_MESGSTART "Over the crackle of The Fire, you hear:"
#define LGELLIR_ETHER_INACTION_MESG \
"\n...the paralysing chill of the Larsether stays all action...\n"

#define LGELLIR_YELL_XPANTE 10000

#define LGELLIR_DEFAULT_RARITY_WORD "young"

#define LGELLIR_QUEST_DEFAULT_ACTIVE 0
#define LGELLIR_QUEST_NAME "Tending The Fire"
#define LGELLIR_QUEST_XP 400
#define LGELLIR_QUEST_DOMAIN "Sparkle"
#define LGELLIR_QUEST_GROUP 1
#define LGELLIR_QUEST_BIT 12
#define LGELLIR_QUEST_LOG "/d/Sparkle/log/quest_log/lgellirs_intro"

#define LGELLIR_PROP_TENDED_FIRE "_lgellir_player_has_tended_fire"
#define LGELLIR_PROP_LEAP_WARNING "_lgellir_player_leap_warning_"
#define LGELLIR_PROP_GXP_INCREMENT "_lgellir_player_generalxp_increment_"
#define LGELLIR_PROP_INCR_COUNT "_lgellir_player_incr_count_"

#define LGELLIR_OBJ_ID "_lgellirs_club_obj_"

#define LARSREYKR_ACTION_WORD "lg"

// DAEMON functions used by various club objects
#define LGELLIR_IS_DAEMON() (LGELLIRDAEMON->is_lgellir_daemon())
#define LGELLIR_PROCESS_ENABLED() (LGELLIRDAEMON->process_is_enabled())
#define LGELLIR_QUEST_ENABLED() (LGELLIRDAEMON->quest_is_enabled())
#define LGELLIR_ACCESS_GRANTED(ob) (LGELLIRDAEMON->access_granted(ob))
#define LGELLIR_ETHER_ACCESS(ob) (LGELLIRDAEMON->gellir_ether_access(ob))
#define LGELLIR_WINNERS_GALDRAR() (LGELLIRDAEMON->current_winners_galdrar())
#define LGELLIR_OLD_GALDRAR() (LGELLIRDAEMON->last_cycle_galdrar())
#define LGELLIR_NUM_NEW_GALDRAR() (LGELLIRDAEMON->num_galdrar_this_cycle())
#define LGELLIR_ART_GALDRAR() (LGELLIRDAEMON->ordered_voted_galdrar())
#define LGELLIR_HIGH_GALDR(ob) (LGELLIRDAEMON->last_highpower_galdr(ob))
#define LGELLIR_LAST_GALDR(ob) (LGELLIRDAEMON->gellir_last_galdr(ob))
#define LGELLIR_INSPIRE(ob) (LGELLIRDAEMON->inspire_gellir(ob))
#define LGELLIR_EXPIRE(ob) (LGELLIRDAEMON->expire_gellir(ob))
#define LGELLIR_GALDR_POWER(str) (LGELLIRDAEMON->galdr_power(str))
#define LARSGELLIR_DESCR(str) (LGELLIRDAEMON->gellir_description(str))
#define LGELLIR_PETNAME(str) (LGELLIRDAEMON->gellir_petname(str))
#define LGELLIR_SET_BOON_INCR(obj) (LGELLIRDAEMON->set_boon_increment(obj))
#define LGELLIR_LOG_BOON_COMPLETION(obj) (LGELLIRDAEMON->log_boon_completion(obj))
#define LGELLIR_SET_ETHERMSGS() (LGELLIRDAEMON->set_larsether_messages())
#define LGELLIR_GET_ETHERMSG(int) (LGELLIRDAEMON->get_larsether_message(int))
#define LGELLIR_UPDATE_DEATHS(str) (LGELLIRDAEMON->update_gellir_deaths(str))
#define IS_A_LARSGELLIR(ob) (LGELLIRDAEMON->is_a_larsgellir(ob))
#define IS_A_KRAFTORD(str) (LGELLIRDAEMON->is_a_kraftord(str))
#define IS_AN_EXCEPTED_NAME(str) (LGELLIRDAEMON->is_an_excepted_name(str))

// WIZARD-only functions
#define LGELLIR_QUERY_QUEST() (LGELLIRDAEMON->query_quest())
#define LGELLIR_ENABLE_QUEST() (LGELLIRDAEMON->enable_quest())
#define LGELLIR_DISABLE_QUEST() (LGELLIRDAEMON->disable_quest())
#define LGELLIR_NEW_KRAFTORD(s0,s1) (LGELLIRDAEMON->introduce_kraftord(s0,s1))
#define LGELLIR_BAN_KRAFTORD(str) (LGELLIRDAEMON->suspend_kraftord(str))
#define LGELLIR_SHOW_EXCEPTED() (LGELLIRDAEMON->show_excepted_names())
#define LGELLIR_EXCEPT_NAMES(str) (LGELLIRDAEMON->except_player_names(str))
#define LGELLIR_QUERY_PROCESS() (LGELLIRDAEMON->query_process())
#define LGELLIR_PROCESS_SUSPENSION() (LGELLIRDAEMON->process_suspension())
#define LGELLIR_PROCESS_RESUMPTION() (LGELLIRDAEMON->process_resumption())
#define LGELLIR_DAEMON_SHOWLOG() (LGELLIRDAEMON->show_daemon_log())
#define LGELLIR_DAEMON_MORELOGS() (LGELLIRDAEMON->more_daemon_logs())
#define LGELLIR_MORE_GALDRAR(str) (LGELLIRDAEMON->more_galdrar(str))
#define LGELLIR_VOTE_FOR_GALDR(str) (LGELLIRDAEMON->vote_for_galdr_merit(str))
#define LGELLIR_MORE_GELLIRS() (LGELLIRDAEMON->more_gellirs())
#define LGELLIR_BAN_GELLIR(str) (LGELLIRDAEMON->ban_gellir(str))
#define LGELLIR_UNBAN_GELLIR(str) (LGELLIRDAEMON->unban_gellir(str))
#define LGELLIR_NEW_WMAP(str) (LGELLIRDAEMON->import_write_globalwd_map(str))

#endif _LGELLIR_

