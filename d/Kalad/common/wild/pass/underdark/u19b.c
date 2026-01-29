/*
 * /d/Kalad/common/wild/pass/underdark/u19b.c
 * Purpose    : Hide a treasure to be found.
 * Located    : Under Hespyre, near shaft to Dark Dominion
 * Created By : Antharanos
 * Modifed By : Nikklaus, Oct'97: adapted to dark_dom inherit
 */

# pragma strict_types
# include "dark_dom.h"
# include <macros.h>
# include <ss_types.h>
# include <stdproperties.h>

inherit DARK_DOM;

int recently_searched = 0;

string
search_moss(object tp, string str)
{
    if (!strlen(str) || str != "moss" ||
      tp->query_skill(SS_AWARENESS) < random(30))
	return "";

    if (time() < recently_searched + 600)
	return "You thoroughly search through the moss but only manage to "+
	"stain your hands red. You quickly wipe it off on "+
	"one of the rugs.\n";

    recently_searched = time();
    say(QCTNAME(tp)+ " takes something from the moss.\n");
    clone_object(SPARKLE_GEM)->move(tp);
    return "After carefully searching through the moss, you find a "+
    "sparkling gem!\n";
}

void
create_dark_dom()
{
    set_short("Chamber");
    set_long("You seem to have reached what can only be described as a "+
      "birthing chamber. Many crude and smelly furs blanket the stone floor "+
      "of this room. A raised area to the side of the chamber is covered in "+
      "some strange reddish moss. There seems to be a lot more waste here "+
      "than in other areas of the cavern.\n");
    add_item(({"crude furs","crude fur","smelly furs","smelly fur"}),
      "The stench coming from the crude hides is so bad that you can't bring "+
      "yourself to come close enough to examine them.\n");
    add_item(({"stone floor","floor"}),"The floor, like the rest of this "+
      "chamber is made of that same strangely dark stone of the underdark.\n");
    add_item(({"raised area","area"}),"A section of this room where the "+
      "rock is higher and apparently cleaner.\n");
    add_item(({"strange reddish moss","strange moss","reddish moss","moss"}),
      "It covers the entire raised area protectively.\n");
    add_prop(OBJ_S_SEARCH_FUN, "search_moss");
    add_prop(OBJ_I_SEARCH_TIME, 4);
    add_exit(DARK(u19), "west");
}

