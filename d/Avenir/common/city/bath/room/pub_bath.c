#pragma strict_types
/*
 * ~/pub_bath.c
 *
 * Bath House Public Pool
 *
 * Revisions:
 *   Grace,  Feb 1994: Created.
 *   Grace,  Aug 1994: ?
 *   Lucius, Oct 2008: Cleanup.
 *   Lucius, Aug 2016: Recoded baths.
 *
 */
#include "../bath.h"
#include <macros.h>

inherit BATH_ROOM;
inherit "/lib/commands";

static void
create_bath_room(void)
{
    set_short("Public Bath");
    set_long("Warm and perfumed with oils, the water's silken "+
	"caress is reminiscent of a lover's embrace. Smooth stones "+
	"beneath your feet radiate a soothing warmth. At the center "+
	"of the pool is a simple fountain from which water falls. "+
	"Steam rises from the pool's surface, obscuring your vision.\n"); 

    add_item(({"column", "columns", "pedestal", "arch", "ceiling"}),
	"The mist obscures it from your sight.\n");
    add_item("pool", "You are unable to determine its size from here.\n");
    add_item("stones", "They are white and octagonal in shape.\n");
    add_item("water", "It is surprisingly clear and quite warm.\n");
    add_item(({"fountain", "simple fountain"}),
	"It is a simple stone fountain. Water falls from its tiers, "+
	"creating restful tinkling sounds.\n");

    add_cmd_item("water", "drink",
	"It is warm and tastes of minerals and sulphur.\n");

    MIST;

    add_exit(BATHRM + "steps_s", "south");
    add_exit(BATHRM + "steps_n", "north");

    add_npc(MON  + "dej-minha4", 1, &->equip_me());
    add_npc(BATH + "npc/attendant", 1, &->equip_me());
    add_npc(BATH + "npc/noble_galerin", 1, &->equip_me());
}

public int
do_swim(void)
{
    write("You swim around the pool at a languid pace.\n");
    say(QCTNAME(this_player()) + " swims lazily around the pool.\n");
    return 1;
}

public int
do_wash(void)
{
    object ob;

    write("You wash away the marks of battle and travel.\n");
    say(QCTNAME(this_player()) + " washes away layers of dirt and grime.\n");

    while(ob = present("dirty", this_player()))
    {
	write("You feel much less dirty now.\n");
	ob->remove_object();
    }

    return 1;
}

public int
do_splash(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You splash playfully in the water, feeling "
	  +"like a child again.\n");
	all(" splashes noisily about in the pool.\n");
	return 1;
    }

    oblist = parse_this(str, "[water] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Splash who?\n");
	return 0;         
    }

    target(" splashes water in your face.", oblist);
    actor("You splash", oblist, " in the face with water.");
    all2act(" splashes", oblist, " in the face with water.");
    return 1;
}

public int
do_paddle(void)
{
    write("You skillfully tread water.\n");
    say(QCTNAME(this_player()) +
	" looks like a dog paddling about in the pool.\n");
    return 1;
}

public int
do_dead(void)
{
    write("Rolling onto your back, you float contentedly in the water.\n");
    say(QCTNAME(this_player()) + " floats on the surface of the water.\n");
    return 1;
}

public int
do_dive(void)
{
    write("You dive under the water.\n");
    say(QCTNAME(this_player()) +
	" disappears beneath the water's surface.\n");
    return 1;
}

public int
do_dunk(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You dunk beneath the water. You can hear "
	  +"the sound of water lapping the pool's edge.\n");
	all(" dunks beneath the pool's surface.\n");
	return 1;
    }

    oblist = parse_this(str, "[beneath] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Dunk who?\n");
	return 0;
    }

    target(" dunks your head beneath the water.", oblist);
    actor("You dunk", oblist, " underneath the water.");
    all2act(" dunks", oblist, " under the water.");
    return 1;
}

public void 
init(void) 
{
    ::init();

    add_action(do_swim, "swim");
    add_action(do_wash, "wash");
    add_action(do_wash, "bathe");
    add_action(do_splash, "splash");
    add_action(do_paddle, "paddle");
    add_action(do_paddle, "tread");
    add_action(do_dead, "float");
    add_action(do_dive, "dive");
    add_action(do_dunk, "dunk");
}
