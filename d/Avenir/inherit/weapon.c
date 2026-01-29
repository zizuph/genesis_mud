// file name:    ~Avenir/inherit/weapon
// creator(s):   Lord Cirion, August 17th, 1996
// last update:  
// purpose:      An inheritable weapon with some better combat
//               descriptions, based on the DT of the weapon.
//               These weapons have a few nifty features, like
//               making wounds bleed/bruise if you hit hard enough,
//               simulate misses being deflected by armours, and
//               severing limbs if you kill with a blade.
// note:         Yes, this weapon is considerably more cpu-consumptive
//               than the normal weapons, but considering the amount
//               of time players spend in combat, and how much cpu
//               combat takes up anyway, I think it is worth it to
//               put a little extra load to make fights look
//               a lot more interesting.  -Cirion.
// bug(s):       move_limb_to_corpse, line 256 returning "bad arg to '+'" 
//               runtime error.  I've removed the whole sever_limb() 
//               sequence in did_hit().   Lilith 10 Aug 2001            
// to-do:        
#pragma strict_types
#pragma save_binary

inherit "/std/weapon";           /* The normal weapon file   */
inherit "/lib/keep";
inherit "/d/Avenir/inherit/hitlocs"; /* Hitloc descs         */

#include <wa_types.h>   /* Weapon definitions, W_IMPALE, etc */
#include <macros.h>     /* QTNAME, etc                       */
#include <filter_funs.h>
#include <formulas.h>   /* F_LEGAL_DT                        */
#include <stdproperties.h>
#include <options.h>

/* The paths to the bruise and blood objects */
#define BRUISE      "/d/Avenir/inherit/bruise"
#define BLOOD       "/d/Avenir/inherit/blood"

/* A few definitions to make combat messages easier
 * Uses the variables defined in did_hit, so can't be used
 * in any other functions.
 */
#define ME(x)   if(interactive(wield)) wield->catch_msg(x + ".\n");
#define YOU(x)  if(interactive(enemy)) enemy->catch_msg(x + ".\n");
#define THEM(x) wield->tell_watcher(x + ".\n", enemy);

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

static string *acrobatic_miss_actions = ({
  "backflip",
  "groundroll",
  "sommersault",
  "twist"
}); /* Acrobatic miss verbs */

static string *acrobatic_miss_actions_other = ({
  "backflips",
  "groundrolls",
  "sommersaults",
  "twists"
}); 

static string *dodge_miss_actions = ({
  "dodge",
  "sidestep",
  "elude",
  "evade"
}); /* Dodge miss verbs */

static string *dodge_miss_actions_other = ({
  "dodges",
  "sidesteps",
  "eludes",
  "evades"
}); 

static string *parry_miss_actions = ({
  "parry",
  "deflect",
  "ward off",
  "counter",
  "fend off",
  "repel",
}); /* Parry miss verbs */

static string *parry_miss_actions_other = ({
  "parries",
  "deflects",
  "wards off",
  "counters",
  "fends off",
  "repels"
}); 


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
 * Function name: get_enemy_weapon_desc
 * Description:   returns the QSHORT of a random weapon
                  that was used to parry the attack.
 * Arguments:     enemy - the person to check for
 * Returns:       the QSHORT of the armour if any, otherwise 0
 */
private nomask mixed get_enemy_weapon_desc(object enemy)
{
    object *weapons = FILTER_SHOWN(enemy->query_weapon(-1));
    weapons = FILTER_CAN_SEE(weapons, query_wielded());

    if (!sizeof(weapons))
      return 0;

    object weapon = one_of_list(weapons);
    if (!weapon)
      return 0;
    return QSHORT(weapon);
  }


/*
 * Function name: make_weapon_blood
 * Description:   make a wound on the enemy bleed by cloning a
 *                blood subloc object and moving to the the enemy's
 *                inventory (just cosmetic ... does no real damage)
 * Arguments:     enemy  - the person the make bleed
 *                hitloc - the hitloc of the enemy
 * Returns:       0
 * Note:          
 */
private nomask void
make_weapon_blood(object enemy, string hitloc)
{
   object    blood;

   /* Only make live (not undead) humanoids bleed */
   if((!interactive(enemy) && !function_exists("create_monster", enemy))
      || enemy->query_prop(LIVE_I_UNDEAD))
     return;

   /* We already have some blood ... add on to that one */
   if(blood = present("avenir_blood", enemy))
   {
    blood->add_hurt(hitloc);
    return;
   }

   /* Else clone a new one into the enemy's inventory */
   setuid();
   seteuid(getuid());

   blood = clone_object(BLOOD);
    blood->move(enemy, 1);
    blood->add_hurt(hitloc);

   /* Make sure we are really there */
   if(!present(blood, enemy))
    blood->remove_object();
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
 * Function name: move_limb_to_corpse
 * Description:   called from a brief alarm, we move the severed
 *                limb to the room where the corpse is, provided
 *                the corpse is really there.
 * Arguments:     limb   - the limb we cloned before
 *                where  - the location of the corpse
 *                name   - the name of the corpse, used for an id
 * Returns:       0
 * Note:          
 */
nomask void
move_limb_to_corpse(object limb, object where, string name)
{
  object   corpse;

  /* Is everything real? */
  if(!objectp(limb) || !where->query_prop(ROOM_I_IS))
   return;

  corpse = present("corpse of " + lower_case(name), where);

  /* Is our corpse there? */
  if(!objectp(corpse))
  {
   limb->remove_object();
   return;
  }

  corpse->add_adj(limb->query_name() +"less");
  corpse->set_short(limb->query_name() +"less "
    + corpse->short());
  corpse->set_long("The corpse is "
    + "missing " + LANG_ADDART(limb->query_name()) + ", severed "
    + "off by a massive blow from a bladed weapon.\n" + corpse->long());

  limb->move(environment(corpse), 1);
}

private nomask void
sever_limb(object enemy, string hitloc)
{
   object   limb;
   string   noun,
            desc,
            rname;

   setuid();
   seteuid(getuid());

   if(enemy->query_prop(LIVE_I_NO_CORPSE))
     return;

   switch(hitloc)
   {
     case "head":
      noun = "head";
      desc = "It is a severed head from "
           + LANG_ADDART(enemy->query_race_name()) + ".\n";
      break;
     case "legs":
      noun = "leg";
      desc = "It is a severed leg from "
           + LANG_ADDART(enemy->query_race_name()) + ".\n";
      break;
     case "right arm":
     case "left arm":
      noun = "arm";
      desc = "It is a severed arm from "
           + LANG_ADDART(enemy->query_race_name()) + ".\n";
      break;
     /* Not a normal limb. Do nothing. */
     default:
      return;
      break;
    }

   /* Get some good adjectives from the race name */
   switch(enemy->query_race_name())
   {
     case "dwarf":
      rname = "dwarven";
      break;
     case "gnome":
      rname = "gnomish";
      break;
     case "elf":
      rname = "elvish";
      break;
     case "hobbit":
      rname = "halfling";
      break;
     case "orc":
      rname = "orcish";
      break;
     default:
      rname = enemy->query_race_name();
      break;
   }

    limb = clone_object("/d/Avenir/inherit/leftover");
    limb->set_name(noun);
    limb->add_name("limb");
    limb->set_heap_size(1);
    limb->set_short("severed " + rname + " " + noun);
    limb->set_adj(({ rname, enemy->query_race_name() }));
    limb->set_long(desc);
    limb->set_amount(200);
    limb->add_prop(OBJ_I_WEIGHT, 1500);
    limb->add_prop(OBJ_I_VOLUME, 1500);

   /* Unfortunate, but it is essential we use an alarm here,
    * otherwise there is no corpse present to behead, etc..
    */
   set_alarm(0.0, 0.0, &move_limb_to_corpse(limb,
             environment(enemy), enemy->query_name()));
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
              parry_wep, /* weapon that caused a parry         */
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
   hitloc = translate_hitloc(enemy, hdesc);

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
     
     switch (phurt)
     {
          case -3: // Acrobatic dodge
              int acro_idx = random(sizeof(acrobatic_miss_actions));
              mdoes = ", but";
              edoes = ", but you " + acrobatic_miss_actions[acro_idx];
              " away from your attack";
              break;
          case -2: // Parry
              int parry_idx = random(sizeof(parry_miss_actions));
              mdoes = odoes = ", but " + enemy->query_possessive()
                  + " " + parry_miss_actions_other[parry_idx];
              edoes = ", but you " + parry_miss_actions[parry_idx];
              mixed weapon_desc = get_enemy_weapon_desc(enemy);
              if (stringp(weapon_desc))
              {
                  mdoes += " with " + enemy->query_possessive() + " "
                      + weapon_desc;
                  edoes += " with your " + weapon_desc;
              }
              break;
          case -1: // Dodge
              int dodge_idx = random(sizeof(dodge_miss_actions));
              mdoes = odoes = ", but " + enemy->query_possessive()
                  + " " + dodge_miss_actions_other[dodge_idx] + " the attack";
              edoes = ", but you " + dodge_miss_actions[dodge_idx] + " the attack";
              break;
          default:
              if(stringp(deflect))
              {
                  mdoes = odoes = missstr + enemy->query_possessive() + " "
                      + deflect;
                  edoes = missstr + "your " + deflect;
              }
              else
              {
                  mdoes = ", but miss";
                  odoes = edoes = ", but misses";
              }
              break;
      }
     /* gag misses if the wielder has that option on */
     if (!wield->query_option(OPT_GAG_MISSES))
         ME("You " + dstr + aimfor + " with your"
           + wep + mdoes);

     /* Message for the watchers */
     dstr = get_damage_str_other(dt);

     /* Gag misses for watchers if they have that option on */
     wield->tell_watcher_miss(me + " " + dstr + aimfor
         + " with " + his + wep + odoes + ".\n", enemy);

     /* gag misses if the enemy has that option on */
     if (!enemy->query_option(OPT_GAG_MISSES))
         YOU(me + " " + dstr + " your " + hitloc + " with " + his + wep + edoes);

     return 1;
   }

   /* Moving right along, here we generate combat messages
    * based on the %hp of damage we did and the damage type
    * of the weapon.
    */

   /* Impaling weapons, daggers etc... */
   if(dt == W_IMPALE)
   {
    /* Make him bleed if we hit hard enough */
    if(phurt > 4 && random(100) < phit && enemy->query_hp())
      make_weapon_blood(enemy, hitloc); /* Make 'em bleed */

    /* stab, impale, poke, bury, graze, pierce, touch, nick, jab */
    switch (phurt)
    {
      case 0..4:
       mdoes = " barely touch" + aimfor + " with your" + wep;
       edoes = " barely touches your " + hitloc + whwep;
       odoes = " barely touches" + aimfor + whwep;
       break;
      case 5..9:
       verb = random(2) ? " jab" : " nick";
       overb = LANG_PSENT(verb);
       mdoes = verb + aimfor + " with your" + wep;
       edoes = overb + " your " + hitloc + whwep;
       odoes = overb + aimfor + whwep;
       break;
      case 10..15:
       mdoes = " pierce" + aimfor + " with your" + wep;
       edoes = " pierces your " + hitloc + whwep;
       odoes = " pierces" + aimfor + whwep;
       break;
      case 16..19:
       mdoes = " stab your" + wep + " into" + aimfor;
       edoes = " stabs" + hwep + " into your " + hitloc;
       odoes = " stabs" + hwep + " into" + aimfor;
       break;
      case 20..29:
       verb = random(2) ? " stab" : " drive";
       overb = LANG_PSENT(verb);
       mdoes = verb + " your" + wep + " into" + aimfor + ", opening a "
              +"large wound";
       edoes = overb + hwep + " into your " + hitloc + ", opening "
              +"a large wound";
       odoes = overb + hwep + " into" + aimfor + ", opening a large "
              +"wound";
       break;
      case 30..49:
       verb = random(4) ? " drive" : " stab";
       overb = LANG_PSENT(verb);
       mdoes = verb + " your" + wep + " into" + aimfor + ", opening a "
              +"very serious wound";
       edoes = overb + hwep + " into your " + hitloc + ", opening "
              +"a very serious wound";
       odoes = overb + hwep + " into" + aimfor + ", opening a very "
              +"serious wound";
       break;
      case 50..69:
       mdoes = " bury your" + wep + " into" + aimfor;
       edoes = " buries" + hwep + " into your " + hitloc;
       odoes = " buries" + hwep + " into" + aimfor;
       break;
      case 70..92:
       mdoes = " bury your" + wep + " into" + aimfor + " to the hilt";
       edoes = " buries" + hwep + " into your " + hitloc + " to the hilt";
       odoes = " buries" + hwep + " into" + aimfor + " to the hilt";
       break;
      default:
       verb = random(4) ? " impale" : " gouge";
       overb = LANG_PSENT(verb);
       mdoes = verb + " " + enem + " with your" + wep;
       edoes = overb + " you with" + whwep;
       odoes = overb + " " + enem + " with" + whwep;
       break;
    }

    ME("You" + mdoes);
    YOU(me + edoes);
    THEM(me + odoes);
    return 1;
   }

   /* Slashing weapons, swords, polearms etc... */
   else if(dt == W_SLASH)
   {
    /* Make him bleed if we hit hard enough */
    if(phurt > 4 && random(90) < phit && enemy->query_hp())
      make_weapon_blood(enemy, hitloc); /* Make 'em bleed */

    /* graze, slash, slice, bury, sever, cut, lacerate, scrape */
    switch (phurt)
    {
      case 0..4:
       verb = random(2) ? " graze" : " scrape";
       overb = verb + "s";
       mdoes = verb + " your" + wep + " along" + aimfor;
       edoes = overb + hwep + " along your " + hitloc;
       odoes = overb + hwep + " along" + aimfor;
       break;
      case 5..9:
       mdoes = " cut open a small wound in" + aimfor + " with your" + wep;
       edoes = " cuts open a small wound in your " + hitloc + whwep;
       odoes = " cuts open a small wound in" + aimfor + whwep;
       break;
      case 10..19:
       mdoes = " slice open" + aimfor + " with your" + wep;
       edoes = " slices your " + hitloc + whwep;
       odoes = " slices open" + aimfor + whwep;
       break;
      case 20..29:
       verb = random(3) ? " slash" : " lacerate";
       overb = LANG_PSENT(verb);
       mdoes = verb + aimfor + " with your" + wep;
       edoes = overb + " your " + hitloc + whwep;
       odoes = overb + aimfor + whwep;
       break;
      case 30..49:
       mdoes = " slash" + aimfor + " with your" + wep
              + ", opening a nasty wound";
       edoes = " slashes your " + hitloc + whwep
              + ", opening a nasty wound";
       odoes = " slashes" + aimfor + whwep
              + ", opening a nasty wound";
       break;
      case 50..69:
       verb = random(3) ? " cut deeply into" : " tear into";
       overb = ( verb == " tear into" ? 
               " tears into" : " cuts deeply into");
       mdoes = verb + aimfor + " with your" + wep;
       edoes = overb + " your " + hitloc + whwep;
       odoes = overb + aimfor + whwep;
       break;
      case 70..89:
       mdoes = " bury your" + wep + " into" + aimfor;
       edoes = " buries" + hwep + " into your " + hitloc;
       odoes = " buries" + hwep + " into" + aimfor;
       break;
      default:
       /* If we have killed him, let's sever off a limb ;) */
/* Taken out, problem with move_limb_to_corpse()
 * producing runtime error: bad arg to '+' on line 256
 * which doesn't make any sense to me.
 * Lilith 10 Aug 2001
 *
 *      if(!enemy->query_hp())
 *        sever_limb(enemy, hdesc);
 *
 *      else
 */
         nearly = random(2) ? " nearly" : " almost";
       verb = random(4) ? " sever" : " sunder";
       overb = LANG_PSENT(verb);
       mdoes = nearly + verb + aim + " with your" + wep;
       edoes = nearly + overb + " your " + hitloc + whwep;
       odoes = nearly + overb + aim + whwep;
       break;
    }

    ME("You" + mdoes);
    YOU(me + edoes);
    THEM(me + odoes);
    return 1;
   }

   /* Bludgeoning weapons, clubs etc... */
   else if(dt == W_BLUDGEON)
   {
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
       edoes = " smashes" + hwep + " into your " + hitloc;
       odoes = " smashes" + hwep + " into" + aimfor;
       break;
      case 70..89:
       mdoes = " smash your" + wep + " into" + aimfor + ", with a terrible noise";
       edoes = " smashes" + hwep + " into your " + hitloc + ", with a terrible noise";
       odoes = " smashes" + hwep + " into" + aimfor + ", with a terrible noise";
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

  /* Let normal combat messages take place. This shouldn't normally
   * happen, unless the dt was magic, in which case most magic
   * weapons would (should) handle the combat messages themselves.
   */
  return 0; 
}

