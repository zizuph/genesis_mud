/*
 * /d/Gondor/common/dwarf_guild/obj/tablet.c
 *
 * This tablet will be placed in the room join.c for all interested
 * dwarves to read.
 *
 * /Mercade, 10 January 1994
 *
 * Revision history:
 */

#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <composite.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../dwarf.h"

#define MORE_OBJ         "/std/board/board_more"
#define TABLET_ID        (DWARVEN_RACE_GUILD_PREFIX + "tablet_")
#define MINIMUM_LANGUAGE (30)

/* Yeah.. It is ugly. This array has to be updated manually. */
#define CHAPTERS ({ "Information", "Rules", "Membership", "Leaving" })

/*
 * Prototype.
 */
int do_read(string str);

void
create_object()
{
    set_name("tablet");
    add_name("stone");
    add_name(TABLET_ID);

    set_pname("tablets");
    add_pname("stones");

    add_adj("stone");
    add_adj("old");
    add_adj("weathered");

    set_short("stone tablet");

    set_long("It is a stone tablet. In it you see some runic writing " +
	"engraved in it. It looks old and weathered, even though it " +
	"probably has not seen the sun for a very long time. Scanning " +
	"the text, you notice the writing contains information on the " +
	"guild.\n");

    FIX_EUID;

    add_item( ({ "runes", "writing", "runic writing" }),
	"You might be able to read the runic writing on the tablet.\n");

    add_prop(OBJ_I_VOLUME,  20000);
    add_prop(OBJ_I_WEIGHT, 150000);
    add_prop(OBJ_I_VALUE,    1070);
    add_prop(OBJ_M_NO_SELL, "The tablet is not to be sold.\n");
    add_prop(OBJ_M_NO_BUY,  "The tablet is not to be bought.\n");
    add_prop(OBJ_M_NO_GET,  "Do you want to help yourself to a hernia?\n");
    add_prop(OBJ_S_WIZINFO,
	"Just read the tablet and find out. All you need is more than " +
	MINIMUM_LANGUAGE + " in SS_LANGUAGE or be a Dwarf to be able to " +
	"read it.\n");
}

void
init()
{
    ::init();

    add_action(do_read, "read");
}

int
do_read(string str)
{
    object tp = TP;
    string topic;

    if (!strlen(str))
    {
	NF0("What do you want to read?\n");
    }

    str = LOW(str);

    if (parse_command(str, ({ }), "[the] [stone] 'tablet'"))
    {
	write("Read the runic writing, not the tablet.\n");
	return 1;
    }

    if ((tp->query_race() != "dwarf") &&
	(tp->query_skill(SS_LANGUAGE) <=
	    (MINIMUM_LANGUAGE + random(MINIMUM_LANGUAGE / 3))))
    {
	write("You are unable to decipher the runic writing on the tablet.\n");
	return 1;
    }

    if (parse_command(str, ({ }),
	"[the] [runic] 'writing' / 'topics' [on] [the] [stone] [tablet]"))
    {
	write("Reading the runic writing on the stone tablet you discover " +
	    "that there are several topics to read and that you can read " +
	    "the runic writing on each individual topic.\n");
	write("The possible topic" +
	    ((sizeof(CHAPTERS) == 1) ? " is " : "s are ") +
	    COMPOSITE_WORDS(CHAPTERS) + ".\n");
	return 1;
    }

    if (parse_command(str, ({ }), "[the] [runic] [writing] [on] [the] " +
	"[stone] [tablet] [on] / [about] [the] [topic] %s", topic) != 1)
    {
	NF0("What do you want to read the runic writing on?\n");
    }

    if (member_array(CAP(topic), CHAPTERS) == -1)
    {
	NF0("You seem unable to locate the topic \"" + topic +
	    "\" on the tablet.\n");
    }

    if (file_size(DWARVEN_RACE_GUILD_TEXT + topic) <= 0)
    {
	write("The topic \"" + topic + "\" should exist, but it does not. " +
	    "Please make a bugreport about this.\n");
	return 1;
    }

    TP->more(read_file(DWARVEN_RACE_GUILD_TEXT + topic));

    return 1;
}
