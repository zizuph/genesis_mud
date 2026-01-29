/*
 * File:     staff
 * Created:  Cirion, 1998.06.05
 * Purpose:  standard staff for the monks. Has some more
 *           interesting combat descriptions, etc.
 *           Based heavily on /d/Avenir/inherit/weapon.c (also
 *           by Cirion)
 * Modification Log:
 *
 */
#pragma strict_types
#pragma save_binary

#include "defs.h"
inherit "/std/weapon";           /* The normal weapon file   */
inherit MONKLIB;

#include <wa_types.h>   /* Weapon definitions, W_IMPALE, etc */
#include <macros.h>     /* QTNAME, etc                       */
#include <formulas.h>   /* F_LEGAL_DT                        */
#include <stdproperties.h>
#include <options.h>

/* The paths to the bruise objects */
#define BRUISE      MONK_OBJ + "bruise"

/* A few definitions to make combat messages easier
 * Uses the variables defined in did_hit, so can't be used
 * in any other functions.
 */
#define ME(x)   if(interactive(wield)) wield->catch_msg(x + ".\n");
#define YOU(x)  if(interactive(enemy)) enemy->catch_msg(x + ".\n");
#define THEM(x) wield->tell_watcher(x + ".\n", enemy);


void
create_weapon ()
{
    set_name ("staff");
    set_adj ("long");

    set_long ("It is a long wooden staff.\n");

    set_wt (W_POLEARM);
    set_hands (W_BOTH);
    set_dt (W_BLUDGEON);


    set_hit (8);
    set_pen (9);

    /* Now give the weapon some value, weight and volume */
    /* use standard functions, randomize to hide actual WC values */
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(8,9) + random(20) -10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(8,W_POLEARM) + random(50) - 25);

    /* calculate volume from weight */
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);

}


/*
 * Function name: get_damage_str_other
 * Description:   gives back a verb based on what sort of
 *                damage the weapons will be doing, person
 *                in the watcher
 * Arguments:     the damage type
 * Returns:       the verb
 * Note:          switches are slower than if-else statements,
 *                and since this is used often, let's be
 *                cpu-friendly at the cost of not being sexy
 */
private nomask string
get_damage_str_other(int dt)
{
  if(dt == W_IMPALE)
    return "stabs at";
  else if(dt == W_BLUDGEON)
    return "swings at";
  else if(dt == W_SLASH)
    return "slashes at";
  else
    return "aims for";
}

/*
 * Function name: get_damage_str_attacker
 * Description:   gives back a verb based on what sort of
 *                damage the weapons will be doing, person
 *                in the attacker
 * Arguments:     the damage type
 * Returns:       the verb
 * Note:          switches are slower than if-else statements,
 *                and since this is used often, let's be
 *                cpu-friendly at the cost of not being sexy
 */
private nomask string
get_damage_str_attacker(int dt)
{
  if(dt == W_IMPALE)
    return "stab at";
  else if(dt == W_BLUDGEON)
    return "swing at";
  else if(dt == W_SLASH)
    return "slash at";
  else
    return "aim for";
}

/*
 * Function name: get_hitloc_armour
 * Description:   returns the QSHORT of the armour covering the
 *                certain hitloc of a living
 * Arguments:     enemy - the person to check for
 *                hitloc - the hitloc string
 * Returns:       the QSHORT of the armour if any, otherwise 0
 * Note:          This is a nasty hack, but there appears no other
 *                way to get to the armour covering something from
 *                a string other than asking the poor, overused
 *                combat object.
 */
private nomask mixed
get_hitloc_covering(object enemy, string hitloc)
{
  object   cobj,
           armour;
  int      id,
           i,
          *hitloc_id;
  mixed    hits;

  /* Sanity check, enemy really exists? */
  if(!objectp(enemy) || !living(enemy))
   return 0;

  /* Everyone needs a combat object... */
  if(!objectp(cobj = enemy->query_combat_object()))
   return 0;

  /* Refer to the combat object to compare hitloc ids with
   * the string hitloc to search for.
   */
  hitloc_id = cobj->query_hitloc_id();
  for(i=0; i<sizeof(hitloc_id); i++)
  {
    hits = cobj->query_hitloc(hitloc_id[i]);
    if(hits[2] == hitloc)
    {
       id = hitloc_id[i];
       break;
    }
   }

   /* Did we find anything? */
   if(!id || !(armour = enemy->query_armour(id)))
     return 0;

  /* Is it a normal piece of armour? Seen, not no_show? */
  if(objectp(armour) && !armour->query_no_show() &&
     CAN_SEE(query_wielded(), armour))
   return QSHORT(armour);

  return 0;
}


/*
 * Function name: make_weapon_bruise
 * Description:   make a wound on the enemy look bruised by cloning a
 *                bruise subloc object and moving to the the enemy's
 *                inventory (just cosmetic ... does no real damage)
 * Arguments:     enemy  - the person the make bruised
 *                hitloc - the hitloc of the enemy
 * Returns:       0
 * Note:          
 */
private nomask void
make_weapon_bruise(object enemy, string hitloc)
{
   object    bruise;

    return; // ### disable for now


   /* Only make live (not undead) humanoids bleed */
   if((!interactive(enemy) && !function_exists("create_monster", enemy))
      || enemy->query_prop(LIVE_I_UNDEAD))
     return;

   /* We already have been bruised ... add on to that one */
   if(bruise = present("avenir_bruise", enemy))
   {
    bruise->add_hurt(hitloc);
    return;
   }

   /* Else clone a new one into the enemy's inventory */
   setuid();
   seteuid(getuid());

   bruise = clone_object(BRUISE);
    bruise->move(enemy, 1);
    bruise->add_hurt(hitloc);

   /* Make sure we are really there */
   if(!present(bruise, enemy))
    bruise->remove_object();
}

/*
 * Function name: did_hit
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. These weapons
 *                produce improved messages for most damage types
 *                (tho not magic dts)
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
 *                dam:   The actual damage caused by this weapon in hit points
 * Returns:       True if it handled combat messages, returning a 0 will let
 *                the normal routines take over. We do in fact
 *                handle most combat messages.
 * Note:          Examples of some of the variable values:
 *                aimfor: " the lower right arm of the tall guard"
 *                hwep: " with his long, vicious knife"
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam)
{
   /* Well, ok: these are a whole lot of variables, but I think it
    * is worth it to make the code _much_ more readable later on,
    * as is the case when you are using a lot of similiar text.
    */
   object     wield = query_wielded(); /* object wielded us    */
   string     me = QCTNAME(wield),/* The slender blue-eyed elf */
              his = wield->query_possessive(), /* "his"        */
              enem = QTNAME(enemy),  /* "the tall guard"       */
              wep = " " + QSHORT(this_object()), /* "long axe" */
              aim,       /* describer for what we are aiming   */
              aimfor,    /* the object of the string           */
              dstr,      /* the string corresponding to the dt */
              deflect,   /* armour that deflected our hit      */
              missstr,   /* string when we missed              */
              hitloc,    /* new and improved hitloc desc       */
              mdoes,     /* message the wielded will get       */
              edoes,     /* message the enemy will get         */
              odoes,     /* message the watchers will get      */
              hwep = " " + his + wep,
              whwep = " with" + hwep,
              wywep = " with your" + wep,
              nearly = "",
              verb,
              overb;

   /* Check the callback for update in the weapon's condition */
   ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

   /* Sanity check before we continue. Do we all exist?
    * Is our dt normal? Was there a hitloc we struck?
    */
   if(!objectp(wield) || !objectp(enemy) || 
      !F_LEGAL_DT(dt) || !stringp(hdesc))
    return 0;

   /* Get a more interesting hitloc desc for a humanoid, 
    * handled in /d/Avenir/inherit/hitloc. It will just
    * return the normal hdesc if enemy is not a normal humanoid.
    * Much safer that way.
    */
   hitloc = m_translate_hitloc(hdesc, enemy);

   /* Describer of what we are aiming for */
   aim = random(2) ? " the " + hitloc + " of " + enem :
                        " " + enem + "'s " + hitloc;

   /* We don't need to _always_ show the hitloc */
   aimfor = random(5) ? aim : " " + enem;


    /* Miss.
     * These happen quite often, so let's make the
     * message more interesting, based on the damage type of
     * the weapon and whether what we were aiming for is covered
     * by the enemy's armour.
     */
    if(phurt <= 0 || phit <= 0 || dam <= 0)
    {
        /* Is the enemy wearing armour over that hitloc? If so,
          * let's pretend that the miss was caused by the weapon
          * bouncing off the enemy's armour. The only problem with
          * this is that misses don't change the condition of the
          * armour, whereas this method implies that it would.
          */
         deflect = get_hitloc_covering(enemy, hdesc);

         if(stringp(deflect))
         {
           if(!random(3))
               missstr = ", but it bounces off ";
           else if(!random(3))
               missstr = ", but it is deflected by ";
           else
               missstr = ", but it glances off ";
          }


     /* Message for the attacker */
     dstr = get_damage_str_attacker(dt);
     if(stringp(deflect))
       mdoes = missstr + enemy->query_possessive() + " " + deflect;
     else
       mdoes = ", but miss";

     /* gag misses if the wielder has that option on */
     if (!wield->query_option(OPT_GAG_MISSES))
         ME("You " + dstr + aimfor + " with your"
           + wep + mdoes);

     /* Message for the watchers */
     dstr = get_damage_str_other(dt);
     if(stringp(deflect))
       odoes = missstr + enemy->query_possessive() + " " + deflect;
     else
       odoes = ", but misses";

     /* Gag misses for watchers if they have that option on */
     wield->tell_watcher_miss(me + " " + dstr + aimfor
         + " with " + his + wep + odoes + ".\n", enemy);

     /* Message for the enemy */
     if(stringp(deflect))
       edoes = missstr + "your " + deflect;
     else
       edoes = ", but misses";

     /* gag misses if the enemy has that option on */
     if (!enemy->query_option(OPT_GAG_MISSES))
         YOU(me + " " + dstr + " your " + hitloc + " with " + his + wep + edoes);

     return 1;
   }

   /* Moving right along, here we generate combat messages
    * based on the %hp of damage we did and the damage type
    * of the weapon.
    */


    /* Bruise him if we hit hard enough */
    if(phurt > 4 && random(80) < phit && enemy->query_hp())
      make_weapon_bruise(enemy, hitloc); /* Make 'em bruised */

    /* bump, hurt, smash, crush, slam, brush */
    switch (phurt)
    {
      case 0..4:
       verb = random(3) ? " brush" : " tap";
       overb = LANG_PSENT(verb);
       mdoes = verb + " your" + wep + " against" + aimfor;
       edoes = overb + hwep + " against your " + hitloc;
       odoes = overb + hwep + " against" + aimfor;
       break;
      case 5..9:
       mdoes = " bump" + aimfor + " with your" + wep;
       edoes = " bumps your " + hitloc + whwep;
       odoes = " bumps" + aimfor + whwep;
       break;
      case 10..19:
       verb = random(4) ? " hit" : " thump";
       overb = LANG_PSENT(verb);
       mdoes = verb + aimfor + " with your" + wep;
       edoes = overb + " your " + hitloc + whwep;
       odoes = overb + aimfor + whwep;
       break;
      case 20..29:
       verb = random(3) ? " slam" : " pound";
       overb = LANG_PSENT(verb);
       mdoes = verb + " your" + wep + " against" + aimfor;
       edoes = overb + hwep + " against your " + hitloc;
       odoes = overb + hwep + " against" + aimfor;
       break;
      case 30..49:
       verb = random(4) ? " slam" : " pound";
       overb = LANG_PSENT(verb);
       mdoes = verb + " your" + wep + " against" + aimfor + ", very hard";
       edoes = overb + hwep + " against your " + hitloc + ", very hard";
       odoes = overb + hwep + " against" + aimfor + ", very hard";
       break;
      case 50..69:
       mdoes = " smash your" + wep + " into" + aimfor;
       edoes = " smashes" + hwep + " intro your " + hitloc;
       odoes = " smashes" + hwep + " intro" + aimfor;
       break;
      case 70..89:
       mdoes = " smash your" + wep + " into" + aimfor + ", with a terrible noise";
       edoes = " smashes" + hwep + " intro your " + hitloc + ", with a terrible noise";
       odoes = " smashes" + hwep + " intro" + aimfor + ", with a terrible noise";
       break;
      default:
       mdoes = " crush" + aimfor + " with your" + wep;
       edoes = " crushes your " + hitloc + whwep;
       odoes = " crushes" + aimfor + whwep;
       break;
    }

    ME("You" + mdoes);
    YOU(me + edoes);
    THEM(me + odoes);
    return 1;

}


