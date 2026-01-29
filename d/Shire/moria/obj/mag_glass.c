/*
 * magnifying_glass.c                   (C) Sir Rogon, 1994.
 *
 * The magnifying glass have some nice properties. First of all,
 * when you are using it (look through glass), you will see a
 * strange world upside down.
 *
 * However, the main feature of this item is to use it to 
 * decifer a text which describes how to take the Balrog.
 *
 * Also, it is an important object in the Quest of the Ogress.
 * With the star (~moria/obj/star.c), the Dwarven Alchemyst
 * will order you to visit him in his workroom.
 *
 * This item works as a skill raiser, in this way:
 *   SS_APPR_VAL  : + 10  
 *   SS_APPR_OBJ  : + 30
 *   SS_AWARENESS : + 10
 * 
 * Sir Rogon.
 */

inherit "/std/object";

#define RAISE_VAL  10
#define RAISE_OBJ  30
#define RAISE_AWARE   10

#include "defs.h"

int raised_val, raised_obj, raised_aware;

create_object()
{
    set_name("glass");
    set_short("simple magnifying glass");
    add_adj(({"simple", "magnifying"}));
    set_long("You are looking at a simple magnifying glass.\n" +
	     "You could probably use it to magnify an object.\n");
	     
    add_prop(OBJ_I_VALUE, 1420);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME,  45);
   TO->remove_object();   // A temporary solution, I really don't
                          // like this object and what it does.
}

init()
{
    ::init();
    add_action("do_magnify", "magnify");
    add_action("do_look", "look");
    add_action("do_exa", "exa");
    add_action("do_exa", "examine");
    add_action("do_appraise", "appraise");
}

int 
do_magnify(string arg)
{
    notify_fail("Magnify what?\n");
    write("You look at " + arg + " with the magnifying glass, " +
	  "and everything seems much bigger!\n");
    return 1;
}

int 
do_look(string arg)
{
    object obj;
    string what;

    if (!strlen(arg))
	return 0;
    if (parse_command(arg, INV(TP), "'in' / 'into' / 'through' [the] %o", obj)) {
	write("Whee!! What a strange view! It looks like everything " +
	      "have turned upside down.\n");
	return 1;
    }

    if (!parse_command(arg, INV(TP), "'at' [the] %s 'through' / 'using' [the] %o", what, obj))
	return 0;
    if (obj != TO)
	return 0;
    if (id(what))
	return notify_fail("I guess that would be impossible.\n");

    write("You look into the " + short() + " enhancing the details!\n");
    say(QCTNAME(TP) + " uses " + HIS_HER(TP) + " " + QSHORT(obj) + ".\n");
    return TP->command("look at " + what);
}

int 
do_exa(string arg)
{
    object obj;
    string rest;

    if (!parse_command(arg, INV(TP), "%s 'through' / 'using' / 'with' [the] %o", rest, obj))
	return 0;
    if (obj != TO)
	return 0;
    if (id(rest))
	return notify_fail("I guess that would be impossible.\n");
    write("You look into the " + short() + " enhancing the details!\n");
    say(QCTNAME(TP) + " uses " + HIS_HER(TP) + " " + QSHORT(obj) + ".\n");
    return TP->command("examine " + rest);
}

int
do_appraise(string arg)
{
    object obj, what;

    if (!parse_command(arg, INV(TP), "%o 'through' / 'using' / 'with' [the] %o", what, obj))
	return 0;

    if (obj != TO)
	return 0;
    if (id(what))
	return notify_fail("I guess that would be impossible.\n");
    
    write("You handidly ready your " + short() + " to " +
	  "get a clearer view.\n");
    return 0;
}

int
raise_skill(object who, int what, int raise)
{
    int skill_extra = who->query_skill_extra(what);
    int skill_base = who->query_base_skill(what);

    if (skill_base + skill_extra + raise > 100)
	raise = 100 - skill_base - skill_extra;

    who->set_skill_extra(what, raise + skill_extra);
    return raise;
}

int
lower_skill(object who, int what, int raise)
{
    int skill_extra = who->query_skill_extra(what);
    who->set_skill_extra(what, skill_extra - raise);
}

void
leave_env(object from, object dest)
{
    if (living(from)) {
	lower_skill(from, SS_APPR_VAL, raised_val);
	lower_skill(from, SS_APPR_OBJ, raised_obj);
	lower_skill(from, SS_AWARENESS, raised_aware);
    }
    ::leave_env(from, dest);
}

void
enter_env(object dest, object old)
{
    if (living(dest)) {
	raised_val = raise_skill(dest, SS_APPR_VAL, RAISE_VAL);
	raised_obj = raise_skill(dest, SS_APPR_OBJ, RAISE_OBJ);
	raised_aware = raise_skill(dest, SS_AWARENESS, RAISE_AWARE);
    }
    ::enter_env(dest, old);
}

int
get_the_alchemist()
{
    object alch = CONTROL->query_alchemist();

    if (living(alch)) {
	if (living(TP) && (TP == alch->query_saviour())) {
	    alch->fetch_the_glass(TP, TO);
	}
    }
}
