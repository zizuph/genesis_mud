/* 
 *  The emotions of the Dragon Order, from I - P
 *
 *  Transferred into an .h file by 	Cirion, 160496
 *  Emotes updated and added by 	Lilith, 01 Feb 99
 */

/*
 * Function name: aod_inspired
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int
aod_inspired(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You stand momentarily transfixed by a shaft of "+
            "inspiration as one of the teachings of Segoy becomes "+
            "suddenly clear to you.\n");
        allbb(" stands momentarily transfixed, an ecstatic, "+
            "enlightened look upon "+ HIS(TP) +" face.");
        SOULDESC("standing transfixed");
        return 1;
    }

    oblist = parse_this(str, "[by] [the] / [a] %i");
    if(!sizeof(oblist))
    {
         notify_fail("Whom or what art thou inspired by?\n");
         return 0;
    }
    
    actor("You are so inspired by", oblist, " that you stand as "+
        "though transfixed, suffused with enlightened ecstacy.");
    targetbb(" stands as though transfixed, apparently inspired "+
        "by you on a deeply spiritual level.", oblist);
    all2actbb(" stands as though transfixed, apparently inspired "+
        "by", oblist," on a deeply spiritual level.");    
    return 1;
}

int 
kiai_access(object ob)
{
    if (!living(ob))
        return 0;

    if (!CAN_SEE(TP, ob))
        return 0;

    if (ob == TP)
        return 0;

    /* Only normal monsters (not creatures like dragons)
     * can be affected by the combat cry 
     */
    if (!interactive(ob) && !function_exists("create_monster", ob))   
        return 0;

    return 1;
}

/*
 * Function name: aod_kiai
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_kiai(string str)
{
    int      skill,
             i;
    string   how;
    object  *people;
   
    if (str) 
    {
        notify_fail("Kiai what?\n");
        return 0;
    }    

    if (TP->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        notify_fail("You cannot seem to use your mouth.\n");
        return 0;
    }
   
    if (TP->query_fatigue() < 4)
    {
        notify_fail("You are too tired to utter a combat cry.\n");
        return 0;
    }

    /* Players must put a lot of effort into this combat cry if 
     * they are going to be able to scare their opponents with it.
     */
    TP->add_fatigue(-15);

    skill = this_player()->query_skill(SS_UNARM_COMBAT);

    switch(skill)
    {
        case -10 .. 5:  how = "tiny";         break;
        case 6 .. 10:   how = "pathetic";     break;
        case 11 .. 20:  how = "amateur";      break;
        case 21 .. 28:  how = "loud";         break;
        case 29 .. 36:  how = "rather loud";  break;
        case 37 .. 50:  how = "very loud";    break;
        case 51 .. 65:  how = "roaring";      break;
        case 66 .. 80:  how = "titanic";      break;
        case 81 .. 90:  how = "deafening";    break;
        case 91 .. 120: how = "heroic, dragon-like";
                                              break;
        default:         how = "simple";   break;
    }

    write("You utter "+LANG_ADDART(how)+" combat cry.\n");
    all(" utters "+LANG_ADDART(how)+" combat cry.");


    /*
     * Cirion: removed at the request of Teth
    people = filter(all_inventory(environment(TP)), kiai_access) -
             ({TP});

    for(i=0;i<sizeof(people);i++)
    {
        if(people[i]->query_stat(SS_DIS) > skill * 3 / 2)
        {
            people[i]->catch_msg("You are unimpressed.\n");
            tell_room(environment(people[i]), QCTNAME(people[i])
                +" looks completely unimpressed.\n", people[i]);
            continue;
        }

        switch((skill * 3 / 2) - people[i]->query_stat(SS_DIS) - 
              random(10))
        {
            case -100 .. 5:
                people[i]->catch_msg("You are slightly impressed.\n");
                tell_room(environment(people[i]), QCTNAME(people[i])
                    +" looks slightly impressed.\n", people[i]);
                continue;
            case 6 .. 15:
                people[i]->catch_msg("You are somewhat impressed.\n");
                tell_room(environment(people[i]), QCTNAME(people[i])
                    +" looks somewhat impressed.\n", people[i]);
                continue;
            case 16 .. 25:
                people[i]->catch_msg("You are rather impressed.\n");
                tell_room(environment(people[i]), QCTNAME(people[i])
                    +" looks rather impressed.\n", people[i]);
                continue;
            case 26 .. 35:
                people[i]->catch_msg("You are somewhat impressed.\n");
                tell_room(environment(people[i]), QCTNAME(people[i])
                    +" looks somewhat impressed.\n", people[i]);
                continue;
            case 36 .. 46:
                people[i]->catch_msg("You are a bit nervous.\n");
                tell_room(environment(people[i]), QCTNAME(people[i])
                    +" looks a little bit nervous.\n", people[i]);
                people[i]->add_panic(1);
                continue;
            case 47 .. 56:
                people[i]->catch_msg("You are somewhat nervous.\n");
                tell_room(environment(people[i]), QCTNAME(people[i])
                    +" looks somewhat nervous.\n", people[i]);
                people[i]->add_panic(3);
                continue;
            case 57 .. 66:
                people[i]->catch_msg("You are very nervous.\n");
                tell_room(environment(people[i]), QCTNAME(people[i])
                    +" looks very nervous.\n", people[i]);
                people[i]->add_panic(5);
                continue;
            case 67 .. 76:
                people[i]->catch_msg("You are scared.\n");
                tell_room(environment(people[i]), QCTNAME(people[i])
                    +" looks scared.\n", people[i]);
                people[i]->add_panic(10);
                if(interactive(people[i]) && people[i]->query_panic()
                    == people[i]->query_max_panic())
                people[i]->run_away();
                continue;
            case 77 .. 86:
                people[i]->catch_msg("You are terrified.\n");
                tell_room(environment(people[i]), QCTNAME(people[i])
                    +" looks terrified.\n", people[i]);
                people[i]->add_panic(20);
                if(interactive(people[i]) && people[i]->query_panic()
                    == people[i]->query_max_panic())
                people[i]->run_away();
                continue;
            default:
                people[i]->catch_msg("You feel like you are about "+
                    "to have a heart attack.\n");
                tell_room(environment(people[i]), QCTNAME(people[i])
                    +"'s face goes white, and looks like "
                    +people[i]->query_possessive()+" is about "
                    +"to pass out.\n", people[i]);
                people[i]->add_panic(40);
                if(interactive(people[i]) && people[i]->query_panic()
                    == people[i]->query_max_panic())
                people[i]->run_away();
                continue;
        }    

    }

    */

    return 1;
}

/*
 * Function name: aod_kill
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_kill(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        notify_fail("Whom dost thou wish to kill?\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %l");
    oblist -= ({ this_player() });

    if (!sizeof(oblist))
    {
        notify_fail("Whom dost thou wish to kill?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("It is possible to attack but one person "+
            "at a time.\n");
        return 0;
    }

    targetbb("'s face looks serenely determined as "+ HE(TP) +
        " focuses "+ HIS(TP) +" eyes upon you and slips fluidly "+
        "into a distinctly martial stance.", oblist);
    actor("Mind and body become one as you fluidly slip into "+
        "a stance from which you can attack", oblist);
    TP->command("$kill "+ str);
    return 1;
}

/*
 * Function name: aod_knuckles
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_knuckles(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "gingerly", 0);
 
    if (!strlen(how[0]))
    {
        write("You nurse your knuckles" + how[1] + ", in " +
            "hopes the pain will subside.\n ");
        allbb(" nurses "  + TP->query_possessive() + " knuckles"
            +how[1] + ", in an effort to stop the pain.");
        return 1;
    }

    if (!sizeof(oblist = parse_this(how[0], "[to] [the] %l")))
    {
        notify_fail("Whose knuckles dost thou wish to tend to?\n");
        return 0;
    }

    targetbb(how[1] + " tends to your wounded knuckles.", oblist);
    actor("You nurse", oblist, "'s knuckles" +how[1] +", in an "+
        "effort to stop the pain.");
    all2actbb(how[1] +" nurses", oblist, "'s knuckles.");
    return 1;
}

/*
 * Function name: aod_look
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int
aod_look(string str)
{
    object *oblist;
    string *how;
    string a, b;

    if (m_query_monk(TP, SS_OCCUP))
        how = parse_adverb_with_space(str, "confidently", 0);
    else
        how = parse_adverb_with_space(str, "carefully", 0);

    if (!strlen(how[0]))
    {
         write("You look"+ how[1] +" about you, feeling "+
             "completely secure and self-reliant.\n");
         all(" looks" + how[1] + " around, to all appearances quite "+
             "secure and self-reliant.");
         SOULDESC("looking dangerous");
         return 1;
    }

    if (!sizeof(oblist = parse_this(how[0], "[at] [the] %l")))
    {
        notify_fail("Whom dost thou wish to look at?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("Such a look as thou wouldst give may only "+
            "be done to one person at a time.\n");
        return 0;
    }

    if (m_query_monk(TP, SS_OCCUP))
    {
        a = HE(oblist[0]) +" appears to entertain "+
               "second-thoughts about trifling with you.";
        //b = "\nPerhaps you should not trifle with "+ HIM(TP) +
        //    " after all.";
        b = "";
    }
    else
    {
        a = "you hope "+ HE(oblist[0]) +" will think twice "+
            "before trifling with you.";
        b = "";
    }

    actor("You"+ how[1] + " look", oblist, " over, so secure in your "+
        "abilities that "+ a);
    target(" looks"+ how[1] +" at you, to all appearances quite "+
        "secure and self-reliant." + b, oblist);
    all2act(" looks" + how[1] + " at", oblist, ", to all appearances "+
        "quite secure and self-reliant.");
    return 1;
}

/*
 * Function name: aod_pray
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int 
aod_pray(string str)
{
    if (strlen(str))   
        return 0;
 
    write("You pray that the strength and wisdom you are developing "+
        "through your study of the dragon-discipline will not fail "+
        "you in your moment of need.\n");
    allbb(" appears to concentrate for a long moment, as though in "+
         "prayer.");
    SOULDESC("looking pious");
    
    return 1;
}

/*  Pity
 */
/* Is the target of the emote wielding a weapon? */
object
check_weapon(object ob)
{
    object *o_weapons;
    object w;

    o_weapons = ob->query_weapon(-1);

    if (sizeof(o_weapons))
        w = o_weapons[0];

    if (w)
        return w;      
}

/*
 * Function name: aod_pity
 * Description:   
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
int
aod_pity(string str)
{
    object *oblist;
    object  wep;
 
    if (!strlen(str))
    {
        write("You find yourself pitying all those who are lacking "+
            "in dragon-discipline.\n");
        allbb(" looks about "+ HIM(TP) +" with an expression of "+
            "pity on "+ HIS(TP) +" face.");
        return 1;
    }

    if (!sizeof(oblist = parse_this(str, " [for] [a] / [the] %l"))) 
    {
        notify_fail("Whom dost thou feel pity for?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("Thou may pity but one person at a time in "+
            "this way.\n");
        return 0;
    }

    wep = check_weapon(oblist[0]);
    if (!wep)
    {
        if (m_query_monk(oblist[0], SS_OCCUP))
        {
            notify_fail("Why wouldst thou pity one who is mastering "+
                "unarmed combat for a dependancy upon weapons?\n");
            return 0;
        }
        actor("You pity", oblist," "+ HIS(oblist[0]) +" dependence "+
            "upon weapons.");
        targetbb(" appears to pity you your dependence upon weapons.",
            oblist);
        all2actbb(" appears to pity", oblist, " "+ HIS(oblist[0]) +
            " dependance upon weapons.");
        return 1;
    }

    actor("You look from", oblist," to the "+ wep->short() +" "+
        HE(oblist[0]) +" wields, pitying "+ HIM(oblist[0]) +" "+
        HIS(oblist[0]) +" dependance upon weapons.");
    targetbb(" looks from you to your "+ wep->short() +" and back, "+
        "a look of pity upon "+ HIS(TP) +" face.", oblist);
    all2actbb(" looks from", oblist," to the "+ wep->short() +" "+
        HE(oblist[0]) +" wields, a look of pity on "+ HIS(TP) +
        " face.", oblist);
    return 1;
}

                
