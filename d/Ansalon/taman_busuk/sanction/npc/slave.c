

/* 
 2007-07-07. Added a name so they can be identified.
 Cherek
*/

inherit "/std/act/action.c";
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

inherit AM_FILE

/* Sarr */
/* Borrowed from Sarrs code of a dog in the Neraka npc directory 
*/

object Aowner;

int sX = 20 + random(20);

int *gGender = ({0, 1});

string *gRace = ({"elf","human","dwarf","half-elf"});

string *gAdj = ({"tired","scared","scarred","frightened","forlorn",
  "pitiful","weak","beaten","hungry"});

string gMaster = "master";

int react_kick(object who, string adverb);
int react_touch(object who, string adverb);
int react_anger(object who, string adverb);
int react_forgive(object who, string adverb);
int react_comfort(object who, string adverb);

EMOTE_HOOK

#ifndef ONE_OF
#define ONE_OF(x) (x[random(sizeof(x))])
#endif

string
check_estring(object ob)
{
    int i;
    string str1,*str;
    str1 = ob->query_m_out();
    str = explode(str1," ");
    for(i=0;i<sizeof(str);i++)
    {
	str[i] = "'"+str[i]+"'";
    }
    str1 = implode(str," ");
    return str1;
}


int
set_owner(object ob)
{
    if(!ob)
	return 0;
    trig_new("%s "+check_estring(ob)+" %w","react_leave");
    Aowner = ob;
    if (ob->query_gender() == 1)
        gMaster = "mistress";
    else
        gMaster = "master";
    return 1;
}

object
query_owner()
{
    return Aowner;
}

void
create_krynn_monster()
{
    set_name("slave");
    add_name("_sanction_slave_npc");
    add_adj(ONE_OF(gAdj));
    set_race_name(ONE_OF(gRace));
    set_gender(ONE_OF(gGender));
    set_long("This wretched creature is one of the many "+
      "slaves that can be bought from the slavers in " +
      "Sanction.\n" +capitalize(HE(TO))+ " is wearing an iron collar with "+
      "a chain attached to it around " +HIS(TO)+ " neck.\n");
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(CONT_I_HEIGHT, 150 + random(50));
    add_prop(CONT_I_WEIGHT, 49000 + random(5000));
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_stats(({sX,sX,sX,sX,sX,sX}));
    set_act_time(4);
    add_act("groan piti");
    add_act("say Please "+gMaster+"... release me!");
    add_act("sniff");
    add_act("say These chains hurt my neck...");

    add_emote_hook("kick",1.0,react_kick);
    add_emote_hook("knee",1.0,react_kick);
    add_emote_hook("slap",1.0,react_kick);
    add_emote_hook("lick",1.0,react_touch);
    add_emote_hook("caress",1.0,react_touch);
    add_emote_hook("kiss",1.0,react_touch);
    add_emote_hook("french",1.0,react_touch);
    add_emote_hook("fondle",1.0,react_touch);
    add_emote_hook("grope",1.0,react_touch);
    add_emote_hook("poke",1.0,react_touch);
    add_emote_hook("explode",1.0,react_anger);
    add_emote_hook("growl",1.0,react_anger);
    add_emote_hook("fume",1.0,react_anger);
    add_emote_hook("glare",1.0,react_anger);
    add_emote_hook("scold",1.0,react_anger);
    add_emote_hook("scream",1.0,react_anger);
    add_emote_hook("forgive",1.0,react_forgive);
    add_emote_hook("comfort",1.0,react_comfort);

    add_ask(({"board","board ship"}),
         VBFC_ME("board_command"));
    add_ask("disembark",VBFC_ME("disembark_command"));

    seteuid(getuid());
}

void
init_living()
{
    ::init_living();
    ADA("release");
    add_action(release, "free");
}

void
calculate_experience(object who)
{

    int xp_base = 200;

    if(who->test_bit("ansalon", 0, 1))
    {
	return;
    }

    who->catch_tell("Your good deed makes you " +
      "feel slightly more experienced!\n");
    if(who->query_wiz_level())
    {
	who->catch_msg("xp : " +xp_base+ "\n");
    }

    if(who->query_alignment() < -100)
    {
	who->catch_tell("Your good deed also makes you feel less " +
	  "malevolent.\n");
	who->set_alignment(who->query_alignment() +400);
    }

    who->add_exp(xp_base, 0);
    who->set_bit(0,1);

    A_QUEST_LOG("quest","Free Sanction Slave", who, xp_base);
    return;
}

string
board_command()
{
    if(TO->query_owner() && (TO->query_owner() != TP))
   return "";

    command("say Yes "+gMaster+".");
    command("board ship");
   
   return "";
}

string
disembark_command()
{
    if(TO->query_owner() && (TO->query_owner() != TP))
   return "";

    command("say As you command, "+gMaster+".");
    command("disembark");
   return "";
}

int
release(string str)
{

    if(!str)
	return 0;

    if(str != "slave")
    {
	NF("Release what? The slave?\n");
	return 0;
    }

    if (TO->query_owner() &&
	(TO->query_owner() != TP) &&
	(E(TO->query_owner()) == E(TO)))
    {
	write("You cannot release the slave while the " +
	  "owner is present in the room!\n");
	return 1;
    }

    if(TO->query_owner() != TP)
	calculate_experience(TP);

    write("You remove the chain from around the slaves neck!\n");
    say(QCTNAME(TP)+ " removes the chain from around the slaves neck!\n");
    command("thank " +OB_NAME(TP));
    command("say My thanks! I owe you my life!");
    command("emote quickly scurries off.");
    TO->remove_object();
    return 1;
}

int
react_kick(object who, string adverb)
{
    if(who != TO->query_owner())
	set_alarm(1.0, 0.0, "command","say "+C(gMaster)+"! Will you let others " +
	  "beat me like this?");
    else
    {
	command("emote cries out in pain and anguish.");
	set_alarm(0.5, 0.0, "do_cower", who->query_real_name());
    }
    return 1;
}

do_cower(string who)
{
    object obj;

    if(obj = present(who, environment()))
    {
	command("cower");
	set_alarm(1.0,0.0,"command","say to " +who+ " Please "+gMaster+"! Mercy...");
	return "";
    }
}

int
react_touch(object who, string adverb)
{
    command("say Keep away from me!");
    set_alarm(1.0,0.0,"command","cringe");
    return 1;
}

int
react_anger(object who, string adverb)
{
    if(who == TO->query_owner())
    {
	command("back");
	set_alarm(1.0,0.0,"command","emote starts to shake with fear.");
    }
    return 1;
}

int
react_forgive(object who, string adverb)
{
    if(who != TO->query_owner())
    {
	command("ignore " +who->query_real_name());
    }
    else
    {
	command("emote smiles with relief.");
	set_alarm(1.0,0.0,"command","say Nothing to forgive "+gMaster+"... " +
	  "I am yours to do with as you wish.");
    }
    return 1;
}

int
react_comfort(object who, string adverb)
{
    if(who == TO->query_owner())
	command("smile blank");
    else
    {
	command("say Thankyou... being a slave is a horror I hope you " +
	  "never have to experience...");
	set_alarm(1.0,0.0,"command","shiver");
    }
    return 1;
}

void
react_leave(string name, string dir)
{
    object tone;
    tone = find_player(lower_case(name));
    if(!tone)
    {
	return;
    }
    if(query_owner() == tone)
    {
	dir = extract(dir,0,-3);
	set_alarm(0.2,0.0,&command(dir));
	return;
    }
}

