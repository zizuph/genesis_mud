/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include "../temple/defs.h"

#include <filter_funs.h>
#include <macros.h>

inherit INNER_OUT;
inherit NTEMPLE + "lib/blocking";

object g1,g2,priest;
object dragon;
int dragon_cloned = 0;
int cracked = 0;
int undeads_cloned = 0;
object *undeads = ({ });

void
reset_neraka_room()
{
    if (!objectp(priest))
        priest = clone_npc(NNPC + "priest");
    if (!objectp(g1))
        g1 = clone_npc(NNPC + "templeguard");
    if (!objectp(g2))
        g2 = clone_npc(NNPC + "templeguard");

    set_guards(({priest, g1, g2}));

    if (objectp(dragon))
    {
        if (!dragon->query_attack())
        {
            tell_room(E(dragon),"The " + dragon->short() + " gracefully " +
            "leaps into the air and flies away.\n");
            dragon->move_living("M",AVOID);
            dragon->remove_object();
        }
    }
    dragon_cloned = 0;
    undeads_cloned -= 10;
    if (undeads_cloned < 0)
        undeads_cloned = 0;
    undeads -= ({ 0 });
}

/*
 * undead support routines
 */
public void
add_undead()
{
    object undead;
    
    if (undeads_cloned > 15)
        return;

    undead = clone_object(NNPC + "zombie_temple_gate");
    undead->arm_me();
    undead->move_living("M", TO);
    tell_room(TO, QCNAME(undead) + " crawls up through the cracks " +
    "in the flagstones, the horrid stench almost making you gag.\n");

    undeads += ({ undead });
    undeads -= ({ 0 });
}

// remove_undead() - called by the undead itself when it returns into the ground
public void
remove_undead(object undead)
{
    if (member_array(undead, undeads) >= 0)
        undeads_cloned--;

    undeads -= ({ undead });

}

int
is_valid_target(object ob) { return ob->query_alignment() > 200; }

// finds a random target for an undead to attack.
public object
find_random_undead_target()
{
    object *t, *e;

    // t is the union of all goodaligned in the room
    t = FILTER_LIVE(all_inventory(TO));
    t = filter(t, is_valid_target);

    e = ({ });
    if (objectp(g1))
        e += ({ g1->query_attack() });
    if (objectp(g2))
        e += ({ g2->query_attack() });
    if (objectp(priest))
        e += ({ priest->query_attack() });

    t = t | e;
    t -= ({ 0 });

    if (!sizeof(t))
        return 0;
    return t[random(sizeof(t))];
}

void
check_for_help()
{
    if (random(2) && objectp(g2) && (g2->query_attack()) && (E(g2) == TO))
    {
        if (dragon && (E(dragon) != TO))
        {
            dragon->move_living("xxx",TO);
            if (P("horse",TO))
            {
                dragon->command("say Ahh.. Food...");
                dragon->command("kill horse");
            }
        }
        else if (!dragon && !dragon_cloned)
        {
            dragon = clone_object(NNPC+"youngblue");
            dragon_cloned = 1;
            if (dragon)
                tell_room(TO,"A great voice booms from above: Help is on the way!\n");
        }
    }
    else if (objectp(priest) && (priest->query_attack()) && (E(priest) == TO))
    {
    	if (!cracked)
    	{
    	    tell_room(TO,QCTNAME(priest) + " waves " + HIS(priest) + " arms " +
    	    "and the flagstones beneath your feet start to shift and crack!\n");
    	    remove_item("stones");
    	    remove_item("black stones");
            add_item(({"stones","black stones","cracked stones"}),
            "The black stones that make " +
            "up the square are similar in texture to the Temple of " +
            "Takhisis. Right here, the stones are shifted and cracked by " +
            "some great force.\n");
            set_alarm(5.0,0.0,add_undead);
            cracked=1;
    	}
    	else if (random(2))
    	{
            add_undead();
    	}
    }
}

string
long_descr()
{
    string str;

    str = tod_short_descr() + tod_long_descr()
      + extra_long_descr + " ";
    if (cracked)
        str += "The stones paving the square are shifted and cracked. ";
        
    str += season() + "\n";

    return str;
}

void
set_up_allowed()
{
    int x;
    
    for (x = T_LEADER ; x <= T_INITIATE ; x++)
        add_allowed(x, T_TEAMMEMBER, ({ "south" }));
    add_allowed(T_PILGRIM, 0, ({ "south" }));
    add_allowed(T_WIZARD, 0, ({ "south" }));
}

void
create_neraka_room()
{
    set_short("in the Temple Square");
    set_extra_long("You are in the north part of the Temple Square. " +
        "The square stretches west, east and north of here. " +
        "The Temple of Takhisis is south of here, the main entrance gaping " +
        "like the maw of some horrible beast.");

    add_item_citywalls();
    add_item_street1();
    add_item_templesquare();
    add_item("entrance","The entrance is designed to give the impression " +
        "of an open mouth, with long fangs just waiting to bite down on " +
        "the unsuspecting victim. A pair of torches are burning in " +
        "alcoves on either side of the entrance, adding the illusion of " +
        "a pair of burning eyes. The entrance is sealed shut.\n");

    add_exit(NINNER + "s4", "west");
    add_exit(NINNER + "s6", "east");
    add_exit(NINNER + "s2", "north");
    add_exit(NINNER + "s1", "northwest");
    add_exit(NINNER + "s3", "northeast");

    add_exit(NTEMPLE + "entrance", "south", "@@check_guards");
//    add_exit(NTEMPLE + "m1", "south", "@@enter_temple@@");

    set_up_allowed();

    reset_room();

    add_prop(ROOM_I_HIDE, -1);

    clone_object("/d/Ansalon/guild/pot/obj/donation_box")->move(TO);

    set_alarm(13.0,13.0,check_for_help);
}

int
my_look(string str)
{
    if (!str || (str != "up"))
        return 0;

    write("The temple towers above you, black stone jutting out at " +
        "impossible angles.\n");
    if (dragon && (E(dragon) != TO))
        write("You see a blue dragon circling above the temple.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(my_look,"look");
}

/*
int
enter_temple()
{
    object g;
    g = g1;
    if (!objectp(g))
        g = g2;
    if (!objectp(g))
        g = priest;

    if (!g)
        return 0;
    
    if (TP->query_guild_member_occ() == "Dragonarmy")
    {
        g->command("say to " + OB_NAME(TP) + " Use your respective " +
            "army entrance.");
        g->command("point");
        return 1;
    }

    if (!(NERAKA_ADMIN)->query_may_enter_temple(TP,g))
    {
        write("The " + g->short() + " blocks you from entering the " +
            "temple.\n");
        return 1;
    }
    else
    {
        if (!MEMBER(TP))
            write("You bravely enter the Temple of Takhisis.\n");
        return 0;
    }
}
*/
