/* 
 * This file, /d/Gondor/minas/ingate1.c, was modified from /d/Gondor/morgul/city/i_ngate.c
 * Thanks to Olorin for his excellent city Minas Morgul, which
 * made me want to recode parts of Minas Tirith.
 * Elessar, Feb/Mar 94.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/friend_or_foe";
inherit "/d/Gondor/common/lib/binbit";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"
#define KNIGHT_S_GUILD_NAME "Solamnian Knights"

object  gate,
        other_gate,
        officer,
       *fighters = ({0, 0, 0, 0}),
       *guards;
int     oc = 0,
        ga_aid = 0,
        cg_aid = 0;

void set_oc(int i) { oc = i; }
void guard_attack(object *enemy);
void prepare_guard_attack(object *enemy);
void close_gate();

void
add_stuff()
{
}

void
reset_room()
{
  int     s, i;

  add_stuff();
  oc = 0;

  if (officer && present(officer,TO) && !officer->query_attack())
  {
    officer->command("west");
    officer->command("south");
    officer->command("east");
  }
  if (s = sizeof(guards))
  while(i < s)
  {
    if (guards[i] && present(guards[i],TO) && !guards[i]->query_attack())
    {
      guards[i]->command("west");
      guards[i]->command("south");
      guards[i]->command("east");
    }
    i++;
  }
}

void
create_gondor()
{
  set_long(BSN("The roads from every corner of Gondor enter the city here " +
    "through a giant gatehouse of strong white stone. To the east are the "+
    "two large doors of the gate, iron doors on steel posts. " +
    "To both sides of the gate you notice arrow slits in the walls. " +
    "To the west you see a broad cobbled street, lined with white stone "+
    "houses. "));
  set_short("Inside the Great Gate of Minas Tirith");
  add_exit(MINAS_DIR + "gate1","west","@@check_exit",1);
  add_exit(ANO_DIR + "pelennor/citygate","east",1);
  add_prop(ROOM_I_INSIDE,1);
  add_item("gatehouse",BSN(
    "You are standing inside the large gatehouse archway of the Great "+
    "Gate of Minas Tirith. There are thick, white stone walls north and "+
    "south, with arrow slits in both. The walls arch inwards above, "+
    "forming the archway of the gate. A strong wooden beam blocks the "+
    "iron doors of the Gate, both its ends disappearing "+
    "through the stone walls."));
  add_item(({"archway","arch"}), BSN(
    "The giant archway runs through the city wall. Only here, inside the " +
    "archway can you see the true width of the citywalls, exceeding 40 feet " +
    "at the base. High above you, you can see the large, white stone blocks "+
    "which have been expertly fitted together to form the arch in the " +
    "wall. "));
  add_item(({"wall","walls","city walls","city wall"}), BSN(
    "You are standing in an archway running through the First Wall. Only here, " +
    "inside the walls you can see the true width of the wall, exceeding 40 feet " +
    "at the base. There are several arrow slits in both walls. "));
  add_item(({"stone","stones","white stones","white stone"}), BSN(
    "You marvel at the work of craftsmen of ancient times, who brought stone "+
    "from a quarry in the White Mountains, and expertly fitted them " +
    "together so that you can hardly make out any cracks between them, to " +
    "build these mighty white walls. "));
  add_item(({"slits","slit","arrow slit","arrow slits"}), BSN(
    "There are several arrow slits in both walls inside the gatehouse, " +
    "and probably guards behind them, aiming at you right now! "));
  add_item(({"door","doors","plates"}), BSN(
    "The two doors of the gate are made of strong iron, each held up " +
    "by a steel post. "));
  seteuid(getuid());
  gate = clone_object(MINAS_DIR + "obj/tirithgate2");
  gate->move(TO);
    other_gate = gate->query_other_door();
  reset_room();
}

int 
filter_enemy(object enemy)
{
    if (!interactive(enemy))
	return 0;
    if (query_friend_or_foe(enemy) < 0)
	return 1;
    return 0;
}

int 
query_allow_escape(object invader, object guard)
{
    if ((guard->id("_minas_tirith_guard")) && 
        (random(guard->query_stat(SS_DEX)) > random(invader->query_stat(SS_DEX))/2) )
    {
        invader->catch_msg("The " + guard->query_nonmet_name() + " stops you!\n");
        return 0;
    }
    return 1;
}

string
ranger_title(object pl)
{

#ifndef NEW_RANGERS_OPEN
    if (pl->query_company() == "the Ranger pupils")
    {
    return "a fresh Ranger";
    }
    if (query_bin_bits(1,18,2,pl) == 2)
    {
    return "the Captain of the Rangers of " + pl->query_company();
    }
    return "a Ranger of " + pl->query_company();
#endif

#ifdef NEW_RANGERS_OPEN
    if (RANGERS_MEMBER(pl))
        return (LANG_ADDART(MANAGER->query_title_name(pl->query_real_name())));
#endif
}

object *
check_enemies()
{
    return filter(all_inventory(TO),"filter_enemy",TO);
}

int 
do_knock(string str)
{
    object *enemy;
    string  fname;
    string vb = QVB;

    NF(CAP(vb)+" on what?\n");
    if (str != "gate" && str != "on gate")
	return 0;

    TP->reveal_me(1);

    other_gate = gate->query_other_door();

    if (gate->query_open())
    {
	write("You "+vb+" on the open gate. Stupid, isn't it?\n");
	say(QCTNAME(TP)+" "+vb+"s on the open gate. Stupid, isn't it?\n");
    }
    else
    {
	write("You "+vb+" on the Great Gate.\n");
	say(QCTNAME(TP)+" "+vb+"s on the Great Gate.\n");
	enemy = check_enemies();
	if( (query_friend_or_foe(TP) > - 1) && (!sizeof(enemy)) )
	{
	    fname = "some " + TP->query_race_name();
	    if (IS_RANGER(TP))
	    {
		if (present("ranger_guild_object",TP))
		    if (present("ranger_guild_object",TP)->query_worn())
			fname = ranger_title(TP);
		    else if (IS_DUNADAN(TP)) 
			fname = "a Dunadan";
	    }
	    else if (IS_DUNADAN(TP))
		fname = "a Dunadan";
	    else if (TP->query_guild_name_occ() == KNIGHT_S_GUILD_NAME)
		fname = "some knight";

      tell_room(TO,BSN("From the room to the east, someone shouts: Open the gate, "
        +fname+" wants to leave!"));
      tell_room(gate->query_other_room(),
		BSN("You hear a muffled shout from the other side of the Great Gate.\n"));

      other_gate->do_unlock_door("You hear something heavy moving on the other side of the Gate.\n");
      gate->do_unlock_door("Suddenly, the wooden beam blocking the door start moving.\n");
      other_gate->do_open_door("The Great Gate opens as the iron doors of the gate swing inwards.\n");
      gate->do_open_door("The Great Gate opens as the iron doors of the gate swing inwards.\n");
    }
    else
    {
      tell_room(TO,BSN("From beyond the arrow slits, someone shouts: Alarm! Enemies in the gatehouse!"));
      tell_room(gate->query_other_room(),BSN("You hear muffled shouts from the other side of the gate.\n"));
      tell_room(TO,BSN("You hear more loud shouts coming from the north!"));
      if(!enemy)
        enemy = ({TP});
      if (oc < 3)
          (MINAS_DIR + "wall/ninwall1")->reset_room_and_improve_guards(oc);
      set_alarm(2.0 + rnd()*4.0, 0.0, &prepare_guard_attack(enemy));
    }

  }
  return 1;
}

int 
clone_officer()
{
    int    i,
           astat = 0,
           mstat,
           ostat;

    if (!officer && oc < 3)
    {
	officer = clone_object(MINAS_DIR + "npc/gondor_officer");
	officer->arm_me();
	officer->move(MINAS_DIR + "wall/ninwall1");
	if (oc)
	{
	    astat = TP->query_average_stat();
	    mstat = 3*astat/2;
	    ostat = (officer->query_average_stat())/3*2;
	    for (i = 0; i < (oc*2); i++)
	    {
		if (sizeof(fighters) < i)
		    break;
		fighters[i] = clone_object(MINAS_DIR + "npc/gondor_officer");
		fighters[i]->set_short("fighter");
		fighters[i]->set_pshort("fighters");
		fighters[i]->set_name("fighter");
		fighters[i]->set_pname("fighters");
		fighters[i]->set_long(BSN(
                  "This is one of the most experienced fighters of the Minas Tirith Garrison. " +
                  "He is especially trained to handle troublemakers and infiltrators."));
		if (astat > ostat)
		{
		    fighters[i]->set_stats(({mstat+20, mstat+20, mstat+20, mstat-20, mstat-20,mstat-20}));
		    fighters[i]->set_skill(SS_WEP_SWORD,   100);
		    fighters[i]->set_skill(SS_WEP_POLEARM, 100);
		    fighters[i]->set_skill(SS_WEP_CLUB,    100);
		    fighters[i]->set_skill(SS_WEP_AXE,     100);
		    fighters[i]->set_skill(SS_WEP_KNIFE,   100);
		    fighters[i]->set_skill(SS_PARRY,       100);
		    fighters[i]->set_skill(SS_DEFENCE,     100);
		    fighters[i]->add_prop(LIVE_I_QUICKNESS, 300);
		    fighters[i]->refresh_mobile();
		}
		fighters[i]->arm_me();
		fighters[i]->move(MINAS_DIR + "wall/ninwall1");
		tell_room(MINAS_DIR + "wall/ninwall1",
			  CAP(LANG_ADDART(fighters[i]->query_nonmet_name())) +
			  " arrives running!\n");
		officer->team_join(fighters[i]);
	    }
	}
	oc++;
    }
    else if (oc >= 3)
	return 0;
    else
    {
	if (officer->query_attack())
	    return 0;
	tell_room(ENV(officer), QCTNAME(officer) + " leaves.\n");
	officer->move_living("M",MINAS_DIR + "wall/ninwall1");
    }
    tell_room(MINAS_DIR + "wall/ninwall1",
	      CAP(LANG_ADDART(officer->query_nonmet_name())) + 
	      " arrives running!\n");
    officer->command("shout Alarm! Enemies inside the gates!");
    officer->command("shout All cityguards follow me!");
    return 1;
}

void 
prepare_guard_attack(object *enemy)
{
  int    i;

  tell_room(TO,"You hear people running and shouting somewhere north of here!\n");
  if (clone_officer() && !ga_aid)
    ga_aid = set_alarm(6.0 + rnd()*4.0, 0.0, &guard_attack(enemy));
}

void 
guard_attack(object *enemy)
{
  int    s, i, flag;

  if (ga_aid)
    remove_alarm(ga_aid);
  ga_aid = 0;
  if(!(s = sizeof(enemy)))
    return;

  flag = 0;
  i = 0;
  while(i < s) 
  {
    if(present(enemy[i],TO) && query_friend_or_foe(enemy[i]) < 1) 
      flag = 1; 
    i++;
  }

  if(!flag || !officer)
    return;

  guards = ENV(officer)->query_guards();
  i = 0;
  while(i < sizeof(guards))
  {
    if(guards[i])
      officer->team_join(guards[i]);
    i++;
  }
  officer->command("west");
  officer->command("south");
  officer->command("east");

  officer->command("kill " + enemy[0]->query_real_name());
  i = 0;
  while(i < sizeof(guards))
  {
    if(guards[i])
        guards[i]->command("kill " + enemy[0]->query_real_name());
    if((sizeof(fighters) > i) && objectp(fighters[i]))
        fighters[i]->command("kill " + enemy[0]->query_real_name());
    i++;
  }
}

public void 
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(!ob || !to)
	return;
    
    if(!living(ob))
	return;

    if (gate->query_open())
    {
	remove_alarm(cg_aid);
	cg_aid = set_alarm(3.0, 0.0, close_gate);
    }
}

void 
close_gate() 
{ 
    remove_alarm(cg_aid);
    cg_aid = 0;
    other_gate = gate->query_other_door();

    if (!gate->query_open())
	return;

    gate->do_close_door("The iron doors swing back to close the Great Gate again.\n");
    other_gate->do_close_door("The iron doors of the Gate swing back to close the Great Gate again.\n");

    gate->do_lock_door("The beam moves back into position, blocking the Gate.\n");
    other_gate->do_lock_door("You hear something heavy moving on the other side of the Gate.\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (living(ob)) 
    {
	"/d/Gondor/minas/wall/sguard1"->enter_ingate(ob,from);
	"/d/Gondor/minas/wall/nguard1"->enter_ingate(ob,from);
    }
}
  
object query_gate() { return gate; }

public void 
init()
{
    ::init();
    add_action(do_knock, "knock");
    add_action(do_knock, "pound");
}

public void
hook_wagon_depart(object wagon, string where)
{
    if (where != "east")
	return;

    if (gate->query_open())
	return;

    tell_room(TO, BSN("From the room to the east, someone shouts: Open the gate, "
		+     "the transport to Edoras has to leave.\n"));
    tell_room(gate->query_other_room(),
	      "You hear a muffled shout from the other side of the Great Gate.\n");

    other_gate->do_unlock_door("You hear something heavy moving on the other side of the Gate.\n");
    gate->do_unlock_door("Suddenly, the wooden beam blocking the door start moving.\n");
    other_gate->do_open_door("The Great Gate opens as the iron doors of the gate swing inwards.\n");
    gate->do_open_door("The Great Gate opens as the iron doors of the gate swing inwards.\n");

}

public void
hook_wagon_arrive(object wagon, string from)
{
    if (from != "west")
	return;

    close_gate();
}

