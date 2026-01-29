inherit "/std/object";

#include "defs.h"
#include <wa_types.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include <comb_mag.h>
#include <formulas.h>
#include <filter_funs.h>
#include <language.h>

// Prototypes
void sing_verse();

create_object()
{
    set_name("skilltester");
    add_name("skills");
    set_short("skilltester");
}

init()
{
    ::init();
    FIXEUID;
    add_action("do_list",	  "ilist");
    add_action("do_sing",	  "sing");
    add_action("do_evaluate",	  "evaluate");
    add_action("do_comp_wep",	  "compare");
    add_action("disarm_armed",	  "disarm");
    add_action("disarm_unarmed",  "disarm");
    add_action("do_fumble",       "fumble");
    add_action("do_punch",        "punch");
    add_action("do_bash",         "bash");
    add_action("do_clinch",       "clinch");
    add_action("prevent_unwield", "unwield");
}

string *song_text;
int verse;

sing_verse()
{
    string *lines = explode(song_text[verse], "\n");
    int i;
    for(i=0;i<sizeof(lines);i++)
    {
	write("You chant: "+lines[i]+"\n");
	say("The dwarf chants: "+lines[i]+"\n");
    }
    verse ++;
    if(verse < sizeof(song_text))
    {
	write("You pause.\n");
	say("The dwarf pauses.\n");
    set_alarm(6.0, 0.0, &sing_verse());
    }
    else
    {
	write("You stand silent for a while.\n");
	say("The dwarf stands silent for a while.\n");
    }
}

int
do_sing(string song)
{
    if(song != "moria")
	return 0;

    setuid(); seteuid(getuid());
    song = read_file("/d/Shire/rogon/dwarf/moria.song");
    song_text = explode(song, "---");

    write("You stand up in the dark and begin to chant with a deep voice.\n");
    say(QCTNAME(TP)+" stands up in the dark and begins to chant with a deep voice.\n");

    verse = 0;
    sing_verse();
    return 1;
}


int
is_weapon(object what)
{
    return function_exists("create_object", what) == "/std/weapon";
}

int
is_armour(object what)
{
    return function_exists("create_object", what) == "/std/armour";
}

int
is_worn(object what)
{
    return objectp(what->query_worn());
}

int
is_wielded(object what)
{
    return objectp(what->query_wielded());
}

string
make_list(string header, object *list)
{
    int i;
    string ret;

    if(!sizeof(list))
	return "";

    ret = header + "...................."[0..-strlen(header)] + ":\n";
    for(i=0;i<sizeof(list);i++)
	ret += "  " + CAP(LANG_ASHORT(list[i])) + ".\n";
    return ret;
}

int
do_list(string what)
{
    object *worn, *wielded, *arms, *weps, *inv;
    int i;

    if (!CAN_SEE_IN_ROOM(TP))
	return notify_fail("It is to dark.\n");

    inv = FILTER_CAN_SEE(all_inventory(TP), TP);

    if (member_array(what, ({ "-?", "--help", "help", "usage", "-u", "--usage", "?" })) >= 0)
	{
	    write("Usage: " + query_verb() + "         : Lists all your inventory.\n" +
		  "       " + query_verb() + " <items> : Lists all your inventory of <items>.\n");
	    return 1;
	}  

    if(strlen(what))
	inv = FIND_STR_IN_ARR(what, inv);

    if(!sizeof(inv))
    {
	write("Nothing found in your inventory.\n");
	return 1;
    }

    arms = filter(inv, "is_armour", TO);
    worn = filter(arms, "is_worn", TO);

    weps = filter(inv, "is_weapon", TO);
    wielded = filter(weps, "is_wielded", TO);

    inv -= arms + weps;
    arms -= worn;
    weps -= wielded;

    write(make_list("Wielded weapons", wielded));
    write(make_list("Worn armours", worn));
    write(make_list("Weapons", weps));
    write(make_list("Armours", arms));
    write(make_list("Misc", inv));

    return 1;
}

int
do_evaluate(string str)
{
    object *items;
    object *weps;
    object *arms;

    notify_fail("Evaluate which weapon/armour?\n");

    items = FIND_STR_IN_OBJECT(str, TP);
    weps = filter(items, "is_weapon", TO);
    if(!sizeof(weps))
    {
	arms = filter(items, "is_armour", TO);
	if(!sizeof(arms))
	    return 0;

	write(_EVAL_ARMS(arms[0]));
	return 1;
    }
    else
    {
	write(_EVAL_WEPS(weps[0]));
	return 1;
    }
}

int
do_comp_wep(string str)
{
    string s1, s2;
    object wep1, wep2, *weps;

    if(sscanf(str, "%s with %s", s1, s2)!=2)
	return notify_fail(
	    "Syntax: " + CAP(query_verb()) + " weapon 'with' weapon\n");

    weps = FIND_STR_IN_OBJECT(s1, TP);
    weps = filter(weps, "is_weapon", TO);
    if(!sizeof(weps))
	return notify_fail("Compare which weapon?\n");

    wep1 = weps[0];

    weps = FIND_STR_IN_OBJECT(s2, TP);
    weps = filter(weps, "is_weapon", TO);
    if(!sizeof(weps))
	return notify_fail("Compare weapon with what?\n");

    wep2 = weps[0];

    write(_COMP_WEPS(wep1, wep2));
    return 1;
}

mixed
test_drop(string file_tp)
{
    object *clinching;
    object tp = find_object(file_tp);
    object wep = previous_object(-2);

    if(!tp || !living(tp))
	return 0;

    clinching = tp->query_prop("_live_ao_clinch_weapon");
    if(!sizeof(clinching))
	return 0;
    clinching = clinching & tp->query_weapon(-1);
    if(!sizeof(clinching))
	return 0;
    if(member_array(wep, clinching)==-1)
	return 0;
    return "You can't drop the weapon you are clinched to!\n"+
	   "Do: 'clinch off' to do it!\n";
}

int
prevent_unwield(string str)
{
    object *weps = TP->query_prop("_live_ao_clinch_weapon");
    object *weapons = TP->query_weapon(-1);
    object *wanted, *clinched;
    int i;

    if(!sizeof(weps))
	return 0;
    if(!sizeof(weapons))
	return 0;

    wanted = CMDPARSE_STD->find_str_in_arr(str, weapons);
    clinched = wanted & weps;

    if(sizeof(clinched))
    {
	write("Alas! You must first clinch off "+COMPOSITE_DEAD(weps)+
	      " to unwield it!\n");
	wanted = wanted - clinched;
	for(i=0;i<sizeof(wanted);i++)
	    TP->unwield(wanted);
	return 1;
    }
    return 0;
}

int
do_clinch(string arg)
{
    object *weps;
    object *clinching;
    object *cs;
    int i;
    string toggle, weapon;

    notify_fail("Syntax: clinch [on|off] weapon\n");

    clinching = TP->query_prop("_live_ao_clinch_weapon");
    if(!sizeof(clinching))
	clinching = ({});

    if(!strlen(arg))
	arg = sizeof(clinching)?"off":"on";

    weps = TP->query_weapon(-1);

    if(sscanf(arg, "on %s", weapon)==1 || arg=="on")
    {
	if(!sizeof(weps))
	    return notify_fail("You must wield weapons to clinch on.\n");
	if(!strlen(weapon))
	    weapon = "weapon";

	cs = FIND_STR_IN_ARR(weapon, weps);
	if(!sizeof(cs))
	    return notify_fail("You must wield a weapon to clinch on it.\n");
	for(i=sizeof(cs)-1;i>=0;i--)
	{
	    if(cs[i]->query_prop(OBJ_M_NO_DROP))
	    {
		write("You can't drop the "+cs[i]->short()+" anyhow.\n");
		cs = exclude_array(cs, i, i);
		if(sizeof(cs))
		    continue;
		else
		    return 1;
	    }
	    cs[i]->add_prop(OBJ_M_NO_DROP,
		"@@test_drop:"+MASTER+"|"+file_name(TP)+"@@");
	}

	TP->add_prop("_live_ao_clinch_weapon", weps+cs);
	write("You clinch to your "+COMPOSITE_DEAD(cs)+".\n");

	say(QCTNAME(TP)+" secures "+HIS_HER(TP)+" grip on "+HIS_HER(TP)+
	    " "+ QCOMPDEAD + ".\n");
	return 1;
    }
    else
    {
	if(!sizeof(weps))
	    return notify_fail("But, you do not wield any weapons.\n");
	if(!strlen(weapon))
	    cs = weps;
	else
	    cs = FIND_STR_IN_ARR(weapon, weps);

	if(!sizeof(cs))
	    return notify_fail("Eh, which weapon did you say?\n");
	for(i=0;i<sizeof(cs);i++)
	    cs[i]->remove_prop(OBJ_M_NO_DROP);
	TP->remove_prop("_live_ao_clinch_weapon");
	write("Ok, you loosen your grip on "+COMPOSITE_DEAD(cs)+".\n");
	say(QCTNAME(TP)+" loosens "+HIS_HER(TP)+" grip on "+QCOMPDEAD+".\n");
	return 1;
    }
}

int
do_bash(string arg)
{
    object who;

    if(!arg||arg=="")
	who = TP->query_attack();
    if(!who && !strlen(arg) || !(who=present(arg, ETP)))
	return notify_fail("Bash who?\n");
    if(!present(who, ETP))
	return notify_fail("But, "+HE_SHE(who)+" is not here.\n");
    if(NPATTACK(who))
	return notify_fail("You can't attack here!\n");
    if(!F_DARE_ATTACK(TP, who))
	return notify_fail("You do not dare to attack!\n");

    return _BASH(who, TP);
}

int do_fumble(string arg)
{
    object who;
    if(!arg||arg=="")
	who = TP->query_attack();
    if(!who && !strlen(arg) || !(who=present(arg, ETP)))
	return notify_fail("Fumble who?\n");
    if(!present(who, ETP))
	return notify_fail("But, "+HE_SHE(who)+" is not here.\n");
    // FIXEUID;
    return FUMBLE_FILE->fumble(who, TP);
}

int do_punch(string arg)
{
    object who;

    if (!strlen(arg))
	who = TP->query_attack();
    if (!who && !(who=present(arg, ETP)))
	return notify_fail("Punch who?\n");
    if (!who || !present(who, ETP))
	return notify_fail(HE_SHE(who)+" is not here.\n");
    if (NPATTACK(who))
	return notify_fail("You can't attack here!\n");
    if (!F_DARE_ATTACK(TP, who))
	return notify_fail("You do not dare to attack!\n");

    return _PUNCH(who, TP);
}

int disarm_unarmed(string arg)
{
    object who;

    notify_fail("Disarm who?\n");

    if(!arg)
	return "/d/Shire/rogon/skills/disarm"->disarm_foe_unarmed(who, TP);
    if(!(who=present(arg, ETP)) || who==TP->query_name())
	return notify_fail(CAP(arg)+" is not here!\n");
    if(!living(who))
	return notify_fail("Disarm what??\n");

    return _DISARM_U(who, TP);
}

int disarm_armed(string arg)
{
    object who;

    notify_fail("Disarm who?\n");

    if(!arg)
	return "/d/Shire/rogon/skills/disarm_a"->disarm_foe_armed(who, TP);
    if(!(who=present(arg, ETP)) || who==TP->query_name())
	return notify_fail(CAP(arg)+" is not here!\n");
    if(!living(who))
	return notify_fail("Disarm what??\n");

    return _DISARM_A(who, TP);
}
