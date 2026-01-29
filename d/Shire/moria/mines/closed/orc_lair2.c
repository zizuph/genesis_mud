#include "defs.h"
#include <macros.h>

#define MAX_SOLDIERS 25
#define PROMPT       "PANEL> "

object captain;
object *soldiers;

CONSTRUCT_ROOM
{
    set_short("Orc lair!");
    set_long(
	"This is not a place for you, but if you are here, you probably are a "+
	"wizard. Well, this is the room where the orc soldiers are generated. "+
	"A call to create_soldier() in this room generates a soldier, arms him and "+
	"after a while he travels to a random room. You can examine the panel "+
	"to find out where the soldiers are. You might also push button to "+
	"generate one. If you <wipe panel>, they will be destroyed."
    );
    add_item("panel","@@dump_soldiers@@");
    add_call(({ "press", "push" }), "[the] 'button'", "create_soldier");
    add_call(({ "wipe", "clean", "dest" }), "'panel' / 'soldiers' / 'orcs'",
	"destruct_soldier");
    add_call(({ "press", "push" }), "[the] 'red' [button]",
        "start_captain");
    add_call(({ "wipe", "clean", "dest" }), "'captain'",
	"destruct_captain");
    add_call("stat", 0, "stat");
    add_call("cbs", 0, "cbs");
    add_call("cbd", 0, "cbd");
    add_call(({"skills", "skillstat"}), 0, "skillstat");

    add_exit(THIS_DIR+"corr3", "north");
    add_exit(THIS_DIR+"gallery",	  "northeast");
    add_exit(THIS_DIR+"bigrw",  "nortwest");
    add_exit(THIS_DIR+"rattrap", "south");
    add_exit(THIS_DIR+"exit2", "southwest");
    add_exit(THIS_DIR+"corridor",   "down");
    add_exit(THIS_DIR+"mining/mining.3", "southeast");
    add_exit(THIS_DIR+"big_hall",	  "east");

    add_exit("/d/Immortal/rogon/workroom", "west", "@@chk_npc@@");
   "/d/Shire/moria/mines/team7"->teleledningsanka();
   "/d/Shire/moria/mines/team8"->teleledningsanka();
   "/d/Shire/moria/mines/team9"->teleledningsanka();
   "/d/Shire/moria/mines/team10"->teleledningsanka();
   add_prop(ROOM_I_LIGHT, 1);
}

int
chk_npc()
{
    if (TP->query_npc())
	return 1;
    return 0;
}

string
create_soldier()
{
    int number=-1, i;
    object new;

    if (!soldiers)
	soldiers = allocate(MAX_SOLDIERS);

    for(i=0;i<MAX_SOLDIERS;i++)
	if (!soldiers[i])
	    number = i;

    if (number==-1)
	return "Sorry, there are already "+MAX_SOLDIERS+" soldiers out there.\n";

    new = clone_object(MORIA_NPC+"cavetroll");
    if (!new)
	return "Sorry, error in compiling moriaorc.c\n";

    new -> create_troll_soldier(number);
    soldiers[number] = new;
   new->set_random_move(6);
    new -> move(this_object(), 1);
    return "Watch out! Trollsoldier in the lair!!\n";
}

string
start_captain()
{
    if (living(captain))
	return 
	    "The Captain is living and well..\n"+
	    "Bolg is lurking in: " + file_name(ENV(captain));

    captain = clone_object(MORIA_NPC + "urukcap");
    captain -> move(this_object(), 1);
    return "Captain created!!";
}

string
destruct_captain()
{
    if (!captain || !living(captain))
	return "Captain lost.\n";

    captain->remove_object();
    return "Captain removed.\n";
}

string
fname(object where)
{
    string r="Unknown position";
    if (sscanf(file_name(where), THIS_DIR + "%s", r))
	return r;
    if (sscanf(file_name(where), "/d/%s", r))
	return r;
    if (stringp(file_name(where)))
	return file_name(where);
    else
	return "Lost in void.";
}

string
dump_soldiers()
{
    int i;
    string s="The panel shows:\n";
    string str;
    object *en;

    if (soldiers) for(i=0;i<MAX_SOLDIERS;i++)
    {
	if (soldiers[i]) {
	    en = soldiers[i]->query_enemy(-1);
	    s += sprintf(
		    "%2d: %-10s #%-6s F:%-10s",
		    i,
		    (string)soldiers[i]->query_name(),
		    OB_NUM(soldiers[i]),
		    fname(ENV(soldiers[i]))
		);

	    if (sizeof(en))
		s += sprintf("E: %@-11s", en->query_name());

	    s+="\n";
	}
    }
    else s="* No orc soldiers created!\n";

    if (living(captain))
    {
	en = captain->query_enemy(-1);
	s += sprintf(
		"CAPTAIN: %-10s ", fname(ENV(captain)));
	if (sizeof(en))
	    s += sprintf("E: %@-11s", en->query_name());

	s += "\n";
    }

    return s;
}

int
skills(string arg)
{
    int who;
    if (!strlen(arg))
	return 0;
    if (sscanf(arg,"%d",who)!=1)
	return 0;
    if (who<0||who>MAX_SOLDIERS)
	return 0;
    if (!soldiers[who])
	write("Status: Does not exist.\n");
    else
	TP->command("skillstat "+file_name(soldiers[who]));
    return 1;
}

int
stat(string arg)
{
    int who;
    if (!strlen(arg))
	return 0;
     if (sscanf(arg,"%d",who)!=1)
	return 0;
    if (who<0||who>MAX_SOLDIERS)
	return 0;
    if (!soldiers[who])
	write("Status: Does not exist.\n");
    else
	write(soldiers[who]->stat_living());
    return 1;
}

int
cbs(string arg)
{
    int who;
    if (!strlen(arg))
	return 0;
    if (sscanf(arg,"%d",who)!=1)
	return 0;
    if (who<0||who>MAX_SOLDIERS)
	return 0;
    if (!soldiers[who])
	write("Status: Does not exist.\n");
    else
	write(soldiers[who]->combat_status());
    return 1;
}

int
cbd(string arg)
{
    int who;
    if (!strlen(arg))
	return 0;
    if (sscanf(arg, "%d", who) != 1)
	return 0;
    if (who<0 || who>MAX_SOLDIERS)
	return 0;
    if (!soldiers[who])
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
