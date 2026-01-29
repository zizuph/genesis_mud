#ifndef _GREY_HAVENS_SPARKLE_SHIPLINE
#define _GREY_HAVENS_SPARKLE_SHIPLINE 1

#include "../ship.h"

#define SHIPLINE_DIR (BASE_SHIP_DIR + "gh-sparkle/")

#define CABIN          (SHIPLINE_DIR + "ship/cabin")
#define CREWROOM       (SHIPLINE_DIR + "ship/crewroom")
#define PLATFORM       (SHIPLINE_DIR + "ship/platform")
#define DECK           (SHIPLINE_DIR + "ship/deck")
#define CAPTAIN        (SHIPLINE_DIR + "crew/riondir")
#define HELMSMAN       (SHIPLINE_DIR + "crew/targon")
#define TICKET         (SHIPLINE_DIR + "objs/ticket")
#define CUTLASS        (SHIPLINE_DIR + "objs/cutlass")
#define SHIELD         (SHIPLINE_DIR + "objs/shield")

#define SHIP_NAME      "Flying Swan"

#define SPARKLE_PIER        "/d/Genesis/start/human/town/pier3"
#define GREY_HAVENS_PIER    "/d/Shire/common/greyhaven/shore"

#include "/d/Gondor/met_defs.h"

#define BS(x)    break_string(x, 75)
#define BSN(x)   (BS(x) + "\n")
#define WRITE(x) this_player()->catch_msg(x)
#define NF(x)    notify_fail(x)
#define NFN(x)   NF(BSN(x))
#define NFN0(x)  { NFN(x); return 0; }
#define WRITEN(x) write(BSN(x))
#define HIM_HER(x) x->query_objective()

#endif
