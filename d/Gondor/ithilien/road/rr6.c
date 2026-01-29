inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MIN_AWARE  40         /* minimum awareness to notice something in the bushes */
#define MIN_TRACK  30         /* minimum tracking to find the tracks on the path */

public int      pass_hedge(string str);

public void
create_area_room()
{
    set_areatype(0);
    set_areadesc("a path on the east bank of the Anduin");
    set_area("western");
    set_areaname("North Ithilien");
    set_land("Ithilien");
    set_extraline("The path runs north and south through fields between the "
      + "river and the green forests of North Ithilien, close to a long row "
      + "of thorny hedges. A pleasant smell of flowers and plants is ever "
      + "present as you walk along. In places where the hedge is slightly "
      + "lower, you can see forests covering most of the sloping hillsides "
      + "and ridges in the lands that rise towards dark mountains on the "
      + "east horizon. To the west the mighty River Anduin flows quietly past "
      + "from the north towards the south.");
    add_item(({"anduin", "river", "river anduin", }), BSN(
        "The great river Anduin flows calmly past to the west, on its way "
      + "south to its mouths at the Bay of Belfalas. The river is "
      + "broad, but you can see green fields beyond it. In the middle of the "
      + "river further north, is an islet, and there is a stone fortress on "
      + "the south end of the islet."));
    add_item("path","@@path");
    add_item("forest",BS(
    "The forests of Ithilien are lovely to look upon; a refreshing "+
    "smell of green herbs and fair flowers is brought by the wind. "+
    "\n"));
    add_item(({"field","fields","pastures"}), BS(
    "The path runs through green fields on the east bank of the Anduin. To the east, " +
    "here a long row of hedges prevents progress and view into that direction. " +
    "Further along the path, small groups of trees can be seen in the fields, until " +
    "in some distance to the east, the forests of " + 
    "northern Ithilien begin. The fields must be very fertile, and there are still some " +
    "traces of cultivation, but evidently these fields have not seen the scythe or the plough " +
    "of a farmer for decades.\n"));
    add_item("bank","The riverbank is just a couple of meters above the river surface,\n"+
    "sloping gently down to the river, the last few feet barren sand only.\n");
    add_item("mountains","You catch a glimpse of dark peaks in the misty distance beyond the\n"+
    "forests of Ithilien. The peaks of the Ephel Duath, and Mordor.\n");
    add_item(({"hedge","hedges","row","bush","bushes"}), "@@hedge");
    add_item(({"thorns"}),BS(
    "The thorns of the hedge are rather long and sharp. You guess they must be " +
    "extremely effective in preventing man and beast from walking through that hedge.\n"));
    add_item(({"gap","twigs"}), "@@gap");
    add_exit(ITH_DIR + "road/rr7", "north", 0, 4);
    add_exit(ITH_DIR + "road/rr5", "south", 0, 4);

    reset_room();
}

public void
init()
{
    ::init();
    add_action(pass_hedge, "enter");
    add_action(pass_hedge, "pass");
}

public string
hedge()
{
    string desc =
        "A long row of hedges is growing close to the path. Perhaps long ago " +
        "they were planted as an enclosure for a meadow, but have long since " +
        "grown wild and in part overhang the path. The long and sharp " +
        "thorns prevent your progress to the east. ";
    int p_aware = TP->query_skill(SS_AWARENESS);

    if ((p_aware > (MIN_AWARE / 2 + random(MIN_AWARE) + 1)) || IS_RANGER(TP))
    {
	desc += "But there seems to be a small gap where the hedge is " +
	    "thinner. You notice even a few broken twigs.";
	TP->add_prop("_noticed_gap_in_hedge_on_riverroad",1);
    }

    return BS(desc + "\n");
}

public string
path()
{
  string desc;
  int p_track = TP->query_skill(SS_TRACKING);
  
  desc = "The path runs north and south here along the river and the "+
    "forest. It doesn't look as if it used very often. ";
  desc += "To the east side of the path a long row of thorny hedges is growing. ";

  if(p_track > MIN_TRACK || IS_RANGER(TP))
  {
    desc += "Curiously, you notice some tracks on the path that do not follow it, " +
      "but enter from the south and seem to disappear through a small gap in the hedges. ";
    TP->add_prop("_noticed_gap_in_hedge_on_riverroad",1);
  }

  return BS(desc + "\n");
}

public string
gap()
{
  if(!TP->query_prop("_noticed_gap_in_hedge_on_riverroad") && !IS_RANGER(TP))
    return "You find no gap.\n";
  return BS("Although the hedge looks impenetrable at first glance, there is a " +
    "small gap where the twigs and boughs of the hedge, that are tightly interwoven " +
    "elsewhere, are thinner and allow passage through the hedge.\n");
}

public int
ranger_test(object player)
{
  return (player->test_bit("Gondor",1,18) || player->test_bit("Gondor",1,19));
}

public int
pass_hedge(string str)
{
  int damage;

  if(!TP->query_prop("_noticed_gap_in_hedge_on_riverroad") && !IS_RANGER(TP))
  {
    if((str == "hedge" || str == "bush" || str == "bushes") && query_verb() == "enter")
    {
      write("Heedless of the long and sharp thorns you walk into the dense hedge.\n");
      say("Heedless of the long and sharp thorns " + QTNAME(TP) + " walks into the dense hedge.\n");
      damage = TP->query_max_hp() / 10;
      if(damage > 100) damage = 100;
      TP->heal_hp(-damage);
      write("The thorns pierce you clothing and armour. They are incredibly tough and sharp.\n");
      write("They stab you into the face, into your arms and legs. You are hurt.\n");
      say("Small wonder, " + TP->query_pronoun() + " is pierced by the thorns and hurt.\n");
      write("But, of course, you don't manage to pass through the hedge.\n");
      say("Of course, " + TP->query_pronoun() + " doesn't manage to pass through the hedge.\n");
      return 1;
    }
    return 0;
  }

  NF(CAP(query_verb()) + " what?\n");
  if(!str) return 0;

  if(str == "hedge" || str == "gap" || str == "through hedge" || str == "through gap" 
                    || str == "bush" || str == "bushes") 
  {
    write("Carefully evading the thorns, you walk through the small gap in the hedge.\n");
    say(QCTNAME(TP) + " enters the dense row of hedges east of the road.\n");
    TP->move_living("M",ITH_DIR + "nforest/fpath/fpath9",1);
    tell_room(ENV(TP),QCNAME(TP) + " arrives through the dense hedges to the west.\n",TP);
    return 1;
  }
  return 0;
}

public string
short_desc()
{
    return CAP(areadesc) + " in the " + area + " parts of " + areaname;
}
