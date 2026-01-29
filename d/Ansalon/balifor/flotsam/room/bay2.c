#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>

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
   set_short("Rough waters of the Blood Bay");
   set_long("@@long_descr");
   
   add_item("wreck","On the side of the wreck facing " +
      "you, you notice a great gaping hole, torn open by " +
      "one of the great rocks. \n");
   add_item("hole","You could probably enter the vessel " +
      "through this hole. \n");
   
   add_invis_exit(FROOM + "nowhere","north","@@no_go");
   add_invis_exit(FROOM + "nowhere","south","@@no_go");
   add_invis_exit(FROOM + "nowhere","west","@@rocks");
   add_invis_exit(FROOM + "bay1","east","@@bay");
   
   add_cmd_item(({"ship","in ship","into ship",
            "vessel","in vessel","into vessel",
            "wreck","in wreck","into wreck",
            "hole","into hole","in hole"}),
      ({"enter","climb","go"}),
      "@@into_ship");
   
   
   set_tell_time(40);
   add_tell("Waves crash over you " +
      "with a malevolent mind of their own, trying to drag you " +
      "to the sea floor. \n");

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
   return tod_descr1() + "Great waves crash over you, pushing " +
   "you dangerously close to great sharp rocks. In front of " +
   "you lies the wreck of an old fishing vessel, hanging " +
   "precariously on the points of the rocks. The rough waters " +
   "make it difficult to make out anything else of your " +
   "surroundings. \n";
}

int
no_go()
{
   write("You try and swim in that direction, but wind and waves " +
      "push you back. \n");
   return 1;
}

int
rocks()
{
   write("West of you are great sharp rocks that would tear you " +
      "to nothing more than fish food. You decide not to go in that " +
      "direction. \n");
   return 1;
}

int
bay()
{
   write("You swim into slightly calmer waters... \n");
   return 0;
}


string
into_ship()
{
   write("You pull yourself into the wreck...\n");
   TP->move_living("into the wreck",
      FROOM + "ship_wreck",1,0);
   return "";
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
        start_room_tells();
}
