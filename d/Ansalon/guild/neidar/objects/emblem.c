#pragma strict_types

inherit "/std/object";
inherit "/lib/commands";

#include "../guild.h"

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include "/d/Ansalon/common/defs.h"
#define PUNISH_FILE (SAVE_PATH + "punish")
#define RETIRED_FILE (SAVE_PATH + "elder_retired")

int pipe_filled = 0;
int pipe_lit = 0;
string *punishlist = ({ });
string *retiredlist = ({ });

void
create_object()
{
    set_name("pipe");
    add_name(GUILD_EMBLEM_ID);
    set_adj("long-stemmed");
    add_adj("long");
    add_adj("stemmed");
    set_short("long-stemmed pipe");


    set_long("This long-stemmed pipe is common amongst " +
      "dwarven warriors, who enjoy a good smoke after a battle, " +
      "meal, or just about any occasion. Skilfully " +
      "carved along the stem of the pipe are the words " +
      "written in dwarven 'help clan menu'." +
      "\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GET,  1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME,  500);

    remove_prop(OBJ_I_VALUE);
    seteuid(getuid(TO));
    restore_object(PUNISH_FILE);
}

void
enter_env(object from, object to)
{
    string who;

    who = TP->query_real_name();

    if(member_array(who, punishlist) >= 0)
    {
	set_alarm(2.0, 0.0, "banish_member");
    }
    if(member_array(who, retiredlist) >= 0)
    {
	set_alarm(3.0,0.0, "retire_elder");
    }
    ::enter_env(from, to);
}

void
banish_member()
{
    if(TP->test_bit("Ansalon",3,4) &&
      TP->test_bit("Ansalon",3,3))
	return;
    write("Two gruff looking dwarves approach you, the " +
      "larger one saying: You have been exiled from the Clan by " +
      "the Thane of the Hill Dwarves! You are no longer welcome " +
      "in Iron Delving!\nTwo gruff looking dwarves storm off.\n");
    say("Two gruff looking dwarves approach " +QTNAME(TP)+
      ", the larger of the two saying: You have been exiled from " +
      "the Clan by the Thane of the Hill Dwarves! You are no longer "+
      "welcome in Iron Delving!\nTwo gruff looking dwarves " +
      "storm off.\n");
    TP->set_bit(3,4);
    TP->set_bit(3,3);
}

void
retire_elder()
{
    string str = TP->query_real_name();

    write("You have been retired as an advisor of the Thane.\n");
    restore_object(RETIRED_FILE);
    retiredlist -= ({str});
    save_object(RETIRED_FILE);
    if(BANISHED(TP))
	return;
    TP->clear_bit(3,4);
}

void
leave_env(object inv, object to)
{
    ::leave_env(inv,to);
}

void
init()
{
    ::init();
    ADA("dchew");
    ADA("dclean");
    ADA("dcomplain");
    ADA("dglow");
    ADA("dpack");
    ADA("dscratch");
    ADA("dsuspect");
    ADA("blow");
    ADA("fill");
    ADA("light");
    ADA("smoke");
    ADA("tap");
}

int
dchew(string str)
{
    if(!str)
    {
     notify_fail("Chew on what? Your pipe?\n");
     return 0;
    }

    if(str == "pipe" || str == "long-stemmed pipe" ||
       str == "on pipe" || str == "on long-stemmed pipe")
      {
        write("You start chewing on the end of your " +
        TO->short()+ " thoughtfully.\n");
	say(QCTNAME(TP)+ " starts chewing on the end of " +HIS(TP)+
        " " +TO->short()+ " thoughtfully.\n");
       return 1;
      }
    notify_fail("Chew on what?\n");
    return 0;
}

int
dclean(string str)
{
    if(str && str != "pipe")
    {
     notify_fail("Do what with your pipe?\n");
     return 0;
    }

        write("You start to lovingly clean your " +TO->short()+ ".\n");
	say(QCTNAME(TP)+ " starts to lovingly clean " +HIS(TP)+
        " " +TO->short()+ ".\n");
       return 1;
}

int
dcomplain(string str)
{
    if(str)
    {
     notify_fail("Do what?\n");
     return 0;
    }

        write("You complain about being out of tobacco.\n");
	say(QCTNAME(TP)+ " is not happy about being out of " +
        "tobacco, and makes it perfectly clear to anyone who " +
        "cares to listen to " +HIS(TP)+ " complaints " +
        "that this is not a good thing.\n");
       return 1;
}


int
dglow(string str)
{
    if(str)
    {
     notify_fail("Do what with your pipe?\n");
     return 0;
    }


	if(pipe_lit == 0)
	{
	    write("The long-stemmed pipe isn't lit!\n");
	    return 1;
	}
	if(pipe_filled == 0)
	{
	    write("There is nothing in the long-stemmed pipe to smoke!\n");
	    return 1;
	}

        write("You take a long drag on your " +TO->short()+
        ", making the cherry glow very brightly.\n");
	say(QCTNAME(TP)+ " takes a long drag on " +HIS(TP)+
        " " +TO->short()+ ", making its cherry glow very brightly.\n");
       return 1;
}

int
dpack(string str)
{
    object tobac;

    if(!str)
	return 0;

    if(str == "pack")
	return 0;

    if(str == "backpack")
	return 0;

    if(str == "lamp with oil" || str == "lamp")
	return 0;

    if(str == "pipe with tobacco" || str == "pipe")
    {
	if(!P("tobacco", TP))
	{
	    write("You have no tobacco to fill your pipe with!\n");
	    return 1;
	}
	if(pipe_filled == 1)
	{
	    write("The pipe is already full of tobacco!\n");
	    return 1;
	}
	tobac = P("tobacco", TP);
	write("You start packing your pipe with " +tobac->short() + 
          " while contemplating the situation.\n");
	say(QCTNAME(TP)+ " starts packing " +HIS(TP)+ " pipe " +
	  "with " +tobac->short() + " while contemplating the " +
          "situation.\n");
	tobac->remove_object();
	pipe_filled = 1;
	return 1;
    }
    return 0;
}

int
dscratch(string str)
{
    string beard;

    if(str)
    {
     notify_fail("Do what with your pipe?\n");
     return 0;
    }
    
    if(TP->query_gender() == 1) /* Female */
     beard = "whiskers";
    else
     beard = "beard";


        write("You scratch your " +beard+ " with the end of " +
         "your " +TO->short()+ ".\n");
	say(QCTNAME(TP)+ " scratches " +HIS(TP)+ " " +beard+ " " +
         "with the end of " +HIS(TP)+ " " +TO->short()+ ".\n");
       return 1;
}

int
dsuspect(string str)
{

    object *ob;

    if(!str)
	return 0;


    ob = PARSE_THIS(str, "%l");

    if(sizeof(ob))
    {

	actor("You stare suspiciously at", ob, " over the top of " +
          "your " +TO->short() + ".");
	target(" stares suspiciously at you over the top of " +
          HIS(TP)+ " " +TO->short()+ ".", ob);
	all2act(" stares suspiciously at", ob, " over the top of " +
          HIS(TP)+ " " +TO->short()+ ".");
	return 1;
    }

    return 0;
}

int
blow(string str)
{

    object *ob;

    if(!str)
	return 0;

    if(str == "smoke" || str == "rings" || str == "smokerings")
    {
	if(pipe_lit == 0)
	{
	    write("The long-stemmed pipe isn't lit!\n");
	    return 1;
	}
	if(pipe_filled == 0)
	{
	    write("There is nothing in the long-stemmed pipe to smoke!\n");
	    return 1;
	}

	if(str == "smoke")
	{
	    write("You inhale on your long-stemmed pipe, " +
	      "and casually blow great plumes of smoke out your nose.\n");
	    say(QCTNAME(TP)+ " inhales on " +HIS(TP)+ 
	      " long-stemmed pipe, and then casually blows great " +
	      "plumes of smoke out " +HIS(TP)+ " nose.\n");
	    return 1;
	}
	if(str == "rings" || str == "smokerings")
	{
	    write("You inhale on your long-stemmed pipe, " +
	      "and then pleasurably blow out rings of smoke that " +
	      "slowly float away from you.\n");
	    say(QCTNAME(TP)+ " inhales on " +HIS(TP)+ 
	      " long-stemmed pipe, and then pleasurably blows " +
	      "out rings of smoke that slowly float away from " +
	      HIM(TP) + ".\n");
	    return 1;
	}
	return 0;
    }

    ob = PARSE_THIS(str, "[smoke] [at] [the] %l");

    if(sizeof(ob))
    {
	if(pipe_filled == 0)
	{
	    write("Your pipe is empty!\n");
	    return 1;
	}
	if(pipe_lit == 0)
	{
	    write("Your pipe is not lit.\n");
	    return 1;
	}
	actor("You casually inhale on your long-stemmed pipe, and " +
	  "then blow a great cloud of smoke into", ob, "'s face.");
	target(" casually inhales on " +HIS(TP)+ " long-stemmed pipe, " +
	  "and then blows a great cloud of smoke into your face!", ob);
	all2act(" casually inhales on " +HIS(TP)+ " long-stemmed pipe, " +
	  "and then blows a great cloud of smoke into", ob,"'s face!");
	return 1;
    }

    return 0;
}

void
extinguish_pipe()
{
    write("Your pipe goes out.\n");
    say(QCTNAME(TP) + "'s long-stemmed pipe goes out.\n");
    pipe_filled = 0;
    pipe_lit = 0;
}


int
fill(string str)
{
    object tobac;

    if(!str)
	return 0;

    if(str == "pack")
	return 0;

    if(str == "backpack")
	return 0;

    if(str == "lamp with oil" || str == "lamp")
	return 0;

    if(str == "pipe with tobacco" || str == "pipe")
    {
	if(!P("tobacco", TP))
	{
	    write("You have no tobacco to fill your pipe with!\n");
	    return 1;
	}
	if(pipe_filled == 1)
	{
	    write("The pipe is already full of tobacco!\n");
	    return 1;
	}
	tobac = P("tobacco", TP);
	write("You fill your pipe with " +tobac->short() + ".\n");
	say(QCTNAME(TP)+ " fills " +HIS(TP)+ " pipe " +
	  "with " +tobac->short() + ".\n");
	tobac->remove_object();
	pipe_filled = 1;
	return 1;
    }
    return 0;
}

int
light(string str)
{
    if(!str)
	return 0;

    if(str == "pipe" || str == "long-stemmed pipe")
    {
	if(pipe_filled == 0)
	{
	    write("The pipe has no tabacco in it!\n");
	    return 1;
	}
	write("You light up your long-stemmed pipe.\n");
	say(QCTNAME(TP)+ " lights up " +HIS(TP)+
	  " long-stemmed pipe.\n");
	pipe_lit = 1;
	set_alarm(600.0, 0.0, "extinguish_pipe");
	return 1;
    }
    return 0;
}

int
smoke(string str)
{
    if(!str)
    {
	NF("Smoke what? Your pipe?\n");
	return 0;
    }

    if(str == "pipe" || str == "long-stemmed pipe")
    {
	if(pipe_filled == 0)
	{
	    write("You have no tabacco in your pipe!\n");
	    return 1;
	}
	if(pipe_lit == 0)
	{
	    write("Your pipe is not lit.\n");
	    return 1;
	}
	write("You puff contently on your long-stemmed pipe.\n");
	say(QCTNAME(TP)+ " puffs contently on " +HIS(TP)+
	  " long-stemmed pipe.\n");
	return 1;
    }
    return 0;
}

int
tap(string str)
{
    if(!str)
	return 0;

    if(str == "pipe" || str == "long-stemmed pipe")
    {
	if(pipe_lit == 1)
	{
	    write("You tap your smoking pipe absentmindedly " +
	      "with a gnarled finger.\n");
	    say(QCTNAME(TP)+ " taps " +HIS(TP)+ " smoking " +
	      "long-stemmed pipe absentmindedly with a " +
	      "gnarled finger.\n");
	    return 1;
	}
	if(pipe_filled == 1)
	{
	    write("You tap your unlit long-stemmed pipe " +
	      "thoughtfully, wondering how much tobacco is in there?\n");
	    say(QCTNAME(TP)+ " taps " +HIS(TP)+ " unlit long-stemmed " +
	      "pipe thoughtfully, as " +HE(TP)+ " wonders how much " +
	      "tobacco is left in it.\n");
	    return 1;
	}
	write("You tap your long-stemmed pipe on your palm, " +
	  "knocking all the ash out of it onto the ground.\n");
	say(QCTNAME(TP)+ " calmly taps " +HIS(TP)+
	  " long-stemmed pipe with " +HIS(TP)+ " palm, knocking ash " +
	  "from it onto the ground.\n");
	return 1;
    }
    return 0;
}
