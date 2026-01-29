/*
 *	/d/Gondor/ithilien/sforest/thicket2.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 6-Feb-1997, Olorin:	Changed inheritance,
 *				general revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

/* how hard is it to find the way through the bushes? */
#define HARD_TO_FIND    50 
/* how hard is it to notice the pigeon? */
#define HARD_TO_NOTICE  40 

void fly_pigeon(object tp);

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("dense thicket");
    set_area("southern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("briar");
    set_extraline(
    "The thicket covers a small hog-back of land here. For the most part " +
    "it is covered with a thick growth of gorse and whortleberry, and low " +
    "tough thorns. To the southeast, a small clearing opens, a scar of a recent fire. " +
    "The top of the hog-back lies to the west, where the gorse-bushes and " +
    "the briars become more frequent. In the midst of the bushes to the west, " +
    "two giant oaks are rising.");

    set_up_herbs( ({ HERB_DIR + "athelas", HERB_DIR + "ginger", 
		     HERB_DIR + "mint",    HERB_DIR + "red_pepper", 
		     HERB_DIR + "tarragon", }), 
		  ({ "forest","ground","field","flowers","forest"}), 3);

    add_item(({"hog-back","back","top"}), BSN(
    "For the most part, the hog-back is covered with a thick growth of gorse " +
    "and whortleberry, and low tough thorns. The top lies west of here. "));
    add_item(({"thicket","whortleberry","bush","bushes"}), BSN(
    "The gorse-bushes and briars become more frequent to the west, where " +
    "the top of the hog-back of land lies. There the bushes are very old and " +
    "gaunt and leggy below but thick above, and putting out yellow flowers " +
    "that give a faint scent. Through the thorns and whortleberry all around " +
    "you only a single gap, leading southeast, can be seen. "));

    add_item(({"forest","tree","trees"}), BSN(
    "The are only a few trees here, growing in small groups, with wide glades " +
    "filled by dense bushes between them. But to the west, on the top of the hog-back, " +
    "there are two giant oaks standing, rising far into the sky with their crowns. "));
    add_item(({"oak","oaks","oak tree","oak trees"}), BS(
    "In the thicket west of you, there are two giant oaks. The lower parts of the trunks " +
    "are hidden by the gorse-bushes and briars. \n"));
    add_item(({"gorse","gorse-bushes","briar","briars"}),
    "@@exa_bushes");

    add_exit(ITH_DIR + "sforest/thicket1","southeast", 0, 1);
    add_exit(ITH_DIR + "sforest/thicket3","west","@@enter_bushes",1, 2);
}

public string
exa_bushes()
{
  string bush_desc;
  int aware_skill, track_skill, luck;

  aware_skill = TP->query_skill(SS_AWARENESS);
  track_skill = TP->query_skill(SS_TRACKING);
  luck = (100 - (1 + random(9)) * (1 + random (9))) * HARD_TO_FIND / 100;

  bush_desc = "The gorse-bushes and briars grow much taller than you are, " +
    "very old, gaunt and leggy, but thick above, putting out flowers " +
    "that give a faint sweet scent. They block the view west, and the " +
    "intertwining branches and boughs seem prevent your passage completely. ";

  if(aware_skill + track_skill > luck || TP->query_prop("_ithilien_found_entry_in_thicket"))
  {
    bush_desc +=
      "But skilled as you are, you notice a small opening where " +
      "you might manage to walk under the spiny thicket. ";
    TP->add_prop("_ithilien_found_entry_in_thicket",1);
  }

  bush_desc = BS(bush_desc + "\n");

  return bush_desc;
}

public int
enter_bushes()
{
  int aware_skill, track_skill, luck;

  aware_skill = TP->query_skill(SS_AWARENESS);
  track_skill = TP->query_skill(SS_TRACKING);
  luck = (100 - (1 + random(9)) * (1 + random (9))) * HARD_TO_FIND / 100;

  if(aware_skill + track_skill > luck || TP->query_prop("_ithilien_found_entry_in_thicket"))
  {
    write("With your skills you manage to find a small opening in the bushes. \n");
    TP->add_prop("_ithilien_found_entry_in_thicket",1);
    return 0;
  }

  write("You try to find a way through the bushes to the west, but you fail.\n");
  return 1;
}

public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

  if (interactive(ob) && (TP->query_skill(SS_AWARENESS) > HARD_TO_NOTICE + random(100-HARD_TO_NOTICE)))
      set_alarm(15.0, 0.0, &fly_pigeon(TP));
}

void
fly_pigeon(object tp)
{
  if(environment(tp) == this_object())
  {
    tp->catch_msg(BS("Suddenly, you notice a pigeon flying from the top of one of the two " +
      "giant oaks standing to the west. \n"));
  }
}
