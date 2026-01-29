#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "local.h"
#include <composite.h>
#include <filter_funs.h>

inherit EAST_ROAD;
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "w";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

#define MAX_RABBITS 1
#define RABBIT      "/d/Gondor/common/npc/rabbit"
#define TREETOP     "/d/Shire/bree/rooms/road/treetop"

static object *rabbit = allocate(MAX_RABBITS);



void
create_er_room()
{
   area = "close to";
   areaname = "the Great East Road";
   land = "Eriador";
   areatype = 1;
   areadesc = "field";
   grass = "green";
   
   extraline = "You are standing at the foot of many hills. "+
     "The hills go on for miles to the north. South of you is "+
       "the Great East Road. While to the west you see more hills. ";
   
   add_item(({"surroundings","expanse","fields","shire"}),
	    
	    "The hills stretch out to the north and west. To the south of "+
	    "you runs the Great East Road.\n");
   
   add_item(({"hills","hill",}),
	    "The hills themselves, while steep, look very rich and full "+
	    "of life.\n");

    add_item(({"bushes", "shrubs"}),
        "The bushes and shrubs grow across the hills. They are healthy " +
        "and different sizes. Some are even large enough to hide a hobbit. " +
        "@@bushes_descr@@\n");

   reset_shire_room();
   
   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er29","south", "@@tree_south@@", 0,2);
   add_exit(EAST_R_DIR + "er28n","west", "@@tree_west@@", 0,2);   
}

public void
enter_inv(object ob, object from)
{
	string *names;
	::enter_inv(ob, from);
	names = ob->query_names();
	if(ob->id(npc_name))
	{
		if (!move_alarm || !sizeof(get_alarm(move_alarm)))
		{
			move_alarm = set_alarm(50.0 + rnd() * 20.0, 0.0, &move_patrol(ob));
		}
	return;
	}
}

public void
init()
{
    ::init();
    add_action("enter_bushes", "enter");

}

void reset_shire_room()
{
    int index;

    setuid();
    seteuid(getuid());

    for(index = 0; index < MAX_RABBITS; index++)
    {
        if (!objectp(rabbit[index]))
        {
            rabbit[index] = clone_object(RABBIT);
            rabbit[index]->set_random_move(3);
            rabbit[index]->move(TO);
        }
    }
}


string bushes_descr(string str)
{
        if (R_ALLOWED || this_player()->query_wiz_level())
            return "Hidden within the bushes is path that leads into " +
            "them so you may go into them.";
        else
            return "";
}


int enter_bushes(string str)
{

    if (R_ALLOWED || this_player()->query_wiz_level())
    {    
        if(!str)
        {
            write("Enter what?\n");
            return 1;
        }

        if(str =="bushes")
        {
            write("You disappear from the field and into the bushes.\n");
            TP->move_living("M","/d/Shire/bree/rooms/road/treetop_glade", 1);
            tell_room("treetop.c", QCTNAME(TP) + 
            " went east into the bushes.\n");
            tell_room(ENV(TP), QCTNAME(TP) + " arrives from the field.\n",TP);
            return 1;
        }
        else 
        {
            write("Enter what?\n");
            return 1;
        }
    }    
}


string ranger_descr()
{
    if (R_ALLOWED || this_player()->query_wiz_level())

        return "One tree near the road looks larger than the others. Bushes " +
            "grow around it, hiding a way behind the tree.";
    else
        return "";

}

string
tree_top_descr()
{
    object other_room;
    mixed opeople;
 
    if (!LOAD_ERR(TREETOP))
        other_room = find_object(TREETOP);
    else
        return "Some sort of magic is plaguing the treetop. Contact " +
            "a Shire wizard.";
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        return " No one is visible in the large tree.";
    else
        return " Up in the tree, you see hidden "+COMPOSITE_LIVE(opeople)+
            " watching your every move.";
}


void tree_south()
{
    tell_tree("went south to the Great East Road.\n");
    tell_tree_fort("went south to the Great East Road.\n");
}


void tree_west()
{
    tell_tree("stayed in the field and went west.\n");
    tell_tree_fort("stayed in the field and went west.\n");
}
