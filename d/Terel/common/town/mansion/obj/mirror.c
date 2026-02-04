/* Dust 920814: Mirror for teh blue room. No special meaning,
 * just for fun..
 */
inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

string
pronoun()
{
    if (this_player()->query_gender()) return("she");
    return("he");
}

string
Pronoun()
{
    if (this_player()->query_gender()) return("She");
    return("He");
}

string
reverse(string s)
{
    string *orig, *dest;
    int siz,i;

    orig = explode(s,"");
    siz = sizeof(orig);
    dest = allocate(siz);
    for (i=0; i<siz; i++)
	dest[i] = orig[siz-i-1];
    return implode(dest,"");
}

create_object()
{
    set_name("mirror");
    set_short("mirror");
    set_adj("blue");
    set_long(break_string("This is a blue mirror hanging on " +
	"the north wall. Well, actually " +
	"you are not sure if it's really blue, or if it's only " +
	"because of the blue light in this room. " +
	"You see the picture " +
	"of a strange figure in the mirror.\n",70));
    add_item("figure","@@figure");
    add_cmd_item("mirror",({ "break","rub","ask" }),
	({ "@@brk", "@@rub", "@@ask" }) );
    add_prop(OBJ_I_NO_GET,reverse("The blue mirror can't be taken.") + "\n");
}

string
brk() {
    return(break_string(reverse("You try to break the mirror... " +
		"but the figure behind the mirror seems to do the same... " +
		pronoun() + " looks so ugly and scary that you don't " +
		"dare to go on...") + "\n", 70));
}

string
rub() {
    return(reverse("You rub the mirror... did you expect it opens??") + "\n");
}

string
ask() {
    return(reverse("The mirror says: You're the ugliest in the whole " +
		"country.") + "\n");
}

string
figure()
{
    return(break_string(reverse("You see an ugly, wrinkled " +
	this_player()->query_race_name() +
	" staring at you. What a jerk! " + Pronoun() + " looks like " +
	"a water corpse.") + "\n",70));
}

