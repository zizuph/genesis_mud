// Ziggurat  (cahor.c)
// creator(s):   Zielia 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include <macros.h>
#include </sys/ss_types.h>
#include "zigg.h"

inherit ZIG_ROOM;

private static object altar;

private void
find_altar(object ob)
{
    altar = ob;
}

public void
zig_room(void)
{
    set_short("@@my_short");
    set_long("@@my_long");

    add_exit("sanctorium", "north", "@@query_closed", 1, "@@can_see");

    add_zigg();

    add_item(({"keystone", }), "The keystone is "+
	"embellished to make it the prominent feature of the archway. It "+
	"is somewhat larger than the other voussoirs and dropped "+
	"slightly so that the bottom breaks the natural line of the arch. "+
	"The surface of the keystone is completely smooth, polished and "+
	"unmarked.\n");

    add_item(({"wall", "walls", "floor", "ceiling", "stone", "ground"}), 
        "@@see_walls");
    add_item(({"arch", "archway", "voussairs"}), "@@see_archway");
    add_item(({"bricks", "stones", "white bricks", "white stones",
	"white wall"}), "@@see_bricks");
    add_item(({"silver runes", "runes"}), "@@see_runes");

    add_cmd_item(({"silver runes", "runes"}), ({"read"}), "@@see_runes");
    add_cmd_item(({"keystone", "keystones",}), ({"touch", "rub"}),
	"@@touch_stone");

    add_object(ZIG_OBJ + "altar_cahor", 1, find_altar);
}

string
my_short()
{
    if (CAN_SEE_TRUE(TP))
    {
	if (altar->id_altar_check(TP))
	    return "Cahor's Reliquary";
	else
	    return "A breathtaking reliquary";
    }

    return "A large stone chamber";
}

string
my_long()
{
    string str;
    if (CAN_SEE_TRUE(TP))
    {
	str = "The walls in this chamber are breathtaking. They are "+
	      "carved of black stone marbleized with thin veins of Source "+
	      "crystal, making the whole room glow with swirlng lines of "+
	      "irridescent light. Even the floor is made of this stone "+
	      "making you feel as though you are floating in some fantastic "+
	      "abyss. At the center of the chamber a black stone slab "+
	      "supports a crystal basin of pure clear water next to which "+
	      "lies a neatly folded piece of black webcloth. There is a "+
	      "well crafted archway which opens to the sanctorium to the "+
	      "north.\n";

	if (altar->id_altar_check(TP))
	    return "This is the altar room to Cahor. "+ str;
	else
	    return str;
    }

    return "The walls are rough and unpolished in this large, dim chamber, "+
	"as is the floor. Tool marks in the black stone are the only "+
	"sign that the walls were carved and not naturally formed. An "+
	"expertly crafted archway stands to the north, filled with a wall "+
	"of white stone. The chamber appears to be otherwise empty.\n";
}

public int
item_id(string str)
{
    if (::item_id(str))
	return 1;
    else
	return altar->item_id(str);
}

public int
query_closed(void)
{
    if (!CAN_SEE_TRUE(TP))
    {
	write("You don't want to walk through the wall, do you?\n");
	return 1;
    }
    write("You feel an odd chill as you walk through the archway, when "+
        "you turn and look back, it appears once more to be blocked by "+
        "white bricks.\n");
    return 0;
}

public int
can_see(void)
{
    if (CAN_SEE_TRUE(TP))
    {
	return 0;
    }

    return 1;
}

public string
see_walls(void)
{
    if (CAN_SEE_TRUE(TP))
    {
	return "The walls, floor and ceiling are made out of a breathtaking "+
	    "black marble with thin veins of sourcelight that glow and "+
	    "shimmer with faint rainbow colors.\n";
    }
    else
    {
	return "The walls, floor and ceiling have been carved out of "+
	    "black stone and left rough and unpolished. The stone is dull "+
	    "and doesn't reflect the smallest bit of light. Deep scratches "+
	    "and tool marks further mar the stone.\n";
    }
}

public string
see_archway(void)
{
    if (CAN_SEE_TRUE(TP))
    {
        return "The archway has been set in the marbleized wall of the "+
	"chamber. It is formed by twelve voussoirs carved of glossy black "+
	"stone typical of the Ziggurat, but lacking the glowing lines of "+
	"the rest of the chamber, making it well defined by contrast. "+
	"The edges of the voussairs are beveled to further emphasize their "+
	"form and create a nice finish. At the apex of the arch is an "+
	"embellished keystone which sits slightly lower than the other "+
	"voussairs. Beyond the archway, you can see the sanctorium.\n";
    }
    else
    {
        return "The archway has been set in the black stone wall "+
	"It is formed of twelve voussoirs carved of the same black stone "+
	"but polished to a high gloss and with beveled edges to emphasize "+
	"their form and giving it an elegant not seen elsewhere in this "+
	"chamber. At the apex of the arch is an "+
	"embellished keystone which sits slightly lower than the other "+
	"voussairs. For some reason, this archway has been completely "+
	"filled in with white alabaster stones like bricks. They stand "+
	"in sharp contrast to the black stone around them.\n";

    }
}

public string
see_bricks(void)
{
    if (CAN_SEE_TRUE(TP))
    {
        return "You find none.\n";
    }
    else
    {
        return "The archway has been filled in with white, brick-like "+
	"stones which are probably carved alabaster. White mortar fills the "+
	"spaces between the stones and prevents any sort of glimpse at what "+
	"lies behind them. The stones have been cut to perfectly match the "+
	"shape of the archway that binds them and contrast sharply with the "+
	"black stone in a way that would almost be an eyesore if "+
	"it wasn't so skillfully crafted. Silver runes have been etched "+
	"into one of the bricks.\n";
    }
}

public string
see_runes(void)
{
    string str;

    if (CAN_SEE_TRUE(TP))
    {
        return "You find no runes.\n";
    }
    else
    {
	if (TP->query_skill(SS_LANGUAGE) > 19)
	{
	    str = "some sort of prayer or incantation. You think they "+
		  "read 'Let that which is but a dream become unseen.'\n";
	}
	else
	{
	    str = "but you cannot understand them.\n";
	}

        return "The runes glimmer in the light. You recognize them as "+
	    "an archaic form of sybarite, "+ str;
    }
}

public int
f_kiss(string str)
{
    string what;

    if (!strlen(str))    {return 0;}

    if(parse_command(str, ({}), "[my] / [myself] [on] [the] %w", what))
    {
	if(what == "finger" || what == "fingers" || what == "hand")
	{
	    write("You kiss your "+ what +" lightly.\n");
	    say(QCTNAME(TP) +" kisses "+ HIS(TP) +" "+ what +
		"lightly.\n");

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

public string
touch_stone(void)
{
    if (IN_ARRAY(TP->query_race(), ({"kender", "dwarf", "hobbit", "goblin"})))
    {
	    return "You'll have to grow some first.\n";
    }

    write("You reach up to touch the keystone. The stone is cool and "+
	"slick to the touch, perfectly polished and unremarkable.\n");

    if (present("salilus::kiss", TP))
    {
	write("Your gesture goes unnoticed.\n");
    }

    say(QCTNAME(TP) +" reaches up to touch the keystone.\n");

    return "";
}

public int
f_incant(string str)
{
    if(str == "Let that which is but a dream become unseen." ||
    str == "let that which is but a dream become unseen")
    {
	write("You say the incantation and immediately your vision "+
	    "blurrs, everything seeming to shift slightly to the left. "+
	    "The white stones in the archway seem to fade away and the "+
	    "entire room looks different.\n");
	say(QCTNAME(TP) +" incants something in an archaic form of "+
	    "Sybarite.\n");
	TP->add_prop(PROP_I_SEE_TRUE, 1);
	return 1;
    }

    notify_fail("Incant what?\n");
    return 0;
}

public int
wall_exit(string str)
{
    if(CAN_SEE_TRUE(TP))
    {
        return 0;
    }

    if (str == "through wall" || str == "through the wall")
    {

	write("Convincing yourself that it is only an illusion, despite "+
	    "all that your senses tell you, you walk through the white stone "+
	    "wall.\n");

	TP->move_living("through the wall", ZIG_RL2 +"sanctorium", 1, 0);

	return 1;
    }

	return 0;

}


public int
f_push(string str)
{
    string what;

    if (CAN_SEE_TRUE(TP))
    {
        return 0;
    }

    if (!strlen(str))
    {
	notify_fail("Push what?\n");
	return 0;
    }

    if (!parse_command(str, ({ }),
        "[on] [the] [white] [stone] / [brick] / [north] / [northern] "+
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

    if (CAN_SEE_TRUE(TP))
    {
        return 0;
    }

    if (!strlen(str))
    {
	notify_fail("Pull what?\n");
	return 0;
    }

    if (!parse_command(str, ({ }),
        "[on] [the] [white] [stone] / [brick] / [north] / [northern] "+
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

    if (CAN_SEE_TRUE(TP))
    {
        return 0;
    }

    if (!strlen(str))
    {
	notify_fail("Break what?\n");
	return 0;
    }

    if (!parse_command(str, ({ }),
        "[down] [the] [white] [stone] / [brick] / [north] / [northern] "+
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
    add_action(f_kiss, "kiss");
    add_action(f_incant, "incant");
    add_action(f_push, "push");
    add_action(f_pull, "pull");
    add_action(f_break, "break");
}
