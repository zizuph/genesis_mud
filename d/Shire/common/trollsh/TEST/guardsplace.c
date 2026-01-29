#include "/d/Shire/common/hollin/rom.h"
#include "/d/Shire/odin/abbrevs.h"
#include <macros.h>

#define MAX_SOLDIERS 6

object *guards;

create_rom()
{
    set_short("Guards hideout!");
    set_long(
	"This is not a place for you, but if you are here, you probably are a "+
	"wizard. Well, this is the room where the troll soldiers are generated. "+
	"A call to create_soldier() in this room generates a soldier, arms him and "+
	"after a while he travels to a random room. You can examine the panel "+
	"to find out where the soldiers are. You can _NOT_ in any way manipulate "+
	"the trolls."
    );
    add_item("panel","@@dump_guards");

    add_exit(TROLLSH_DIR + "trollsh15", "trollsh15");
    add_exit(TROLLSH_DIR + "sectunnel3","tunnels");
    add_exit(TROLLSH_DIR + "stunnel2",	"stunnel2");
    add_exit(TROLLSH_DIR + "trollsh9",	"trollsh9");
    add_exit(TROLLSH_DIR + "trollsh3",	"trollsh3");
    add_exit(TROLLSH_DIR + "trollsh12", "trollsh12");
}

init()
{
    ::init();
    add_action("stat", "stat");
    add_action("cbs",  "cbs");
    add_action("cbd",  "cbd");
}

string
create_soldier()
{
    int number=-1, i;
    object new;

    if(!guards)
	guards = allocate(MAX_SOLDIERS);

    for(i=0;i<MAX_SOLDIERS;i++)
	if(!guards[i])
	    number = i;

    if(number==-1)
	return "Sorry, there are already "+MAX_SOLDIERS+" soldiers out there.\n";

    new = clone_object("/d/Shire/common/trollsh/trollguard");
    if(!new)
	return "Sorry, error in compiling trollsoldier.c\n";

    guards[number] = new;
    new -> move(this_object(), 1);
    return "Watch out! Trollsoldier in the lair!!\n";
}

string
fname(object where)
{
    string r="Unknown position";
    sscanf(file_name(where), "/d/Shire/common/%s", r);
    return r;
}

string
dump_guards()
{
    int i;
    string s="The panel shows:\n";

    for(i=0;i<MAX_SOLDIERS;i++)
    {
	if(guards[i]) {
	    s += "#"+i+": "+guards[i]->short()+"   : #"+OB_NUM(guards[i])+"\n";
	    s += "  Location: "+fname(E(guards[i]))+"\n";
	    s += "  Enemies : "+sprintf("%@-11s\n", guards[i]->query_enemy(-1)->short());
	} else
	    s += "#"+i+": Not created.\n";
    }
    return s;
}

int
stat(string arg)
{
    int who;
    who = member_array(arg, ({"0","1","2","3","4","5"}) );
    if(who==-1)
	return 0;
    if(!guards[who])
	write("Status: Does not exist.\n");
    else
	write(guards[who]->stat_living());
    return 1;
}

int
cbs(string arg)
{
    int who;
    who = member_array(arg, ({"0","1","2","3","4","5"}) );
    if(who==-1)
	return 0;
    if(!guards[who])
	write("Status: Does not exist.\n");
    else
	write(guards[who]->combat_status());
    return 1;
}

int
cbd(string arg)
{
    int who;
    who = member_array(arg, ({"0","1","2","3","4","5"}) );
    if(who==-1)
	return 0;
    if(!guards[who])
	write("Status: Does not exist.\n");
    else
	write(guards[who]->combat_data());
    return 1;
}
