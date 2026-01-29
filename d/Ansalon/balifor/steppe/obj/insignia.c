inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

#define SWORD_ID     "ansalon_sword_object"
#define PLAYER_KILLED_VIRIDIAN "_player_killed_viridian"

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
create_object()
{
    set_name("insignia");
    set_adj("kestrel");
    add_adj("crimson");
    add_pname(SWORD_ID + "s");
    add_name(SWORD_ID);
    set_short("crimson kestrel insignia");
    set_long("This insignia is of a small falcon in flight, " +
      "a crimson kestrel, an avian creature that was once " +
      "common in the Old World. This is the mark bestowed upon " +
      "those proven to be masters in the art of swordsmanship, " +
      "and is recognised throughout the realms." +
      " You are able to 'display insignia', as well as 'crossarms' as only a master " +
      "with blades could do. " +
      "As a swordsmaster you are also able to 'leansword' if " +
      "you are wielding a sword. " +
      " If you have no further use of the insignia, simply " +
      "discard it." +
      "\n");
    add_prop(OBJ_M_NO_DROP,"You are unable to drop or give " +
      "away the insignia.\n");
    TP->add_subloc("the_swordsman_club", TO);
    set_no_show_composite(1);
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "You are wearing your insignia of the crimson kestrel.\n";

    if (for_obj == me)
	return "You are wearing your insignia of the crimson " +
	"kestrel, the mark of a Swordsmaster of the Realms.\n";
    else
	return C(PRONOUN(me)) + " is wearing " + POSSESSIVE(me) +
	" insignia of the crimson kestrel, the mark of a " +
	"Swordsmaster of the Realms.\n";
}

void
init()
{
    if (!interactive(TP))
	return;
    if(TP->query_skill(SS_WEP_SWORD) < 81)
	set_alarm(3.0,0.0,"destroy");
    if(TP->query_prop(PLAYER_KILLED_VIRIDIAN))
	set_alarm(1.0,0.0, "destroy4");
    ADA("discard");
    ADA("display");
    ADA("crossarms");
    ADA("leansword");

}

int
display(string str)
{
    if(str == "insignia")
    {
	tell_object(E(TO),"You display your insignia of the crimson kestrel, showing all that " +
	  "you are a Swordsmaster of the Realms.\n");
	say(QCTNAME(TP) + " displays " +HIS(TP) + " crimson kestrel insignia, the mark " +
	  "of a Swordsmaster of the Realms.\n");
	return 1;
    }
    return 0;
}

int
filter_swords(object obj)
{
    return (obj->query_wt() == W_SWORD);
}

int
leansword(string str)
{
    object *weapon;

    /* Filter out non-swords */
    weapon = filter(TP->query_weapon(-1), filter_swords);

    if(!sizeof(weapon))
    {
	notify_fail("Lean on what sword?\n");
	return 0;
    }

    /* Use the first sword found to lean upon */
    write("You place the point of your " +weapon[0]->short()+
      " on the ground and complacently lean on its pommel.\n");
    say(QCTNAME(TP) + " places the point of " +HIS(TP)+
      " " +weapon[0]->short()+ " on the ground and " +
      "complacently leans on its pommel.\n");
    return 1;
}

int
crossarms(string str)
{
    if(!str)
    {
	tell_object(E(TO),"You cross your arms, confident in your ability to take care of any " +
	  "problem with your blades.\n");
	say(QCTNAME(TP) + " crosses " +HIS(TP)+ " arms, confident in " +HIS(TP)+
	  " ability to take care of any problem with " +HIS(TP)+ " blades.\n");
	return 1;
    }
    return 0;
}

int
discard(string str)
{
    if(str == "insignia")
    {
	set_alarm(1.0,0.0,"destroy3");
	return 1;
    }
    return 0;
}

void
destroy()
{
    tell_object(E(TO), "You fumble with the insignia, and " +
      "lose it on the ground somewhere.\n");
    remove_object();
}

void
destroy2()
{
    tell_object(E(TO),"Deciding that you only need one " +
      "insignia, you discard the one you just discovered.\n");
    remove_object();
}

void
destroy3()
{
    tell_object(E(TO),"Deciding you no longer wish to keep " +
      "the insignia, you discard it.\n");
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
	oblist = FIND_STR_IN_OBJECT("all " + SWORD_ID + "s",dest);
	oblist -= ({ 0, TO });
	if(oblist && sizeof(oblist) > 0)
	    set_alarm(4.0,0.0,"destroy2");
    }
    ::enter_env(dest,old);
}
