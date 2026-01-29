/*
 * Emote:       kcalm
 * Description: Sylvana, composed and calm, carefully observes the situation.
 *
 *              After idea from Sylvana Knight of the Crown
 *
 */int
kcalm(string str)
{
    object *oblist;

    NF("Calmly observe whom?\n");

    if (!str)
    {
        write("Composed and calm, you carefully observe the "+
        "situation.\n");
        all(", composed and calm, carefully observes the situation.");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
        return 0;

    actor("Composed and calm, you carefully watch ", oblist);
    target(", composed and calm, watches you carefully.", oblist);
    all2act(", composed and calm, watches", oblist, " carefully.");
    return 1;
}



