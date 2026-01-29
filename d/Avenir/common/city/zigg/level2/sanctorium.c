// Ziggurat  (sanctorium.c)
// creator(s):   Lucius + Zielia 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include <macros.h>
#include <language.h>
#include "zigg.h"

inherit ZIG_ROOM;
inherit RLOG;

public int portal;
public int closed = 1;

public void
zig_room(void)
{
    set_short("sanctorium");

    set_long("The weighty black stone and dramatic arches create a hushed, "+
        "almost reverent air, as though the Gods themselves might be "+
        "listening to the echoes of words and prayers whispered here. In "+
        "the center of this chamber a simple chandelier hangs above a "+
        "quietly trickling bronze and glass clepsydra. Glossy black stone "+
        "surrounds you with arched openings to the north, east and west. A "+
	"similar archway to the south has been bricked off.\n");

    add_item(({"arch","archway"}),
        "Which archway did you want to examine?\n");

    add_item(({"walls","wall","stone","black stone","black stones"}),
	"The walls are comprised of a naturally black stone "+
        "that has been highly polished to give it a glossy shine. This "+
        "helps serve to further distribute the light given off by the "+
        "glowing chandelier above. Dramatic arches open to the north, "+
	"east and west. A similar archway to the south has been bricked "+
	"off with white stones.\n");

    add_item(({"arches","archways"}),
        "Archways have been set in the black stone to the north, south, "+
	"east and west. Each rounded archway is formed of twelve wedge-shaped "+
	"voussoirs of matching black stone with beveled edges to emphasize "+
	"their form. At the apex of each arch is a decoratively carved "+
	"keystone. The archway to south is completely filled in with alabaster "+
	"bricks.\n");

    add_item(({"north arch","north archway","northern arch",
	"northern archway", "archway to the north", "arch to the north",}),
        "The archway has been set in the black stone wall of the Ziggurat. "+
	"It is formed of twelve voussoirs carved of the same black stone "+
	"but with beveled edges to emphasize their form. At the apex of "+
	"each arch is a decoratively carved keystone. Through the archway "+
	"you can see the corridor leading to the stairs and deeper into "+
	"the Ziggurat.\n");

    add_item(({"east arch","east archway","eastern arch",
	"eastern archway", "archway to the east", "arch to the east",}),
        "The archway has been set in the black stone wall of the Ziggurat. "+
	"It is formed of twelve voussoirs carved of the same black stone "+
	"but with beveled edges to emphasize their form. At the apex of "+
	"each arch is a decoratively carved keystone. Dim green light fills "+
	"the space beneath the arch.\n");

    add_item(({"west arch","west archway","western arch",
	"western archway", "archway to the west", "arch to the west",}),
        "The archway has been set in the black stone wall of the Ziggurat. "+
	"It is formed of twelve voussoirs carved of the same black stone "+
	"but with beveled edges to emphasize their form. At the apex of "+
	"each arch is a decoratively carved keystone. Flickering blue and "+
	"red light fills the space beneath the arch.\n");

    add_item(({"south arch","south archway","southern arch",
	"southern archway", "archway to the south", "arch to the south",}),
        "The archway has been set in the black stone wall of the Ziggurat. "+
	"It is formed of twelve voussoirs carved of the same black stone "+
	"but with beveled edges to emphasize their form. At the apex of "+
	"each arch is a decoratively carved keystone. For some reason, "+
	"this archway has been completely filled in with white alabaster "+
	"stones like bricks. They stand in sharp contrast to the black "+
	"stone around them almost as though someone did not want this bit "+
	"of remodeling to go unnoticed.\n");

    add_item(({"chandelier","simple chandelier"}),
        "Twelve glowing points of light hang in a perfect circle above "+
        "this juncture. Curvaceous scrolled bronze arms support bell-shaped "+
        "glasses, each of which contains a steadily glowing source crystal.\n");

    add_item(({"north keystone", "northern keystone",}),
	"The keystone is embellished to make it the "+
	"prominent feature of the archway. It is somewhat larger than the "+
	"other voussoirs and dropped slightly so that the bottom breaks "+
	"the natural line of the arch, further drawing your attention "+
	"to the stone. It is made of glossy black stone with beveled "+
	"edges. On the face of the keystone is a low bas-relief of a lock "+
	"and key, the carving barely rising from the surface of the "+
	"surrounding stone, but unpolished so it contrasts very clearly "+
	"and displays fine detail.\n");

    add_item(({"lock", "key", "lock and key", "north bas relief",
	"northern bas relief"}),
	"A picture of a lock and key has been carved to rise slightly from "+
	"the surface of the northern keystone. The picture is unpolished, "+
	"its natural finish allowing it to contrast more fully from "+
	"the glossy stone which surrounds it.\n");

    add_item(({"east keystone", "eastern keystone",}),
	"The keystone is embellished to make it the prominent feature of "+
	"the archway. It is somewhat larger than the other voussoirs and "+
	"dropped slightly so that the bottom breaks the natural line of "+
	"the arch, further drawing your attention to the stone. It is "+
	"made of glossy black stone with beveled edges. On the face of "+
	"the keystone is a low bas-relief crescent, its points upward. "+
	"The carving barely rising from the surface of the surrounding "+
	"stone, but it has been limned with gold, giving it clear "+
	"definition.\n");

    add_item(({"crescent", "east bas relief", "eastern bas relief"}),
	"A simple crescent has been carved to stand up from the stone of "+
	"the eastern keystone. It's edges have been carefully painted with "+
	"gold, making it well defined amidst all the black stone of this "+
	"chamber.\n");

    add_item(({"west keystone", "western keystone",}),
	"The keystone is embellished to make it the prominent feature of "+
	"the archway. It is somewhat larger than the other voussoirs and "+
	"dropped slightly so that the bottom breaks the natural line of "+
	"the arch, further drawing your attention to the stone. It is "+
	"made of glossy black stone with beveled edges. Inset into the "+
	"face of the keystone a red spinel, carefully faceted into the "+
	"shape of a triangle and set beneath what must be a black "+
	"diamond, also triangular, with it's point downward and sparkling "+
	"with cold brilliance even in the rather dim light.\n");

    add_item(({"spinel", "red spinel", "red triangle"}),
	"A large red spinel has been set into the keystone of the western "+
	"arch. It has been cut into the shape of a triangle with its point "+
	"up by what must have been a master craftsman. It is carefully "+
	"faceted to catch the light and allow it's vivid red coloring to "+
	"show even while surrounded by the raven-black walls.\n");

    add_item(({"diamond", "black diamond", "black triangle"}),
	"A large black diamond has been set into the keystone of the "+
	"western arch. It has been cut into the shape of a triangle with "+
	"its point down by what must have been a master craftsman. "+
	"It is carefully faceted to catch the light and glimmers with a "+
	"cold brilliance that far surpasses the glossy black stone of the "+
	"walls surrounding it.\n");

    add_item(({"south keystone", "southern keystone",}), "The keystone is "+
	"embellished to make it the prominent feature of the archway. It "+
	"is somewhat larger than the other voussoirs and dropped "+
	"slightly so that the bottom breaks the natural line of the arch, "+
	"dipping into the carved white stones which block the archway. "+
	"A dull raised spot on the surface leads you to suspect "+
	"there was once a low bas-relief carved onto the face of the "+
	"keystone, but whatever it was is no longer distinguishable.\n");

    add_item(({"dull spot", "raised spot", "dull raised spot",
	"south bas relief", "southern bas relief"}),
	"There is a dull, slightly raised spot on the face of the southern "+
	"keystone. Perhaps the carving was removed when the entrance "+
	"was bricked over, but it does not look as though it was scratched "+
	"or filed away. It is looks dull and very smooth, almost like it "+
	"had been worn down by being touched or rubbed often over a long "+
	"period. There is some kind of smudge on it.\n");

    add_item(({"streak","smudge", "streaks", "smudges"}),
	"It looks like something waxy, slightly shiny, perhaps sticky. It "+
	"has the shape of two streak-like marks which fade as they move "+
	"from the center of the keystone toward the bottom, almost like "+
	"someone had wiped something on it with two fingers.\n");

    add_item(({"bricks", "stones", "white bricks", "white stones", "white wall"}),
	"@@see_bricks");

    add_item(({"bas relief", "relief", "keystone", "keystones",
	"voussoirs", "carving", "jewel",  }), "Which would you like to "+
	"examine?\n");

    add_cmd_item(({"bas relief", "relief", "keystone", "keystones",
	"voussoirs", "carving", "jewel",  }), ({"touch", "rub"}),
	"Touch which?\n" );

    add_cmd_item(({"key", "lock", "lock and key", "north bas relief",
	"northern bas relief", "north keystone", "northern keystone",
	"north relief", "northern relief", "north carving",
	"northern carving", }), ({"touch", "rub"}), "@@touch_north");

    add_cmd_item(({"crescent", "gold", "simple crescent", "east bas relief",
	"eastern bas relief", "east keystone", "eastern keystone",
	"east relief", "eastern relief", "east carving",
	"eastern carving",  }), ({"touch", "rub"}), "@@touch_east");

    add_cmd_item(({"spinel", "diamond", "jewels",  "west keystone",
	"western keystone", "upper triangle", "lower triangle",
	"black triangle", "red triangle", }), ({"touch", "rub"}),
	"@@touch_west");

    add_cmd_item(({"dull spot", "raised spot", "dull raised spot",
	"south bas relief", "southern bas relief", "smudge", "streak",
	"streaks", "smudges", "south keystone", "southern keystone",
	"south relief", "southern relief", "south carving",
	"southern carving", "spot", }), ({"touch", "rub"}), "@@touch_south");


    add_exit("stairs", "north",  0);
    add_exit("mizrun", "east",   0);
    add_exit("cahor2", "south", "@@query_closed", 1, 1);
    add_exit("jazsis",  "west",   0);

    add_zigg();

    add_object(ZIG_OBJ +"clepsydra", 1);
}


public string
touch_north(void)
{
    object tp = TP;

    if (IN_ARRAY(TP->query_race(), ({"kender", "dwarf", "hobbit", "goblin"})))
    {
	    return "You'll have to grow some first.\n";
    }

    write("You reach up to touch the northern keystone. The stone is cool "+
	"to the touch. The raised carving is well defined and very smooth, "+
	"though not slick like the glossy stone around it.\n");


    if (present("salilus::kiss", TP))
    {
	set_alarm(2.0, 0.0, &tell_object(tp, "Your gesture goes unnoticed.\n"));
	present("salilus::kiss", TP)->remove_object();
    }

    say(QCTNAME(TP) +" reaches up to touch the northern keystone.\n");

    return "";
}

public string
touch_east(void)
{
    object tp = TP;

    if (IN_ARRAY(TP->query_race(), ({"kender", "dwarf", "hobbit", "goblin"})))
    {
	    return "You'll have to grow some first.\n";
    }

    write("You reach up to touch the eastern keystone. The stone is cool "+
	"to the touch. The raised crescent is well defined. It has clean "+
	"edges where it rises from the stone, softened only slightly "+
	"by the coating of gold that was added to it. The surface of the "+
	"crescent is likewise very flat with just the slightest discernible "+
	"seam between the stone and the gold at the edge.\n");

    if (present("salilus::kiss", TP))
    {
	set_alarm(2.0, 0.0, &tell_object(tp, "Your gesture goes unnoticed.\n"));
	present("salilus::kiss", TP)->remove_object();
    }

    say(QCTNAME(TP) +" reaches up to touch the eastern keystone.\n");

    return "";
}

public string
touch_west(void)
{
    object tp = TP;

    if (IN_ARRAY(TP->query_race(), ({"kender", "dwarf", "hobbit", "goblin"})))
    {
	    return "You'll have to grow some first.\n";
    }

    write("You reach up to touch the western keystone. The stone is cool "+
	"to the touch. The two jewels seem even colder though. Their "+
	"perfectly cut facets are even smoother than the glossy black "+
	"stone which surrounds them. They are well mounted without even the "+
	"slightest wiggle to indicate they might come loose.\n");

    if (present("salilus::kiss", TP))
    {
	set_alarm(2.0, 0.0, &tell_object(tp, "Your gesture goes unnoticed.\n"));
	present("salilus::kiss", TP)->remove_object();
    }

    say(QCTNAME(TP) +" reaches up to touch the western keystone.\n");

    return "";
}

public string
see_bricks(void)
{
    if (CAN_SEE_TRUE(TP))
    {
	return "The southern archway has been filled in with white, "+
	    "brick-like stones which look like alabaster. The stones "+
	    "seem to waver slightly in your sight, almost as though you "+
	    "were looking at them through a sheet of falling water. As "+
	    "you look closely, you find you now recognize them as a "+
	    "brilliantly created illusion designed to fool all the senses, "+
	    "but you could walk right through the wall if you tried.\n";
    }
    
    return "The southern archway has been filled in with white, "+
	"brick-like stones which are probably carved alabaster. White "+
	"mortar fills the spaces between the stones and prevents any kind "+
	"of glimpse at what lies behind them. The stones have been cut to "+
	"perfectly match the shape of the archway that binds them and "+
	"contrast sharply with the black stone in a way that would almost "+
	"be an eyesore if it wasn't so skillfully crafted.\n";
}		

public int
query_closed(void)
{
    if (closed)
    {
	write("You don't want to walk through the wall, do you?\n");
    }
    else
    {
	write("You enter the portal and are momentarily blinded as you "+
	    "step out into another chamber.\n");

	logrotate(ZIG_LOGS + "portal",
	    time2format(time(), "mmm dd yyyy tt: ") +
	    TP->query_cap_name() +" entered the Sanctorium portal.\n");

    }

    return closed;
}

public int
wall_exit(string str)
{
    if(!closed)
    {
        return 0;
    }

    if (str == "through wall" || str == "through the wall")
    {

	write("Convincing yourself that it is only an illusion, despite "+
	    "all that your senses tell you, you walk through the white stone "+
	    "wall.\n");

	TP->move_living("through the wall", ZIG_RL2 +"cahor", 1, 0);

	return 1;
    }

	return 0;

}

public int
enter_portal(string str)
{
    if(closed)
    {
        return 0;
    }

    if (str == "portal" || str == "the portal")
    {

	write("You enter the portal and are momentarily blinded as you "+
	    "step out into another chamber.\n");

	logrotate(ZIG_LOGS + "portal",
	    time2format(time(), "mmm dd yyyy tt: ") +
	    TP->query_cap_name() +" entered the Sanctorium portal.\n");

	TP->move_living("through the portal", ZIG_RL2 +"cahor2", 1, 0);

	return 1;
    }
    else
    {
	notify_fail("Enter what?\n");
	return 0;
    }
}

public void
open_portal(int count, object tp)
{
    float wait = 5.0;

    if (count == -1)
    {
	tell_room(TO, "Suddenly the glowing purple light filling the "+
	    "southern archway flickers repeatedly and goes out, leaving "+
	    "nothing but white stone and mortar in its place.\n", 0, TO);
	portal = 0;
	closed = 1;
	return;
    }

    switch(++count)
    {
    case 1:
	tp->catch_tell("A feeling of ecstasy uplifts you, as though you "+
	    "can feel Salilus' pleasure in your actions.\n");
	break;
    case 2:
	tell_room(TO, "The southern archway begins to glow with a strange "+
	    "purple light.\n", 0, TO);
	break;
    case 3:
	tell_room(TO, "The purple light bleeds inwards from the arch, "+
	    "becoming brighter and brighter until you can no longer see "+
	    "the white stones within it.\n", 0, TO);
	break;
    case 4:
	tell_room(TO, "The southern archway has become a glowing purple "+
	    "vortex, a doorway to the unknown.\n", 0, TO);
	closed = 0;
	break;
    default:
	tell_room(TO, "The purple light in the doorway becomes "+
	    "brighter for a moment and then dims again.\n", 0, TO);
	wait = 14.0;
	break;
    }
    if (count > (6 + random(4)))
    {
	count = -1;
    }

    portal = set_alarm(wait, 0.0, &open_portal(count, tp));
}

public string
touch_south(void)
{
    object tp = TP;

    if (IN_ARRAY(TP->query_race(), ({"kender", "dwarf", "hobbit", "goblin"})))
    {
	    return "You'll have to grow some first.\n";
    }

    if (present("salilus::kiss", TP) && !portal)
    {
	write("You reach up to touch the southern keystone, completing the "+
	    "ritual gesture expressing praise and adoration to Salilus, "+
	    "keeper of portals, in hopes of safe passage.\n");

	portal = set_alarm(2.0, 0.0, &open_portal(0, tp));
    }
    else
    {

	write("You reach up to touch the southern keystone. The stone is cool "+
	    "to the touch and has slight curve to the face where it has been "+
	    "worn down. It feels very smooth until your fingers run over "+
	    "something kind of waxy. When you pull them away, you notice a "+
	    "shiny pink substance on them kind of like the pomades some women "+
	    "wear on their lips.\n");

	if (present("salilus::kiss", TP) && portal)
	{
	    set_alarm(2.0, 0.0, &tell_object(tp, "Your gesture goes unnoticed.\n"));
	    present("salilus::kiss", TP)->remove_object();
	}
    }

    say(QCTNAME(TP) +" reaches up to touch the southern keystone.\n");
    return "";
}

public int
f_kiss(string str)
{
    string what;

    if (!strlen(str))    {return 0;}

    if (parse_command(str, ({}), "[my] / [myself] [on] [the] [north] / "+
	"[northern] /  [east] / [eastern]  / [south] / [southern] / "+
	"[west] / [western] %w", what))
    {
	if (what == "keystone")
	{
	    write("Your lips can't reach it.\n");
	    return 1;
	}

	if (IN_ARRAY(what, ({ "finger", "fingers", "hand",
	    	"fingertip", "fingertips" })))
	{
	    write("You kiss your "+ what +" lightly.\n");
	    say(QCTNAME(TP) +" kisses "+ HIS(TP) +" "+ what +
		" lightly.\n");
	    if (!present("salilus::kiss", TP))
	    {
		object kiss = clone_object(ZIG_OBJ +"s_kiss");
		kiss->move(TP, 1);
	    }

	    return 1;
	}

	return 0;
    }
}

public void
f_urge(object tp, string god)
{
    mapping which =  ([	"Jazur"   :   "west",
			"Sisera"  :   "west",
			"Cahor"   :   "south",
			"Mizrun"  :   "east",
		     ]);

    if (god == "Salilus" && portal)
    {
	tp->catch_tell("Your prayers go unheard.\n");

	return;
    }

    tp->catch_tell("You feel a strange urge to go "+ which[god] +", as "+
	"though something were drawing you that way.\n");
}

public int
f_pray(string str)
{
    string who;

    if (!strlen(str))
    {
	notify_fail("Pray to whom?\n");

	return 0;
    }

    parse_command(str, ({}), "[a] [prayer] [to] %w", who);

    who = capitalize(who);

    if (IN_ARRAY(who, ({"Jazur", "Sisera", "Cahor", "Mizrun", "Salilus"})))
    {
	write("You bow your head and whisper a prayer to "+ who +".\n");


	if (who == "Salilus" && !portal)
	{
	    portal = set_alarm(2.0, 0.0, &open_portal(0, TP));

	}
	else
	{
	    set_alarm(2.0, 0.0, &f_urge(TP, who));
	}

    }
    else
    {
	write("You bow your head and pray but feel as if you did it wrong.\n");
    }

    say(QCTNAME(TP) +" bows "+ HIS(TP) +" head and whispers a "+
	"prayer.\n");
    return 1;
}

public int
f_push(string str)
{
    string what;

    if (!strlen(str))
    {
	notify_fail("Push what?\n");
	return 0;
    }

    if (!parse_command(str, ({ }),
        "[on] [the] [white] [stone] / [brick] / [south] / [southern] / "+
        "[west] / [western] / [north] / [northern] / [east] / [eastern] "+
        "%w", what))
    {
        return 0;
    }

    if (IN_ARRAY(what, ({"wall", "bricks", "stones", "brick", "stone",
	"keystone", "arch", "archway"})))
    {
	write("You push on the "+ what +" as hard as you can, but it "+
	    "doesn't budge at all.\n");

	say(QCTNAME(TP) +" pushes hard against the "+ what +" but "+
	    "it doesn't seem to have any effect.\n");

	return 1;
    }

    notify_fail("Push what?\n");
    return 0;
}

public int
f_pull(string str)
{
    string what;

    if (!strlen(str))
    {
	notify_fail("Pull what?\n");
	return 0;
    }

    if (!parse_command(str, ({ }),
        "[on] [the] [white] [stone] / [brick] / [south] / [southern] / "+
        "[west] / [western] / [north] / [northern] / [east] / [eastern] "+
        "%w", what))
    {
        return 0;
    }

    if (IN_ARRAY(what, ({"wall", "bricks", "stones", "brick", "stone",
	"keystone", "arch", "archway"})))
    {
	write("You try to pull on the "+ what +" but can't find a handhold.\n");

	say(QCTNAME(TP) +" tries to pull on the "+ what +" but "+
	    "can't find anywhere to hold on.\n");

	return 1;
    }

    notify_fail("Pull what?\n");
    return 0;
}

public int
f_break(string str)
{
    string what;

    if (!strlen(str))
    {
	notify_fail("Break what?\n");
	return 0;
    }

    if (!parse_command(str, ({ }),
        "[down] [the] [white] [stone] / [brick] / [south] / [southern] / "+
        "[west] / [western] / [north] / [northern] / [east] / [eastern] "+
        "%w", what))
    {
        return 0;
    }

    if (IN_ARRAY(what, ({"wall", "bricks", "stones", "brick", "stone",
	"keystone", "arch", "archway"})))
    {
	write("The "+ what +" is thick, sturdy stone and expertly crafted. "+
	    "You would only hurt yourself trying.\n");

	return 1;
    }

    notify_fail("Break what?\n");
    return 0;
}

public void
init(void)
{
    ::init();

    add_action(wall_exit, "walk");
    add_action(enter_portal, "enter");
    add_action(f_kiss, "kiss");
    add_action(f_pray, "pray");
    add_action(f_pray, "whisper");
    add_action(f_push, "push");
    add_action(f_pull, "pull");
    add_action(f_break, "break");
}
