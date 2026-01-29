/*
 * - /sys/basic.h
 * This holds common definitions that are used throughout the domain.
 */

/* Include the basic includes used for almost every file */
#include <composite.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>   /* required for SECURITY definition. */
#include <stdproperties.h>

#define TP          this_player()
#define TO          this_object()
#define TI          this_interactive()
#define NF(x)       notify_fail(x)
#define NFN(x)      notify_fail(x + "\n")
#define NFN0(x)     { NFN(x); return 0; }
#define ENV(x)      environment(x)
#define E(x)        environment(x)
#define CAP(x)      capitalize(x)
#define LC(x)       lower_case(x)
#define LS(x)       LANG_SHORT
#define LAS(x)      LANG_ASHORT
#define LTS(x)      LANG_THESHORT
#define HE_SHE(x)   (x)->query_pronoun()
#define HIS_HER(x)  (x)->query_possessive()
#define HIM_HER(x)  (x)->query_objective()
#define FIXEUID     { setuid(); seteuid(getuid()); }
#define LOG_SIZE    50000
#define ONE_OF(x)   one_of_list(x)
#define ONE_OF_LIST(x)  ONE_OF(x)
#define F_VOLUME_ARMOUR this_object()->query_prop(OBJ_I_WEIGHT)/4
#define F_VOLUME_WEAPON this_object()->query_prop(OBJ_I_WEIGHT)/5

//#define MORE(x)    this_player()->more(read_file(x, 2))

// Obsolete, but kept for backwards compatibility
#define HE(x)   (x)->query_pronoun()
#define HIS(x)  (x)->query_possessive()
#define HIM(x)  (x)->query_objective()


// global to set max number of unique items in domain
#define MAX_UNIQUE_ITEMS 7
#define UNIQUE_CLONE(file, MAX_UNIQUE_ITEMS, alt_file_name) \
    "/d/Faerun/sys/global/clones"->unique_clone(file, MAX_UNIQUE_ITEMS, alt_file_name)

// Props
#define NO_STEEDS   add_prop(ROOM_I_ALLOW_STEED, 0)
#define ALLOW_STEEDS    add_prop(ROOM_I_ALLOW_STEED,1)
#define INDOORS     add_prop(ROOM_I_INSIDE, 1)
#define INSIDE      add_prop(ROOM_I_INSIDE, 1)
#define OUTDOORS    add_prop(ROOM_I_INSIDE, 0)
#define OUTSIDE     add_prop(ROOM_I_INSIDE, 0)
#define DARK        add_prop(ROOM_I_LIGHT, 0)
#define NO_LIGHT    add_prop(ROOM_I_LIGHT, 0)
#define NOLIGHT     add_prop(ROOM_I_LIGHT, 0)


// shortcut to log events
//#define LOG_FILE(filename,text)      log_file(filename,extract(ctime(time()), 4,15) + " " + CAP(TP->query_real_name())+ "  " + "(" + TP->query_average_stat() + ") " + text + "\n");

// new log - Month Day Year
#define LOG_FILE(filename,text)              log_file(filename, (extract(ctime(time()), 4,9) + " " + (extract(ctime(time()), 20) + " " + CAP(TP->query_real_name())+ "  " + "(" + TP->query_average_stat() + ") " + text + "\n")));



// shortcut to log quests
#define QUEST_LOG_FILE(quest_name,exp)      log_file("QUESTS", (extract(ctime(time()), 4,9) + " " + (extract(ctime(time()), 20) + " " + CAP(TP->query_real_name())+ "  " + "(" + TP->query_average_stat() + ") completed the " + quest_name + " and received " + exp + " experience.\n")));
