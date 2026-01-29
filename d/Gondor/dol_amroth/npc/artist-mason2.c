/* -*- Mode: C -*-
 *
 * npc/artist-mason.c
 *
 * By Skippern 20(c)01
 *
 * A mason that is going to be hammering on a marble block on a pier.
 */
inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";

#include "../defs.h"
#include <const.h>
#include <files.h>
#include <macros.h>
#include <ss_types.h>

/* Globale variables */
private object     marble;
private mixed      *ob;

/* Prototypes */
public void        cant_see_in_room();
       void        hammer();
       void        whipe();
       void        new_block();

/*
 * Function name:    find_marble
 * Description  :    Finds the block of marble, and stores it as
 *                   an object variable
 */
void 
find_marble() 
{
    int i, j;
    object room;

    if (IS_ROOM_OBJECT(this_object()))
    {
        room = this_object();
	write("this_object\n");
    }
    else
    {
        room = environment(this_object());
	write("environment\n");
    }
    ob = all_inventory(room);
    j = sizeof(ob);

    for (i = 0; i < j; i++)
    {
        if (ob[i]->query_name() == "DolMarbleBlock")
	{
	    marble = ob[i];
	}
    } 
}

/*
 * Function name:    create_dunadan
 * Description  :    Creates the mobile dunedain
 */
public void
create_dunadan()
{
    set_living_name("wilhelma");
    set_name("wilhelma");
    add_name( ({ "dunadan", "artist", "mason" }) );
    set_race_name("human");
    set_gender(G_FEMALE);
    set_title("artistic mason");
    set_dunedain_house("Beor");
    set_long("This is an artist working with marble, she have marble " +
	"dust in her hair.\n");
    default_config_npc(55);

    set_base_stat(SS_INT, 80);
    set_skill(SS_WEP_CLUB, 55);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_APPR_OBJ, 75);
    set_skill(SS_APPR_VAL, 80);
    set_skill(SS_TRADING, 75);

    set_alignment(350);

    set_chat_time(600);
    add_chat("I hope I get this piece finished before the end of next month.");
    add_chat("Oh, there I was distracted again.");

    set_act_time(10);
    add_act(&hammer());
    add_act(&hammer());
    add_act(&hammer());
    add_act(&hammer());
    add_act(&hammer());
    add_act(&hammer());
    add_act(&whipe());
    add_act(&cant_see_in_room());

    find_marble();
}

public void
introduce_me(object pl, string name)
{
    command("say Greetings " + capitalize(name) +".");
    command("introduce me to "+name);
    command("say Might I interest you in a statue?");
}

public void
add_introduced(string name)
{
    object    pl;

    //    if (!objectp(pl = find_player(name)) ||
    //        pl->query_met(query_real_name()))
    //        return;

    if (!CAN_SEE_IN_ROOM(this_object()))
        cant_see_in_room();
    set_alarm(2.0, 0.0, &introduce_me(pl, name) );
}

/*
 * Function name:    cant_see_in_room
 * Description  :    Tests if our mason is able to see in the room, if
 *                   not, why not light the lamp post?
 */
public void
cant_see_in_room()
{
    if (CAN_SEE_IN_ROOM(this_object()))
        return;

    command("say I better turn the lights on.");
    command("light lamp posts");
    return;
}

/*
 * Function name:    hammer
 * Description  :    The hammering on the marble block.
 */
void
hammer()
{
    if(!CAN_SEE_IN_ROOM(this_object()))
        cant_see_in_room();
    
    if(!present(marble))
    {
        command("say I'll get a new block of marble.");
	command("emote whistles loudly.");
	set_alarm(3.0, 0.0, &new_block());
	return;
    }
    

    command("emote hammers on the marble block.");
    marble->chip();
}

/*
 * Function name:    whipe
 * Description  :    Whipe some sweat from the forehead
 */
public void
whipe()
{
    if(!CAN_SEE_IN_ROOM(this_object()))
        cant_see_in_room();

    command("emote whipes some sweat from her forehead.");
}

/*
 * Function name:    new_block
 * Description  :    Out of marble to hammer on? Order a new block of marble.
 */
void
new_block()
{
    object o;

    if (present(marble)) return;

    tell_room(environment(this_object()), "A wheeled chart enters from " +
	      "northwest, dumps off a marble block and leaves back " +
	      "where it came from.\n", 0);

    o = clone_object(DOL_OBJ + "marble");
    o->move(environment(this_object()));
    find_marble();
}
