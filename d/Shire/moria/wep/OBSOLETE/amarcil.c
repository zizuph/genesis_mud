//
// amarcil.c
//
// 'Amarcil' is an Elvish longsword made of golden laen. 
// Its crosspiece is shapes like a brilliant sunset.
// A 'holy' weapon, 30% extra damage against evil
// beings. Can cast three spells: 'firebolt',
// 'beacon' and 'utterlight'.
//

#include "defs.h"
#include "/d/Immortal/rogon/open/spell/spell.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <filter_funs.h>

inherit BASE_WEAPON;
inherit IM_TELL_FILE;
inherit IM_PARSE_FILE;

int current_light, last_light;
int alarm_id;
object last_room;
object *rooms;

CONSTRUCT_WEAPON
{
    set_name("sword");
    add_name("amarcil");
    add_name("longsword");
    set_adj(({"long", "elven", "brilliant", "laen"}));

    set_short("brilliant elven longsword");

    set_long("@@my_long@@");

    set_hit(49); // +4 on elven design
    set_pen(27); // +4 on elven design

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);

    set_wf(TO);

    add_prop(OBJ_I_VALUE,  3*F_VALUE_WEAPON(29, 27) + random(1000) - 500);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment", 40, "spells", 50, "evil-slaying" }));
    add_prop(MAGIC_AM_ID_INFO, ({ 
	"Amarcil seems to be a weapon for good aligned livings.\n", 1,
	"It is magically enchanted.\n", 10,
	"It is Holy, and contains spells which can be cast.\n", 20,
	"The spells are:\n" +
	"  'sunfire'    - Used as a firebolt.\n" +
	"  'beacon'     - \n" +
	"  'utterlight' - Produces extreme light.\n", 40,
	"It is evil slaying.\n", 60
    }));
    add_prop(OBJ_I_LIGHT, "@@light@@");
    set_hands(W_RIGHT);
    FIXEUID;
    last_light = 0;
}

int
query_usable(object who)
{
    return who->query_alignment() > 500;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, 
	int dt, int phit, int dam)
{
    int extra_dam;   // Extra damage in percent.

    if (enemy->query_hp() > 0) {
	if (!random(4))
	    tell_room(ENV(enemy), "Amarcil glows sparkingly in white!\n");
	extra_dam = 30 * dam / 100;
	if (extra_dam>0)
	    enemy->heal_hp(-extra_dam);
    }

    //::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam + extra_dam);

    if (HP(enemy) <= 0)
        enemy->do_die(ENV(TO));

    return 1;
}

#define DEBUG(msg) find_player("rogon")->catch_msg("AMARCIL: " + msg + "\n");

string
shining_text(int light)
{
    return ({
	"Amarcil does not shine.",
	"Amarcil shimmers somewhat.",
	"Amarcil shimmers in white!",    
	"Amarcil glows brightly in white!",
	"Amarcil sparkles brightly!",
	"Amarcil sparkles in brilliant white!!",
	"Amarcil shines sparkingly in brilliant white!!!" 
    })[light];
}

void
notify_status(int new_light)
{
    int delta = new_light - last_light;
    string str;

    if (!wielder)
	return;

    if (delta > 0) 
	switch (delta) 
	    {
	    case 1: str = "Amarcil glows somewhat brighter!"; break;
	    case 2: str = "Amarcil glows brighter!"; break;
	    case 3: str = "Amarcil glows much brighter!"; break;
	    case 4: str = "Amarcil starts to sparkle much brighter!"; break;
	    default:str = "Amarcil sparkles flashingly out, much brighter than before!!";
	    }
    else
	switch (-delta)
	    {
	    case 1: str = "Amarcil glows somewhat dimmer."; break;
	    case 2: str = "Amarcil glows dimmer.."; break;
	    case 3: str = "Amarcil glows much dimmer.."; break;
	    case 4: str = "Amarcil dims considerably now.."; break;
	    default:str = "Amarcil suddenly dims very much...";
	    }
    tell_room(ENV(wielder),
	      str + "\nNow, " + shining_text(new_light) + "\n"); 
}
	    
int
evil_present(object room)
{
    object *livings = FILTER_LIVE(deep_inventory(room));
    int i, evil = 0, align, sz;

    sz = sizeof(livings);

    for (i=0; i<sz; i++)
	if ((align = livings[i]->query_alignment()) < 0)
	    evil += align;
    return evil;
}

// Light property handling routines
//---------------------------------- 

int
set_light(int new_val)
{
    if (new_val == last_light)
	return last_light;

    if (!environment())
	return last_light;

    current_light = new_val;
    environment()->notify_change_prop(OBJ_I_LIGHT, new_val, last_light);
    
    return new_val - last_light;
}

int
light()
{
    return current_light;
}

int
check_light(int i)
{
    int evil, sz;

    evil = 0;

    if (!environment()) 	
	return 0;

    if (!wielder) 
	return set_light(0);

    if (ENV(wielder) != last_room || !sizeof(rooms)) {
	rooms = "/d/Shire/imladris/lib/getrooms"->get_rooms(ENV(wielder), 3);
	last_room = ENV(wielder);
    }    

    sz = sizeof(rooms);

    for (i=0; i<sz; i++)
	evil += evil_present(rooms[i]);

    if (evil >= 0)
	return set_light(0);
    else {
	if (evil < -2499) 
	    evil = -2499;
	return set_light(-evil/500+1);
    }
}

string
my_long()
{
    return "This is Amarcil, an Elvish longsword made of golden laen. " 
	+ "Its crosspiece is shaped like a brilliant sunburst. It was " 
	+ "once wielded by Feamire, a Sindarin Elf originally from Ost-in-Edhil, "
	+ "but continues to serve in the fight against evil in other hands. " 
	+ shining_text(check_light(0)) + "\n";
}

init()
{
    ::init();
    add_action("do_cast", "cast");
}

#define SPELLS       ({ "sunfire", "beacon", "utterlight" })
#define SPELL_FILE   ({ "lw/sunfire", "lw/beacon", "lw/utterlight" })

static int spell_no;

int
do_cast(string arg)
{
    string spell_name, rest;
    object obj;
    mixed parse_where;

    notify_fail("Usage: cast <spell name> on <who>\n" +
		"       cast <spell name> in <what> on <who>\n" +
		"       cast <spell name> in <what> here\n");

    if (!strlen(arg))
	return 0;

    if (!query_usable(TP))
	return 0;

    if (!query_wielded())
	return notify_fail("You must wield it to cast spells.\n");

    parse_where = all_inventory(TP);

    obj = TO;
    rest = "";

    if (parse_command(arg, parse_where, "%w 'in' %o %s", 
		      spell_name, obj, rest)        ||
	parse_command(arg, parse_where, "%w 'in' %o",
		      spell_name, obj)              ||
	parse_command(arg, parse_where, "%w %s", 
		      spell_name, rest))
    {
	spell_no = member_array(spell_name, SPELLS);
	if (spell_no==-1)
	    return 0;
	
	return obj->cast_it(SPELL_FILE[spell_no], rest);
    }

    return 0;
}

int
cast_it(string file, string rest)
{
    object spell;

    if (TP->query_name() == "Rogon")
	write("ROGON: File: /d/Shire/imladris/spell/" + file + "\n");

    FIXEUID;
    spell = clone_object("/d/Shire/imladris/spell/" + file);

    if (!spell)
	return notify_fail("Sorry, something in the fabric of " +
			   "great magical nature screwed up!\n");

    spell->set_sf(TO);

    return spell->cast_spell(rest, TO);
}

object target;

object *
area_of_effect(string arg)
{
    if (spell_no == 0) 
	return (target = parse_attack(arg, "'on'"));
    else
	return ({});
}

int
start_spell_msg(string arg)
{
	object me,target;
	int spell_no;
    switch (spell_no) {
    default:
	{
		me->catch_msg("You point Amarcil at "+QCTNAME(target)+", and start "+
		"releasing \"Sunfire\"!\n");
		target->catch_msg(QCTNAME(me)+" points "+HIS_HER(me)+" sword "+
		"at you, and start releasing a spell!\n");
		tell_room(ENV(me),QCTNAME(me)+" points "+HIS_HER(me)+" sword at "+
		QCNAME(target)+", and start releasing a spell!\n");
		
	}
    }
    return 1;
}



