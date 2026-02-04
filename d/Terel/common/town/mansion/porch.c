inherit "/std/room";

#include "/d/Terel/common/terel_defs.h"

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>

#define TP          this_player()

#define VERY_HEAVY  (75)   /* percentage */
#define TORTURE     MANSION + "base/tort"
#define FOOD_ROOM   MANSION + "base/food_room"
#define ENTRANCE    MANSION + "entrance"

public void
create_room()
{
   object door;

   set_short("A porch");
   set_long("This is the porch to an old ruined manor.  " +
         "It has been deserted for some time now.  It has been rumoured " +
         "that this manor holds some connection with all of the recent " +
         "disappearences in town.  A thin rope hangs out of a small hole " +
         "in the wall next to the entrance.\n");

   add_item("entrance", "In it's prime, this entrance would indeed have " +
         "been impressive.  However, the years of neglect have taken " +
         "their toll on the paintwork.\n");
   add_item(({"paint", "paintwork"}),
       "It is peeling from all around the formerly magnificent entrance.\n");
   add_item(({"hole", "wall"}),
         "The hole in the wall has a thin rope protruding from it.\n");
   add_item(({"rope", "thin rope"}), "The rope looks very pullable.\n");

   add_cmd_item(({"rope", "thin rope"}), "pull", "@@pull_rope");

   /* This is what is needed for the west door. */
   door = clone_object(TOWNDIR + "mansion/ruin_door1");
   door->move(this_object());
   door->set_key(89890);

    add_exit("/d/Terel/calathin/paths/path_e07","west",0);
}

public void
dong(object who)
{
    int w,m;

    tell_room(this_object(),
                "You hear a loud bell echoing deep within the mansion.\n");
    tell_room(ENTRANCE,
                "You hear a loud bell echo throughout the mansion.\n");
    tell_room(FOOD_ROOM,
                "*Ding Dong*  Someone is ringing the front door bell.\n");

    if (((who->query_prop(OBJ_I_WEIGHT) * 100) /
          who->query_prop(CONT_I_MAX_WEIGHT)) > VERY_HEAVY)
    {
        if (SECURITY->query_wiz_level(who->query_real_name()))
        {
            who->catch_msg("A trap door opens up under your weight!\n" +
                           "Your wizard powers stop you from falling in.\n");
            return;
        }
        if (!who->move_living("M", TORTURE))
        {
          who->catch_msg("A trap door opens up under your weight!\n" +
                         "You go plumetting down...down...down, " +
                         "then suddenly land with a crash!\n");
          tell_room(this_object(), QCTNAME(who) +
            " suddenly disappears into a hole in the ground.\n");
          tell_room(TORTURE, QCTNAME(who) +
            " suddenly crashes onto the floor from no-where!\n", who);
        }
     }
}

public string
pull_rope()
{
    string race;
    race = TP->query_race_name();

    if ((race == "dwarf") || (race == "gnome") || (race == "hobbit"))
    {
        if (SECURITY->query_wiz_level(TP->query_real_name()))
        {
            say(QCTNAME(TP) +
                   " floats up to the rope and gives it a strong tug.\n");
            set_alarm(2.0, 0.0, &dong(TP));
            return "Being a bit short to reach the rope, you use your " +
                   "wizard powers to float up and give it a strong tug.\n";
        }
        say(QCTNAME(TP) + " attempts to pull the rope - but can't reach!\n");
        return "You can't reach the rope to pull it!\n";
    }
    say(QCTNAME(TP) + " grabs the rope and gives it a strong tug.\n");
    set_alarm(2.0, 0.0, &dong(TP));
    return "You give the rope a strong sharp tug.\n";
}
