/*
 *  The wedding corsage; it should be worn by the groom,
 *  or else he will not be recognised as the groom.
 *							Tricky, Dec 1992
 */
inherit "/std/object";

#include "defs.h"
#include "/sys/stdproperties.h"

#define CARNAGE_SUBLOC "_wed_corsage_subloc"

void
create_object()
{
    set_name(({"wed_corsage","corsage"}));
    set_adj("wedding");
    set_short("wedding corsage");
    set_long(break_string(
	"The corsage is composed of brightly coloured flowers. They seem "
      + "to have an air of magic around them that keeps them fresh and "
      + "pleasantly fragrant. The corsage is cleary for the groom to "
      + "wear.\n", 70));

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
	dest->add_subloc(CARNAGE_SUBLOC, this_object());
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
	old->remove_subloc(CARNAGE_SUBLOC);
}

string
show_subloc(string subloc, object on_obj, object for_obj)
{
    string str;

    if (subloc != CARNAGE_SUBLOC)	
	return "";

    if (on_obj == for_obj)
	str = "You are ";
    else
	str = on_obj->query_pronoun() + " is ";

    str += "wearing the groom's wedding corsage.\n";

    return str;
}
