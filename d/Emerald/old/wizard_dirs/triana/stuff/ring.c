/* A ring to help change directories
* i got sick of long path names!
* any suggestions can be mailed to triana
*/
inherit "/std/armour";
#include "/sys/macros.h"
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Avenir/common/common.h"

void
create_armour()
{
	set_name("wedding ring");
	add_name("ring");
	add_name("gold ring");
	add_name("white gold ring");
	set_short("white gold wedding ring");
	set_long("A small ring. For help help aid.\n");

	add_prop(OBJ_I_NO_DROP, 1);
	add_prop(OBJ_M_NO_DROP, 1);
	add_prop(OBJ_I_NO_STEAL, 1);
	add_prop(OBJ_M_NO_STEAL, 1);
	add_prop(OBJ_I_WEIGHT, 0);
	add_prop(OBJ_I_VALUE, 0);
	
	add_cmd_item("aid", "help",
"Here is what the ring can help you do \n" +
" \n" +
	"	light		turn ring's light on \n" +
	"	extinguish	turn ring's light off \n" +
	"	reader		turn mail reader on or off \n" +
	"	tailem		tail ~Emerald/log \n" +
	"	tailp		tail ~/lplog \n" +
	"	tlog		tail ~triana/errors/log \n" + 
	"	reader		turnmail reader on or off \n" +
	"	vol		turn to emerald volcano directory \n" +
	"	vnpc		turn to emerald volcano npc directory \n" +
	"	vobj		turn to emerald volcano obj directory \n" +
	"	priv		turn to prive dir \n" +
	"	stuff		turn to stuff dir \n" +
	"	study		turn to study ri \n" +
	"	maps		turn to map dir \n"+
	"\n");
	set_am(({0, 0, 0}));
	set_ac(3);
	set_at(A_ANY_FINGER);
}

init()
{
	::init();
	add_action("light_ring", "light");
	add_action("extinguish_ring", "extinguish");
	add_action("reader", "reader");
	add_action("vol", "vol");
	add_action("vnpc", "vnpc");
	add_action("vobj", "vobj");
	add_action("tailp", "tailp");
	add_action("tlog", "tlog");
	add_action("tailem", "tailem");
	add_action("stuff",  "stuff");
	add_action("study", "study");
	add_action("maps", "maps");
	add_action("priv", "priv");
}

int
light_ring()
{
	add_prop(OBJ_I_LIGHT, 10);
	write("The ring starts to glow, creating a soft light\n");
	say(QCTNAME(this_player()) + "mumbles some soft words and is surrounded by light.\n");
return 1;
}

int
extinguish_ring()
{
	write("The light of the ring slowly fades away.\n");
	say(QCTNAME(this_player()) + "mumbles soft words and the light surrounding her dims.\n");
	add_prop(OBJ_I_LIGHT, 0);
	return 1;
}

reader()
{
	object ob;
	int i;

	ob = deep_inventory(this_player());
	for (i=0; i <sizeof(ob);i++)
	{
		if (ob[i]->id("mailreader"))
		{
			"secure/master"->do_debug("destroy",ob[i]);
		write("MAil readeing is now off.\n");
		return 1;
			}
		}
	ob = clone_object("/secure/mail_reader.c");
	ob->move(this_player());
	write("Mail reading is now on. \n");
	return 1;
}

vol()
{
	this_player()->set_path("/d/Emerald/mountains/volcano");
	write(this_player()->query_path() + " \n");
	ls(this_player()->query_path(),"F");
	return 1;
}

vobj()
{
	this_player()->set_path("/d/Emerald/mountains/volcano/obj");
	write(this_player()->query_path() + " \n");
	ls(this_player()->query_path(),"F");
	return 1;
}

vnpc()
{
	this_player()->set_path("/d/Emerald/mountains/volcano/npc");
	write(this_player()->query_path() + " \n");
	ls(this_player()->query_path(),"F");
	return 1;
}
	
maps()
{
	this_player()->set_path("/d/Wiz/triana/maps");
	write(this_player()->query_path() + "\n");
	ls(this_player()->query_path(),"F");
	return 1;
}

stuff()
{
	this_player()->set_path("/d/Wiz/triana/stuff");
	write(this_player()->query_path() + "\n");
	ls(this_player()->query_path(),"F");
	return 1;
}

study()
{
	this_player()->set_path("/d/Wiz/triana/study");
	write(this_player()->query_path() + "\n");
	ls(this_player()->query_path(),"F");
	return 1;
}
priv()
{
	this_player()->set_path("/d/Wiz/triana/private");
	write(this_player()->query_path() + "\n");
	ls(this_player()->query_path(),"F");
	return 1;
}


tailem()
{
	tail("/d/Emerald/log/errors");
	return 1;
}

tailp()
{
	tail("/lplog");
	return 1;
}

tlog()
{
	tail("/d/Emerald/triana/log/errors");
	return 1;
}

string query_auto_load()
{
	return MASTER;
}

