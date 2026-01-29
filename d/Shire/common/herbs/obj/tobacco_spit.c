#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include "/d/Shire/sys/defs.h"

void
create_object()
{
    set_name("spit_obj");
    set_short("_shire_tobacco_spit");
    set_long("You should never see this.\n");
    set_no_show();
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_NO_DROP, 1);
    set_alarm(itof(200+random(100)),0.0,&remove_object());
}

void
init()
{
    ::init();
    add_action("do_spit","spit");
    add_action("do_chew","chew");
}

int
do_spit(string str)
{
    object *oblist;

    if (!str)
    {
	if (ENV(TP)->item_id("spittoon") || present("spittoon",ENV(TP)))
	{
	    if (!random(20))
	    {
		write("You attempt to spit some of your chewing tobacco into "+
		  "a nearby spittoon, but miss it entirely!\n");
		say(QCTNAME(TP)+" misses the spittoon with some of "+
		  HIS_HER(TP)+" chewing tobacco spit!\n");
	    }
	    else
	    {
		write("You skillfully spit some of your chewing tobacco "+
		  "into a nearby spittoon.\n\nTWANG!\n");
		say(QCTNAME(TP)+" skillfully spits some of "+HIS_HER(TP)+
		  " chewing tobacco into a nearby spittoon.\n\nTWANG!\n");
	    }
	}
	else
	{
	    write("You spit some of your chewing tobacco on the "+
	      (ENV(TP)->query_prop(ROOM_I_INSIDE) ? "floor" : "ground")+"!\n");
	    say(QCTNAME(TP)+" spits some of "+HIS_HER(TP)+" chewing "+
	      "tobacco on the "+
	      (ENV(TP)->query_prop(ROOM_I_INSIDE) ? "floor" : "ground")+"!\n");
	}
    }
    else
    {

	oblist = PARSE_THIS(str,"[at] %l");
	if (!sizeof(oblist))
	{
	    write("There is no "+str+" here to spit at.\n");
	    return 1;
	}
	if (sizeof(oblist) != 1)
	{
	    write("You can only spit at one person at a time!\n");
	    return 1;
	}
	TP->catch_msg("You spit some of your chewing tobacco on "+
	  QTNAME(oblist[0]) + "!\n");
	oblist[0]->catch_msg(QCTNAME(TP)+" spits some of "+HIS_HER(TP)+
	  " chewing tobacco on you!\n");
	say(QCTNAME(TP)+" spits some of "+HIS_HER(TP)+" chewing tobacco "+
	  "on "+QTNAME(oblist[0])+"!\n",({TP,oblist[0]}));
    }
    return 1;
}

int
do_chew(string str)
{
    if (!str)
    {
	write("You chew on your tobacco, in an attempt to gather some "+
	  "more flavour.\n");
	say(QCTNAME(TP)+" chews on "+HIS_HER(TP)+" chewing tobacco.\n");
	return 1;
    }
    notify_fail("Chew on what?\n");
    return 0;
}
