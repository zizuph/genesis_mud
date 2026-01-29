/* 
 * /d/Kalad/common/wild/pass/goblin/guild/riders/collar_test.c
 * Purpose    : Mhyrky's guild collar. This one is just a test file, thou
 * Located    : 
 * Created By : Mhyrkhaan 
 * Modified By: Rico 23.Mar.97; no changes other than some spacing added in 
 */ 

inherit "/std/object";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/goblin/guild/riders/default.h"
#include <tasks.h>

static int worn;

void
create_object()
{
    ::create_object();

    set_name("_rider_");
    add_name("collar");
    set_short("@@query_rank@@");
    set_long("This is your collar, it shows you are a "+
      "Rider of the Red Fang guild. Wear it Proudly!\n");

    add_prop(OBJ_I_WEIGHT,400);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_M_NO_DROP,"You cannot be rid of this unless you leave "+
      "the Riders of the Red Fang.\n");
    add_prop(OBJ_M_NO_SELL,"You dare not sell your Rider collar!.\n");

    set_alarm(3.0,0.0,"message");
}

int
wear(string arg)
{
    object collar;

    NF("Wear what?\n");
    parse_command("wear "+arg,TP,"'wear' %o",collar);
    if(!collar)
	    return 0;

    if(collar != TO)
	    return 0;

    NF("But you already wear it!\n");
    if(worn) 
	    return 0;

    write("You wear "+short()+" around your neck.\n");
    say(QCTNAME(TP)+" wears "+short()+" around "+HIS(TP)+" neck.\n");
    worn = 1;
    TP->add_subloc(file_name(TO), TO);
    set_no_show_composite(1);

    return 1;
}

int
remove(string arg)
{
    NF("Remove what?\n");

    if(!parse_command(arg, TP, " %o ")) return 0;

    NF("First you must have it!\n");
    if(E(TO) != TP) return 0;

    NF("But you don't wear it!\n");
    if(!worn) return 0;

    write("You remove the "+short()+" from your neck.\n");
    say(QCTNAME(TP)+" removes a "+short()+" from "+HIS(TP)+" neck.\n");
    worn = 0;
    TP->remove_subloc(file_name(TO));
    set_no_show_composite(1);

    return 1;
}

string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc != file_name(TO))
	    return "";

    if (for_obj != on)
       return capitalize(HE(on)) + " is wearing " + short() +
          "around " + HIS(on) + " neck.\n";
    else
	    return "You are wearing "+short()+" around your neck.\n";
}

string 
query_auto_load() 
{
    return MASTER+":"; 
}

void
message()
{
    write("Hail Red Fang Rider! Destroy the human empire!\n");

    return;
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if (to->query_wiz_level())
	return;
    if(to->query_race_name() == "human")
    {
	to->catch_msg("Your collar is blown up as you have betrayed the "+
	  "Riders by changing your race to human!\n");
	to->remove_guild_race();
	to->clear_bit(4,8);
	to->clear_guild_stat(SS_LAYMAN);
	to->update_hooks();
	remove_object();
    }
    to->set_m_in("arrives.");
    to->set_m_out("leaves");
}

void
init()
{
    ::init();
    AA(riderhelp,riderhelp);
    AA(rtitles,rtitles);
    AA(remotes,remotes);
    AA(rhistory,rhistory);
    AA(wear,wear);
    AA(rsummon,rsummon);
    AA(remove,remove);
    set_alarm(1.0,0.0,"get_me_soul",TP);
}

void
get_me_soul(object ob)
{
    int i;
    string *souls;

    seteuid(getuid());
    souls = ob->query_cmdsoul_list();
    for (i = 0; i < sizeof(souls); i++)
	ob->remove_cmdsoul(souls[i]);

    ob->add_cmdsoul(RIDER_SOUL);

    for(i = 0; i < sizeof(souls); i++)
	if(souls[i] != RIDER_SOUL)
	    ob->add_cmdsoul(souls[i]);
    ob->update_hooks();
}

int
rsummon()
{
    write("You whistle for a weasel.\n");
    say(QCTNAME(TP)+" whistles for a weasel.\n");
    if(TP->resolve_task(TASK_ROUTINE,({SKILL_WEIGHT,200,105})) > 0)
    {
	set_alarm(5.0,0.0,"weasel");
	return 1;
    }
    set_alarm(5.0,0.0,"fail");
    return 1;
}

void
weasel()
{
    object obj;
    seteuid(getuid(TO));
    tell_room(E(TP),"A weasel skitters up to "+QCTNAME(TP)+".\n",TP);
    obj = clone_object(CPASS(goblin/guild/weasel));
    write("A weasel skitters up to you.\n");
    obj->move(TP);
}

void
fail()
{
    write("You feel that you failed to summon your weasel.\n");
}

int
riderhelp()
{
    write("+------------------------------------------------------+\n");
    write("| To get a list of emotes------------------- remotes   |\n");
    write("| To get a history of the Riders------------ rhistory  |\n");
    write("| To speak in the Rider language------------ risay     |\n");
    write("| To get a list of titles------------------- rtitles   |\n");
    write("+------------------------------------------------------+\n");
    return 1;
}
int
rhistory()
{
    TP->more("/d/Kalad/open/RIDER_INFO",1);
    return 1;
}

int
rtitles()
{
    write("+----------------------------------------------+\n");
    write("| Novice Rider of the Red Fang                 |\n");
    write("| Trainee Rider of the Red Fang                |\n");
    write("| Trained Rider of the Red Fang                |\n");
    write("| Experineced Rider of the Red Fang            |\n");
    write("| Expert Rider of the Red Fang                 |\n");
    write("| Specialist Rider of the Red Fang             |\n");
    write("| Master Rider of the Red Fang                 |\n");
    write("| Elite Rider of the Red Fang                  |\n");
    write("| Legendary Rider of the Red Fang              |\n");
    write("+----------------------------------------------+\n");
    return 1;
}

int
remotes()
{
    TP->more("/d/Kalad/open/RIDER_EMOTES",1);
    return 1;
}

string query_rank()
{
    switch(environment()->query_rider_level())
    {
    case 0:
	return "a black leather collar";
	break;
    case 1:
	return "a rusted iron collar";
	break;
    case 2:
	return "a dingy copper collar";
	break;
    case 3:
	return "a polished steel collar";
	break;
    case 4:
	return "a smooth brass collar";
	break;
    case 5:
	return "a shiny, gold-studded silver collar";
	break;
    case 6:
	return "a bright, emerald-studded gold collar";
	break;
    case 7:
	return "an exsquisite, saphire-studded platinum collar";
	break;
    case 8:
	return "an impresive, ruby-spiked obsidian collar";
	break;

    }
}                          
