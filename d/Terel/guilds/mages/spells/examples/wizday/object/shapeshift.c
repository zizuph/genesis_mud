#include "../spells.h"
#include "/d/Khalakhor/sys/defs.h"
#include <language.h>
#include <login.h>
#include <living_desc.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>

inherit SPELL_OBJECT;
inherit "/d/Genesis/newmagic/resist";
inherit "/std/shadow";

// Prototypes
public varargs string query_the_name(object pobj);
public string query_race_name();
public string query_name();

private mapping com_sounds;
private object gPlayer;

string
query_true_description()
{
    return shadow_who->query_met_name();
}

mixed
my_no_attack()
{
    object attacker;
    int i = -1;

    while (!living(previous_object(i)))
    {
	i--;
	if (i == -4)
	    break;
    }
    attacker = previous_object(i);
    // If the attacker isn't living (couldn't find one) so we abort
    if (!living(attacker))
	return 0;

    // If we change form don't allow players to attack the 
    // new form without testing if they are hunting them
    // index of -1 means player arrived in the room an index of
    // -3 means he typed kill or assist.
    if (living(gPlayer) && i != -1)
	return 0;

    if (random(100) < spell_resist_illusion(shadow_who, attacker,
	SS_ELEMENT_LIFE, TASK_DIFFICULT))
	return 0;

    // Create a peace between these two (prevent hunting messages.)
    attacker->stop_fight(shadow_who);
    shadow_who->stop_fight(attacker);
    return "You find no such living thing.\n";
}

varargs public int
dispel_magic_effect(object dispeler)
{
    if (objectp(dispeler))
    {
	if (random(dispeler->query_avatar_level()) <
	  random(spell_caster->query_avatar_level()))
	{
	    dispeler->catch_tell("Your attempt to dispel the "+
	      query_spell_effect_desc()+" placed on "+
	      spell_target->query_the_name(dispeler) +" was "+
	      "unsuccessful.\n");
	    return 0;
	}
    }
    if (objectp(gPlayer))
    {
	spell_target->catch_tell("Your illusion of "+query_the_name()+
	  " unravells revealing your true self.\n");
	tell_room(ENV(spell_target), QCTNAME(spell_target) +" shimmers "+
	  "as it begins to fade from view revealing "+
	  query_true_description()+".\n", spell_target);
    }
    else
    {
	spell_target->catch_tell("A surge of energy from the void "+
	  "disrupts your ability to maintain your illusion, revealing "+
	  "your true self for all to see.\n");
	tell_room(ENV(spell_target), QCTNAME(spell_target) +" " +
	  "emerges from a blinding burst of light, as "+
	  HIS_HER(spell_target)+" illusion shatters "+
	  "violently.\n", spell_target);
    }
    shadow_who->remove_prop(OBJ_M_NO_MAGIC_ATTACK);
    shadow_who->remove_prop(OBJ_M_NO_ATTACK);
    remove_spell_effect_object();
    return 1;
}

public int
setup_spell_effect()
{
    set_spell_effect_desc("shape-shifter illusion");
    if (!::setup_spell_effect())
    {
	remove_spell_effect_object();
	return 0;
    }
    gPlayer = spell_caster->query_prop(AVATAR_O_SHAPESHIFT);
    if (!objectp(gPlayer))
    {
	spell_target->remove_prop(AVATAR_O_SHAPESHIFT);
	spell_target->catch_tell("Your attempt to change form "+
	  "fails horribly.  You now must remember a new form "+
	  "to change into.\n");
	remove_spell_effect_object();
	return 0;
    }
    shadow_me(spell_target);
    set_alarm(itof(900 + random(600)), 0.0, dispel_magic_effect);
    // set up the race_sound mapping.
    if (!mappingp(com_sounds = RACESOUND[query_race_name()]))
    {
	com_sounds = ([ ]);
    }
    shadow_who->add_prop(OBJ_M_NO_MAGIC_ATTACK, my_no_attack);
    shadow_who->add_prop(OBJ_M_NO_ATTACK, my_no_attack);
    return 1;
}

public string
race_sound()
{
    string race_to = previous_object(-1)->query_race_name();
    string safety;

    if (objectp(gPlayer))
    {
	if (!living(gPlayer))
	    return "says";
	else
	    safety = gPlayer->race_sound();
    }
    else
    {
	safety = shadow_who->race_sound();
	set_alarm(0.0, 0.0, dispel_magic_effect);
    }

    if (safety != "says")
    {
	return safety;
    }

    if (!com_sounds[race_to])
    {
	return "says";
    }

    return com_sounds[race_to];
}

public string
query_m_in()
{
    if (objectp(gPlayer))
    {
	if (!living(gPlayer))
	    return "arrives";
	else
	    return gPlayer->query_m_in();
    }
    set_alarm(0.0, 0.0, dispel_magic_effect);
    return shadow_who->query_m_in();
}

public string
query_m_out()
{
    if (objectp(gPlayer))
    {
	if (!living(gPlayer))
	    return "leaves";
	else
	    return gPlayer->query_m_out();
    }
    set_alarm(0.0, 0.0, dispel_magic_effect);
    return shadow_who->query_m_out();
}

public string
query_mm_in()
{
    if (objectp(gPlayer))
    {
	if (!living(gPlayer))
	    return "arrives in a puff of smoke.";
	else
	    return gPlayer->query_mm_in();
    }
    set_alarm(0.0, 0.0, dispel_magic_effect);
    return shadow_who->query_mm_in();
}

public string
query_mm_out()
{
    if (objectp(gPlayer))
    {
	if (!living(gPlayer))
	    return "disappears in a puff of smoke.";
	else
	    return gPlayer->query_mm_out();
    }
    set_alarm(0.0, 0.0, dispel_magic_effect);
    return shadow_who->query_mm_out();
}

public varargs string
short(mixed for_obj)
{
    if (objectp(gPlayer))
	return gPlayer->short(for_obj);

    set_alarm(0.0, 0.0, dispel_magic_effect);
    return shadow_who->short(for_obj);
}

public varargs string
long(mixed for_obj)
{
    if (!objectp(for_obj))
	for_obj = this_player();
    if (objectp(gPlayer))
    {
	if (!living(gPlayer))
	    return gPlayer->long(0, for_obj);
	else
	    return gPlayer->long(for_obj);
    }

    set_alarm(0.0, 0.0, dispel_magic_effect);
    return shadow_who->long(for_obj);
}

varargs public mixed 
query_adj(int arg)
{
    if (objectp(gPlayer))
	return gPlayer->query_adj(arg);

    set_alarm(0.0, 0.0, dispel_magic_effect);
    return shadow_who->query_adj(arg);
}

public string *
query_adjs()
{
    if (objectp(gPlayer))
	return gPlayer->query_adjs();

    set_alarm(0.0, 0.0, dispel_magic_effect);
    return shadow_who->query_adjs();
}

public string
query_presentation()
{
    if (objectp(gPlayer))
    {
	if (!living(gPlayer))
	    return shadow_who->query_presentation();
	else
	    return gPlayer->query_presentation();
    }

    set_alarm(0.0, 0.0, dispel_magic_effect);
    return shadow_who->query_presentation();
}

public int
query_gender()
{
    if (objectp(gPlayer))
	return gPlayer->query_gender();

    set_alarm(0.0, 0.0, dispel_magic_effect);
    return shadow_who->query_gender();
}

public string
query_objective()
{
    if (objectp(gPlayer))
    {
	if (!living(gPlayer))
	    return "it";
	else
	    return gPlayer->query_objective();
    }

    set_alarm(0.0, 0.0, dispel_magic_effect);
    return shadow_who->query_objective();
}

public string
query_possessive()
{
    if (objectp(gPlayer))
    {
	if (!living(gPlayer))
	    return "its";
	else
	    return gPlayer->query_possessive();
    }

    set_alarm(0.0, 0.0, dispel_magic_effect);
    return shadow_who->query_possessive();
}

public string
query_pronoun()
{
    if (objectp(gPlayer))
    {
	if (!living(gPlayer))
	    return "it";
	else
	    return gPlayer->query_pronoun();
    }

    set_alarm(0.0, 0.0, dispel_magic_effect);
    return shadow_who->query_pronoun();
}

public string
query_race_name()
{
    if (objectp(gPlayer))
    {
	if (!living(gPlayer))
	    return shadow_who->query_race_name();
	else
	    return gPlayer->query_race_name();
    }

    set_alarm(0.0, 0.0, dispel_magic_effect);
    return shadow_who->query_race_name();
}

string
query_nonmet_name()
{
    if (!living(gPlayer))
	return gPlayer->short();

    return gPlayer->query_nonmet_name();
}

public string
query_name()
{
    if (objectp(gPlayer))
    {
	if (!living(gPlayer))
	    return capitalize(LANG_ADDART(query_nonmet_name()));
	else
	    return gPlayer->query_name();
    }

    set_alarm(0.0, 0.0, dispel_magic_effect);
    return shadow_who->query_name();
}

public string
query_met_name()
{
    if (!objectp(gPlayer))
    {
	set_alarm(0.0, 0.0, dispel_magic_effect);
	return shadow_who->query_met_name();
    }
    if (!living(gPlayer))
	return gPlayer->short();
    if (gPlayer->query_ghost())
	return "ghost of "+query_name();

    return query_name();
}

public string
query_Met_name()
{
    return capitalize(query_met_name());
}

public string
query_art_name(object pobj)
{
    string pre = "", aft = "";

    if (!objectp(pobj))
	pobj = previous_object(-1);

    if (!objectp(gPlayer))
    {
	set_alarm(0.0, 0.0, dispel_magic_effect);
	return shadow_who->query_the_name(pobj);
    }

    if (!living(gPlayer))
	return LANG_ASHORT(gPlayer);

    if (!CAN_SEE(pobj, shadow_who) || !CAN_SEE_IN_ROOM(pobj))
	return LD_SOMEONE;
    if (shadow_who->query_prop(OBJ_I_HIDE))
    {
	pre = "[";
	aft = "]";
    }
    if (shadow_who->query_prop(OBJ_I_INVIS))
    {
	pre = "(";
	aft = ")";
    }

    if (gPlayer->notmet_me(pobj))
	return pre + LANG_ADDART(shadow_who->query_nonmet_name()) + aft;
    else
	return pre + query_met_name() + aft;
}

public string
query_Art_name(object pobj)
{
    return capitalize(query_art_name(pobj));
}

public string
query_the_name(object pobj)
{
    string pre = "", aft = "";

    if (!objectp(pobj))
	pobj = previous_object(-1);

    if (!objectp(gPlayer))
    {
	set_alarm(0.0, 0.0, dispel_magic_effect);
	return shadow_who->query_the_name(pobj);
    }
    if (!living(gPlayer))
	return LANG_THESHORT(gPlayer);

    if (!CAN_SEE(pobj, shadow_who) || !CAN_SEE_IN_ROOM(pobj))
	return LD_SOMEONE;
    if (shadow_who->query_prop(OBJ_I_HIDE))
    {
	pre = "[";
	aft = "]";
    }
    if (shadow_who->query_prop(OBJ_I_INVIS))
    {
	pre = "(";
	aft = ")";
    }

    if (gPlayer->notmet_me(pobj))
	return pre + LD_THE + " " + shadow_who->query_nonmet_name() + aft;
    else
	return pre + query_met_name() + aft;
}

public string
query_The_name(object pobj)
{
    return capitalize(query_the_name(pobj));
}

public varargs string
query_art_possessive_name(object pobj)
{
    return LANG_ADDART(query_art_name(pobj));
}

public varargs string
query_Art_possessive_name(object pobj)
{
    return capitalize(query_art_possessive_name(pobj));
}

public varargs string
query_the_possessive_name(object pobj)
{
    return LANG_POSS(query_the_name(pobj));
}

public varargs string
query_The_possessive_name(object pobj)
{
    return capitalize(query_the_possessive_name(pobj));
}

public string *
parse_command_id_list()
{
    if (objectp(gPlayer))
	return gPlayer->parse_command_id_list();

    return shadow_who->parse_command_id_list();
}

public string *
parse_command_adjectiv_id_list()
{
    if (objectp(gPlayer))
	return gPlayer->parse_command_adjectiv_id_list();

    return shadow_who->parse_command_adjectiv_id_list();
}

// Okay some other functions to prevent abuse
void
attack_object(object victim)
{
    shadow_who->attack_object(victim);
    dispel_magic_effect();
}

void
attacked_by(object attacker)
{
    shadow_who->attacked_by(attacker);
    dispel_magic_effect();
}

varargs public mixed 
hit_me(int wcpen, int dt, object attacker, int attack_id, 
  int target_hitloc = -1)
{
    dispel_magic_effect();
    return shadow_who->hit_me(wcpen, dt, attacker, attack_id,
      target_hitloc);
}


int
query_avatar_shapeshift()
{
    return 1;
}
