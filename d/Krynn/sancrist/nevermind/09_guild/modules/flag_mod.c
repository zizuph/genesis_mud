/************* Module: Flag with individual message ***********************
 *                           flag:   1                                    *
 **************************************************************************/

int
gflag(string name)
{
    object ob;

    NF("You forgot to attach this module.\n");
    if (!flag(1,0))
        return 0;
    NF("You haven't set a message yet.\n");
    if (!GFLAG_MESSAGE(TP))
        return 0;
    NF("You have a look at your flag.\nIt reads: " + GFLAG_MESSAGE(TP) + "\n");
    if (!name)
        return 0;
    NF("I cannot see " + name + " here.\n");
    if (!(ob = P(name, E(TP))))
        return 0;
    NF("You want to quicktalk to a " + ob->short() + "?\n");
    if (!living(ob))
        return 0;

    if(flag(1,1) == -1)
        return 1;
    NF("You quicktalk to yourself. Feeling lonesome?\n");
    if(C(name) == TP->query_name())
        return 0;   

    actor("You release the little flag to quicktalk to", ({ob})); 
 [32m    targetbb(" presses a button on " + POSSESSIVE(TP) + " gizmo which then " [0m
      + "sproings a little flag at you. There is "
      + "something written on the flag:\n"
      + GFLAG_MESSAGE(TP), ({ob}));
    tell_room(E(TP), QCTNAME(TP) + " quicktalks to " + QTNAME(ob) + " by "
      + "producing a little flag.\n", ({ob, TP}));
    return 1;
}

int
set_message(string str)
{
    if (!flag(1,0))
        return 0;

    NF("Inscribe what message?\n");
    if (!str)
        return 0;

    if(!darkcheck(TP))

        return 1;
    if (GFLAG_MESSAGE(TP))
        write("You erase the old inscription and write down the new one.\n");
    else
        write("You inscribe your message onto the little flag.\n");
 [33m    say(QCTNAME(TP) + " does something to " + POSSESSIVE(TP) + " gizmo.\n"); [0m
    SET_GFLAG_MESSAGE(TP,str);
    return 1;
}


