inherit "/d/Kalad/std/armour";
inherit "/cmd/std/command_driver";
#include "/d/Kalad/defs.h"

/* club tie, sarr */

query_recover()
{
    return 0;
}

void
create_armour()
{
    ::create_armour();
    set_name("bowtie");
    set_adj("black");
    add_adj("silk");
    set_ac(0);
    set_at(A_NECK);
    add_prop(OBJ_I_WEIGHT,8);
    add_prop(OBJ_I_VOLUME,10);
    set_long("Its a cool tie. The words 'gchelp' are sewn in the back.\n");
}

init()
{
    ::init();
    AA(gc_help,gchelp);
    AA(gc_flex,flex1);
    AA(gc_flex2,flex2);
    AA(gc_kiss1,kiss1);
    AA(gc_kiss2,kiss2);
    AA(gc_wrap,wrap);
    AA(gc_pat,patbutt);
    AA(gc_flirt1,flirt1);
    AA(gc_flirt2,flirt2);
    AA(gc_dance1,dance1);   
}

int
gc_help()
{
    write("List of emotes for the Gentlemen's Club:\n");
    write("flex1            ---  Flex your muscles.\n"); 
    write("flex2            ---  Flex your pecs.\n");
    write("kiss1 <person>   ---  Do a sexy kiss.\n");
    write("kiss2 <person>   ---  Do a gentle kiss.\n");
    write("wrap <person>    ---  Be a gentlemen and keep someone warm.\n");
    write("patbutt <person> ---  Pat your bottom for someone to kiss.\n");
    write("flirt1 <person>  ---  Pat the butt of someone.\n");
    write("flirt2 <person>  ---  Sexy look at someone.\n");
    write("dance1 [slow/fast] ---  Sway your hips.\n");
    return 1;
}

int
gc_dance1(string str)
{
    string sp;
    switch(str)
    {
        case "slow":
        sp = " slowly";
        break;
        case "fast":
        sp = " quickly";
        break;
        default:
        sp = "";
    }
    write("You sway your hips from side to side"+sp+", smiling "+
    "enticingly.\n");
    say(QCTNAME(TP)+" sways his hips from side to side"+sp+", "+
    "smiling enticingly.\n");
    return 1;
}


int
gc_flex(string str)
{
    string player = TP->query_name();
    int i;
    object *obj;
    obj = FILTER_LIVE(all_inventory(E(TP)));
    write("You flex your bulging muscles with pride.\n");
    say(QCTNAME(TP)+ " flexes his bulging muscles with pride.\n");
    for (i=0;i<sizeof(obj);i++)
    {
        if(obj[i]->query_gender() == 1)
        {
            obj[i]->catch_msg("You sigh dreamily at "+QCTNAME(TP)+".\n");
            TP->catch_msg(QCTNAME(obj[i])+ " sighs dreamily at you.\n");
            tell_room(E(TP),QCTNAME(obj[i])+" sighs dreamily at "+
            QCTNAME(TP)+".\n",({obj[i],TP}));
	        }
    }
    return 1;
}

int
gc_flex2()
{
    write("You flex your pectoral muscles, making them "+
    "ripple like waves.\n");
    say(QCTNAME(TP)+ " flexes his pectoral muscles, making them "+
    "ripple like waves.\n");
    return 1;
}

int    
gc_kiss1(string name)
{
    string pos;
    object *oblist;
    oblist = parse_this(name,"[the] %l");
    if(sizeof(oblist) == 0)
        { NF("Kiss whom?\n"); return 0; }
    if(sizeof(oblist) == 1)
        pos = oblist[0]->query_objective();
    else
        pos = "them";
    target(" bends you over his knee, leans down and gives you a deep, "+
    "hot kiss.",oblist);
    actor("You bend",oblist," over your knee, lean down and give "+
    pos+" a deep, hot kiss.");
    all2act(" bends", oblist," over his knee, leans down and gives "+
    pos+" a deep, hot kiss.");
    return 1;
}

int    
gc_flirt1(string name)
{
    string pos;
    object *oblist;
    oblist = parse_this(name,"[the] %l");
    if(sizeof(oblist) == 0)
        { NF("Flirt with whom?\n"); return 0; }
    if(sizeof(oblist) == 1)
        pos = oblist[0]->query_objective();
    else
        pos = "them";
    target(" pats your round butt.",oblist);
    actor("You pat the round butt of",oblist,".");
    all2act(" pats the round butt of",oblist,".");
    return 1;
}

int    
gc_flirt2(string name)
{
    string pos;
    object *oblist;
    oblist = parse_this(name,"[the] %l");
    if(sizeof(oblist) == 0)
        { NF("Flirt with whom?\n"); return 0; }
    if(sizeof(oblist) == 1)
        pos = oblist[0]->query_objective();
    else
        pos = "them";
    target(" brushes his hair from his face and looks at "+
    "you with a sexy smile.",oblist);
    actor("You brush your hair from your face and look at",oblist,
    " with a sexy smile.");
    all2act(" brushes his hair from his face and looks at",oblist,
    " with a sexy smile.");
    return 1;
}

int    
gc_kiss2(string name)
{
    string pos;
    string os;
    object *oblist;
    oblist = parse_this(name,"[the] %l");
    if(sizeof(oblist) == 0)
        { NF("Kiss whom?\n"); return 0; }
    if(sizeof(oblist) == 1)
        os = oblist[0]->query_possessive()+ "s"; 
    else
        os = "theirs";
    target(" wraps his strong arms around your waist and gently touches"+
    " his lips to yours.",oblist);
    actor("You wrap your strong arms around",oblist," and gently touch"+
    " your lips to "+os+".");
    all2act(" wraps his strong arms around",oblist," and gently touches"+
    " his lips to "+os+".");
    return 1;
}

int 
gc_wrap(string name)
{
    string pos;
    object *oblist;
    oblist = parse_this(name,"[the] %l");
    if(sizeof(oblist) == 0)
        { NF("Wrap your coat around whom?\n"); return 0; }
    if(sizeof(oblist) >1)
        { NF("One at a time please!\n"); return 0;}
    if(sizeof(oblist) == 1)
        pos = oblist[0]->query_objective();
    actor("You take off your cloak and wrap it around",oblist," to keep "+
    pos+" warm.");
    target(" takes off his cloak and wraps it around you to keep you warm.",
    oblist);
    all2act(" takes off his cloak and wraps it around",oblist," to keep "+
    pos+" warm.");
    return 1;
}

int 
gc_pat(string name)
{
    string pos;
    object *oblist;
    oblist = parse_this(name,"[at] [the] %l");
    if(sizeof(oblist) == 0)
        { NF("Pattbutt at whom?\n"); return 0; }
    actor("You pat your butt smugly, implying that",oblist," should kiss it.");
    target(" pats his butt smugly, implying that you should kiss it.",oblist);
    all2act(" pats his butt smugly, implying that",oblist," should "+
    "kiss it.");
    return 1;
}


