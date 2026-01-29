inherit "/std/object";

#include <composite.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <language.h>
#include "/d/Shire/common/defs.h"
#include <options.h>

//   Prototypes
void
create_object() 
{
    set_name("sayer");
    set_short("sayer");
    set_no_show();
    add_prop(OBJ_M_NO_GIVE,1);
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_M_NO_STEAL,1);
}

void
init()
{
    ::init();
    add_action("my_say","ramble");
}

int
ramble_to(string str)
{
    object *oblist;
    object *live, *dead;
    string foo, object_name, comp_names;

    sscanf(str,"%s %s",object_name,foo);
    object_name = lower_case(object_name);
    if (object_name == this_player()->query_real_name() ||
      object_name == "me" || object_name == "myself")
    {
	if (this_player()->query_option(OPT_ECHO))
	{
	    write("You ramble to yourself: "+foo+"\n");
	}
	else
	{
	    write("Ok.\n");
	}
	say(QCTNAME(TP)+" rambles to "+HIM_HER(TP)+"self: "+foo+".\n");
	return 1;
    }
    if (environment(this_player())->item_id(object_name))
    {
	if (this_player()->query_option(OPT_ECHO))
	{
	    write("You ramble to the "+object_name+": " +foo+"\n");
	}
	else
	{
	    write("Ok.\n");
	}
	say(QCTNAME(TP)+" rambles to the "+object_name+": "+ foo +"\n");
	return 1;
    }
    if (!parse_command(str,environment(this_player()),
	"[the] %i %s", oblist, str))
    {
	return 0;
    }
    oblist = NORMAL_ACCESS(oblist,0,0) - ({this_player()});
    if (!sizeof(oblist) || !strlen(str))
    {
	return 0;
    }
    live = FILTER_LIVE(oblist);
    dead = FILTER_DEAD(oblist);
    if (sizeof(live)) // We rather talk to the living so we ignore the dead
    {
	comp_names = COMPOSITE_LIVE(live);
	if (this_player()->query_option(OPT_ECHO))
	{
	    write("You ramble to "+comp_names+": "+str+"\n");
	}
	else
	{
	    write("Ok.\n");
	}
	say(QCTNAME(TP)+" rambles to "+QCOMPLIVE+": "+str+"\n",(live + ({TP})));
	live->catch_msg(QCTNAME(TP)+" rambles to you: "+str+"\n");
	return 1;
    }
    else  // Must be dead objects
    {
	comp_names = COMPOSITE_DEAD(dead);
	if (this_player()->query_option(OPT_ECHO))
	{
	    write("You ramble to "+comp_names+": "+str+"\n");
	}
	else
	{
	    write("Ok.\n");
	}
	say(QCTNAME(TP)+" rambles to "+QCOMPDEAD+": "+str+"\n");
	return 1;
    }
}

int
my_say(string str)
{
    if (!str)
    {
	write("You ramble on about nothing in particular.\n");
	say(QCTNAME(TP)+" rambles on about nothing in particular.\n");
	return 1;
    }
    if (wildmatch("to *",str))
    {
	if (ramble_to(extract(str,3)))
	{
	    return 1;
	}
    }
    if (this_player()->query_option(OPT_ECHO))
	write("You ramble: "+str+"\n");
    else
	write("Ok.\n");
    say(QCTNAME(TP)+" rambles about: "+str+"\n");
    return 1;
}
