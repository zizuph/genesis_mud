#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#define LIBDIR          "/d/Gondor/std/library/"
#define BOOK            LIBDIR + "book"
#define W_BOOK		LIBDIR + "bbook"

#define BEDIT           "/obj/edit"
#define MOREOBJ         "/obj/more"

#define ACCESS_LEVEL(bname)   gTopics[mkmapping(map(TOPICLIST, lower_case),\
                                      TOPICLIST)[gBooks[bname][1]]]


