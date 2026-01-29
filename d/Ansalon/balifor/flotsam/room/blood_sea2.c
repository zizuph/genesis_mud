#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;

#include "/d/Krynn/common/herbsearch.h"
#define H1 "/d/Krynn/common/herbs/bull_kelp"
#define H2 "/d/Krynn/common/herbs/sargassum"

int thrown_bait = 0;

void
reset_flotsam_room()
{
    thrown_bait = 0;
}


create_flotsam_room()
{
   set_short("Swimming in the Blood Sea");
   set_long("@@long_descr");
   add_item("sea","The deep water must contain different sorts of fish, "+
                  "perhaps even lethal ones.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
   add_exit(FROOM + "blood_sea2","south", 0);
   add_exit(FROOM + "blood_sea2","northeast", 0);
   add_exit(FROOM + "blood_sea2","west", 0);
   add_exit(FROOM + "blood_sea2","east", 0);
   add_exit(FROOM + "blood_sea2","northwest", 0);
   add_exit(FROOM + "blood_sea2","north", 0);
   add_exit(FROOM + "blood_sea1","southwest", 0);
   add_exit(FROOM + "blood_sea2","southeast", 0);

/*  
   There is no shark file as outlined below, so I've disabled this
   cmd item - Arman, April 2017

   add_cmd_item(({"bait","bloody bait","shark bait"}),
     ({"throw"}),"@@throw_bait");

*/

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
    if (!thrown_bait)
    {
        return tod_descr1() + "You are swimming in the red waters of " +
       "the Blood Sea of Istar. The water here is actually very deep " +
       "the water has almost changed into a black reddish color. "+
       "Far to the southwest the faint lights of the city of Flotsam "+
       "can be seen. The sea continues in all directions here.\n";
    }
    else
    {
        return tod_descr1() + "You are swimming in the red waters of " +
       "the Blood Sea of Istar. The water here is actually very deep " +
       "the water has almost changed into a black reddish color. "+
       "Far to the southwest the faint lights of the city of Flotsam "+
       "can be seen. The sea continues in all directions here.\n"+
       "A large pool of blood has dyed the water deep red.\n";
    }
}

int
summon_shark()
{
    object shark;

    shark = clone_object("/d/Ansalon/guild/pirates/npc/shark.c");
    shark->move(TO);
}


string
throw_bait()
{
    if (!P("_shark_bait",TP))
    {
        write("What ?\n");
        return "";
    }

    if (thrown_bait)
    {
        write("You throw the bloody bait in the water, but it just blends into the "+
              "rest of the blood and disappears into the water.\n");
        return "";
    }

    thrown_bait = 1;

    write("You throw the bloody shark bait into the water.\n");
    set_alarm(1.0,0.0, &write("The bloody bait flies though the "+
             "air...\n"));
    set_alarm(4.0,0.0, &write("With a loud SPLASH the bloody bait hits "+
             "the water.\n"));
    set_alarm(7.0,0.0, &write("The bloody bait begins to dye the color "+
             "deep red color.\n"));
    set_alarm(10.0,0.0, &write("Some fish arrives and begins to "+
             "eat the smaller pieces of bait.\n"));
    set_alarm(14.0,0.0, &write("You notice a dark shadow in the water to "+
             "the north.\n"));
    set_alarm(17.0,0.0, &write("Suddenly a massive shark rushes towards "+
             "you.\n"));
    set_alarm(17.0,0.0, &summon_shark());
    return "";
}

