inherit "std/armour.c";
inherit "/lib/keep";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

private string   color = "fur-trimmed"; 
public string    color_protection();
public string    color_element_skill_bonus();
public string    query_color();

private int resist_elem = 25;
private int skill_bonus = 10;
private int skill_type;

int bonus_added;

void
create_magi_armour()
{
}

nomask void
create_armour()
{
    set_name("robe");
    set_ac(30);
    set_at(A_ROBE);
    set_af(TO);

    set_adj("magi");
    add_adj(color);
    set_short("magi robe");
    set_long("This @@query_color@@ robe is covered with arcane runes, " +
       "an ostentatious and garishly-designed piece of apparel for " +
       "someone who clearly wants to be perceived as a wizard!\n");

    add_prop(OBJ_I_VOLUME, 4750);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(30, A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30));

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, "This is the robe worn by the Tharkadan " +
       "ogre magi /d/Krynn/tharkadan/living/ogre_magi.c. When cloned " +
       "it has a 40% chance of being a non-magical - yet decent ac - " +
       "robe. There is otherwise a 10% chance of a robe providing a " +
       "bonus 10 skill points to one of the six SS_ELEMENT_* skills, " +
       "plus 25 resistance to the opposite element (i.e. +10 life " +
       "element skill +25 death element resistance.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 75, "enchantment" }) );

    create_magi_armour();
}

public void
set_color(string new_color)
{
    remove_adj(color);
    color = new_color;
    set_short(0);
    set_adj(color);
    set_short(color + " magi robe"); 
    remove_prop(MAGIC_AM_ID_INFO);

    if(new_color != "fur-trimmed")
        add_prop(MAGIC_AM_ID_INFO, ({
            "This robe is the magical creation of a powerful ogre " +
            "magi. It will enhance the " +color_element_skill_bonus()+ 
            " magic knowledge for those already skilled, and protect "+
            "the wearer against " + color_protection() + " magic.\n", 60}));                        
}

public void
random_set_color()
{
    int random_value = random(100);

    // 40% chance non-magical robe, 10% chance of 6 magical varieties

    switch(random_value)
    {
       case 0..39:
        set_color("fur-trimmed");
        remove_prop(OBJ_I_IS_MAGIC_ARMOUR);
        remove_prop(MAGIC_AM_MAGIC);
        remove_prop(MAGIC_AM_ID_INFO);
        break;
       case 40..49:
        set_color("red-trimmed");
        break;
       case 50..59:
        set_color("blue-trimmed");
        break;
       case 60..69:
        set_color("white-trimmed");
        break;
       case 70..79:
        set_color("purple-trimmed");
        break;
       case 80..89:
        set_color("brown-trimmed");
        break;
       case 90..99:
        set_color("grey-trimmed");
        break;
       default:
        set_color("fur-trimmed");
        remove_prop(OBJ_I_IS_MAGIC_ARMOUR);
        remove_prop(MAGIC_AM_MAGIC);
        remove_prop(MAGIC_AM_ID_INFO);
        break;
    }
}

string
query_color()
{
    return color;
}

public string
color_element_skill_bonus()
{
    switch ( query_color() )
    {
        case "red-trimmed":
            return "fire";
        case "blue-trimmed":
            return "water"; 
        case "white-trimmed":
            return "life";
        case "purple-trimmed":
            return "death";
        case "brown-trimmed":
            return "earth";
        case "grey-trimmed":
            return "air";
        default:
            return "no_bonus";
    }
}

public int
color_element_skill_type()
{
    switch ( query_color() )
    {
        case "red-trimmed":
            return SS_ELEMENT_FIRE;
        case "blue-trimmed":
            return SS_ELEMENT_WATER; 
        case "white-trimmed":
            return SS_ELEMENT_LIFE;
        case "purple-trimmed":
            return SS_ELEMENT_DEATH;
        case "brown-trimmed":
            return SS_ELEMENT_EARTH;
        case "grey-trimmed":
            return SS_ELEMENT_AIR;
        default:
            return 0;
    }
}

public string
color_protection()
{
    switch ( query_color() )
    {
        case "red-trimmed":
            return "water";
        case "blue-trimmed":
            return "fire"; 
        case "white-trimmed":
            return "death";
        case "purple-trimmed":
            return "life";
        case "brown-trimmed":
            return "air";
        case "grey-trimmed":
            return "earth";
        default:
            return "no_prot";
    }
}


string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + color;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_color(a[1]);
    init_arm_recover(a[0]);
}

varargs mixed
query_magic_protection(string prop, object protectee = previous_object()) 
{
    if ( protectee == query_worn() )
    {
        switch ( color_protection() )
        {
            case "water":
                if ( prop == MAGIC_I_RES_WATER )
                    return ({ resist_elem, 1 });
            break;
            case "fire":
                if ( prop == MAGIC_I_RES_FIRE )
                    return ({ resist_elem, 1 });
            break;
            case "death":
                if ( prop == MAGIC_I_RES_DEATH )
                    return ({ resist_elem, 1 });
            break;
            case "life":
                if ( prop == MAGIC_I_RES_LIFE )
                    return ({ resist_elem, 1 });
            break;
            case "air":
                if ( prop == MAGIC_I_RES_AIR )
                    return ({ resist_elem, 1 });
            break;
            case "earth":
                if ( prop == MAGIC_I_RES_EARTH )
                    return ({ resist_elem, 1 });
            break;
            default:
                return ::query_magic_protection(prop, protectee);
            break;
        }
    }
    else
    {
        return ::query_magic_protection(prop, protectee); 
    }
}

void
add_skill_bonus(object who, int skill)
{
   write("As you wear the " +TO->short()+ " you feel your " +
      TO->color_element_skill_bonus()+ " magic knowledge enhanced!\n");
   who->set_skill_extra(skill, who->query_skill_extra(skill) + skill_bonus);
   return;
}

void
remove_skill_bonus(object who, int skill)
{
   write("As you remove the " +TO->short()+ " you feel your " +
      TO->color_element_skill_bonus()+ " magic knowledge decrease.\n");
   who->set_skill_extra(skill, who->query_skill_extra(skill) - skill_bonus);
   return;
}

public mixed
wear(object what)
{
    skill_type = TO->color_element_skill_type();

    if(TO->color_element_skill_bonus() != "no_bonus")
    {
       if(TP->query_skill(skill_type) > 0)
       {
          TO->add_skill_bonus(TP, skill_type);
          bonus_added = 1;
       }
    }

    TP->add_magic_effect(TO);
    return 0;
}

public mixed
remove(object what)
{
    set_this_player(query_worn());

    if(bonus_added)
    {
       TO->remove_skill_bonus(TP, skill_type);
       bonus_added = 0;
    }

    TP->remove_magic_effect(TO);
    return 0;
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    if(bonus_added)
    {
       TO->remove_skill_bonus(TP, skill_type);
       bonus_added = 0;
    }
}