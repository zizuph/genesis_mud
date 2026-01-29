#pragma save_binary
#pragma strict_types

inherit "/std/shadow";

/*
 * There are (at least) four functions in /std/object.c to check
 * the adjectives set in an object. In this shadow, I shadow them all.
 * parse_command_adjectiv_id_list() is necessary so that parse_command()
 * works with the new adjectives.
 */

#ifndef OBJ_ADJS
#define OBJ_ADJS ({"black-robed", "hooded"})
#endif

#define EYES_SUBLOC         "eyes"
#define HAIR_SUBLOC         "hairstyle"

private mixed
query_list(mixed list, int arg)
{
    if (!pointerp(list))
        return 0;

    if (!arg && sizeof(list))
        return list[0];
    else
        return list + ({});
}

varargs public mixed
query_adj(int arg) 
{
    return query_list(OBJ_ADJS, arg);
}

public string *
query_adjs() 
{ 
    return query_list(OBJ_ADJS, 1);
}

public int
adjectiv_id(string str)
{
    return (member_array(str, OBJ_ADJS) >= 0);
}

public string *
parse_command_adjectiv_id_list()
{
    return OBJ_ADJS + ({ query_shadow_who()->query_gender_string() });
}

/*
 * This is used by the robe code to allow an easy check
 * if the hood is worn.
 */
int
query_hooded()
{
    object po = previous_object();
    mixed caller;
    
    if (!objectp(po))
        return 0;

    caller = file_name(po);

    if(caller[0..8]== "/d/Avenir")
        return 0;
    return 1;
}

/*
 * Function   : remove_hood_shadow
 * Description: Removes this shadow.
 */
public void 
remove_hood_shadow()
{
    destruct();
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if (subloc == EYES_SUBLOC || subloc == HAIR_SUBLOC)
        return "";
    else return shadow_who->show_subloc(subloc, me, for_obj);
}



