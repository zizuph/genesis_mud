inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>


/*
 * The following macros are intended to prevent lines from wrapping
 * around the screen, and avoid the wizard from having to put in explicit 
 * \n's.
 */

#define BSN(s) break_string((s) + "\n",70)
#define BSNN(s) break_string((s) + "\n\n",70)

int opened;

create_object()
{
    set_name("book");
    set_adj("black");
    set_adj("old");
    set_short("black book");
    set_long(BSN("This is a very old looking, black book. All pages of " +
	"it are black. The letters however appear in scarlet-red, as " +
	"if they were written with blood. Who knows, maybe they really " +
	"ARE written with blood... But the most unusual about the book " +
	"is that it is floating magically in the air with no table below it." +
	" You can't move it...."));
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_NO_GET,
	BSN("You try to get the book, but it seems you can't move it from " +
	    "it's place where it's floating magically."));
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    opened = 0;
}

reset_object()
{
    opened = 0;
}

init()
{
    ::init();
    add_action("do_read","read");
    add_action("do_open","open");
    add_action("do_close","close");
    add_action("do_cast","cast");
}

do_cast(string str)
{
    int success;

    notify_fail("Cast what?\n");
    if (str != "spell" && str != "conjuration spell")
	return 0;
    notify_fail("I don't see any spell to cast...\n");
    if (!opened) return 0;
    if (this_player()->query_mana() < 50)
    {
	write("You don't feel strong enough to cast the spell.\n");
	return 1;
    }
    this_player()->add_mana(-50);
    success = this_player()->resolve_task(TASK_DIFFICULT,
	({SKILL_WEIGHT, 25, SS_SPELLCRAFT,
	  SKILL_WEIGHT, 50, SKILL_MIN, SS_WIS, SS_INT, SKILL_END,
	  SKILL_WEIGHT, 25, SS_FORM_CONJURATION}));
    if (success > 0)
    {
	say(QCTNAME(this_player()) + " casts a spell with success.\n");
	write(BSN("You concentrate yourself and get together all " +
		"your power... and you succeed to cast the spell " +
		"with success!\n"));
	environment(this_player())->call_death();
    }
    else
    {
	say(QCTNAME(this_player()) + " tries to cast a spell, but fails.\n");
	write(BSN("You concentrate yourself and get together all " +
		"your power... but nothing seems to happen.\n"));
    }
    return 1;
}

do_read(string str)
{
    if (str == "spell" && opened)
    {
	write("You read the spell, but it doesn't make sense to your mind.\n");
	return 1;
    }
    notify_fail("Read what?\n");
    if (str != "book" && str != "black book" && str != "old book")
	return 0;
    if (!opened)
    {
	write("You just see a pentagram on the cover of the book.\n");
	return 1;
    }
    say(QCTNAME(this_player()) + " reads the black book.\n");
    write(BSN("You don't understand most of the runes you find on " +
	"the black pages. In the middle of it, however, you find " +
	"something that looks like a conjuration spell. However, " +
	"you are not sure if you understand how to pronounce it..."));
    return 1;
}

do_open(string str)
{
    notify_fail("Open what?\n");
    if (str != "book" && str != "black book" && str != "old book")
	return 0;
    notify_fail("But the black book is already open.\n");
    if (opened) return 0;
    say(QCTNAME(this_player()) + " opens the black book.\n");
    write("You open the black book. A shiver goes through your body.\n");
    opened = 1;
    return 1;
}

do_close(string str)
{
    notify_fail("Close what?\n");
    if (str != "book" && str != "black book" && str != "old book")
	return 0;
    notify_fail("But the black book is already closed.\n");
    if (!opened) return 0;
    say(QCTNAME(this_player()) + " closes the black book.\n");
    write("As you close the black book, you feel relieved.\n");
    opened = 0;
    return 1;
}
