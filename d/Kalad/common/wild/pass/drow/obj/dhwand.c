/*
 * By Antharanos
 *
 * Changes:
 * Revised, Aug'97 by Nikklaus, WIZINFO added.   
 *
 * 2006-07-01 - Cotillion
 * - Somehow players know that verb that there is no way to find out
 *   funny. :)
 *   Changed it so it's printed when the wand is used, add a time limit 
 *   between the wand uses.
 *   Changed command word also.
 *
 * 2009-02-23 - Cotillion
 *   Oops, players can carry multiple wands!
 *   It now recovers.
 *   3 min cooldown.
 *
 * 2009-04-08 - Lucius
 *   Fixed recovery to work with global mudlib change.
 *
 * 2016-06-13 - Lucius
 *   Fixed so magic ID mentions that you should 'utter'
 *   the command word.
 *
 * 2016-08-01 - Arman
 *   Added holdable_item functionality and 'base wand' functions.
 * 
 * 2020-12-24 - Cotillion
 * - Added item expiration
 *
 * 2021-12-28 - Arman
 * - Added as a magic enhancer
 */
inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/item_expiration";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include "/d/Kalad/defs.h"

/* by Antharanos */
int uses = 5, last_used;

#define USE_INTERVAL  60*3
#define COMMAND_WORD  "q'ressuluquarvalsharess"
#define LAST_USED     "kalad_dhwand_use"

/* Prototypes */
int        do_heal(string str);

public void
create_wand()
{
    // Mask this function to customize the wand.
}

void
create_object()
{
    set_name("wand");
    set_adj("long");
    add_adj("thin");
    add_adj("onyx");
    set_long("@@my_long@@");

    add_prop(MAGIC_AM_MAGIC, ({ 25, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({ "It is a wand of healing.", 10,
				      "Utter the command word " + COMMAND_WORD + 
                      " to activate.", 30 }));
    
    add_prop(OBJ_I_VALUE,1728);
    add_prop(OBJ_I_WEIGHT,250);
    add_prop(OBJ_I_VOLUME,250);

    set_slots(W_ANYH);
    set_magic_spellpower(45);

    add_prop(OBJ_S_WIZINFO,
        "Five charges of 1000 hp healing. Utter the word " +
        COMMAND_WORD + " to activate charge.\n");

    // Call the create_wand function for customization purposes
    create_wand();

    set_item_expiration();
}

string
my_long()
{
    string empty_desc;
    if (uses < 1)
	empty_desc = "It feels powerless now.";
    else
	empty_desc = "It feels as if there is much power within.";
    return BS(
      "A wand as black as the heart of Lolth herself. " + empty_desc + "\n");
}
init()
{
    ::init();
    add_action(do_heal, "utter");
}

int
do_heal(string str)
{
    NF(capitalize(query_verb()) + " what?\n");

    if (!str || str != COMMAND_WORD)
	return 0;

    if(!TO->query_held())
    {
        NF("You have to be holding the wand to activate it.\n");
        return 0;
    }

    NF("The wand makes an unusual noise but nothing occurs.\n");
    if (uses < 1 || (time() - last_used) < USE_INTERVAL ||
        time() < (TP->query_prop(LAST_USED) + USE_INTERVAL))
	return 0;
    
    write("You utter the command word, " + COMMAND_WORD + 
	  ", and feel the soothing touch of the "+
	  "wand's power flow around your body, healing your wounds.\n");
    
    say(QCTNAME(TP) + " utters " + COMMAND_WORD + ", then you watch as miraculously "+
	TP->query_possessive() + " wounds close up and heal.\n");
    say(QCTNAME(TP) + " looks much better now!\n");

    TP->add_prop(LAST_USED, time());
    last_used = time();
    uses = uses - 1;
    TP->heal_hp(1000);
    
    return 1;
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
}

void
init_recover(string arg)
{
    mixed foo;
    sscanf(arg, "%s#du#%d#%s", foo, uses, foo);
    init_keep_recover(arg);
    init_item_expiration_recover(arg);
}

string
query_recover()
{
    return MASTER + ":#du#" + uses + "#" + query_keep_recover() + query_item_expiration_recover();
}

/*
 * Function name:        appraise_object
 * Description  :        This function needs to be overridden
 *                       for the wand to works properly
 * Arguments    :        int num
 *                       
 */
void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}