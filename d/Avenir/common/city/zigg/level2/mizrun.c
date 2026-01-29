// Ziggurat  (mizrun.c)
// creator(s):   Zielia 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

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

    add_exit("sanctorium", "west",  0);

    add_item(({"candles","sconces","flower-shaped sconces",}),
        "Several sconces are secured to the glossy black walls. Each "+
        "sconce has a wrought-iron support resembling a stem and holds "+
        "a blue tinted, tulip-shaped candle cup. Lighted candles "+
        "flicker within the cup, providing just enough light to see "+
        "by.\n");
    add_item(({"wall","walls","floor", "ground"}),
        "The walls and floor of this chamber are all made of highly "+
        "polished black stone.\n");
    add_item(({"ceiling","mist","vapors","lights","green lights",
        "tiny lights","tiny green lights","cloud"}),
        "The ceiling is shrouded by a misty green nebula, probably created "+
        "by rising vapors from the silver font. Tiny green lights "+
        "float within the vapors. You can't quite make them out, but they "+
        "dance and move within the cloud, darting here and there, leaving "+
        "streaking trails to be swallowed by the mist.\n");

    add_zigg();

    add_object(ZIG_OBJ + "altar_mizrun", 1, find_altar);
}

string
my_short()
{
    if (altar->id_altar_check(TP))
        return "Mizrun's Reliquary";
    else
        return "A dimly lit reliquary";
}

string
my_long()
{
    string str;

    str =   "Candles flicker inside flower-shaped sconces placed "+
            "strategically along the glossy black walls, offering a small "+
            "amount of light. At the center of the chamber, a low altar "+
            "enshrouded in a hazy aura emits a faint green glow. High "+
            "above your head, the ceiling is veiled by misty vapors "+
	    "illuminated by the tiny green lights dancing within the cloud.\n";

    if (altar->id_altar_check(TP))
        return "This is the altar room to Mizrun. "+ str;
    else
        return str;
}

public int
item_id(string str)
{
    if (::item_id(str))
	return 1;
    else
	return altar->item_id(str);
}

public void
hook_smelled(string what)
{
    switch(what)
    {
    case "vapors":
        write("The haze around the font has a warm, saccharine smell "+
            "that is almost too sweet yet makes you feel relaxed and "+
            "lethargic.\n");
    break;
    default:
	if (strlen(what))
	    return altar->hook_smelled(what);

        write("The air is scented with a pungent, sickly-sweet scent "+
            "that is somehow relaxing.\n");
    break;
    }
}
