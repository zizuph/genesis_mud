/*
 * Room of spheres, part of the Union Guru quest
 *
 * This is the third and last puzzle in the area:
 *   In this room, the player must raise the spheres in
 *   the correct sequence. The sequence depends on the
 *   sequence of rooms the player passed through in order
 *   to get through the maze. Since the maze is randomly generated,
 *   the player will first need to find a way to get through it,
 *   and will also need to keep track of the words over the
 *   doorways through which he passed in order to reach the
 *   end of the maze. The words (stored in the player in the
 *   form of a property) are reset each time the player returns
 *   to the beginning of the maze, so he can try repeatedly.
 *
 * Cirion, March 9th, 1997
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/room";

#include <macros.h>
#include <language.h>
#include <composite.h>

public int door;
public string *seq = ({});
public mapping spheres = ([]);


public void
open_door(void)
{
    if (door)
       return;

    tell_room(TO, "A large section of plaster on the western wall "+
	"silently turns to dust.\n");
    tell_room(RESTING, "The eastern wall silently turns to dust.\n");

    door = 1;
    add_exit(RESTING, "west");
    RESTING->add_exit(file_name(TO), "east");
}

public void
close_door(void)
{
    if (!door)
        return;

    tell_room(TO, "The dust at the base of the opening in the west wall "+
	"rises and reforms into solid plaster.\n");
    tell_room(RESTING, "The dust in the eastern opening rises into the "+
	"air and reforms into solid plaster.\n");

    door = 0;
    remove_exit("west");
    RESTING->remove_exit("east");
}

public string
door_desc(void)
{
    if (!door) return "";
    return " Part of the plaster in the western wall has fallen away, "+
	"revealing an opening beyond it.";
}

public string
spheres_desc(void)
{
    int *where = m_values(spheres), raised = sizeof(where);
    string str = " There are "+ LANG_WNUM(raised) +" translucent "+
	"blue spheres arranged in a perfect circle";

    where -= ({ 0 });
    raised = sizeof(where);

    if (!raised)
	str += " resting on the floor.";
    else if (raised == m_sizeof(spheres))
	str += ", all of which are hovering gently above the floor.";
    else
	str += ", "+ LANG_WNUM(raised) +" of which are hovering "+
	    "above the floor.";

    return str;
}

public void
reset_room(void)
{
    string *which = ({ });
    int cnt, *where = m_values(spheres);

    seq = ({ });

    foreach(string sph, int val: spheres)
    {
	cnt++;
	if (!val) continue;

	which += ({ LANG_WORD(cnt) });
	spheres[sph] = 0;
    }

    if (sizeof(which))
    {
	tell_room(TO, "The "+ COMPOSITE_WORDS(which) +" sphere" +
	    (sizeof(which) > 1 ? "s sink " : " sinks") +
	    " to the floor.\n");
    }

    close_door();
}

public string
dir_from_num(int i)
{
    string *dirs = ({ "north", "northeast", "east", "southeast", "south",
                      "southwest", "west", "northwest" });
    int which = i * sizeof(dirs) / m_sizeof(spheres);

    return dirs[which];
}

public string
hover_desc(string which)
{
    if (!spheres[which])
    {
	return "It is resting gently on the floor, as if any movement "+
	    "would send it rolling.\n";
    }

    return "It is hovering "+ LANG_WNUM(spheres[which]) +" inch"+
	(spheres[which] > 1 ? "es" : "") + " above the floor.\n";
}

public void
create_room(void)
{
    int cnt;

    set_short("room of spheres");
    set_long("This is a wide, oval chamber with walls of dull white "+
	"plaster. A strange smell hangs in the air, reminding you of "+
	"a distant memory which you cannot quite grasp.@@spheres_desc@@"+
	"@@door_desc@@ A smooth set of grey stone steps leads up to a "+
	"circular opening in the ceiling.\n");


    /* Initialiaze the state of the spheres */
    foreach(string str: WORDS)
	spheres[str] = 0;

    add_item(({ "sphere", "spheres" }),
	"There are "+ LANG_WNUM(m_sizeof(spheres)) +" translucent blue "+
	"spheres, arranged in a perfect circle in the center of the "+
	"floor. The appear very fragile.\n");

    foreach(string sph: m_indices(spheres))
    {
	cnt++;

	add_item(({ sph + " sphere", "sphere " + LANG_WNUM(cnt),
		LANG_WORD(cnt) +" sphere", sph +" globe",
		"globe "+ LANG_WNUM(cnt), LANG_WORD(cnt) +" globe" }),
	    "It is a fragile globe of thin blue glass, filled with "+
	    "swirling grey smoke. It is near the "+ dir_from_num(cnt - 1) +
	    " side of the room. The smoke seems to form spidery letters "+
	    "in the sphere. "+ VBFC("hover_desc:" + file_name(TO) +
		"|" + sph));

       add_cmd_item(({ sph +" sphere", "sphere "+ LANG_WNUM(cnt),
	       LANG_WORD(cnt) +" sphere", sph +" globe",
	       "globe "+ LANG_WNUM(cnt), LANG_WORD(cnt) +" globe" }),
	   "read", "The letters in the "+ LANG_WORD(cnt) +" sphere "+
	   "read: "+ CAP(sph) + ".\n");
     }

    add_exit("maze18", "up");
    reset_room();
}

public int
compare(string *arr1, string *arr2)
{
    for(int i = 0; i < sizeof(arr1) && i < sizeof(arr2); i++)
    {
	if (arr1[i] != arr2[i])
	    return 0;
    }

    if (sizeof(arr1) == sizeof(arr2))
	return 2;  // exact match
    else
	return 1;  // partial match
}

public int
touch(string str)
{
    int which, comp;
    string sph, *words = ({ });

    NF(CAP(query_verb()) + " what?\n");
    if (!strlen(str))
        return 0;

    str = lower_case(str);
    if (!parse_command(str, ({}), "[the] %s 'sphere' / 'ball' / 'globe'", sph))
        return 0;

    if (strlen(TP->query_prop(WORD_PROP)))
       words = explode(TP->query_prop(WORD_PROP), " ");

    sscanf(sph, "%d", which);

    NF(CAP(query_verb()) + " which sphere?\n");
    if (!which && !(which = LANG_NUMW(sph)) && !(which = LANG_ORDW(sph)))
    {
	which = member_array(sph, m_indices(spheres));
        if (++which == 0)
           return 0;
    }

    which--;

    NF(CAP(query_verb()) + " which sphere?\n");
    if (which >= m_sizeof(spheres))
	return 0;

    write("You lightly touch the "+ LANG_WORD(which + 1) + " sphere.\n");
    say(QCTNAME(TP) + " lightly touches the "+ LANG_WORD(which + 1) +
	" sphere.\n");

    sph = m_indices(spheres)[which];

    seq += ({ sph });
    if (!sizeof(words) || !(comp = compare(words, seq)))
	set_alarm(1.5, 0.0, reset_room);

    if (!spheres[sph]++)
    {
	tell_room(TO, "The sphere slowly rises from the ground until "+
	    "it hovers an inch above the floor.\n");
    }
    else
    {
       tell_room(TO, "The sphere slowly rises further, until it is "+
	   "hovering about " + LANG_WNUM(spheres[sph]) + " inches "+
	   "above the floor.\n");
    }

    if (comp == 2)
	open_door();

    return 1;
}

public void
init(void)
{
    ::init();

    add_action(touch, "touch");
    add_action(touch, "pass");
    add_action(touch, "rub");
}
