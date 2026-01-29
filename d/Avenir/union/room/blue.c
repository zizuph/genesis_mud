/* The board room for the Shadow Union     */
/*           Cirion 031996                 */
#pragma strict_types

#include "../defs.h"

#include <macros.h>
#include <cmdparse.h>
#include <language.h>

inherit BASE;

public string *phrases = ({
    "Through beauty and grace shall our enemies be destroyed.",
    "We walk in Shadow.", "The mist of darkness shall hold us within "+
	"her arms.",
    "The Sway shall summon forth deeper sight.",
    "Along paths unknown and treacherous, we remain stolid.",
    "With dignity and silence will we humiliate our enemies.",
    "Banished to the terrible Outside shall be those who would "+
	"betray the Union.",
    "Cleanliness and order is the way to glory.",
    "Many secrets are held within the deep.", "The Flame will be "+
	"our link to the shadows. Let it not go out."
});

public int ex, words = random(sizeof(phrases));

public void
union_room(void)
{
    set_short("blue room");
    set_long("Long, flat walls of pale blue limestone "+
	"border this room, making it a perfect cube. The "+
	"light reflected off of the walls is soft and "+
	"gentle, and much of it falls in a shallow pool "+
	"on a large gneiss tablet which sits in the "+
	"east end of the room. @@door_desc@@\n");

    add_item(({"wall","walls","limestone"}),
	"The walls are pale blue, soft to the touch.\nAll along "+
	"the walls are tiny inscriptions engraved within the walls "+
	"in elegant script.\n@@wall_desc@@\n");
    add_item(({"indentation"}),
	"It is a small indentation in the east wall.\n");
    add_item("east wall",
	"It looks just like the other walls, except that in the direct "+
	"center of it is a tiny spherical indentation.\n");
    add_item(({"floor","ground"}),
	"The floor is made from solid granite, dark and hard.\n");
    add_item("light",
	"The light that reflects off the walls is a pale blue.\n");
    add_item(({"word","words","wall","inscription","inscriptions"}),
	"@@words@@");

    add_cmd_item(({"wall","walls","limestone"}),({"touch","feel"}),
	"The limestone is smooth to the touch.\n");
    add_cmd_item(({"board","tablet","gneiss"}),({"touch","feel"}),
	"It is rough and hard, covered with many spidery scrawlings.\n");
    add_cmd_item(({"word","words","wall","inscription","inscriptions"}),
	"read", "@@words@@");

    add_exit("landing", "west");
    add_object(OBJ + "board");
}

public string
door_desc(void)
{
    if (!ex) return "";
    return "A section of the east wall has opened up, leading "+
	"into a very large room.\n";
}

public string
wall_desc(void)
{
    if (ex) return door_desc();
    return "In the center of the east wall is a tiny, "+
	"half-sphere indentation.";
}

public string
words(void)
{
    if (!IS_MEMBER(TP))
	return "They are all indecipherable.\n";

    if (++words >= sizeof(phrases))
	words = 0;

    return "One of the phrases reads:\n" +
	break_string(phrases[words], 55, 5) +"\n";
}

public void
rem_exit(void)
{
    remove_exit("east");
    if (!ex) return 0;

    ex = 0;
    tell_room(TO,
	"The section of the east wall slides closed silently.\n");
    tell_room(ROOM + "meeting",
	"The opening in the west wall closes silently.\n");
}

public int
exit_open(void)
{
    return ex;
}

public int
open_exit(void)
{
    if (ex) return 0;

    tell_room(TO,
	"A section of the east wall slides noislessly open.\n");
    tell_room(ROOM + "meeting",
	"A section in the west wall slides noislessly open.\n");

    ex = 1;
    add_exit("meeting", "east");

    set_alarm(6.0, 0.0, rem_exit);
    return 1;
}

public int
place(string str)
{
    string what;
    object *obs, ob;

    NF(CAP(query_verb()) + " what where?\n");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({}),
	    "[the] %s 'in' / 'into' [the] 'hole' / 'indentation'", what))
    {
	return 0;
    }

    obs = FIND_STR_IN_OBJECT(what, TP);
    if (!sizeof(obs))
	return 0;

    ob = obs[0];

    if (!ob->id(TOKEN_ID))
    {
	write(CAP(LANG_THESHORT(ob)) + " does not fit.\n");
	return 1;
    }

    if (ex)
    {
	write("Nothing happens.\n");
	return 1;
    }

    write("You " + query_verb() + " the sphere in the indentation.\n");
    say(QCTNAME(TP) + " " + LANG_PWORD(query_verb()) + " " +
	LANG_ASHORT(ob) +" into the indentation in the east wall.\n");

    open_exit();
    return 1;
}

public void
init(void)
{
    ::init();

    add_action(place, "place");
    add_action(place, "put");
    add_action(place, "insert");
}
