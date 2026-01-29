// Ziggurat makeover salon (ZIG_RL3 + "makeovers.c")
// creator(s):   Zielia 2006
// last update:
// purpose:      Ziggurat shop where players can obtain makeovers.
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"
#include <macros.h>

#define MIST present(keeper, TO)
#define BLINDED(x)  present("rynal::blind", x)

inherit ZIG_ROOM;

private static int no_attack;
private static object keeper;

public string
mist_tells(void)
{
    set_tell_time(480);

    add_tell(({"An icy tendril of mist caresses your cheek sending "+
	"delicious shivers down your spine.\n",
	"The fog swirls about you in graceful patterns.\n",
	"A thick patch of mist drifts before your eyes making "+
	"it hard to see anything for a moment.\n",
	"A hazy globe of light drifts closer to you. Suddenly it "+
	"seems to disappear only to reappear across the room.\n",
	"Out of the corner of your eye you see a figure emerge "+
	"and then disappear back into the fog.\n"}));
}

public void
set_no_attack(int i)	{ no_attack = i; }

private int
check_no_attack(void)	{ return no_attack; }

private void
reset_npc(object npc)
{
    keeper = npc;
    mist_tells();
}

public void
zig_room(void)
{
    set_short("@@my_short");
    set_long("@@my_long");

    add_prop(ROOM_S_DARK_LONG, "@@my_dark_long");
    add_prop(ROOM_S_DARK_MSG, "@@my_dark_msg");
    add_prop(ROOM_M_NO_ATTACK, check_no_attack);

    add_item(({"pedestal",			}),	"@@see_pedestal");
    add_item(({"bowl","bowls",			}),	"@@see_bowls"	);
    add_item(({"cloth","cloths","stack","pile"	}),	"@@see_cloths"	);
    add_item(({"stool","stools",		}),	"@@see_stool"	);
    add_item(({"figures","figure"		}), 	"@@see_figures"	);
    add_item(({"light","lights",		}), 	"@@see_lights"	);
    add_item(({"globe","globes",		}), 	"@@see_globes"	);
    add_item(({"floor","ground",		}), 	"@@see_floor"	);
    add_item(({"ceiling",			}), 	"@@see_ceiling"	);
    add_item(({"mirror",			}), 	"@@see_mirror"	);
    add_item(({"reflections",			}), 	"@@reflect_room");
    add_item(({"reflection"			}), 	"@@reflect_me"	);
    add_item(({"walls","stone walls","wall",
	"stone wall","mirrors"			}),	"@@see_walls");
    add_item(({"mist","fog","smoke","fingers",
	"tendrils","nimbus",			}),	"@@see_mist");

    add_cmd_item(({"on stool","on stools","stool","stools"}),"sit",
	"@@sit_stool");

    add_exit("room1", "east", 0);

    add_npc(ZIG_MON + "rynal", 1, reset_npc);

}

public string
my_short(void)
{
    if (MIST)
	return "A mist filled salon";
    else
	return "A stark shop";
}

public string
my_long(void)
{
    if (MIST)
    {
	return "Surreal grey fog swirls around you, caressing you with "+
	    "ethereal fingers and clouding your vision. The room is "+
	    "almost cold compared to the warmth of the galleria "+
	    "outside. The fog obscures the details of the room but seems "+
	    "to purposefully part at the center, revealing an impressive "+
	    "figure who could only be Ry'nal himself.\n";
    }
    else
    {
	return "The room seems oddly vacant. Dimly lit mirrors line the "+
	    "black stone walls. A grey marble pedestal stands in the center "+
	    "of the room near the back and holds several clay bowls and a "+
	    "stack of folded white cloths. Next to the pedestal stands a "+
	    "grey stool, which looks to be carved of the same marble.\n";
    }
}

public string
my_dark_long()
{
    if (BLINDED(TP))
	return "All you can see is bright white mist swirling around you.\n";

    return "A dark room.\n";
}

public string
my_dark_msg()
{
    if (BLINDED(TP))
	return "Bright white fog blinds your eyes making you unable to";

    return "It is too dark to";
}

public void
enter_inv(object ob, object from)
{
    if (MIST)
    {
	if (BLINDED(ob))
	{
	    BLINDED(ob)->blind_me();
	}
	else
	{
	    ob->catch_tell("Wisps wonderfully cool fog curl around you, "+
		"drawing you inward.\n");
	}
    }

    ::enter_inv(ob, from);
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (MIST)
    {
	if (BLINDED(ob))
	{
	    BLINDED(ob)->unblind_me();
	    ob->catch_tell("You blink your eyes, forcing the remnants of "+
		"mist from your vision.\n");
	}
    }
}

public string
see_pedestal(void)
{
    if (MIST)
        return "You find no pedestal.\n";

    return "It is an elegant pedestal crafted out of smooth grey "+
	"marble that could easily go unnoticed if the fog were "+
	"slightly thicker. Atop the pedestal stands a silver chalice, "+
	"seeming highly revered in that place of honor.\n";
}

public string
see_bowls(void)
{
    if (MIST)
        return "You find no bowls.\n";

    return "Three small ceramic bowls rest on the pedestal. One holds "+
	"a bluish liquid. One holds a yellow powder and the last "+
	"holds a fushia paste.\n";
}

public string
see_cloths(void)
{
    if (MIST)
        return "You find no cloths.\n";

    return "A stack of folded, white linen cloths sits on the pedestal "+
	"next to three ceramic bowls.\n";
}

public string
see_stool(void)
{
    if (MIST)
        return "You find no stool.\n";

    return "The stool is made of grey marble and doesn't look very "+
	"comfortable.\n";
}

public string
sit_stool(void)
{
    if (MIST)
        return "You see no stool.\n";

    return "The stool doesn't look comfortable enough to bother.\n";
}

public string
see_mist(void)
{
    if (MIST)
    {
        return "Cool tendrils of mist swirl around the salon making it "+
	    "difficult to see much of anything, including the source of the "+
	    "fog. Odd lights and dark figures appear and disappear into the "+
	    "mist.\n";
    }
    return "You find no mist.\n";
}

string
see_figures(void)
{
    if (MIST)
    {
	return "The mirrors cast dark reflections through the fog, creating "+
	    "the eerie illusion of figures emerging from and melting into "+
	    "the mist.\n";
    }
    return "You find no figures.\n";
}

public string
see_lights(void)
{
    if (MIST)
    {
	return "Hazy globes of light flash and brighten the mist, "+
	    "changing it from diffuse, silvery-grey to white and almost "+
	    "solid looking.\n";
    }
    return "Above each mirror, a small glowing source-crystal is mounted, "+
	"dimly illuminating the reflections for examination.\n";
}

public string
see_globes(void)
{
    if (MIST)
    {
	return "Hazy globes of light flash and brighten the mist, changing it "+
            "from diffuse, silvery-grey to white and almost solid looking.\n";
    }
    return "You find no globes.\n";
}

public string
reflect_me(void)
{
    if (MIST)
    {
	write("Peering through the mist, you can just make out your "+
	    "reflection in one of the mirrors:\n\n"+ TP->long() +"\n");
	say(QCTNAME(TP) +" peers intently through the mist at one of the "+
	    "mirrors.\n");
    }
    else
    {
	write("You stand before one of the mirrors and examine your "+
	    "reflection:\n\n"+ TP->long() +"\n");
	say(QCTNAME(TP) +" stands before one of the full length mirrors "+
	    "and examines "+ HIS(TP) +" reflection.\n");
    }

    return "";
}

public string
reflect_room(void)
{
    if (MIST)
    {
	return "The mirrors cast dark reflections through the fog, creating "+
	    "the eerie illusion of figures emerging from and melting into "+
	    "the mist.\n";
    }
    return "All around the room, tall, lighted mirrors surround you, "+
	"reflecting the room back at you again and again:\n\n"+
	long() +"\n";
}

public string
see_walls(void)
{
    if (MIST)
    {
	return "You can only catch the barest glimpses of the walls through "+
            "the swirling mist. They appear to be made of black stone as is "+
            "typical of the Ziggurat and covered with silvery mirrors.\n";
    }
    return "All around the room, full length mirrors line the black stone "+
	"walls, reflecting the room from all angles. The mirrors are "+
	"lit by Source-crystals mounted into the walls above them.\n";
}

public string
see_mirror(void)
{
    write("You approach one of the mirrors and examine it more closely:\n\n"+
        "It is a full length mirror set into the black stone of the walls. "+
        "Above each mirror, a small glowing source-crystal is mounted, "+
	"dimly illuminating the reflections for examination.\n");

    say(QCTNAME(TP) +" approaches one of the full length mirrors, examining "+
        "it closely.\n");

    return "";
}

public string
see_floor(void)
{
    if (MIST)
    {
	write("You look down to carefully examine the floor:\n\n"+
	    "Through the mist you see that the floor is made of rough black "+
            "stone. Unlike the polished floor of the galleria, the stone "+
            "here is natural and uneven causing you to walk carefully to "+
            "avoid stumbling in the fog.\n");
    }
    else
    {
	write("You look down to carefully examine the floor:\n\n"+
	    "The floor is made of rough black stone. Unlike the polished "+
	    "floor of the galleria, the stone here is natural and uneven.\n");
    }

    say(QCTNAME(TP) +" looks down to carefully examine the floor.\n");
    return "";
}

public string
see_ceiling(void)
{
    if (MIST)
    {
	write("The ceiling is obscured by a hazy, white nimbus.\n");
    }
    else
    {

	write("The ceiling, like the floor, is made of unpolished black "+
	    "stone.\n");
    }

    say(QCTNAME(TP) +" looks up to carefully examine the ceiling.\n");
    return "";
}

/*  Support for Ry'nals quests. */

private static mapping solved = ([]);

public int
query_solved(object player, string which)
{
    string who = player->query_cap_name();

    if (!solved[who])
	return 0;

    return solved[who][which];
}

public void
set_solved(object player, string which)
{
    string who = player->query_cap_name();

    if (!solved[who])
	solved[who] = ([]);

    solved[who][which] = 1;
}
