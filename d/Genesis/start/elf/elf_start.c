
#include "stddefs.h"

#pragma save_binary

inherit TERRAIN_FIR_FOREST;

create_mapsquare(int wlx, int wly, int slx, int sly) 
{ 
  set_exceptions(({ 
    "x.5y.7", "/d/Genesis/start/elf/glade" ,
    "x.5y.5", ROOMDIR + "trade_road_1.c",
    "x.4y.4", ROOMDIR + "trade_road_2.c",
    "x.5y.3", ROOMDIR + "trade_road_3.c",
    "x.5y.2", ROOMDIR + "trade_road_4.c",
    "x.4y.1", ROOMDIR + "trade_road_5.c",
    "x.3y.1", ROOMDIR + "trade_road_6.c",

    "x.3y.4", ROOMDIR + "cairn",
    "x.4y.2", ROOMDIR + "orchard_1",
    "x.6y.5", ROOMDIR + "magestone_place"
    }));

  ::create_mapsquare(wlx, wly, slx, sly);
}
