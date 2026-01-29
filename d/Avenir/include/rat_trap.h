// rat_trap.h, include file for rat trap quest
// Made by Boriska@Genesis, Nov 1994

#define GROUP 0
#define BIT 3
#define XP 3750
// I said once '3500-4000 looks OK to me', and Tep agreed :)
// Good example of finding a compromise, don't you think ?

#define RAT_CAUGHT_BY "_avenir_s_rat_caught_by"

#define RAT_ID "avenir_tunnel_rat"
#define RAT_ALIVE_ID "avenir_rat_alive"
#define TRAP_ID "avenir_rat_trap"
#define MEAT_ID "avenir_rotten_meat"

#define LOG_FILE "/d/Avenir/log/quest/rat_trap"

#define WRITE_LOG(ob,x) (write_file(LOG_FILE, ctime(time()) + " " + \
	     (ob)->query_name() + " (" + \
	     (ob)->query_wiz_level() + "," + \
	     (ob)->query_average_stat() + ") " + (x)))
