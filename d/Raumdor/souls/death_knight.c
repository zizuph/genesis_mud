#pragma strict_types

#include "defs.h"

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

public string
get_soul_id()
{
    return "Death Knight soul";
}

public int
query_cmd_soul()
{
    return 1;
}

public mapping
query_ability_map()
{
    return ([
        "bash" : SPECIALS_DIR + "bash",
        "whirlwind" : SPECIALS_DIR + "whirlwind",
    ]);
}

public mapping
query_cmdlist()
{
    return ([
        "bash"          : "do_ability",
        "whirlwind"		: "do_ability",
		"klaugh"		: "emote_klaugh",
    ]);
}

public int
emote_klaugh(string str)
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

