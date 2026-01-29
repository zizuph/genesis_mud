/*
 * ldefs.h
 *
 * Defines for the Silent Forest.
 *
 * Copyright (C): Tianar, Jul 2003
 * Work continued and changed by Baldacin, Sep 2003.
 *
*/

// I N C L U D E D   F I L E S
#include "/d/Calia/domain.h"
#include <macros.h>

// D E F I N I T I O N S
#define GUILDS      "/d/Calia/guilds/"
#define SFDIR       "/d/Calia/argos/silent_forest/"
#define AMAZONDIR   (GUILDS + "amazon_race/")
#define SFSTD       (SFDIR + "std/")
#define SFEQDIR     (SFDIR + "equipment/")
#define SFLIVDIR    (SFDIR + "living/")
#define SFOBJDIR    (SFDIR + "objects/")
#define SFLOGDIR    (SFDIR + "logs/")
#define HERBDIR     (SFDIR + "herbs/")
#define AMAARMDIR   (AMAZONDIR +"objects/armours/")
#define AMAWEPDIR   (AMAZONDIR +"objects/weapons/")

#define FORESTSTD   (SFSTD + "forest_std.c")
#define CAVESTD     (SFSTD + "cave_std.c")
#define AMAZONSTD   (AMAZONDIR + "npcs/std_amazon.c")

#define HE(x)       x->query_pronoun()
#define HIS(x)      x->query_possessive()
#define HIM(x)      x->query_objective()
#define LOGFILE(x,y)       write_file(SFLOGDIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )

/* where do we end up if we leave this area? */
#define SILFOR_ACCESS   "/d/Calia/argos/nwterr/rooms/sfor13"

#define EXITNOTOBVIOUS  1
#define FOREST_FATIGUE  2
#define MOUNT_FATIGUE   (8 - (TP->resolve_task(TASK_DIFFICULT, \
                            ({ TS_CON, SS_CLIMB })) ? 4 : 0))
#define LIVE_I_KILLED_UNDEAD_CHAMP "_live_i_killed_undead_champ"

// STD ROOM DEFINES
#define NOCLIFF     0
#define ADDCLIFF    1
#define MM_FOREST   1
#define MM_CREEK    2
#define MM_LAKE     3
#define MM_SHRINE   4
