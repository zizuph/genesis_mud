#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <language.h>

inherit CITY_OUT;
object p1, *g;

void
clone_elite_guard(int i, object enemy)
{
    g[i] = clone_object(KNPC + "elite_guard");
    g[i]->arm_me();
    if (i)
	g[0]->team_join(g[i]);
    g[i]->move(TO,1);
    if (objectp(enemy) && E(enemy) == TO)
	g[i]->command("kill " +OB_NAME(enemy));
}

void
princess_attacked(object ob)
{
    int i;

    if (!objectp(p1))
	return;

    g = allocate(5+random(5));

    for (i=0; i<sizeof(g); i++)
    {
	switch (i)
	{
	case 0:
	    tell_room(TO,"An elite guard rushes from the palace!\n");
	    clone_elite_guard(i, ob);
	    g[i]->command("shout The princess! She is under attack!");
	    break;
	case 1:
	    tell_room(TO,"An elite guard charges from the palace!\n");
	    clone_elite_guard(i, ob);
	    g[i]->command("shout My life for the princess!");
	    break;
	case 2:
	    tell_room(TO,"An elite guard rushes from between some trees.\n");
	    clone_elite_guard(i, ob);
	    g[i]->command("shout To arms! Enemy in the palace grounds!");
	    break;
	case 3:
	    if (sizeof(g) == 5)
		tell_room(TO,"A pair of elite guards charge from the palace!\n");
	    else
		tell_room(TO,C(LANG_WNUM((sizeof(g)-3)))+
				" elite guards charge from the palace!\n");
	    clone_elite_guard(i, ob);
	    g[i]->command("shout Princess! Flee to the palace!");
	    tell_room(TO,"The princess flees into the palace.\n");
	    p1->remove_object();
	    break;
	default:
	    // we use alarm to prevent too long evaluation runtime error
	    // when cloning too many guards
	    // Milan
	    set_alarm(0.0, 0.0, &clone_elite_guard(i, ob));
	}
    }
}

void
reset_kalaman_room()
{
    int i;
    object *o = all_inventory(TO);

    if (sizeof(FILTER_PLAYERS(o)))
	return;

    for (i=0; i<sizeof(o); i++)
	o[i]->remove_object();

    if (!objectp(p1))
    {
	p1 = clone_object(KNPC + "princess");
	p1->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("A luxurious garden in the palace grounds");

    add_item(({"garden","luxurious garden","palace grounds"}),
      "@@long_descr");
    add_item("palace","To your north rises the great palace of Kalaman.\n");
    add_item(({"lush green grass","green grass","grass","ground"}),
      "Lush green grass covers the ground like a blanket. It looks " +
      "well maintained.\n");
    add_item(({"neatly trimmed trees","trees","tree"}),
      "Neatly trimmed trees are scattered throughout the " +
      "garden, offering shade to those who would rest here.\n");
    add_item(({"wall","walls"}),
      "To your south is a high wall that seperates the city from " +
      "the palace grounds. Creepers have been allowed to grow " +
      "up the side of the wall here.\n");
    add_item("creepers","Creepers have been allowed to grow " +
      "up the side of the wall to the south. You could probably " +
      "climb them.\n");

    add_cmd_item(({"wall","creepers"}),"climb","@@climb_wall");

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand in a luxurious garden at the back " +
    "of the palace. Lush green grass covers the ground " +
    "around you like a blanket, and a few neatly trimmed trees offer shade " +
    "to those who walk this garden. " +tod_descr1() +
    "A wall to the south separates the palace grounds " +
    "from the city beyond" +
    ".\n";
}

string
climb_wall()
{

    if(TP->query_attack())
    {
	write("You can't climb the wall while in battle!\n");
	return "";
    }
    write("You climb the creepers over the wall.\n");
    say(QCTNAME(TP) + " climbs the wall to the south.\n");
    tell_room(CITY + "r16",QCTNAME(TP)+ " leaps down " +
      "off the palace wall to the north.\n", 0);

    TP->move_living("M",CITY + "r16",1,0);
    return "";
}

