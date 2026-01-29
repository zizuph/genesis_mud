#include "rom.h"
#include "abbrevs.h"
#include <macros.h>

#define MAX_SOLDIERS 5

object *soldiers;

create_rom()
{
    set_short("Trolls lair!");
    set_long(
	"This is not a place for you, but if you are here, you probably are a "+
	"wizard. Well, this is the room where the troll soldiers are generated. "+
	"A call to create_soldier() in this room generates a soldier, arms him and "+
	"after a while he travels to a random room. You can examine the panel "+
"to find out where the soldiers are. Updating this room in any way "+
"is not legal, and will be punished by an arch wizard or the Lord of the "+
"Shire.");
    add_item("panel","@@dump_soldiers");
    create_soldier();
     enable_reset();
       add_exit(STAND_DIR+"plain_s", "north");
       add_exit(STAND_DIR+"f0101",    "south");
       add_exit(STAND_DIR+"rom1",     "east");
       add_exit(STAND_DIR+"rom5",     "west");
       add_exit(STAND_DIR+"tree_n",   "southwest");
}


init()
{
    ::init();
    add_action("stat", "stat");
    add_action("cbs",  "cbs");
    add_action("cbd",  "cbd");
    add_action("move","move");
}

string
create_soldier()
{
    int ran;
    int number=-1, i;
    object new;

    if(!soldiers)
	soldiers = allocate(MAX_SOLDIERS);

    for(i=0;i<MAX_SOLDIERS;i++)
	if(!soldiers[i])
	    number = i;

    if(number==-1)
	return "Sorry, there are already "+MAX_SOLDIERS+" soldiers out there.\n";

    new = clone_object(STAND_MONSTER+"trollsoldier");
	new->arm_me();
    if(!new)
	return "Sorry, error in compiling trollsoldier.c\n";

    soldiers[number] = new;
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
dump_soldiers()
{
    int i;
    string s="The panel shows:\n";

    for(i=0;i<MAX_SOLDIERS;i++)
    {
	if(soldiers[i]) {
	    s += "#"+i+": "+soldiers[i]->short()+"   : #"+OB_NUM(soldiers[i])+"\n";
	    s += "  Location: "+fname(E(soldiers[i]))+"\n";
	    s += "  Enemies : "+sprintf("%@-11s\n", soldiers[i]->query_enemy(-1)->short());
	} else
	    s += "#"+i+": Not created.\n";
    }
    return s;
}

int
stat(string arg)
{
    int who;
    who = member_array(arg, ({"0","1","2","3","4"}) );
    if(who==-1)
	return 0;
    if(!soldiers[who])
	write("Status: Does not exist.\n");
    else
	write(soldiers[who]->stat_living());
    return 1;
}

int
cbs(string arg)
{
    int who;
    who = member_array(arg, ({"0","1","2","3","4"}) );
    if(who==-1)
	return 0;
    if(!soldiers[who])
	write("Status: Does not exist.\n");
    else
	write(soldiers[who]->combat_status());
    return 1;
}

int
cbd(string arg)
{
    int who;
    who = member_array(arg, ({"0","1","2","3","4"}) );
    if(who==-1)
	return 0;
    if(!soldiers[who])
	write("Status: Does not exist.\n");
    else
	write(soldiers[who]->combat_data());
    return 1;
}

string
destruct_soldiers()
{
    int i;
    soldiers = soldiers - ({ 0 });
    for(i=0;i<sizeof(soldiers);i++)
	soldiers[i]->remove_object();
    return "All removed.\n";
}

