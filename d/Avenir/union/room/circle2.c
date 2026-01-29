/* Gallery 2
 *  Cirion 040296
 *
 * Revised, Lucius May 2005: Recoded a bit to work fully.
 *          Lilith Apr 2022: added missing add_items
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <language.h>
#include <composite.h>
#include <stdproperties.h>

#define SEE_IN          ({ ROOM +"circle1", ROOM +"circle0" })
#define GET_STATUES(x)  find_object(ROOM + "circle0")->query_statues(x)

public string *statues;


public string 
see_view(void)
{
    object *obs = get_view(SEE_IN);
    if (sizeof(obs))
    {
	return " Looking inward, you see "+ COMPOSITE_LIVE(obs) +
	    " amongst the statues standing around a spiral flue.";
    }
    return " Looking inward, you see a ring of statues facing "+
	"a spiral flue that rises up to the ceiling.";
}

public void 
make_statues(void)
{
    int size, ix, cnt;

    statues = GET_STATUES(2);
    size = sizeof(statues);
    obj_items = ({ });

    set_long("You are at the outer edge of a large, circular cavern that "+
      "seems to hum with energy. Shadows are in constant movement, "+
      "ebbing and flowing in a complex dance of aching, incomprehen"+
      "sible beauty. Wave after wave of feeling crashes over you, "+
      "lifting you up as the passions of Jazur rise within you to "+
      "dizzying heights. Placed here are "+ LANG_WNUM(size / 2) +
      " statues, each facing outwards, standing back-to-back with the "+
      "figures in the inner circle.@@see_view@@\n");

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
	"facing outwards, forming a protective circle around the "+
	"center of the cavern. Engraved into the plaques at the base "+
	"of the statues are the names "+ COMPOSITE_WORDS(names) +".\n";
}

public void 
union_room(void)
{
    set_short("outer circle");
    add_prop(ROOM_S_DARK_LONG, "You are enveloped by a darkness whose "+
      "silence seems to hum in your ears. Wave after wave of "+
      "feeling crashes over you, lifting you up as the passions "+
      "of Jazur rise with you to dizzying heights.\n"); 

    add_prop(ROOM_I_LIGHT,  5);
	
    add_exit("circle1", "inward");
    add_exit("circle1", "in", 0, 1, 1);

    make_statues();
}

public int
query_prevent_snoop(void)
{
    return 1;
}
