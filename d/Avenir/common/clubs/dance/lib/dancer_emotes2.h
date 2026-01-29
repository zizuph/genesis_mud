// -*-C++-*-
// file name: 	  dancer_emotes1		
// creator(s):	  Gracie&Tep	July 1995
// update:	  Lilith 28 July 1997
// history:       Grace, 21 Nov 1995 (added emotes)
//                Boriska, 10 Oct 1995
// purpose:       for dancer emotes dl - dz

/*
 * 	dlean
 */

int
dlean(string str)
{
    object *oblist;   

    if (!strlen(str))
    {
        NF("Dlean against who?\n");
        return 0;
    }
       
    oblist = parse_this(str, "[on] [against] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dlean against who?\n");
        return 0;
    }
    
    actor("You lean your body against", oblist, ", offering "+
        "your mouth for a kiss.");
    target(" leans her warm, fragrant body against yours "+
        "and offers her mouth to be kissed.", oblist);
    all2actbb(" leans against", oblist,", offering her "+
        "mouth for a kiss.");
    return 1;
}

/*
 * 	dlook
 */

int
dlook(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        NF("Dlook at who?\n");
        return 0;
    }
   
    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dlook at who?\n");
        return 0;
    }

    actor("You boldly give", oblist, " a sultry look.\n");
    targetbb(" looks at you with bold, sultry eyes.", oblist);
    all2actbb(" boldy gives", oblist," a sultry look.");
    SOULDESC("looking very sultry");
    return 1;
}


/*
 *   	dmouth
 */

int
dmouth(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You moisten your lips with the tip of your tongue "+
            "in a blatant invitation to be kissed.\n");
        allbb(" runs the tip of her tongue along her lips, "+
            "leaving you with "+
	    "the impression that she wants to be kissed.");
	return 1;
    }
  
    oblist = parse_this(str, "[for] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dmouth for who?\n");
        return 0;
    }

    if (sizeof(oblist) == 1)
        str = (string)oblist[0]->query_objective();
    else
        str = "them";

    targetbb(" slowly traces the contours of her mouth "+
        "with the tip of her tongue in a blatant invitation "+
        "to be kissed!", oblist);
    actor("You slowly trace the contours of your mouth with the "+
        "tip of your tongue, blatantly inviting", oblist, " to "+
        "kiss you.");
    all2actbb(" seems to invite", oblist, " to kiss her by looking "+
        "steadily at "+str+ " while slowly "+
        "tracing the contours of her mouth with the tip of her "+
        "tongue.");
    return 1;
}

/*
 *     doffer
 */

int
doffer(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You offer your bottom to be spanked.\n");
        allbb(" offers her bottom to be spanked.");
	return 1;
    }

    oblist = parse_this(str, "[to] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Doffer your bottom to be spanked by who?\n");
        return 0;
    }

    targetbb(" offers her bottom to you for spanking.", oblist);
    actor("You offer your bottom to", oblist, " to be spanked.");
    all2actbb(" offers", oblist, " her bottom for spanking.");
    return 1;
}

/*
 *    dperf
 */
int
dperf(string str)
{
    if (strlen(str))
    {
         NF("Dperf " +str+ " can't be done.\n");
         return 0;
    }
    
    write("You refresh your perfume. The scents of balsam and "+
        "patchouli blended with cinnamon and sandalwood emanate "+
        "from you.\n");
    allbb(" refreshes her perfume. The scents of balsam and patchouli "+
        "blended with cinnamon and sandalwood emanate from her.");
    return 1;  
}

/*
 *   dpir
 */  
int
dpir(string str)
{
    if (strlen(str))
    {
         NF("Dpir " +str+ " can't be done.\n");
         return 0;
    }
    
    write("Poised and confident, you perform a demanding pirhouette "+ 
        "that emphasizes the strength and flexibility of your legs.\n");
    allbb(" performs a demanding pirhouette with poise and confid"+
        "ence, the strength and flexibility of her legs revealing "+
        "her superb training as a dancer.");
    return 1;  
}

/*
 *   
 */

int
dpoke(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You poke yourself in the sternum.\n");
	return 1;
    }
  
    oblist = parse_this(str, "[in] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dpoke who?");        
        return 0;
    }

    if (sizeof(oblist) == 1)
        str = (string)oblist[0]->query_possessive();
    else
        str = "their";

    target(" pokes you in the sternum with stiffened fingers.\n"+
        "The air whooshes out of your lungs and you find it "+
        "difficult to breathe.", oblist);
    actor("You poke", oblist, " in the sternum with stiffened "+
       "fingers.\nThe air whooshes out of " + str +" lungs, "+
       "making it difficult to breathe.");        
    all2actbb(" pokes", oblist, " in the sternum with stiffened "+
       "fingers.\nThe air whooshes out of "+ str +" lungs.");        
    SOULDESC("looking very irritated");
    return 1;
}


/*
 *   dpout
 */
int
dpout(string str)
{
    object *oblist, *oblf = ({ }), *oblm = ({ });
  
    if (!strlen(str))
    {
        write("You purse your mouth in an adorable pout.\n");
        allbb(" purses her mouth in an adorable pout.");
        SOULDESC("pouting adorably");
        return 1;
    }
  
    oblist = parse_this(str, "[at] [the] %l");
    
    if (!oblist || !sizeof(oblist))
    {
        NF("Dpout at who?\n");
        return 0;
    }
    
    oblf = filter(oblist, female);
    oblm = filter(oblist, male);
    
    if (oblf && sizeof(oblf))
    {
        actor("You pout adorably at", oblf, ".");
        targetbb(" pouts at you, looking truly adorable.", oblf);
        all2actbb(" pouts adorably at", oblf,".");
    }

    if (oblm && sizeof(oblm))
    {
        actor("You give", oblm, " your most adorable, " +
            "kissable, and irresistable pout.");
        targetbb(" pouts at you, looking adorable, kissable, and "+
            "thoroughly irresistable.", oblm);
        all2actbb(" pouts adorably at", oblm,".");
    }
    SOULDESC("pouting adorably");
    return 1;
} 
/*
 *    drub
 */
int
drub(string str)
{
    object *oblist;
 
    if (!str)
    {
        NF("Drub who?\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Drub who?\n");
        return 0;
    }

    target("'s gentle fingers knead the muscles of your neck and "+
        "shoulders.\nYou feel soothed and relaxed by her ministrat"+
        "ions.", oblist);
    actor("Your fingers gently knead", oblist, "'s neck and shoulder "+
        "muscles.");
    actor("Your ministrations appear to have soothed and "+
        "relaxed", oblist, ".");
    all2actbb(" gently kneads", oblist, "'s neck and shoulder muscles.");
    return 1;
}

/*
 *   	dsigh
 */

int
dsigh(string str)
{

    object *oblist, *oblf = ({ }), *oblm = ({ });
    
    if (!strlen(str))
    {
        write("You sigh in such a way as to make your bosom "+
            "heave appealingly.\n");
        allbb(" sighs in such a way as to make her bosom "+
            "heave appealingly."); 
        return 1;
    }
    
    oblist = parse_this(str, "[at] %l ");
    oblist -= ({ this_player });

    if (!oblist || !sizeof(oblist))
    {
        NF("You heave a long sigh.\n");
        return 0;
    }

    oblf = filter(oblist, female);
    oblm = filter(oblist, male);
        
    if (oblf && sizeof(oblf))
    {
        actor("You heave a long sigh that draws", oblf, "'s eyes to " +
            "your bosom.");
        targetbb(" sighs, making her lovely bosom heave "+
            "appealingly.", oblf);
        all2actbb(" heaves a long sigh that draws", oblf,"'s eyes to her " +
            "bosom.");
    }
   
    if (oblm && sizeof(oblm))
    {
        actor("You heave a long sigh that causes", oblm, " to stare " +
            "at your bosom in admiration.");
        targetbb(" sighs, making her lovely bosom heave "+
            "appealingly.", oblm);
        all2actbb(" heaves a long sigh that causes", oblm," to stare "+
            "at her bosom in admiration.");
    }
    return 1;
} 

/* 
 *   dsmile
 */
int
dsmile(string str)
{
    object *oblist;
 
    if (!str)
    {
        write("Your mouth curls upward in a small, enigmatic smile.\n");
	allbb("'s mouth curls upward in a small, enigmatic smile.");
        SOULDESC("looking enigmatic");
	return 1;
    }
  
    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dsmile at who?\n");
        return 0;
    }
    
    targetbb(" looks at you, and a small, enigmatic smile curls "+
         "her lips.", oblist);
    actor("You look at", oblist, " and a small, enigmatic smile "+
         "curls your lips.");
    all2actbb(" looks at", oblist, ", and a small, enigmatic "+
         "smile curls her lips.");
    SOULDESC("looking enigmatic");
    return 1;
}
 
/*
 *   dsmooth
 */
int
dsmooth(string str)
{
    if (strlen(str))
    {
        NF("Dsmooth " +str+ " can't be done.\n");
        return 0;
    }

    write("You run your hands over your shapely figure, smoothing "+
        "the lines of your clothing.\n");
    allbb(" runs her hands over her clothing and draws your attention "+
        "to her shapely curves.");
    return 1;
}

/*
 *   	dstick
 */

int
dstick(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You stick your tongue out.\nDon't you "+
            "feel wonderfully childish?\n");
        allbb(" sticks her tongue out.");
        return 1;
    }
  
    oblist = parse_this(str, "[at] [the] %l");
    if (!sizeof(oblist))
    {
        NF("Dstick at who?\n");
        return 0;
    }

    targetbb(" sticks her tongue out at you.", oblist);
    actor("You stick your tongue out at", oblist, ".");
    all2actbb(" sticks her tongue out at", oblist, ".");
    return 1;
}

/*
 *   dstretch
 */
int
dstretch(string str)
{

   if (strlen(str))
      {
         NF("Dstretch "+ str +" can't be done.\n");
         return 0;
      }

     write("Standing on tip-toes, you raise your hands above your "+
        "head and stretch first one arm and then the other, luxur"+
        "iating in the feeling it gives you.\n");
     allbb(" stands on tip-toes and with sinuous grace stretches "+
        "one arm high above her head, then the other.");
     return 1;
}

/* 
 *   dswoon
 */
int
dswoon(string str)
{
    object *oblist, *oblf = ({ }), *oblm = ({ });

    if (!str)
    {
        write("Overcome with emotion, you fall to the "+
            "ground in a swoon.\n");
	allbb(" is overcome with emotion, and falls to the "+
            "ground in a swoon.");
        SOULDESC("swooning");
	return 1;
    }
     
    oblist = parse_this(str, "[on] [the] %l ");
    oblist -= ({ this_player });
    
    if (!oblist || !sizeof(oblist))
    {
        NF("dswoon on who?\n");
        return 0;
    }

    oblf = filter(oblist, female);
    oblm = filter(oblist, male);

    if (oblf && sizeof(oblf))
    {
        actor("Overcome with emotion, you fall against", oblf, " "+
            "in a swoon.");
        target(" suddenly appears overcome with emotion. She falls "+
            "against you in a swoon.", oblf);
        all2actbb(" suddenly appears to be overcome with emotion. She "+
            "falls against", oblf, " in a swoon.");
        SOULDESC("swooning");
        return 1;
    }

    if (oblm && sizeof(oblm))
    {
        actor("Overcome with rapturous emotions, you fall into the "+
            "shelter of", oblm, "'s strong arms in a swoon.");
        target(" suddenly appears to be overcome with emotion. She "+
            "falls into your arms in a swoon.", oblm);
        all2actbb(" suddenly appears to be overcome with emotion. She "+
            "falls into", oblm, "'s arms in a swoon.");
        SOULDESC("swooning");
    }
    return 1;
}

/*
 *   dthigh
 */
int
dthigh(string str)
{
    object *oblist;

    if (!str)
    {
        write("You trail your fingers along the outline of your thigh "+
            "stroking it absentmindedly.\n");
	allbb(" trails her fingers along the outline of her thigh, "+
            "stroking it absentmindedly.");
        SOULDESC("looking inward");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dthigh who?\n");
        return 0;
    }
    
    targetbb(" trails her fingers along the outline of your thigh, "+
          "stroking it absentmindedly.\nYour flesh tingles in the "+
          "aftermath of her hand's passage.", oblist);
    actor("You trail your fingers along the outline of", oblist, "'s "+
          "thigh, stroking it absentmindedly.");
    all2actbb(" trails her fingers along the outline of", oblist, "'s "+
          "thigh, stroking it absentmindedly.");
    return 1;
}

/*
 *    dthink
 */
int
dthink(string str)
{

   if (strlen(str))
      {
         NF("Dthink "+ str +" can't be done.\n");
         return 0;
      }

     write("You click together the long, painted fingernails templed "+
         "beneath your chin, apparently deep in thought.\n");
     allbb(" repeatedly clicks together the long, painted fingernails "+
         "templed beneath her chin, apparently deep in thought.");
     return 1;
}


