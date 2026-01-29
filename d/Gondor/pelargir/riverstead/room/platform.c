/*
 *  NCAMP_ROOM + "platform.c"
 *
 *  A watchtower. Only newbies and wizards should ever see this place.
 *
 *  Last modified by Alto, 16 November 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/lib/commands";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <math.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "../ncamp_defs.h"

inherit NCAMP_LIB + "ncamp_funcs.c";

#define WAS_PUSHED       	 "_was_pushed"
#define RIVERSTEAD_TOURING       "_riverstead_touring"
#define RIVERSTEAD_FOUND         "_riverstead_found"

public void        create_gondor();
public string      long_desc();
public int         exit_room();
public int         move_climber(object actor);
public int         jump_down(object actor);
public int	   push_down(string str);
public int	   move_pushed(object ob);
public int	   really_move_pushed(object ob);

static object *Man = allocate(4);
static object *Orc = allocate(4);

object             actor, *inv;

public void
create_gondor()
{
    set_short("On a platform atop the watchtower");
    set_long(&long_desc());

    add_item(({"room", "area", "surroundings", "place",
        "watchtower", "tower", "building", "platform"}), long_desc);
        
    add_item(({"wood"}), "The platform, like almost everything else "
        + "in the settlement, is made from rough-cut timber.\n");
    add_item(({"board", "boards", "timber", "rough-cut timber"}),
        "The floor of the platform is made from crudely milled boards "
        + "produced from the wooodland growing about the settlement.\n");
    add_item(({"ladder", "narrow ladder"}), "You can see the ladder "
        + "through the hole in the floor. The top of it is too far "
        + "down to reach.\n");
    add_item(({"settlement", "village", "huts", "town"}), "The settlement "
        + "spreads out in all directions about the tower. You see many "
        + "huts, but notice the ones to the east are almost all on fire!\n");
    add_item(({"ground", "floor"}), "The floor of the platform is made "
        + "of wood. The ground below the tower is far below. It seems the "
        + "only way to reach it would be to leap over the edge.\n");
    add_item(({"hole", "hole in the platform"}), "Below you is a hole "
        + "in the middle of the platform. Although you came up that way "
        + "it seems very doubtful you could return through it. The ladder "
        + "is simply too far below.\n");
    add_item(({"edge", "edge of the platform"}), "You examine the edge "
        + "of the platform. It is quite high above the ground. Leaping "
        + "over it probably will not kill you, but it might hurt.\n");

    add_cmd_item(({"ground", "to ground", "edge", "to the ground",
        "over the edge", "over edge"}), "leap", &exit_room());

    add_prop(ROOM_I_INSIDE, 1);
    defence_status = 1;

    reset_room();
}

public void
reset_room()
{
    if(defence_status)
    {
        clone_npcs(Man, NCAMP_NPC + "tower_human", -1.0);
        return;
    }

    clone_npcs(Orc, NCAMP_NPC + "tower_orc", -1.0);
}

string
long_desc()
{

    return "You are standing on a wide platform made of wood, overlooking "
        + "the settlement. Be careful! You could be pushed over the edge "
        + "quite easily. On the other hand, you could also push someone "
        + "else over if you had a mind to do so. In fact, the only "
        + "way down appears to be leaping over the edge! The narrow "
        + "ladder is too far below to make use of.\n";
}

int
jump_down(object actor)
{
    set_alarm(0.0, 0.0, &actor->catch_tell("You peer nervously over the edge.\n"));
    set_alarm(0.5, 0.0, &actor->catch_tell("Putting your better judgement aside, "
        + "you leap for the ground!\n"));

    tell_room(environment(actor), QCTNAME(actor) + " peers "
        + "nervously over the edge of the platform.\n", 
        ({actor}));
    set_alarm(0.5, 0.0, &tell_room(environment(actor), QCTNAME(actor) +
        " suddenly leaps out into thin air!\n", ({actor})));

    return 1;
}


int
exit_room()
{
    object actor = this_player();

    jump_down(actor);
    set_alarm(1.0, 0.0, &move_climber(actor));        
    return 1;
}

int
really_move_climber(object actor)
{
    actor->move_living("M", NCAMP_ROOM + "camp7", 1, 0);
    set_alarm(0.5, 0.0, &actor->catch_tell("Luckily you land on your feet, but "
        + "you lose your balance and roll through the mud!\n"));
    return 1;
}



int
move_climber(object actor)
{
    say(QCTNAME(actor) + " plummets quickly out of sight.\n");
    tell_room(NCAMP_ROOM + "camp7", QCNAME(actor) + " falls to the "
        + "ground and rolls through the mud.\n");

    set_alarm(1.0, 0.0, &really_move_climber(actor));
    return 1;
}

public int
push_down(string str)
{
    object *oblist;
    object victim;
    actor = TP;
    
        if (!strlen(str))
    {
         NFN0("Who did you want to push?");
    }

    oblist = parse_this(str, "[the] %l", ACTION_PROXIMATE);
    
    if (!sizeof(oblist))
    {
        oblist = parse_this(str, "[the] %i", ACTION_PROXIMATE);
    }
    
    switch(sizeof(oblist))
    {
    case 0:
        NFN0("There is nobody here of that description to push!");
        return 0;
    case 1:
        break;
    default:
        NFN0("You can only push one person at a time!");
        return 0;
    }
    
    victim = oblist[0];  
    
    if (!victim->query_hp())
    {
        NFN0("That doesn't seem like an appropriate thing to push!");
        return 0;
    }

    if (victim->query_prop(WAS_PUSHED))
    {
        NFN0("That person is already on the way over the edge!");
        return 0;
    }
    
    actor->catch_tell("You start pushing people around!\n");
    tell_room(environment(actor), QCTNAME(actor) + " starts "
        + "pushing people around!\n", 
        ({actor}));

    victim->add_prop(WAS_PUSHED, 1);
    set_alarm(1.0, 0.0, &move_pushed(victim));

    return 1;
}

int
move_pushed(object ob)
{
    ob->catch_tell("You are pushed over the edge!\n");
    tell_room(environment(ob), QCTNAME(ob) + " is pushed over the "
        + "edge of the platform!\n", 
        ({ob}));
    tell_room(NCAMP_ROOM + "camp7", QCNAME(ob) + " falls from the sky "
        + "and lands with a painful crunch. Ouch!\n");

    set_alarm(1.0, 0.0, &really_move_pushed(ob));
    return 1;
}

int
really_move_pushed(object ob)
{
    int healed, int_health, hurt;

    actor = ob;
    healed = ob->query_hp();
    int_health = healed / 2;
    hurt = healed - int_health;

    if (ob->query_npc())
    {
        ob->set_hp(1);
    }
    else
    {
        ob->set_hp(hurt);
        ob->catch_tell("You fall backwards over the edge and hit the "
            + "ground with a very painful thud!\n");
    }
        
    ob->remove_prop(WAS_PUSHED);
    ob->move_living("M", NCAMP_ROOM + "camp7", 1, 0);
    return 1;
}


void
init()
{
    ::init();
    add_action("push_down", "push");
}

public void
check_tour(object player)
{
    if (player->test_bit("gondor", RIVERSTEAD_TOUR_GROUP, RIVERSTEAD_TOUR_BIT))
        return;

    if (player->query_prop(RIVERSTEAD_FOUND))
        return;
        
    if (player->query_prop(RIVERSTEAD_TOURING))
        {
            player->catch_tell("\n\nFrom here you can see the extent of the "
                + "orc invasion. It would be wise to return and inform Grub "
                + "the farm boy as soon as possible. Remember to ask him for "
                + "your reward!\n\n");
            player->add_prop(RIVERSTEAD_FOUND, 1);
        }
    return;
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        set_alarm(1.0, 0.0, &check_tour(ob));
}


