inherit "/std/receptacle";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/shadow_walkers/default.h"

#define PTLOG "/d/Kalad/common/guilds/shadow_walkers/PLAYER_TITLES/"

/* The Shadow Walkers Guild Item */


string my_title;

string
query_auto_load()
{
    return MASTER;
}

void
create_receptacle()
{
    set_name("_shadow_walkers_");
    add_name("case");
    set_adj("black");
    add_adj("leather");
    add_adj("carrying");
    set_short("black leather carrying case");
    set_long("This is a medium-sized carrying case made of leather. "+
    "It can carry a fair amount of your stuff that you don't want "+
    "others to get ahold of. On it, you see the symbol of the "+
    "Shadow Walkers etched: A skull and two daggers crossed. You also "+
    "see the words: 'help shadow' on it.\n");
    add_prop(CONT_I_WEIGHT,500);
    add_prop(CONT_I_VOLUME,500);
    add_prop(CONT_I_MAX_WEIGHT,5500);
    add_prop(CONT_I_MAX_VOLUME,5500);
    add_prop(CONT_I_RIGID,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_M_NO_DROP,"You don't want to do that.\n");
    set_alarm(3.0,0.0,"message");
}

void
message()
{
    object me = E(TO);
    me->catch_msg("Welcome "+me->query_name()+", you mangy thief.\n");
}

void
init()
{
    ::init();
    AA(do_title,stitle);
}

int
do_title(string str)
{
    string str1,str2,sname,sadj;
    NF("You must enter two words, lowercase, from the title list. The "+
    "first must be from the name collumn, the second from the adjective "+
    "collumn.\n"); 
    if(!str)
        return 0;
    if(str == "off")
    {
        my_title = "off";
        TP->set_shadow_walker_title(my_title);
        reset_euid();
        save_object(PTLOG+lower_case(TP->query_name()));
        return 1;
    }
    if(sscanf(str,"%s %s",str1,str2) != 2)
        return 0;
    switch(str1)
    {
        case "off":
        sname = "off";
        break;
        case "thief":
        sname = "thief";
        break;
        case "thug":
        sname = "thug";
        break;                   
        case "arsonist":
        sname = "arsonist";
        break;
        case "lurker":
        sname = "lurker";
        break;
        case "menace":
        sname = "menace";
        break;
        case "cutpurse":
        sname = "cutpurse";
        break;
        case "hoodlum":
        sname = "hoodlum";
        break;
        case "ruffian":
        sname = "ruffian";
        break;
        case "brigand":
        sname = "brigand";
        break;
        case "bandit":
        sname = "bandit";
        break;
        case "marauder":
        sname = "marauder";
        break;
        case "looter":
        sname = "looter";
        break;
        case "raider":
        sname = "raider";
        break;
        case "plunderer":
        sname = "plunderer";
        break;
        case "pillager":
        sname = "pillager";
        break;
        case "rogue":
        sname = "rogue";
        break;
        default:
        NF(str1+" is an invalid option.\n");
        return 0;
    }
    switch(str2)
    {
        case "shadow":
        sadj = "shadow";
        break;
        case "grim":
        sadj = "grim";
        break;
        case "dinky":
        sadj = "dinky";
        break;
        case "alley":
        sadj = "alley";
        break;
        case "street":
        sadj = "street";
        break;
        case "unstable":
        sadj = "unstable";
        break;
        case "notorious":
        sadj = "notorious";
        break;
        case "dark":
        sadj = "dark";
        break;
        case "feared":
        sadj = "feared";
        break;
        case "hazerdous":
        sadj = "hazerdous";
        break;
        case "keen":
        sadj = "keen";
        break;
        case "dangerous":
        sadj = "dangerous";
        break;
        case "evil":
        sadj = "evil";
        break;
        case "foul":
        sadj = "foul";
        break;
        case "devious":
        sadj = "devious";
        break;
        case "crazy":
        sadj = "crazy";
        break;
        case "shifty":
        sadj = "shifty";
        break;
        case "twisted":
        sadj = "twisted";
        break;
        case "lone":
        sadj = "lone";
        break;
        case "fearsome":
        sadj = "fearsome";
        break;
        case "brutal":
        sadj = "brutal";        
        break;
        default:
        NF(str2+" is an invalid option.\n");
        return 0;
    }
    my_title = C(sadj)+" "+C(sname);
    TP->set_shadow_walker_title(my_title);
    reset_euid();
    save_object(PTLOG+lower_case(TP->query_name()));
    return 1;
}

