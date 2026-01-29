/*
 *  Description routines, composite sentences
 */
#pragma save_binary

#include "/sys/language.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"

inherit "/d/Krynn/open/sys/global/old_mudlib_composite.c";

mixed art = 0;

/*
 * Function:    desc_same
 * Description: Gives a textdescription of a set of nonunique objects.
 *              Normal case: "two swords", "a box" etc.
 *              The basic function to get the description of an objects is
 *              its 'short' function. Pluralforms are taken from:
 *              1) The 'plural_short' function of the object.
 *              2) If 1) is not defined then the singular form is transformed
 *                 into the pluralform, not always correctly.
 *              Articles are added to singular objects that does NOT have a
 *              capitalized short description and that are not heap objects.
 * ADDITION:    When the global variable art is 0: use 'A'
 *                                              1: use 'The'
 *                                              2: use '' as article if needed.
 * Arguments:   oblist: Array of objectpointers to the nonunique objects.
 * Return:      Description string or 0 if no 'short' was not defined.
 */
string
desc_same(object *oblist) /* Used as dfun to composite() for composite_live */
{
    string str, sh, pre, aft;
    object ob;

    if (!pointerp(oblist)) /* This is here to take care of the gExtra */
	oblist = ({ oblist });

    if (!sizeof(oblist))
	return "";

    pre = ""; aft = "";
    ob = oblist[0];
    if (ob->query_prop(OBJ_I_HIDE))
    {
	pre = "[";
	aft = "]";
    }
    if (ob->query_prop(OBJ_I_INVIS))
    {
	pre = "(";
	aft = ")";
    }
    sh = ob->short(Fobject);
    if (sizeof(oblist) > 1)
    {
	if (ob->query_prop(HEAP_I_IS))
	{
	    gExtra += oblist;
	    return 0;
	}
	str = ob->plural_short();
	if (!stringp(str) && !stringp(sh))
	    return 0;
	if (!str)
	    str = LANG_PSENT(sh);
/*
	if (sizeof(oblist) < 4)
	    return pre + LANG_WNUM(sizeof(oblist)) + " " + str + aft;
	else if (sizeof(oblist) < 8)
	    return pre + "some " + str + aft;
*/
  	if (sizeof(oblist) < 9)
	    return pre + LANG_WNUM(sizeof(oblist)) + " " + str + aft;
	else
	    return pre + "many " + str + aft;
    }
    else if (!stringp(sh))
	return 0;
    else if (ob->query_prop(HEAP_I_IS))
	return pre + sh + aft;
    else if (sh[0] > 'Z')
      { /* This is the only change from the normal /sys/global/composite.h file */
	  if (art == 0)
	    return pre + LANG_ADDART(sh) + aft;
	  if (art == "")
	    return pre + sh + aft;
	  return pre + art + " " + sh + aft;
      }
    else
	return pre + sh + aft;
}

/* These two functions are added to set the prefixed article correctly before
 * the calculation.
 */
varargs string
myart_desc_live(mixed arr, int no_someone, string my_prefix)
{
    string tmp;
    art = my_prefix;
    tmp = desc_live(arr, no_someone);
    art = 0;
    return tmp;
}

varargs string
myart_desc_dead(mixed arr, int no_someone, string my_prefix)
{
    string tmp;
    art = my_prefix;
    tmp = desc_dead(arr, no_someone);
    art = 0;
    return tmp;
}

