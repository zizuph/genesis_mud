inherit "/std/object";

#include "/d/Emerald/defs.h"

void make_fire(mixed args);
void make_correct_fire(mixed args);
void start_false_fire();
void start_true_fire();

void
create_object()
{
  set_short("wood");
  set_name("wood");
  set_long("This bundle of wood was collected in a dry forest, it may "+
	"be useful for starting a fire.\n");

  add_prop(OBJ_I_VALUE, 2);
  add_prop(OBJ_M_NO_SELL, 1);
}

void
start_false_fire()
{
  notify_fail("For some reason you can't start a fire here.\n");
  if(!ENV(TO)->query_prop(ROOM_I_INSIDE))
  	return 0;

  TO->add_prop(OBJ_M_NO_GET, "Are you stupid? It's on fire!n");
  set_alarm(1.0, 0.0, "make_fire", ({ TP, 1 }) );
}

void
start_true_fire()
{
  notify_fail("For some reason you can't make the fire here.\n");
  if(!ENV(TO)->query_prop(ROOM_I_INSIDE))
	return 0;

  if(MASTER_OB(ENV(TO)) == (VILLAGE_DIR + "ground") 
    set_alarm(1.0, 0.0, "make_correct_fire", ({ TP, 1 }) );
  else
    set_alarm(1.0, 0.0, "make_fire", ({ TP, 1 }) );
} 

void
make_fire(mixed args)
{
  object ob;
  int time;

  if (sizeof(args) != 2)
      return;

  ob = args[0];
  time = args[1];

  switch(time) 
  {
    case 1:
    ob->catch_msg("You put the wood on the floor and set light to it.\n");
    tell_room(ENV(TO), QCTNAME(ob)+" puts some wood on the floor and "+
	"lights it.\n", ob);
    break;

    case 2:
    tell_room(ENV(TO), "The flames start to take hold of the wood.\n");
    break;

    case 3:
    tell_room(ENV(TO), "The wood has become a roaring fire now, you step "+
	"back a little.\n");
    break;

    case 4:
    tell_room(ENV(TO), "The flames dies down to a small flicker.\n");
    break;

    case 5:
    tell_room(ENV(TO), "Embers are left now.\n");
    setuid();
    seteuid(getuid());
    clone_object(VILLAGE_DIR + "obj/embers")->move(this_object(), 1);
    TO->remove_object();
    break;
  
    default:
    /* Give a default message in case the program goes wrong. */
    tell_room(ENV(TO), "The flames flicker around the wood.\n");
    break;
  }
  set_alarm(10.0, 0.0, "make_fire", ({ ob, time + 1 }) );
}

void
make_correct_fire(mixed args)
{
  object ob;
  int time;

  if (sizeof(args) != 2)
      return;

  ob = args[0];
  time = args[1];

  switch(time) 
  {
    case 1:
    ob->catch_msg("You put the wood on the floor and set light to it.\n");
    tell_room(ENV(TO), QCTNAME(ob)+" puts some wood against the pillar and "+
	"lights it.\n", ob);
    break;

    case 2:
    tell_room(ENV(TO), "The flames start to take hold of the wood.\n");
    break;

    case 3:
    tell_room(ENV(TO), "The wood has become a roaring fire now, you step "+
	"back a little.\n");
    break;

    case 4:
    tell_room(ENV(TO), "You hear a loud 'crack' as the pillar shatters. You "+
	"can see a glint of copper in the pillar!\n");
    break;

    case 5:
    tell_room(ENV(TO), "Embers are left now.\n");
    setuid();
    seteuid(getuid());
    clone_object(VILLAGE_DIR + "obj/embers")->move(this_object(), 1);
    ENV(TO)->start_room_move();
    TO->remove_object();
    break;
  
    default:
    /* Give a default message in case the program goes wrong. */
    tell_room(ENV(TO), "The flames flicker around the wood.\n");
    break;
  }
  set_alarm(10.0, 0.0, "make_correct_fire", ({ ob, time + 1 }) );
}
