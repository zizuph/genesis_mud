/*
 * Function name: parse_herb
 * Description:   parse_command functionality (partially) for herbs.
 * Arguments:     string str - the name of the herb to search for
 *                   (accepts constructs like "two parsley")
 * Returns:       array of objects in the parse_command %i format
 */
mixed *
parse_herb(string str, object *inv)
{
    object *items;
    int num;
    string wnum,herb;
    if (sscanf(str,"%s %s",wnum,herb)==2)
    {
        num = LANG_NUMW(wnum);
    }
    else
    {
        num = 1;
        herb = str;
    }

    items = filter(inv, &operator(==)(herb) @ &->query_herb_name());
    if (num > sizeof(items))
    {
        gTmp = 1;
        return ({ });
    }
    return ({ num, }) + items;
}   
