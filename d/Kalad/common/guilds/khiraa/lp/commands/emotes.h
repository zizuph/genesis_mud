/*
 * /d/Kalad/common/guilds/khiraa/lp/commands/emotes.h
 * Purpose    : Emotes for the Lichs of the Khiraa
 * Located    : 
 * Created By : Sarr 6.Apr.97
 * Modified By: 
 */

int
e_lpity(string str)
{
    object *obs;
    NF("Pity who?\n");
    if(!str)
        return 0;
    obs = parse_this(str,"[the] %l");
    if(!sizeof(obs))
        return 0;
    actor("You pity",obs," and "+HIS(obs[0])+" enslavement to the life"+
    "-spark which corrodes "+HIS(obs[0])+" soul and prevents "+HIM(obs[0])+
    " from attaining a higher existence.");
    all2act(" pities",obs," and "+HIS(obs[0])+" enslavement to the life"+
    "-spark which corrodes "+HIS(obs[0])+" soul and prevents "+
    HIM(obs[0])+" from attaining a higher existence.");
    targetbb(" pities you and your enslavement to the life-spark which "+
    "corrodes your soul and prevents you from attaining a higher "+
    "existence.",obs);
    return 1;
}

int
e_ljuggle()
{
    write("You conjur up three glowing purple spheres and juggle them.\n");
    allbb(" conjurs up three glowing purple spheres and juggles them.");
    return 1;
}

int
e_lwiggle()
{
    write("You wiggle your fingers, and they burst into an eerie purple "+
    "flame.\n");
    allbb(" wiggles "+HIS(TP)+" fingers, and they burst into an eerie "+
    "purple flame.");
    return 1;
}

void
rskull(object ob)
{
    tell_room(E(ob),"The skull in the air slowly fades away.\n");
}

int
e_lsign()
{
    write("You draw a black grim skull in the air with your finger.\n");
    allbb(" draws a black grim skull in the air with "+HIS(TP)+" finger.");
    set_alarm(3.0,0.0,&rskull(TP));
    return 1;
}

int
e_lsay(string str)
{
    string str2,str3,str4;
    object robe,tar,*tars;
    robe = TP->query_armour(A_ROBE);
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
                TP->catch_msg("You turn to "+QTNAME(tar)+" and hiss "+
                "from within your "+robe->short()+": "+str4+"\n");
                tar->catch_msg(QCTNAME(TP)+" turns to you and hisses "+
                "from within "+HIS(TP)+" "+robe->short()+": "+str4+"\n");
                tell_room(E(TP),QCTNAME(TP)+" turns to "+QTNAME(tar)+
                " and hisses from within "+HIS(TP)+" "+robe->short()+
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
        write("You hiss from within your "+robe->short()+": "+str+"\n");
        say(QCTNAME(TP)+" hisses from within "+HIS(TP)+" "+robe->short()+
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
e_llaugh(string str)
{
    object *obs;
    object helm = TP->query_armour(A_ROBE);
    obs = parse_this(str, "[at] / [to] / [toward] [the] %l");
    NF("Laugh at whom?\n");
    if(str && !sizeof(obs))
        return 0;
    if(sizeof(obs))
    {
        if(helm)
        {
            actor("You hiss a laugh from within your "+helm->short()+
            " at",obs,".");
            all2actbb(" emits a soft hissing sound from within "+HIS(TP)+
            " "+helm->short()+"; you realize "+HE(TP)+" is laughting "+
            "at",obs,".");
            targetbb(" emits a soft hissing sound from within "+HIS(TP)+
            " "+helm->short()+"; you realize "+HE(TP)+" is laughing at "+
            "you.",obs);
        }
        else
        {
            actor("You hiss a sinister laugh at",obs,"."); 
            all2actbb(" hisses a sinister laugh at",obs,".");
            targetbb(" hisses a sinister laugh at you.",obs);
        }
        return 1;
    }
    if(helm)
    {
        write("You hiss a laugh from within your "+helm->short()+".\n");
        say("A soft hissing sound comes from "+QTNAME(TP)+"'s "+
        helm->short()+"; you realize "+HE(TP)+" is laughing.\n");
    }
    else
    {
        write("You hiss a sinister laugh.\n");
        all(" hisses a sinister laugh.");
    }
    return 1;
}

