/*
 *    dbo
 */
string
dbow_adj()
{
    string *adjs = ({ "delightful", "lovely", "delectable", "stunning",
           "beautiful", "soft-skinned", "incomparable", "shapely", 
           "exquisite", "flawless", "splendid", "voluptous" });
    return adjs[random(sizeof(adjs))];
}

int
dbo(string str)
{
    object *oblist;   
    string newadj;
    newadj = dbow_adj();

    if (!str)
    {
        write("You bow deeply and gracefully, displaying your "+ newadj +
            " bosom to its best advantage.\n");
	allbb(" bows deeply and with languid grace, permitting you a "+
            "glimpse of her "+ newadj +" bosom.");
	return 1;
    }
     
    oblist = parse_this(str, "[deeply] [to] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Ddow to who?\n");
        return 0;
    }
    
    actor("You bow deeply and with languid grace, permitting",
         oblist, " a glimpse of your "+ newadj +" bosom.");
    target(" bows deeply before you. The languid grace of her "+
         "movement permits you a glimpse of her "+ newadj +
         " bosom.", oblist);
    all2actbb(" bows deeply and with languid grace before", 
        oblist,".");
    return 1;

}

/*
 *     dhand
 */
int
dhold(string str)
{
    object *oblist;
    string name;

    if (!str)
    {
        notify_fail("Dhold whose hand?\n");
	return 0;
    }

    oblist = parse_this(str, "[the] [hand] [of] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dhold the hand of whom?\n");
        return 0;
    }
        
    target(" smiles softly and takes your hand in hers.", oblist);
    actor("You smile softly at", oblist, " and take "+
        oblist[0]->query_possessive() +" hand in yours.");
    all2actbb(" smiles softly at", oblist, " and takes "+
        oblist[0]->query_possessive() +" hand in hers.");
    return 1;
}

/*
 *   dmark
 */     
int
dmark(string str)
{
    object *oblist;
    object kiss;

    if (!str)
    {
        notify_fail("Dmark whose cheek with a lipstick kiss?\n");
	return 0;
    }

    oblist = parse_this(str, "[the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dmark who?\n");
        return 0;
    }
    
    target(" kisses you on the cheek for a long moment.", oblist);
    actor("You kiss", oblist, "'s cheek for a long moment, leaving "+
        "a red lipstick imprint on "+ oblist[0]->query_possessive() +
        " face.");
    all2actbb(" kisses", oblist, "'s cheek, leaving a red lipstick "+
        "imprint on "+ oblist[0]->query_possessive() +" face.");

    setuid(); seteuid(getuid());
    kiss = clone_object(HERE +"kiss");
    kiss->move(oblist[0], 1);
    return 1;
}


/*
 *   dthrow
 */
int
dthrow(string str)
{
    object *oblist;

    if (!str)
    {
        notify_fail("Dthrow yourself into whose arms?\n");
	return 0;
    }

    oblist = parse_this(str, "[myself] [at] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dthrow yourself at who?\n");
        return 0;
    }
    
    target(" throws herself into your arms and showers you with "+
        "kisses.", oblist);
    actor("You throw yourself into", oblist, "'s "+
        "arms and shower "+ oblist[0]->query_objective() +
        " with kisses.");
    all2actbb(" throws herself into", oblist, "'s arms and showers "+
        oblist[0]->query_objective() +" with kisses.");
    return 1;
}

/*
 *     dspeak
 */
string *dspeak_adverbs = ({
    "seductively", "softly", "charmingly", "huskily",
    "provocatively", "bewitchingly", "persuasively", "sweetly",
    "suggestively", "casually", "languidly", "thrillingly",
    "tenderly", "amorously", "delectably", "delightfully"
});

varargs int 
dspeak(string str, string sayadv)
{
    object ob, *oblist = filter(all_inventory(ENV(TP)) - ({ TP }), living);
    
    int attrs = ACTION_AURAL | ACTION_INGRATIATORY;

    if (!stringp(str))
    {
	NF("Say what [to whom] in the breathy speech of the Dancers?\n");    
        return 0;
    }

    if (TP->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        NF("You seem to have suddenly become mute!\n");
        return 0;
    }

    if (!strlen(sayadv))
	sayadv = one_of_list(dspeak_adverbs);

    if (!parse_command(str, oblist, " 'to' [the] %o %s", ob, str))
    {
	if (TP->query_option(OPT_ECHO))
	{	    
	    write("You "+ sayadv +" breathe: "+ str +"\n");
	}
	else
	{
	    write("Ok.\n");
	}
	
	all(" "+ sayadv +" breathes: "+ str);
	return 1;
    }

    oblist = ({ ob });
    
    if (!strlen(str))
    {
    	NF("Say what [to whom] in the breathy speech of the Dancers?\n");
    	return 0; 
    }
    	   
    if (TP->query_option(OPT_ECHO))
    {   
    	actor("You "+ sayadv +" breathe to", oblist, ": "+ str +"\n");
    }
    else
    {
	write("Ok.\n");  
    }
    
    all2act(" "+ sayadv +" breathes to", oblist, ": " + str +"\n");
    target(" "+ sayadv +" breathes to you: "+ str, oblist, "", attrs);
    return 1;
}
/*
 * Allow to choose the adverbs.
 */
int
daspeak(string str)
{
    string *arr, *how;

    if (!strlen(str))
    {
        notify_fail("Syntax: "+ query_verb() +" <adverb> <text>\n");
        return 0;
    }

    /* We want a curated list, but the mudlib functions
     * don't readily allow for that.
     */
    how = explode(str, " ");
    if (sizeof(how) == 1)
	how = ({ "", 0 });

    arr = regexp(dspeak_adverbs, "^" + how[0]);

    if (sizeof(arr) != 1)
	how = ({ "", 0 });
    else
	how = ({ arr[0], implode(how[1..], " ") });

    if (!strlen(how[0]))
    {
        notify_fail("Cannot resolve \"" + explode(str, " ")[0] +
            "\" to an adverb.\nYou must choose from the following:\n"+
	    sprintf("   %-#74s\n", implode(sort_array(dspeak_adverbs), "\n")));
        return 0;
    }

    return dspeak(how[1], how[0]);
}
/*
 *     dstrut
 */
int
dstrut(string arg)
{
    if (!arg) 
    {
        write("At present, when you leave a room others see: "+
            capitalize(TP->query_real_name()) +" "+ 
            TP->query_m_out() +" <exit>.\n");
        return 1;
    }        

    if (arg == "on")
    {
        if (!TP->query_wiz_level())
//            TP->set_m_out("turns to walk away. Your eyes follow "+
//            "the gentle sway of her hips as she struts");
            TP->set_m_out("turns to walk away, her hips swaying "+
            "gently as she struts");        
        
        write("You are now ready to strut your stuff.\n"+
            "When you leave a room now, others will see: "+
            capitalize(TP->query_real_name()) +" "+
            TP->query_m_out() +" <exit>.\n");
        return 1;
    }
   
    if (arg == "off")
    {
        if (!TP->query_wiz_level())
            TP->set_m_out("leaves");
        TP->catch_msg("You change your stance. When you "+
            "leave a room, others will now see: "+
            capitalize(TP->query_real_name()) +" "+ 
            TP->query_m_out() +" <exit>.\n");
        return 1;
    } 
       
}

/*
 *    dtrace
 */
int
dtrace(string str)
{
    object *oblist;   

    if (!strlen(str))
    {
        NF("Dtrace your finger on who?\n");
        return 0;
    }
       
    oblist = parse_this(str, "[my] [finger] [on] [down] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dtrace your finger on who?\n");
        return 0;
    }
    
    actor("You trace your finger from the tip of", oblist, 
        "'s chin down to "+ oblist[0]->query_possessive() +
        " chest, where you whorl it gently over "+ 
        oblist[0]->query_possessive() +" heart.");
    target(" traces her finger from the tip of your chin "+
        "down to your chest, where she whorls it gently "+
        "over your heart.", oblist);
    all2actbb(" traces her finger from the tip of", oblist,
        "'s chin down to "+ oblist[0]->query_possessive() +
        " chest, where she whorls is gently over "+
        oblist[0]->query_possessive() +" heart.");
    return 1;

}
