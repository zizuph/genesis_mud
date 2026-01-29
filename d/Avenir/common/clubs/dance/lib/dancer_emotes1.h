// -*-C++-*-
// file name: 	  dancer_emotes1		
// creator(s):	  Gracie&Tep	July 1995
// update:	  Lilith 28 July 1997
// history:       Grace, 21 Nov 1995 (added emotes)
//                Boriska, 10 Oct 1995
// purpose:       An interesting club for females		
// note:          Contains emotes da - dk

// some filter functions
private int
male (object ob) { return ob->query_gender() == G_MALE; }

private int
female (object ob) { return ob->query_gender() == G_FEMALE; }

/*
 * 	dbeam
 */
int 
dbeam(string str)
{
    object *oblist;
 
    if (!str)
    {
        NF("Dbeam at who?\n");
        return 0;
    }

    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dbeam at who?\n");
        return 0;
    }

    targetbb(" beams at you, her face aglow with pleasure at "+
         "seeing you.", oblist);
    actor("You beam at", oblist, ", your face aglow with pleasure "+
         "in seeing "+ oblist[0]->query_objective() +".");
    all2actbb(" beams at", oblist, ", her face aglow with pleasure "+
         "in seeing "+ oblist[0]->query_objective() +".");
    return 1;
}

/*
 * 	dbeck  
 */
int
dbeck(string str)
{
    object *oblist;
 
    if (!str)
    {
        write("You crook your index finger in a beckoning motion.\n");
	allbb(" crooks her index finger in a beckoning motion.\n");
        SOULDESC("looking seductive");
	return 1;
    }
  
    oblist = parse_this(str, "[to] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dbeck to who?");
        return 0;
    }
    
    targetbb(" beckons to you with her index finger, an enigmatic "+
          "smile on her face.", oblist);
    actor("You beckon to", oblist, " with your index finger "+
         "and an enigmatic smile.");
    all2actbb(" beckons to", oblist, " with her index finger, "+
        "an enigmatic smile on her face.");
    SOULDESC("looking seductive");
    return 1;
}


/*
 * 	dblow
 */

int 
dblow(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You kiss your fingers and then blow on them.\n");
	allbb(" blows a kiss.");
	return 1;
    }
    
    oblist = parse_this(str, "[a] [kiss] [to] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dblow a kiss to who?\n");
        return 0;
    }
    
    targetbb(" blows you a kiss!", oblist);
    actor("You blow", oblist, " a kiss.");
    all2actbb(" blows", oblist, " a kiss!");
    return 1;
}

/*
 * 	dbored
 */

int
dbored(string str)
{
    if (strlen(str))
    {
        NF("Dbored " +str+ " can't be done.\n");
        return 0;
    }

    write("Feeling utterly bored, you study your "+
        "cuticles and fingernails closely.\n");
    allbb(" studies the fingernails on her left hand, an "+
        "expression of utter boredom on her face.");
    return 1;
}

/*
 * 	dchew
 */

int
dchew(string str)
{
    if (strlen(str))
    {
        NF("Dchew " +str+ " can't be done.\n");
        return 0;
    }

    write("You chew thoughtfully on your bottom lip.\n");
    allbb(" chews thoughtfully on her bottom lip.");
    SOULDESC("chewing thoughtfully on her lower lip");
    return 1;
}




/*
 * dflash
 */

int 
dflash(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You flash a fiery look full of temper and promise.\n");
	return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dflash at who?\n");
        return 0;
    }
    
    targetbb(" flashes you a fiery look full of temper and promise.", oblist);
    actor("You flash", oblist, " a fiery look full of temper and promise.");
    all2actbb(" flashes", oblist, " a fiery look full of temper and promise!");
    return 1;
}

/*
 *  	dglow
 */

int
dglow(string str)
{
    if (strlen(str))
    {
        NF("Dglow " +str+ " can't be done.\n");
        return 0;
    }

    write("You perform the beauty ritual of the Dancers, "+
        "hoping to Jazur and Sisera that your beauty and "+
        "vitality stand the test of time.\nThe ritual "+
        "leaves you glowing with renewed vitality and "+
        "luminous beauty.\n");
    allbb(" glows with renewed vitality and luminous "+
        "beauty.\n");
    SOULDESC("glowing with vitality");     
    return 1;
}


/*
 * 	dhair
 */

int
dhair(string str)
{
    if (strlen(str))
    {
        NF("Dhair " +str+ " can't be done.");
        return 0;
    }

    write("You idly twirl a lock of silken hair.\n");
    allbb(" idly twirls a lock of silken hair.");
    SOULDESC("twirling a lock of hair");
    return 1;
}

/*
 *       dhug
 */

int
dhug(string str)
{
    object *oblist;

    oblist = parse_this(str, "[for] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dhug who?\n");
        return 0;
    }

    if (sizeof(oblist) == 1)
        str = (string)oblist[0]->query_possessive();
    else
        str = "them";

    target(" twines her arms around your neck and arches her body "+
        "against yours in a warm, welcoming hug.", oblist);
    actor("You twine your arms around", oblist, "'s neck and arch "+
        "your body against "+str+" in a warm, welcoming hug.");
    all2actbb(" twines her arms around", oblist, "'s neck and "+
        "arches her body against "+str+ " in a warm hug.");
    return 1;
}

/* 
 *   dhuff
 */
int
dhuff(string str)
{
    object *oblist, *oblf = ({ }), *oblm = ({ });

    if (!str)
    {
        write("You turn your back in a huff.\n");
	allbb(" turns her back in a huff.");
        SOULDESC("looking inward");
	return 1;
    }
     
    oblist = parse_this(str, "[on] [the] %l ");
    oblist -= ({ this_player });
    
    if (!oblist || !sizeof(oblist))
    {
        NF("dhuff on who?\n");
        return 0;
    }

    oblf = filter(oblist, female);
    oblm = filter(oblist, male);

    if (oblf && sizeof(oblf))
    {
        actor("You turn your back on", oblf, " in a huff.");
        target(" turns her back on you in a huff, obviously quite "+
            "disgusted.", oblf);
        all2act(" turns her back on", oblf, " in a huff.");
        SOULDESC("in a huff");
        return 1;
    }

    if (oblm && sizeof(oblm))
    {
        actor("You turn your back on", oblm, ", pondering aloud "+
            "the obdurate, inconsiderate nature of the male species.");
        target(" turns her back on you in a huff and ponders aloud "+
            "the obdurate, inconsiderate nature of the male species "+
            "(meaning YOU, of course).", oblm);
        all2act(" turns her back on", oblm, " and ponders aloud the "+
            "obdurate, inconsiderate nature of the male species.");
        SOULDESC("in a huff");
    }
    return 1;
}

/*
 * 	dhum
 */

int
dhum(string str)
{
    if (strlen(str))
    {
        NF("Dhum " +str+ " can't be done.");
        return 0;
    }

    write("You hum a little tune and move your shoulders "+
        "sinuously.\n");
    allbb(" hums a little tune and moves her shoulders sinously.");
    SOULDESC("humming a tune");
    return 1;
}

/*
 *   	dhelp	(See dancer_soul.c)
 */


/*
 *   	dimmune
 */

int
dimmune(string str)
{
   object *oblist;

    if (!strlen(str))
    {
        write("Are you immune to your own charms?\n");
	return 1;
    }
  
    oblist = parse_this(str, "[to] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("You are immune to whose charms?\n");    
        return 0;
    }
    
    targetbb(" appears to be immune to your charms.", oblist);
    actor("You are immune to", oblist, "'s charms.");
    all2actbb(" appears to be immune to", oblist, "'s charms.");
    return 1;
}


/*
 * 	dinsult  
 */

int
dinsult(string str)
{

    object *oblist, *oblf = ({ }), *oblm = ({ });
    int hurl;
    
    oblist = parse_this(str, "[at] [the] %l ");
    oblist -= ({ this_player });
    
    if (!str || !oblist || !sizeof(oblist))
    {
        NF("Hurl an insult at who?\n");
        return 0;
    }

    oblf = filter(oblist, female);
    oblm = filter(oblist, male);
    
    if (oblf && sizeof(oblf))
    {
        hurl = random(3);
        switch(hurl)
        {
            case 0:
                actor("You hurl an insult at", oblf, ", calling "+
                    "her a scabby, diseased slattern.");
                target(" hurls an insult at you, calling you "+
                    "a scabby, diseased slattern.", oblf);
                all2act(" hurls an insult at", oblf,", calling her "+
                    "a scabby, diseased slattern.");
                break;
            case 1:
                actor("In a casual, offhand manner, you remark that "+
                    "if", oblf, " gets her looks from her mother, it "+
                    "is a wonder she was ever born.");
                target(" remarks, in a casual, offhand manner, that "+
                    "if you get your looks from your mother, it is a "+
                    "wonder you were ever born.", oblf);
                all2act(" remarks in a casual, offhand manner that "+
                   "if", oblf," gets her looks from her mother, it "+
                   "is a wonder she was ever born.");
                break;
            case 2:
                actor("You wonder aloud how someone as frigid and "+
                    "sexless as", oblf, " can call herself a woman.");
                target(" wonders how somwone as frigid and sexless "+
                    "as you can call herself a woman.", oblf);
                all2act(" wonders how someone as frigid and sexless "+
                    "as", oblf, " can call herself a woman.");
                break;
        }
    }
   
    if (oblm && sizeof(oblm))
    {
        hurl = random(3);
        switch(hurl)
        {
            case 0:
                actor("You hurl an insult at", oblm, " calling his " +
                    "manhood into question.");
                target(" deliberately insults you by calling your "+
                    "manhood into question,", oblm);
                all2act(" hurls an insult at", oblm,", calling his "+
                    "manhood into question.");
                break;
            case 1:
                actor("You make a show of studying", oblm, ". Finding "+
                    "him lacking in maleness, you declare him a 'eunuch.'");
                target(" seems to inspect you closely.\nA moment later "+
                    "she insults you deeply by calling you a eunuch.", oblm);
                all2act(" inspects", oblm," closely.\nA moment later "+
                    "she insults him, calling him a eunuch.");
                break;
            case 2:
                actor("You revile", oblm, " as a pathetic, grovelling "+
                    "worm desperately seeking a way to prove his lost "+
                    "manhood.");
                target("'s voice drips with venom and amusement as she "+
                    "labels you a pathetic, grovelling worm "+
                    "desperately seeking a way to prove his lost "+
                    "manhood.", oblm);
                all2act(" labels", oblm, " a pathetic, grovelling worm "+
                    "desperately seeking a way to prove his lost "+
                    "manhood.");
                break;
        }
    }
    return 1;
} 

/*
 *    dkill
 */
int
dkill(string str)
{
    object *oblist;

    if (!str)
    {
        NF("Dkill at who?\n");
        return 0;
    }

    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dkill at who?\n");
        return 0;
    }

    actor("If looks could kill,", oblist," would be dead."); 
    oblist[0]->catch_msg("If the look "+ QCNAME(TP) +" just gave "+
         "you could kill, you would be dead.\n");
    return 1;
}    

/*
 *    dkiss
 */
int
dkiss(string str)
{
    object *oblist;

    if (!str)
    {
        NF("Dkiss whom?\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dkiss whom?\n");
        return 0;
    }

    actor("You press your mouth to", oblist,"'s in a tender, "+
        "lingering kiss."); 
    target(" presses her mouth to yours in a tender, lingering kiss.", 
        oblist);
    all2actbb(" presses her mouth to", oblist, "'s in a tender, "+
        "lingering kiss.");
    SOULDESC("looking dreamy-eyed");

    return 1;
}    

  


