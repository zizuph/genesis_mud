/*
 *      /d/Gondor/minas/lib/outgate.c
 *
 *      Modification log:
 *
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/minas/lib/archery";
inherit "/d/Gondor/common/lib/binbit";

#include <composite.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

#define KNIGHT_S_GUILD_NAME "Solamnian Knights"
#define DID_ATTACK_MT_GATES  "_attacked_mt_gate"
#define ARCHERY_PANIC  "_archery_panic"
#ifndef DEBUG
#define DEBUG 1
#endif
#ifdef DEBUG
#define DEBUG_MSG(p,x) find_player((p))->catch_msg("#outgate.c#" + (x) + "\n")
#else
#define DEBUG_MSG(p,x)
#endif

/* 
 * Prototypes:
 */
public int     do_knock(string str);
public string  long_func();

/*
 * Global variables:
 */
object  patrol,
        gate,
        signpost,
        other_gate,
        officer,
       *guards;
int     oc,
        cg_aid,
        ga_aid;
string  gfile1,
        ofile,
        ogroom,
        igroom,
        igdir,
        gdir,
       *grtoog,
        gopen,
        gclosed,
        gatename;

void    set_gfile1(string str) { gfile1 = str; }
void    set_ofile(string str) { ofile = str; }
void    set_ogroom(string str) { ogroom = str; }
void    set_igroom(string str) { igroom = str; }
void    set_igdir(string str) { igdir = str; }
void    set_gdir(string str) { gdir = str; }
void    set_grtoog(string *str) { grtoog = str; }
void    set_gopen(string str) { gopen = str; }
void    set_gclosed(string str) { gclosed = str; }
void    set_gatename(string str) { gatename = str; }
void    close_gate();
void    prepare_guard_attack(object *enemy);
void    guard_attack(object *enemy);

int
hook_check_attacked_here(object pl)
{
    if (pl->query_prop(DID_ATTACK_MT_GATES) == TO)
        return 1;
    else
        return 0;
}

void
hook_log_kill(object pl)
{
    write_file(LOG_DIR + "goodkill",pl->query_name()+" died "+
        "by archery fire outside the Rammas Echor, on "+ctime(time())+".\n");
}

void
create_outgate()
{
    // dummy gate to get the file load w/o runtime error
    set_gfile1("/d/Gondor/anorien/pelennor/obj/sgate1");
}

nomask void
create_gondor()
{
    set_short("before the gate");
    set_long(long_func);
    create_outgate();
    gate = clone_object(gfile1);
    gate->move(TO);
    (ogroom)->load_me();
    (igroom)->load_me();
}

void 
init()
{
    ::init();
    add_action(do_knock, "knock");
    add_action(do_knock, "pound");
}

public string 
long_func()
{
    int gate_open;
    seteuid(getuid(TO));
    if (!gopen) 
	gopen = "You are standing before an open gate, somewhere undescribable.\n";
    if (!gclosed) 
	gclosed = "You are standing before a closed gate, somewhere undescribable.\n";
    gate_open = gate->query_open();
    if (gate_open) 
	return BS(gopen);
    return BS(gclosed);
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

void 
reset_room()
{
    int     s, i;

    oc = 0;
    if (officer && present(officer,TO) && !officer->query_attack())
	officer->move_living(igdir+" through the gate",ogroom);
    if (s = sizeof(guards))
    {
	while(i < s)
	{
	    if (guards[i] && present(guards[i],TO) && !guards[i]->query_attack())
		guards[i]->move_living(igdir+" through the gate",ogroom);
	    i++;
	}
    }
}

varargs void 
get_guards_ready(object *enemy)
{
    tell_room(TO,BSN("From the top of the walls, someone shouts: Alarm! Enemies at the gate!"));
    tell_room(gate->query_other_room(),BSN("From the top of the walls, someone shouts: Alarm! Enemies at the gate!"));
    tell_room(TO,BSN("You hear more loud shouts from the top of the walls and on the other side of the gate!"));
    tell_room(gate->query_other_room(),
        BSN("You hear more loud shouts from the top of the walls and on the other side of the gate!"));
    if(!sizeof(enemy))
        enemy = ({TP});
    set_alarm(rnd()*4.0, 0.0, &prepare_guard_attack(enemy));
}

static void
suspicious_to_entry(object pl)
{
    string  fname = "stranger";

    if (IS_DUNADAN(pl))
	fname = "dunadan!\n\tYou have lost the trust of the Steward!";
    tell_room(TO, "From the top of the wall, someone shouts: " +
	"Turn away, "+fname+"!\n\tGondor is at War, and you are not welcome here now!\n");
    tell_room(gate->query_other_room(),
	      BSN("You hear someone shouting from somewhere above."));
}

void
laugh_at_newbie(object pl)
{
    tell_room(TO,BSN("From the top of the wall you hear mocking laughter."));
    tell_room(TO,BSN("Then someone shouts: Go away, kid! Come back when you are older!"));
    tell_room(gate->query_other_room(),
	      BSN("You hear laughter and shouting from above."));
}


public int 
do_knock(string str)
{
    int     war,
	    fof;
    object *enemy,
	    token;
    string  fname;
    string  vb = QVB;
 
    NF(CAP(vb)+" on what?\n");
 
    if ((str != "gate") && (str != "on gate"))
	return 0;

    TP->reveal_me(1);

    other_gate = gate->query_other_door();

    if (gate->query_open())
    {
	write("You "+vb+" on the open gate. Stupid, isn't it?\n");
	say(QCTNAME(TP)+" "+vb+"s on the open gate. Stupid, isn't it?\n");
	return 1;
    }

    write("You "+vb+" on the great iron gate.\n");
    say(QCTNAME(TP)+" "+vb+"s on the great iron gate.\n");

    enemy = check_enemies();
    war = (find_object(CLOCK))->query_war();

    if ( ((fof = query_friend_or_foe(TP)) > (war - 1)) &&
	 !sizeof(enemy) )
    {
	fname = "some " + TP->query_race_name();
#ifndef NEW_RANGERS_OPEN
	if (IS_RANGER(TP) &&
	    objectp(token = present("ranger_guild_object", TP)) &&
	    token->query_worn())
	{
	    fname = ranger_title(TP);
	}
#endif
#ifdef NEW_RANGERS_OPEN
    if (RANGERS_MEMBER(TP))&&
        objectp(token = present("ranger_guild_object", TP)) &&
        token->query_worn())
    {
        fname = ranger_title(TP);
    }
#endif
	else if (IS_DUNADAN(TP)) 
	    fname = "a Dunadan";
	else if (TP->query_guild_name_occ() == KNIGHT_S_GUILD_NAME)
	    fname = "some knight";
	tell_room(TO,BSN("From the top of the gatehouse, someone shouts: Open the gate, "
			 +fname+" wants to enter!"));
	tell_room(gate->query_other_room(),
	    BSN("From the top of the gatehouse, someone shouts: Open the gate, "
		+fname+" wants to enter!"));
	    
	gate->do_unlock_door("You hear something heavy moving on the other side of the gate.\n");
	other_gate->do_unlock_door("Suddenly, the wooden beam blocking the door starts moving.\n");
	gate->do_open_door("The gate opens as the iron doors swing inwards.\n");
	other_gate->do_open_door("The gate opens as the iron doors swing inwards.\n");
	cg_aid = set_alarm(20.0, 0.0, close_gate);
    }
    else if (sizeof(enemy))
    {
	tell_room(TO, BSN("From atop the gatehouse someone shouts: "
			  + "Get thee hence, " + TP->query_nonmet_name() + "! "
			  + "There are enemies near!"));
	get_guards_ready(enemy);
    }
    else
    {
	if ((fof == -1) && (TP->query_average_stat() < 30))
	    laugh_at_newbie(TP);
	else if (fof == -1)
	    get_guards_ready(enemy);
	else if ((fof == 0) && war)
	    suspicious_to_entry(TP);
    }
    return 1;
}

void 
close_gate()
{
    remove_alarm(cg_aid);
    cg_aid = 0;
    gate->query_other_room()->close_gate();
}

void 
close_gate_to_stop_invaders(object one_enemy)
{
    object *enemy;
    one_enemy->catch_msg("When you try to enter the gate, you hear a shout from inside.\n");
    tell_room(TO,"When "+QTNAME(one_enemy)+" tries to enter the gate, " +
        "you hear a shout from inside.\n", one_enemy);
    tell_room(TO,"Someone shouts: Close the gate! Invaders!\n");
    close_gate();
    enemy = ({one_enemy});
    get_guards_ready(enemy);
}

void set_oc(int i) { oc = i; }

int clone_officer()
{
  int    i;

  if(!officer)
  {
    if ((oc > 2) || !random(2))
    {
        start_archers(0);
        return 0;
    }
    else
    {
      officer = clone_object(ofile);
      officer->set_name("officer");
      officer->arm_me();
      officer->set_gate(ogroom);
      (ogroom)->reset_room();
      oc++;
    }
  }
  else
  {
    if(officer->query_attack())
      return 0;
    tell_room(ENV(officer), QCTNAME(officer) + " leaves.\n");
  }
  officer->move_living("M",ogroom);
  tell_room(ogroom,CAP(LANG_ADDART(officer->query_nonmet_name())) + " arrives running!\n");
  officer->command("shout Alarm! Enemies at the gates!");
  officer->command("shout All guards follow me!");
  guards = ENV(officer)->query_guards();
  while(i < sizeof(guards))
  {
    if(guards[i])
      officer->team_join(guards[i]);
    i++;
  }
  return 1;
}

void
prepare_guard_attack(object *enemy)
{
  int    i;

  tell_room(TO,"You hear people running and shouting on the other side of the gate!\n");
  if (clone_officer() && !ga_aid)
    ga_aid = set_alarm(rnd()*5.0 + 2.0, 0.0, &guard_attack(enemy));
}

void
guard_attack(object *enemy)
{
    int    s,
           i,
           n,
           flag = 0;

    remove_alarm(ga_aid);
    ga_aid = 0;
    DEBUG_MSG("elessar", "Guard_attack initiated.");
    enemy -= ({ 0 });
    if (!pointerp(enemy) || !(s = sizeof(enemy)))
    {
        DEBUG_MSG("elessar", "No enemy in guard_attack.");
        return;
    }

    i = 0;
    while(i < s) 
    {
        if (present(enemy[i],TO) && query_friend_or_foe(enemy[i]) == -1) 
            flag = 1; 
        i++;
    }

    if (!flag)
    {
        DEBUG_MSG("elessar", "No enemy present in gate attack.");
        return;
    }

    if (!officer)
    {
        DEBUG_MSG("elessar", "No officer left at gate!");
        return;
    }

    DEBUG_MSG("elessar", "Officer should now be moving.");

    while (n < sizeof(grtoog))
    {
        officer->command(grtoog[n]);
        n++;
    }
    officer->command("shout Open the gate!");
    tell_room(TO, "The iron doors of the gate swing open. \n");
    tell_room(ENV(officer), "The iron doors of the gate swing open. \n");

    officer->move_living(gdir+" through the gate",TO);
    officer->command("shout For Gondor and the City!");
    officer->command("kill "+enemy[0]->query_real_name());
    if (sizeof(enemy) > random(3)+2)
    {
        officer->command("shout Archers! We need support!");
        set_alarm(3.0, 0.0, start_archers);
        DEBUG_MSG("elessar", "Officer called for archers.");
    }
    i = 0;
    while (i < sizeof(guards))
    {
        if(guards[i])
        {
            guards[i]->move_living(gdir+" through the gate",TO);
            if (!random(3))
                guards[i]->command("shout For Gondor!");
                guards[i]->command("kill " + ONE_OF_LIST(enemy)->query_real_name());
        }
        i++;
    }
    tell_room(gate->query_other_room(), "The gate closes again. \n");
    tell_room(ENV(officer), "The gate closes again. \n");
}

public void leave_inv(object ob, object to)
{
  ::leave_inv(ob, to);

  if(!ob || !to)
    return;

  if(!living(ob))
    return;

  ob->remove_prop(ARCHERY_PANIC);

  if(gate->query_open())
  {
    if (cg_aid)
    {
        remove_alarm(cg_aid);
        cg_aid = 0;
    }
    cg_aid = set_alarm(1.0, 0.0, close_gate);
  }
}

public void 
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!ob || !from) return;
    if (!living(ob)) return;
    if (ob->query_prop(DID_ATTACK_MT_GATES))
	start_archers(1);
}

/*
 * int query_friend_or_foe(object pl)
 * returns: -1 = goblins, morgul mages, angmarim, vampires, align < -250
 *           0 = others
 *           1 = elves, rangers, paladines, align > 750
 */
varargs int
query_friend_or_foe(mixed pl)
{
    int     fof;

    if (stringp(pl))
        pl = find_living(LOW(pl));
    else if (!objectp(pl))
        pl = TP;

    if (!objectp(pl))
        return 0;

    if (M_TIRITH_MASTER->query_enemy(pl->query_real_name(),
        pl->query_race()))
        return -1;
  
    if (pl->query_prop(DID_ATTACK_MT_GATES))
        return -1;

    fof = ::query_friend_or_foe(pl);

    // We make this extra check to permit dunedain to enter the city
    // during war time even if they do not have an alignment in excess
    // of 750:
    if ( (pl->query_guild_name_race() == DUNEDAIN_S_GUILD_NAME) &&
	 (fof >= 0) && (pl->query_alignment() > 250)) 
	return 1;

    return fof;
}
