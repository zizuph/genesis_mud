
/*  The light object of the Heralds of the Valar
 *  Modified from the candle.c
 *  by Sir Denbarra of Gondor
 *  7 May 1995
 *  Modified to serve as special language for the Heralds
 *
 *  Updated and modified for the new spellcasting system.
 *  By Igneous Feb, 98
 */

#include "../spells.h"

inherit "/std/object";
inherit SPELL_OBJECT;

void
create_object()
{
    set_name("mic");   /* extra unique name */
    add_name("_herald_mic");
    set_adj("sound");
    set_no_show();

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_S_WIZINFO, "This is the special voice of the Heralds of " +
      "the Valar guild, summoned to provide a secret language.");
}

varargs int
dispell_spell_effect(object dispeller)  
{
    spell_target->catch_tell("Your powerful voice dwindles and you begin "+
      "to speak normally again.\n");
    tell_room(environment(spell_target), "The powerful speaking voice of "+ 
      QTNAME(spell_target)+ " returns to normal.\n", spell_target);
    remove_spell_effect_object();
    return 1;
}

int
start()
{
    set_spell_effect_desc("lammen voice object");
    if (!::start())
    {
	remove_spell_effect_object();
	return 0;
    }
    move(spell_target, 1);
    set_alarm(1800.0, 0.0, dispell_spell_effect);
}

int
query_understand_speak(object ob)
{
    if (IS_MEMBER(ob))
	return 1;
    if (ob->query_skill(SS_LANGUAGE) > 65)
	return 1;
    if (ob->query_wiz_level())
	return 1;

    return 0;
}

int
speak(string str)
{
    object *ppl, *understand;

    if (!stringp(str) || !strlen(str))
    {
	notify_fail("What do you wish to speak?\n");
	return 0;
    }
    ppl = filter(all_inventory(environment(spell_target)), living);
    ppl = ppl - ({spell_target});
    understand = filter(ppl, query_understand_speak);

    spell_target->catch_tell("In the voice of Manwe you speak: "+str+"\n");
    understand->catch_msg(QCTNAME(spell_target) +" speaks in a high "+
      "and beautiful tongue: "+ str +"\n");
    (ppl - understand)->catch_msg(QCTNAME(spell_target) + " says "+
      "something in a high unknown tongue, which are unable to "+
      "decipher.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(speak, "speak");
}
