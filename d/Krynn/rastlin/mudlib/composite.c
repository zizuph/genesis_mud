/*
 *  Description routines, composite sentences
 */
#pragma save_binary

#include "/sys/language.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"

/*
 *  Globals
 */
mixed	*gLastObjects;
mixed	*OldArr; 	/* The old origional array. */
object	Fobject; 	/* The object for whom we describe the things. */
object	*gExtra;	/* we might find two heaps with the same short desc :-/ */

/*
 *  Prototypes
 */
string composite(mixed arr, string sepfunc, string descfunc, object obj);
string lpc_describe(mixed uarr, string dfun, object dobj);

static varargs string
desc_live_dead(mixed arr)
{
    return composite(arr, "short", "desc_same", this_object());
}

mixed *get_last_objects() { return gLastObjects; }

varargs string
desc_live(mixed arr, int no_someone)
{
    string str;

    Fobject = this_player();
    str = desc_live_dead(arr);
    if (!str && !no_someone)
	return "someone";
    return str;
}

varargs string
desc_dead(mixed arr, int no_something)
{
    string str;

    Fobject = this_player();
    str = desc_live_dead(arr);
    if (!str && !no_something)
	return "something";
    return str;
}

string fo_desc_live(mixed arr, object for_ob)
{
    string str;

    if (!for_ob)
	for_ob = previous_object(-1);
    if (!arr)
	arr = OldArr;
    find_player("rastlin")->catch_msg(sprintf("%O %O\n", for_ob, arr));
    Fobject = for_ob;
    str = desc_live_dead(arr);
    if (!str)
	return "someone";
    return str;
}

string fo_desc_dead(mixed arr, object for_ob)
{
    string str;

    if (!for_ob)
	for_ob = previous_object(-1);
    if (!arr)
	arr = OldArr;
    Fobject = for_ob;
    str = desc_live_dead(arr);
    if (!str)
	return "something";
    return str;
}

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
	return pre + LANG_ADDART(sh) + aft;
    else
	return pre + sh + aft;
}

/*
 * Function:    composite
 * Description: Creates a composite description of objects
 * Arguments:   arr:        Array of the objects to describe
 *              sepfunc:    Function to call in objects to get its <name>
 *                          Objects with the same <names> are described
 *                          together.
 *              descfunc:   Function to call to get the actual description of
 *                          a group of 'same objects' i.e objects whose
 *                          sepfunc returned the same value.
 *              obj:        Object to call descfunc in.
 * 
 * Returns:     A description string on the format:
 *              <desc>, <desc> and <desc> 
 *              Where <desc> is what obj->descfunc() returns
 *
 */
varargs string
fo_composite(mixed arr, string sepfunc, string descfunc, object obj,
		object for_obj)
{
    if (!for_obj)
	for_obj = previous_object();
    Fobject = for_obj;
    return composite(arr, sepfunc, descfunc, obj);
}


varargs string
composite(mixed arr, string sepfunc, string descfunc, object obj)
{
    mixed *a;
    
    gLastObjects = ({ "** ERROR **" });
    if (!Fobject)
	Fobject = this_player();
    
    if (objectp(arr))
	arr = ({ arr });

    arr = filter(arr, "exclude_no_show", this_object());
    OldArr = arr;
    arr = filter(arr, "exclude_invis", this_object());
    arr = filter(arr, "exclude_hidden", this_object());
    arr = filter(arr, "exclude_no_see_room", this_object());
    
    if ((!pointerp(arr)) || (sizeof(arr) < 1))
    {
	Fobject = 0;
	return 0;
    }

    /* Make an array of unique lists of objects 
     */    
    a = unique_array(arr, sepfunc); 
    gLastObjects = a;
    return lpc_describe(a, descfunc, obj);
}

int
exclude_no_show(object ob)
{
    if (!ob || ob->query_no_show_composite())
	return 0;
    return 1;
}

int
exclude_invis(object ob) 
{ 
    if (Fobject && !Fobject->query_wiz_level() &&
	    Fobject->query_prop(LIVE_I_SEE_INVIS) < ob->query_prop(OBJ_I_INVIS))
	return 0;
    return 1;
}

int
exclude_hidden(object ob) 
{ 
    int seed;
    sscanf(OB_NUM(ob), "%d", seed);
	
    if (Fobject && !Fobject->query_wiz_level() &&
	    random(Fobject->query_skill(SS_AWARENESS), seed) < 
		ob->query_prop(OBJ_I_HIDE))
	return 0;
    return 1;
}

int
exclude_no_see_room(object ob)
{
    return CAN_SEE_IN_ROOM(ob);
}

/*
 * Function:    sort_similar
 * Description: sort an array in order shown to player
 * Arguments:   arr:        Array of the objects to sort
 *              sepfunc:    Function to call in objects to get its <name>
 *                          Objects with the same <names> are sorted
 *                          together.
 * 
 * Returns:     0 or sorted array
 *
 */
mixed
sort_similar(mixed arr, string sepfunc)
{
    int b, i;
    mixed *a;

    if ((!pointerp(arr)) || (sizeof(arr)<1)) return 0;
    
    a = unique_array(arr, sepfunc);

    if (!sizeof(a))
	return 0;

    b = a[0];
    for (i = 1; i < sizeof(a); i++)
    {
      b += a[i];
    }
    
    return b;

/*
    a = map(arr, "map_fun", this_object(), sepfunc);
    a = sort_array(a, "sort_fun", this_object());
    a = map(a, "second_fun", this_object());
    return a;
*/
}


second_fun(arr) { return arr[1]; }

#if 0  /* If unique_array does not work */
/*
  unique300

   Input: array of objects
   Output: array of unique objects: ({ 
                                       ({uniqueobj, copyobj,...}),
                                       ({uniqueobj, copyobj,...}),
                                       ({uniqueobj, copyobj,...})
				    })
*/
#define S(a, b) sort_array(a, b, this_object())


unique300(arr, sepfunc)
{
    int a, b, c, d;
    
    if ((!pointerp(arr)) || (sizeof(arr) < 1))
	return 0;
    a = map(arr, "map_fun", this_object(), sepfunc);
    a = S(a, "sort_fun");
    if (a[0][1] == 0)
	a = slice_array(a, 1, sizeof(a));
    if ((!pointerp(arr)) || (sizeof(arr)<1))
	return 0;
    
    b = ({ ({ a[0][1] }) });
    for (c = 1, d = 0; c < sizeof(a); c++) {
	if (a[c][0] == a[c - 1][0])
	    b[d] = b[d] + ({ a[c][1] });
	else
	{
	    d++;
	    b = b + ({ ({ a[c][1] }) });
	}
    }
    return b;
}
#endif

int
sort_fun(int *a, int *b)
{
    if (a[0] < b[0]) return -1;
    if (a[0] == b[0]) return 0;
    return 1;
}

mixed
map_fun(mixed ob, string f)
{
    if (objectp(ob))
	return ({call_other(ob, f), ob});
    else
	return ({"", 0});
}

string
lpc_describe(mixed uarr, string dfun, object dobj)
{
    mixed *a, *b;

    gExtra = ({});
    a = map(uarr, dfun, dobj);

    if (sizeof(gExtra))
    {
    	b = map(gExtra, dfun, dobj);
	a += b;
    }

    a = filter(a, "no_invis", this_object());

    Fobject = 0;
    if (!a || sizeof(a) == 0)
	return 0;
    else
	return this_object()->composite_words(a);
}

no_invis(str)
{
    return (stringp(str));
}

string composite_words(string *wlist)
{
    if (!sizeof(wlist))
	return "";

    if (sizeof(wlist) == 1)
	return wlist[0];

    if (sizeof(wlist) == 2)
	return implode(wlist, " and ");

    return implode(wlist[0..sizeof(wlist) - 2], ", ") +
	" and " + wlist[sizeof(wlist) - 1];
}

