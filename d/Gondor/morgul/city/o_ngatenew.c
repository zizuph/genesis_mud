/* Fixed trolls being cloned and not armed. Changed the normal trolls
   with magical black platemails to the trolls with limited black
   platemails.
   Gwyneth - May 31, 2000
*/
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/morgul/feeling.c";

#include <composite.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define BEHOLDING_CHAMBER  "/d/Gondor/common/guild2/tower/tower_6c"
#define TOWER_IN_GATE      (MORGUL_DIR + "tower/tower_entrance")

object  patrol, gate, other_gate, officer, *guards;
public int do_knock(string str);
int     oc,
        al_guard_attack = 0;

int fire_volley_alarm;
int close_gate_alarm;
void prepare_guard_attack(object *enemy, int av);
void close_gate();
void clone_olog();
void guard_attack(object *enemy, int av);

void
add_stuff()
{
    if (!objectp(patrol))
    {
	patrol = clone_object(NPC_DIR+"redleadorc");
	patrol->set_restrain_path(MORGUL_DIR+"road");
	// packsize must be set before arm_me() is called:
	patrol->set_pack_size(6);
	patrol->arm_me();
	patrol->move_living("down", TO);
    }
}

void
create_gondor()
{
    set_name("Morgul Gate");
    set_short("before the Dark Gate of Minas Morgul");
    set_long("@@long_func");
    
    add_exit(MORGUL_DIR + "road/mrd4","northwest",0);
    
    gate = clone_object(MORGUL_DIR + "city/morgulgate1.c");
    gate->move(TO);
    
    add_item(({"road","ground","street"}), BSN(
        "The road is winding down into the Morgul Vale to the north. "
      + "In some distance you can make out the bridge on which the road "
      + "crosses the river. "));
  add_item(({"morgul","morgul vale","morgulduin","river","bridge"}), BSN(
        "To the north, the Morgulduin with its dark waters is running "
      + "westwards. On the opposite side of the river, the mountains of the "
      + "Ephel Duath are rising steeply into the sky. The road is crossing "
      + "the Morgulduin on an ancient bridge. "));
  add_item(({"spikes","teeth","mouth"}), BSN(
        "The gate is shaped like a dark gaping mouth, the steel "
      + "spikes looming down looking like gleaming teeth. It is probably "
      + "possible to lower the spikes when the gate is attacked as an "
      + "additional fortification of the gate. "));
  add_item(({"wing","wings","plates"}), BSN(
        "The two wings of the gate are covered with thick black metal plates. "
      + "The body of the wings is probably made from wood, and the metal "
      + "protect the wood against fire and splintering. "));
  add_stuff();
  (MORGUL_DIR + "city/gateh1")->load_me();
}

/*  Taken out since I decided its too spammy, keeping the
    code in though in case I want to put it back in - Morbeche
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
	      "The black raven on the window ledge caws.\n");
}                                                                              

*/


void init()
{
  ::init();
    add_action(do_knock, "knock");
    add_action(do_knock, "pound");
}

string
long_func()
{
    int     gate_open;

    seteuid(getuid(TO));
    gate_open = gate->query_open();

    if (gate_open)
    {
        return BSN("You are standing before the Dark Gate of Minas"
          + " Morgul. The cavernous gate, shaped like an open mouth"
          + " with gleaming teeth, is gaping wide. Inside the city looks"
          + " pale and gloomy, and you think twice before entering. The"
          + " road winds down towards the bridge to the north"
          + ", gleaming faintly.");
    }

    return BSN("You are standing before the Dark Gate of Minas Morgul."
      + " The dark and ominous gate is closed, but you feel as if you are"
      + " being watched. The road winds down towards the bridge to the"
      + " north.");
}

void
reset_room()
{
  int     s, i;
  string *where;

  add_stuff();
  oc = 0;
  if (officer && !officer->query_attack())
  {
      where = explode(file_name(ENV(officer)), "/");
      if (implode(where[0..4], "/") == "/d/Gondor/morgul/road")
          officer->move_living("back to the gate", TO);
      if (present(officer,TO))
          officer->move_living("south through the gate",
	      MORGUL_DIR + "city/gateh1");
  }
  for (i = 0; i < sizeof(guards); i++)
  {
      if (guards[i] && !guards[i]->query_attack())
      {
          where = explode(file_name(ENV(guards[i])), "/");
          if (implode(where[0..4], "/") == "/d/Gondor/morgul/road")
              guards[i]->move_living("back to the gate", TO);
          if (present(guards[i],TO))
              guards[i]->move_living("south through the gate",
		 MORGUL_DIR + "city/gateh1");
      }
  }
}

int
filter_enemy(object enemy)
{
  if(!interactive(enemy))
    return 0;
  if(query_feeling(enemy) == -1)
    return 0;
  return 1;
}

object *
check_enemies()
{
    return filter(all_inventory(TO),"filter_enemy",TO);
}
  
varargs void
get_guards_ready(object *enemy)
{
    int     i,
            tmp,
            max = 0,
            s;

    tell_room(TO,BSN(
        "From the top of the walls, someone shouts: "
      + "Alarm! Enemies at the gate!"));
    tell_room(gate->query_other_room(),BSN(
        "From the top of the walls, someone shouts: "
      + "Alarm! Enemies at the gate!"));
    tell_room(TO,BSN(
        "You hear more loud shouts from the top of the walls and on the other "
      + "side of the gate!"));
    tell_room(gate->query_other_room(), BSN(
        "You hear more loud shouts from the top of the walls and on the other "
      + "side of the gate!"));
    if(!sizeof(enemy))
        enemy = ({TP});
    if ((s = sizeof(enemy)) > 2)
    {
        tell_room(TO, "A male human voice shouts: We will need archers!\n");
        tell_room(gate->query_other_room(),
	    "A male human voice shouts: We will need archers!\n");
    }
    for (i = 0; i < s; i++)
    {
        tmp = enemy[i]->query_average_stat();
        if (tmp > max)
            max = tmp;
    }
    set_alarm(itof(random(4)), 0.0, &prepare_guard_attack(enemy, max));
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

  if (gate->query_open())
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
              "From the top of the walls, someone shouts: "
            + "Alarm! Enemies at the gate!"));
          tell_room(gate->query_other_room(),BSN(
              "From the top of the walls, someone shouts: "
            + "Alarm! Enemies at the gate!"));
          tell_room(TO,BSN(
	      "From the top of the walls, a deep voice shouts: Hold your "
	    + "fire! This elf belongs to our Master!"));
          tell_room(gate->query_other_room(),BSN(
	      "From the top of the walls, a deep voice shouts: Hold your "
	    + "fire! This elf belongs to our Master!"));
          tell_room(TO,BSN(
	      "From the top of the walls, a deep voice shouts: "
	    + "Open the gate!"));
          tell_room(gate->query_other_room(),BSN(
	      "From the top of the walls, a deep voice shouts: "
	    + "Open the gate!"));
	}
	else
	{
          if (TP->query_guild_name_occ() == MORGUL_S_GUILD_NAME)
            fname = LANG_ADDART(TP->query_morgul_title());
          else if (TP->query_guild_name_occ() == VAMPYR_S_GUILD_NAME)
            fname = "some vampyr";
	  else
            fname = "some " + fname;
          tell_room(TO,BSN(
	      "From the top of the walls, someone shouts: "
	    + "Open the gate, "+fname+" wants to enter!"));
          tell_room(gate->query_other_room(),BSN(
	      "From the top of the walls, someone shouts: Open the gate, "
            + fname+" wants to enter!"));
        }
        gate->do_unlock_door(
	    "You hear something heavy moving on the other side of the "
	  + "gate.\n");
        other_gate->do_unlock_door(
	    "Suddenly, the three wooden beams blocking the door start "
	  + "moving.\n");
        gate->do_open_door(
	    "The dark gate opens as the wings of the gate swing inwards.\n");
        other_gate->do_open_door(
	    "The dark gate opens as the wings of the gate swing inwards.\n");
        close_gate_alarm = set_alarm(10.0, 0.0, close_gate);
    }
    else
        get_guards_ready(enemy);
  }
  return 1;
}

void close_gate() { gate->query_other_room()->close_gate(); }

void
close_gate_to_stop_invaders(object one_enemy)
{
    object *enemy;

    one_enemy->catch_msg(
	"When you try to enter the gate, you hear a shout from inside "
      + "the city.\n");
    tell_room(TO,"When "+QTNAME(one_enemy)+" tries to enter the gate, " +
        "you hear a shout from inside the city.\n", one_enemy);
    tell_room(TO,"Someone shouts: Close the gate! Invaders!\n");
    close_gate();
    enemy = ({ one_enemy });
    get_guards_ready(enemy);
}

void fire_volley_at_enemy(int interval)
{
    object *enemy,
           *victims = ({}),
            armour,
            co;
    int     n, i, j,
            dam,
           *hloc_id,
            hloc,
            hit,
            hurt,
            phurt,
            hp,
            tmp;
    mixed  *hloc_ac,
            ac;
    string  mstr;

    enemy = check_enemies();

    n = sizeof(enemy);
    if (!n)
        return;

    tell_room(TO,
	"Someone shouts: Fire!\n" 
      + "A volley of quarrels is fired from the top of the walls.\n");
    
    for (i = 0; i < n; i++)
    {
        if ((hit = enemy[i]->resolve_task(TASK_DIFFICULT, ({SKILL_AVG, TS_DEX, 
            SS_AWARENESS, SS_ACROBAT, SS_PARRY, SKILL_END}))) < 0)
        {
            co = enemy[i]->query_combat_object();
            hloc_id = co->query_hitloc_id();
            tmp = random(100);
            for (j = 0, hloc = 0; hloc < sizeof(hloc_id); hloc++)
            {
                hloc_ac = co->query_hitloc(hloc_id[hloc]);
                if (!sizeof(hloc_ac))
                    break;
                j += hloc_ac[1];
                if (j >= tmp)
                    break;
            }
            if (hloc >= sizeof(hloc_id))
        	hloc = sizeof(hloc_id) - 1;

            ac = hloc_ac[3];
    
	    if (sizeof(ac))
	        ac = ac[0];
	    else if (!intp(ac))
	        ac = 0;

	    dam = random(400);
 	    ac = random(ac);
	    dam = F_DAMAGE(dam, ac);

            if (dam < 1)
                dam = 0;

            hp = enemy[i]->query_hp();

    /*
     * Wizards are immortal. (immorale ??)
     */
            if ((int)enemy[i]->query_wiz_level() && dam >= hp)
            {
        	tell_object(enemy[i],
		    "Your wizardhood protects you from death.\n");
                tell_room(environment(enemy[i]),
                    QCTNAME(enemy[i]) + " is immortal and fails to die!\n",
		    enemy[i]);
            }
    
            if (dam > 0 && hp)
            {
                phurt = (100 * dam) / hp;
                if (dam && !phurt)
                    phurt = 1;     /* Less than 1% damage */
            }
            else if (dam > 0)
                phurt = 100;
            else
                phurt = -1;   /* Enemy missed */

            if (dam > 0)
                enemy[i]->heal_hp(-dam);
    
    /*
     * Adjust our panic level
     */
            if (phurt >= 0)
               enemy[i]->add_panic(2 + phurt / 5);
    
            if (phurt == 0)
                mstr = "A quarrel barely misses you.\n";
            else if (phurt < 10)
                mstr = "A quarrel hits you.\n";
            else if (phurt < 30)
                mstr = "You are hurt by a quarrel.\n";
            else if (phurt < 50)
                mstr = "You are badly hurt by a quarrel.\n";
            else if (phurt < 70)
                mstr = "You are seriously wounded by a quarrel.\n";
            else
                mstr = "Your chest is pierced by a quarrel. "
		     + "You are dangerously wounded.\n";
            enemy[i]->catch_msg(mstr);
            victims += ({enemy[i]});
        }
    }
    switch(sizeof(victims))
    {
        case 0:
            tell_room(TO, "The quarrels miss.\n");
            break;
        case 1:
            tell_room(TO,CAP(COMPOSITE_LIVE(victims)) +
		" is hit by a quarrel.\n",victims);
            break;
        default:
            tell_room(TO,CAP(COMPOSITE_LIVE(victims)) +
		" are hit by quarrels.\n", victims);
            break;
    }
    for (i = 0; i < sizeof(victims); i++)
    {
        if (victims[i]->query_hp() <= 0)
        {
            victims[i]->do_die(TO);
            write_file(LOG_DIR + "evilkill", enemy[i]->query_name() + " (" + 
                enemy[i]->query_average_stat() +
		") was killed at the Morgul Gate on " +
                ctime(time()) + ".\n");
        }
    }
    if (!get_alarm(fire_volley_alarm))
        fire_volley_alarm = set_alarm(itof(interval + random(4)), 0.0,
            fire_volley_at_enemy);
}

void set_oc(int i) { oc = i; }

int
clone_officer(int av)
{
  int    i;

  if (!officer)
  {
    if (oc > 1)
    {
        if (!get_alarm(fire_volley_alarm))
            tell_room(TO,
		"Several soldiers appear on top of the wall over the "
	      + "gate.\n" 
	      + "Someone shouts: Prepare your cross-bows! "
	      + "Fire at my command!\n");
        remove_alarm(fire_volley_alarm);
        fire_volley_alarm = set_alarm(3.0, 0.0, &fire_volley_at_enemy(2));
        return 0;
    }
    else
    {
        officer = clone_object(MORGUL_DIR + "npc/ithil_officer");
        i = (3 * av) / 2;
        if (officer->query_average_stat() < i)
            officer->upgrade_monster(i);
        (MORGUL_DIR + "city/gateh1")->reset_room();
        oc++;
    }
  }
  else
  {
    if (officer->query_attack())
      return 0;
    tell_room(ENV(officer), QCTNAME(officer) + " leaves.\n");
  }
  officer->move_living("M",MORGUL_DIR + "city/gateh1");
  tell_room(MORGUL_DIR + "city/gateh1",
      CAP(LANG_ADDART(officer->query_nonmet_name())) + " arrives running!\n");
  officer->command("shout Alarm! Enemies at the gates!");
  officer->command("shout All guards follow me!");
  guards = ENV(officer)->query_guards();

  for (i = 0; i < sizeof(guards); i++)
  {
      if (objectp(guards[i]))
          officer->team_join(guards[i]);
      else if (!random(3))
          set_alarm(0.0, 0.0, clone_olog);
  }
  return 1;
}

void
clone_olog()
{
    object  troll;

    troll = clone_object(MORGUL_DIR + "npc/ithil_olog_out");
    troll->move(ENV(officer));
    tell_room(ENV(officer), QCNAME(troll) + " arrives running.\n");
    troll->arm_me();
    officer->team_join(troll);
    guards += ({ troll });
}

void
prepare_guard_attack(object *enemy, int av)
{
    int    i;

    tell_room(TO,"You hear people running and shouting on the other side "
       + "of the gate!\n");
    if ( (clone_officer(av)) && (!al_guard_attack) )
        al_guard_attack = set_alarm(5.0, 0.0, &guard_attack(enemy, av));
}

void 
guard_attack(object *enemy, int av)
{
  int    s, i, flag, stat;
  object mage;

  al_guard_attack = 0;

  if(!(s = sizeof(enemy)))
    return;

  flag = 0;
  i = 0;
  while(i < s) 
  {
    if (objectp(enemy[i]) && present(enemy[i],TO) &&
    query_feeling(enemy[i]) > -1) 
      flag = 1; 
    i++;
  }

  if(!flag || !officer)
    return;

  officer->command("east");
  officer->command("shout Open the gate!");
  officer->command("shout Alert the tower!");

  TOWER_IN_GATE->teleledningsanka();
  if (mage = present("morandir", TOWER_IN_GATE))
  {
      mage->remote_tour();
  }

  tell_room(TO, "The wings of the gate swing open. \n");
  tell_room(ENV(officer), "The wings of the gate swing open. \n");

  officer->move_living("north through the gate",TO);
  officer->command("kill " + enemy[0]->query_real_name());

  stat = (5 * av) / 4;
  flag  = 0;

  for (i = 0; i < sizeof(guards); i++)
  {
      if (guards[i])
      {
          if (guards[i]->query_average_stat() < stat)
              flag++;
          guards[i]->move_living("north through the gate",TO);
          guards[i]->command("kill " + enemy[0]->query_real_name());
      }
  }
  tell_room(gate->query_other_room(), "The gate is closed again. \n");
  tell_room(ENV(officer), "The gate is closed again. \n");
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
    remove_alarm(close_gate_alarm);
    close_gate_alarm = set_alarm(1.0, 0.0, close_gate);
  }
}
