inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

int on_look;
int on_move;
string *gDirs;
mapping dir_short;

#define DIRS  ({ "north", "northeast", "east", "southeast", "south",\
		 "southwest", "west", "northwest" })
#define ADIRS (DIRS + ({ "up", "down" }))
#define SDIRS ({ "n","ne","e","se","s","sw","w","nw","u","d" })
#define EP environment(this_player())


void do_compass_look();

create_object()
{
    set_name("compass");
    set_short("compass");
    set_pshort("compasses");
    set_long(break_string(
	"You are looking at a strange instrument. It is obviously magical " +
	"because there are runes on it. You might want to read them.\n",60) +
	"@@check_updated@@");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_M_NO_DROP, 1);
    on_look = 0;
}

void
enter_env(object dest, object from)
{
    object *obs = all_inventory(dest);
    int i, change = 0;
    for(i=0;i<sizeof(obs);i++)
	if(obs[i]->id("compass") && obs[i]!=TO)
	{
	    obs[i]->remove_object();
	    change ++;
	}
    if(change)
	write("There can only be one compass. The other compasses shatters!\n");
}

string query_auto_load() { return MASTER_OB(this_object())+":"; }
void init_arg(string arg) { return; }

update_dirs()
{
    string dirstr, dummy;
    if(!EP) return;
    if(!EP->query_noshow_obvious())
	gDirs = EP->query_exit_cmds();
    else {
	sscanf(EP->long(), "%sobvious exit%s: %s.", dummy, dummy, dirstr);
	dirstr = implode( explode(dirstr,"\n"), " ");
	gDirs = explode(dirstr, ", ");
    }
    update_actions();
}

string
check_updated()
{
    update_dirs();
    return "";
}

mixed
short_of(string dir)
{
    int p=member_array(dir, ADIRS);
    if(p==-1)
	return 0;
    else
	return SDIRS[p];
}

init()
{
    int i;
    string t;

    ::init();
    add_action("read","read");
    add_action("compass","compass");
    if(on_look) {
	 add_action("look","look");
	 add_action("look","l");
    }
    if(on_move)
	for(i=0;i<sizeof(gDirs);i++) {
	     add_action("hook_move", gDirs[i]);
	     if(t=short_of(gDirs[i]))
		 add_action("hook_move", t);
	}
}

hook_move()
{
    set_alarm(1.0, 0.0, &do_compass_look());
    return 0;
}

look(string str)
{
    if(str) return 0;
    else if (on_look)
        set_alarm(0.0, 0.0, &do_compass_look());
}

compass(string str)
{
    if(str=="on") {
	on_look = 1;
	on_move = 1;
	write("Compass now shows on 'look' and moves.\n");
	update_dirs();
	return 1;
    } else if(str=="on look") {
	on_look = 1;
	write("Compass now shows on 'look'.\n");
	update_dirs();
	return 1;
    } else if(str=="on move"||str=="on moves") {
	on_move = 1;
	write("Compass now shows on moves.\n");
	update_dirs();
	return 1;
    } else if(str=="off look") {
	on_look = 0;
	write("Compass now does not show on 'look'.\n");
	update_dirs();
	return 1;
    } else if(str=="off move"||str=="off moves") {
	on_move = 0;
	write("Compass now does not show on moves.\n");
	update_dirs();
	return 1;
    } else if(str=="off") {
	on_look = 0;
	on_move = 0;
	write("Compass now off on 'look' and moves.\n");
	update_dirs();
	return 1;
    } else {
	write("Compass is now: "+
	      (on_look?"on":"off")+" 'look' and "+
	      (on_move?"on":"off")+" moves.\n");
	update_dirs();
	return 1;
    }
}

do_read()
{
    write(
	"The runes says:\n"+
	"\nThis is a tool to show you direction in a graphical manner.\n"+
	"Try to read the compass, and you'll see. The left part is the\n"+
	"horizontal directions and the right the vertical directions.\n"+
	"\nCommands:\n"+
	"  'compass on'      : Always read the compass.\n"+
	"  'compass on look' : Read compass on look.\n"+
	"  'compass on move' : Read compass on moves.\n"+
	"  'compass off'     : Stop reading the compass.\n"+
	"  'compass'         : Displayes the status.\n"+
	"  'read compass'    : Read the compass.\n"+
	"\nNOTE: If the compass stops for some reason, just write 'compass'.\n"+
	"\nPlease mail bugs/typos/ideas to Sir Rogon or some other wizard of the Shire.\n"
    );
}

int
filter_fun(string dir)
{
    return member_array(dir, DIRS ) != -1;
}

do_compass()
{
    int i;
    mapping m = ([  "north": 1, "northeast":2, "east":5, "southeast":8,
		    "south": 7, "southwest":6, "west":3, "northwest":0 ]);
    int *p = ({ 0,0,0, 0,1,0, 0,0,0 });
    string *o = ({ "\\", "|", "/", "-", "*", "-", "/", "|", "\\" });
    string *dirs;
    string res = "---------\n| ";

    update_dirs();

    if(!CAN_SEE_IN_ROOM(TP)) {
	write("It is to dark to see the compass.\n");
	return 1;
    }

    dirs = filter(gDirs, "filter_fun", this_object());

    for(i=0;i<sizeof(dirs);i++)
	p[ m[dirs[i]] ] = 1;

    for(i=0;i<9;i++)
    {
	res += (p[i] ? o[i] : " ");
	if(i%3==2) {
	    res += " ";
	    if(i/3==0) res += (member_array("up", gDirs)==-1 ? " " : "^");
	    if(i/3==1) res += "+";
	    if(i/3==2) res += (member_array("down", gDirs)==-1 ? " " : "v");
	    res += " |\n";
	    if(i/3!=2)
		res += "| ";
	}
    }
    res += "---------\n";
    write(res);
    return 1;
}

do_compass_look()
{
    write("\n");
    do_compass();
}

mixed
read(string str)
{
    if(str=="compass runes"||str=="runes on compass") {
	do_read();
	return 1;
    }
    else if(str=="runes") {
	write("Compass - Syntax is: read compass runes.\n");
	notify_fail("Read what?\n");
	return 0;
    }
    else if(str=="compass") {
	return do_compass();
    }
}
