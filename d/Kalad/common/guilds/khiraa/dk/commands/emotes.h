/*
 * /d/Kalad/common/guilds/khiraa/dk/commands/emotes.h
 * Purpose    : Emotes for the Death Knights of the Khiraa
 * Located    : 
 * Created By : Sarr 6.Mar.97
 * Modified By: 
 */

int
e_kobey(string str)
{
    string tits;
    object *obs,tar;
    if(!str)
    {
        write("You bow deeply and intone in a hollow voice: It shall "+     
        "be done.\n");
        allbb(" bows deeply and intones in a hollow voice: It shall "+
        "be done.");
        return 1;
    }
    obs = parse_this(str,"[the] %l");
    NF("Obey who?\n");
    if(!sizeof(obs))
        return 0;
    tar = obs[0];
    NF("Obey only one at a time.\n");
    if(sizeof(obs) > 1)
        return 0;
    tits = "Buggy One.";
    if(!IS_DK(tar) && !IS_LP(tar))
    {
        actor("You nod at",obs," and intone: Aye.");
        all2act(" nods at",obs," and intones: Aye.");
        targetbb(" nods at you and intones: Aye.",obs);
        return 1;
    }
    if(IS_DK(tar))
    {
    if(TP->query_base_stat(SS_OCCUP) > tar->query_base_stat(SS_OCCUP))
            tits = ".";
        else
            tits = ", Superior Knight.";
        if(tar->query_circle() == 3)
            tits = ", my Lord.";
    }
    if(IS_LP(tar))
    {
        tits = ", Holy One.";
        if(tar->query_circle() == 2)
            tits = ", Master of the Khiraa.";
        if(tar->query_circle() == 1)
            tits = ", Master.";
    }
    actor("You bow deeply to",obs," and intone: It shall be done"+tits);
    all2act(" bows deeply to",obs," and intones: It shall be done"+tits);
    targetbb(" bows deeply to you and intones: It shall be done"+tits,obs);
    return 1;
}

int
e_ksniff()
{
    write("You sniff the air for blood.\n");
    allbb(" sniffs the air for blood.");
    return 1;
}

int
e_karc(string str)
{
    object sword;
    object *obs;
    NF("You need to be wielding a two-handed sword to do this.\n");
    sword = TP->query_weapon(W_BOTH);
    if(!objectp(sword))
        return 0;
    obs = parse_this(str,"[the] %l");
    NF("Arc at whom?\n");
    if(!sizeof(obs) && str)
        return 0;
    if(sizeof(obs))
    {
        actor("You grip your "+sword->short()+" with both hands "+
        "tightly and swing a massive arch in front of",obs,".");
        all2act(" grips "+HIS(TP)+" "+sword->short()+" with both "+
        "hands tightly and swings a massive arch in from of",obs,".");
        targetbb(" grips "+HIS(TP)+" "+sword->short()+" with both "+
        "hands tightly and swings a massive arch in front of you, "+
        "nearly hitting you!",obs);
        return 1;
    }
    write("You grip your "+sword->short()+" with both hands tightly "+
    "and swing a massive arch through the air.\n");
    all(" grips "+HIS(TP)+" "+sword->short()+" with "+
    "both hands tightly and swings a massive arch through the air.");
    return 1;
}



int
e_kspin()
{
    object first_s,second_s;
    first_s = TP->query_weapon(W_RIGHT);
    second_s = TP->query_weapon(W_LEFT);
    NF("You need two swords wielded to do this.\n");
    if(!first_s || !second_s)
        return 0;
    write("You spin and twirl your "+first_s->short()+" and "+
    second_s->short()+" around a bit then toss them in the air and "+
    "watch them land in the ground at your sides. You pull them out "+
    "of the ground.\n");
    allbb(" spins and twirls "+HIS(TP)+" "+first_s->short()+
    " and "+second_s->short()+" around a bit then tosses them in the "+
    "air and watches them land in the ground at "+HIS(TP)+" sides. "+
    C(HE(TP))+" then pulls them out of the ground.");
    return 1;
}

int
e_kscrape()
{
    object first_s,second_s;
    first_s = TP->query_weapon(W_RIGHT);
    second_s = TP->query_weapon(W_LEFT);
    NF("You need two swords wielded to do this.\n");
    if(!first_s || !second_s)
        return 0;
    write("You slowly scrape the blades of your "+first_s->short()+" and "+
    second_s->short()+" together with a cruel look on your face.\n");
    allbb(" slowly scrapes the blades of "+HIS(TP)+" "+first_s->short()+
    " and "+second_s->short()+" together with a cruel look on "+HIS(TP)+
    " face.");
    return 1;
}

int
e_kjuggle()
{
    object first_s,second_s;
    first_s = TP->query_weapon(W_RIGHT);
    second_s = TP->query_weapon(W_LEFT);
    NF("You need two swords wielded to do this.\n");
    if(!first_s || !second_s)
        return 0;
    write("You juggle the "+first_s->short()+" and "+second_s->short()+
    " together with deadly precision.\n");
    allbb(" juggles the "+first_s->short()+" and "+
    second_s->short()+" together with deadly precision.");
    return 1;
}


int
e_kpoint(string str)
{
    mixed *items;
    int index,i;
    object *obs;
    string arm,*dirs;
    dirs = ({"east","west","south","north","up","down","northeast","northwest",
    "southwest","southeast"});
    NF("Point at what?\n");
    if(TP->query_armour(A_R_HAND))
        arm = "an armoured";
    else
        arm = "a skeletal";
    obs = parse_this(str,"[toward] / [at] [the] %l");
    if(sizeof(obs))
    {
        actor("You raise "+arm+" hand up and slowly point at",obs,".");
        all2act(" raises "+arm+" hand up and slowly points at",obs,".");
        targetbb(" raises "+arm+" hand up and slowly points at you.",obs);
        return 1;
    }
    parse_command("kpoint "+str,E(TP),"'kpoint' [at] [the] %i",obs);
    if(sizeof(obs))
    {
        write("You raise "+arm+" hand up and slowly point at the "+
        obs[1]->short()+".\n");
        allbb(" raises "+arm+" hand up and slowly points at "+
        "the "+obs[1]->short()+".");
        return 1;
     }
    items = E(TP)->query_item();
    for(i=0;i<sizeof(items);i++)
    {
        if((index = member_array(str,items[i][0])) != -1)
        {
            write("You raise "+arm+" hand up and slowly point at "+
            "the "+items[i][0][index]+".\n");
            allbb(" raises "+arm+" hand up and slowly "+
            "points at the "+items[i][0][index]+".");
            return 1;
        }
    }
    if((index = member_array(str,dirs)) != -1)
    {
        write("You raise "+arm+" hand up and slowly point "+dirs[index]+
        ".\n");
        allbb(" raises "+arm+" hand up and slowly points "+
        dirs[index]+".");
        return 1;
    }
    return 0;
}


int
e_kdeath(string str)
{
    object wep,*targets,target;
    string hand_desc;
    if(sizeof(TP->query_weapon(-1)))
        wep = TP->query_weapon(-1)[0];
    if(wep)
        hand_desc = wep->short();
    else
    {
        if(TP->query_armour(A_R_HAND))
            hand_desc = "armoured hand";
        else
            hand_desc = "skeletal hand";
    }
    targets = parse_this(str,"[toward] / [at] [the] %l");
    NF("Death whom?\n");
    if(!sizeof(targets))
        return 0;
    target = targets[0];
    TP->catch_msg("You point your "+hand_desc+" at "+QTNAME(target)+" and "+
    "give "+HIM(target)+" a look of death implying that "+HE(target)+
    " will be next to fall by your hand.\n");
    target->catch_msg(QCTNAME(TP)+" points "+HIS(TP)+" "+hand_desc+" at "+
    "you and gives you a look of death implying that you will be "+
    "next to fall by "+HIS(TP)+" hand.\n");
    tell_room(E(TP),QCTNAME(TP)+" points "+HIS(TP)+" "+hand_desc+" at "+
    QTNAME(target)+" and gives "+HIM(target)+" a look of death implying "+
    "that "+HE(target)+" will be next to fall by "+HIS(TP)+" hand.\n",
    ({TP,target}));
    return 1;
}


int
e_ksay(string str)
{
    string str2,str3,str4;
    object robe,tar,*tars;
    robe = TP->query_armour(A_HEAD);
    NF("Say what?\n");
    if(!str) 
        return 0;
    if(sscanf(str,"%s %s %s",str2,str3,str4) == 3)
    {
        if(str2 == "to")
        {
            NF("Say what to who?\n");
            tars = parse_this(str3,"[the] %l");
            if(!sizeof(tars))
                return 0;
            tar = tars[0];
            if(!objectp(tar))
                return 0;
            if(robe)
            {
                TP->catch_msg("You turn to "+QTNAME(tar)+" and echo "+
                "from within your "+robe->short()+": "+str4+"\n");
                tar->catch_msg(QCTNAME(TP)+" turns to you and echos "+
                "from within "+HIS(TP)+" "+robe->short()+": "+str4+"\n");
                tell_room(E(TP),QCTNAME(TP)+" turns to "+QTNAME(tar)+
                " and echos from within "+HIS(TP)+" "+robe->short()+
                ": "+str4+"\n",({TP,tar}));
                return 1;
            }
            else
            {
                TP->catch_msg("You hiss in a death-like voice to "+
                QTNAME(tar)+": "+str4+"\n");
                tar->catch_msg(QCTNAME(TP)+" hisses in a death-like "+
                "voice to you: "+str4+"\n");
                tell_room(E(TP),QCTNAME(TP)+" hisses in a death-like "+
                "voice to "+QTNAME(tar)+": "+str4+"\n",({tar,TP}));
                return 1;
            }
        }
    }

    if(robe)
    {
        write("You echo from within your "+robe->short()+": "+str+"\n");
        say(QCTNAME(TP)+" echos from within "+HIS(TP)+" "+robe->short()+
        ": "+str+"\n");
    }
    else
    {
        write("You hiss in a death-like voice: "+str+"\n");
        say(QCTNAME(TP)+" hisses in a death-like voice: "+str+"\n");
    }
    return 1;
}

int
e_klaugh(string str)
{
    object *obs;
    object helm = TP->query_armour(A_HEAD);
    obs = parse_this(str, "[at] / [to] / [toward] [the] %l");
    NF("Laugh at whom?\n");
    if(str && !sizeof(obs))
        return 0;
    if(sizeof(obs))
    {
        if(helm)
        {
            actor("You rumble a laugh from within your "+helm->short()+
            " at",obs,".");
            all2actbb(" emits a low rumbling sound from within "+HIS(TP)+
            " "+helm->short()+"; you realize "+HE(TP)+" is laughting "+
            "at",obs,".");
            targetbb(" emits a low rumbling sound from within "+HIS(TP)+
            " "+helm->short()+"; you realize "+HE(TP)+" is laughing at "+
            "you.",obs);
        }
        else
        {
            actor("You rumble a sinister laugh at",obs,"."); 
            all2actbb(" rumbles a sinister laugh at",obs,".");
            targetbb(" rumbles a sinister laugh at you.",obs);
        }
        return 1;
    }
    if(helm)
    {
        write("You rumble a laugh from within your "+helm->short()+".\n");
        say("A low rumbling sound comes from "+QTNAME(TP)+"'s "+
        helm->short()+"; you realize "+HE(TP)+" is laughing.\n");
    }
    else
    {
        write("You rumble a sinister laugh.\n");
        all(" rumbles a sinister laugh.");
    }
    return 1;
}

