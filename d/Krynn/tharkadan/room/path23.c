#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"mountains","hills",}));
#define HAS_SEARCHED   "_has_found_hopeful_vale"

int see_trail = (25 + random(25));
int found_trail;

void
reset_tharkadan_room()
{
    set_searched(random(2));
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
        "@@add_item_snow");
    add_item(({"path","trail","pass","valley pass","highlands"}),
        "You stand on the edge of a precipice that drops into a steep " +
        "canyon on a trail running through the Tharkadan Mountain Range. " +
        "Snow-covered peaks and ridgelines rise around you. " +
        "@@add_item_trail@@ \n");
    add_item(({"canyon","dirken canyon","precipice","glacier","edge",
        "steep canyon"}), "You stand on the edge of a precipice that " +
        "drops into a steep canyon known as Dirken Canyon. A stream " +
        "flowing from Crystal Lake to your north runs through the " +
        "canyon.\n");
    add_item(({"stream","crystal lake","lake","glacier"}),"To your " +
        "north a stream flows from Crystal Lake down a glacier " +
        "into the canyon below. It follows the canyon south.\n");
    add_item(({"valley","wooded valley"}), "@@wooded_valley");

    add_search(({"here","trail","ground","path"}), 5, "search_track", 1); 
    add_cmd_item(({"trail","the trail"}),"reveal","@@reveal_trail");
    add_cmd_item(({"precipice","down precipice","canyon","down canyon",
        "down"}), "climb", "There is nowhere along the edge of the " +
        "precipice for you to climb down into the canyon from here.\n");

    add_exit(ROOM + "path22","northeast",0);
    add_exit(ROOM + "path24","south",0);
    add_invis_exit(ROOM + "path26","east","@@go_east");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 6);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "on the edge of Dirken Canyon in the Tharkadan Mountains";
}

string
track_long()
{
   if((TP->query_skill(SS_TRACKING) > see_trail) || 
       TP->query_prop(HAS_SEARCHED) ||
       TP->query_guild_name_lay() == "Holy Order of the Stars")
     return "You also notice a well-disguised trail leading down into " +
         "a wooded valley to your east.";
   else
     return "";
}

string
long_descr()
{
    return "You stand on the edge of a precipice overlooking a steep " +
         "canyon running through the Tharkadan Mountain Range. A trail " +
         "runs along the edge of the canyon to your south while a path " +
         "leads northeast into the highlands. " +track_long()+ "\n";
}

string
add_item_trail()
{
   if((TP->query_skill(SS_TRACKING) > see_trail) || 
       TP->query_prop(HAS_SEARCHED) ||
       TP->query_guild_name_lay() == "Holy Order of the Stars")
     return "To your east you detect a well-disguised trail leading " +
         "down into a wooded valley. If you wanted to, you could " +
         "<reveal> the trail to others in your team.\n";
   else
     return "";
}

string
wooded_valley()
{
   if((TP->query_skill(SS_TRACKING) > see_trail) || 
       TP->query_prop(HAS_SEARCHED) ||
       TP->query_guild_name_lay() == "Holy Order of the Stars")
     return "To your east is a wooded valley. A trail leads to it that " +
        "looks like it has been skillfully hidden.\n";
   else
     return "What?\n";
}

int
go_east()
{
   if((TP->query_skill(SS_TRACKING) > see_trail) || 
       TP->query_prop(HAS_SEARCHED) ||
       TP->query_guild_name_lay() == "Holy Order of the Stars")
   {
       write("You follow a well-disguised trail east into a wooded " +
           "valley...\n");
       return 0;
    }

   write("There is no obvious exit east.\n");
   return 1;

}

string
reveal_trail()
{
   if((TP->query_skill(SS_TRACKING) > see_trail) || 
       TP->query_prop(HAS_SEARCHED) ||
       TP->query_guild_name_lay() == "Holy Order of the Stars")
   {
      object * team = TP->query_team_others();
      if (sizeof(team) > 0)
      {
         write("You reveal the trail east to everyone in your team.\n");
         say(QCTNAME(TP)+ " reveals a trail heading east to you.\n");

         foreach(object teammates: team)
         {
            teammates->add_prop(HAS_SEARCHED, 1);
         }
         return "";
       }
       write("You have no teammates to reveal the trail to.\n");
       return "";
   }

   return "What?\n";
}

string
search_track(object searcher, string what)
{
    int tracking_skill = searcher->query_skill(SS_TRACKING);

    if (CAN_SEE_IN_ROOM(searcher))
      {
	    if (tracking_skill <  random(75))
	    {
		  return ("You search around but find nothing of " +
                      "interest.\n");
	    }

	    searcher->add_prop(HAS_SEARCHED, 1);
	    return ("You discover a well-disguised trail leading " +
               "east into a wooded valley.\n");
	    
    }
   return 0;
}
