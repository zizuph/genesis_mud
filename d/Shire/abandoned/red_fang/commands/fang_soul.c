#pragma strict_types

inherit "/cmd/std/command_driver";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"
#include <tasks.h>
#include <cmdparse.h>

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Fang"; }

public mapping
query_cmdlist()
{
    return ([
#include "fcommands.h"
            ]);
}

public int
c_fanghelp(string str)
{
    string file;
    setuid();
    seteuid(getuid());
    NF("Fanghelp on what?\n");
    if(!str)
    {
        file = read_file(FANG_DIR(doc/help_fang));
        if(stringp(file))
            TP->more(file,0);
        return 1;
    }
    if(str == "emotes")
    {
        file = read_file(FANG_DIR(doc/help_emotes));
        TP->more(file,0);
        return 1;
    }
    if(str == "tribes")
    {
        file = read_file(FANG_DIR(doc/GOBLIN_TRIBES));
        TP->more(file,0);
        return 1;
    }
    if(str == "titles")
    {
        file = read_file(FANG_DIR(doc/help_titles));
        TP->more(file,0);
        return 1;
    }
    if(str == "history")
    {
        file = read_file(FANG_DIR(doc/help_history));
        TP->more(file,0);
        return 1;
    }
    return 0;
}

public int
ftoggle(string str)
{
    int i;
    if(!str)
        return 0;
    sscanf(str,"%d",i);
    TP->set_toggle(i);
    write("Toggle set to option "+i+".\n");
    return 1;
}

public int
set_tribe(string str)
{
    mapping master_tribes;
    string clan, tribe,*tribes;

    master_tribes = (["Red Hand":
                        ({"T'Sarn","Og'Tog","Fume","Ruzar","Ugblop"}),
                      "Black Tooth":
                        ({"Ha'Gash","Zagnug","Argon","Taktak","Anaar"}),
                      "Iron Rock":
                        ({"Boldar","Elbog","Yur'Nash","Cush","Zolraag"}),
                      "Bone Smasher":
                        ({"Rancor","Bazakur","Olgnar","Un'Taro","Guggug"}),
                      "Bloody Fist":
                        ({"Ussak","Yel'Dagar","Rordak","Ulhass","Jag"}),
                      "Black Blade":
                        ({"Taranor","Torak","Rivinor","Smine","Vindicore"}),
                      "Grinning Skull":
                        ({"Zaash","Enkish","Hack'Tak","Gerleer","Slake"})
                       ]);
    tribes = m_indexes(master_tribes);
    NF("Invalid option or name.\n");
    if(sscanf(str,"%s of %s",clan,tribe) != 2)
        return 0;
    if(member_array(tribe,tribes) == -1)
        return 0;
    if(member_array(clan,master_tribes[tribe]) == -1)
        return 0;
    TP->set_family(C(clan),C(tribe),3);
    write("Tribe set.\n");
    return 1;
}


public int
e_fyawn()
{
    allbb(" yawns tiredly, revealing jagged sharp teeth.");
    write("You yawn tiredly, revealing jagged sharp teeth.\n");
    return 1;
}

public int
e_fwipe()
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
e_fwait()
{
    allbb(" draws the symbol of the Red Fang on the ground in the "+
        "dirt with "+HIS(TP)+" foot.");
    write("You draw the symbol of the Red Fang on the ground in the "+
        "dirt with your foot.\n");
    return 1;
}

public int
e_fbored()
{
    allbb(" boringly picks "+HIS(TP)+" nose.");
    write("You boringly pick your nose.\n");
    return 1;
}

public int
e_fblood()
{
    allbb(" wipes the blood off "+HIS(TP)+" face with "+HIS(TP)+
        " hand.");
    write("You wipe the blood off your face with your hand.\n");
    SOULDESC("dripping with blood");
    return 1;
}   

public int
e_fdrool(string str)
{
    NF("Fdrool at the thought of what?\n");
    if(!str)
        return 0;
    allbb(" drools all over "+HIS(TP)+" chest at the thought of "+
        str+".");
    write("You drool all over your chest at the thought of "+str+".\n");
    SOULDESC("drooling all over");
    return 1;
}   

public int
e_frest()
{
    allbb(" sits on the ground and rests "+HIS(TP)+" battle weary "+
        "body.");
    write("You sit on the ground and rest your battle weary body.\n");
    SOULDESC("resting on the ground");
    return 1;
}   

public int
e_ftrack(string str)
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
e_fspin(string arg)
{
    int i;
    object obj;
    object *oblist; 
    NF("Spin what dagger or knife in your hand?\n");
    if(!arg)
        return 0;
    oblist = FIND_STR_IN_OBJECT(arg,TP);
    if(sizeof(oblist))
        obj = oblist[0];
    if(!objectp(obj))
        return 0;
    if(present(obj,TP))
    {
        NF("That is not a dagger or knife!\n");
        if(obj->query_wt() != W_KNIFE)
            return 0;
        allbb(" spins the "+obj->query_short()+" in "+HIS(TP)+
            " hand with a malevolent gleam in "+HIS(TP)+" eye.");
        write("You spin the "+obj->query_short()+" in your hand "+
            "with a malevolent gleam in your eye.\n");
        return 1;
    }
    NF("You don't have the "+obj->query_short()+".\n");
    return 0;
}

public int
e_fgrowl(string arg)
{
    object *oblist;
    
    NF("Fgrowl at whom?\n");
    
    if (!strlen(arg))
        {
        allbb(" growls with menacing hatred.");
        write("You growl with menacing hatred.\n");
        SOULDESC("growling with menacing hatred");
        return 1;
    }
    
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if (!sizeof(oblist))
        return 0;
    
    SOULDESC("growling with menacing hatred");
    actor("You growl at", oblist, " with menacing hatred.");
    all2actbb(" growls at", oblist, " with menacing hatred.");
    targetbb(" growls at you with menacing hatred.", oblist);
    return 1;
}

public string
q_title(object ob, int wiz)
{
    if (!ob->query_guild_member("Red Fang Guild"))
        return 0;
    if(ob->query_wiz_level())
        return implode(explode(break_string("@"+ob->query_presentation(), 76), "\n"),
        "\n    "); 
    return implode(explode(break_string(ob->query_presentation(), 76), "\n"),
        "\n    ");
}

public int
e_flist(string arg)
{
    int i;
    i = (query_verb() == "mwlist" ? 1 : 0);
    write("You know that the following members of the Red Fang "+
        "are currently within the world:\n"+
        implode(map(users() - ({ 0 }), "q_title", this_object(), i) - ({ 0 }),
            "\n") + "\n");
    return 1;
}

public int
e_fsay(string arg)
{
    if (!strlen(arg))
    {
        NF("Say what in the ancient Kaladian goblin tongue?\n");
        return 0;
    }
    
    if(TP->query_skill(SS_LANGUAGE) < 30)
    {
        NF("You are not skilled enough in foreign tongues to be able to "+
            "speak the ancient Kaladian goblin tongue.\n");
        return 0;
    }
    
    write("In the ancient Kaladian goblin tongue, you say: " + arg + "\n");
    
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
    tell_object(who, this_player()->query_The_name(who) + " growls " +
        "in the ancient Kaladian goblin tongue: " + arg + "\n");
    else
        tell_object(who, this_player()->query_The_name(who) + " growls " +
        "something.\n");
}

public int
e_flaugh(string arg)
{
    object *oblist;
    
    NF("Flaugh at who?\n");
    
    if (!strlen(arg))
        {
        all(" howls a terrible and frightening laughter.");
        write("You howl a terrible and frightening laughter.\n");
        SOULDESC("howling a terrible and frightening laughter");
        return 1;
    }
    
    oblist = parse_this(arg, "[at] / [to] [the] %l");
    if (!sizeof(oblist))
        return 0;
    
    actor("You howl a terrible and frightening laughter at", oblist);
    all2act(" howls a terrible and frightening laughter at", oblist);
    target(" howls a terrible and frightening laughter at you.", oblist);
    SOULDESC("howling a terrible and frightening laughter");
    return 1;
}

public int
e_fint(string arg)
{
    object *oblist;
    
    NF("Fint who?\n");
    if (!strlen(arg))
        return 0;
    
    oblist = parse_this(arg, "[the] %l");
    if (!sizeof(oblist))
        return 0;
    if (sizeof(oblist) >1)
        { NF("You can only do this to one person at a time.\n"); return 0; }
    actor("You grab and pin", oblist, " against a wall, staring intently "+
        "into "+oblist[0]->query_possessive()+" eyes.");
    all2actbb(" grabs and pins", oblist, " against a wall, staring intently "+
        "into "+oblist[0]->query_possessive()+" eyes.");
    targetbb(" grabs and pins you against a wall, staring intently "+
        "into your eyes.", oblist);
    return 1;
}

public int
e_fspit(string arg)
{
    object *oblist;
    NF("Fspit at whom?\n");
    if(!strlen(arg))
        {
        allbb(" spits on the ground in hatred of foul humans.");
        write("You spit on the ground in hatred of foul humans.\n");
        SOULDESC("spitting in hatred of foul humans");
        return 1;
    }
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if (!sizeof(oblist))
        return 0;
    SOULDESC("spitting in hatred of foul humans");
    actor("You spit on", oblist, " in hatred.");
    all2actbb(" spits on", oblist, " in hatred.");
    targetbb(" spits on you in hatred.", oblist);
    return 1;
}

public int
e_fgrin(string arg)
{
    object *oblist;
    NF("Grin at whom?\n");
    if(!strlen(arg))
        {
        allbb(" grins treacherously, revealing jagged sharp teeth.");
        write("You grin treacherously, revealing jagged sharp teeth.\n");
        SOULDESC("grinning treacherously");
        return 1;
    }
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if(!sizeof(oblist))
        return 0;
    SOULDESC("grinning treacherously");
    actor("You grin treacherously at", oblist,", revealing jagged sharp teeth.");
    all2actbb(" grins treacherously at", oblist,", revealing jagged sharp teeth.");
    targetbb(" grins treacherously at you, revealing jagged sharp teeth.", 
        oblist);
    return 1;
}


public int
e_fsnarl(string arg)
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
e_fsalute(string arg)
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
e_fnod(string arg)
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
e_fcross()
{
    allbb(" folds "+TP->query_possessive()+" arms across "+
        TP->query_possessive()+" chest and stands straight in "+
        "defiance."); 
    write("You fold your arms across your chest and stand "+
        "straight in defiance.\n");
    SOULDESC("crossing "+TP->query_possessive()+" arms defiantly");
    return 1;
}

int
e_fblaze()
{
    write("Your eyes blaze red with fury.\n");
    say(QCTNAME(TP)+"'s eyes blaze red with fury.\n");
    return 1;
}

int
e_fhowl()
{
    write("You howl in fury like a wolf.\n");
    say(QCTNAME(TP)+" howls in fury like a wolf.\n");
    return 1;
}

int
e_fflex()
{
    write("You flex your bulging goblin muscles.\n");
    say(QCTNAME(TP)+" flexes "+TP->query_possessive()+" bulging goblin "+
        "muscles.\n");
    return 1;
}

int
e_fwar()
{
    string warcry;
    switch(random(6))
    {
        case 0:
        warcry = "The Red Fang shall never die!\n";
        break;
        case 1:
        warcry = "Down with the Thanar!\n";
        break;
        case 2:
        warcry = "Long live the Goblins!\n";
        break;
        case 3:
        warcry = "Kalad! Kalad! Forever our home!\n";
        break; 
        case 4:
        warcry = "Death to the enemies of the Red Fang!\n";
        break;
        case 5:
        warcry = "Aaaaiiiieeeeee!!\n";
        break;
    }
    
    write("You cry out: "+warcry);
    say(QCTNAME(TP)+" cries out: "+warcry);
    return 1;
}

int
e_fbark(string arg)
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
    write("Your eyes blaze with battle lust.\n");
    say(QCTNAME(TP) + "'s eyes blaze with battle lust.\n");
    return 0;
}

