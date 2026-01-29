/* The base for magical dragonarmour (body and arms)
 * uses the updated version of add_magic_effect (03/95)
 * added making it keepable (01/97) Teth
 *
 * Aridor, 03/95
 *

 * Carnak September 2016, Added effects based on the color and moved magic
 *                        properties below create_dragon_armour to allow for
 *                        magic_am_id_info to reveal the new effects.
 */ 

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

private string color        = "uncolored";
private int resist_elem     = 25;

public string    color_protection();

void
create_dragon_armour()
{
}

nomask void
create_armour()
{
    set_name("armour");
    add_name("scale");
    add_name("dragonscale");
    set_ac(45);
    /* NOTE: 45 is the basic ac for the BODY, the ARMS have a lower ac (39)*/
    set_at(A_BODY | A_ARMS);
    set_af(TO);
    add_adj(({ color, "dragonscale"}));
    set_long("It is a body armour made from @@query_color@@ dragon scales. " +
	     "Therefore it must be especially protective. You can feel " +
	     "a strange power radiating from the armour and you " +
	     "@@query_feeling_about_armour@@.\n");
    set_keep(1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 8040);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(45, A_BODY));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(45) + 1000); /* it is magical! */
    add_prop(OBJ_I_COLORABLE, 1);
    create_dragon_armour();
    add_prop(OBJ_S_WIZINFO,"This armour is made from the scales of a " +
	     "dragon. A Krynnian dragon is magical, thus transferring it " +
	     "to this armour. Anyone with dis < 50 cannot wear this armour " +
	     "and anyone with alignment > 200 will get mana reduced a " +
	     "little when wearing it. Anyone wearing it with " +
	     "alignment > 100 will get hurt when removing it. If the " +
	     "person is not strong enough, he won't even be able to remove " +
	     "the armour again. The magic of the dragon provides " +
	     "resistance elements matching its color. " +
         "red/fire, blue/lightning, white/cold, green/poison, black/acid.\n");
    add_prop(MAGIC_AM_ID_INFO,
	     ({"This armour is made from the scales of a Krynnian dragon. " +
		 "A Krynnian dragon is magical and so is this armour.\n", 5,
		 "Anyone weak in self-control cannot wear this armour.\n",20,
		 "Any goodaligned player wearing it can get hurt since this " +
		 "armour has been made from the scales of an evil dragon.\n",
		 40,"There is a special protection from this armour against " +
		 "natural threats.\n",50, 
                 "This armour protects the wearer against " +
                 color_protection() + ".\n", 70}));
    add_prop(MAGIC_AM_MAGIC,({100, "enchantment"}));
}

set_color(string new_color)
{
    remove_adj(color);
    color = new_color;
    set_short(0);
    set_adj(color);
    set_short(color + " dragonscale armour");
    remove_prop(MAGIC_AM_ID_INFO);
    add_prop(MAGIC_AM_ID_INFO,
	     ({"This armour is made from the scales of a Krynnian dragon. " +
		 "A Krynnian dragon is magical and so is this armour.\n", 5,
		 "Anyone weak in self-control cannot wear this armour.\n",20,
		 "Any goodaligned player wearing it can get hurt since this " +
		 "armour has been made from the scales of an evil dragon.\n",
		 40,"There is a special protection from this armour against " +
		 "natural threats.\n",50, 
                 "This armour protects the wearer against " +
                 color_protection() + ".\n", 70}));
}

string
query_color()
{
    return color;
}

public string
color_protection()
{
    switch ( query_color() )
    {
        case "red":
            return "fire";
        case "blue":
            return "electricity";
        case "white":
            return "cold";
        case "black":
            return "acid";
        case "green":
            return "poison";
        default:
            return "fire";
    }
}

string
query_feeling_about_armour()
{
    int ali = TP->query_alignment();
    if (ali > 200)
      return "feel very uneasy about it";
    if (ali > 100)
      return "feel uneasy about it";
    if (ali > -100)
      return "feel nothing about it";
    return "feel comfortable with it";
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
        switch ( query_color() )
        {
            case "red":
                if ( prop == MAGIC_I_RES_FIRE )
                    return ({ resist_elem, 1 });

            break;
            case "blue":
                if ( prop == MAGIC_I_RES_ELECTRICITY )
                    return ({ resist_elem, 1 });

            break;
            case "white":
                if ( prop == MAGIC_I_RES_COLD )
                    return ({ resist_elem, 1 });

            break;
            case "green":
                if ( prop == MAGIC_I_RES_POISON )
                    return ({ resist_elem, 1 });

            break;
            case "black":
                if ( prop == MAGIC_I_RES_ACID )
                    return ({ resist_elem, 1 });

            break;
            default:
                if ( prop == MAGIC_I_RES_FIRE )
                    return ({ resist_elem, 1 });

            break;
        }
    }
    else
    {
        return ::query_magic_protection(prop, protectee);
    }
}

mixed
wear(object what)
{
    if (TP->query_stat(SS_DIS) < 50)
      {
	  TP->add_mana(-100-random(200));
	  TP->add_panic(20 + random(20));
	  TP->heal_hp(-20-random(50));
	  say(QCTNAME(TP) + " shudders uncontrollably as " + PRONOUN(TP) +
	      " unsuccessfully tries to wear the " + what->short() + ".\n");
	  return "You try to wear the " + what->short() + " over your " +
	    "shoulders, but you have to give up as you cannot " +
	    "get yourself to wear such powerful armour. " +
	    "The effort alone leaves you drained and afraid.\n";
      }
    if (TP->query_alignment() > 200)
      {
	  TP->add_mana(-random(100));
	  TP->catch_msg("You get an uneasy feeling as you wear the " +
			what->short() +  " over your shoulders. You feel " +
			"a little drained.\n");
	  say(QCTNAME(TP) + " wears the " + what->short() + ".\n");
	  TP->add_magic_effect(TO);
	  return 1;
      }
    TP->add_magic_effect(TO);
    return 0;
}

mixed
remove(object what)
{
    int str = wearer->query_stat(SS_STR);
    if (TP->query_alignment() > 100)
      {
	  if (15 * str > wearer->query_alignment())
	    {
		wearer->catch_msg("Ouch! The armour sticks to your body! " +
				  "You have to pull hard and finally you " +
				  "succeed.\n");
		wearer->heal_hp(-50 - random(str));
		wearer->remove_magic_effect(TO);
		return 0;
	    }
	  else
	    {
		wearer->heal_hp(-100 - random(str));
		wearer->catch_msg("Ouch! The armour sticks to your body! " +
				  "You pull with all your strength but " +
				  "you are unable to remove the " +
				  what->short() + ". " + "Instead, you " +
				  "have only hurt yourself!\n");
		tell_room(QCTNAME(wearer) + " tries unsuccessfully to " +
			  "remove the " + what->short() + ".\n", wearer);
		return -1;
	    }
      }
    wearer->remove_magic_effect(TO);
    return 0;
}

varargs int
query_ac(int hid)
{
    if (hid & A_ARMS)
      return (::query_ac(hid) - 6);
    return ::query_ac(hid);
    
}
