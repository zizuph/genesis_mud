/* 
 * This file, ingate.c, was modified from 
 * /d/Gondor/morgul/city/i_ngate.c to be a standard file for
 * the rooms just inside the gate.
 * Thanks to Olorin for his excellent city Minas Morgul, which
 * made me want to recode parts of Minas Tirith.
 * Elessar, Feb/Mar 94.
 *
 * Modification log:
 * 12-Jul-1997: Changed inheritance, function vars. Olorin.
 * May, 2004: Updated for ranger recode, Tigerlily
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
#define KNOCKED_ONCE  "_mt_i_knocked_once"

/*
 * Prototypes:
 */
public int     do_knock(string str);

/*
 * Global variables:
 */
object  gate,
        other_gate,
        officer,
        token,
       *fighters = ({0, 0, 0, 0}),
       *guards;
int     oc,
        cg_aid,
        ga_aid;
string IGROOM, GROOMDIR, GFILE2, GDIR, WROOM, OFILE, *GRTOIG;

void reset_room();

void guard_attack(object *enemy);
void prepare_guard_attack(object *enemy);
void close_gate();
void set_oc(int i) { oc = i; }

public void 
create_gondor()
{
    set_long("You are inside an undescribed gatehouse somewhere.\n");
    set_short("Inside some gate");
    add_prop(ROOM_I_INSIDE,1);
    add_item(({"archway","arch"}), BSN(
    "The giant archway runs through the city wall. Only here, inside the " +
    "archway can you see the true width of the citywalls, exceeding 40 feet " +
    "at the base. High above you, you can see the large, white stone blocks "+
    "which have been expertly fitted together to form the arch in the " +
    "wall. "));
  add_item(({"wall","walls","city walls","city wall"}), BSN(
    "You are standing in an archway running through the walls. Only here, " +
    "inside the walls you can see the true width of the wall, exceeding 40 feet " +
    "at the base. There are several arrow slits in both walls. "));
  add_item(({"stone","stones"}),"Large stone blocks form the walls.\n");
  add_item(({"slits","slit","arrow slit","arrow slits"}), BSN(
    "There are several arrow slits in both walls inside the gatehouse, " +
    "and probably guards behind them, aiming at you right now! "));
  add_item(({"door","doors","plates"}), BSN(
    "The two doors of the gate are made of strong iron, each held up " +
    "by a steel post. "));
    seteuid(getuid());
    if (GFILE2)
	gate = clone_object(GFILE2);
    gate->move(TO);
    enable_reset(0);
    reset_room();
}

public void 
init()
{
    ::init();
    add_action(do_knock, "knock");
    add_action(do_knock, "pound");
}

void
reset_room()
{
    int     s,n,i;

    oc = 0;

    if (officer && present(officer,TO) && !officer->query_attack())
    {
        while (n < sizeof(GRTOIG))
        {
            officer->command(GRTOIG[n]);
            n++;
        }
    }
    n = 0;
    if (s = sizeof(guards))
    while (i < s)
    {
        if (guards[i] && present(guards[i],TO) && !guards[i]->query_attack())
        {
            while(n<sizeof(GRTOIG))
            {
                guards[i]->command(GRTOIG[n]);
                n++;
            }
        }
        i++;
    }
}

int
filter_enemy(object enemy)
{
    if (!interactive(enemy))
	return 0;
    if (query_friend_or_foe(enemy) == -1)
	return 1;
    return 0;
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

object *
check_enemies()
{
    return filter(all_inventory(TO), filter_enemy);
}

public int 
do_knock(string str)
{
    object *enemy;
    string  fname;
    string  vb = QVB;
    object tp = this_player();
 
    NF(CAP(vb)+" on what?\n");
    if (str != "gate" && str != "on gate")
        return 0;

    tp->reveal_me(1);

    other_gate = gate->query_other_door();

    if(gate->query_open())
    {
    write("You "+vb+" on the open gate. Stupid, isn't it?\n");
    say(QCTNAME(tp)+" "+vb+"s on the open gate. Stupid, isn't it?\n");
    }
    else
    {
    write("You "+vb+" on the gate.\n");
    say(QCTNAME(tp)+" "+vb+"s on the gate.\n");
    enemy = check_enemies();
    if( (query_friend_or_foe(tp) > - 1) && (!sizeof(enemy)) )
    {
        fname = "some " + tp->query_race_name();


#ifndef NEW_RANGERS_OPEN
        if (IS_RANGER(tp))
        {
            if (present("ranger_guild_object", tp))
                if (present("ranger_guild_object", tp)->query_worn())
                    fname = ranger_title(tp);
                else if (IS_DUNADAN(tp)) 
                   fname = "a Dunadan";
        }
#endif
#ifdef NEW_RANGERS_OPEN
        if (RANGERS_MEMBER(tp))
        {
            if (objectp(token = present("ranger_guild_object", tp)) &&
            token->query_worn())
            fname = ranger_title(tp);
        }
        else if (IS_DUNADAN(tp))
            fname = "a Dunadan";
        }
#endif
        else if (IS_DUNADAN(tp))
            fname = "a Dunadan";

        else if (tp->query_guild_name_occ() == KNIGHT_S_GUILD_NAME)
            fname = "some knight";
        
        if (sizeof(gate->query_other_door()->check_enemies())>0 &&
        !tp->query_prop(KNOCKED_ONCE))
        {
        tell_room(TO,BSN("From the "+GDIR+" you hear a guard shouting: "+
            "Since you are "+fname+", I'll warn you against going out there! "+
            "There is an attack going on! But if you want to help us against "+
            "the attackers, you can just "+vb+" again."));
        tp->add_prop(KNOCKED_ONCE,1);
        }
        tell_room(TO,BSN("From the room to the "+GDIR+", someone shouts: " +
            "Open the gate, " +fname+" wants to leave!"));
        tell_room(gate->query_other_room(),BSN("You hear a muffled shout " +
            "from the other side of the gate.\n"));
        other_gate->do_unlock_door("You hear something heavy moving on " +
            "the other side of the gate.\n");
        gate->do_unlock_door("Suddenly, the wooden beam blocking the door " +
            "starts moving.\n");
        other_gate->do_open_door("The gate opens as the iron doors of the " +
            "gate swing inwards.\n");
        gate->do_open_door("The gate opens as the iron doors of the gate " +
            "swing inwards.\n");
        }
        else
        {
        tell_room(TO,BSN("From beyond the arrow slits, someone shouts: " +
            "Alarm! Enemies in the gatehouse!"));
        tell_room(gate->query_other_room(),BSN("You hear muffled shouts from " +
            "the other side of the gate.\n"));
        tell_room(TO,BSN("You hear more loud shouts coming from the "+
            GROOMDIR+"!"));
        if(!enemy)
            enemy = ({tp});
        if (oc < 3)
            (IGROOM)->reset_room_and_improve_guards(oc);
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

  if(!officer && oc < 3)
  {
      officer = clone_object(OFILE);
      officer->set_name("officer");
      officer->arm_me();
      officer->move(IGROOM);
      if (oc)
      {
          astat = TP->query_average_stat();
          mstat = 3*astat/2;
          ostat = (officer->query_average_stat())/3*2;
          for(i = 0; i < (oc*2); i++)
          {
              if (sizeof(fighters) < i)
                  break;
              fighters[i] = clone_object(OFILE);
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
                    fighters[i]->arm_me();
              }
              fighters[i]->move(IGROOM);
              tell_room(IGROOM,CAP(LANG_ADDART(fighters[i]->query_nonmet_name())) +
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
    officer->move_living("M",IGROOM);
  }
  tell_room(IGROOM,CAP(LANG_ADDART(officer->query_nonmet_name())) + " arrives running!\n");
  officer->command("shout Alarm! Enemies inside the gates!");
  officer->command("shout All cityguards follow me!");
  return 1;
}

void 
prepare_guard_attack(object *enemy)
{
    int    i;
    
    tell_room(TO,"You hear people running and shouting somewhere "+GROOMDIR+" of here!\n");
    if (clone_officer() && !ga_aid)
	ga_aid = set_alarm(4.0 + rnd()*4.0, 0.0, &guard_attack(enemy));
}

void 
guard_attack(object *enemy)
{
    int    s, i, n, flag;
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
    while (n<sizeof(GRTOIG)) {
	officer->command(GRTOIG[n]);
	n++;
    }
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
    
    if (ob->query_prop(KNOCKED_ONCE))
	ob->remove_prop(KNOCKED_ONCE);
    
    if(gate->query_open())
    {
	remove_alarm(cg_aid);
	cg_aid = set_alarm(3.0, 0.0, close_gate);
    }
}

void 
close_gate() 
{ 
    cg_aid = 0;
    other_gate = gate->query_other_door();
    
    if(!gate->query_open())
	return;
    
    gate->do_close_door("The iron doors swing back to close the gate again.\n");
    other_gate->do_close_door("The iron doors of the gate swing back to close the gate again.\n");
    
    gate->do_lock_door("The beam moves back into position, blocking the gate.\n");
    other_gate->do_lock_door("You hear something heavy moving on the other side of the gate.\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (living(ob)) {
	WROOM->enter_ingate(ob,from);
    }
}

public object
query_gate() { return gate; }

public void
set_igroom(string str)
{
  IGROOM = str;
}

public void set_groomdir(string str) { GROOMDIR = str; }
public void set_gfile2(string str) { GFILE2 = str; }
public void set_ofile(string str) { OFILE = str; }
public void set_grtoig(string *str) { GRTOIG = str; }
public void set_gdir(string str) { GDIR = str; }
public void set_wroom(string str) { WROOM = str; }
