/*
 * A scroll with hints for the White Towers quest
 * A bit devious; you have to have a high SS_LANGUAGE to read it
 * properly. Having a SS_LANGUAGE that is too low will result in
 * a garbage text.
 *
 *					Tricky, 28-2-92
 */
inherit "/std/object";

#include "/sys/stdproperties.h"

void
create_object()
{
    set_name("scroll");
    set_pname("scrolls");
    set_adj("white");
    set_short("white scroll");
    set_pshort("white scrolls");
    set_long("@@my_long");

    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 850);
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
}

void
init()
{
    add_action("do_read", "read");
}

/*
 * Function name:   plaintext
 * Description:     The real text that is written on the scroll.
 * Returns:	    Just that.
 */
string
plaintext()
{
    return
	+ "\n"
	+ "          Quaesto Towaeres Blances\n"
	+ "\n"
	+ "      In toweram trappae upsit ambulant,\n"
	+ "      Bockit aquam fillant et returnant,\n"
	+ "      Fuegio expungare necessis habeant,\n"
	+ "      Cle ex serpens porta sudis ovrant,\n"
	+ "      Tendrilo ae alchemistior takebant,\n"
	+ "      In blasto fuegio conjura changant,\n"
	+ "      Torcha blocci aquam duro imeltant,\n"
	+ "      Quae gargoliam mortuararitor zant,\n"
	+ "      Via uppa librio quaesto solutiant.\n"
	+ "\n";
}

string
wizinfo()
{
    return
	  "You need to have SS_LANGUAGE at 33 to see the real text.\n"
	+ "If it is lower, random characters will be scrambled.\n"
	+ "However, since you're a wizard, here it is...\n"
	+ plaintext();
}

string
my_long()
{
    int chance;
    string str;

    chance = 100 - 3*this_player()->query_skill(SS_LANGUAGE));

    str = "The document is written in a strange language.\n";

    if (chance > 0)
	str += "You do not know all characters, you guess it says:\n"
    else
	str += "You are skilled enough in languages to read:\n"

    str += plaintext();

    return scramble(str, chance);
}

int
do_read(string str)
{
    if (id(str))
    {
	write(my_long());
	return 1;
    }
    return 0;
}

/*
 *  The replacement characters are randomly picked from this string.
 */
#define MISS_STR "abcdefghijklmnopqrstuvwxyz"

/*
 * Function name:   scramble
 * Description:	    Scramble a text, dependent on a chance in percent.
 *		    If the chance is > 100, all characters will be scrambled,
 *		    if it is smaller than 0, no characters will be scrambled.
 * Arguments:	    text:   The text to scramble
 *		    chance: A chance in percent that any character in the
 *		    text will be scrambled.
 */
string
scramble(string text, int chance)
{
    int len, i, ran;
    string char;

    text = " " + text  + " ";
    len = strlen(text);

    for (i=1; i<len-1; i++)
    {
	if (chance > (ran = random(100)))
	{
	    char = extract(text, i, i);

	    /* Leave spaces and newlines intact */
	    if (char != " " && char != "\n")
	    {
		/*
		 * Treating the text as an array would be much quicker...
		 * E.g.: text[i] = MISS_STR[ran%26];
		 */
		text = extract(text,0,i-1) + extract(MISS_STR,ran%26,ran%26)
		     + extract(text,i+1,len-1);
	    }
	}
    }
    return extract(text,1,len-2);
}
