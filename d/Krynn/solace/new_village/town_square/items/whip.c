/* 
 ** Zahrtok's Whip
 ** Created By Leia
 ** Code Help Provided By Louie
 ** June 19, 2005
 */

/*
 ** Last Updated By:
 ** Leia
 ** July 1, 2005
 */

/*
 ** Idea Submitted By
 ** Anahita
 */

/** Navarre Oct 20th 2009, Fixed keep/unkeep. */
/** Cotillion Dec 2014, Cleaned up, fixed runtime */

inherit "/std/weapon";
inherit "/lib/keep";

#include "/d/Krynn/common/defs.h";
#include "../local.h"
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <filter_funs.h>
#include <stdproperties.h>

private int charge_counter;
int do_charge(string str);

#define HIT 42
#define PEN 38

/* Make the general whip. */
public void
create_weapon()
{
    set_name("whip");
    add_name(({"club","weapon"}));
    set_adj("long");
    add_adj("dragon-skin");
    add_adj("dragonskin");
    add_adj("dragon skin");
    set_short("long dragon-skin whip");
    set_pshort("long dragon-skin whips");
    set_long("This is a very long whip, with the cord itself being made of the finest chromatic dragon-skin. The handle is made from hard oak and has been carved in the shape of a dragon who is curled perfectly to fit in your hand. The whip is cold to the touch, as though it held the souls of a million dead.\n");
        
    charge_counter = 1;
        
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 100, "death"}));
            
    add_prop(MAGIC_AM_ID_INFO,
        ({"This weapon is the type that would belong to a harsh slave driver. It would most likely make any enemy formiddable in combat.", 20,
          "This weapon is the type that would belong to a harsh slave driver. Such whips have been known to build up ferocity, and draw the soul from an enemy during combat.", 50}));
    add_prop(OBJ_S_WIZINFO, "This weapon is a weapon for both good aligned and evil aligned people. It builds up counters during combat and does a cool looking special that does some damage. This weapon is cloned to Zahrtok in Solace Town Square.");
    add_prop(OBJ_M_NO_BUY, 1);
    set_default_weapon(HIT, PEN, W_CLUB, W_SLASH, W_LEFT);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_CLUB));
    set_wf(this_object());
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_VOLUME, 2750);
}

/* Make the chargeup action. */
void
init()
{
    ::init();
    add_action(do_charge, "chargeup");
}

/* Allow wizards to chargeup the whip with the command 'charge up'. */
int
do_charge(string str)
{
    if (!this_player()->query_wiz_level())
        return 0;
        
    this_player()->catch_tell("WIZINFO: Charging up!\n");
    charge_counter = 1000;
        
    return 1;
}

/* Wield message. */
public mixed
wield(object obj)
{
        write("As you wield the whip, it feels cold. It feels as merciless as its former master. You growl, ready to take on anyone who crosses your path.\n");
        say("As " + QTNAME(this_player()) + " wields the " + query_short() + ", " + HE(this_player()) + " lets loose a deep growl.\n"); 
        return 1;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    string *how, descrip; 
    string loc_id;
    int penet;
    string *what = ({"slashing","lacerating","cutting","gashing"});
    object who = E(TO);
    object welt;

    if (!objectp(who) || !objectp(enemy))
    {
        return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }
    
    /* Add a charge when damage is done. */
    if (dam > 0)
        charge_counter++;
    
    /* Decide if the special will be done. */
    if((dam <= 20) || random(4) || (charge_counter < 8))
    {
        return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
    }

    /* How the whip flies through the air. */
    switch(random(5))
    {
        case 0: descrip = "rips through the air";
            break;
        case 1: descrip = "zips through the air";
            break;
        case 2: descrip = "whistles through the air";
            break;
        case 3: descrip = "zings through the air";
            break;
        case 4: descrip = "flies through the air";
            break;
        default: descrip = "does a really weird thing (bug this!)";
    }
    
    /* Decide the location the special will hit. */
    
    /* Special for humanoids */
    if (enemy->query_humanoid())
    {
        switch(random (15))
        {
            case 0: loc_id = "right forearm";
                break;
            case 1: loc_id = "left forearm";
                break;
            case 2: loc_id = "right shoulder";
                break;
            case 3: loc_id = "left shoulder";
                break;
            case 4: loc_id = "right thigh";
                break;
            case 5: loc_id = "left thigh";
                break;
            case 6: loc_id = "right cheek";
                break;
            case 7: loc_id = "left cheek";
                break;
            case 8: loc_id = "right hand";
                break;
            case 9: loc_id = "left hand";
                break;
            case 10: loc_id = "right shin";
                break;
            case 11: loc_id = "left shin";
                break;
            case 12: loc_id = "chest";
                break;
            case 13: loc_id = "stomach";
                break;
            case 14: loc_id = "bottom";
                break;
        }
    }
    
    /* Special non-humanoids. */
    if (!enemy->query_humanoid())
    {
        loc_id = hdesc;
    }

    /* Message for the special. */    
    who->catch_tell("Your " + short() + " suddenly " + descrip + ", " + what[random(sizeof(what))] +" " + enemy->query_the_name(who)+ " on " + HIS(enemy) + " " + loc_id + " and drawing upon " + HIS(enemy) + " soul!\n");
    enemy->catch_tell(capitalize(who->query_the_name(enemy)) + "'s " + short() + " suddenly " + descrip + ", " + what[random(sizeof(what))] + " you on your " + loc_id + ". You feel your spirit weaken!\n");
    who->tell_watcher(QCTNAME(who)+"'s " + short() + " suddenly " + descrip+", " + what[random(sizeof(what))] + " " + QTNAME(enemy) +" on " + HIS(enemy) + " " + loc_id + ". " + QTNAME(enemy) + "'s fervor for combat seemingly weakens!\n", enemy);

    /* Figure the damage to be done by special. */
    penet = MAX(2*dam + 30, 3*dam);
   
    /* Do the special damage. */
    enemy->hit_me(penet, MAGIC_DT, who, -1);
           
    /* Kill message. */
    if(enemy->query_hp() <= 0)
    {
        who->catch_tell("As your enemy falls before you, you are sure you see " + HIS(enemy) + " soul drawn from " + HIS(enemy) + " body and into the whip.\n");
        enemy->do_die(who);
        return 1;
    }
	else 
    {
        seteuid(getuid(this_object()));
        welt = clone_object(WELT);
        welt->set_welt_location(loc_id);
        welt->move(enemy, 1);
    }

    charge_counter -= 8;

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    return 1;
}

