/*
 * A horn to make a sound. :)
 *
 * Aridor, 09/95
 *
 */
#include "local.h"
#include <macros.h>

inherit "std/container";

int num_gold = 0;


void
create_container()
{
    set_name("horn");
    set_adj("brass");
    set_short("brass horn");
    set_long("This is a brass horn. It is about a foot in diameter " +
	     "and turned around once to make a loop. One end of the " +
	     "tube forms a fairly large opening and the other end " +
	     "has a small opening.\n");
    add_prop(CONT_I_WEIGHT,1000);
    add_prop(CONT_I_VOLUME,1111);
    add_prop(OBJ_I_VALUE,2500);
    add_prop(CONT_I_HIDDEN,1);
    add_prop(CONT_I_MAX_VOLUME,5000);
    add_prop(CONT_I_MAX_WEIGHT,5000);
    add_prop(CONT_I_RIGID,1);
}

void
init()
{
    ADA("blow");
    ADA("stir");
    ADA("shake");
}

int
blow(string str)
{
    int i, size;
    mixed *exits;

    if (!str)
      return 0;
    
    if (!id(str))
      return 0;
    
    write("You blow the brass horn with all your force.\n");
    say(QCTNAME(TP) + " blows into a brass horn.\n");
    tell_room(E(TP),"A loud, deep and even sound comes from the horn.\n");
    
    exits = E(TP)->query_exit();
    size = sizeof(exits);
    for(i=0;i<size;i+=3)
      tell_room(exits[i],"A loud, deep and even sound from a horn is " +
		"coming from somewhere nearby.\n");
    
    return 1;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    set_alarm(1.0,0.0,"handle_input",ob,from);
}

void
handle_input(object ob, object from)
{
    if (ob->id("mishakalfeather"))
      {
	  return;
      }
    if (ob->id("dragon acid"))
      {
	  /* test black dragon quest here */
	  /* test gnome quest here */
	  if (!P("mishakalfeather",TO))
	    {
		tell_object(from,"The acid runs out of the bottom of the " +
			    "horn, dropping onto your foot! OUCH!\n");
		from->heal_hp(-40);
		from->do_die(ob);
	    }
	  ob->remove_object();
	  seteuid(getuid(TO));
	  clone_object("empty_bottle")->move(from);
	  return;
      }
    if (ob->id("kitring"))
      {
	  if (!P("mishakalfeather",TO))
	    {
		tell_object(E(TO),"The ring clanks in the horn, and " +
			    "suddenly the horn is much smaller than before. " +
			    "In no time, the horn has melted and luckily " +
			    "you retrieve the ring again.\n");
		set_alarm(0.1,0.0,"remove_object");
		return;
	    }
	  if (!P("dragon acid",TO))
	    {
		tell_object(E(TO),"The ring clanks in the horn, only " +
			    "softened a little by the feather, when " +
			    "the horn suddenly becomes much heavier!\n");
		seteuid(getuid(TO));
		if (random(10) <= num_gold++)
		  clone_object("/d/Krynn/solamn/thief/obj/goldpiece")->move(TO);
		return;
	    }
      }
    
}

void
get_result(string ob)
{
    object obj;

    seteuid(getuid(TO));
    obj = clone_object(ob);
    if (obj->move(E(TO)))
      obj->move(E(E(TO)));
    tell_object(E(TO),"The horn is suddenly tranformed and " +
		LANG_ASHORT(obj) + " appears!\n");
    set_alarm(0.1,0.0,"remove_object");
}

void
do_it_failed(string str)
{
    string failure;

    write("You " + str + ".\n");
    write("Something seems to happen with the horn.\n");
    failure = ({FEATHER,MAGICIAN,HORN,RANDOM_ACID})[random(4)];
    set_alarm(15.0,0.0,"get_result",failure);
}

void
do_it_ok(string str)
{
    object *oinside = ({ P("kitring",TO),
			  P("dragon_acid",TO),
			  P("feather",TO)  });

    if (oinside != all_inventory(TO))
      do_it_failed(str);

    write("You " + str + ".\n");
    write("Something seems to happen with the horn.\n");
    set_alarm(15.0,0.0,"get_result",MAGIC_HORN);
}

int
shake(string str)
{
    int i;
    object what;
    string extra;
    int shake, how;

    NF("Shake what?\n");
    if (!str)
      return 0;

    i = parse_command(str,E(TP),"[the] %o %w",what,extra);

    if (what != TO)
      return 0;

    if (!TP->query_prop(HORN_I_READ_RECIPE))
      {
	  do_it_failed("shake the horn");
	  return 1;
      }

    shake = TP->query_prop(HORN_I_SHAKE);
    how = TP->query_prop(HORN_I_HOW);

    if (shake != 1)
      {
	  do_it_failed("shake the horn");
	  return 1;
      }
    
    if (extra == "violently" && how == 2)
      do_it_ok("shake the horn violently");
    else if (extra == 0 && how == 1)
      do_it_ok("shake the horn");
    else if (extra == "carefully" && how == 0)
      do_it_ok("shake the horn carefully");
    else
      do_it_failed("shake the horn");

    return 1;
}

int
stir(string str)
{
    int i;
    object what;
    string extra;
    int shake, how;

    NF("Stir what?\n");
    if (!str)
      return 0;

    i = parse_command(str,E(TP),"[the] %o %w",what,extra);

    if (what != TO)
      return 0;

    if (!TP->query_prop(HORN_I_READ_RECIPE))
      {
	  do_it_failed("stir the horn");
	  return 1;
      }

    shake = TP->query_prop(HORN_I_SHAKE);
    how = TP->query_prop(HORN_I_HOW);

    if (shake != 0)
      {
	  do_it_failed("stir the horn");
	  return 1;
      }
    
    if (extra == "violently" && how == 2)
      do_it_ok("stir the horn violently");
    else if (extra == 0 && how == 1)
      do_it_ok("stir the horn");
    else if (extra == "carefully" && how == 0)
      do_it_ok("stir the horn carefully");
    else
      do_it_failed("stir the horn");

    return 1;
}
