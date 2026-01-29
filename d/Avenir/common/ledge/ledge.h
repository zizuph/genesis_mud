
//          ledge.h
// creator(s):   Ilyian
// last update:           
// purpose:      To be #included /ledge files
// note:       
// bug(s):
// to-do:

#include "/d/Avenir/common/common.h"

#define WRITE_THIS_LOG(file, msg) \
             (write_file(file, ctime(time()) + " " + \
             this_player()->query_name() + "(" + \
             this_player()->query_average_stat() + ") " + \
             (msg)))

#define CHISEL_LOG      "/d/Avenir/log/chisel_log"
#define L_SOURCE        (OUTPOST + "obj/lsource")


#define LONG    set_long
#define SHORT   set_short

