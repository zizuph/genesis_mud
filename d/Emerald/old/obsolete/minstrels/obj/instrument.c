inherit "/std/object";
inherit "/lib/holdable_item";

#include <wa_types.h>
#include <macros.h>

static public object spellob;
static public string spellname;

public void
create_minstrel_instrument()
{
}

nomask public void
create_object()
{
    set_name(({ "instrument", "_minstrel_instrument" }));
    
    create_minstrel_instrument();
    set_slots(W_BOTH);
}

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    /* Call this to make sure that the item is released if it is
     * being held.
     */
    holdable_item_leave_env(env, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);

    /* We must call this to show how this item can be held. */
    appraise_holdable_item();
}

public string
query_auto_load()
{
    return MASTER + ":";
}

public int
query_minstrel_instrument()
{
    return 1;
}

public void
start_spell(object ob, string spell)
{
    spellob = ob;
    spellname = spell;
}
