#pragma strict_types
// Combat veil shadow 
// creator(s):  Lilith Jan 96
// purpose:     Shadowing player adjectives
// note:        There is a veil associated with this file
/* Revisions:
 * 	Cirion, May, 1997: Added query_is_veiled() function
 * 	Lucius, Apr, 2005: Changed the Veil checking methods.
 * 	Lucius, Apr, 2009: Changed shadow handling + small tweaks
 */
inherit "/std/shadow";
/*
 *   The functions below are altered from the /std/object.c
 *
 *   Shadowing them is necessary for effective restoration
 *   of player adjectives. Lets hope I found all the needed
 *   functions.
 */
// This is a substitute for obj_adjs in /std/object.c
public string *veil_adjs = ({ "shadowy", "veiled" });

/*
 * Function name: parse_command_adjectiv_id_list
 * Description  : This will return the adjective words that can be used to
 *                point at one particular object or a group of objects,
 *                i.e. an adjective 'id'.
 * Returns      : string * - the list.
 */
public string *
parse_command_adjectiv_id_list(void)
{
    return secure_var(veil_adjs);
}

/*
 * Function name: adjectiv_id
 * Description  : This function can be used to see whether a certain
 *                adjective is used by this object, i.e. whether the
 *                adjective has been added with set_adj or add_adj.
 * Arguments    : string str - the adjective you want to test.
 * Returns      : int 1/0 - true if the adjective is indeed used.
 */
public int
adjectiv_id(string str)
{
    return (member_array(str, veil_adjs) >= 0);
}

/*
 * Function name: query_list
 * Description:   Gives the return of a query on a list.
 * Arguments:     list: The list in question
 *                arg: If true then the entire list is returned.
 * Returns:       A string or an array as described above.
 */
private mixed
query_list(mixed list, int arg)
{
    if (!pointerp(list))
	return 0;

    if (!arg && sizeof(list))
	return list[0];
    else
	return secure_var(list);
}

/*
 * Function name: query_adj
 * Description  : Gives the adjective(s) of the object.
 * Arguments    : int arg - if true, all adjectives are returns, else only
 *                          the first adjective is returned.
 * Returns      : mixed   - int 0    - if there are no adjectives. 
 *                          string   - one adjective if 'arg' is false. 
 *                          string    - an array with all adjectives if 
 *                                     'arg' is true.
 */
public varargs mixed
query_adj(int arg) 
{ 
    return query_list(veil_adjs, arg); 
}

/*
 * Function name: query_adjs
 * Description  : This function returns an array of all adjectives of
 *                this object.
 * Returns      : string * - an array of all adjectives of this object
 *                           or 0 if there are no adjectives.
 */
public string *
query_adjs(void) 
{ 
    return query_list(veil_adjs, 1); 
}

public int
query_is_veiled(void)
{
    return 1;
}

public object
query_union_veil(void)
{
    return this_object();
}

public void
remove_union_veil(void)
{
    remove_shadow();
}
