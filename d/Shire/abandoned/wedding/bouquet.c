/*
 *  The wedding bouquet; it should be carried by the bride,
 *  or else she will not be recognised as the bride.
 *							Tricky, Dec 1992
 */
inherit "/std/object";

#include "defs.h"
#include "/sys/stdproperties.h"

#define BOUQUET_SUBLOC "_wed_bouquet_subloc"

void
create_object()
{
    set_name(({"wed_bouquet","bouquet"}));
    set_adj("wedding");
    set_short("wedding bouquet");
    set_long(break_string(
	"The bouquet is composed of brightly coloured flowers. They seem "
      + "to have an air of magic around them that keeps them fresh and "
      + "pleasantly fragrant. The bouquet is cleary for the bride to "
      + "carry.\n", 70));

    add_prop(OBJ_I_WEIGHT, 190);
    add_prop(OBJ_I_VOLUME, 210);
}

/*
 * Function name:   enter_env
 * Description:     Make sure that if a person carries this object,
 *		    it can be seen by someone else.
 * Arguments:	    dest: To where this object is moving
 *		    old:  From where this object came
 */
void
enter_env(object dest, object old)
{
    if (living(dest))
	dest->add_subloc(BOUQUET_SUBLOC, this_object());
}

/*
 * Function name:   leave_env
 * Description:     Make sure that if a person carried this object,
 *		    the description we added in enter_inv is removed.
 * Arguments:	    old:  From where this object came
 *		    dest: To where this object is moving
 */
void
leave_env(object old, object dest)
{
    if (living(old))
	old->remove_subloc(BOUQUET_SUBLOC);
}

string
show_subloc(string subloc, object on_obj, object for_obj)
{
    string str;

    if (subloc != BOUQUET_SUBLOC)	
	return "";

    if (on_obj == for_obj)
	str = "You are ";
    else
	str = on_obj->query_pronoun() + " is ";

    str += "carrying the bride's wedding bouquet.\n";

    return str;
}
