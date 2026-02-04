/*
 * /d/Terel/mountains/ghastly_keep/arm/gkeep_spellbook.c
 *
 * Sleepwalker, Grimoire of Knowledge
 *
 *  Created by Znagsnuf.
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                  Gorboth
 *  26/04-17                   Fixed a bug when removing the item      Znagsnuf
 *  15/05-17                   Made it keepable                        Znagsnuf
 *  15/05-17                   Made it recoverable                     Znagsnuf  
 *  23/12-20                   Added item expiration                  Cotillion
 *  2021-12-29                 Add spellpower of 48                      Zizuph
 *  2021-12-29                 Add 10 points death magic                 Zizuph
 */

inherit "/std/object";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

inherit "/lib/holdable_item";
inherit "/lib/item_expiration";
inherit "/lib/keep";

#include "defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <formulas.h>

int MAX_SKILL = 10;

int spellcraft_added = 0;
int death_added = 0;
int life_added = 0;

void
create_object()
{
    set_name("grimoire");
    add_name(({"book"}));
    set_adj("dark");
    set_short("dark grimoire");

    set_long("This book is old and lightweight. The cover feels hard and "
        + "delicate, and it has faded blue bindings. You run your fingers "
        + "over the gold lettering carefully before you open the cover. "
        + "Words appear and disappear as your eyes flit across "
        + "the pages, struggling to pick out anything of importance from "
        + "the jumble of sentences that comprise the world you have "
        + "become immersed in. The fragile old pages almost seem like "
        + "delicate snowflakes to the touch of your hand.\n");

    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 1200);

    //This has some value.
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(60)
                        + random(500) + 100);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_M_NO_BUY, 1);

    add_prop(MAGIC_AM_MAGIC, ({70,"enchantment"}) );

    add_prop(MAGIC_AM_ID_INFO, ({
        "You feel there is powers within these delicate covers. Hold it in "
        + "your hand to unleash its true power.\n", 20,
        "As your eyes flit across the pages, you read a single word among "
        + "the jumble of sentences: Knowledge.\n", 50,
        "You recognize this grimoire as: Sleepwalker, Grimoire of "
        + "Knowledge.\n", 70 }));

     add_prop(OBJ_S_WIZINFO, "This Grimoire of Power is held by Sabine in the "
             + "basement of the Ghastly Keep. :\n"
             + "    /d/Terel/mountains/ghastly_keep/npc/g_witch.c\n"
             + "This spellbook can be hold in any of your hands, and provides "
             + "spellcraft for the person holding it.\n");

    set_slots(W_ANYH);
    set_item_expiration();
    
    // This sets the strength of damage spells for holders of this item.
    set_magic_spellpower(48);
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
    init_item_expiration_recover(arg);
}

string
query_recover()
{
    return MASTER + ":" + query_item_expiration_recover() + query_keep_recover();
}


/*
 * Function name: hold
 * Description  : Called when the person wants to hold an item. This function
 *                may allow or disallow the object to be held, and it may
 *                print its own messages.
 * Returns      : string / int -
 *                 0 - The item can be held, print default messages.
 *                 1 - The item can be held, print no messages.
 *                     Messages were printed within the function.
 *                -1 - The item cannot be held. Print default messages.
 *                string - The item cannot be held. The string contains the
 *                         fail message.
 */
public mixed
hold()
{

    TP->catch_msg("As you hold the "+TO->short()+" "+query_slot_desc(TP)+", "
                 +"you feel a deep dark connection.\n");

    say(QCTNAME(TP) + " holds the " +TO->short() +" "+query_slot_desc(TO)+", "
        + "establishing a deep dark connection.\n");

    int spellcraft_added = min(MAX_SKILL,
       100 - TP->query_skill(SS_SPELLCRAFT));
    
    TP->set_skill_extra(SS_SPELLCRAFT, 
    (TP->query_skill_extra(SS_SPELLCRAFT) + spellcraft_added));

    int life_added = min(MAX_SKILL,
       100 - TP->query_skill(SS_ELEMENT_LIFE));

    TP->set_skill_extra(SS_ELEMENT_LIFE, 
    (TP->query_skill_extra(SS_ELEMENT_LIFE) + life_added));

    int death_added = min(MAX_SKILL,
       100 - TP->query_skill(SS_ELEMENT_DEATH));

    TP->set_skill_extra(SS_ELEMENT_DEATH, 
    (TP->query_skill_extra(SS_ELEMENT_DEATH) + death_added));

    return 1;
}

/*
 * Function name: release
 * Description  : Called when the person wants to release the item. This
 *                function may allow or disallow the object to be released,
 *                and it may print its own messages.
 * Returns      : string / int -
 *                 0 - The item can be relased, print default messages.
 *                 1 - The item can be relased, print no messages.
 *                     Messages were printed within the function.
 *                -1 - The item cannot be released. Print default messages.
 *                string - The item cannot be relased. The string contains the
 *                         fail message.
 */
public mixed
release()
{
    if (!query_held())
        return -1;

    object holder;
    holder = query_holder();

    holder->catch_msg("As you release the " + TO->short() + " from your " 
                  + "hand, you feel the deep dark connection fades.\n");
    
    say(QCTNAME(holder) + " release the " + TO->short() + " from " + 
    holder->query_possessive() + " hand, the deep dark connection fades.\n");

    holder->set_skill_extra(SS_SPELLCRAFT,
    (holder->query_skill_extra(SS_SPELLCRAFT) - spellcraft_added));
    spellcraft_added = 0;

    holder->set_skill_extra(SS_ELEMENT_LIFE, 
    (holder->query_skill_extra(SS_ELEMENT_LIFE) - life_added));
    life_added = 0;

    holder->set_skill_extra(SS_ELEMENT_DEATH, 
    (holder->query_skill_extra(SS_ELEMENT_DEATH) - death_added));
    death_added = 0;
    return 1;
}

/*
 * Function name: leave_env
 * Description  : When you inherit /lib/holdable_item.c you MUST also define
 *                the function leave_env() as copy of this function. It MUST
 *                make the call to holdable_item_leave_env(from, to) as well.
 *                If you omit this, then the item will not be automatically
 *                released when the player drops it, for instance.
 *                PS: This is just a dummy function. It does not exist. You
 *                    must write your own as copy of this one.
 * Arguments    : object from - the environment we are leaving.
 *                object to   - the environment we are entering.
 */

void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    holdable_item_leave_env(from, to);
}

/*
 * Function name: appraise_object
 * Description:   This is called when someone appraises this item.
 *                We want to mask it to add a message telling the
 *                appraiser that the item can be held.
 */
public void
appraise_object(int num)
{
    ::appraise_object(num);
    write(holdable_item_usage_desc());
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}


