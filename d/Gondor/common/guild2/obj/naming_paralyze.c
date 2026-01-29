/*
 *	/d/Gondor/common/guild2/obj/naming_paralyze.c
 *
 * 	Olorin, November 1995
 */

inherit "/std/paralyze.c";

static int     gGagged;

public void    set_gagged(int i = 1) { gGagged = i; }

/*
 * Function name: create_paralyze
 * Description:	  Set up paralyze
 */
void
create_paralyze()
{
    set_fail_message("The Red Eye holds you in its terrible "
      + "stare, making it impossible for you to move.\n");
    set_name(({"Stare of the Red Eye", "stare", "_Stare_of_the_Red_Eye"}));
}

/*
 * Function name: stop
 * Description:   Here all commands the player gives comes.
 * Argument:	  str - The extra string the player sent.
 */
varargs int
stop(string str)
{
    /* Only paralyze our environment */
    if (environment(this_object()) != this_player())
	return 0;

    if (!gGagged)
    {
        if (wildmatch("'*", query_verb()))
            return 0;
        switch (query_verb())
        {
        // Morgul emotes:
        case "msmile":
        case "mhiss":
        case "rasp":
        // Communication verbs:
        case "rsay":
        case "say":
        case "shout":
        case "whisper":
        // General emotes:
        case "choke":
        case "hmm":
        case "nod":
        case "shiver":
        case "smile":
        case "tremble":
        // Eyes:
        case "l":
        case "look":
        case "exa":
        case "examine":
        // meta-commands
        case "bug":
        case "idea":
        case "typo":
        case "sysbug":
        case "praise":
            return 0;
            break;
        default:
            if (fail_message)
                this_player()->catch_msg(fail_message);
            if (!this_player()->query_wiz_level())
                return 1;
            break;
        }
    }
    else
    {
        switch(query_verb())
        {
        // Morgul emotes:
        case "msmile":
        // General emotes:
        case "choke":
        case "hmm":
        case "nod":
        case "shiver":
        case "smile":
        case "tremble":
        // Eyes:
        case "l":
        case "look":
        case "exa":
        case "examine":
        // meta-commands
        case "bug":
        case "idea":
        case "typo":
        case "sysbug":
        case "praise":
            return 0;
            break;
        default:
            if (fail_message)
                this_player()->catch_msg(fail_message);
            if (!this_player()->query_wiz_level())
                return 1;
            break;
        }
    }
    
    write("Since you are a wizard this paralyze won't affect you.\n");
    return 0;
}

