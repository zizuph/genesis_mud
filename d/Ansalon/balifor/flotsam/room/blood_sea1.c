#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;

#include "/d/Krynn/common/herbsearch.h"
#define H1 "/d/Krynn/common/herbs/bull_kelp"
#define H2 "/d/Krynn/common/herbs/sargassum"

void
reset_flotsam_room()
{
   return;
}


create_flotsam_room()
{
   set_short("Swimming in the Blood Sea");
   set_long("@@long_descr");
   add_item("sea","Yep, there sure is a lot of it.\n");
   

   add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
   add_exit(FROOM + "street24","south", 0);
   add_exit(FROOM + "blood_sea2","northeast", 0);
   add_exit(FROOM + "blood_sea1","west", 0);
   add_exit(FROOM + "blood_sea1","east", 0);
   add_exit(FROOM + "blood_sea1","northwest", 0);
   add_exit(FROOM + "blood_sea1","north", 0);

    seteuid(getuid(TO));
    set_search_places(({"sea","water","herbs"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(H1);
    add_herb_file(H2);

   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + "You are swimming in the red waters of " +
   "the Blood Sea of Istar. The water here is still fairly shallow " +
   "however further northward the sea becomes deeper.\n";
}

string
swim_water()
{
    write("You have a quick wade around in the water here "+
      "and then return to shore.\n");
    return "";
}
