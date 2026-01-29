
// definitions and such for the water quest at
// the outpost.
//  -Cirion, Jan 1996

#define GROUP                0
#define BIT                  12

#define EXP                  150

#define EVIL_ALIGN           -300
#define GOOD_ALIGN           100

#define GOOD_PRESTIGE        50
#define BAD_PRESTIGE         -2

#define GOOD_PROP            "_avenir_quest_good_water"
#define EVIL_PROP            "_avenir_quest_evil_water"

#define POISON               "/d/Avenir/common/outpost/obj/water_poison"
#define POISON_PROP          "_avenir_quest_water_is_poisoned"
 
#define QUEST_FILE           "/d/Avenir/log/quest/outpost_water"

#define WRITE_THIS_LOG(file, msg) \
             (write_file(file, ctime(time()) + " " + (msg)))


