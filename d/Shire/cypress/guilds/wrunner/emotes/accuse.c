int accuse(string str)
{
        object *oblist;

        notify_fail("Accuse whom?\n");
        if(!strlen(str))
                return 0;

        oblist = parse_this(str, "%l");
        if(!sizeof(oblist))
                return 0;
        target(" points an accusatory finger at you.", oblist);
        actor("You point an accusatory finger at", oblist);
        all2act(" points an accusatory finger at", oblist);
        return 1;
}
