/*
 *  Union lanthorn room
 *  Created by Lilith in July, 2004
 *
 *  Revisions:
 *    Lucius, Aug 2017: Recoded and changed candle handling.
 *    Zizuph, Oct 2022: Changed to re-stock one candle once an 
 *                       hour rather than once a day so members
 *                       can get to the Well of Souls to visit
 *                       Raelle's statue more often.
 */
#pragma strict_types
#include "../defs.h"
#include "/d/Avenir/include/macros.h"

inherit BASE;

#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <stdproperties.h>

#define LANTHORN	(GUILDLOG + "lanthorn")
// Set at 1 once per hour 
#define INTERVAL	3600


public string *phrases = ({
    "Tend the lanthorn, for it shall light the way to eternal "+
	"remembrance.",
    "Whosoever embraces the shadows shall know revelations.",
    "With thine presence dost thou cast illumination before "+
	"the darkness and companionship amongst the shadows.",
    "Shadows and steel shall part before the blue flame.",
    "May you govern your passions with absolute sway,\n"+
	"And grow wiser and stronger as your impuritues burn away.",
    "The Eight Passions of Jazur are ardor, ecstacy, fury, "+
	"fidelity, anguish, loathing, ambition, and zeal."
});

public object lanthorn;
public int words, ex, op, count;

public mapping candles = ([
    "Ambition" : 0,
     "Anguish" : 0,
       "Ardor" : 0,
     "Ecstacy" : 0,
    "Fidelity" : 0,
        "Fury" : 0,
    "Loathing" : 0,
        "Zeal" : 0,
]);

private int
expired(int val)
{
    if (time() > (INTERVAL + val))
	return val;
}

public int
avenir_time(int year, int week, int day, int hour)
{

    if (count < 8)
    {
	mapping used = filter(candles, expired);

	if (m_sizeof(used))
	{
	    string which = one_of_list(m_indices(used));
	    candles[which] = 0;
	    count++;
	    year++;

	    tell_room(TO, "A shadow flits through the room and after "+
		"it has passed, a small blue candle can be seen in the "+
		"corner marked by the "+ which +" glyph.\n");
	}
    }

    if (!year)
    {
	tell_room(TO, "The shadows in each of the corners dance and "+
	    "slide in an enigmatic pattern.\n");
    }

    return 1;
}

public string
cand_desc(void)
{
    string one, two;

    switch(count)
    {
    case 0:  one = "none";
	     two = "is there";
	break;
    case 8:  one = "each";
	     two = "there is";
	break;
    default: one = LANG_WNUM(count);
	     two = "there is";
	break;
    }

    return " On the floor in "+ one +" of the eight corners "+
	two +" a blue candle.";
}

public string
glyph_desc(void)
{
    if (count == 0)
	return "";

    if (count == 8)
    {
	return " Each of the glyphs has a blue candle sitting "+
	    "at its point.";
    }

    string *used = m_indices(filter(candles, identity));
    int size = sizeof(used);

    return " The glyph" + (size == 1 ? "" : "s") +" for "+
	COMPOSITE_WORDS(sort_array(used)) +" "+ (size == 1 ?
	    "is missing a candle at its point" :
	    "are missing candles at their points") +".";
}

public void
reset_room()
{
    if (!present("lanthorn"))
    {
	lanthorn = clone_here(OBJ + "lanthorn");
	lanthorn->move(TO);
    }

    lanthorn->reset_lanthorn();
}

public void
union_room(void)
{
    set_short("an eight-cornered room");
    set_long("A lanthorn depends from the ceiling by a thick "+
      "spiral of iron chain, hanging above the floor at chest-height."+
      "@@lanth_desc@@ There are eight corners in this room, and in "+
      "those corners shadows dance and slide in a complex, ritualistic "+
      "pattern. Most of the walls are made of a dark limestone that "+
      "retains the faintest blue tint, and a series of inscriptions "+
      "have been etched into them. An eight-pointed star has been "+
      "carved into the floor directly below the lanthorn. An enigmatic "+
      "air of expectancy, of pregnant mystery, pervades this space, "+
      "filling you with a growing sense of wonder and anticipation."+
      "@@door_desc@@@@op_desc@@\n");

    add_item(({"star", "eight-pointed star", "point", "points"}),
	"This star is identical to the one painted on the ceiling "+
	"of the conference room. At the apex of each point is a "+
	"different glyph.\n");
    add_item(({"glyph", "glyphs", "rune", "symbol" }),
	"Each glyph represents one of the Eight Passions of Jazur: "+
	"Ardor, Ecstacy, Fury, Fidelity, Anguish, Loathing, "+
	"Ambition, and Zeal.@@glyph_desc@@\n");
    add_item(({"corner", "corners"}),
	"Shadows dance in a complex pattern.@@cand_desc@@\n");
    add_item(({"candle", "blue candle", "candles", "blue candles"}),
	"The candles appear to be made from soft blue wax. They "+
	"are short and rather wide.\n");
    add_item(({"outline"}),
	"It is a circular outline in the west wall.\n");
    add_item("west wall",
	"It looks just like the east wall.@@wall_desc@@\n");
    add_item("east wall", "It looks much like the west wall, "+
	"being made of a darkened steel. Its surface is marked "+
	"as though it has been touched in multiple places by "+
	"an open flame.@@east_desc@@\n");
    add_item(({"wall","walls"}),
	"There are eight of them, each facing a cardinal direction.\n");
    add_item(({"north wall", "south wall", "northeast wall",
	"southwest wall", "northwest wall", "southeast wall",
	"limestone" }),
	"It is made of dark limestone with a faint bluish tint.\n");
    add_item(({"indentation", "center"}),
	"There is an indentation in the center panel of the west "+
	"wall, not unlike the one in the blue room with the tablet.\n");
    add_item(({"floor","ground"}),
	"The floor is made from solid granite, dark and hard. "+
	"An eight-pointed star has been carved into it.\n");
    add_item(({"word","words","wall","inscription","inscriptions",
	    "etchings"}), "@@words@@");
    add_item(({"shadow", "shadows", "pattern"}),
	"The shadows move in a pattern whose meaning is just beyond "+
	"your grasp. There is no doubt in your mind that they are as "+
	"sentient as you are.\n");
    add_item("ceiling", "It is made of the same bluish limestone as the "+
	"walls. It is unadorned save for the lanthorn hanging by a chain "+
	"from it.\n");
    add_item(({"chain", "iron chain", "thick iron chain"}),
	"This chain is made of iron. It supports the lanthorn that hangs "+
	"in the center of the room.\n");

    add_cmd_item(({"word","words","wall","inscription","inscriptions",
	    "etchings"}), "read", "@@words@@");
    add_cmd_item(({"indentation", "small indentation"}),
	({ "touch", "feel" }), "Running your fingers along the "+
	"indentation, you grow certain that your sphere would fit "+
	"perfectly if it was placed in it.\n");
    add_cmd_item(({"shadow", "shadows", "the shadow", "the shadows"}),
	({"embrace", "grasp"}),
    "You embrace the shadow and its nature is revealed "+
	"unto you: it is the essence of one who came before you, a "+
	"warrior no longer enfleshed and yet not at rest, who serves "+
	"Jazur and the Union through bonds of passion that transcend "+
	"your comprehension.\n");
    add_cmd_item(({"wall","walls","limestone", "west wall",
	"east wall", "north wall", "south wall", "northeast wall",
	"southwest wall", "northwest wall", "southeast wall" }),
	({"touch","feel"}), "You can feel that most of the walls are "+
	"made of stone, while the east and west walls seem metallic. "+
	"Your sensitive fingertips notice a small indentation "+
	"in the west wall, not unlike the one in the blue room "+
	"with the tablet.\n");

    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_S_DARK_LONG, "You are enveloped by a darkness whose "+
      "silence seems to pound in your ears.\nThe darkness is so "+
      "complete that you have lost your sense of direction. You "+
      "will have to feel your way out or find a ready source of "+
      "illumination.\n");

    count = 8;
    words = random(sizeof(phrases));
    LIST->notify_time(TO);
    reset_room();
}

public string
lanth_desc(void)
{
    if (!op) return "";
    return " A radiant light shines from within it, "+
	"casting fragments of luminescent blue along the walls.";
}

public string
door_desc(void)
{
    if (!ex) return "";
    return " A section of the west wall has opened up, "+
	"leading into a very large room.";
}

public string
wall_desc(void)
{
    if (strlen(door_desc()))
	return door_desc();

    return " In the center of the west wall you can see the "+
	"large, circular outline of a panel of sorts, "+
	"with an indentation in the center not unlike "+
	"the one in the blue room with the tablet.";
}

public string
words(void)
{

    if (!IS_MEMBER(TP))
	return "They are all indecipherable.\n";

    if (++words >= sizeof(phrases))
	words = 0;

    return "One of the inscriptions reads:\n"+
	break_string(phrases[words], 55, 5) +"\n";
}

/*
 * Function name: do_get
 * Description:   get a candle from a corner
 */
public int
do_get(string str)
{
    object candle;

    notify_fail("Get what from where?\n");
    if (!str || !strlen(str))
	return 0;

    if (parse_command(str, ({ }), "[a] / [one] [of] [the] [small] "+
	    "[blue] 'candle' / 'candles'"))
    {
	write("Get a candle from where?\n");
	return 1;
    }

    if (!parse_command(str, ({ }), "[a] / [one] [of] [the] [small] "+
	    "[blue] 'candle' / 'candles' [from] [the] / [a] 'corner'"))
	return 0;

    if (count == 0)
    {
	write("There are no candles left to "+ query_verb() +".\n");
	return 1;
    }

    str = one_of_list(m_indices(filter(candles, not)));
    candles[str] = time();
    count--;

    write("You reach down into the corner marked with the glyph for "+
       str +" and remove the small blue candle from it.\n");
    say(QCTNAME(TP) +" reaches down into the corner marked with the "+
	"glyph for "+ str +" and takes a small blue candle from it.\n");

    candle = clone_object(OBJ + "candle");
    if (candle->move(TP))
	candle->move(TP, 1);

    SCROLLING_LOG(LANTHORN, CAP(TP->query_real_name()) +" took a candle.");
    return 1;
}

public void
rem_exit(void)
{
    if (!ex) return;
    remove_exit("west");

    ex = 0;
    tell_room(TO, "The section of the west wall slides closed silently.\n");

/* Silent for now.
    tell_room(ROOM + "meeting", "The opening in the east wall "+
	"closes silently.\n");
 */
}

public int
open_exit(void)
{
    if (ex) return 0;
    add_exit("meeting", "west");

    tell_room(TO, "The circular panel in the west wall twists "+
	"noislessly open.\n");

/* Silent for now.
    tell_room(ROOM + "meeting", "The mural on the east wall "+
	"wavers and then twists open.\n"\n");
 */

    set_alarm(6.0, 0.0, rem_exit);
    return (ex = 1);
}

public int
place(string str)
{
    string what;
    object *obs, ob;

    NF(CAP(query_verb()) + " what where?\n");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({}), "[the] %s 'in' / 'into' "+
	    "[the] 'hole' / 'indentation'", what))
	return 0;

    obs = FIND_STR_IN_OBJECT(what, TP);
    if (!sizeof(obs))
	return 0;

    ob = obs[0];

    NF(CAP(LANG_THESHORT(ob)) + " does not fit.\n");
    if (!ob->id(TOKEN_ID))
	return 0;

    NF("Nothing happens.\n");
    if (ex) return 0;

    write("You " + query_verb() + " the sphere in the indentation.\n");
    say(QCTNAME(TP) + " " + LANG_PWORD(query_verb()) + " " +
	LANG_ASHORT(ob) + " into the indentation in the west wall.\n");

    open_exit();
    return 1;
}

public string
op_desc(void)
{
    if (!op) return "";
    return " A section of the east wall has opened up, leading "+
	"into darkness.";
}

public string
east_desc(void)
{
    if (strlen(op_desc()))
	return op_desc();
    else
	return "";
}

public void
rem_east(void)
{
    if (!op) return;
    remove_exit("east");

    op = 0;
    tell_room(TO, "The open section of the east wall slides "+
	"closed silently.\n");
}

public int
open_east(void)
{
    if (op) return 0;

    add_exit("lanth_stairt", "east");
    set_alarm(0.5, 0.0, &tell_room(TO,
	    "A section of the east wall slides open.\n"));

    return (op = 1);
}

public void
catch_lanthorn_got_flame(void)
{
    open_east();
    SCROLLING_LOG(LANTHORN, CAP(TP->query_real_name()) +
	" lit the lanthorn.");
}

public void
catch_lanthorn_lost_flame(void)
{
    rem_east();
}

public void
init(void)
{
    ::init();

    add_action(place,  "put");
    add_action(place,  "place");
    add_action(place,  "insert");
    add_action(do_get, "get");
    add_action(do_get, "take");
}

public int
query_prevent_snoop(void)
{
    return 1;
}

public string
union_hook_sway_msg(int phase, object ob)
{
    switch(phase)
    {
    case -1: return "Speak to no one of these mysteries, lest your tongue "+
	"wither and your passions fade in the shadow of Jazur's "+
	"displeasure.";
    case 1:  return "Oh Tornu, art thou ready to delve the mysteries?";
    case 2:  return "The solving of one mystery opens the door to another.";
    case 3:  return "That which lies beyond can be seen by the candlelight of "+
	"the Flame.";
    case 4:  return "Where passions dwell in darkness, there is the spirit "+
	"of Jazur.";
    case 5:  return "Memories of the flesh stand as stone, guarding "+
	"the soul of unity and the eight points of Her passion.";
    }

    return "";
}

public string
union_hook_sway_msg_other(int phase, object ob)
{
    switch(phase)
    {
    case -1: return "The almost-sound fades from your awareness.";
    case 1:  return "You hear a rushing sound, the sound of wind through reeds.";
    case 4:  return "A blue flame ignites before your eyes, then receeds "+
	"as suddenly as it appeared.";
    }

    return "";
}
