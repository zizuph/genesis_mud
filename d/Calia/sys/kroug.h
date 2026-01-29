
/* 
   Definitions for smart krougs in Calia.

   Maniac 1/8/95 
*/


/* Raid defs */
#define RAID_MIN_GROUP_SIZE 2
#define RAID_MAX_GROUP_SIZE 25
#define RAID_MIN_GROUPS 3 
#define RAID_MAX_GROUPS 16   
#define RAID_MEMLIM 95
#define RAID_MIN_WARNING_DUR 2   /* minumum raid warning duration */ 
#define RAID_MAX_WARNING_DUR 15  /* maximum raid warning duration */ 
#define RAID_MIN_KROUGS 15  /* minimum number of krougs for raid */
#define RAID_PRE_RAID 0          /* Before any raid has been initiated. */
#define RAID_CHECK_ROOMS 1       /* Rooms being checked */ 
#define RAID_WARNING_PERIOD 2    /* warning period currently in progress. */
#define RAID_ACTIVE 3       /* raid currently in progress. */
#define RAID_TERMINATING 4  /* raid in the process of terminating */
#define RAID_TERMINATED 5   /* raid terminated by wizard. */  
#define RAID_OVER 6 /* Raid completed by natural means (all krougs wiped). */ 

#define KROUG_S_HOME_ROOM "_kroug_s_home_room"
#define OBJ_I_KROUG_ORIGIN "_obj_i_kroug_origin"

/* Kroug types */
#define NUM_KROUG_TYPES 6
#define KROUG_WEAK 0
#define KROUG_REGULAR 1
#define KROUG_TOUGH 2
#define KROUG_ELITE 3
#define KROUG_ULTRA 4
#define KROUG_MONSTER 5

/* Elite kroug subtypes */
#define ELITE_SWORD 1
#define ELITE_AXE 2
#define ELITE_SPEAR 3


/* avenger details */
#define WRATHFUL_AVENGER 0
#define FURIOUS_AVENGER 1
#define RAGING_AVENGER 2
#define DEADLY_AVENGER 3
#define AVENGER "/d/Calia/std/avenger"
#define MT_OB "/d/Calia/mountain/obj/"

#define KROUG_BRAIN "/d/Calia/special/kroug_brain"
#define KROUG_RAID_ROOM "/d/Calia/kroug_raid_room"
#define KROUG_WAITING_ROOM "/d/Calia/special/kwr/kroug_waiting_room"
#define PALACE_RAID_ROOM "/d/Calia/palace_raid_room"
#define PALACE_RAID_OB "/d/Calia/special/palace_raid"
#define PALACE_RAID_SAVE "/d/Calia/special/palace_raid_save"
#define RAID_HELP "/d/Calia/special/raidhelp.txt"
#define GELAN_RAID_ROOM "/d/Calia/gelan_raid_room"

#define LIVE_I_NO_ATTACKED_BY_SMART_KROUG "_live_i_no_attacked_by_smart_kroug"
#define MIN_AVG_STAT_TO_ATTACK 30

#define KROUG_SAY_VERBS  ({"growls", "grumbles", "blurts", "grunts", \
                           "pukes", "garbles", "burbles" })

#define KROUG_ADJ1  \
    ({ "green-haired", "orange-haired", "purple-haired",  \
       "raven-haired", "red-haired", "grey-haired",  \
       "long-nosed", "sharp-nosed", "red-nosed", "beak-nosed", \
       "warty", "black-eyed", "green-eyed", "red-eyed", "white-eyed", \
       "slit-eyed", "wide-eyed", "crazy-eyed",  \
       "pointy-eared", "big-eared", "flappy-eared",  \
       "fat-lipped", "black-lipped",  \
       "fork-tongued", "snake-tongued",  \
       "sarcastic", "vitriolic", "gibbering", "wild",   \
       "psychotic",  \
       "cunning", "wily", "uncompromising", "offensive",  \
       "anarchic", "angry", "furious", "raving", "frantic" })

#define KROUG_ADJ2  \
   ({ ({"slight", "miniature", "pint-sized", "impish",  \
        "skinny", "runt-like", "diminutive", "inexperienced",  \
        "small" }),    \
   ({"burly", "strong-armed", "big", "well-built",   \
      "large", "thick-set", "agile", "strong", "stout" }),  \
   ({"menacing", "experienced", "muscular", "steely",  \
     "fierce", "broad-shouldered", "swift", "tough",  \
     "dangerous" }),  \
   ({"ferocious", "huge", "venomous",  \
     "massive", "enormous", "mighty",  \
     "musclebound", "athletic" }),  \
   ({"terrifying", "demonic", "towering",  \
     "titanic", "deadly" }), \
   ({"terrifying", "demonic", "towering",  \
     "titanic", "deadly" })   })

#define KROUG_TYPE_NP_SING ({ "lesser warrior", "regular", \
                              "high ranking warrior", \
                              "elite warrior", \
                              "commander","monster" }) 
 
#define KROUG_TYPE_NP ({"lesser warriors", "regulars",   \
                        "high ranking warriors",   \
                        "elite warriors", "commanders","monsters"}) 

#define KROUG_DESC(type, num) ((num == 1) ? KROUG_TYPE_NP_SING[type] : \
                                            KROUG_TYPE_NP[type]) 

#define KROUG_TYPE_PHYS  ({"weak", "average", "formidable",   \
                           "very powerful", "extremely powerful", \
                           "extremely powerful" })

#define KROUG_MOVE_DESC ({ "struts", "saunters", "speeds",  \
                  "bounces", "wanders", "heads" }) 
 
#define KROUG_TYPE_TRAIN \
          ({"not been very well trained",     \
            "trained to a reasonable level of combat skill",     \
            "well trained in combat skills",       \
            "trained to become exceptionally skilled",     \
            "trained to become peerlessly skilled", \
            "trained to become peerlessly skilled" })

