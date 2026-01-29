//-*-C++-*-
// file name: d/Avenir/common/outpost/outpost.h
// creator(s):  Kazz    Jan '95
// last update: May 1995, 
// purpose:     misc. header file
// note:
// bug(s):
// to-do:  

#include "/d/Avenir/common/common.h"

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

#define ENTR_LOG	"/d/Avenir/log/outpost/entrance"

#define MON		"/d/Avenir/common/outpost/mon/"
#define OBJ		"/d/Avenir/common/outpost/obj/"

#define TOMATO_ID	"avenir_tomato_id"

#define SHORT   set_short
#define LONG	set_long

#define ADD_TUNNEL_ITEMS \
        add_item(({"tunnel"}), \
		 "The tunnel walls are naturally smooth on the eastern " + \
                 "side, and chiseled on the western.\n" ); \
	add_item(({"east wall", "eastern wall"}), \
		 "This half of the tunnel seems to be carved from the " + \
                 "rock.\n" ); \
        add_item(({"west wall", "western wall"}), \
		 "The western wall seems naturally smooth, perhaps from " +\
                 "flowing water.\n" );
