inherit "/std/object";
inherit "/lib/holdable_item";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_object()
{
    set_name("eye");
    set_adj("slimy");
    set_short("slimy eye");
    set_long("This is a big eye stalk cut from a beholder. Judging by "+
             "the size of the eye, you come to the conclusion "+
             "that this is one of the main eyes of the creature.\n");

    add_prop(OBJ_I_WEIGHT,  200);
    add_prop(OBJ_I_VOLUME,  200);
    add_prop(OBJ_I_VALUE, 30000);
    add_prop(MAGIC_AM_MAGIC, ({30,"enchantment"}));

    add_prop(MAGIC_AM_ID_INFO, ({ 
        "This eye contains the lifeforce of a beholder.\n" +
        "If a person holds this eye, it will pass on some resistance to magic.\n", 30}));
    
    add_prop(OBJ_S_WIZINFO, "This object gives 25 levels of " +
        "magical resistance.\n");

    set_slots(W_ANYH);
}


varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    if (prop == MAGIC_I_RES_MAGIC)
        return 25;
    return 0;
}

public mixed
hold()
{
    write("As you graps the " + short() + " in your hand, " +
          "a strange aura surrounds your body.\n");

    this_player()->add_magic_effect(this_object());
    return 1;
}

public mixed
release()
{
    this_player()->remove_magic_effect(this_object());
    return 0;
}

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}
