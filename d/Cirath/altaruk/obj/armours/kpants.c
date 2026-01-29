inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

create_armour()
{
    set_name("pants");
    set_adj("red");
    add_adj("leather");
    set_short("red leather pants");
    set_long("Tight red speckled leather pants. Its made from" +
        " some sort of exotic animal hide. There are some runes" +
        " down on of the legs.\n");

    add_item(({"rune", "runes"}), "The runes are glowing" +
        " strangely.\n");

    set_ac(45);
    set_am(({ -3, 3, 0 }));
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(45, A_LEGS));
    add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_ARMOUR(45, A_LEGS) / 5);

    set_af(this_object());
    set_keep(1);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(45) + 100); 
    add_prop(OBJ_M_NO_BUY, "Nope! not for sale.");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "These boots are enchanted. ", 10,          
        "They have the virtues of the creature from whose hide "+
        "they were made. ", 30,
        "They are made from fire drake hide and are resistant to" +
        " damage by fire.\n", 50}));
    add_prop(OBJ_S_WIZINFO,
        "These boots are enchanted. They add MAGIC_I_RES_FIRE to 20.\n");
}

varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    if (query_prop(OBJ_I_IS_MAGIC_ARMOUR) && (protectee == query_worn()))
    {
        if (prop == MAGIC_I_RES_FIRE)
            return ({ 20, 1}); 
    } 
    else
    {
        return ::query_magic_protection(prop, protectee);
    }
}

mixed
wear(object ob)
{
    if (!query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        return 0;
    }

    if (wearer->query_mana() <= 25) 
    {
        return "You are too mentally exhausted to engage the "+ short() +
               "in a battle of wills\n";
    }

    wearer->add_mana(-25);    

    wearer->add_magic_effect(this_object());

    wearer->catch_tell("You feel a nice coolness spread through" +
        " your body as you wiggle into the pants.\n");

    return 0;
}

mixed
remove(object ob)
{
    wearer->remove_magic_effect(this_object());

    if (query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        wearer->catch_tell("The heat hits you like a fire as" +
            " the coolness subsides.\n");
    }

    return 0;
}


public int
disenchant_object(object disenchanter)
{

    remove_prop(OBJ_I_IS_MAGIC_ARMOUR);
    remove_prop(MAGIC_AM_MAGIC);
    add_prop(MAGIC_AM_ID_INFO, ({ 
        "The boots once possessed some magical power, but it is " +
        "now gone.\n", 50 }));

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(45)); 

    remove_prop(OBJ_M_NO_BUY);

    if (query_worn())
    {
        wearer->remove_magic_effect(this_object());
    }

    tell_room(environment(this_object()), "The the runes on " +
        " red leather pants suddenly fades!\n");

    remove_item("fur");
    add_item(({"rune", "runes"}), "The runes are glowing" +
        " strangely.\n");

    return 1;
}
