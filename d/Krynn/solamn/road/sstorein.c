/* Aridor, 04/99 
 *
 * 2008-08-12 - Cotillion
 * - Fixed annoying runtime spamming the logs.
 */

#include <filter_funs.h>
#include <local.h>

inherit ROOM_BASE

object door;


void
reward_tour(object who)
{
    int exp = 100;
    int group = 4;
    int bit = 0;
    string ei_name = "Vault EI";

    if (who->test_bit("Krynn",group,bit))
      return;
    setuid();
    seteuid(getuid());
    STD_QUEST_LOG(ei_name, who, exp);
    who->set_bit(group,bit);
    who->add_exp_quest(exp);
    write("You have never stood in a vault like this before. " +
            "You feel slightly more experienced!\n");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if (interactive(ob))
      set_alarm(0.1,0.0,&reward_tour(ob));
}

void
hide_dagger(object ob)
{
    ob->add_prop(OBJ_I_HIDE, 11 + random(30));
}

void
create_road_room()
{
    set_short("In a small vault");
    set_long("You are standing in a small vault off the cliff of the Vingaard " +
	     "River.\n");
    INSIDE;
    DARK;

    add_object(JDAGGER, 1, hide_dagger);

    reset();
}

void
reset_road_room()
{
    setuid();
    seteuid(getuid());
    
    if (!objectp(door))
    {
        (door = clone_object(DOORINSIDE))->move(TO);
    }

    if (!sizeof(FILTER_PLAYERS(all_inventory(this_object()))))
    {
        object other_door = door->query_other_door();

//	door->set_open(0);
//	door->set_locked(1);
	door->close_door("door");
	door->do_lock_door("");
	other_door->do_lock_door("");
    }
}
