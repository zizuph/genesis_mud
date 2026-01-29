/*
 *	/d/Gondor/anorien/nimrais/quest/base.c
 *
 *	Coded by Olorin
 *
 *	Modification log:
 *	 7-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "dirdefs.h"
 
public void
create_area_room()
{
    set_areatype(2);
    set_areadesc("hillside");
    set_grass("thick ");
    set_area("central");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_extraline("The valley comes from the northwest, makes a bend and " +
    "continues to the southwest. The slopes on both sides are rather steep. To the " +
    "east and south the slopes are the foot of a mighty mountain " +
    "and are crowned by mighty rock walls " +
    "rising into the sky for several hundred feet. High on the rock wall to the south, you can " +
    "see a projecting rock. You might try to climb the slope to the south. " +
    "A small stream is running northwest in the middle of the valley.");
  add_item(({ "slope", "mountain slope" }), BS("The higher it goes, the "  +
    "steeper it is, until it goes over into an almost vertical rock wall " +
    "rising for several hundred feet into the sky.\n"));
  add_item(({ "rock", "projecting rock" }), BS("It is a big rock. It is "
    + "rather high on the almost vertical rock wall to the " +
    "south. From here you cannot make out if you can climb that wall, " +
    "You would have to climb the slope leading up to it first, " +
    "but without any doubt only an experienced climber would have any chance at all.\n"));
  add_item(({"mountain","rock wall"}), BS(
    "This side of the impressive mountain to the south is an almost vertical " +
    "rock wall, a cliff rising into the sky for several hundred feet. " +
    "High on that cliff, you can see a prominent projecting rock. From " +
    "where you are in the middle of the valley, you cannot make out if " +
    "it is possible to scale the rock wall, you would have to climb the " +
    "steep slope leading up to it first, but without doubt only an " +
    "experienced climber has any chance at all to achieve this feat.\n"));
  add_item(({"stream","water"}),BS(
    "A small stream is running northwest in the middle of the valley. " +
    "The water is quite clean and probably rather cold.\n"));
  add_exit(ANO_DIR + "nimrais/rimvalley5", "northwest", 0, 2);
  add_exit(ANO_DIR + "nimrais/rimvalley6", "southwest", 0, 2);
  add_prop(OBJ_I_CONTAIN_WATER, 1000000);

    set_up_herbs( ({ ONE_OF_LIST(HERB_MASTER->query_herbs("middle earth")),
                     ONE_OF_LIST(HERB_MASTER->query_herbs("moderate")),
                     ONE_OF_LIST(HERB_MASTER->query_herbs("hills")), }),
                  ({ "hill", "hillsides", "slope", "slopes", }), 3);
}
 
public int
climb_up()
{
    int     skill = TP->query_skill(SS_CLIMB),
            rnd;

    if (skill < 10)
    {
        write("You aren't very skilled in climbing, so you dare not try it.\n");
        return 1;
    }
    skill += random(20);
    if (skill  > 20)
    {
        write("You skillfully climb up the slope.\n");
        say(QCTNAME(TP) + " climbs up the slope.\n", TP);
        TP->move_living("M", THIS_DIR + "wall1", 1);
        say(QCTNAME(TP) + " climbs up the slope.\n", TP);
        return 1;
    }
    write("You try to climb up, but you lose your grip!\n\n" +
      "You fall to the ground.\n");
    say(QCTNAME(TP) + " tries to climb up the slope, but " +
      TP->query_pronoun() + " loses " + TP->query_possessive()
      + " grip and falls to the ground.\n");
    TP->heal_hp(-random(20) - 20);
    return 1;
}
 
public int
climb(string str)
{
    NF("Climb what?\n");
    if(str == "mountain")
    {
      write("You cannot climb the mountain wall from here. Try to climb the slope first.\n");
      return 1;
    }
    else if(str == "rock")
    {
      write(BS("The projecting rock is high on the mountain. To reach it you have to climb " +
      "the slope first. Once you managed that you will have to climb the rock wall, if that is possible at all.\n"));
      return 1;
    }
    if (str == "up" || str == "slope")
        return climb_up();
    return 0;
}

public void
do_fall(object player = TP, int height = 0)
{
    int     acrobat = player->query_skill(SS_ACROBAT),
            dex = player->query_stat(SS_DEX),
            hurt,
            max_hurt;
    object  egg;

    if (acrobat > 25)
        acrobat = 25;
    if (dex > 100)
        dex = 100;

    hurt = height * height * 20 - acrobat * 2 - dex / 2;
    max_hurt = height * height * 10;

    if (hurt < max_hurt)
        hurt = max_hurt;
    hurt = hurt * 3 + random(hurt * 4);
    write("You crash to the ground.\n");
    say(QCTNAME(player) + " falls down from the mountain slope.\n");
    if (objectp(egg = present("egg", player)))
    {
        write("The "+egg->query_short()+" shatters.\n");
        egg->remove_object();
    }
    player->heal_hp(-hurt);
    if (player->query_hp() <= 0)
    {
        player->do_die(TO);
        write_file(LOG_DIR + "climb", player->query_name()
          + " died climbing in the White Mountains at the base. "
          + "Avg_stat = " + player->query_average_stat() + ", climbing = "
          + player->query_skill(SS_CLIMB) + ", " + ctime(time())+".\n");
    }
    return;
}

public void
init()
{
    ::init();
    add_action(climb, "climb");
}
 
