/* Modification of the hoopak originally created by Erine /12/11/94
/* for the hoopak seller in Kendermore.
/* Code from Trapspringer's magical hoopak included in the wield routine
/* Modified by Gwyneth, July 1999
/* Fixed by Milan, 18.4.2001
*/

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
//#include "/sys/global/cmdparse.c"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"

int alload, alaim, alshoot;

void
create_weapon()
{
    seteuid(getuid(TO));
    set_name(({"hoopak","_hoopak_"}));
    set_adj("yew");
    add_adj("kender");
    add_name("staff");
    set_short("yew hoopak");
    set_pshort("yew hoopaks");
    set_long("@@long_desc@@");
    set_default_weapon(15,15,W_POLEARM, W_BLUDGEON | W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(35, W_POLEARM));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40,35) + random(100)); 
    set_wf(TO);
}

void
kender_wield()
{
    if(E(TO) != wielder)
        return;
    wielder->catch_tell("You feel at ease with the hoopak as you grip " + 
        "your fingers around it. You give it a little swing to test it " + 
        "out.\n");
    wielder->command("$swing hoopak");

    set_hit(40);
    set_pen(35);
    wielder->update_weapon(TO);
}

void
default_wield()
{
    if(E(TO) != wielder)
        return;

    wielder->catch_tell("You feel somewhat foolish wielding " +
      "a weapon designed for kender.\n");
    set_hit(15);
    set_pen(15);
    wielder->update_weapon(TO);
}

mixed
wield(object what)
{
    wielder = TP;

    if(TP->query_race_name() == "kender")
        set_alarm(1.0, 0.0, kender_wield);
    else
        set_alarm(1.0, 0.0, default_wield);
    return 0;
}

string 
long_desc()
{
    string ken; /* to add_desc */
    /* later it will be connected with function wield() so previous */
    /* wielder will be mentioned <not by name ofcourse> */
    object owner; // just to define where hoopak is. I wonder if it will work

    owner=E(TO);
    ken = "creator must have been your kin.\n";

    if(living(owner) != 1)
    {
	ken = "former user must have been a kender.\n";
    }
    else
    {
	if(owner->query_race_name() != "kender")
	    ken = "former user must have been a kender.\n";
    }

    return "This is a staff, that is for sure, but quite an unusual " +
	"one. It is made from a single piece of flexible yew wood that, " + 
	"from the forked top to the very end, is polished and smoothed, " + 
	"most likely from long usage. The bottom end of it is steel clad " + 
	"and comes to a sharp point. The opposite side of it is adjusted " + 
        "to be used as a catapult and has a leather sling tied across it. " + 
        "Bright feathers are attached to the top. Judging from the shape " + 
        "and adornment its " + ken;
}

int
make_noise(string str)
{
    if(E(TO) == TP)
    {
	if(str == "hoopak" || str == "staff")
	{
	    say(QCTNAME(TP) +" raises " + HIS(TP) + 
	      " hand high in the air and starts to spin " + 
              HIS(TP) + " hoopak. A hollow, " +
	      "whining sound that starts out low, grows higher and higher " +
	      "and higher comes from the hoopak, making the hair at the " + 
              "back of your neck stand on end.\n");

	    write("You start to swing the hoopak over your head, creating " + 
	      "a low sound at first that rises to a high-pitched screaming " + 
              "sound as you swing it faster and faster.\n");

	    return 1;
	}
    }
    NF("Swing what?!?\n");
    return 0;  
}

void
load_hoopak(object tp)
{
    if (!objectp(tp) || E(TO) != tp)
	return;
	
    tp->catch_tell("You proceed to load the hoopak.\n");
    tell_room(E(tp), QCTNAME(tp) + " sticks " + HIS(tp) + " tongue out as " +
		HE(tp) + " loads the hoopak with a pebble.\n", tp);
}

void
aim(object target, object tp)
{
    if (!objectp(tp) || E(TO) != tp || !objectp(target) || E(target) != E(tp))
	return;
	
    tp->catch_tell("You start to aim the hoopak at " + target->query_the_name(tp) +
      " and hope " + HE(target) + " stands still long enough for you to get " +
      HIM(target) + " in your sight.\n");
    target->catch_tell(tp->query_The_name(target) + " aims the hoopak in your direction.\n");
    tell_room(E(tp), QCTNAME(tp) +" aims the hoopak in " + QTNAME(target) + 
      "'s direction.\n", ({tp, target}));
}

void
shoot(object target, object tp)
{
    if (!objectp(tp) || E(TO) != tp || !objectp(target) || E(target) != E(tp))
	return;
	
    tp->catch_tell("You let the pebble fly towards " + target->query_the_name(tp) + ".\n" +
      "The pebble hits " + HIM(target) + " harmlessly.\n");
    target->catch_tell(tp->query_The_name(target) + " lets the pebble fly from the " + 
      "hoopak.\nIt hits you harmlessly and falls to the ground.\n");
    tell_room(E(tp), QCTNAME(tp) + " let the pebble go and fly towards " +
      QTNAME(target) + ".\nThe pebble hits " + HIM(target) + 
      " harmlessly and falls to the ground.\n",({tp,target}));
}

void
stop_shoot()
{
    remove_alarm(alload);
    remove_alarm(alaim);
    remove_alarm(alshoot);
}

int
shoot_player(string str)
{
    object * temparray;
    object target;
    object obj;
    /* If this code look fimiliar .. Well it should I was wonder around
    mackers workroom one day and when i got back home LO and Behold!
    this code was in one of my pouches so i decided to use it.. after
    all what good is code that is not in use :)
     Erine
    "Borrowed from code by macker feather.c"
    */

    if(E(TO) != TP)
    {
	NF("Shoot what?\n");
	return 0;    
    }

    if (!str || !strlen(str) ||
	!parse_command(str, inventory(E(TP)), "[the] %l 'with' [the] 'hoopak'/'staff'", temparray))
    {
	NF("Shoot who with what?\n");
	return 0;
    }

    if(sizeof(temparray) == 0)
    {
	NF("Shoot who with what?\n");
	return 0;
    }
    target = temparray[0];
    if(target==TP)
    {
	write("This feat seems quite hard to accomplish not to mention " +
		"the fact you may miss and make someone lose an eye! " +
		"You decide not to do this.\n");
	return 1;
    }

    TP->catch_tell("You bend down and pick up a pebble from the ground.\n");
    tell_room(E(TP),QCTNAME(TP) + " bends down and picks up a pebble from "+
	  "the ground.\n",TP);
    alload = set_alarm(4.0,0.0, &load_hoopak(TP));
    alaim = set_alarm(6.0,0.0, &aim(target, TP));
    alshoot = set_alarm(8.0,0.0, &shoot(target, TP));
    obj = clone_object("std/paralyze");
    obj->set_stop_object(TO);
    obj->set_stop_fun(stop_shoot);
    obj->set_remove_time(8);
    obj->set_fail_message("You are trying to shoot somebody with your " +
	  "hoopak. Maybe you should 'stop' before trying anything else.\n");
    obj->set_stop_message("You stop trying to shoot people with your " + 
            "hoopak.\n");
    obj->move(TP);
    return 1;
}

void 
init()
{
    ::init();

    if (TP == E(TO))
    {
	add_action(shoot_player, "shoot");
	add_action(make_noise,   "swing");
	add_action(make_noise,   "spin");
    }
}

