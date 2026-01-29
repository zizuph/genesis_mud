/*
* The Rich Men's Club
*
* Coded by Conan
* 
*/

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>

int acc;
mapping coated = ([ ]);
int res;

void
log_me()
{
    string *s,t;
    int i;

    t = "# Time for reset: " + extract(ctime(time()),4,15) + "\n";
    write_file(COAT_LOG, t);

    t = sprintf("%s%d%s","# Number of reset rooms passed: ",res,".\n");
    write_file(COAT_LOG, t);

    t = sprintf("%s%d%s","# Number of weapons registered in log: ",m_sizeof(coated),
		".\n");
    write_file(COAT_LOG, t);

    s = m_indexes(coated);
    write_file(COAT_LOG, "# Overnumbered weapons:\n");
    for (i = 0; i < sizeof(s); i++)
    {
	if (coated[s[i]] == 48)
	    write_file(COAT_LOG, "\t- "+s[i]+"\n");
    }
}

string
sign()
{
    return "\n"+
        "+----------------------------+\n"+
        "| $                        $ |\n"+
        "|       RICH MEN'S CLUB      |\n"+
        "|         BLACKSMITH         |\n"+
        "|                            |\n"+
        "| -------------------------- |\n"+
        "| We can coat you armours or |\n"+
        "|   weapons with gold. The   |\n"+
        "|  cost depends on how much  |\n"+
        "|     gold we have to use.   |\n"+
        "| -------------------------- |\n"+
        "| If you want some armour or |\n"+
        "| weapon coated. Type 'coat' |\n"+
        "|   and the thing you want   |\n"+
        "| to have the golden coating |\n"+
        "|   If you want to see how   |\n"+
        "|   much it will cost, type  |\n"+
        "|    'cost' and that item.   |\n"+
        "| $                        $ |\n"+
        "+----------------------------+\n\n"+
        "A small sign is beneath saying:\n"+
        "      We only take plats!\n\n";
}

void
reset_room()
{
    string ws;

    res++;

    if (res == 31 || m_sizeof(coated) > (100 + random(50)))
    {
	log_me();
	
	res = 0;
	coated = ([ ]);
	save_object(COAT_OBJ);
    }
}

void
check_room()
{
    string *s;
    int i;

    write("[COAT] Number of reset rooms passed: "+res+".\n");
    write("[COAT] Number of weapons registered in log: "+ m_sizeof(coated)+
	  ".\n");

    s = m_indexes(coated);
    write("[COAT] Overnumbered weapons:\n");
    for (i = 0; i < sizeof(s); i++)
    {
	if (coated[s[i]] == 48)
	    write("\t- "+s[i]+"\n");
    }
}

void
create_room()
{
    set_short("Small room on the third floor");
    set_long(break_string(
        "This is a quite small room on the third floor of the "+
        "Rich Men's Club. It is not as richly decorated as the "+
        "others and the heat in here is awesome. A stone table "+
        "has been placed in the middle of the room and on it, "+
        "blacksmith tools are spread out. Large plates of gold "+
        "lines the walls and on one wall there is a huge fire"+
        "place. A neat sign is hanging over it.\n",60));

    add_item("room","You're standing in it.\n");
    add_item("floor", "This is the third floor of the Rich Men's Club.\n");
    add_item("table", "It's a large table, sturdy enough to hit with "+
             "a blacksmith's hammer.\n");
    add_item("tools", "They are spread out on the table.\n");
    add_item(({"plate","plates"}), "The plates are made of very thin gold.\n");
    add_item(({"wall","walls"}), "The walls are gray and not very "+
    "decorated.\n");
    add_item("fireplace", "It is a large fireplace and inside it, a fire "+
             "sparkles and heats up the room.\n");
    add_item("sign", "There's some readable text on it.\n");
    add_cmd_item("sign", "read", "@@sign");

    INSIDE;
    LIGHT;

    add_exit(RICHCLUB + "richprivate3.c", "west", 0);

    restore_object(COAT_OBJ);
    reset_room();
}

void
init()
{
    ::init();

    add_action("cost", "cost");
    add_action("coat", "coat");
}

int
cost(string str)
{
    int c, v;
    object ob;

    FIXEUID;

    ob = present(str, TP);

    NF("You don't have a such thing!\n");
    if (!ob)
        return 0;

    if (coated[ob->short()] > 47)
    {
	if (ob->plural_short())
	    write("The blacksmith explains that he will not coat any "+
		  "more "+ob->plural_short()+".\n");
	else
	    write("The blacksmith explains that he will not coat any "+
		  "more "+ob->short()+"s.\n");

	return 1;
    }
    
    NF("It's not an armour or a weapon!\n");
    if (!(ob->query_ac) && !(ob->query_pen()))
        return 0;

    write("The blacksmith quickly estimates how much gold it will take to "+
          "coat this "+ob->short()+".\n");

    v = ob->query_prop(OBJ_I_VOLUME);
    c = v/1000;

    if (c == 0)
        c = 1;

    write("The blacksmith says: Coating the "+ob->short()+" will cost you "+c+
          " platinum coins.\n");

    return 1;
}

int
coat(string str)
{
    int c, v;
    object ob, mon;
    string sh, psh;
    string ws;

    FIXEUID;

    ob = present(str, TP);
    mon = present("platinum coin", TP);

    NF("You don't have a such thing!\n");
    if (!ob)
        return 0;

    NF("It's not an armour or a weapon!\n");
    if (!(ob->query_ac) && !(ob->query_pen()))
        return 0;

    NF("You can't coat already golden objects!\n");
    if (sizeof(FIND_STR_IN_OBJECT("gold", ob)))
        return 0;

    NF("It's already coated with gold!\n");
    if(ob->query_prop(RMC_I_GOLD_COATED))
        return 0;

    if (coated[ob->short()] > 47)
    {
	ws = "  - " + CQRLNAME(TP) + " tried to coat "+ob->short()+", but failed\t"+
	    extract(ctime(time()),4,15) + "\n";

	write_file(COAT_LOG, ws);

	if (ob->plural_short())
	    write("The blacksmith plainly refuses to do that. He is dead tired "+
		  "coating "+ob->plural_short()+"!\n");
	else
	    write("The blacksmith plainly refuses to do that. He is dead tired "+
		  "coating "+ob->short()+"s!\n");

	return 1;
    }
    
    v = ob->query_prop(OBJ_I_VOLUME);
    c = v/1000;

    if (c == 0)
        c = 1;

    NF("You don't have the money!\n");
    if(mon->num_heap()<c)
        return 0;

    sh = ob->short();
    psh = ob->plural_short();
  
    if (!psh)
        psh = sh + "s";

    write("The blacksmith quickly estimates how much gold it will take to "+
          "coat this "+sh+" and fetches a golden plate.  Expertly "+
          "he cuts the gold and coats the "+sh+" with it, and before you "+
          "know it, it is ready! He hands over your gold coated "+sh+
          " to you and you pay him gladly the "+c+" platinum coins.\n");

    if (coated[ob->short()])
	coated[ob->short()] = coated[ob->short()] + 1;
    else
	coated[ob->short()] = 1;
    
    ob->set_short("gold coated "+sh);
    ob->set_pshort("gold coated "+psh);
    ob->add_prop(RMC_I_GOLD_COATED, 1);
    mon->split_heap(c);
    mon->move(RMC_TREASURE_ROOM);
    (RICHROOM)->add_purchased(TP, c);
    
    acc += c;
    save_object(COAT_OBJ);

    return 1;
}
