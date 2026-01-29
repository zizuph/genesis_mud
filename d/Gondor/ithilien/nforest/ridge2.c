/*
 *      /d/Gondor/ithilien/nforest/ridge2.c
 *
 *      Coded 1993 by Olorin.
 *
 *      Modification log:
 *      31-Jan-1997, Olorin: Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

/* how hard is it to find the way through the bushes? */
#define HARD_TO_FIND	50  
/* how hard is it to notice the pigeon? */
#define HARD_TO_NOTICE	40 
#define ITHILIEN_FOUND_ENTRY_ON_RIDGE	"_ithilien_found_entry_on_ridge"

public int     enter_bushes();
public string  exa_bushes();

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("stony ridge");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar and cypress");
    set_extraline( 
        "The ridge is completely overgrown by a thicket of bushes, " +
        "which are blocking the view in all directions. To the west " +
        "there are a few trees in the midst of the thicket. The only " +
        "obvious exit from the bushes is to the south.");
    add_item( ({ "ridge", }), BSN(
        "The ridge comes running down from the slopes of the Ephel Duath. " +
        "East of here, a road cleaves its way through the ridge. The bank " +
        "falling down to the road is very steep and covered with dense bushes " +
        "so that you cannot see the road from here. The thicket surrounds you " +
        "in all directions, so that the path to the north and the west seems " +
        "to be blocked, too."));
    add_item( ({ "bush", "bushes", "thicket"}), exa_bushes);
    add_item( ({ "forest", "tree", "trees", }), BSN(
        "There are hardly any trees on the ridge. Thick bushes are dominating. " +
        "Only to the west there are a few cypress trees and two large " + 
        "cedars."));
    add_item(({"cypress","cypresses"}), 
        "The tops of a few cypress trees can be seen above the bushes to the west.\n");
    add_item( ({ "cedar", "cedars", "cedar tree", "cedar trees", }), BSN(
        "In the thicket west of you, there are two giant cedars. The " +
        "lower parts of the trunks are hidden by the bushes."));

    set_up_herbs( ({ HERB_DIR + "athelas", HERB_DIR + "caraway", 
		     HERB_DIR + "ginger",  HERB_DIR + "mint", 
		     HERB_DIR + "tarragon",  }), 
		  ({ "forest", "ground", "field", "flowers", }), 3);

    add_exit(ITH_DIR + "nforest/ridge",  "south", 0, 1, 0);
    add_exit(ITH_DIR + "nforest/ridge3", "west",  enter_bushes, 1, 1);
}

private int
skill_check()
{
    int     aware  = TP->query_skill(SS_AWARENESS),
            track  = TP->query_skill(SS_TRACKING),
            diff   = (HARD_TO_FIND / 2 + random(HARD_TO_FIND) + 1);

    return ((aware + track) > diff);
}

public string
exa_bushes()
{
    string  bush_desc =
	"The bushes are much higher than you are, so they block the view " +
        "in all directions. But when you look closely, you notice that to " +
        "the north and the east the ridge ends in sheer-sided cliffs only " +
        "a few feet from here. To the west, the bushes seem impenetrable.";

    if (skill_check() || TP->query_prop(ITHILIEN_FOUND_ENTRY_ON_RIDGE))
    {
	bush_desc += " But skilled as you are, you notice a small opening there.";
	TP->add_prop(ITHILIEN_FOUND_ENTRY_ON_RIDGE, 1);
    }

    return BSN(bush_desc);
}

public int
enter_bushes()
{
    if (skill_check() || TP->query_prop(ITHILIEN_FOUND_ENTRY_ON_RIDGE))
    {
	write("With your skills you manage to find a small opening in the bushes.\n");
	TP->add_prop(ITHILIEN_FOUND_ENTRY_ON_RIDGE, 1);
	return 0;
    }

    write("You try to find a way through the bushes to the west, but you fail.\n");
    return 1;
}

public void
fly_pigeon(object tp)
{
    if (ENV(tp) != TO)
	return;

    tp->catch_tell("Suddenly, you notice a pigeon flying from the top " +
		   "of one of the two giant cedars standing to the west.\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !interactive(ob))
	return;

    if (ob->query_skill(SS_AWARENESS) > 
	(HARD_TO_NOTICE / 2 + random(HARD_TO_NOTICE)))
	set_alarm(10.0 + 20.0 * rnd(), 0.0, &fly_pigeon(ob));
}
