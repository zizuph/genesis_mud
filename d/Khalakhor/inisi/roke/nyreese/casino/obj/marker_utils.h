/* Marker utility functions */

#define MARKER CASINO + "obj/marker"
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

/* Give markers to player */
void
give_markers(int *arr, object ob)
{
    int t, res;
    object m, *inv, leftover;
    for (t = 0; t < MARKER_NUM; t++)
    {
        if (arr[t] <= 0)
            continue;
        m = clone_object(MARKER);
        m->set_marker_type(t);
        m->set_heap_size(arr[t]);
        // first move it into this object, to have a source for the move
        // to the player
        m->move(this_object(), 1);
        res = m->move(ob);
        if (res)
        {
            ob->catch_msg("You can't carry  " + m->short() +
                          " so you drop them on the ground.\n");
            tell_room(environment(ob), QCTNAME(ob) + " drops " + m->short() + 
                      ".\n", ({ob}));
            m->move(environment(ob));
        }
        else
        {
            // Detect anything left behind
            inv = all_inventory(this_object());
            if (sizeof(inv))
            {
                leftover = inv[0];
                ob->catch_msg("You can't carry all and drop " + leftover->short() +
                              " on the ground.\n");
                tell_room(environment(ob), QCTNAME(ob) + " drops " +
                          leftover->short() + ".\n", ({ob}));
                leftover->move(environment(ob));
            }
        }            
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
    int t, rem;
    int *r = ({ });
    for (t = 0; t < MARKER_NUM; t++)
        r += ({c1[t] * m});
    if (d > 1)
        for (t = 0; t < MARKER_NUM; t++)
        {
            rem = r[t] % d;
            r[t] = r[t] / d;
            if (rem != 0 && t > 0)
                r[t-1] += rem * 12 / d;
        }
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

mixed
pay_markers2(object ob, int *markers)
{
    int i, *res;
    mixed r;

    res = allocate(MARKER_NUM);

    for (i = 0; i < MARKER_NUM; i++)
    {
        if (markers[i] == 0) continue;
        r = pay_markers(ob, markers[i], MARKER_TYPES[i]);
        if (r == 0) {
            give_markers(res, ob);
            return 0;
        }
        res = add_markers(res, r);
    }
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

int
do_buy(string str)
{
    int amount, i, t, value, wealth;
    string type, change_text, rest;
    int *accept, *coinarr;
    mixed res;

    notify_fail("Buy what? (Try e.g. 'buy 5 red markers')\n");

    res = parse_markers(str);
    if (!pointerp(res) || sizeof(res) == 0)
        return 0;

    amount = res[0];
    type = res[1];

    if ((i = member_array(type, MARKER_TYPES)) == -1)
    {
        notify_fail("There are no " + type + " markers.\n");
        return 0;
    }

    value = amount * MARKER_VALUES[i];
    accept = ({0, 1, 1, 1});

    // This does nothing?? i uninitialized...
    for (t = 0; t <= i; t++)
        accept[t] = 0;

    set_money_accept(accept);
    coinarr = pay(value, this_player());
    if (sizeof(coinarr) == 1)
    {
/*                  0 - Noone to pay the price found
 *                  1 - The specified money is not enough to pay the price
 *                  2 - Choosed to pay with money object haven't got
 *                  3 - Haven't got enough money
 *                  4 - Can' pay the price after we compare what player has
 *                      to what we accept, i.e. can't pay in acceptable coins
 */
        write("You can't afford " + amount + " " + type + " marker" +
            (amount == 1 ? "" : "s") + ".\n");
        return 1;
    }

    accept = allocate(MARKER_NUM);
    accept[i] = amount;
    give_markers(accept, this_player());

    change_text = text(coinarr[4..7]);

    write("You hand the cashier " + text(coinarr[0 .. 3]) + " through the bars.\n");
    say(QCTNAME(TP) + " hands the cashier some coins through the bars.\n");
    tell_room(TO, "The cashier says: Thank you!\n");
    write("The cashier quickly counts the coins before handing you " + 
        amount + " " + type + " marker" + (amount == 1 ? "" : "s"));
    if (stringp(change_text))
        write(", and " + change_text + " in change.\n");
    else
        write(".\n");
    say("The cashier quickly counts the coins before handing something back " +
        "to " + QTNAME(TP) + ".\n");
    tell_room(TO, "The cashier says: Have a marvelous day with lots of luck! Don't forget " +
             "to come back and sell your markers when you are ready to cash out.\n");
    write("The cashier smiles pleasently at you.\n");
    say("The cashier smiles pleasently at " + QTNAME(TP) + ".\n");

    return 1;
}

int
do_sell(string str)
{
    int amount, i, t, value, wealth;
    string type, change_text, rest, *words;
    int *accept, *coinarr;
    mixed *res;

    notify_fail("Sell what? (Try e.g. 'sell 5 red markers')\n");

    if (!str || str == "")
        return 0;
    
    res = parse_markers_tp(str);

    if (!sizeof(res))
        return 0;

/*    write("Size: " + sizeof(res) + "\n");
    for (t = 0; t < sizeof(res); t++)
    {
        write(" " + t + ":" + res[t]->short() + ":" + file_name(res[t]) + "\n");
    }
*/

    //write("You sell " + COMPOSITE_DEAD(res) + ".\n");
    write("You slide " + COMPOSITE_DEAD(res) + " through the bars in the opening to the cashier.\n");
    say(QCTNAME(TP) + " slides some markers through the bars in the opening to the cashier.\n");
    tell_room(TO, "The cashier says: Thank you, looks like you were in luck today!\n");
    coinarr = allocate(4);
    for (t = 0; t < sizeof(res); t++)
    {
        type = res[t]->query_marker_type();
        amount = res[t]->num_heap();
        i = member_array(type, MARKER_TYPES);
        if (i < 0) i = 0;
        coinarr[i + 1] += amount;
        res[t]->remove_marker();
    }
    MONEY_MOVE_COIN_TYPES(coinarr, 0, this_player());
    //write("You get " + text(coinarr) + ".\n");
    write("The cashier arranges some markers into neat stacks and hand " +
          "you " + text(coinarr) + ".\n");
    say("The cashier arranges some markers into neat stacks and hands " +
        QTNAME(TP) + " some coins.\n");
    tell_room(TO, "The cashier says: Have a wonderful day, and I hope " + 
                  "we will have the pleasure to see you back here again soon!\n");
    write("The cashier smiles pleasently at you.\n");
    say("The cashier smiles pleasently at " + QTNAME(TP) + ".\n");
    return 1;
}
