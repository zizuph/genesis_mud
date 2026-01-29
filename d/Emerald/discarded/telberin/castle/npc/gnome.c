/*
 * /d/Emerald/room/vamp/gnome.c
 *
 * This gnome knows everything about genealogy. He is specialized in the
 * pedigree of the members of the Vampyre Guild.
 *
 * /Mercade, 8 April 1994
 *
 * Revision history:
 */

#pragma no_inherit
#pragma strict_types

inherit "/std/monster";

#include <const.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#define MORE_OBJ    "/std/board/board_more"

#define BSN(text)   (break_string((text), 75) + "\n")
#define PRICE(coin) (random((coin) / 2) + ((coin) * 3 / 4))
#define STAT(num)   (random((num) * 2 / 3) + ((num) * 2 / 3))
#define SAY(text)   command("say " + (text))

#define NONMET      (this_player()->query_nonmet_name())
#define MY_NAME     (this_player()->query_real_name())

#define MINIMUM_COLUMN_WIDTH   23
#define COPPERS_PER_SILVER     12

#define ANCESTORS_NO_VAMPYRE    5
#define ANCESTORS_DARKNESS     15
#define ANCESTORS_LIVINGS      10

#define RELATION_NO_VAMPYRE     5
#define RELATION_VAMPYRES      10

#define DESCENDANTS_NO_VAMPYRE  5
#define DESCENDANTS_VAMPYRE    15

#define DOTS   ". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . "
#define SPACES "                                                            "

static int only_value;

void
create_monster()
{
    add_name("genealogist");
    set_adj("distinguished");
    add_adj("smart-looking");
    add_adj("smart");
    add_adj("looking");

    set_race_name("gnome");
    set_pname("gnomes");
    set_gender(G_MALE);

    set_short("distinguished smart-looking gnome");
    set_long(BSN("This gnome is very smart-looking. He is a master " +
	"in genealogy and he has many books, filled with information " +
	"on people, their ancestors and descendants. Ask him the right " +
	"question and he will tell you everything he knows. At a fair " +
	"price naturally."));

    set_stats( ({ STAT( 40),
		  STAT( 50),
		  STAT( 50),
		  STAT( 75),
		  STAT( 75),
		  STAT( 40) }) );

    add_prop(OBJ_M_NO_ATTACK  , "@@obj_m_no_attack");
    add_prop(OBJ_M_NO_TELEPORT, 1);
    add_prop(OBJ_S_WIZINFO,
	BSN("This gnome knows everything about genealogy. He is specialized " +
	"in the pedigree of the members of the Vampyre Guild. For his " +
	"presence on this donut and his skills, he owes gratitude to " +
	"Mercade."));
}

mixed
obj_m_no_attack()
{
    command("laugh");
    SAY("If you kill me now, " + NONMET + ", I will never be able to help " +
	"you with my knowledge on genealogy, so I am sure that you will " +
	"be sensible and not attack me.");

    return "";
}

string
query_nonmet_name()
{
    return "distinguished smart-looking gnome";
}

int
compute(int number, int price)
{
    int value = 0;
    int index;

    for (index = 0; index < (number * 2); index += 2)
    {
	value += (price - ((index >= price) ? 2 : index));
    }

    return value;
}

int
cannot_pay(int price)
{
    /* Remove the money from the player if (s)he can pay me.
     */
    if (MONEY_ADD(this_player(), -(price * COPPERS_PER_SILVER)))
    {
	write(BSN("You pay " + query_nonmet_name() + " his fee, " +
	    price + " silver coins."));
	return 0;
    }

    SAY("Excuse me, " + NONMET +
	", but you are not rich enough to pay my fee.");
    return 1;
}

void
more(string to_write)
{
    string *lines = explode(to_write, "\n");
    int     scrw = this_player()->query_prop(PLAYER_I_SCREEN_WIDTH);
    int     index = 0;
    int     largest = 0;

    if (scrw == 0)
    {
	scrw = 80;
    }

    if (sizeof(lines) >= 10)
    {
	for (index = 0; index < sizeof(lines); index++)
	{
	    if (strlen(lines[index]) > largest)
	    {
		largest = strlen(lines[index]);
	    }
	}

	lines[0] += SPACES[strlen(lines[0])..(MAX((largest + 5),
	    MINIMUM_COLUMN_WIDTH))];

	to_write = sprintf("%-*#s\n", (scrw - 3), implode(lines, "\n"));
    }

    if (sizeof(explode(to_write, "\n")) <= 20)
    {
	write(to_write);
	return;
    }

    seteuid(getuid());
    clone_object(MORE_OBJ)->more(to_write);
}

void
answer_ancestors(string child)
{
    mixed ancestors = FAMILY_TREE->query_ancestors(child);
    string tmp = ((child == MY_NAME) ? "your ancestors" :
	"the ancestors from " + capitalize(child));

    if (ancestors == 0)
    {
	if (only_value)
	{
	    SAY("The information about " + tmp + ", " + NONMET +
		", would cost you approximately " +
		PRICE(ANCESTORS_NO_VAMPYRE) + " silver coins.");
	    return;
	}

	if (cannot_pay(ANCESTORS_NO_VAMPYRE))
	{
	    return;
	}

	SAY("About " + tmp + ", " + NONMET +
	    ", I have no information in my register.");
	return;
    }

    if (!pointerp(ancestors))
    {
	SAY("Excuse me, " + NONMET + ". My documents are not in order. I " +
	    "cannot give you accurate information on " + tmp + ". " +
	    "Please make a bugreport about this and do not forget to add " +
	    "the exact question you asked.");
	return;
    }

    if (!sizeof(ancestors))
    {
	if (only_value)
	{
	    SAY("The information about " + tmp + ", " + NONMET +
		", would cost you approximately " +
		PRICE(ANCESTORS_DARKNESS) + " silver coins.");
	    return;
	}

	if (cannot_pay(ANCESTORS_DARKNESS))
	{
	    return;
	}

	SAY(((child == MY_NAME) ? "You were" : capitalize(child) + " is") +
	    " created from utter darkness, " + NONMET + ".");
	return;
    }

    if (only_value)
    {
	SAY("The information about " + tmp + ", " + NONMET +
	    ", would cost you approximately " +
	    PRICE(compute(sizeof(ancestors), ANCESTORS_DARKNESS)) +
	    " silver coins.");
	return;
    }

    if (cannot_pay(compute(sizeof(ancestors), ANCESTORS_DARKNESS)))
    {
	return;
    }

    SAY("Let me give you a list of " + tmp + ", " + NONMET + ".");
    more(implode(map(ancestors, "cap", this_object()), "\n") + "\n");

    return;
}

void
answer_relation(string child, string parent)
{
    int relation = FAMILY_TREE->is_ancestor(parent, child);

    if (relation == 0)
    {
	relation = FAMILY_TREE->is_ancestor(child, parent);
    }
    else
    {
        relation = 2;
    }

    if (only_value)    
    {
	SAY("Information about the relation between those two people will " +
	    "cost you approximately " + ((relation == 0) ?
	    PRICE(RELATION_NO_VAMPYRE) : PRICE(RELATION_VAMPYRES)) +
	    " silver coins, " + NONMET + ".");
	return;
    }

    if (relation == 0)
    {
	if (cannot_pay(RELATION_NO_VAMPYRE))
	{
	    return;
	}

	SAY("At least one the people you asked about is not in my books, " +
	    NONMET + ".");
	return;
    }

    if (cannot_pay(RELATION_VAMPYRES))    
    {
	return;
    }

    SAY(capitalize((child == MY_NAME) ? "You are" : parent + " is") +
	((relation == 1) ? " a descendant from " : " an ancestor of ") +
	((parent == MY_NAME) ? "you" : capitalize(child)) + ".");
}

string
list_descendants(mixed descendants, int depth)
{
    int    index;
    string to_write = "";

    if ((!sizeof(descendants)) || (depth >= 30))
    {
	return "";
    }

    for (index = 0; index < sizeof(descendants); index += 2)
    {
	to_write += (DOTS[0..((depth * 2) + 1)] +
	    capitalize(descendants[index]) + "\n" +
	    list_descendants(descendants[(index + 1)], (depth + 1)));
    }

    return to_write;
}

void
answer_descendants(string parent)
{
    mixed descendants = FAMILY_TREE->query_descendants(parent);
    string tmp = ((parent == MY_NAME) ? "your descendants" :
	"the descendants from " + capitalize(parent));

    if (descendants == 0)
    {
	if (only_value)
	{
	    SAY("The information about " + tmp + ", " + NONMET +
		", would cost you approximtely " +
		PRICE(DESCENDANTS_NO_VAMPYRE) + " silver coins.");
	    return;
	}

	if (cannot_pay(DESCENDANTS_NO_VAMPYRE))
	{
	    return;
	}

	SAY("About " + tmp + ", " + NONMET +
	    ", I have no information in my register.");
	return;
    }

    if (!pointerp(descendants))
    {
	SAY("Excuse me, " + NONMET + ". My documents are not in order. I " +
	    "cannot give you accurate information on " + tmp + ". " +
	    "Please make a bugreport about this and do not forget to add " +
	    "the exact question you asked.");
	return;
    }

    if (!sizeof(descendants))
    {
	if (only_value)
	{
	    SAY("The information about " + tmp + ", " + NONMET +
		", would cost you approximately " +
		PRICE(DESCENDANTS_VAMPYRE) + " silver coins.");
	    return;
	}

	if (cannot_pay(DESCENDANTS_VAMPYRE))
	{
	    return;
	}

	SAY(((parent == MY_NAME) ? "You have" : capitalize(parent) + " has") +
	    " no descendants, " + NONMET + ".");
	return;
    }

    if (only_value)
    {
	SAY("The information about " + tmp + ", " + NONMET +
	    ", would cost you approximately " +
	    PRICE(compute(sizeof(descendants), DESCENDANTS_VAMPYRE)) +
	    " silver coins.");
	return;
    }

    if (cannot_pay(compute(sizeof(descendants), DESCENDANTS_VAMPYRE)))
    {
	return;
    }

    SAY("Let me give you a list of " + tmp + ", " + NONMET + ".");
    more(list_descendants(descendants, 0));
}

void
catch_question(string question)
{
    string parent;
    string child;

    if (!strlen(question))
    {
	return;
    }

    /* Log the question.. I'm just curious :-)
     */
    seteuid(getuid());
    write_file("/d/Emerald/room/keep/log/gnome.log",
	(ctime(time()) + sprintf(" %-12s :",
	    this_player()->query_real_name()) + question + "\n"));

    question = lower_case(question);

    if (sscanf(question, "test %s", question) == 1)
    {
	only_value = 1;
    }
    else
    {
	only_value = 0;
    }

    if (question == "who are my ancestors?")
    {
	answer_ancestors(MY_NAME);
	return;
    }

    if (sscanf(question, "who are the ancestors from %s?", child) == 1)
    {
	answer_ancestors(child);
	return;
    }

    if (sscanf(question, "is %s related to me?", child) == 1)
    {
	answer_relation(child, MY_NAME);
	return;
    }

    if (sscanf(question, "is %s related to %s?", child, parent) == 2)
    {
	answer_relation(child, parent);
	return;
    }

    if (question == "who are my descendants?")
    {
	answer_descendants(MY_NAME);
	return;
    }

    if (sscanf(question, "who are the descendants from %s?", parent) == 1)
    {
	answer_descendants(parent);
	return;
    }

    command("ponder");
    SAY("Excuse me, " + NONMET + ", but I fail to understand your question.");

    if (question[strlen(question) - 1] != "?"[0])
    {
	SAY("Maybe you forgot the question mark?");
    }
}

string
cap(string str)
{
    return capitalize(str);
}
