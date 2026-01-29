#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define BEHOLDING_CHAMBER  "/d/Gondor/guilds/morgulmage/rooms/tower_6c"

int     do_knock(string str);

object  gate,
        other_gate,
        officer,
       *fighters = ({0, 0, 0, 0}),
       *guards;
int     oc;
int     g_att_alarm;
int     c_gate_alarm;

public void    set_oc(int i) { oc = i; }

public void    add_stuff() { }

void prepare_guard_attack(object *enemy);
void guard_attack(object *enemy);
void close_gate();

public void
reset_room()
{
    int     s, i;

    add_stuff();
    oc = 0;

  if (officer && present(officer,TO) && !officer->query_attack())
      officer->command("east");
  if (s = sizeof(guards))
  while (i < s)
  {
      if (guards[i] && present(guards[i],TO) && !guards[i]->query_attack())
          guards[i]->command("east");
      i++;
  }
}

public void
create_morgul_room()
{
    set_extraline("The Morgul Road is entering the city here through a "
      + "giant archway under the city wall. To the north, you can see "
      + "the two large wings of the gate. The wide walls are made from "
      + "large boulders of dark rock. To both sides of the gate some "
      + "steps lead into guardrooms inside the walls.");
    set_road(9);
    set_short_desc("inside the Morgul Gate in Minas Morgul");
    set_side("north");

    add_exit(MORGUL_DIR + "city/gateh2","east","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/mmr1","south","@@check_exit",2);
    add_exit(MORGUL_DIR + "city/gateh1","west","@@check_exit",1);

    add_morgul_road();

    add_item(({"archway","arch"}), BSN(
        "The giant archway runs through the city wall. Only here, "
      + "inside the archway can you see the true width of the "
      + "citywalls, exceeding 40 feet at the base. High above you, you "
      + "can see the large stone blocks which have been expertly "
      + "fitted together to form the arch in the wall."));
  add_item(({"wall","walls","city walls","city wall"}), BSN(
        "You are standing in an archway running through the city walls. "
      + "Only here, inside the walls you can see the true width of the walls, "
      + "exceeding 40 feet at the base. "));
  add_item(({"boulder","boulders","rock"}), BSN(
	"These walls stand as testimony to the work of long dead craftsmen. "
      + "Giant boulders have been hewn from hard rock, and fitted "
      + "seamlessly together to form these mighty walls."));
  add_item(({"step","steps","stone slabs","slabs"}), BSN(
        "Just three stone slabs leading up into the guardrooms. "));
  add_item(({"wing","wings","plates"}), BSN(
        "The two wings of the gate are covered with thick black metal plates. "
      + "The body of the wings is probably made from wood, and the metal "
      + "plates protect the wood against fire and splintering. "));

    gate = clone_object(MORGUL_DIR + "city/morgulgate2.c");
    gate->move(TO);
    (MORGUL_DIR + "city/mmr3")->load_me();
    (MORGUL_DIR + "city/wall/wall01")->load_me();
    (MORGUL_DIR + "city/wall/wall08")->load_me();
    (MORGUL_DIR + "city/gateh2")->load_me();
    reset_room();
}

/*  I took this out since it seems too spammy - Morbeche */
public void
enter_inv(object ob, object from)
{
    int     wizrank;
    string  name;

    ::enter_inv(ob, from);

    if (!objectp(ob) || !interactive(ob))
        return;

    name = ob->query_real_name();
    if (ob->query_invis())
        return;

    tell_room(BEHOLDING_CHAMBER,
	      "The black raven on the window ledge caws loudly.\n");
}                                                                              


void
init()
{
    ::init();
    add_action(do_knock, "knock");
    add_action(do_knock, "pound");
}

int
filter_enemy(object enemy)
{
  object  attacker;

  if(!interactive(enemy))
    return 0;
  if(query_feeling(enemy) == -1)
  {
    if (!objectp(attacker = enemy->query_attack()))
      return 0;
    if (attacker->id("_morgul_monster"))
      return 1;
    return 0;
  }
  return 1;
}

int
query_allow_escape(object invader, object guard)
{
    if ((guard->id("_morgul_monster")) && 
        (random(guard->query_stat(SS_DEX)) >
	 random(invader->query_stat(SS_DEX))/2) )
    {
        invader->catch_msg("The " + guard->query_nonmet_name() +
	    " stops you!\n");
        return 0;
    }
    return 1;
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
  string  vb = QVB;
 
  NF(CAP(vb)+" on what?\n");
  if (str != "gate" && str != "on gate")
    return 0;

  TP->reveal_me(1);

  other_gate = gate->query_other_door();

  if(gate->query_open())
  {
    write("You "+vb+" on the open gate. Stupid, isn't it?\n");
    say(QCTNAME(TP)+" "+vb+"s on the open gate. Stupid, isn't it?\n");
  }
  else
  {
    write("You "+vb+" on the dark gate.\n");
    say(QCTNAME(TP)+" "+vb+"s on the dark gate.\n");
    enemy = check_enemies();
    if ((query_feeling(TP) == -1) && (!sizeof(enemy)))
    {
        fname = TP->query_race_name();
	if (fname == "elf")
	{
          tell_room(TO,BSN(
              "From the room to the east, someone shouts: "
            + "Alarm! Enemies inside the gate!"));
          tell_room(gate->query_other_room(),BSN(
	      "You hear muffled shouts from the other side of the gate."));
          tell_room(TO,BSN(
	      "From the room to the east, a deep voice shouts: Hold your "
	    + "fire! This elf belongs to our Master!"));
          tell_room(gate->query_other_room(),BSN(
	      "You hear muffled shouts from the other side of the gate."));
          tell_room(TO,BSN(
	      "From the room to the east, a deep voice shouts: "
	    + "Open the gate!"));
	}
	else
	{
          if (TP->query_guild_name_occ() == MORGUL_S_GUILD_NAME)
        {
              if(TP->query_nazgul() != 2)
                fname = LANG_ADDART(TP->query_morgul_title());
              else
                fname = "make haste, the " + TP->query_morgul_title();
        }
          else if (TP->query_guild_name_occ() == VAMPYR_S_GUILD_NAME)
            fname = "some vampyr";
	  else
            fname = "some " + fname;
          tell_room(TO,BSN(
	      "From the room to the east, someone shouts: "
	    + "Open the gate, "+fname+" wants to leave!"));
          tell_room(gate->query_other_room(),BSN(
	      "You hear a muffled shout from the other side of "
	    + "the gate.\n"));
	}
        other_gate->do_unlock_door(
	    "You hear something heavy moving on the other side of "
	  + "the gate.\n");
        gate->do_unlock_door(
	    "Suddenly, the three wooden beams blocking the door "
	  + "start moving.\n");
        other_gate->do_open_door(
	    "The dark gate opens as the wings of the gate swing "
	  + "inwards.\n");
        gate->do_open_door(
	    "The dark gate opens as the wings of the gate swing "
	  + "inwards.\n");
    }
    else
    {
      tell_room(TO,BSN(
	  "From the room to the east, someone shouts: "
	+ "Alarm! Enemies inside the gate!"));
      tell_room(gate->query_other_room(),BSN(
	  "You hear muffled shouts from the other side of the gate."));
      tell_room(TO,BSN(
	  "You hear more loud shouts from the room to the east!"));
      if(!enemy)
        enemy = ({TP});
      if (oc < 3)
          (MORGUL_DIR + "city/gateh2")->reset_room_and_improve_guards(oc);
      set_alarm(itof(2 + random(4)), 0.0, &prepare_guard_attack(enemy));
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

  if(!officer && oc < 3)
  {
      officer = clone_object(MORGUL_DIR + "npc/ithil_officer");
      officer->move(MORGUL_DIR + "city/gateh2");
      if (oc)
      {
          astat = TP->query_average_stat();
          mstat = 3*astat/2;
          ostat = (officer->query_average_stat())/3*2;
          for(i = 0; i < (oc*2); i++)
          {
              if (sizeof(fighters) < i)
                  break;
              fighters[i] = clone_object(MORGUL_DIR + "npc/ithil_officer");
              fighters[i]->set_short("fighter");
              fighters[i]->set_pshort("fighters");
              fighters[i]->set_name("fighter");
              fighters[i]->set_pname("fighters");
              fighters[i]->set_long(BSN(
                  "This is one of the most experienced fighters of the Morgul "
		+ "Army. He is especially trained to handle troublemakers and "
		+ "infiltrators."));
              if (astat > ostat)
              {
                  fighters[i]->set_stats(({mstat+20, mstat+20, mstat+20,
			mstat-20, mstat-20,mstat-20}));
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
              fighters[i]->move(MORGUL_DIR + "city/gateh2");
              tell_room(MORGUL_DIR + "city/gateh2",
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
    officer->move_living("M",MORGUL_DIR + "city/gateh2");
  }
  tell_room(MORGUL_DIR + "city/gateh2",
    CAP(LANG_ADDART(officer->query_nonmet_name())) + " arrives running!\n");
  officer->command("shout Alarm! Enemies inside the gates!");
  officer->command("shout All guards follow me!");
  return 1;
}

void
prepare_guard_attack(object *enemy)
{
  int    i;

  tell_room(TO,
    "You hear people running and shouting from the room to the east!\n");
  if(clone_officer() && !get_alarm(g_att_alarm))
    g_att_alarm = set_alarm(itof(6 + random(5)), 0.0, &guard_attack(enemy));
}

void
guard_attack(object *enemy)
{
  int    s, i, flag;

  if(!(s = sizeof(enemy)))
    return;

  flag = 0;
  i = 0;
  while(i < s) 
  {
    if (objectp(enemy[i]) && present(enemy[i],TO) &&
	(query_feeling(enemy[i]) > -1))
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

  if(gate->query_open())
  {
    remove_alarm(c_gate_alarm);
    c_gate_alarm = set_alarm(itof(2 + random(2)), 0.0, close_gate);
  }
}

void
close_gate() 
{ 
  other_gate = gate->query_other_door();

  if(!gate->query_open())
    return;

  gate->do_close_door(
    "The wings of the gate swing back to close the gate again.\n");
  other_gate->do_close_door(
    "The wings of the gate swing back to close the gate again.\n");

  gate->do_lock_door(
    "The beams move back into position, blocking the gate.\n");
  other_gate->do_lock_door(
    "You hear something heavy moving on the other side of the gate.\n");
}
