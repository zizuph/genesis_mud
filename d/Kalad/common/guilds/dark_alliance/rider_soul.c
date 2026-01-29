#pragma strict_types

inherit "/cmd/std/command_driver";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/dark_alliance/default.h"
#include <tasks.h>

#define WOLF_O_OCCUPIED "_wolf_o_occupied"
#define WOLF_O_RIDING "_wolf_o_riding"
#define WOLF_SUBLOC "_fang_wolf_subloc"
#define SLASH_RESET_TIME    16.0
#define SLASH_RESET   "_slash_reset"
object corpse;              
public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Rider"; }

public mapping
query_cmdlist()
{
    return ([
#include "rcommands.h"
            ]);
}

public int
e_ryawn()
{
    allbb(" yawns tiredly, wishing a battle would start up.");
    write("You yawn tiredly, wishing a battle would start up.\n");
    return 1;
}

public int
e_rwipe()
{
    object *wep;
    string swep;
    wep = TP->query_weapon(-1);
    if(!sizeof(wep))
        swep = "hands";
    else
        swep = wep[0]->short();
    NF("There is no corpse here.\n");
    if(!present("corpse",E(TP)))
        return 0;
    allbb(" wipes the blood off "+HIS(TP)+" "+swep+" with the "+
        "corpse of "+HIS(TP)+" last victim.");
    write("You wipe the blood off your "+swep+" with the corpse of "+
        "your last victim.\n");
    return 1;
}

public int
e_rwait()
{
    allbb(" draws the symbol of the Dark Alliance on the ground in "+
        "blood.");
    write("You draw the symbol of the Dark Alliance on the ground in "+
        "blood.\n");
    return 1;
}

public int
e_rblood()
{
    allbb(" wipes the blood off "+HIS(TP)+" armour with "+HIS(TP)+
        " hand.");
    write("You wipe the blood off your armour with your hand.\n");
    SOULDESC("dripping with blood");
    return 1;
}   

public int
e_rrest()
{
    allbb(" sits on the ground and rests "+HIS(TP)+" battle weary "+
        "body.");
    write("You sit on the ground and rest your battle weary body.\n");
    SOULDESC("resting on the ground, resting");
    return 1;
}   

public int
e_rtrack(string str)
{
    /*
    * Function name: track
    * Description:   look for tracks
    * Argument:      str - the string given to the command
    * Returns:       0 - failure
    */
    object  room = E(TP);
    
    if (this_player()->query_attack())
        {
        notify_fail("But you are in the middle of a fight!\n");
        return 0;
    }
    
    if (strlen(str) && str != "here")
        {
        notify_fail("Track where?\n");
        return 0;
    }
    
    if (!room->query_prop(ROOM_I_IS))
        {
        notify_fail("You cannot look for tracks here!\n");
        return 0;
    }
    
    if (room->query_prop(ROOM_I_INSIDE))
        {
        notify_fail("You cannot look for tracks inside a room!\n");
        return 0;
    }
    
    if (this_player()->query_mana() < 2*F_TRACK_MANA_COST)
        {
        notify_fail("You are mentally too exhausted to look for tracks.\n");
        return 0;
    }
    
    write("You get down on all fours and bury your nose in the ground, "+
        "expertly sniffing for your prey.\n");
    allbb(" gets down on all fours and buries "+HIS(TP)+" nose in "+
        "the ground, expertly sniffing for "+HIS(TP)+" prey.");
    this_player()->add_prop(LIVE_S_EXTRA_SHORT, ", kneeling on the ground");
    this_player()->add_mana(-F_TRACK_MANA_COST);
    room->track_room();
    return 1;
}


public int
e_rtwirl(string arg)
{
    int i;
    object obj;
    object *oblist; 
    NF("Twirl what sword?\n");
    if(!arg)
        return 0;
    oblist = all_inventory(TP);
    for(i=1;i<sizeof(oblist);i++)
    {
        if(oblist[i]->query_short() == arg)
            {
            obj = oblist[i];
            break;
        }
        if(oblist[i]->query_adj()+" "+oblist[i]->query_name() == arg)
            {
            obj = oblist[i];
            break;
        }
        if(oblist[i]->query_name() == arg)
            {
            obj = oblist[i];
            break;
        }
    }
    if(!obj)
        return 0;
    if(present(obj,TP))
        {
        NF("That is not a sword!\n");
        if(obj->query_wt() != 0)
            return 0;
        allbb(" twirls the "+obj->query_short()+" in "+HIS(TP)+
            "hand impressively, with a malevolent gleam in "+HIS(TP)+" eye.");
        write("You twirl the "+obj->query_short()+" impressively "+
            "with a malevolent gleam in your eye.\n");
        return 1;
    }
    NF("You don't have the "+obj->query_short()+".\n");
    return 0;
}

public int
e_rgrowl(string arg)
{
    object *oblist;
    
    NF("rgrowl at whom?\n");
    
    if (!strlen(arg))
        {
        allbb(" growls with obvious hatred.");
        write("You growl with obvious hatred.\n");
        SOULDESC("growling with obvious hatred");
        return 1;
    }
    
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if (!sizeof(oblist))
        return 0;
    
    SOULDESC("growling with menacing hatred");
    actor("You growl at", oblist, " with obvious hatred.");
    all2actbb(" growls at", oblist, " with obvious hatred.");
    targetbb(" growls at you with obvious hatred.", oblist);
    return 1;
}

public string
q_title(object ob, int wiz)
{
    if (!ob->query_guild_member(GUILD_NAME))
        return 0;
    if(ob->query_wiz_level())
        return implode(explode(break_string("@"+ob->query_presentation(), 76), "\n"),
        "\n    "); 
    if (extract(ob->query_name(), -2) == "jr")
        return 0;
    return implode(explode(break_string(ob->query_presentation(), 76), "\n"),
        "\n    ");
}

public int
e_rlist(string arg)
{
    int i;
    i = (query_verb() == "mwlist" ? 1 : 0);
    write("You know that the following members of the Dark Alliance "+
        "are currently within the world:\n"+
        implode(map(users() - ({ 0 }), "q_title", this_object(), i) - ({ 0 }),
            "\n") + "\n");
    return 1;
}

int kolla(object ob)
{
    if(!living(ob))
        return 0;
    
    return 1;
}

public int
e_risay(string arg)
{
    if (!strlen(arg))
        {
        NF("Say what in the Alliance tongue?\n");
        return 0;
    }
    
    if(TP->query_skill(SS_LANGUAGE) < 30)
        {
        NF("You are not skilled enough in foreign tongues to be able to "+
            "speak the Alliance tounge.\n");
        return 0;
    }
    
    if (this_player()->query_get_echo())
        write("In the Alliance Tounge, you say: " + arg + "\n");
    else
        write("Ok.\n");
    
    filter(all_inventory(environment(this_player())) - ({ this_player() }),
        "do_say", this_object(), arg);
    return 1;
}

public int
do_say(object who, string arg)
{
    if (!living(who))
        return 0;
    if ((IS_MEMBER(who) && who->query_skill(SS_LANGUAGE) > 29) ||
            who->query_skill(SS_LANGUAGE) > 69)
    tell_object(who, this_player()->query_The_name(who) + " sneers " +
        "in the Alliance tounge: " + arg + "\n");
    else
        tell_object(who, this_player()->query_The_name(who)  +" sneers " +
        "something while moveing thier hands.\n");
}

public int
e_rlaugh(string arg)
{
    object *oblist;
    
    NF("Rlaugh at who?\n");
    
    if (!strlen(arg))
        {
        all(" howls a vicious cruel laughter.");
        write("You howl a vicious, cruel laughter.\n");
        SOULDESC("howling a vicious cruel laughter");
        return 1;
    }
    
    oblist = parse_this(arg, "[at] / [to] [the] %l");
    if (!sizeof(oblist))
        return 0;
    
    actor("You howl a vicious, cruel laughter at", oblist);
    all2act(" howls a vicious, cruel laughter at", oblist);
    target(" howls a vicious, cruel laughter at you.", oblist);
    SOULDESC("howling a vicious, cruel laughter");
    return 1;
}

public int
e_rint(string arg)
{
    object *oblist;
    
    NF("Rint who?\n");
    if (!strlen(arg))
        return 0;
    
    oblist = parse_this(arg, "[the] %l");
    if (!sizeof(oblist))
        return 0;
    if (sizeof(oblist) >1)
        { NF("You can only do this to one person at a time.\n"); return 0; }
    actor("You grab", oblist, " with both hands by the collar and pull "+HIM(oblist[0])+" to your "+
        "face staring down into "+HIS(oblist[0])+" eyes, with inhuman rage.");
    all2actbb(" grabs", oblist, " with both hands by the collar and pulls "+HIM(oblist[0])+" to "+
        HIS(TP)+" face, staring down into their eyes with inhuman rage.");
    targetbb(" grabs you by the collar and pulls you to "+HIS(TP)+" face, stating down into your eyes "+
        "with inhuman rage.", oblist);
    return 1;
}

public int
e_rspit(string arg)
{
    object *oblist;
    NF("Rspit at whom?\n");
    if(!strlen(arg))
        {
        allbb(" spits on the ground in hatred of all Thanarims.");
        write("You spit on the ground in hatred of all Thanarims.\n");
        SOULDESC("spitting in hatred of all Thanarims");
        return 1;
    }
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if (!sizeof(oblist))
        return 0;
    SOULDESC("spitting in hatred of all Thanarim scum");
    actor("You spit on", oblist, " in hatred.");
    all2actbb(" spits on", oblist, " in hatred.");
    targetbb(" spits on you in hatred.", oblist);
    return 1;
}

public int
e_rsnarl(string arg)
{
    object *oblist;
    NF("Snarl at whom?\n");
    if(!strlen(arg))
        {
        allbb(" snarls with inhuman rage.");
        write("You snarl with inhuman rage.\n");
        SOULDESC("snarling with inhuman rage");
        return 1;
    }
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if(!sizeof(oblist))
        return 0;
    SOULDESC("snarling with inhuman rage");
    actor("You snarl at", oblist," with inhuman rage.");
    all2actbb(" snarls at", oblist,"with inhuman rage.");
    targetbb(" snarls at you with inhuman rage.\n"+
        "You take a slight step back.",oblist);
    return 1;
}

public int
e_rsalute(string arg)
{
    object *oblist;
    NF("Salute whom?\n");
    if(!strlen(arg))
        {
        allbb(" stands straight and salutes sharply.");
        write("You stand straight and salute sharply.\n");
        return 1;
    }
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if(!sizeof(oblist))
        return 0;
    actor("You stand straight and salute sharply at", oblist);
    all2actbb(" stands straight and salutes sharply at", oblist);
    targetbb(" stands straight and salutes sharply at you.", oblist);
    return 1;
}


public int
e_rnod(string arg)
{
    object *oblist;
    NF("Nod at whom?\n");
    if(!strlen(arg))
        return 0;
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if(!sizeof(oblist))
        return 0;
    actor("You give", oblist," a slight, acknowledging nod.");
    all2actbb(" gives", oblist," a slight, acknowledging nod.");
    targetbb(" gives you a slight acknowledging nod.", oblist);
    return 1;
}

public int
e_rcross()
{
    allbb(" folds "+TP->query_possessive()+" arms across "+
        TP->query_possessive()+" chest and stands straight in "+
        "direct defiance."); 
    write("You fold your arms across your chest and stand "+
        "straight in direct defiance.\n");
    SOULDESC("crossing "+TP->query_possessive()+" arms defiantly");
    return 1;
}

int
e_rblaze()
{
    write("Your eyes blaze with fury.\n");
    say(QCTNAME(TP)+"'s eyes blaze with fury.\n");
    return 1;
}

int
e_rhowl()
{
    write("You viciously howl in fury like a warwolf.\n");
    say(QCTNAME(TP)+" viciously howls in fury like a warwolf.\n");
    return 1;
}

int
e_rwar()
{
    string warcry;
    switch(random(6))
    {
        case 0:
        warcry = "The Dark Alliance shall never fall!\n";
        break;
        case 1:
        warcry = "Down with the Thanar!\n";
        break;
        case 2:
        warcry = "Long live the Alliance!\n";
        break;
        case 3:
        warcry = "Kalad! Kalad! Forever our home!\n";
        break; 
        case 4:
        warcry = "Death to the enemies of the Dark Alliance!\n";
        break;
        case 5:
        warcry = "Die scum!!\n";
        break;
    }
    
    write("You cry out: "+warcry);
    say(QCTNAME(TP)+" cries out: "+warcry);
    return 1;
}

int
e_rbark(string arg)
{
    NF("Bark what?\n");
    if(!arg)
        return 0;
    write("You bark out: "+arg+"\n");
    say(QCTNAME(TP)+" barks out: "+arg+"\n");
    return 1;
}

int
kill(string str)
{
    write("You roar viciously!.\n");
    say(QCTNAME(TP) + " roars viciously!.\n");
    return 0;
}

int
rslash(string str)
{
    object warwolf, enemy,*enemys;
    int skill,my_dis,pen;
    string mess;
    string com;
    mixed *hitres;
    warwolf = TP->query_prop(WOLF_O_RIDING);
    NF("You are not on a wolf!\n");
    if(!objectp(warwolf))
        return 0;
    NF("Your warwolf is too tired.\n");
    if(warwolf->query_fatigue() < 1)
        return 0;
    NF("Your warwolf has not recovered from it's last slash.\n");
    if(TP->query_prop(SLASH_RESET))
        return 0;
    NF("rlash who?\n");
    if(!str)
    {
        if(objectp(TP->query_attack()))
            enemy = TP->query_attack();
        else 
            return 0;
    }
    else
    { 
        enemys = parse_this(str,"[the] %l");
        if(!sizeof(enemys))
            return 0;
        enemy = enemys[0];
    }
    NF("You don't dare to attack.\n");
    if(!F_DARE_ATTACK(TP,enemy))
        return 0;
    skill = TP->query_skill(SS_WOLF_HANDLING);
    NF("You don't know how to do this manuver.\n");
    if(!skill)
        return 0;
    my_dis = TP->query_stat(SS_DIS);
    warwolf->add_fatigue(-5);
    pen = F_PENMOD(MIN(50,random (21)+(my_dis/4)),skill);
    hitres = enemy->hit_me(pen,W_SLASH,TP,-1);
    switch(hitres[0])
    {
        case 0..10:
           mess = "slightly, opening a small wound";
        break;
        case 11..20:
           mess = "opening a large wound";
        break;
        case 21..30:
           mess = "solidly, tearing open a vicious gash";
           com = "wince";
        break;
        case 31..50:
           mess = "badly, ripping open many gashes";
           com = "groan";
        break;
        case 61..70:
           mess = "very badly, sliceing open many hideous wounds";
           com = "scream";
        default:
           mess = "with incredible force, pieces fly everywhere!";
           com = "wail";
    }
    TP->catch_msg("Your "+warwolf->short()+" slashes "+QTNAME(enemy)+
    " "+mess+".\n");
    enemy->catch_msg(QCTNAME(TP)+"'s "+warwolf->short()+" slashes "+
    "you "+mess+".\n");
    tell_room(E(TP),QCTNAME(TP)+"'s "+warwolf->short()+" slashes "+
    QTNAME(enemy)+" "+mess+".\n",({enemy,TP}));
    if(com)
        enemy->command(com);
    
    TP->add_prop(SLASH_RESET,1);
    set_alarm(SLASH_RESET_TIME,0.0,"reset_slash",TP);
    if(enemy->query_hp() <= 0)
        {
        if (!enemy->query_prop(LIVE_I_NO_CORPSE) &&
            !enemy->query_prop(LIVE_I_NO_BODY))
        {
            setuid(); 
            seteuid(getuid(this_object()));
            corpse = clone_object("/std/corpse");
            corpse->set_name(enemy->query_name());
            corpse->change_prop(CONT_I_WEIGHT, enemy->query_prop(CONT_I_WEIGHT));
            corpse->change_prop(CONT_I_VOLUME, enemy->query_prop(CONT_I_VOLUME));
            corpse->add_prop(CORPSE_S_RACE, enemy->query_race_name());
            corpse->add_prop(CONT_I_TRANSP, 1);
            corpse->change_prop(CONT_I_MAX_WEIGHT, enemy->query_prop(CONT_I_MAX_WEIGHT));
            corpse->change_prop(CONT_I_MAX_VOLUME, enemy->query_prop(CONT_I_MAX_VOLUME));
            corpse->set_short("horridly mutilated corpse");

            tell_room(E(TP),"The "+warwolf->short()+"'s final slash rips it's "+
            "target apart, leaveing a bloody, mutilated corpse twitching on the ground!\n");
            enemy->add_prop(LIVE_I_NO_CORPSE, 1);
            enemy->do_die(TP);
            corpse->move(environment(TP), 0);
        }
    else
        enemy->do_die(TP);
    }
    return 1;

}
void
reset_slash(object ob)
{
    tell_object(ob,"Your warwolf has recovered.\n");
    ob->remove_prop(SLASH_RESET);
}
