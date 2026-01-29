/* Gallery 2
 *  Cirion 040296
 *
 * Revisions:
 *   Lucius May 2005: Recoded a bit to work fully.
 *   Lilith Apr 2022: added missing add_items
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <language.h>
#include <composite.h>
#include <stdproperties.h>

#define SEE_IN          ({ ROOM +"circle0" })
#define SEE_OUT         ({ ROOM +"circle2" })
#define GET_STATUES(x)  find_object(ROOM + "circle0")->query_statues(x)

public string *statues;


public string 
see_view(void)
{
    string str = "";
    object *obs = get_view(SEE_IN);

    if (sizeof(obs))
    {
	str += " Looking inward, you see "+ COMPOSITE_LIVE(obs) +
	    " at the base of the spiral staircase.";
    }

    obs = get_view(SEE_OUT);
    if (sizeof(obs))
    {
	str += " Beyond the statues you see "+ COMPOSITE_LIVE(obs) +
	    " standing at the outer edge of the cavern. ";
    }

    return str;
}

public void 
make_statues(void)
{
    int size, ix, cnt;

    statues = GET_STATUES(1);
    size = sizeof(statues);
    obj_items = ({ });

    set_long("You are in the middle ring of a large, circular "+
      "cavern that seems to hum with energy. Shadows are in "+
      "constant movement, ebbing and flowing in a complex dance "+
      "of aching, incomprehensible beauty. Your soul feels stripped "+
      "bare, wide open to the tide of passions that rise and sweep "+
      "through you, mingling innervation and exhaustion in equally "+
      "intoxicating portions. Standing here are "+ LANG_WNUM(size / 2) +
      " statues, each facing the center of the cavern, where the "+
      "flue spirals upward like a flame frozen in stone."+
      "@@see_view@@\n");

    /* Item name: statue 1, first statue,
     *            statue of cirion, cirion
     */
    for(ix = 0, cnt = 0; ix < size; ix += 2)
    {
	cnt++;
	add_item(({"statue "+ cnt, LANG_WORD(cnt) +" statue",
		"statue of "+ statues[ix], statues[ix] }),
	    statues[ix + 1]);
    }
    add_item("statues", "@@exa_statues@@");
	add_item(({"flame", "blue flame", "jazur flame", "well"}), 
        "A great blue flame arises from the center of the cavern, "+
        "dazzling your eyes.\n");
	add_item(({"flue"}), "A stone flue spirals down toward the center "+
        "of the cavern.\n");

}

public string 
exa_statues(void)
{
    int size;
    string *names = ({ });

    if (!(size = sizeof(statues)))
	return "There are no statues here.\n";

    for (int ix = 0; ix < size; ix += 2)
	names += ({ CAP(statues[ix]) });

    return "There are "+ LANG_WNUM(size / 2) +" statues "+
	"facing inwards, forming a protective circle around the "+
	"center of the cavern. Guarding their backs is another, "+
	"outer ring of statues. Engraved into the plaques at the base "+
	"of the statues nearby are the names "+
	COMPOSITE_WORDS(names) +".\n";
}

public void 
union_room(void)
{
    set_short("inner circle");
    add_prop(ROOM_S_DARK_LONG, "You are enveloped by a darkness whose "+
      "silence seems to hum in your ears. Wave after wave of "+
      "feeling crashes over you, lifting you up as the passions "+
      "of Jazur rise with you to dizzying heights.\n"); 

    add_prop(ROOM_I_LIGHT,  5);
	

    add_exit("circle0", "inward");
    add_exit("circle2", "outward");
    add_exit("circle0", "in", 0, 1, 1);
    add_exit("circle2", "out", 0, 1, 1);

    make_statues();
}

public int
query_prevent_snoop(void)
{
    return 1;
}
