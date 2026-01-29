// Ziggurat Garden (room3.c)
// creator(s):   Zielia 2006
// last update:  Lilith, 2021: added poppies, they were missing
//                 from the garden.
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"

inherit ZIG_GARDEN;

public void
zig_room(void)
{
    /* Avtime events. */
    AVTIME->add_event(this_object());
    season = AVTIME->get_avenir_week();

    set_long("A webcloth hammock is strung between two silver linden trees in "+
      "the center of this clearing. A gentle breeze carries the melodious notes "+
      "of windchimes suspended in the tree branches and stirs beds of poppies, "+
	  "lavender blossoms, and bluebells which border soft, well clipped grass. "+
      "The white flagstone path wanders west of the trees, approaching the "+
      "aquaduct railing before weaving back between the bushes to the north "+
	  "and south.\n");

    add_exit("room4", "north", "@@exit_string");
    add_exit("room2", "south", "@@exit_string");
}

public string query_trees(void) {   return "linden tree";    }

static void
garden_items(void)
{
    ::garden_items();

    add_views("From this side of the "+
      "Ziggurat you can see some of the High Lord Inquisitor's enclave "+
      "to the northwest, opulent noble houses circle the High Lord's "+
      "palace on the central hill.", "enclave, giving it");

    add_rock("the picture of a flute with the lines carved into the "+
      "stone and filled with silver", ", the symbol of Bucaphi");

    add_item(({"tree","trees","linden tree","linden trees", "silver tree",
	"silver trees","silver linden tree","silver linden trees"}),
      "@@see_tree");

    add_item(({"tree branch","tree branches","branch","branches"}),
      "The sturdy tree branches radiate out from the trunks in interesting "+
      "patterns as the light filters through, creating a "+
      "restful canopy for the hammock. Several windchimes hang from the "+
      "branches.\n");

    add_item(({"windchime","windchimes","wind chime","wind chimes",
	"chime", "chimes"}),
      "Several windchimes hang from the branches of the linden trees. "+
      "They are made of hollow silver tubes of different lengths strung "+
      "from a round platform of ebony. A wooden disk hangs at the center "+
      "of the ring of tubes and an engraved wooden clapper hangs from that. "+
      "The clapper catches the strange breeze which blows through this "+
      "arbor and sends the disk swinging against the silver tubes. The "+
      "tubes resonate with clear, pure notes, interpreting the music of "+
      "nature.\n");

    add_item(({"clapper","wooden clapper","engraved wooden clapper",
	"engraved clapper","clappers","engraving"}),
      "@@see_clapper");

    add_item(({"nut","seed","nuts","seeds",}), "@@see_fruit");

    add_item(({"linden flower","linden blossom","linden flowers",
	"linden blossoms",}), "@@see_lindenflower");

    add_object(ZIG_RLG + "hammock_r3", 1, 0 );
}

static void
garden_tells(void)
{
    ::garden_tells();

    add_tell(({"The windchimes play the breeze, making playful, soothing music.",
	"The windchimes echo tranquilly as they are stirred by the breeze.",
	"A soft breeze caresses the windchimes into melancholy song.",
	"Metal chimes in the branches the resonate hauntingly beautiful "+
	"and hypnotic tones of the breeze.",}));

}

public void
ring_chime(void)
{
    switch(random(4))
    {
    case 0:
	tell_room(TO, "The windchimes play the breeze, making playful, "+
	  "soothing music.\n", 0, TO);
	break;
    case 1:
	tell_room(TO, "The windchimes echo tranquilly as they are stirred by "+
	  "the breeze.\n", 0, TO);
	break;
    case 2:
	tell_room(TO, "A soft breeze caresses the windchimes into melancholy "+
	  "song.\n", 0, TO);
	break;
    case 3:
	tell_room(TO, "Metal chimes in the branches resonate the hauntingly "+
	  "beautiful and hypnotic tones of the breeze.\n", 0, TO);
	break;
    }
}

public string
see_clapper(void)
{
    set_alarm(2.0, 0.0, &ring_chime());

    return "You focus your attention on the engraved wooden clapper of the "+
    "closest windchime. Like all the clappers, it is engraved with the "+
    "image of a flute. As you study the clapper, you notice the flute "+
    "glow brightly for a moment and immediately a gentle breeze begins "+
    "to swirl around the linden trees.\n";
}

static void
garden_flowers(void)
{
    add_flower("lavender");
    add_flower("bluebell");
    add_flower("poppy", ({ "red", "orange"}));
    ::garden_flowers();
}

public string
see_lindenflower(void)
{
    string str;

    switch(season)
    {
    case 5..10: /* Tree flowers*/
	str = "The fragrant flowers of the Linden tree hang from the middle "+
	"of leafy, ribbon-like green bracts in long-stalked clusters. "+
	"The flowers are tiny, with 5 yellowish-white petals.\n";
	break;
    default: /* No flowers. */
	str = "The tree is currently blossomless.";
	break;
    }

    return str;
}

public string
see_fruit(void)
{
    string str;

    switch(season)
    {
    case 8..10: /* Autumn. */
	str = "The linden trees have many small nutlets about the size of a "+
	"pea. They are clustered beneath large leafy wing bracts which "+
	"act as parachutes as they carry the seeds to the ground.";
	break;
    default: /* Tree is dead. */
	str = "The tree is not seeding right now.";
	break;
    }

    return str + "\n";
}

public string
see_tree(void)
{
    string str;

    switch(season)
    {
    case 2..4: /* Tree regrows. */
	str = "They have nice, rounded growth and fresh green "+
	"heart-shaped leaves with glistening bright undersides.";
	break;
    case 5..7: /* Tree flowers/grows young fruit. */
	str = "They have nice, rounded growth reminiscent of lollipops and "+
	"masses of silver-green, wide, heart-shaped, tooth-edged leaves."+
	"and tiny, yellow flowers.";
	break;
    case 8..10: /* Autumn. */
	str = "They have nice, rounded growth reminiscent of lollipops and "+
	"masses of wide, heart-shaped, tooth-edged leaves that have "+
	"turned a pretty yellow. Tiny nut-like seeds cling to the branches.";
	break;
    default: /* Tree is dead. */
	str = "The branches are presently bare, focusing attention on their "+
	"bark, which is grey and deeply furrowed sometimes looking like "+
	"wrinkled faces peering out at you.";
	break;
    }

    return "Two tall silver linden trees stand in this arbor. "+ str +"\n";

}
