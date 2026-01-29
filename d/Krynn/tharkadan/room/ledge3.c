#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"mountains",}));

void
reset_tharkadan_room()
{
    set_searched(0);
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + "ledge2","southwest",0);

    add_item(({"valley","vale","wide vale","protected vale",
         "isolated valley", "floor","centre","forested valley"}),
         "You stand on the side of a towering peak overlooking a wide " +
         "vale rimmed by mountains. Aspens and firs grow in abundance, " +
         "although the most notable feature of this valley is the " +
         "towering peak you currently stand on.\n");
    add_item(({"mountains"}),"Mountains rim the valley beneath you.\n");
    add_item(({"aspen","aspen trees","aspens"}), "You see aspen trees " +
         "growing in large numbers in the valley below.\n");
    add_item(({"fir","fir trees","firs"}), "You see large fir trees " +
         "growing in the valley below.\n");
    add_item(({"trees","tree"}), "Aspens and firs grow in abundance " +
         "below in the valley.\n");
    add_item(({"snow","snow-covered","snow-covered ground",
	 "white","snow-covered land","winters snow","winter's snow"}),
         "@@add_item_snow");
    add_item(({"towering peak","peak","ancient volcano","volcano",
         "mountain","ledge"}), "You are standing on a ledge on the side " +
         "of a towering peak, likely once an ancient volcano. Below you " +
         "can see this mountain stands alone amongst a sea of aspen and " +
         "fir trees.\n");
    add_item(({"cracks","deep cracks"}),"Deep cracks run up the side of " +
         "the peak here towards the summit. You could probably attempt " +
         "to climb them.\n");
    add_item(({"summit"}), "You look up towards the summit, and " +
         "estimate you are probably halfway to the top.\n");

    add_cmd_item(({"cracks","deep cracks","up","up cracks"}), "climb",
        "@@climb_cracks");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "canyon","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "a ledge on the side of a towering peak in the Tharkadan " +
        "mountain range";
}

string
mountain_desc()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
    case SUMMER:
	str = "The ledge ends here, running steeply downwards to your " +
           "southwest. Cracks running up the side of the peak here " +
           "do look deep enough to climb, if you have the confidence! ";
	break;
    case AUTUMN:
    case WINTER:
	str = "The snow-covered ledge ends here, running steeply " +
            "downwards to your southwest. Cracks run up the side of " +
            "the peak here, largely protected from the snow, and look " +
            "deep enough to allow you to climb if you have the " +
            "confidence! ";
	break;
    }
    return str;
}

string
long_descr()
{
    return "You stand on a ledge running along the side of a towering " +
        "peak that sits in the centre of a forested valley. " +
        mountain_desc()+ "\n";
}

string
climb_cracks()
{
      if(TP->query_skill(SS_CLIMB) < 35)
      {
        write("You start climbing the cracks up along the side of " +
            "the peak. You reach a point where the crux of the climb " +
            "is too difficult for one of your skill, and you are " +
            "forced to return down to the ledge.\n");
        say(QCTNAME(TP) + " starts climbing the cracks up along the " +
            "side of the peak. " +C(HE(TP))+ " reaches a point where " +
            "the crux of the climb is too difficult, forcing " +HIM(TP)+ 
            " to return down to the ledge.\n");
        return "";
      }

      write("You confidently start climbing the cracks up along the " +
          "side of the peak, eventually pulling yourself up on to a " +
          "ledge higher up the mountain.\n");
      say(QCTNAME(TP) + " confidently starts climbing the cracks up " +
          "along the side of the peak.\n");
        TP->move_living("up along the cracks", ROOM + "ledge4", 1, 0);
      return "";
}