inherit "/std/weapon";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include "/d/Kalad/std/combat.h"

/* A missile launcher base. You can set it to be a bow, crossbow or
 * sling. Use create_missile_launcher and set the name and short. 
 * set the base hit and pens. They cannont exceed 40. Set the 
 * holder type, set the reload time, and the damage type. The default
 * is impale, but if you have a rock and sling, you could use bludgeon.
 * Works just like any other weapon, using SS_WEP_MISSILE skill.
 *
 * Sarr 20.Jul.97 
 */

// Bool, we have somethign loaded or not
int loaded;

int reload; // Reload counter

int reload_time; // How many rounds till we are reloaded

// The arrow inside, loaded
object current_arrow;

// The storage room for this missile
object store_room;

// The ammunition holder type
string holder_type;
string ammo_type; // The ammunition type (arrow,bolt, rock, etc)


/* Set the holder type that holds the ammunition for this missile 
 * weapon. Case for crossbows, quiver for bows, bag for slings, etc 
 */

void
set_missile_type(string str)
{
    ammo_type = str;
}
string
query_missile_type()
{
    return ammo_type;
}
void
set_holder_type(string str)
{
    holder_type = str;
}

/* Set the amount of rounds to wait for it to reload. One every i rounds.
 */
void
set_reload_time(int i)
{
    reload_time = i;
}

int
query_reload_time()
{
    return reload_time;
}

object
query_store_room()
{
    return store_room;
}

void
create_missile_launcher()
{
}


int
query_missile_launcher()
{
    return 1;
}

void
create_weapon()
{
    set_wt(W_MISSILE);
    set_dt(W_IMPALE);

    set_hands(W_BOTH);

    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(40,35) + random(50));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(28,W_MISSILE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);

    loaded = 0;
    reload = 0;
    seteuid(getuid());
    store_room = clone_object("/std/room");

    create_missile_launcher();
}

void
remove_object()
{
    store_room->remove_object();
    ::remove_object();
}

// Try and find an arrow in a case, and return it
// Return an empty object if we failed

object
reload(object me)
{
    int i;
    object *holders,arrow, dummy;

    set_this_player(me);
    holders = FIND_STR_IN_OBJECT(holder_type,TP);

    for(i=0;i<sizeof(holders);i++)
    {
	arrow = holders[i]->get_arrow(TP);
	if(arrow->query_missile_type() != ammo_type)
	{
	    write("You cannot use a "+arrow->short()+" with your "+
	      short()+".\n");
	    loaded = 0;
	    reload = 0;
	    return dummy;
	}

	if(objectp(arrow))
	    break;
    }

    if(!objectp(arrow))
    {
	loaded = 0;
	reload = 0;
	return arrow;
    }
    return arrow;
}

/* Ok, when we are fighting with this weapon, we have to see if we can 
 * hit our target. Check for arrows, face-to-face, etc
 */
int
try_hit(object enemy)
{

    set_this_player(query_wielded());

    if( (TP->query_attack())->query_attack() == TP)
    {
	TP->notify_face_to_face(TO); // These are npc hooks
	write("You can't use this weapon face to face with your enemy.\n");
	return 0;
    }

    /* Is our weapon loaded with an arrow? If so, empty it and return 
     * with a success
     */
    if(loaded == 1)
    {
	loaded = 0;
	return 1;
    }


    if(reload == -1)
	return 0; // We are in the middle of manual reload, let that finish

    /* If we are not loaded, then we try and reload with a reload 
     * routine. */

    // If we have reload value of 0, then we start at the begining of
    // our routine.
    if(reload == 0)
    {
	current_arrow = reload(TP); // Load it into current object arrow

	// Did we have another arrow in our case ?
	if(objectp(current_arrow))
	    write("You start to reload your "+short()+" with a "+
	      current_arrow->short()+".\n");
	else
	{  // Out of ammunitions!
	    write("You have no more ammunition for your "+short()+"!\n");
	    TP->notify_out_of_arrows(TO); // These are npcs hooks
	    return 0;
	}
    }

    reload += 1; // Incriment the round

    // Have we accumilated enough rounds to fully load an arrow? 
    if(reload == reload_time)
    {
	write("Your "+short()+" is reloaded with a "+
	  current_arrow->short()+".\n");
	TP->tell_watcher(QCTNAME(TP)+" reloads "+HIS(TP)+" "+short()+
	  " with a "+current_arrow->short()+".\n");
	current_arrow->move(store_room);
	set_hit( query_hit() + current_arrow->query_hit() );
	set_pen( query_pen() + current_arrow->query_pen() );
	TP->update_weapon(TO);
	loaded = 1; // Loaded and ready sir!
	reload = 0; // Reload time back to 0
    }
    return 0; // During reloading time, we don't hit anything
}

// Reloading routine messages
void
reload_one(object ob)
{
    set_this_player(ob);

    write("You draw back the string of your "+short()+".\n");
    say(QCTNAME(TP)+" draws back the string of "+HIS(TP)+" "+short()+".\n");
}
void
reload_two(object ob)
{
    set_this_player(ob);

    write("You place the "+current_arrow->short()+" into your "+
      short()+".\n");
    say(QCTNAME(TP)+" starts to place the "+current_arrow->short()+" into "+
      HIS(TP)+" "+short()+".\n");
}

// This is called with the manual-reloading routine. When we have finished
// reloading.
void
finish_reload(object ob)
{
    set_this_player(ob);
    if(!objectp(current_arrow))
    {
	reload = 0;
	write("You have lost the arrow you were reloading somehow.\n");
	return;
    }

    write("You have loaded your "+short()+" with a "+current_arrow->short()+".\n");
    say(QCTNAME(TP)+" has loaded "+HIS(TP)+" "+short()+" with a "+
      current_arrow->short()+".\n");

    current_arrow->move(store_room);

    set_hit( query_hit() + current_arrow->query_hit() );
    set_pen( query_pen() + current_arrow->query_pen() );
    TP->update_weapon(TO);
    loaded = 1;
    reload = 0;
}


/* This is the manual reload option command. 
 * It can't be used in normal combat. It will take longer here to reload
 * than in normal combat rounds, so no one can abuse it
 */
int
do_reload(string str)
{
    object *obs;
    NF("You can't reload while in combat, you must let it auto-reload.\n");
    if(TP->query_attack())
	return 0;

    NF("Reload what?\n");
    obs = FIND_STR_IN_OBJECT(str,TP);
    if(!sizeof(obs))
	return 0;
    if(obs[0] != TO)
	return 0;

    NF("You are already reloading!\n");
    if(reload == -1)
	return 0;
    NF("The "+short()+" is already loaded with a "+current_arrow->short()+"!\n");
    if(loaded == 1)
	return 0;

    NF("You have no more ammunition for your "+short()+"!\n");
    current_arrow = reload(TP); // Load arrow
    if(!objectp(current_arrow))
	return 0;

    write("You draw a "+current_arrow->short()+" from your "+
      holder_type+".\n");
    say(QCTNAME(TP)+" draws a "+current_arrow->short()+" from "+HIS(TP)+
      " "+holder_type+".\n");

    reload = -1; // This lets us know we are in the middle of manual load

    set_alarm(15.0,0.0,&finish_reload(TP));
    set_alarm(10.0,0.0,&reload_two(TP));
    set_alarm(5.0,0.0,&reload_one(TP));
    return 1;
}

int
do_fire(string str)
{
    object *obs;
    string what;
    mixed hr;
    int pen;
    NF("You must be wielding a missile launcher.\n");
    if(!sizeof(TP->query_weapon(-1)) )
	return 0;
    if(TP->query_weapon(W_BOTH) != TO)
	return 0;
    NF("You can't fire in combat, you must let it auto-fire.\n");
    if(TP->query_attack())
	return 0;
    NF("You can't see in this room.\n");
    if(!CAN_SEE_IN_ROOM(TP))
	return 0;
    obs = PARSE_THIS(str,"[at] [the] %l");
    NF("Fire at who?\n");
    if(!sizeof(obs))
	return 0;
    what = c_can_attack(obs[0],query_verb());
    if (what)
    {
	NF(C(what));
	return 0;
    }
    NF("The "+short()+" is not loaded.\n");
    if(loaded == 0)
	return 0;
    if(CAN_SEE(obs[0],TP))
	TP->attack_object(obs[0]);

    pen = F_PENMOD(query_pen(),TP->query_skill(SS_WEP_MISSILE));
    if(!(TP->query_combat_object()->cb_tohit(0,query_hit(),obs[0])))
	pen = -1;

    if(CAN_SEE(obs[0],TP))
	hr = obs[0]->hit_me(pen,W_IMPALE, TP, -1);
    else
	hr = obs[0]->hit_me(pen,W_IMPALE,obs[0], -1); // don't start attack
    if(TP->query_prop(OBJ_I_HIDE))
	TP->change_prop(OBJ_I_HIDE,TP->query_prop(OBJ_I_HIDE) - random(10));

    did_hit(0,hr[1],hr[0],obs[0],W_IMPALE,hr[2],hr[3]);

    return 1;
}

int
do_unload(string str)
{
    object *obs;
    NF("You can't unload arrows manualy during combat!\n");
    if(TP->query_attack())
	return 0;

    NF("Unload what?\n");
    obs = FIND_STR_IN_OBJECT(str,TP);
    if(!sizeof(obs))
	return 0;
    if(obs[0] != TO)
	return 0;

    NF("The "+short()+" is already empty!\n");
    if(loaded == 0)
	return 0;

    NF("Strange, there is no arrow in your "+short()+"....\n");
    if(!objectp(current_arrow))
	return 0;
    write("You pop out the "+current_arrow->short()+" from your "+
      short()+".\n");
    say(QCTNAME(TP)+" pops out the "+current_arrow->short()+" from "+
      HIS(TP)+" "+short()+".\n");
    if(current_arrow->move(TP) != 0)
    {
	write("Strange, for some reason, it failed to unload.\n");
	return 1;
    }
    loaded = 0;
    reload = 0;
    return 1;
}

void
init()
{
    ::init();
    add_action(do_reload,"reload");
    add_action(do_fire,"fire");
    add_action(do_unload,"unload");
}

// This is where we fire the arrow when in combat!
varargs int
did_hit(int aid,string hdesc,int phurt, object enemy, int dt, int phit,
  int dam)
{
    object me;
    string how,ehow;
    me = query_wielded();
    loaded = 0;    

    // If we're here, we already did the arrow damage. Now we just take
    // care of the messages. So reduce hit and pen from arrow.
    set_hit( query_hit() - current_arrow->query_hit() );
    set_pen( query_pen() - current_arrow->query_pen() );
    me->update_weapon(TO);

    if(!objectp(me) || !objectp(enemy))
    {
	current_arrow->remove_object(); // Remove arrow before exit
	return 0;
    }

    if(phurt == -1 || phurt == -2)
    {
	if(interactive(me))
	    tell_object(me,"You fire off a "+current_arrow->short()+
	      " from your "+short()+" at "+
	      enemy->query_the_name(me)+", but just narrowly miss "+
	      HIM(enemy)+"!\n");
	if(interactive(enemy))
	    tell_object(enemy,me->query_The_name(enemy)+" fires off a "+
	      current_arrow->short()+" at you from "+HIS(me)+" "+
	      short()+", but just "+
	      "narrowly misses you!\n");
	me->tell_watcher(QCTNAME(me)+" fires off a "+current_arrow->short()+
	  " at "+QTNAME(enemy)+
	  " from "+HIS(me)+" "+short()+", but just narrowly misses "+
	  HIM(enemy)+"!\n",enemy);
	current_arrow->remove_object();
	return 1;
    }

    switch(phurt)
    {
    case 0..4:
	how = "bouncing off "+HIS(enemy)+" "+hdesc+
	" with little effect";
	ehow = "bouncing off your "+hdesc+" with little effect";
	break;
    case 5..9:
	how = "grazing "+HIS(enemy)+" "+hdesc+" somewhat";
	ehow = "grazing your "+hdesc+" somewhat";
	break;
    case 10..19:
	how = "piercing "+HIS(enemy)+" "+hdesc+" solidly";
	ehow = "piercing your "+hdesc+" solidly";
	break;
    case 20..29:
	how = "piercing "+HIS(enemy)+" "+hdesc+" badly";
	ehow = "piercing your "+hdesc+" badly";
	break;
    case 30..49:
	how = "impaling "+HIS(enemy)+" "+hdesc+" severely";
	ehow = "impaling your "+hdesc+" badly";
	break;
    case 50..69:
	how = "slaming into "+HIS(enemy)+" "+hdesc+" with "+
	"ruthless force";
	ehow = "slaming into your "+hdesc+" with ruthless force";
	break;
    case 70..89:
	how = "slaming into "+HIS(enemy)+" "+hdesc+" with "+
	"lethal force";
	ehow = "slaming into your "+hdesc+" with lethal force";
	break;
    default:
	how = "flying through "+HIS(enemy)+" "+hdesc+
	" and out the other side";
	ehow = "flying through your "+hdesc+" and out the other side";
    }


    if(interactive(me))
	tell_object(me,"You fire off a "+current_arrow->short()+
	  " at "+enemy->query_the_name(me)+
	  " and it flies true, "+how+"!\n");
    if(interactive(enemy))
	tell_object(enemy,me->query_The_name(enemy)+" fires off a "+
	  current_arrow->short()+" "+
	  "at you and it flies true, "+ehow+"!\n");
    me->tell_watcher(QCTNAME(me)+" fires off a "+current_arrow->short()+
      " at "+QTNAME(enemy)+" and it flies true, "+how+"!\n",enemy);

    if(current_arrow->query_poison_shadow()) // poison arrow ?
    {
	current_arrow->hit_poison_missile(enemy,query_wielded());
    }

    current_arrow->remove_object(); // get rid of arrow
    return 1;
}

