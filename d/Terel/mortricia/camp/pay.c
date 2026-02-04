do_pay(string str)
{
    string  what, for_c, get_c;
    string  change;
    int     *result;
    int     price;

    price = FEE;

    if (!str) {
	notify_fail("Pay what? Fee?\n");
        return 0;
    }

    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
	if (sscanf(str, "%s with %s", what, for_c) != 2)
	    what = str;

    if (what != "fee" && what != "a silver coin" &&
        what != "silver coin") return 0;

    set_money_give_out(what_coins(TO));

    result = pay(price, TP, for_c, 0, TO, get_c);

    if (sizeof(result) == 1)
	return 0; /* Pay() handles notify_fail if we want to. */

    write ("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    change = text(result[NUM .. 2 * NUM - 1]);
    if (change) {
	write("You get, " + change + " as change.\n");
    }
    say(QCTNAME(TP) + " pays the fee.\n");
    return 1;
}
