/*
 *  file name:   base.c
 *  creator:     Lucius & Zielia
 *  last update:
 *  purpose:    Standard inherit for ziggurat rooms.
 *  note(s):
 *  bug(s):
 *  to-do:
 */
#pragma no_clone
#pragma strict_types

#include "zigg.h"

inherit ZIG_ROOM;

#include <macros.h>
#include <composite.h>
#include <stdproperties.h>

static void kesoit_tells(void);

private static int season;

public void
zig_room(void)
{
    /*
     * Individual room code goes here.
     */
}

static nomask void
create_room(void)
{
    ::create_room();

    /* Avtime events. */
    AVTIME->add_event(this_object());
    season = AVTIME->get_avenir_week();

    add_zigg();

    /* Upper Court specific items. */

    add_cmd_item(({"fruit","kesoit fruit","pale fruit","red fruit",}),
      "pick", "@@pick_fruit");

    add_item(({"sphere","mirrored sphere","obtrusion","convex sphere"}),
      "@@see_sphere");

    add_item(({"balcony","rail","black rail","overlook","railing"}),
      "In the middle of this galleria is a cordoned off area "+
      "that overlooks the kesoit tree growing up from the level below. "+
      "Metallic rails and supports coated with a black, non-reflective "+
      "material run in a square about the overlook and hold in place "+
      "sheets of metal intricately cut with designs of intimately entwined "+
      "figures and rollicking dancers.\n");

    add_item(({"plaza","view",}),
      "Far below, past the radiating branches of the kesoit tree, people "+
      "mill about an indoor plaza while dancing women in their colorful "+
      "garb dance enticingly, their bodies below moving and twirling like "+
      "bits of colored glass in a kaleidoscope.\n");


    add_item(({"fence","fencing","cordoning","sheets","metal sheets"}),
      "@@see_fence");

    add_item(({"walls","wall","stone","stones","black stone","black stones"}),
      "@@see_walls");

    add_item(({"torch","torches","torch stand","torch stands",}),
      "@@see_torches");

    add_item(({"octagon","octagons","ivory","ivory pieces",}),
      "@@see_octagons");

    add_item(({"shadow","shadows","sillhouette","sillouettes","figure",
	"figures",}),"@@see_shadows");

    add_item(({"floor", "ground"}),
      "Footsteps echo dully as shoppers move about. Like the walls, "+
      "the floor is comprised of naturally black stone that has been "+
      "worked smooth.\n");

    add_item(({"ceiling",}),
      "Like the walls and floor, the high ceiling is comprised of a "+
      "naturally black stone making it difficult to distinguish from the "+
      "shadows beyond the reach of the light. In the centre of the ceiling; "+
      "however, a mirrored, convex half-sphere can be seen.\n");

    add_item(({"tree","kesoit tree","branches","branch","limb","limbs"}),
      "@@see_branches");

    add_item(({"leaf","leaves","kesoit leaves","orange leaves","veins",
	"rubbery leaves",}),"@@see_leaves");

    add_item(({"flower","flowers","kesoit flowers","blossoms","buds",
	"flower buds","petals"}),"@@see_flowers");

    add_item(({"fruit","fruits","kesoit fruit","pale fruit","spines",
	"red fruit","kesoit fruits"}),"@@see_fruit");

    add_item(({"lantern", "lanterns"}), "@@see_lanterns");

    /* Special item for looking over below */
    add_item(({"below","down"}), "@@see_overlook");

    /* Various bits for the tree. */
    kesoit_tells();
}

static string
view_overlook(void)
{
    /* Just a dummy description until we have a lower level. */
    return "Looking over the black coated railing you see "+
    "more of the plaza below from where the kesoit tree "+
    "grows. You can see various people milling about "+
    "but cannot make out specifics.\n";
}

public string
see_tree(void)
{
    string str;

    switch(season)
    {
    case 2..4: /* Tree regrows. */
	str = "freshly budding kesoit tree shining with renewed health";
	break;
    case 5..7: /* Tree flowers/grows young fruit. */
	str = "kesoit tree, its flowered branches";
	break;
    case 8..10: /* Fruit ripens, tree in flames. */
	str = "kesoit tree with its halo of fire";
	break;
    default: /* Tree is dead. */
	str = "kesoit tree, its blackened branches bare";
	break;
    }

    return str + " growing up from beyond it";
}

/*
 * Common things amongst all galleria rooms.
 */
static void
kesoit_tells(void)
{
    clear_tells();

    switch(season)
    {
    case 2..4:
	add_tell(({
	  "The light from the lanterns throbs in intensity, almost like a "+
	  "heartbeat.",
	}));
    case 5..7:
	add_tell(({
	  "The light from the lanterns throbs in intensity, almost like a "+
	  "heartbeat.",
	  "The light from the lanterns slowly rises, shining through the "+
	  "orange leaves of the kesoit tree making it look as though it "+
	  "were ablaze for a moment.",
	}));
	break;
    case 8..10:
	add_tell(({
	  "A cindery burst of flame rises from the kesoit tree, "+
	  "filling the galleria with dazzling light.",
	  "Shadows lengthen throughout the gallery as the kesoit "+
	  "flames subside.",
	  "Shadowy silhouettes with golden auras dance and writhe "+
	  "across the walls.",
	  "Golden-red flames flicker behind the artfully cut metal "+
	  "sheets beneath the railing.",
	  "The warm, spicy scent of kesoit fills the air.",
	}));
	break;
    default:
	add_tell(({
	  "The light from the lanterns throbs in intensity, almost like a "+
	  "heartbeat.",
	  "The light from the lanterns slowly rises, haloing the tree "+
	  "branches in a misty white nimbus for a brief moment."
	}));
	break;
    }
}

public string
see_sphere(void)
{
    string str;

    switch(season)
    {
    case 8..10: /* Tree on fire. */
	str = "the flaming kesoit tree below.\n";
	break;
    default: /* Tree not on fire. */
	str = "the glowing orbs hanging from kesoit tree below.\n";
	break;
    }

    return "In the centre of the ceiling a convex half-sphere obtrudes. "+
    "Its surface is covered with silvery plates that serve to "+
    "reflect the light given off by "+ str;
}

public string
see_fence(void)
{
    string str;

    switch(season)
    {
    case 8..10: /* Tree on fire. */
	str = "the gold and orange flames leaping up from the kesoit tree below.\n";
	break;
    default: /* Tree not on fire. */
	str ="the pale, pulsing light of the source lanterns "+
	"tied to the kesoit tree branches below.\n";
	break;
    }

    return "Metal sheets with intricately cut designs form a fence "+
    "cordoning off the drop to the plaza below. The sheets are "+
    "coated with the same non-reflective material as the railing "+
    "creating black silhouettes of intimately entwined figures "+
    "and rollicking dancers against "+ str;
}

public string
see_shadows(void)
{
    switch(season)
    {
    case 8..10: /* Tree on fire. */
	return "Shadowy silhouettes cast by the kesoit flames shining through "+
	"the fence seem to have their own life as they writhe and dance in "+
	"unison with the flickering fire. Shadowy bodies entwine in ecstatic "+
	"patterns, reminding visitors that the Ziggurat is host to all manner "+
	"of pleasures.\n";
	break;
    default: /* Tree not on fire. */
	return "Shadows hovering beyond the reach of the lanterns and torches "+
	"make it difficult to make out the far corners of the galleria.\n";
	break;
    }
}

public string
see_walls(void)
{
    switch(season)
    {
    case 8..10: /* Tree on fire. */
	return "Shadowy figures dance and writhe along walls made of a "+
	"naturally black stone. The stone has been highly polished to give "+
	"it a glossy shine which helps to distribute the light cast by "+
	"the leaping flames of the kesoit tree below. About every "+
	"ten paces, a large octagon is carved into the wall and inlaid "+
	"with pieces of ivory. Occasionally, between the octagons, a "+
	"doorway opens to one of the many galleria shops.\n";
	break;
    default: /* Tree not on fire. */
	return "The walls are comprised of a naturally black stone "+
	"that has been highly polished to give it a glossy shine. This "+
	"helps serve to further distribute the light given off by the "+
	"glowing lanterns hanging from the kesoit tree that can just be "+
	"seen from the overlook in the centre of the galleria. About every "+
	"ten paces, a torch stand has been placed, further lighting the "+
	"walkway. Just above each torch, a large octagon is carved into "+
	"the wall and inlaid with pieces of ivory. Occasionally, between "+
	"the octagons, a doorway opens to one of the many galleria shops.\n";
	break;
    }
}

public string
see_torches(void)
{
    switch(season)
    {
    case 8..10: /* Tree on fire. */
	return "You see no torches.\n";
	break;
    default: /* Tree not on fire. */
	return "Heavy, wrought iron torch stands are placed every ten paces, "+
	"adding more light to the distant glow of the lanterns below.\n";
	break;
    }
}

public string
see_octagons(void)
{
    string str;

    switch(season)
    {
    case 8..10: /* Tree on fire. */
	str = "\n";
	break;
    default: /* Tree not on fire. */
	str = " The polished ivory pieces shine with reflected gold and blue "+
	"hues cast by the torches set below each one.\n";
	break;
    }

    return " Ivory-laden octagons are set flush in the wall every ten "+
    "paces or so, a symbolic prayer to Sair that she might bless the "+
    "walls and keep them strong." + str;
}

public string
see_branches(void)
{
/*
    string info = "\nKesoit trees are very rare, growing naturally on only "+
	"a few of the Sybarun islands and no where else. It is revered by the "+
	"Faithful of Sybarus, both for its beauty and as a symbol of the divine "+
	"power of the gods and respected by infidels as a marvel of natural "+
	"science. Each year through a seemingly natural process the kesoit tree "+
	"ignites and is covered in flames which ripens its fruit. Remarkably, "+
	"the heavy, black wood of the tree is not harmed by the flames and "+
	"sprouts and blooms again the next year.\n";
 */
    switch(season)
    {
    case 2..4: /* Tree regrows. */
	return "Just barely poking up in the center of the galleria "+
	"are the sturdy, black limbs of a sybarun kesoit tree. The branches are "+
	"covered with young, orange leaves and tiny dark flower buds are "+
	"just beginning to sprout. Diamond shaped lanterns hang from the "+
	"branches by black leather strips, adorning the tree with pulsing "+
	"Source-light.\n";
	break;
    case 5..7: /* Tree flowers/grows young fruit. */
	return "Just barely poking up in the center of the galleria "+
	"are the thick black limbs of a sybarun kesoit tree. The branches are "+
	"heavy with rubbery orange leaves and large black flowers in full "+
	"bloom. At the center of some of the flowers, small pale fruits have "+
	"begun to grow. Diamond shaped lanterns hang from the branches "+
	"by black leather strips, shining softly through the heavy leaves.\n";
	break;
    case 8..10: /* Fruit ripens, tree in flames. */
	return "Just barely poking up in the center of the galleria "+
	"are the fiery limbs and leaves of a sybarun kesoit tree. The branches "+
	"are ablaze with dancing flames, but amazingly don't seem to be consumed "+
	"by the flames. The thick rubbery leaves seem to be slowly dissolving "+
	"from the constant heat, but emit almost no smoke, just the warm, spicy "+
	"scent of kesoit.\n";
	break;
    default: /* Tree is dead. */
	return "Just barely poking up in the center of the galleria "+
	"are the skeletal black limbs of a sybarun kesoit tree. The branches "+
	"appear dead and are devoid of leaves, covered instead by what looks "+
	"like a fine layer of soot. Diamond shaped lanterns hang from the "+
	"branches by black leather strips, their pale light creating a halo "+
	"around the dark branches, like a still-life captured in black and "+
	"white.\n";
	break;
    }
}

public string
see_lanterns(void)
{
    string str = "The lanterns are made of triangular, clear glass panes "+
    "set into a diamond shape. Each lantern has a Source crystal suspended "+
    "in the center, ";

    switch(season)
    {
    case 2..4: /* Tree regrows. */
	return str + "making it glow with a pale light.\n";
	break;
    case 5..7: /* Tree flowers/grows young fruit. */
	return str + "which glows with a soft orange glow from behind the "+
	"tree leaves.\n";
	break;
    case 8..10: /* Fruit ripens, tree in flames. */
	return "You find no lanterns.\n";
	break;
    default: /* Tree is dead. */
	return str + "which glows with a pale light, making the bare tree "+
	"branches seem even starker in their blackness.\n";
	break;
    }
}

public string
see_leaves(void)
{
    switch(season)
    {
    case 2..4: /* Tree regrows. */
	return "The leaves on the kesoit tree are young. Many are small and freshly "+
	"sprouted, but many others have grown to their full size. The leaves are "+
	"a muted orange and heart-shaped, contrasting sharply with the coal-black "+
	"bark.\n";
	break;
    case 5..7: /* Tree flowers/grows young fruit. */
	return "The kesoit branches are heavy with the weight of the thick, rubbery "+
	"leaves typical of the tree. The leaves are a muted orange color and heart-"+
	"shaped. Thick red veins radiate out through the leaf and seem to be "+
	"almost pulsing with life.\n";
	break;
    case 8..10: /* Fruit ripens, tree in flames. */
	return "Just as the rest of the tree, the kesoit leaves are encased by "+
	"golden-red flames. The thick rubbery leaves do not seem to burn in the "+
	"fire, however. Instead they seem to be slowly dissolving, their thick veins "+
	"filled with the sap and water mixture the tree uses to fuel the fire which "+
	"will ripen its fruit.\n";
	break;
    default: /* Tree is dead. */
	return "You find no leaves on the kesoit tree, only a fine layer of what "+
	"looks like soot, making you wonder if this poor tree will ever bud again.\n";
	break;
    }
}

public string
see_flowers(void)
{
    switch(season)
    {
    case 2..4: /* Tree regrows. */
	return "Peering carefully through the young leaves of the kesoit tree, "+
	"one can make out small, black flower buds. Most are tightly closed, but "+
	"a few are just starting to open, revealing their papery black petals.\n";
	break;
    case 5..7: /* Tree flowers/grows young fruit. */
	return "Interspersed with the thick orange leaves, large black flowers "+
	"have blossomed all over the kesoit tree. The petals of the leaves are "+
	"long and tear shaped with a tiny barb on the end of each one. Their "+
	"darkness compliments the black wood and stands in contrast to "+
	"the red-orange of the leaves. At the center of many of the flowers a "+
	"small, pale fruit, no bigger than a sybarun coin, seems to be growing.\n";
	break;
    case 8..10: /* Fruit ripens, tree in flames. */
	return "The pretty black flowers seem to have withered away from the flames "+
	"leaving only their fruit behind.\n";
	break;
    default: /* Tree is dead. */
	return "You find no flowers.\n";
	break;
    }
}

public string
see_fruit(void)
{
    switch(season)
    {
    case 5..7: /* Tree flowers/grows young fruit. */
	return "The kesoit fruits are small and round. They are very pale and "+
	"covered with tiny, thorn-like spines that protect the fruit until it "+
	"is ripened in flame.\n";
	break;
    case 8..10: /* Fruit ripens, tree in flames. */
	return "Flames lick at the kesoit fruit, causing the pale fruit to "+
	"plump and develop a slow, red blush. When the fruit becomes nearly "+
	"completely red, the tiny thorns protecting it fall off, indicating "+
	"that the fruit is ripe.\n";
	break;
    default: /* Tree has no fruit. */
	return "You find no fruit.\n";
	break;
    }
}

public string
pick_fruit(void)
{
    switch(season)
    {
    case 5..7: /* Tree flowers/grows young fruit. */
	return "You doubt you can reach and the tiny thorns make you "+
	"reluctant to try.\n";
	break;
    case 8..10: /* Fruit ripens, tree in flames. */
	return "You doubt you can reach and the intense heat radiating from the "+
	"tree makes you reluctant to try.\n";
	break;
    default: /* Tree has no fruit. */
	return "You find no fruit.\n";
	break;
    }
}

public void
change_season(int week)
{
    season = week;
    kesoit_tells();
}

/* Called from the Ziggurat clepsydra as an event. */
public int
avenir_event(int year, int week, int day, int hour)
{
    if (week != season)
	change_season(week);

    return 1;
}
