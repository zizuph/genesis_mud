#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

inherit "/std/armour";

#define RING_ID     "overseer_ring_object"
#define ARMOUR_CLASS 1
#define CHAMPION_LIST ("champion_club/champion_log")

string
query_auto_load()
{
    return MASTER_OB(TO) + ":";
}

void
init_arg(string arg)
{
}

void
create_armour()
{
    set_name("ring");
    set_adj("iron");
    set_adj("thick");
    add_pname(RING_ID + "s");
    add_name(RING_ID);
    set_short("thick ring of iron");
    set_long("This thick band of iron is marked with a pair of crossed axes over " +
      "a crown, signifying it as the ring of the Master of Tournaments.  The " +
      "Master of Tournaments may 'begin games', 'display ring' to indicate his " +
      "authority, 'award <champion>' of the arena a glorious prize, as well as "+
      "'discard ring' when he no longer wants it anymore.  Scribed " +
      "in dwarven along the inside of the band are the words:\n\n     To Bocephus, "+
      "and to the future Arena Overseers,\n" +
      "     May the battles be bloody and\n     glorious!\n     A.K\n\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_ANY_FINGER);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE, 10000);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, "There is no way you would part with the " +
      "Master of the Tournament ring!\n");
    add_prop(OBJ_M_NO_DROP, "There is no way you would part with the " +
      " Master of the Tournament ring!\n");

}



void
init()
{
    if (!interactive(TP))
	return;

    ADA("begin");
    ADA("display");
    ADA("discard");
    ADA("award");
}

int
display(string str)
{
    if(str == "ring")
    {
	tell_object(E(TO),"You display your thick ring of iron, showing all that " +
	  "you are the Master of the Tournament, and that your ruling is final!\n");
	say(QCTNAME(TP) + " displays " +HIS(TP) + " thick ring of iron, " +
	  " showing all that " +HE(TP)+ " is the Master of the Tournament, and that " +
	  HIS(TP)+ " ruling is final!\n");
	return 1;
    }
    return 0;
}


int
begin(string str)
{
    if(str == "games")
    {
	tell_object(E(TO),"You raise your hands into the air and cry out in a mighty voice: " +
	  " LET THE GAMES BEGIN!\n");
	say(QCTNAME(TP) + " raises " +HIS(TP)+ " hands into the air and cries out in a mighty " +
	  "voice: LET THE GAMES BEGIN!\n");
	return 1;
    }
    return 0;
}


int
award(string str)
{
    object ob, ring, *obj;

    if(!str)
	return 0;

    if(strlen(str))
    {
	if(!sizeof(obj = PARSE_THIS(str, "[the] %l")))
	{
	    notify_fail("Award who with the championship ring?\n");
	    return 0;
	}

	ob = obj[0];
    }

    TP->catch_msg("You raise the hand of " +QTNAME(ob)+ ", declaring " +
      HIM(ob)+ " as the victorious Champion of the Arena!\n" +
      "You solemnly hand " +HIM(ob)+ " an engraved ring of obsidian as a momento " +
      "of " +HIS(ob)+ " victory!\n");       
    TP->tell_watcher(QCTNAME(TP)+ " raises the hand of " +QTNAME(ob)+
      ", declaring " +HIM(ob)+ " the victorious Champion of the Arena!\n" +
      QCTNAME(TP) + " solemnly hands " +HIM(ob)+ " an engraved ring of obsidian as " +
      "a momento of " +HIS(ob)+ " victory!\n", ob);
    ob->catch_msg(QCTNAME(TP) + " raises your hand into the air, declaring you " +
      "the victorious Champion of the Arena!\n" + QCTNAME(TP) + " solemnly hands " +
      "you an engraved ring of obsidian as a momento of your victory!\n");

    setuid();
    seteuid(getuid());
    ring = clone_object("/d/Ansalon/guild/champion_club/ring");
    ring->move(ob);

    log_file(CHAMPION_LIST,"     ~ " +C(ob->query_real_name())+ "  " + 
      extract(ctime(time()))+ " ~\n", -1);


    return 1;
}





int
discard(string str)
{
    if(str == "ring")
    {
	set_alarm(1.0,0.0,"destroy3");
	return 1;
    }
    return 0;
}

void
destroy()
{
    tell_object(E(TO), "You fumble with your ring of iron, and " +
      "lose it on the ground somewhere.\n");
    remove_object();
}

void
destroy2()
{
    tell_object(E(TO),"Deciding that you only need one " +
      "ring of iron, you discard the other.\n");
    remove_object();
}

void
destroy3()
{
    tell_object(E(TO),"Deciding you no longer wish to keep " +
      "the ring of iron, you discard it.\n");
    remove_object();
}

void
destroy4()
{
    remove_object();
}

enter_env(object dest, object old)
{
    mixed oblist;
    if (dest)
    {
	oblist = FIND_STR_IN_OBJECT("all " + RING_ID + "s",dest);
	oblist -= ({ 0, TO });
	if(oblist && sizeof(oblist) > 0)
	    set_alarm(4.0,0.0,"destroy2");
    }
    ::enter_env(dest,old);
}
