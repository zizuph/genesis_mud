// File to be included for the hat
// quest in the port
//      --Cirion, Feb 1996--
#define GROUP                1
#define BIT                  0

#define EXP                  200
#define ALIGN                50
#define PRESTIGE             20
#define QUEST_FILE           "/d/Avenir/log/quest/hat_quest"
#define HAT_FILE        "/d/Avenir/common/bazaar/Obj/worn/special_hat"
 
#define WRITE_THIS_LOG(file, msg) \
             (write_file(file, ctime(time()) + " " + (msg)))
 
