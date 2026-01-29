// Ziggurat  (cahor2.c)
// creator(s):   Zielia 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include <macros.h>
#include "zigg.h"

inherit ZIG_ROOM;

public void
zig_room(void)
{
    set_short("A large stone chamber");
    set_long("The walls are rough and unpolished in this large, dim chamber, "+
	"as is the floor. Tool marks in the black stone are the only "+
	"sign that the walls were carved and not naturally formed. An "+
	"expertly crafted archway stands to the north, filled with a thick "+
	"covering of cobwebs. The chamber appears to be otherwise empty.\n");

    add_exit(DARK +"l4/n30", "north", "@@do_web", 5, 1);

    add_item(({"wall", "walls", "floor", "ceiling", "stone", "ground"}),
	"The walls have been carved out of black stone and left "+
	"rough and unpolished. The stone is dull and doesn't reflect "+
	"the smallest bit of light. Deep scratches and tool marks "+
	"further mar the stone.\n");

    add_item(({"arch", "archway", "voussoirs"}),
	"The archway has been set in the black stone wall "+
	"It is formed of twelve voussoirs carved of the same black stone "+
	"but polished to a high gloss and with beveled edges to emphasize "+
	"their form and giving it an elegant not seen elsewhere in this "+
	"chamber. At the apex of the arch is an "+
	"embellished keystone which sits slightly lower than the other "+
	"voussairs. The archway is completely covered by thick cobwebs "+
	"you have to walk through to leave.\n");

    add_item(({"keystone", }), "The keystone is "+
	"embellished to make it the prominent feature of the archway. It "+
	"is somewhat larger than the other voussoirs and dropped "+
	"slightly so that the bottom breaks the natural line of the arch. "+
	"The surface of the keystone is completely smooth, polished and "+
	"unmarked.\n");

    add_item(({"cobweb", "cobwebs", "web", "webs" }), "Thick white cobwebs "+
	"completely fill the archway to the north.\n");

    add_cmd_item(({"keystone", "keystones",}), ({"touch", "rub"}),
	"@@touch_stone");

    add_zigg();
}

public int
do_web(void)
{
    write("You break through the cobwebs.\n" +
	"A shiver runs up your spine as they brush against " +
	"your face.\n");
     this_player()->add_panic(100);

    return 0;
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

public void
init(void)
{
    ::init();

    add_action(f_kiss, "kiss");

}
