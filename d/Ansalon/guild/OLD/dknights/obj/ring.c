#pragma strict_types

inherit "/std/armour";
inherit "/d/Genesis/newmagic/spellcasting";
#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <comb_mag.h>
#include <stdproperties.h>
#include <composite.h>
#include "../local.h"

void
add_spells()
{
    setuid();
    seteuid(getuid());
/*
//  Add the rose knight spells.
    if (TP->test_bit("ansalon", 3, 9))
    {
        add_spell(SPELL_DIR + "pwk");
        add_spell(SPELL_DIR + "pws");
        add_spell(SPELL_DIR + "pwb");
    }
    
//  Add the sword knight spells.
    if (TP->test_bit("ansalon", 3, 8))
    {
        add_spell(SPELL_DIR + "fireball");
        add_spell(SPELL_DIR + "wallofice");
    }
    
//  Add the crown knight spells.
    if (TP->test_bit("ansalon", 3, 7))
    {
        add_spell(SPELL_DIR + "symbolofpain");
        add_spell(SPELL_DIR + "symboloffear");
    }
*/

//  Add the squire spells.
    add_spell(SPELL_DIR + "identify");
    add_spell(SPELL_DIR + "fireball");
    add_spell(SPELL_DIR + "fear");
    add_spell(SPELL_DIR + "pwk");
    add_spell(SPELL_DIR + "pws");
    add_spell(SPELL_DIR + "pwb");
}

void
create_armour()
{
    set_name("ring");
    add_name(GUILD_EMBLEM_ID);
    set_adj("crystal");
    add_adj("charred");
    set_short("charred crystal ring");
    set_at(A_ANY_FINGER);
    set_long("@@my_long");

    add_prop(OBJ_M_NO_DROP, "You find it impossible to drop your "+short()+".\n");
    add_prop(DKNIGHT_ARMOUR,1);
    add_prop(OBJ_M_NO_GET,  1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT,  50);
    add_prop(OBJ_I_VOLUME,  30);
    add_prop(DKNIGHT_ARMOUR, 1);
    remove_prop(OBJ_I_VALUE);
    set_may_not_recover();
 
    add_item(({"flame", "light"}),"The flame looks brightly within "+
               "the crystal ring.\n");
 
    add_item(({"word", "word"}),"The words read:\n"+
                                "'help knights'.\n");

    add_spells();

}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    add_spell_object(env);
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}

public void
remove_object()
{
    cleanup_spells();
    /* Remove any cloned instances of spells that are registered with this
     * spellcasting object so that they aren't sitting around just taking up
     * memory.  You can either call remove_object() in the spells yourself,
     * or use the utility function cleanup_spells() to do it.
     */
    ::remove_object();

}



public void
list_spells()
{
    mapping spells;
    string *verbs;
    int i;
    object ob;


    /* sort the verbs */

    write(
        "  ______________________________________________________________\n" +
        " / \\                                                            \\ \n" +
        "( / )                                                            ) \n"+
        " \\\\/____________________________________________________________/ \n" +
        " |                                                             |\n" +
        " |  Lord Soth has granted you access to the following spells:  |\n" +
        " |                                                             |\n"
        );
     write(
        " |   Detect Magic     - Identify an items magical properties.  |\n");
     write(
        " |   Cause Fear       - Attempt to frighten a single target.   |\n");
     write(
        " |   Fireball         - Conjure a ball of fire can strike a    |\n"+
        " |                      single target.                         |\n");
     write(
        " |   Symbol of Pain   - Summons an arcane symbol that will     |\n"+
        " |                      cause pain to everyone in a room.      |\n");
     write(
        " |   Symbol of Fear   - Summons an arcane symbol that might    |\n"+
        " |                      frighten everyone in a room.           |\n");
     write(
        " |   Wall of Ice      - Conjures a wall of ice that will block |\n"+
        " |                      one exit.                              |\n");
     write(
        " |   Power Word Blind - Utter an arcane word to blind a single |\n"+
        " |                      target.                                |\n");
     write(
        " |   Power Word Stun  - Utter an arcane word to stun a single  |\n"+
        " |                      target.                                |\n");
     write(
        " |   Power Word Kill  - Utter an arcane word to damage a       |\n"+
        " |                      single target.                         |\n");
    write(
        " | ____________________________________________________________|\n" +
        " //\\                                                            \\ \n" +
        "( \\ )                                                            ) \n"+
        " \\_/____________________________________________________________/ \n"
        );
}
