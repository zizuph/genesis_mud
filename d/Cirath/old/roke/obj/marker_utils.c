/* Marker utility functions */

#define MARKER_TYPES ({"red", "green", "blue"})
#define MARKER_VALUES ({12, 144, 1728})
#define MARKER_NUM 3
#define MARKER_NAME(type) ("_marker_" + (type))

/* mtext taken from text in lib/trade */
string
mtext(int *arr)
{
    string *t_arr, coin_str;
    int i, j;
    
    if (sizeof(arr) < MARKER_NUM)  /* Not a valid array. */
	return "";

    t_arr = ({ });

    for (i = MARKER_NUM - 1; i >= 0; i--)
	if (arr[i] > 0)
	{
	    j += arr[i]; /* Total number of coins */
	    t_arr += ({ arr[i] + " " + MARKER_TYPES[i] });
	}

    coin_str = " marker";
    if (j > 1)
	coin_str += "s";

    j = sizeof(t_arr);

    if (j < 1)
	return "";

    if (j == 1)
	return t_arr[0] + coin_str;
    else
	return implode(t_arr[0 .. j - 2], ", ") + " and " +
	       t_arr[j - 1] + coin_str;
}

void
give_markers(int *arr, object ob)
{
    int t;
    object m;
    for (t = 0; t < MARKER_NUM; t++)
    {
        if (arr[t] <= 0)
            continue;
        m = clone_object(ROKEDIR + "obj/markers");
        m->set_heap_size(arr[t]);
        m->set_marker_type(t);
        m->move(ob);
    }
}

int
marker_merge(int *arr)
{
    int t, s;
    for (t = 0; t < MARKER_NUM; t++)
        s += arr[t] * MARKER_VALUES[t];
    return s;
}

int *
add_markers(int *c1, int *c2)
{
    int t;
    int *r = ({ });
    for (t = 0; t < MARKER_NUM; t++)
        r += ({c1[t] + c2[t]});
    return r;
}

int *
mult_markers(int *c1, int m, int d = 1)
{
    int t;
    int *r = ({ });
    if (d == 1)
        for (t = 0; t < MARKER_NUM; t++)
            r += ({c1[t] * m});
    else
        for (t = 0; t < MARKER_NUM; t++)
            r += ({c1[t] * m / d}); // Hantera nar det inte gar jamnt upp FIXA
    return r;
}

mixed
pay_markers(object ob, int amount, string type)
{
    int i = member_array(type, MARKER_TYPES);
    object marker;
    int *res;
    marker = present(MARKER_NAME(type), ob);
    if (!objectp(marker))
    {
        NF("You don't have any " + type + " marker" +
            (amount == 1 ? "" : "s") + ".\n");
        return 0;
    }
    if (amount > marker->num_heap())
    {
        NF("You don't have that many " + type + " markers.\n");
        return 0;
    }

    marker->set_heap_size(marker->num_heap() - amount);
    if (i < 0)
        i = 0;
    res = allocate(MARKER_NUM);
    res[i] = amount;
    return res;
}

int
query_is_marker(object ob)
{
    return (ob->query_is_marker() && objectp(present(ob, this_player())));
}

object *
parse_markers_tp(string str)
{
    return CMDPARSE_ONE_ITEM(str, "query_is_marker", "query_is_marker");
}

mixed
parse_markers(string str)
{
    int amount, sz, marker;
    string type, rest, *words;

    if (!stringp(str) || str == "")
        return 0;

    words = explode(str, " ");
    if (sscanf(words[0], "%d", amount) == 1)
    {
        if (amount <= 0)
            return 0;
        words = words[1..];
    }
    sz = sizeof(words);
    if (sz == 0)
    {
        type == MARKER_TYPES[0];
    }
    else
    {
        if (words[sz-1] == "marker")
            marker = 1;
        else if (words[sz-1] == "markers")
            marker = 2;
        if (marker)
            words = words[0..-2];
    }
    sz = sizeof(words);
    if (sz == 0)
    {
        type = MARKER_TYPES[0];
    }
    else if (sz == 1)
    {
        if (member_array(words[0], MARKER_TYPES) == -1)
            return 0;
        type = words[0];
    }
    else
        return 0;
    if (amount == 0)
    {
        if (marker == 2)
            return 0;
        amount = 1;
    }
    if ((amount == 1 && marker == 2) || (amount > 1 && marker == 1))
        return 0;

    return ({amount, type});
}
