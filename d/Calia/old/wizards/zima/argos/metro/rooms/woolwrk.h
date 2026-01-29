/* note: fees should be UNIQUE for each service; no 2 exact same price */
#define  CLOAK_FEE   35
#define  TUNIC_FEE   30
#define  YARN_FEE    12
 
/* number of steps in spinning/weaving sequence */
#define  NUM_STEPS   6
 
/* Lists of random actions for spinning and weaving. Coded as emotes */
#define SpinAction ({                                               \
        "hums a light tune as she works.",                          \
        "squirms in her chair as she keeps the wheel spinning.",    \
        "spins the wheel in a perfect rhythm.",                     \
        "continues to feed the wool into the spinning wheel.",      \
        "works feverishly behind the spinning wheel.",              \
        "wraps the yarn around a spool as it comes off the wheel.", \
        "spins the wheel faster with perfect coordination.",        \
        "nods at you appreciatively as she works.",                 \
        "hums as she spins."                                        \
        })
 
#define WeaveAction ({                                           \
        "hums a light tune as she works.",                       \
        "squirms in her chair as she works the loom.",           \
        "works the loom with a perfect rhythm.",                 \
        "continues threading the yarn through the loom.",        \
        "labors feverishly behind the loom.",                    \
        "sings a motherly tune as she weaves.",                  \
        "pulls some of the new cloth off the loom.",             \
        "uses a knitting needle on the new material.",           \
        "hums as she weaves."                                    \
        })
 
