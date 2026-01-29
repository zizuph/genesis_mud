/**********************************************************************
 * - cloak.c                                                        - *
 * - Guild item for Thanar                                          - *
 * - Created by Damaris@Genesis 3/2004                              - *
 **********************************************************************/

#pragma strict_types

#include "/d/Raumdor/defs.h"
#include "guild.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/d/Genesis/newmagic/spellcasting";

public string 
query_auto_load()	{ return MASTER + ":"; }

public void
create_object()
{

    set_name("cloak");
    add_name(({"tunic","shirt","clothing", OBJECT_ID}));
    set_short("extravagant black silk cloak");
    set_pshort("extravagant black silk cloaks");
    set_long("This is an extravagant black silk cloak. "+
      "Followers of the illustrious Lord Thanar wear it "+
      "with pride. The length of the cloak has been dyed "+
      "black, and the lining has been dyed black as well. "+
      "For assistance type: <thhelp>.\n");
    add_spell("/d/Raumdor/guilds/thanar/spells/summon");
    set_layers(1);
    set_looseness(10);
    set_wf(this_object());
    set_slots(A_BODY | A_ARMS);
    add_item(({"clasp", "mithril clasp", "snake clasp"}),
      "The clasp is made and mithril and the design "+
      "is of a snake wrapped around a sword.\n");
    add_prop(OBJ_S_WIZINFO, "Thanar Racial Guild Item.\n");
    add_prop(OBJ_M_NO_DROP,"Oddly enough, you can't seem to "+
      "do that.\n");
    add_prop(OBJ_M_NO_GIVE, "It's sentimental value is too high "+
      "for you to simply give it away.\n");
    add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it uninteresting.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_VALUE, 100);
}

public int
wear(object item)
{
    write("You slip the " + short() + " around your shoulders and " +
      "fasten the mithril clasp.\n");
    say(QCTNAME(TP) + " slips the " + short() + " around " +
      HIS(TP) + " shoulders and fastens the mithril clasp.\n");
    return 1;
}

public int
remove(object item)
{
    write("You slip the " + short() + " off over your head.\n");
    say(QCTNAME(TP) + " slips the " + short() +
      " off over " + HIS(TP) + " head.\n");
    return 1;
}
void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (IS_MEMBER(env) || env->query_wiz_level())
        add_spell_object(env);
}
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);

}

