// Weapon oil     /d/Avenir/common/bazaar/Obj/misc/wep_oil.c
// creator(s):    Lilith, 23 Feb 1996 
// revisions:     
// purpose:       This object will remove corrosion on weapons.
// note:          At present, it can be used 10 times.
//                Thanks to Plugh and Mercade, for holding my hand :)
// bug(s):           
// to-do:            
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

#include "/d/Avenir/common/common.h"
#include <cmdparse.h>
#include <formulas.h>
#include <macros.h>

#define OIL_TYPE     "_corrosion_removing_oil"

int oil_check;
string oil_desc();

void
create_object()
{
    oil_check = 10;
    set_name("bottle");
    set_pname("bottles");
    add_name(({OIL_TYPE}));
    set_adj("thick");
    add_adj(({"glass","blue-tinted"}));
    set_short("small bottle of bluish oil");
    set_pshort("small bottles of bluish oil");
    set_long("@@oil_desc@@");

    set_keep(1);
    add_prop(OBJ_I_VALUE,   100 + random(50));
    add_prop(OBJ_I_WEIGHT,  100 + random(50));
    add_prop(OBJ_I_VOLUME,  500 + random(100));
    add_prop(OBJ_I_VALUE,   100 + random(50));
    add_prop(OBJ_S_WIZINFO, "This object contains oil which can "+
       "be rubbed into weapons to reduce their corrosion. Just "+
       "<oil the [weapon]>.\n");

    add_item(({"oil", "blue oil", "blue-tinted oil"}),
       "The oil is tinted blue. It can be rubbed "+
       "into weapons to reduce their corrosion. "+
       "Just <oil the [weapon]>.\n");
}

string 
oil_desc()
{
    string str;
    switch(oil_check)
    {
        case 0: 
          str = "The bottle is empty.\n";
          break;
        case 1..2:
          str = "There is just a little bit of bluish oil inside.\n";
          break;
        case 3..4:
          str = "The bottle is about one-third full of bluish oil.\n";
          break;
        case 5:
          str = "The bottle is half-full of bluish oil.\n";
          break;
        case 6..7:
          str = "The bottle is two-thirds full of bluish oil.\n";
          break;
        case 8..9:
          str = "The bottle is almost completely filled with a bluish "+
                "oil.\n";
          break;
        case 10:
          str = "It is filled with a blue-tinted oil.\n";
          break;
        default:
          str = "It has some blue-tinted oil in it.\n";
          break;
    
    }

    return "A thick glass bottle. "+ str;
}


void
init()
{
    ::init();

    add_action("de_corr", "rub");
    add_action("de_corr", "wipe");
    add_action("de_corr", "oil");
}

void
get_bottle()
{
    object bottle;
    if (!oil_check)
    {
        seteuid(getuid());
        bottle = clone_object("/std/container");
        bottle->set_name("bottle");
        bottle->add_name(({"_std_potion_vial", "vial"}));
        bottle->set_adj("empty");
        bottle->set_long("An empty bottle. You could fill it with "+
            "fluid, perhaps a potion or some water.\n");
        bottle->add_prop(CONT_I_MAX_VOLUME, 1100);
        bottle->add_prop(CONT_I_MAX_WEIGHT, 1250);
        bottle->add_prop(CONT_I_VOLUME, 100);
        bottle->add_prop(CONT_I_WEIGHT, 250);
        if (bottle->move(environment(this_object())))
            bottle->move(environment(this_object()), 1);
        
        set_alarm(1.0, 0.0, remove_object);
    }
}


int 
de_corr(string str)
{
    object player = TP;
    object *oil_it, wep;
    int corr, rep;

    notify_fail("Do what? Perhaps you should try to oil a weapon with it.\n");
    if (!strlen(str))
	  return 0;

    notify_fail("There is no oil in the bottle!");
    if (!oil_check)
    {
        set_alarm(2.0, 0.0, get_bottle);
        return 0;
    }

    notify_fail("Do what? Try to <oil the [weapon]> instead.\n");
    if ( (!parse_command(str, player, "[the] %i", oil_it)) || 
         (!sizeof(oil_it = NORMAL_ACCESS(oil_it, 0, 0))) )
        return 0;

    notify_fail("You may oil only one weapon at a time.\n");
    if (sizeof(oil_it) > 1)        
        return 0;   
    else
        wep = oil_it[0];

    notify_fail("This oil is only useful on weapons.\n");     
    if (function_exists("check_weapon", wep) != "/std/weapon")
        return 0;

    corr = wep->query_corroded();
    rep = wep->query_repair_corr();    
    
    if (!F_LEGAL_WEAPON_REPAIR_CORR(rep + 1, corr))
    {
        oil_check--;    
        notify_fail("You give your "+ wep->short()+ " a prevent"+
              "ative oiling, hoping to keep corrosion at bay.\n");
        say(QCTNAME(player) +" adds some bluish oil "+
            "to a cloth and rubs it into "+ player->query_possessive() +
            " "+ wep->short() +".\n");
        return 0;
    }

    switch(corr - rep)
    {
        case 0:
            {
                notify_fail("You give your "+ wep->short()+ " a prevent"+
                    "ative oiling, hoping to keep corrosion at bay.\n");
                say(QCTNAME(player) +" adds some bluish "+
                    "oil to a cloth and rubs it into "+ 
                    player->query_possessive() +" "+ wep->short() +".\n");
            }
            return 0;
        case 1..3:
            write("You notice that your "+ wep->short() +" has become "+
                "corroded.\n");  
            break;          
        default:
            {
                notify_fail("You pour some oil onto a cloth and rub it "+
                    "gently into your "+ wep->short() +".\nDespite your "+
                     "efforts a few small spots of rust persist.\n");
                say(QCTNAME(player) +" adds some bluish oil "+
                    "to a cloth and rubs it into "+ player->query_possessive() +
                    " "+ wep->short() +".\n");
                --oil_check;
            }
            return 0;
    }           

    rep++;
    wep->set_repair_corr(rep);
    --oil_check;
    if (!oil_check)
        set_alarm(2.0, 0.0, get_bottle);
    write("You pour some oil onto a cloth and rub it gently into your "+
        wep->short() +".\nDirt, rust and dried blood flake away, and "+
        "your weapon gleams like new, with only a few tiny spots of "+
        "rust remaining.\n");
    say(QCTNAME(player) +" adds some bluish oil to a cloth and rubs it in"+
        "to "+ player->query_possessive() +" "+ wep->short() +".\n");
    return 1;
}
