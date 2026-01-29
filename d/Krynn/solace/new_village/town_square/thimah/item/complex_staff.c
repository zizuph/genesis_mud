/* 
** A Complex Medicine Stick
** Created By Leia
** June 18, 2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

/* Modified by Navarre March 30th 2006.
 * enemy->do_die moved below message to killer of enemy since
 * the message uses HE(enemy). It would return 0 otherwise.
 * The stick was also made keepable.
 */
inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include "/d/Krynn/common/defs.h";
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <filter_funs.h>
#include <stdproperties.h>

/* Kender prop, allows alter ability to change the descriptions of the weapon */
#define OBJ_I_CONVERT_HOOPAK "_obj_i_convert_hoopak"

private int charge_counter;
int do_charge(string str);

#define HIT 42
#define PEN 38

public void
create_weapon()
{
    set_name("stick");
    add_name("polearm");
    add_name("staff");
    add_name("medicine stick");
    set_adj("medicine");
    add_adj("complex");
    set_short("complex medicine stick");
    set_pshort("complex medicine sticks");
    set_long("This is a very complex medicine stick. " +
	     "It is made out of a single piece of wood " +
	     "with two intertwining branches. The bottom " +
	     "of the medicine stick is a sharp point while " +
	     "the top is a hard knob, good for bludgeoning. " +
	     "Tied right below the knob is a bag of some " +
	     "sorts, probably containing the ingredients to " +
	     "some hex.\n");
        
    charge_counter = 1;
        
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 100, "enchantment"}));
    
/* Kender prop, allows alter ability to change the descriptions of the weapon */
    add_prop(OBJ_I_CONVERT_HOOPAK, 1);
            
    add_prop(MAGIC_AM_ID_INFO,
	     ({"This weapon is the type that belongs to a great " +
	       "Shaman. It is most likely blessed with some form " +
	       "of magic, to aid him in combat.", 20,
               "The wielder, depending upon how he is aligned, " +
	       "may unlock magicks of health enhancement or dark energies " +
	       "of destruction to aid himself in combat.", 50}));
    add_prop(OBJ_S_WIZINFO, "This weapon is a weapon for both good " +
	                    "aligned and evil aligned people. It builds " +
	                    "up counters during combat, and if the " +
	                    "wielder has an alignment of 0 or above, " +
	                    "it will heal them, and if they have an " +
                            "alignment of below 0, it will damage " +
	                    "their enemy.");

    set_default_weapon(HIT, PEN, W_POLEARM, W_IMPALE | W_BLUDGEON, W_RIGHT);
    set_magic_spellpower(PEN);
    set_spellpower_elements(({
        SS_ELEMENT_LIFE, SS_ELEMENT_DEATH
    }));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_POLEARM));
    add_prop(OBJ_M_NO_BUY, 1);
    set_wf(this_object());
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_VOLUME, 2750);
}

void
init()
{
    ::init();
    add_action(do_charge, "chargeup");
}

/* Allows wizards to chargeup the stick with the command "chargeup". */
int
do_charge(string str)
{
    if (!this_player()->query_wiz_level())
        return 0;
        
    this_player()->catch_tell("WIZINFO: Charging up!\n");
    charge_counter = 1000;
        
    return 1;
}

/* Wield Message Based Upon Alignment */
public mixed
wield(object obj)
{

    if (this_player()->query_alignment() >=0)
    {
        write("The medicine stick feels good in your hand. Suddenly, you are overcome with a great, positive energy.\n");
        say("As " + QTNAME(this_player()) + " wields the medicine stick, " + HE(this_player()) + " begins to look more caring.\n"); 
        return 1;
    }
        
    if (this_player()->query_alignment() < 0)
    {
        write("The medicine stick feels good in your hand. Suddenly, you are overcome with a great, negative energy.\n");
        say("As " + QTNAME(this_player()) + " wields the medicine stick, " + HE(this_player()) + "begins to look more callous.\n");
        return 1;
    }
}


public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam,int penet,int heal_factor)
{
    string he_enemy = HE(enemy);

    /* Check for evil alignment */
    if(this_player()->query_alignment() < 0)
    {
        string *how, descrip; 
        /* Evil Weapon Special Descriptors */
        string *what = ({"injuring","hurting","harming","damaging"});
        object who = query_wielded();

        if(!objectp(who) || !objectp(enemy))
            return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

        /* Add a charge when damage is done. */
        if(dam > 0)
            charge_counter++;
    
        /* Decide if the special will be done. */
        if((dam <= 20) || random(4) || (charge_counter < 8))
            return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

        /* Descriptors for what the special will look like. */
        switch(random(5))
        {
            case 0: descrip = "flashes a bright green";
                break;
            case 1: descrip = "emits a eerie green glow";
                break;
            case 2: descrip = "sparks with green fire";
                break;
            case 3: descrip = "gives off a solid green beam of light";
                break;
            case 4: descrip = "begins to release green smoke";
                break;
            default: descrip = "does a really weird thing (bug this!)";
        }
                
        /* Special Message */        
        who->catch_tell("Your " + query_short() + " abruptly " + descrip +
			", " + what[random(sizeof(what))] +" " +
			enemy->query_the_name(who)+"!\n");
        enemy->catch_tell(capitalize(who->query_the_name(enemy)) +
			  "'s " + query_short() + " abruptly " + descrip +
			  ", " + what[random(sizeof(what))] + " you!\n");
        who->tell_watcher(QCTNAME(who)+"'s " + query_short() + " abruptly " +
			  descrip+", " + what[random(sizeof(what))] +
			  " " + QTNAME(enemy)+"!\n", enemy);

        /* Decide how much damage will be done by the special. */
        penet = MAX(2*dam + 30, 3*dam);
        
        /* Tells the wizard wielder the enemy's current HP.
        if(who->query_wiz_level())
        {
            who->catch_tell("WIZINFO: Enemy's current hp is: " + enemy->query_hp() + "!\n");
        } */
        
        enemy->hit_me(penet, MAGIC_DT, -1);
        
        /* Tells the wizard wielder the enemy's new HP.
        if(who->query_wiz_level())
        {
            who->catch_tell("WIZINFO: Enemy's new hp is: " + enemy->query_hp() + "!\n");
        } */
         
        /* Message for when the enemy is killed by the special. */        
        if(enemy->query_hp() <= 0)
        {
            who->catch_tell("You hear a throaty, animalistic laughter in your head as " + he_enemy + " dies.\n");
            enemy->do_die(who);
            return "";
        }
                
        /* Tells the wizard the damage done. */        
        if(who->query_wiz_level()) 
            who->catch_tell("WIZINFO: Damage done was " + penet + "!\n");

        charge_counter -= 8;
        return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }
    
    /* Check for true neutral or above alignment */
    if(this_player()->query_alignment() >= 0)
    {
        string *how, descrip;
        /* Good alignment special descriptors */
        string *what = ({"gently","softly","lightly","tenderly"});
        object who = query_wielded();

        if(!objectp(who) || !objectp(enemy))
            return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
        
        /* Add a charge when damage is done. */
        if(dam > 0)
            charge_counter++;
    
        /* Decide if the special will be done. */
        if((dam <= 20) || random(4) || (charge_counter < 8))
            return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

        /* Weapon special descriptors. */
        switch(random(5))
        {
            case 0: descrip = "flashes a bright green";
                break;
            case 1: descrip = "emits a eerie green glow";
                break;
            case 2: descrip = "sparks with green fire";
                break;
            case 3: descrip = "gives off a solid green beam of light";
                break;
            case 4: descrip = "begins to release green smoke";
                break;
            default: descrip = "does a really weird thing (bug this!)";
        }
                
        /* Special Message */        
        who->catch_tell("Your " + query_short() + " abruptly " + descrip +
			", " + what[random(sizeof(what))] +
			" bathing you in a healing glow!\n");
        enemy->catch_tell(capitalize(who->query_the_name(enemy)) +
			  "'s " + query_short() + " abruptly " + descrip +
			  ", " + what[random(sizeof(what))] + " bathing " +
			  HIM(who) + " in a healing glow!\n");
        who->tell_watcher(QCTPNAME(who)+" " + query_short() + " abruptly " +
			  descrip+", " + what[random(sizeof(what))] +
			  " bathing " + HIM(who) +
			  " in a healing glow!\n", enemy);
        
        /* Decide how much the wielder will be healed by. */
        heal_factor = MAX(dam*2 + 30, dam*3);
        
        /* Tells the wizard wielder his/her current HP.
        if(who->query_wiz_level())
        {
            who->catch_tell("WIZINFO: " + QCTNAME(who) + "'s current hp is: " + who->query_hp() + "!\n");
        } */
        
        /* Heals the wielder */
        who->heal_hp(heal_factor);
        
        /* Tells the wizard wielder his/her new HP.
        if(who->query_wiz_level())
        {
            who->catch_tell("WIZINFO: " + QCTNAME(who) + "'s new hp is: " + who->query_hp() + "!\n");
        } */
            
        /* Kill message if enemy dies on special. Not positive this is needed, but just in case. */        
        if(enemy->query_hp() <= 0)
        {
            enemy->do_die(who);
            who->catch_tell("You feel a pang of regret at having to cease another creature's life.\n");
            return "";
        }
                
        /* Tell the wizard wielder the extent of the heal. */        
        if(who->query_wiz_level()) 
        {
            who->catch_tell("WIZINFO: Heal was " + heal_factor + "!\n");
        }

        charge_counter -= 8;
        return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}