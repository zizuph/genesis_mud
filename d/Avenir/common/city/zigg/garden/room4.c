// Ziggurat Garden (room4.c)
// creator(s):   Zielia + Lucius 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"
#include <macros.h>

inherit ZIG_GARDEN;

private static int bat, hour;
private static mapping m_spots = ([]);

public void
zig_room(void)
{
    /* Avtime events. */
    AVTIME->add_event(this_object());
    hour = AVTIME->get_avenir_hour();

    if (hour < 6)   {   bat = 1;    }

    set_long("Thick blackberry bushes and tall hollyhock plants enclose this "+
      "section of the terrace, screening the rest of the garden from view "+
      "with stalks of stunning black trumpet-shaped flowers that stand taller "+
      "than a shadow elf. The white flagstone path "+
      one_of_list(({"meanders","snakes","winds"})) +" its way east of a carpet "+
      "of black dream pansies, black violas and silver-edged penny black. "+
      "Perhaps the nightmarish palm tree in the middle of the flowers is "+
      "blocking the Source, but it seems dimmer here somehow, almost as "+
      "though the many black flowers are swallowing the light. Glossy "+
      "purple-black eggplants grow in raised beds set along the Ziggurat "+
      "wall, east of the path, ending just before it enters the "+
      "bushes to the north and south.\n");

    add_exit("room5", "north", "@@exit_string");
    add_exit("room3", "south", "@@exit_string");
}

public string query_trees(void) {   return "palm tree";    }

static void
garden_items(void)
{
    ::garden_items();

    add_ground("The ground of the terrace is made of flat, rich soil "+
      "and covered with a carpet of black flowers.");

    add_views("From this side of the Ziggurat you can see some of the "+
      "High Lord Inquisitor's enclave to the northwest, opulent noble "+
      "houses circle the High Lord's palace on the central hill.",
      "enclave, giving it");

    add_rock("a black mark as though someone had dipped their hand in ink "+
      "and pressed it to the stone", ", a symbol of Thagrinus");

    add_item(({"eggplant","eggplants",}),
      "Tall bushy stems with large, slightly lobed leaves grow in raised "+
      "beds near the Ziggurat wall. Heavy, pear-shaped fruits grow from "+
      "the stems. Their skin is a beautiful glossy purple, so dark it "+
      "appears black.\n");

    add_item(({"cluster","clusters","date","dates","date cluster",
	"date clusters"}),
      "Heavy round clusters of oblong fruits hang beneath the fronds by "+
      "thick stalks. The fruits vary in color some looking dark-brown, "+
      "or reddish or yellowish-brown.\n");

    add_item(({"bushes","bush","blackberry","blackberries","blackberry bush",
	"blackberry bushes", "berry","berries"}),
      "The blackberry bushes are formed of a scrambling habit of dense "+
      "arching stems carrying short, curved, very sharp spines and large "+
      "toothed leaves. The branches root from the node tip when they reach "+
      "the ground forming thick tangled hedgerows all around this section "+
      "of the garden. Many of the bushes have plump, glossy black berries "+
      "formed of clusters of many smaller round berries.\n");

    add_item(({"palm tree","palm trees","palm","palms","tree","trees"}),
      "@@see_palm");

    add_item(({"leaves","fronds"}), "@@see_fronds");

    add_cmd_item(({"date","dates",}), ({"pluck", "pick"}),
      "The dates are high out of reach.\n");

    add_cmd_item(({"eggplant","eggplants",}), ({"pluck", "pick"}),
      "Determining that the eggplants could get bigger if left alone, you "+
      "decide not to pick them afterall.\n");

    add_fruit("blackberry");

    if (bat)
    {
	add_item(({"bat","bats",}), "@@see_bats");
    }

}

static void
garden_flowers(void)
{
    add_flower("hollyhock", "black");
    add_flower("pansy", "black");
    add_flower("viola", "black");
    add_flower("penny black", "black");

    ::garden_flowers();
}

public string
see_palm(void)
{
    string str = "";

    if (hour < 6)
	str = " The fronds seem to rustle slightly as you watch though the "+
	"air of the sybarun cavern is as still as ever.";

    return "At the center of this section stands a palm tree. Something "+
    "about the tree seems unsettling, though what it is you can't discern, "+
    "except to say it has an air of gloom about it. It is shorter than "+
    "most palm trees with longer fronds that look almost too heavy for "+
    "the tree, as though they are struggling not to droop. The trunk is "+
    "clothed from the ground up with upward-pointing, overlapping, woody "+
    "leaf bases making it look uncomfortable to climb. Clusters "+
    "of dates hang beneath the crown."+ str +"\n";
}

public string
see_fronds(void)
{
    string str = "";

    if (bat && (hour < 6))
    {
	str = " Looking closely, you think you notice small grey fruits "+
	"hanging from the dead grey fronds, but after a moment, you "+
	"realize they are tiny bats resting in what must be their roost.";
    }

    return "Enormous feather shaped leaves grow in a spiral pattern at "+
    "the crown of this stocky palm tree. The leaves, or fronds, are "+
    "dark green, but many have died and turned a grey color. They stick "+
    "out in every direction creating a fascinating silhouette against "+
    "the Source."+ str +"\n";
}

private int
bat_fly(int count)
{
    switch(++count)
    {
    case 1:
	tell_room(TO, "Suddenly a black plume like smoke begins to rise from "+
	  "the palm tree.\n", 0, TO);
	remove_item("bat");
	add_item(({"bat","bats",}), "Bats rise in fluttering spirals like "+
	  "a plume of smoke rising up from the palm tree.\n");
	break;
    case 2:
	tell_room(TO, "Silhouetted against the source, the black column "+
	  "rises higher and higher until it is as tall as the Ziggurat.\n",
	  0, TO);
	bat = 0;
	break;
    case 3:
	tell_room(TO, "The column bursts apart into a cloud of hundreds of "+
	  "tiny bats, each bat beating calm, firm wings as they begin diverge "+
	  "and spread out over the terrace.\n", 0, TO);
	remove_item("bat");
	add_item(({"bat","bats",}), "The bats cast a shadow over the garden, "+
	  "their many tiny bodies blocking the Source from your view.\n");
	break;
    case 4:
	tell_room(TO, "For a moment the garden has a roof of "+
	  "bats, flying outward in all directions, all seemingly at the "+
	  "same altitude and in formation before they break apart, flying "+
	  "off to find their dinner.\n", 0, TO);
	break;
    default:
	remove_item("bat");
	count = -1;
	break;
    }
    if (count > 0)
	set_alarm(3.0, 0.0, &bat_fly(count));
}

private int
bat_return(int count)
{
    switch(++count)
    {
    case 4:
	bat = 1;
	add_item(({"bat","bats",}), "@@see_bats");
	break;
    case 7:
	count = -1;
	break;
    default:
	tell_room(TO, one_of_list(({"Two","Three","Four"})) +" tiny bats "+
	  "arrive on flapping wings and disappear into the dark fronds "+
	  "of the palm tree, ready to seek their torpor.\n", 0, TO);
	break;
    }

    if (count > 0)
	set_alarm(itof(10 + random(25)), 0.0, &bat_return(count));
}

public string
see_bats(void)
{
    if (hour == 5)
    {
	return "Many tiny bats are hidden in the palm tree's dead fronds. "+
	"The color of the bats' fur exactly matches the faded, dry "+
	"grey of the dead palm fronds to which they cling with their "+
	"sharp hind claws. They yawn and chatter to one another, "+
	"stretching their thin, leathery wings. Soon they will head "+
	"out to the black sea for a quick drink, then soar off over "+
	"the islands in pursuit of insects.\n";
    }
    else
    {
	return "Many tiny bats sleep hidden in the palm tree's dead fronds "+
	"The color of the bats' fur exactly matches the faded, dry grey "+
	"of the dead palm fronds to which they cling with their sharp "+
	"hind claws. The bats sleep upside down, clinging to a branch "+
	"with their feet, their wings wrapped around them so that it's "+
	"dark inside.\n";
    }
}

private void
f_spot(object tp)
{
    int cspot = 0;

    if (objectp(tp) && !present(tp, TO))
	return;

    if (m_spots[tp])
    {
	m_spots[TP][1] = 0;
	cspot = m_spots[tp][0];
    }

    switch(cspot)
    {
    case 0:
    case 1:
	add_item(({"spot","spot","black spot","black spots",}),"@@see_spot");
	tell_room(TO, "You notice a strange black spot out of the corner of "+
	  "your eye.\n", 0, TO);
	break;
    case 2:
	tell_object(tp, "You sense the black spot again, hovering at "+
	  "the edge of your vision.\n");
	break;
    case 3:
	tell_object(tp, "The spot seems bigger as it returns again, a "+
	  "dark haze blocking out your peripheral vision on the right.\n");
	break;
    case 4:
	tell_object(tp, "The black spot moves around in circles at the "+
	  "edge of sight, distracting you tauntingly.\n");
	break;
    default:
	tell_object(tp, "The black spot returns once more and circles "+
	  "around again, then slowly fades from view.\n");
	break;
    }

    if (cspot++)
	m_spots[tp][0] = cspot;
}

public string
see_spot(void)
{
    object tp = TP;

    if (!m_spots[TP])
	m_spots[TP] = ({ 2, 0 });

    if (m_spots[TP][1] || (m_spots[TP][0] > 5))
	return "You find no spot.\n";

    write("You turn toward the spot but cannot find it. You look all "+
      "around but it has disappeared.\n");

    say(QCTNAME(TP)+ " seems confused as "+ HE(TP) +" looks around for "+
      "something but fails to find it.\n");

    m_spots[TP][1] = set_alarm(itof(5 + random(40)), 0.0, &f_spot(tp));
    return "";
}

public int
avenir_event(int av_year, int av_week, int av_day, int av_hour)
{
    ::avenir_event(av_year, av_week, av_day, av_hour);

    hour = av_hour;

    if (hour == 5)
    {
	set_alarm(30.0, 0.0, &f_spot());
    }
    else if (hour == 6)
    {
	m_spots = ([]);
	remove_item("spot");
	set_alarm(30.0, 0.0, &bat_fly(0));
    }
    else if (hour == 1)
    {
	set_alarm(10.0, 0.0, &bat_return(0));
    }

    return 1;
}
