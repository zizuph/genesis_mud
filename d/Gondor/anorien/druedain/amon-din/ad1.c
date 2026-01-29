/*  This is ad1.c
 *
 *  Tulkas, May 1995
 */
inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/common/lib/clock.h";
#include "/d/Gondor/elessar/lib/forest.h"
#include "/d/Gondor/common/lib/herb_list.h"
#include "/d/Gondor/defs.h"

#define TRACKING_NEEDED 20

void reset_room();
string check_tracking();

void
create_room()
{
  set_short("A dense thicket in the southern parts of the Druedain Forest in Anorien");
  set_long("@@describe");
  forest_density(15);
  set_noshow_obvious(1);
  add_item(({"path","ground"}),"@@exa_ground");
  add_item(({"thicket","shrubbery","shrubs","bushes","bush"}),BSN("Waist-high bushes of various kinds litter this area. They thin to the "
    + "southwest, past a particularly thick area of vegetation, where the "
    + "ground begins to climb slightly."));
  add_item(({"trees","tree","branches"}),BSN("These trees are very similar to the ones surrounding the path to the "
    + "northeast. You do notice that the moisture in this thicket has "
    + "produced some fungal blooms in various places along the bark."));
  add_item(({"structure","peak"}),BSN("From this vantage point you cannot see much. The top of the hill seems to "
    + "have been leveled somewhat, and there appears to be some sort of "
    + "activity going on."));
  add_item("track","@@exa_track");
  add_item(({"hill","slope","amon din"}), "@@exa_hill");

    set_up_herbs( ({ HERB_DIR + "suranie",
                     ONE_OF_LIST(HERBS), ONE_OF_LIST(HERBS), }),
                          ({ "ground","trees","shrubs","shrub","tree", }),
                  3 );

    add_exit(ANO_DIR + "road/wr3", "northeast");
}

string
describe()
{
  string long_descf,time;
  object clock;
  clock = find_object(CLOCK);
  time = clock->query_time_of_day();
  long_descf = "You find yourself in a dense thicket crowded by various sorts of shrubbery. ";
  if (time =="evening" || time =="night")
    long_descf +="The "+time+" air is chill here, and the forest purrs with the sounds "+
     "of sleepless creatures. It is difficult to see very clearly in the darkness. ";
    else long_descf +="The "+time+" sunlight is peeking through the slowly moving branches overhead, and "+
    "the ground can be seen rising slightly to the southwest where the thicket "+
     "runs thinner. ";
  long_descf +="Directly to the west a large hill looms into view, rising above the Druedain "+
    "treetops, and a roadway is barely visible to the northeast. ";
  long_descf = long_descf + check_tracking();
  return break_string(long_descf+"\n",75);
}
  
string
exa_ground()
{
  return "The ground here is grassy and overgrown, yet shows slights signs of wear.\n"+
    "You wonder if you are the first to pass through here.\n";
}

string
exa_track()
{
  if (this_player()->query_skill(SS_TRACKING) > TRACKING_NEEDED)
    return "Your skilled eyes discover a track leading southwest through "+
     "the thicket. It is well hidden in this dense growth.\n";
  else return "You are unable to see any track here.\n";
}

string
check_tracking()
{
  if (this_player()->query_skill(SS_TRACKING) > TRACKING_NEEDED)
    return "Your skilled eyes discover a track leading southwest. "+
           "It seems as if someone does not wish it to be seen. ";
  else return "The thicket looks too dense to pass through to the southwest.";
}

void
init() {
  ::init();
  add_action("follow_track","follow");
  add_action("follow_track","southwest");
  add_action("follow_track","sw");
}

int
follow_track(string str)
{
  if (query_verb()=="follow" && !str) return 0;
  if ((query_verb()=="follow" && (str=="track" || str=="track southwest"))
  || query_verb()=="southwest" || query_verb()=="sw") {
     if (this_player()->query_skill(SS_TRACKING) < TRACKING_NEEDED) {
      write("You're not able to go that way, the thicket is too dense,\n"+
          "and you can't seem to find any track to follow.\n");
       return 1;
       }
    write("You skillfully follow the track to the southwest.\n");
    this_player()->move_living("southwest","/d/Gondor/anorien/druedain/amon-din/ad2");
     return 1;
     }
  return 0;
}

void
reset_room()
{
    set_searched(0);
}

string
exa_hill()
{
    string  htxt;

  htxt = "This must be Amon Din, site of the first of the northern beacon towers "
    + "of Gondor. Dense trees extend nearly halfway up the slope, thinning "
    + "nearer to the top which appears to be mostly bare rock. A structure of "
    + "some sort is barely visible atop the peak.";

    if (rq_stage() >= RQ_STAGE_WAR)
    {
        htxt += " Above the structure, a bright beacon has been lit.";
    }
    return BSN(htxt);
}
