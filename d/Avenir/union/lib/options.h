/*
 * This handles toggleable options via the "uopt" command.
 */

/***************************************************************************
 * uopt - Change/view the options
 */
public nomask int
uopt(string arg)
{
    object List;
    string *args, *text;

    if (!stringp(arg))
    {
        uopt("lang");
#ifdef UOPT_RMTXT
        uopt("room");
#endif
#ifdef UOPT_STOUCH
        uopt("touch");
#endif
        uopt("help");
        return 1;
    }

    List = LIST->get_this_object();

    args = explode(arg, " ");
    if (sizeof(args) == 1)
    {
        switch(arg)
        {
        case "lang":
        case "language":
	    if (List->query_union_option(TP, UOPT_LSHORT))
		arg = "Short form";
	    else if (List->query_union_option(TP, UOPT_LLONG))
		arg = "Long form";
	    else
		arg = "Off";

	    text = ({ "Language", "[lang]", "[ Off, Short, Long ]" });
            break;

#ifdef UOPT_RMTXT
	case "room":
	    if (List->query_union_option(TP, UOPT_RMTXT))
		arg = "Off";
	    else
		arg = "On";

	    text = ({ "Room text", "[room]", "[ Off, On ]" });
	    break;
#endif
#ifdef UOPT_STOUCH
	case "touch":
	case "touching":
	    if (List->query_union_option(TP, UOPT_STOUCH))
		arg = "Off";
	    else
		arg = "On";

	    text = ({ "Touching", "[touch]", "[ Off, On ]" });
	    break;
#endif

	case "help":
	    write("\n\tFor help on options, do \"uopt help <option>\".\n");
	    return 1;

	default:
            return notify_fail("Syntax error: No such option.\n");
        }

	write(sprintf("  %-10s %7s : %-10s %-s\n",
	    text[0], text[1], arg, text[2]));

        return 1;
    }

    switch(args[0])
    {
    case "lang":
    case "language":
        if (args[1] == "short")
	{
	    List->set_union_option(TP, UOPT_LLONG, 0);
	    List->set_union_option(TP, UOPT_LSHORT, 1);
	}
        else if (args[1] == "long")
	{
	    List->set_union_option(TP, UOPT_LLONG, 1);
	    List->set_union_option(TP, UOPT_LSHORT, 0);
	}
	else
	{
	    List->set_union_option(TP, UOPT_LLONG, 0);
	    List->set_union_option(TP, UOPT_LSHORT, 0);
	}

        uopt("lang");
        break;

#ifdef UOPT_RMTXT
    case "env":
    case "room":
        if (args[1] == "off")
	    List->set_union_option(TP, UOPT_RMTXT, 1);
	else
	    List->set_union_option(TP, UOPT_RMTXT, 0);

        uopt("room");
	break;
#endif
#ifdef UOPT_STOUCH
    case "rub":
    case "touch":
    case "touching":
        if (args[1] == "off")
	    List->set_union_option(TP, UOPT_STOUCH, 1);
	else
	    List->set_union_option(TP, UOPT_STOUCH, 0);

        uopt("touch");
        break;
#endif

    case "help":
	switch(args[1])
	{
	case "lang":
	case "language":
	    write("OPTION:  language  [ lang ]\n"+
		  "  ARGS:  off, short, long\n\n"+
		  "This option controls how you sound when speaking.\n\n"+
		  "When 'off', you will say things as normal.\n"+
		  "When 'short', you will \"lilt\" your speech.\n"+
		  "When 'long', you will \"speak with a lilting accent\".\n");
	    return 1;

#ifdef UOPT_RMTXT
	case "env":
	case "room":
	    write("OPTION:  room  [ env ]\n"+
		  "  ARGS:  off, on\n\n"+
		  "This option controls receiving environmental messages\n"+
		  "in some (not all) rooms within the Union.\n\n"+
		  "When 'off', you will not receive messages.\n"+
		  "When 'on', you will see the environmental messages.\n");
	    return 1;
#endif
#ifdef UOPT_STOUCH
	case "rub":
	case "touch":
	case "touching":
	    write("OPTION:  touching  [ touch, rub ]\n"+
		  "  ARGS:  off, on\n\n"+
		  "This option controls receiving messages when\n"+
		  "another rubs or touches their sphere.\n\n"+
		  "When 'off', you will not receive a message.\n"+
		  "When 'on', you will be notified of these activites.\n");
	    return 1;
#endif
	}

    /* Intentional Fallthru */

    default:
        return notify_fail("Syntax error: No such option.\n");
        break;
    }
    return 1;
}
