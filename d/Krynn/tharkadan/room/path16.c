#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

#define I_SEE_CRACK    "_i_see_tharkadan_troll_cave"

string *herbs = HERB_MASTER->query_herbs(({"mountains","hills",}));

void
reset_tharkadan_room()
{
    set_searched(0);
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + "vale1","northwest","@@exit_canyon");
    add_exit(ROOM + "path15","southeast",0);

    add_item(({"narrow canyon","canyon"}),"You stand within a dark " +
        "narrow canyon between two ridges of the Tharkadan Mountain " +
        "Range. It continues to your southeast while opens to a " +
        "valley to your northwest.\n");
    add_item(({"ridges","two ridges","ridge"}),
        "The walls of two ridges make the narrow canyon you now stand " +
        "in.\n");
    add_item(({"walls","wall","canyon walls","ice"}),
        "The walls of the canyon are uncomfortably close and slick with " +
        "ice, making climbing them impossible. " +notice_crack()+ "\n");
    add_item(({"valley","vale","wide vale"}),"To your northwest a " +
        "valley opens up.\n");
    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
      "@@add_item_snow");
    add_item(({"dark narrow crack","narrow crack","crack"}),
        "@@narrow_crack_desc");

    add_cmd_item(({"crack","narrow crack","dark narrow crack","into crack",
        "into the crack","into the narrow crack","into the dark narrow " +
        "crack"}), ({"enter","squeeze"}),"@@enter_crack");

    add_search(({"walls","shadows","wall","canyon walls"}), 5,
        "search_walls", 1);

    add_prop("_no_path_tharkadan", 1);
    add_prop(ROOM_S_DARK_LONG, "A dark, narrow canyon. The shadows " +
          "are too deep to see anything without a light source.\n"); 
    add_prop(ROOM_S_DARK_MSG, "The shadows of the canyon are too deep " +
           "to"); 
    add_prop(ROOM_I_LIGHT, DARKNESS_PASSIVE);

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "canyon","ground" }), 3);

    reset_tharkadan_room();
}

string
notice_crack()
{
   if(TP->query_skill(SS_AWARENESS) > (20 + random(40)))
   {
      TP->add_prop(I_SEE_CRACK, 1);
      return "On the southwestern wall of the canyon you notice a " +
             "dark narrow crack leading into darkness.";
   }
   return "";
}

string
narrow_crack_desc()
{
   if(TP->query_prop(I_SEE_CRACK))
      return "You notice a dark narrow crack in the southwestern wall " +
          "of the canyon, leading into darkness. You could probably " +
          "squeeze into the crack if you wanted to.\n";
   else
      return "You don't see that.\n";
}

string
enter_crack()
{
   if(!TP->query_prop(I_SEE_CRACK))
      return "What?\n";

   write("You squeeze through the narrow crack into a dark cave.\n");
   say(QCTNAME(TP) + " steps into the shadows and vanishes from view!\n");
   TP->move_living("M", TROLL_CAVES + "troll_caves1", 1, 0);

   return "";
}

string
search_walls(object searcher, string what)
{
    if (CAN_SEE_IN_ROOM(searcher))
      {
	    searcher->add_prop(I_SEE_CRACK, 1);
	    return ("You discover a dark narrow crack in the " +
               "southwestern wall of the canyon, leading into " +
               "darkness.\n");	    
    }
   return 0;
}

int
exit_canyon()
{
   write("You leave the dark canyon and enter an isolated valley...\n");
   return 0;
} 

string
short_descr()
{
    return "dark narrow canyon between two ridges of the Tharkadan " +
        "Mountains";
}

string
long_descr()
{
    return "You stand in a narrow canyon between two ridges of the " +
       "Tharkadan Mountains. The height and closeness of the canyon " +
       "walls cast deep shadows around you, and you doubt the light " +
       "of the sun gets down here often. To your northwest the " +
       "canyon opens up to a wide vale while continuing to your " +
       "southeast.\n";
}

