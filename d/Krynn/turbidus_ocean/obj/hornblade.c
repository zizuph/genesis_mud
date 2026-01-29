/* Magical dagger wielded by sahuagin priestesses
 *
 * Arman - November 2020
 */

inherit "/std/weapon";
inherit "/d/Genesis/specials/examples/std_magic_lib";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

#define WATERBREATH   "/d/Krynn/turbidus_ocean/spells/waterbreathe"

void
create_weapon()
{
    set_name("hornblade");
    add_name("_narwhal_hornblade");
    add_name("blade");
    add_name("dagger");
    add_name("knife");
    set_adj("narwhal");
    add_adj("bone");
    set_short("narwhal hornblade");
    set_long("This long dagger is carved from the horn of a narwhal, " +
        "and is inscribed with inky black runes. Along its " + 
        "exceptionally long grip you notice a bony nub.\n");

    add_item(({"nub","bony nub"}), "There is a small bony nub on " +
        "the long grip of the narwhal hornblade that looks like " +
        "it could be pressed.\n");
    add_item(({"inky black runes","black runes","runes"}),
        "Black runes have been carved along this bone blade, " +
        "written in some Abyssal language... likely the sea devils " +
        "known as sahuagin.\n");
    add_cmd_item(({"runes","black runes","inky black runes"}),
        "read", "You are unable to translate these runes. They " +
        "are far too alien for your translation skills!\n");

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({50, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This is an enchanted long dagger " +
         "made from the horn of a narwhal. Apart from enhancements " +
         "that improve its damage and ability to hit, when the " +
         "nub on its grip is pressed it grants the wielder " +
         "water breathing.\n",15}));
    add_prop(OBJ_S_WIZINFO, "This weapon has high hit/pen for a knife " +
         "and when activated provides water breathing to its wielder. " +
         "it is wielded by Sahuagin Priestesses, " +
         "/d/Krynn/turbidus_ocean/living/sahuagin_priestess.c\n");

    set_default_weapon(35, 40, W_KNIFE, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2000);

   add_magic_obj_spell("[the] [bony] 'nub' [on] / [of] [the] [narwhal] [hornblade]",
       ({ "press" }), "/d/Krynn/turbidus_ocean/spells/waterbreathe.c");

    set_magic_obj_effect(({"_hornblade_waterbreath_shadow_"}));

    set_wf(this_object());
    seteuid(getuid(this_object()));
}

mixed 
wield(object what)
{
    add_magic_obj_effects(TP);
    return 0;
}

mixed 
unwield(object what)
{
    remove_magic_obj_effects(TP);
    return 0;
}

public status
verify_magic_obj_spell_cast(string arg, object spell)
{
    if(!this_object()->query_wielded())
    {
        write("You have to be wielding the narwhal hornblade to " +
            "activate it.\n");
        return 0;
    }

    if(WATERBREATH->has_spell_object(E(TO)))
    {
        write("The narwhal hornblade is already activated!\n");
        return 0;
    }

    if(WATERBREATH->query_ability_preparing(E(TO)))
    {
        write("The narwhal hornblade is currently activating!\n");
        return 0;
    }

    return 1;
}

void
init()
{
    ::init();
    
    /* required to use spell_commands from the std_magic_lib */
    init_spell_commands();
}

/*
 * Function:    leave_env
 * Description: Standard leave_env, removes magic effects and
 *              handles holdable object.
 * Arguments:   object from - the environment we are leaving.
 *              object to   - the environment we are entering.
 */
void
leave_env(object env, object to)
{
    /* Required to remove the previously added effects to the item */
    remove_magic_obj_effects(env);
    
    ::leave_env(env, to);
} /* leave_env */

/*
 * Function:    cmd_parse_spell_action
 * Description: Parses actions for spell commands and targets to trigger
 *              spells added to the item.
 * Argument:    string arg - the argument which is parsed
 */
public int
cmd_parse_spell_action(string arg)
{
    int result = ::cmd_parse_spell_action(arg);
    
    if (!result)
        notify_fail("Press what? The bony nub on the narwhal " +
            "hornblade?\n");
    
    return result;
} /* cmd_parse_spell_action */
