//-*-C++-*-
// Bazaar Hill (/d/Avenir/common/bazaar/hill.c)
// creator(s):   Triana 1994
// last update:  Tepisch Aug 94, Mortricia Dec 94
// purpose:      Provides a view of much of the Bazaar area
//               also a place of punishment
//
// added:        the pillory stuff, Mortricia
// note:
// changed:
//   Manat 29 May 2001 Changed the exit_check to check for pobj in this_player
//   Lucius, 7/72006: Added some bounce prevention code; cleanups.
// bug(s):
// to-do:        add punishment sequence.

inherit "/std/room";
#include "/d/Avenir/common/bazaar/bazaar.h"

#define EXIT_ROOM  (EXTR + "centr")
#define CENTER     ({  \
    		EXIT_ROOM,      \
		EXTR + "str6",  \
		EXTR + "str12", \
		EXTR + "str13", \
		EXTR + "str18", \
		EXTR + "str19", \
		EXTR + "str20", \
			})

#define GUARD       NPC + "mguard"
#define PARA_OBJ    MISC + "freeze"
#define STOCK_OBJ   MISC + "pillory"
#define PARA_TIME   320
#define NGUARDS     2
#define LEAVE_MSG   "down the street"
#define TOOLS       ({"lash", "whip", "cane", "chain", "cudgel"})
#define TVERB       ({"lash", "whip", "hit",  "beat",  "torture"})

// Global vars
static int    active=0, alarm_id=0, grd_stat;
static object *guard = allocate(NGUARDS);
static object jade, punisher, pillory, pobj;

// Prototypes
public void lock_and_close(object who, object key);


public void
reset_room(void)
{
    int i;

    if (!punisher)
    {
	punisher = clone_object(NPC + "punisher");
	punisher->arm_me();
    }
	if (environment(punisher) != this_object())
    {
        punisher->move_living("away", this_object());
    }

    if (!jade)
    {
	    jade = clone_object(NPC + "jadestone");
	    jade->arm_me();
    }
	if (environment(jade) != this_object())
    {
	    jade->move_living("away", this_object());
    }

    for (i=0; i<NGUARDS; i++)
    {
	    if (!objectp(guard[i]))
        {
        	guard[i] = clone_object(GUARD);
    	    guard[i]->arm_me();
        }
	    if (environment(guard[i]) != this_object())
        {
    	    guard[i]->move_living("away", TO);
        }
    }
}

static void
create_room(void)
{
    setuid();
    seteuid(getuid());

    SHORT("Top of hill");
    LONG("A small flat-topped hill in the center of the Sybarus Bazaar.\n"
      +"There is a public pillory here, and beside it a wooden post draped "
      +"with assorted tools of punishment.  Guards stand at the base of the "
      +"hill to maintain order among the people awaiting the next public "
      +"flogging.@@center_desc@@");

    AE(EXIT_ROOM, "down", "@@exit_check");

    AI("wood", "Four-fingers in width and very heavy-looking, there is a "
      +"large half-circle and two smaller ones carved into each piece.\n");
    AI("post", "A cold shiver runs down your spine!\nHanging from the post "
      +"you can see stout canes and blood-flecked lashes, a length of "
      +"chain, and a cudgel.\n");
    AI(({"cane", "canes"}), "As thick as your thumb and long as your leg, "
      +"they appear to be slightly flexible and capable of leaving painful "
      +"welts on exposed flesh.\n");
    AI(({"lash", "lashes", "whip", "whips"}), "There are lashes made of "
      +"braided leather, ones with steel hooks at the ends, others with "
      +"knots. They all look like they could tear your skin to ribbons.\n");
    AI(({"chain", "handle"}), "The chain has small links and is threaded "
      +"through a wooden handle, forming a loop. You don't want to see "
      +"that damage it can do to flesh.\n");
    AI("cudgel", "This short, thick stick looks more like a weapon than "
      +"a tool for punishment. Used properly, it could easily break ribs.\n");

    ACI(({"lash","lashes","whip","whips","cane","canes","chain","cudgel"}),
      "get", "You reach out to take it but the skin on your hand feels "
      +"like it should be blackened and dropping off of your bones.\n");

    pillory = clone_object(STOCK_OBJ);
    pillory->move(TO, 1);

    IN

    add_prop(NO_BAZAAR_TELLS, 1);

    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1);

    reset_room();
}

private void
slay(object me, object you)
{
    if (objectp(me) && objectp(you))
	me->command("kill "+ OB_NAME(you));
}

public void
being_killed(object who)
{
    if (present(jade) && !jade->query_attack())
	set_alarm(1.0, 0.0, &slay(jade, who));

    if (present(punisher) && !punisher->query_attack())
	set_alarm(0.5, 0.0, &slay(punisher, who));

    if (!sizeof(filter(guard, objectp)))
	return;

    foreach(object ob : guard)
    {
	if (present(ob) && !ob->query_attack())
	    set_alarm(itof(random(2) + 1), 0.0, &slay(ob, who));
    }
}

public string
center_desc(void)
{
    object *inv, *live, room;
    int i;

    inv = ({});
    for (i = 0; i < sizeof(CENTER); i++)
	if ((room = find_object(CENTER[i])))
	    inv += all_inventory(room);

    if (sizeof(inv)) {
	live = FILTER_LIVE(inv);
	live = FILTER_CAN_SEE(live, TP);
	if (sizeof(live))
	    return "  Down in the center of the marketplace you can see " +
	    COMPOSITE_LIVE(live) + " wandering around.\n";
    }
    return "  The marketplace below looks quiet.\n";
}

public int
call_for_guards(object prisoner, object where)
{
    int i;

    if (!pillory || !where || !prisoner || active)
	return 0;

    if (pillory->query_prisoner())
	return 0;  /* Already a prisoner */

    grd_stat = 0;
    for (i=0; i<sizeof(guard); i++) {
	if (!guard[i]) continue;
	grd_stat += guard[i]->query_average_stat();
    }

    if (grd_stat == 0)
	return 0; /* No guards left to fetch the prisoner! */

    active = 1;

    set_alarmv(4.0, -1.0, "cfg1", ({prisoner, where}));
    alarm_id = set_alarm(itof(18 + random(10)),
      itof(10 + random(18)), "do_something");
    return 1;
}

private void
cfg1(object prisoner, object where)
{
    int i;

    if (!prisoner || !where) {
	active = 0;
	return;
    }

    /* Ok, now we can get the prisoner from "where" */
    pobj = clone_object(PARA_OBJ);
    pobj->set_stop_verb("");
    pobj->set_remove_time(PARA_TIME);
    pobj->set_exit_cmds(({where, TO}));
    pobj->set_stop_object(TO);
    pobj->set_stop_fun("release_prisoner");
    pobj->set_fastened(0);
    pobj->set_fail_message("You are held by a guard. You cannot do that.\n");

    for (i=0; i<sizeof(guard); i++) {
	if (!guard[i]) continue;

	if (where != environment(guard[i]))
	    guard[i]->move_living(LEAVE_MSG, where);

	if (i == 0) {
	    if (random(2))
		guard[i]->command("stare at " + prisoner->query_real_name());
	    else
		guard[i]->command("say What's going on here?");
	} else {
	    if (random(2))
		guard[i]->command("peer at " + prisoner->query_real_name());
	    else
		guard[i]->command("emote kicks the corpse.");
	}

	if (!present(prisoner, where)) {
	    pobj->remove_object();
	    guard[i]->command("emote examines the corpse.");
	    guard[i]->command("hmm");
	    if (where != TO) guard[i]->move_living(LEAVE_MSG, TO);
	    active = 0;
	    return;
	}

	if (prisoner->query_average_stat() < (grd_stat * 3)) {
	    tell_room(where, QCTNAME(guard[i]) + " grabs hold of " +
	      QTNAME(prisoner) +
	      " with a firm grip.\n", prisoner);
	    prisoner->catch_msg(QCTNAME(guard[i]) +
	      " holds you in a firm grip.\n");

	    if (!present(pobj, prisoner)) pobj->move(prisoner);
	} else {
	    tell_room(where, QCTNAME(guard[i]) + " doesn't dare to grab hold of " +
	      QTNAME(prisoner) + ".\n", prisoner);
	    prisoner->catch_msg(QCTNAME(guard[i]) +
	      " doesn't dare to grab hold of you.\n");
	    pobj->remove_object();
	    guard[i]->command("emote examines the corpse.");
	    if (where != TO) guard[i]->move_living(LEAVE_MSG, TO);
	    active = 0;
	    return;
	}
    }

    set_alarmv(5.0, -1.0, "cfg2", ({prisoner, where}));
}

private void
cfg2(object prisoner, object where)
{
    int i;
    object key;

    if (where && prisoner && where != TO)
	tell_room(where, "A guard begins to drag " + QTNAME(prisoner) +
	  " away.\n", prisoner);

    if (prisoner) prisoner->catch_msg("A guard starts to drag you away.\n");

    for (i=0; i<sizeof(guard); i++)
	if (guard[i] && TO != environment(guard[i]))
	    guard[i]->move_living(LEAVE_MSG, TO);

    if (!prisoner) {
	active = 0;
	return;
    }

    if (TO != environment(prisoner)) {
	prisoner->move_living(LEAVE_MSG + ", dragged by a guard", TO, 1);
    } else {
	tell_room(TO, QCTNAME(prisoner) + " is firmly held by a guard.\n",
	  prisoner);
    }

    set_alarm(6.0, -1.0, "cfg3", prisoner);
}

private void
cfg3(object prisoner)
{
    int i;
    object key;

    if (!pillory || !prisoner) {
	active = 0;
	return;
    }

    key = pillory->query_key();
    for (i=0; i<sizeof(guard); i++) {
	if (guard[i] && present(key, guard[i])) {
	    guard[i]->command("unlock pillory with key");
	    guard[i]->command("open pillory");
	    tell_room(TO, QCTNAME(guard[i]) + " places " + QTNAME(prisoner) +
	      " in the " + pillory->short() + ".\n", prisoner);
	    prisoner->catch_msg(QCTNAME(guard[i]) + " places you in the " +
	      pillory->short() + ".\n");
	    guard[i]->command("Your name, prisoner?");
	    pillory->set_prisoner(prisoner);
	    guard[i]->command("close pillory");
	    guard[i]->command("lock pillory with key");
	    if (pobj) {
		pobj->set_fail_message("You are locked in the pillory." +
		  " You cannot do that.\n");
		pobj->set_fastened(1);
	    }
	    break;
	}
    }
    active = 0;
}

public void
release_prisoner(object poor_player)
{
    int i;
    object key, prisoner;

    if (!pillory) return;

    prisoner = pillory->query_prisoner();
    if (!prisoner) return;

    key = pillory->query_key();
    for (i=0; i<sizeof(guard); i++) {
	if (guard[i] && present(guard[i]) && key && present(key, guard[i])) {
	    prisoner->catch_msg("Exhausted and in extreme pain, you whisper your "+
	      "identity to the troloby.");
	    guard[i]->command("unlock pillory with key");
	    guard[i]->command("open pillory");
	    guard[i]->command("point at " + prisoner->query_real_name());
	    guard[i]->command("say You are free to go");
	    guard[i]->command("shout Let it be recorded that "+ 
	      capitalize(prisoner->query_real_name()) +" was flogged "+
	      "on this day for the crime of murder!");       
	    pillory->set_prisoner(0);
	    set_alarmv(4.0, -1.0, "lock_and_close", ({guard[i], 0}) );
	    return;
	}
    }
    tell_room(TO, QCTNAME(prisoner) + " manages to escape the " +
      pillory->short() + ".\n", prisoner);
    prisoner->catch_msg("Somehow you manage to escape the " +
      pillory->short() + ".\n");
    pillory->set_prisoner(0);
    lock_and_close(0, 0);
}

public void
lock_and_close(object who, object key)
{
    if (!pillory)
	return;

    if (pillory->query_prisoner() || active)
	return;

    pillory->set_prisoner(0);

    if (key) pillory->set_key(key);

    if (who && present(who)) {
	who->command("close pillory");
	who->command("lock pillory with key");
    } else {
	pillory->lock_and_close();
    }
}

public object
query_pobj(void)
{
    return pobj;
}

public void
do_something(void)
{
    int i, j;
    string name, tool, verb;
    object who;

    if (!pillory || !pobj) {
	if (alarm_id) remove_alarm(alarm_id);
	alarm_id = 0;
	return;
    }

    who = pillory->query_prisoner();

    if (active || !who)
	return;

    name = who->query_real_name();

    if (punisher && present(punisher)) 
    {
	i = random(sizeof(TOOLS));
	tool = TOOLS[i];
	verb = TVERB[i];
	punisher->command("emote takes a " + tool + " from the post.");
	tell_room(TO, QCTNAME(punisher) + " starts to " + verb + " " +
	  QTNAME(who) + " using the " + tool + ".\n", who);
	who->catch_msg(QCTNAME(punisher) + " starts to " + verb +
	  " you with the " + tool + ".\n");
	who->reduce_hit_point(who->query_hp()/3);
	switch (random(7))
	{
	case 0:
	    write("You struggle within the confines of the pillory, "+
	      "moaning behind your gag as the pain mounts.\n");
	    say(QCTNAME(who) +" struggles within the confines of the "+
	      "pillory and moans pathetically behind "+ POSSESS(who) +
	      " gag.\n");
	    break;
	case 1:
	    write("THE PAIN!!!\nYour body jerks and writhes in an "+
	      "attempt to avoid the fall of the "+ tool +" on your "+
	      "back again.\nYou can hear the crowd cheering the "+
	      "troloby on in his efforts to flay you alive.\n");
	    say(QCTNAME(who) +"'s body jerks and writhes in an "+
	      "obvious attempt to avoid the next fall of the "+
	      tool +".\nThe crowd roars enthusiastically.\n");
	    break;
	case 2:
	    write("Tears sting your eyes, and your mouth opens to "+
	      "scream around your gag.\n");
	    say(QCTNAME(who) +"'s eyes fill with tears and "+ 
	      POSSESS(who) +" mouth opens to scream around "+ 
	      POSSESS(who) +" gag.\n");           
	    break;
	case 3:
	    write("Dignity be damned! You fight with all your strength "+
	      "to free yourself from the pillory before the "+ tool +
	      " strikes you again.\n");
	    say(QCTNAME(who) +" looses all dignity before your very "+
	      "eyes, reduced to an animal vainly struggling to free "+ 
	      OBJECTIVE(who) +"self from a trap.\n");
	    break;
	case 4:
	    write("If this is how they punish people in Sybarus, it "+
	      "is a wonder there is any crime at all!\nThe pain "+
	      "of this flogging has become unbearable.\n");
	    say(QCTNAME(who) +" seems to retreat into "+ POSSESS(who) +
	      " mind in an attempt to escape the pain of "+ POSSESS(who)
	      +" brutal flogging.\n");
	    break;
	case 5:
	    write("Pins and needles run down your arms as you "+
	      "strain against them, trying to escape from the "+
	      "pillory.\n");
	    say(QCTNAME(who) +" seems to strain "+ POSSESS(who) +
	      " arms in an attempt to escape from the pillory.\n");
	    break;
	case 6:
	    write("Your legs feel weak and shaky.\nYou fear that "+
	      "you may fall to your knees before the crowd, "+
	      "who will witness your humiliation.\n");
	    say(QCTNAME(who) +" appears to be struggling to stay on "+ 
	      POSSESS(who) +" feet.\n");
	    break;

	default:
	}   
    }

    for (i=0; i<sizeof(guard); i++) {
	if (!guard[i] || !present(guard[i]))
	    continue;

	j = random(5);
	if (j == 0)
	    guard[i]->command("spit " + name);
	else if (j == 1)
	    guard[i]->command("laugh evilly at " + name);
	else if (j == 2)
	    guard[i]->command("kick "+ name);
	else if (j == 3)
	    guard[i]->command("say to "+ name +" You will confess who "+
	      "you are before we free you."); 
	else
	    guard[i]->command("slap " + name);
	break;
    }
}

public int
exit_check(void)
{
    if (pobj && present(pobj, this_player()))
    {
	write("You are prohibited from doing that!\n");
	return 1;
    }

    if (this_player()->query_attack())
	EXIT_ROOM->am_cowardly(this_player());

    return 0;
}

public object
coward_blocker(void)
{
    return one_of_list(filter(guard + ({ jade, punisher }), objectp));
}
