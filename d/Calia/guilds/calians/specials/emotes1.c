
/*      
        This is the first set of emotes for the Calian warrior's guild.
        It is included into the calian cmdsoul.

    coder(s):   Maniac & Glykron
    history:
               26/4/02   Updated for trainees            Maniac
                2/4/98   cknock, cintro, cnod added      Maniac
                4/4/96   water checks +  chonk, caggr, 
                                          cl, cpace      Maniac
                14/7/95     cni added                    Maniac
                28.4.95     ctaunt added                 Maniac
                10.4.95     cpledge typo taken out       Maniac
                29.3.95     cwarn improved               Maniac
                28.3.95     calian_pledge emote added    Maniac
                15.3.95     split off from cmdsoul       Maniac
                21.3.95     cshake problem solved        Maniac
*/


int
calian_taunt(string str)
{
    object *oblist;
    string s;

    if (!IS_CALIAN_WARRIOR(this_player())) 
    { 
        notify_fail("Only Calian Warriors can do that.\n"); 
        return 0; 
    } 

    if (!strlen(str))
    { 
        notify_fail("Ctaunt whom?\n");
        return 0;
    } 

    UNDER_WATER_BLOCK; 
   
    oblist = parse_this(str, "%l");
    if (!sizeof(oblist))
    {
        notify_fail("Ctaunt whom?\n");
        return 0;
    }

    if (sizeof(oblist) != 1)
    {
        notify_fail("You cannot taunt everyone at the same time!\n");
        return 0;
    }
    setuid();
    seteuid(getuid());
    s = CALIAN_TAUNT_OBJECT->query_insult();
    target(" taunts you, saying: " + s, oblist);
    actor("You taunt",oblist,", saying: " + s);
    all2act(" taunts",oblist,", saying: " + s);
    return 1;
}


int
calian_knock(string str)
{
    object *oblist, helm;
    string helm_desc; 

    notify_fail("Cknock whom?\n");
    if (!strlen(str))
        return 0;

    if (str == "me" || str == "myself") {
        if (objectp(helm = this_player()->query_armour(A_HEAD)))
            helm_desc = helm->short(); 
        else 
            helm_desc = "head"; 

        this_player()->catch_msg("You knock on your " + helm_desc + ".\n");  
        all(" knocks on " + this_player()->query_possessive() + 
            " " + helm_desc + "."); 
     
        return 1;
    }

    oblist = parse_this(str, "%l");
    if (!sizeof(oblist))
        return 0;

    if (sizeof(oblist) != 1)
    {
        notify_fail("You cannot knock on everyone's head at the same time!\n");
        return 0;
    }

    if (objectp(helm = oblist[0]->query_armour(A_HEAD)))
        helm_desc = helm->short(); 
    else 
        helm_desc = "head"; 

    target(" knocks on your " + helm_desc + ".", oblist);
    actor("You knock on",oblist,"'s " + helm_desc + ".");
    all2act(" knocks on",oblist,"'s " + helm_desc + ".");
    return 1;
}


int
calian_nod(string str)
{
    object *oblist, helm, tp;
    string helm_desc, *how; 

    tp = this_player(); 

    if (objectp(helm = tp->query_armour(A_HEAD)))
        helm_desc = helm->short(); 
    else {
        notify_fail("You have to be wearing a helm to use <cnod>.\n"); 
        return 0; 
    }

    how = parse_adverb(str, "", 0);
    if (strlen(how[1]))
        how[1] = " " + how[1]; 

    if (!strlen(how[0]))
    {
        write("You nod your " + helm_desc + how[1] + ".\n"); 
        allbb(" nods " + tp->query_possessive() + " " + helm_desc +
              how[1] + "."); 
        return 1;
    }

    oblist = parse_this(how[0], "%l");
    if (!sizeof(oblist)) {
        notify_fail("Cnod [how] [at whom]?\n"); 
        return 0;
    }

    actor("You nod your " + helm_desc + how[1] + " at", oblist);
    targetbb(" nods " + tp->query_possessive() + " " + 
             helm_desc + how[1] + " at you.", oblist);
    all2actbb(" nods " + tp->query_possessive() + " " + 
              helm_desc + how[1] + " at", oblist);
    return 1;
}


int
calian_intro(string str)
{
    object *oblist, tp;
    string title;

    if (!stringp(title = this_player()->query_calian_special_title())) {
        notify_fail("You need to have a special Calian title set to " +
                    "use this emote.\n"); 
        return 0;
    }
 
    title = ("the " + title + " of Calia"); 

    tp = this_player(); 
    if (!strlen(str)) {
        write("You introduce yourself as " + title + ".\n"); 
        all(" introduces " + tp->query_objective() + "self as " +
            title + "."); 
        return 1;
    } 

    oblist = parse_this(str, "[to] %l");
    if (!sizeof(oblist)) {
        notify_fail("Cintro [to whom]?\n");
        return 0;
    }

    target(" introduces " + tp->query_objective() + "self to you " +
           "as " + title + ".", oblist);
    actor("You introduce yourself to", oblist, " as " + title + ".");
    all2act(" introduces " + tp->query_objective() + "self to", 
           oblist, " as " + title + ".");
    return 1;
}


int
calian_ni(string str)
{
    object *oblist;
    string s, result;

    if (!IS_CALIAN_WARRIOR(this_player())) 
    { 
        notify_fail("Only Calians Warriors can do that.\n"); 
        return 0; 
    } 

    if (!strlen(str))
    { 
        notify_fail("Say `Ni!' to who?\n");
        return 0;
    } 

    UNDER_WATER_BLOCK;

    oblist = parse_this(str, "%l");
    if (!sizeof(oblist))
    {
        notify_fail("Say `Ni!' to who?\n");
        return 0;
    }

    if (sizeof(oblist) != 1)
    {
        notify_fail("You cannot scream `Ni!' at everyone at the same time!\n");
        return 0;
    }

    if (oblist[0]->query_wiz_level()) {
        notify_fail("Nah, it's too rude to scream `Ni!' at a wizard!\n");
        return 0;
    }

    if ((TP->query_stat(SS_DIS)+random(25)) <
        (oblist[0]->query_stat(SS_DIS)+random(25)-45))
    {
        target(" screams `Ni!' at you. You grit your teeth "+
            "and absorb the full force of the assault.",oblist);
        actor("You scream `Ni!' at",oblist,", who grits "+
               oblist[0]->query_possessive()+
               " teeth and absorbs the full force of the assault.");
        all2act(" screams `Ni!' at",oblist,", who grits "+
            oblist[0]->query_possessive()+
            " teeth and absorbs the full force of the assault.");
        return 1;
    }
    if ((TP->query_stat(SS_STR)+random(25)) <
        (oblist[0]->query_stat(SS_STR)+random(25)-45))
         {
             target(" screams `Ni!' at you. You momentarily " +
                    "buckle under the force of the assault.",oblist);
             actor("You scream `Ni!' at",oblist,", who momentarily "+
                    "buckles under the force of the assault.");
             all2act(" screams `Ni!' at",oblist,", who momentarily " +
                    "buckles under the force of the assault.");
             return 1;
         }
      target(" screams `Ni!' at you. You collapse in a quivering heap " +
             "on the ground.",oblist);
      actor("You scream `Ni!' at",oblist,", who collapses "+
            "in a quivering heap on the ground.");
      all2act(" screams `Ni!' at",oblist,", who collapses " +
              "in a quivering heap on the ground.");
      return 1;
}


int
calian_shake(string pred)
{
    object *obs, ob, tp, this, *list, *everyone, *success_list, *fail_list;
    int i;
    string s;

    NF("You shake hands with whom in the manner of Calia?\n");

    if (!pred)
        return 0;

    obs = parse_this(pred, "[hands] [with] %l");

    if (!sizeof(obs))
        return 0;

    tp = TP;
    this = THIS;
    everyone = FILTER_LIVE(all_inventory(environment(tp))) - ({ tp });
    success_list = filter(obs, "is_calian", this);
    fail_list = obs - success_list;

    if (sizeof(success_list))
        tp->catch_msg("You shake hands with " +
            COMPOSITE_LIVE(success_list) + " by putting your two " +
            "forefingers on top in the manner of Calia.\n");

    if (sizeof(fail_list))
        tp->catch_msg("You attempt to shake hands with " +
            COMPOSITE_LIVE(fail_list) + " by putting your two forefingers on " +
            "top, but " + (sizeof(fail_list) == 1 ?
            fail_list[0]->query_pronoun() + " does " : "they do ") +
            "not know the hand shake.\n");

    for (i = 0; i < sizeof(success_list); i++)
    {
        ob = success_list[i];
        ob->catch_msg(QCTNAME(tp) + " shakes hands with you by putting " +
            tp->query_possessive() + " two forefingers on top in the manner " +
            "of Calia.\n");
    }

    for (i = 0; i < sizeof(fail_list); i++)
    {
        ob = fail_list[i];
        ob->catch_msg(QCTNAME(tp) + " attempts to shake hands with you " +
            "in a rather strange manner, but you do not know the hand " +
            "shake and are unable to do it.\n");
    }

    for (i = 0; i < sizeof(everyone); i++)
    {
        ob = everyone[i];
        if (is_calian(ob)) {
            list = success_list - ({ ob });

            if (sizeof(list)) {
                /* Set up for use in QCOMPLIVE */
                s = COMPOSITE_LIVE(list); 

                ob->catch_msg(QCTNAME(tp) + " shakes hands with " +
                    QCOMPLIVE + " in the manner of Calia.\n");
            }
        }
        else
            if (sizeof(success_list)) {
                /* Set up for use in QCOMPLIVE */
                s = COMPOSITE_LIVE(success_list);

                ob->catch_msg(QCTNAME(tp) + " shakes hands with " +
                    QCOMPLIVE + " in a rather strange manner.\n");
            }
    }

    return 1;
}

/*
 * Function name: calian_song
 * Description:   A Calian emote which enables a Calian to sing
                  one of a number of Calian folk songs, chosen 
                  randomly
 * Arguments:     none
 * Returns:       integer indicating success or failure (1 or 0)
 */
int
calian_song()
{
    string song_subj;
    object tp;
    int rnd_num;

    UNDER_WATER_BLOCK; 

    tp = TP;
    rnd_num = random(7, time());
    
    switch (rnd_num)
    {   
    case 0:
	song_subj = "crushing the enemies of Calia in battle";
        break;
    case 1:
	song_subj = "the value of trust in a sometimes treacherous world";
        break;
    case 2:
	song_subj = "the strength of unity in the face of danger";
        break;
    case 3:
	song_subj = "loyalty to ones comrades in arms";
        break;
    case 4:
	song_subj = "the thrill of swarming the minions of evil into oblivion";
        break;
    case 5:
	song_subj = "the dark days, grim times of slavery that preceded the " +
	    "coming of Caliana";
        break;
    case 6:
	song_subj = "the efficiency of the wolf pack in dispatching those who "
	          + "would oppose Calia";
        break;        
    }

    tp->catch_msg("You sing an old Calian folk song about " + 
        song_subj + ".\n");

    tell_room(environment(tp), QCTNAME(tp) + " sings an old Calian " +
        "folk song about " + song_subj + ".\n", ({ tp }) );
    return 1;
}

/*
 * Function name: calian_celeb
 * Description:   A Calian emote which enables a Calian to do 
                  one of a number of celebrations, chosen 
                  randomly
 * Arguments:     none
 * Returns:       integer indicating success or failure (1 or 0)
 */
int
calian_celeb()
{
    string celeb_me, celeb_them;
    object tp;
    int rnd_num;

    UNDER_WATER_BLOCK; 

    tp = TP;
    rnd_num = random(6, time());
    
    switch (rnd_num)
    {   
    case 0:
	celeb_me = "You jump up and down in elation!";
        celeb_them = QCTNAME(tp) + " jumps up and down in elation!"; 
        break;

    case 1:
	celeb_me = "You celebrate, punching the air with delight!";
        celeb_them = QCTNAME(tp) + " celebrates, punching the air " +
            "with delight!"; 
        break;

    case 2:
	celeb_me = "You do a hand-stand and flip into cart-wheels in pure joy!";
        celeb_them = QCTNAME(tp) + " does a hand-stand and flips into " +
	    "cart-wheels in pure joy!"; 
        break;

    case 3:
	celeb_me = "You cackle and do a fighter-style foot shuffle, " +
	    "looking extremely pleased!"; 
        celeb_them = QCTNAME(tp) + " cackles and does a fighter-style foot " +
	    "shuffle, looking extremely pleased!";
        break;

    case 4:
	celeb_me = "You pump your fist thrice and stand proudly and "
	  + "acknowledge the solidarity of the Calian wolf pack!";
        celeb_them = QCTNAME(tp) + " pumps " + tp->query_possessive()
          + " fist thrice and acknowledges the solidarity of the Calian "
          + "wolf pack.";
        break;

    case 5:
	celeb_me = "You leap high into the air in celebration before landing " +
	    "several seconds later and beaming at everyone!";
        celeb_them = QCTNAME(tp) + " leaps high into the air in celebration " +
	    "before landing several seconds later and beaming at everyone!";
        break;
    }

    tp->catch_msg(celeb_me + "\n");

    tell_room(environment(tp), celeb_them + "\n", ({ tp }) );
    return 1;
}



/*
 * Function name: calian_praise
 * Description:   A Calian emote which enables a Calian to praise
                  another character for a certain property they 
                  have e.g. "fine warrior"
 * Arguments:     pred : the string following "cpraise"
 * Returns:       integer indicating success or failure (1 or 0)
 */
int
calian_praise(string pred)
{
    object friend, tp;
    string property, friend_name;

    tp = TP;

    if (!pred)
    {
        NF("You praise whom?  And for what property?\n");
        return 0;
    }

    if (sscanf(pred, "%s %s", friend_name, property) != 2)
    {
        NF("You praise whom?  And for what property?\n");
        return 0;
    }

    if (strlen(property) > 20) { 
        NF("Be more concise.\n");
        return 0;
    }

    friend = present(friend_name, environment(tp));
    if (!friend)
    {
        NF("You praise whom?\n");
        return 0;
    }

    if (friend == tp)
    {
        NF("You praise yourself?!\n");
        return 0;
    }

    tp->catch_msg("You praise " + QTNAME(friend) + " for being " +
        "such " + LANG_ADDART(property) + ".\n");

    friend->catch_msg(QCTNAME(tp) + " praises you for being such " +
        LANG_ADDART(property) + ".\n");

    tell_room(environment(tp), QCTNAME(tp) + " praises " + QTNAME(friend) +
	" for being such " + LANG_ADDART(property) + ".\n", 
                                            ({ tp, friend }) );
 
    return 1;
}



/*
 * Function name: calian_curse
 * Description:   A Calian emote which enables a Calian to curse
                  another character for a certain property they 
                  have e.g. "fool"
 * Arguments:     pred : the string following "ccurse"
 * Returns:       integer indicating success or failure (1 or 0)
 */
int
calian_curse(string pred)
{
    object person, tp;
    string person_name, property;

    tp = TP;

    if (!pred)
    {
        NF("You curse whom?  And for what property?\n");
        return 0;
    }

    if (sscanf(pred, "%s %s", person_name, property) != 2)
    {
        NF("You curse whom?  And for what property?\n");
        return 0;
    }

    if (strlen(property) > 20) { 
        NF("Be more concise.\n");
        return 0;
    }

    person = present(person_name, environment(tp));
    if (!person)
    {
        NF("You curse whom?\n");
        return 0;
    }

    if (person == tp)
    {
        NF("You curse yourself?!\n");
        return 0;
    }
    
    tp->catch_msg("You curse " + QTNAME(person) + " for being " +
        "such " + LANG_ADDART(property) + ".\n");
    person->catch_msg(QCTNAME(tp) + " curses you for being such " +
        LANG_ADDART(property) + ".\n");
    tell_room(environment(tp), QCTNAME(tp) + " curses " +
        QTNAME(person) + " for being such " + LANG_ADDART(property) + ".\n", 
        ({ tp, person }) );
 
    return 1;
}


/*
 * Function name: calian_look
 * Description:   A Calian emote which enables a Calian to give a meaningful
                  look to another Calian, which other Calians in the room 
                  will understand, but non-Calians will not.
 * Arguments:     pred : the string following "clook"
 * Returns:       integer indicating success or failure (1 or 0)
 */
int
calian_look(string pred)
{
    object friend, ob, tp, this, *everyone;
    string look_msg, friend_name, view_name;
    int i, success;

    tp = TP;
    this = THIS;

    if (!pred)
    {
        NF("You give a meaningful look to whom?  And about what?\n");
        return 0;
    }

    if (sscanf(pred, "%s %s", friend_name, look_msg) != 2)
    {
        NF("You give a meaningful look to whom?  And about what?\n");
        return 0;
    }

    if (strlen(look_msg) > 100) { 
        NF("Hey, you can't be _that_ meaningful in a look!\n");
        return 0;
    }

    friend = present(friend_name, environment(tp));
    if (!friend)
    {
        NF("You give a meaningful look to whom?\n");
        return 0;
    }

    if (friend == tp)
    {
        NF("You give a meaningful look to yourself?!\n");
        return 0;
    }

    success = is_calian(friend);
    if (success)
    {
        tp->catch_msg("You give " + QTNAME(friend) + " a meaningful look " +
            "which " + friend->query_pronoun() + " fully understands.\n");
        friend->catch_msg(QCTNAME(tp) + " gives you a meaningful look " + 
            "which you understand to mean: " + look_msg + "\n");
    }
    else
    {
        tp->catch_msg("You give " + QTNAME(friend) + " a meaningful look " +
            "but " + friend->query_pronoun() + " does not understand " +
            "it at all!\n");

        friend->catch_msg(QCTNAME(tp) + " gives you a meaningful look " +
            "but you are at a loss to work out just what it means!\n");
    }

    everyone = FILTER_LIVE(all_inventory(environment(tp))) - ({ tp, friend });
    for (i = 0; i < sizeof(everyone); i++)
    {
        ob = everyone[i];
        if (is_calian(ob))
            ob->catch_msg(QCTNAME(tp) + " gives " + QTNAME(friend) +
                " a meaningful look which you understand to mean: " + look_msg +		"\n");
       
        if (!is_calian(ob))
            ob->catch_msg(QCTNAME(tp) + " gives " + QTNAME(friend) +
                " a meaningful look.\n");
    }

    return 1;
}


/*
 * Function name: calian_warn
 * Description:   A Calian emote to give a warning to potential adversaries
 * Arguments:     none
 * Returns:       integer denoting success or failure (1 or 0)
 */
int calian_warn(string str)
{
    object weapon, tp, *who;
    string weapon_name, handle_name;
    int weapon_type;

    tp = TP;

         
    weapon = query_main_weapon(tp, "none");

    if (weapon) {
        weapon_name = weapon->short();

        weapon_type = weapon->query_wt();    
        if (weapon_type == W_SWORD)
            handle_name = "hilt";
        else if (weapon_type == W_KNIFE)
            handle_name = "handle";
        else
            handle_name = "haft";

        if (!str) {
            write("Your eyes narrow, as you grip the " + handle_name +
                  " of your " + weapon_name + " in warning.\n");
            all("'s eyes narrow, as " + tp->query_pronoun() + 
                " grips the " + handle_name + " of " +
                tp->query_possessive() + " " + weapon_name + 
                " in warning.");
            return 1;
        }
        else {
            who = parse_this(str, "%l");
            if (!sizeof(who)) {
                notify_fail("Warn whom?\n");
                return 0;
            }
            targetbb("'s eyes narrow, as " + tp->query_pronoun() + 
                     " grips the " + handle_name + " of " +
                     tp->query_possessive() + " " + weapon_name + 
                     " in warning to you.", who); 
            actor("Your eyes narrow, as you grip the " + handle_name +
                  " of your " + weapon_name + " in warning to",
                  who);
            all2actbb(" frowns and grips the " + handle_name + " of " +
                     tp->query_possessive() + " " + weapon_name +
                     " in warning to", who);
            return 1;
        }
    }
    else {
        if (!str) {
            write("Your eyes narrow, as you clench your fists " +
                  "in warning.\n");
            all("'s eyes narrow, as " + tp->query_pronoun() + 
                " clenches " + tp->query_possessive() + " fists " +
                "in warning.");
            return 1;
        }
        else {
            who = parse_this(str, "%l");
            if (!sizeof(who)) {
                notify_fail("Warn whom?\n");
                return 0;
            }
            targetbb("'s eyes narrow, as " + tp->query_pronoun() + 
                     " clenches " + tp->query_possessive() + 
                     " fists in warning to you.", who); 
            actor("Your eyes narrow, as you clench your fists in " +
                  "warning to", who);
            all2actbb(" frowns and clenches " + tp->query_possessive() +
                     " fists in warning to", who);
            return 1;
        }
    }    
}


/*
 * Function name: calian_warcry
 * Description:   A Calian emote to give a warcry that also carries to 
                  neighbouring rooms like a shout
 * Arguments:     pred, the war cry being made
 * Returns:       integer denoting success or failure (1 or 0)
 */
int
calian_warcry(string pred)
{
    object weapon, tp;
    string weapon_name, *near_rooms, shout1, shout2, shout3;
    int x;

    tp = TP;

    UNDER_WATER_BLOCK; 

    if (!pred)
    {
        NF("You shout what war cry?\n");
        return 0;
    }

    if (strlen(pred) > 60) {
        NF("That was too long a war cry! Please think of a shorter one.\n");
        return 0;
    }

    weapon = query_main_weapon(tp, "none");
    if (weapon)
    {
        weapon_name = weapon->short();

        tell_room(environment(tp), QCTNAME(tp) + " swings " +
            tp->query_possessive() + " " + weapon_name + " aloft and shouts " +
	    tp->query_possessive() + " mighty war cry: " + pred + "\n", tp); 

        tp->catch_msg("You swing your " + weapon_name + " aloft and shout " + 
            "your mighty war cry: " + pred + "\n");
    }
    else
    {
        tell_room(environment(tp), QCTNAME(tp) + " shouts " + 
            tp->query_possessive() + " mighty war cry: " + pred + "\n", tp);

        tp->catch_msg("You shout your mighty war cry: " + pred + "\n");
    }

    near_rooms = environment(tp)->query_exit_rooms();

    shout1 = "You hear " + tp->query_name() + " shouting " +
	tp->query_possessive() + " mighty war cry: " + pred + "\n";
    shout2 = "You hear a " + tp->query_gender_string() + " " +
	tp->query_race_name() +  " shouting a mighty war cry: " + pred + "\n";
    shout3 = "You hear someone shouting a mighty war cry: " + pred + "\n";
                  
    for (x = 0; x < sizeof(near_rooms); x++)
        tell_room(near_rooms[x], ({ shout1, shout2, shout3 }), tp);

    return 1;
}


int
calian_aggression()
{
     object tp, att; 
     string he, his;

     tp = this_player();
     att = tp->query_attack(); 

     if (!objectp(att)) {
         NF("You are not fighting anyone.\n");
         return 0;
     }

     he = tp->query_pronoun();
     his = tp->query_possessive();
     tp->catch_msg("Your body animates as you focus your aggression " +
                   "on " + QTNAME(att) + ".\n");  
     att->catch_msg(QCTNAME(tp) + "'s body animates as " + he + 
                    " focuses " + his + " aggression on you.\n"); 
     tell_room(environment(tp), QCTNAME(tp) + "'s body animates as " + he + 
                    " focuses " + his + " aggression on " + 
                    QTNAME(att) + ".\n", ({tp, att}) ); 
     return 1;
}


int
calian_honk(string str)
{
    object *oblist;
    string *how;
    object tp = this_player();

    how = parse_adverb_with_space(str, "musically", 0);

    if (!strlen(how[0]))
    {
        NF("Honk [how] who's nose?\n");
        return 0;
    }

    oblist = parse_this(how[0], "%l");

    if (!sizeof(oblist))
    {
        if ((tp->id(how[0])) || (how[0] == "me")) {
            tp->catch_msg("You honk your own nose" + how[1] + ".\n");  
            tell_room(environment(tp), QCTNAME(tp) + " honks " +  
                  tp->query_possessive() + " own nose" + how[1] + ".\n", 
                  tp); 
            return 1;
        } 
        else {
            NF("Honk [how] who's nose?\n");
            return 0;
        }
    }

    if (sizeof(oblist) > 1) {
        NF("What, multi-talented are we?\n");
        return 0;
    }

    if (oblist[0] == tp) { 
        tp->catch_msg("You honk your own nose" + how[1] + ".\n");  
        tell_room(environment(tp), QCTNAME(tp) + " honks " +  
                  tp->query_possessive() + " own nose" + how[1] + ".\n", 
                  tp); 
        return 1;
    }

    target(" honks your nose" + how[1] + ".", oblist);
    actor("You honk", oblist, "'s nose" + how[1] + ".");
    all2act(" honks", oblist, "'s nose" + how[1] + ".");
    return 1;
}


int 
calian_pace()
{
    IN_WATER_BLOCK; 
    UNDER_WATER_BLOCK; 

    write("You pace around restlessly.\n");
    all(" paces around restlessly.");
    return 1;
}


int 
calian_gaze(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "thoughtfully", 0);

    if (!strlen(how[0]))
    {
        write("You look" + how[1] + " at the surroundings.\n");
        allbb(" looks" + how[1] + " at the surroundings.");
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Look [how] at whom?\n");
        return 0;
    }

    targetbb(" looks" + how[1] + " at you.", oblist);
    actor("You look" + how[1] + " at", oblist);
    all2actbb(" looks" + how[1] + " at", oblist);
    return 1;
}

