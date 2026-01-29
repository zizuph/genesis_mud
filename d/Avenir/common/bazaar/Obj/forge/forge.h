#ifndef __BAZAAR_FORGE__
#define __BAZAAR_FORGE__

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 5000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

#define ARMSHOP_PATH      "/d/Avenir/common/bazaar/Obj/forge/"
#define FORGE_MASTER      (ARMSHOP_PATH + "forge_master")
#define ARM_STORE         (ARMSHOP_PATH + "armstore")
#define MS(delay, what)   (set_alarm(itof(delay), 0.0, &ms(what)))
#define ARM_B_COST        100

#define STYLE     one_of_list(FORGE_MASTER->query_styles())
#define LINING    one_of_list(FORGE_MASTER->query_linings())
#define DECOR     one_of_list(FORGE_MASTER->query_decors())
#define PLATING   one_of_list(FORGE_MASTER->query_platings())
#define COLOUR    one_of_list(FORGE_MASTER->query_colours())

#define ONONE     0 
#define OWORN     1
#define OSTYLE    2 
#define ODECOR    3
#define OPLATE    4
#define OCOLOUR   5
#define OLINING   6
#define OWORKING  7
#define OFINISHED 8

#endif  __BAZAAR_FORGE__
