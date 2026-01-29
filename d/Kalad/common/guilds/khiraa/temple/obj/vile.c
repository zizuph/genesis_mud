/* 
 * /d/Kalad/common/guilds/khiraa/temple/obj/vile.c
 * Purpose    : This is the smith of the guild.
 * Located    : ~khiraa/temple/rooms/temple_forge
 * Created By : Sarr 12.Apr.97
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
inherit "/d/Kalad/lib/intro";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

#define NUM sizeof(MONEY_TYPES)
#define AM_BUILDING "am_building"


#pragma save_binary

string *armour_types = ({"helm","breastplate","bracers","gauntlets","greaves","boots","robe"});

string *armour_metal = ({"steel","iron","leather","cloth"});


/* The death knight who works armours and weapons */

void
create_monster()
{
    ::create_monster();
    set_name("vile");
    set_adj("muscular");
    add_adj("hooded");
    set_race_name("human");
    set_short("muscular hooded human");
    set_long("This human is very big and muscular looking. Upon his "+
    "pale skin, you see marks of red that are symbols of magic long "+
    "forgotten. He wears a black hood, and you cannot see his face. "+
    "He wears armoured greaves and boots, but his upper torso is "+
    "bare. Despite the intense heat, no sweat runs down his pale skin.\n");
    add_prop(LIVE_I_UNDEAD,100);
    set_stats(({180,100,200,100,100,100}));
    set_alignment(-2000);
    set_title("the Forger Knight of the Khiraa");
    add_prop(LIVE_I_SEE_DARK,50);
    set_skill(SS_DEFENCE,100);
    set_default_answer("The "+short()+" rumbles from within his "+
    "black hood: If you would like to to know what I can do for you, "+
    "ask me about 'service'.\n");

    add_ask("service","The "+short()+" rumbles from within his "+
    "black hood: Here is what I can do:\n"+
    "build <armour> from <material> -\n"+
    "   Armour Types: helm, breastplate, bracers, gauntlets, greaves\n"+
    "   and boots.\n"+
    "   Material Types: cloth, leather, iron, steel.\n"+
    "wbuild <weapon> - \n"+
    "   Weapons availabled: short sword, sword, long sword, staff\n"+
    "   halberd.\n"+
    "sharpen <weapon> -\n"+
    "   Sharpen a dull weapon.\n"+
    "wax <weapon> -\n"+
    "   Wax a corroded weapon.\n"+
    "repair <armour> -\n"+
    "   Repair a damaged armour.\n"+
    "cost <weapon/armour> - \n"+
    "   Will estimate cost of sharpening or waxing a weapon/armour.\n"+
    "acost <armour> from <material> -\n"+
    "   Estimate cost on constructing this armour.\n"+
    "wcost -\n"+
    "   Costs on building a weapon.\n"+
    "You can ask me 'cross', 'rope', 'stake', or 'hook', to get one of those "+
    "things for free.\n");

    add_ask("build","The "+short()+" rumbles from within his "+
    "black hood: Yes, you type: build 'armour type' from 'metal type'.\n");
    add_ask("fix","The "+short()+" rumbles from within his "+
    "black hood: Yes, you type: fix 'armour'.\n");
    
    add_ask("hook","@@hook@@",1);
    add_ask("rope","@@rope@@",1);
    add_ask("stake","@@stake@@",1);
    add_ask("cross","@@cross@@",1);
    default_config_trade();
}

string
cross()
{
    seteuid(getuid());
    if(objectp(TP))
    {
        command("say Sure, here you go.");
        clone_object(KHIRAA_DIR(temple/obj/crux_poles))->move(TO);
        command("give poles to "+TP->query_real_name());
    }
    if(present("poles",TO))
        present("poles",TO)->remove_object();
    return "emote grins evilly with an unholy light in his eyes.";
}


string
hook()
{
    seteuid(getuid());
    if(objectp(TP))
    {
        command("say Sure, here you go.");
        clone_object(DK_DIR(obj/c_hook))->move(TO);
        command("give hook to "+TP->query_real_name());
    }
    if(present("hook",TO))
        present("hook",TO)->remove_object();
    return "emote grins evilly with an unholy light in his eyes.";
}

string
stake()
{
    seteuid(getuid());
    if(objectp(TP))
    {
        command("say Sure, here you go.");
        clone_object(KHIRAA_DIR(temple/obj/wooden_stake))->move(TO);
        command("give stake to "+TP->query_real_name());
    }
    if(present("stake",TO))
        present("stake",TO)->remove_object();
    return "emote grins evilly with an unholy light in his eyes.";
}

string
rope()
{
    seteuid(getuid());
    if(objectp(TP))
    {
        command("say Sure, here you go.");
        clone_object(DK_DIR(obj/c_rope))->move(TO);
        command("give rope to "+TP->query_real_name());
    }
    if(present("hook",TO))
        present("hook",TO)->remove_object();
    return "emote grins evilly with an unholy light in his eyes.";
}


void
init_living()
{
    ::init_living();
    AA(do_build,build);
    AA(do_wbuild,wbuild);
    AA(do_acost,acost);
    AA(do_wcost,wcost);
}

int
do_wcost(string str)
{
    write("Costs on the weapons I can make:\n"+
    "short sword - 576 cc\n"+
    "sword - 1008 cc\n"+
    "long sword - 1584 cc\n"+
    "staff - 512 cc\n"+
    "halberd - 1412 cc\n");
    return 1;
}

int
do_wbuild(string str)
{
    int *arr,iprice;
    string str2,str3;
    object wep;
    NF("Build what weapon?\n");
    switch(str)
    {
        case "short sword":
            wep = clone_object(RAUM(wep/dopsword));
            iprice = 576;
        break;
        case "sword":
            wep = clone_object(RAUM(wep/kbsword));
            iprice = 1008;
        break;
        case "long sword":
            wep = clone_object(RAUM(wep/kblsword));
            iprice = 1584;
        break;
        case "staff":
            wep = clone_object(RAUM(wep/wstaff));
            iprice = 512;
        break;
        case "halberd":
            wep = clone_object(RAUM(wep/whalberd));
            iprice = 1412;
        break;
        default:
            return 0;
    }
    if(!objectp(wep))
        return 0;
    if (sizeof(arr = pay(iprice, this_player(), str2, 0, 0, str3)) == 1)
       return 0;  /* pay() handles notify_fail() call */
    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
       write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    command("emote looks through a rack of newly forged weapons.");
    command("say Ok, here is a "+wep->short()+" for you.");
    if(wep->move(TP))
        wep->move(E(TP));
    return 1;
}

int
do_build(string str)
{
    string stype,smetal,fname,str2,str3;
    int *arr,iprice;
    object arm;

    NF("What do you want me to build?\n");
    if(!str)
        return 0;
    if(sscanf(str,"%s from %s",stype,smetal) != 2)
        return 0;
    NF("I don't have that type of metal.\n");
    if(member_array(smetal,armour_metal) == -1)
        return 0;
    NF("I don't build that type of armour.\n");
    if(member_array(stype,armour_types) == -1)
        return 0;
    NF("The "+short()+" says: I'm busy right now, later!\n");
    if(query_prop(AM_BUILDING))
        return 0;
    NF("I can't make a "+stype+" from "+smetal+".\n");
    switch(smetal)
    {
        case "steel":
        case "iron":
        case "leather":
           if(stype == "robe")
               return 0;
        break;
        case "cloth":
           if(member_array(stype,({"helm","bracers","gauntlets",
              "boots"})) != -1)
               return 0;
        break;
        default:
            return 0;
    } 
    fname = smetal+"_"+stype;
    if(stype != "robe")
    arm = clone_object("/d/Kalad/common/guilds/khiraa/temple/obj/arms/"+fname);
    else
        arm = clone_object("/d/Kalad/common/guilds/khiraa/temple/obj/khiraa_cloak");

    iprice = arm->query_prop(OBJ_I_VALUE);
    
    if (sizeof(arr = pay(iprice, this_player(), str2, 0, 0, str3)) == 1)
       return 0;  /* pay() handles notify_fail() call */
    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
       write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    command("say Ok, I will get to work on your "+arm->short()+"!");
    command("emote starts working on a "+arm->short()+".");
    set_alarm(15.0,0.0,"deliver",TP,arm);
    add_prop(AM_BUILDING,1);
    return 1;
}

void
deliver(object me, object arm)
{
    command("say Ok, "+me->query_name()+", your "+arm->short()+" is "+
    "done.");
    if(!present(me,E(TO)))
    {
        command("say Bah! "+C(HE(me))+" left, I'll just leave it here for "+
        HIM(me)+".");
        arm->move(E(TO));
        remove_prop(AM_BUILDING);
        return;
    }
    set_this_player(me);

    write("You get "+LANG_ADDART(arm->short())+".\n");
    say(QCTNAME(TP)+" gets "+LANG_ADDART(arm->short())+".\n"); 
    
    if(arm->move(TP))
    {
        write("Its too heavy, and you drop it.\n");
        arm->move(E(TP));
    }
    remove_prop(AM_BUILDING);

    return;
}

int
do_acost(string str)
{
    string stype,smetal,fname,str2,str3;
    int *arr,iprice;
    object arm;

    NF("What do you want me to build?\n");
    if(sscanf(str,"%s from %s",stype,smetal) != 2)
        return 0;
    NF("I don't have that type of metal.\n");
    if(member_array(smetal,armour_metal) == -1)
        return 0;
    NF("I don't build that type of armour.\n");
    if(member_array(stype,armour_types) == -1)
        return 0;
    NF("I can't make a "+stype+" from "+smetal+".\n");
    switch(smetal)
    {
        case "steel":
        case "iron":
        case "leather":
           if(stype == "robe")
               return 0;
        break;
        case "cloth":
           if(member_array(stype,({"helm","bracers","gauntlets",
              "boots"})) != -1)
               return 0;
        break;
        default:
            return 0;
    } 
    fname = smetal+"_"+stype;
    arm = clone_object("/d/Kalad/common/guilds/khiraa/temple/obj/arms/"+fname);
    iprice = arm->query_prop(OBJ_I_VALUE);
    command("say I can make you "+LANG_ADDART(arm->short())+" for "+
    iprice+" coppers.");
    arm->remove_object();
    return 1;
}
