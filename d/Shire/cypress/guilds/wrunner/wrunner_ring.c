/* The Wild Runner ring. This is the symbol of the Wildrunners guild,     */
/* and proudly worn by many Elves. It also handles loading the soul.      */
/* Some code taken from the old Wild Runners ring allegedly by Mylos.     */
/* Based on the nose-ring made by Quis.                                   */
/* Totally recoded 28/08/95 by Tulix III to bring up to Grunts standard.  */
/* No longer loads the soul (see shadow), 
 * no longer auto loads (see shadow), 
 * no longer contains the "ground" command (see soul)
 * -- Shiva 12/04/96 
 * 
 * Updated for Cypress
 * Finwe, June 2001
 *
 * Added spell ability to ring
 * Finwe, Mar 2005
 */

#pragma save_binary

inherit "/std/armour";
inherit "/lib/wearable_item";
inherit "/d/Genesis/magic/spellcasting";
inherit "/lib/help";

// messenger spell
inherit "/d/Shire/cypress/guilds/wrunner/spells/messenger";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "wrunner_defs.h"
#include "/d/Shire/cypress/sys/defs.h"

void
create_armour()
{
    if (!IS_CLONE)
      return;
   
    set_help_dir(GUILD_HELP);
    set_help_category(({"wild", "wildelves"}));


    set_name("ring");
    set_adj("golden");
    add_adj("tiny");
    add_name(RING_ID);

    add_spell("call", "call for a swallow", create_messenger_spell,
      spell_target_caster_environment);
    
    set_long("This is a delicate looking ring of the Wild Elves. It is " +
        "made from white and yellow gold strands woven together in an " +
        "intricate design. The gold strands seem to weave in and out of " +
        "each other in a mesmerizing dance before your eyes. There seems " +
        "to be something magical about them and probably worth examining.\n");
    set_short("golden ring of the Wild Elves");

    add_item(({"white gold", "white gold strands", "white strands", 
            "white gold threads", "white threads"}),
        "They are woven together with yellow gold strands in the ring. " +
        "Etched onto the strands you see the words: Type 'help wild " +
        "elves' for more information.\n");
    add_item(({"yellow gold", "yellow gold strands", "yellow strands", 
            "yellow threads", "yellow gold threads"}),
        "They are woven together with white gold strands in the ring. " +
        "They radiate a natural magic that seem to glow before you. Words " +
        "appear on the strands that may be read.\n");
    add_item(({"strands", "threads", "strands of gold", "gold strands", 
            "threads of gold", "gold threads"}),
        "They are white and yellow colored. They are woven together in such " +
        "a way they create an intricate design before your eyes. Some words " +
        "are etched onto the strands.\n");
    add_item(({"words"}),
        "They are vibrant and seem to rise from the yellow gold strands " +
        "of the ring. \n");
    add_cmd_item("words", "read", "@@read_words@@");       
    set_ac(0);            /* Not much use as armour, to be honest */

    /* The ring can be worn on any finger*/
    set_slots(A_ANY_FINGER);
    set_layers(0);
    /* We allow multiple rings to be worn*/
    set_looseness(2);
   
    seteuid(getuid());    /* Needed for cmdsoul manipulation      */
    
    add_prop(OBJ_I_WEIGHT, 60);  /* Weight 60g */
    add_prop(OBJ_I_VOLUME, 3);   /* Volume 3ml */
    add_prop(OBJ_I_VALUE, 0);     /* Genuinely priceless */
    add_prop(OBJ_M_NO_DROP, "You won't even consider losing your ring.\n");
}

public string
query_recover()
{
    return 0;
}

void enter_env(object env, object from)
{
  ::enter_env(env, from);

    if (env->query_wiz_level() || !env->query_guild_member(GUILD_NAME))
    {
        remove_object();

        return;
    }
    else
        add_spell_object(env);

  // we don't want more than one ring at a time
  filter(all_inventory(env) - ({ this_object() }),
      &->id(RING_ID))->remove_object();

  
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}

string read_words()
{
    return  "The Wild Elves are a racial guild where you can express " +
        "yourself. To learn more about them, type 'help wild'.\n";
}