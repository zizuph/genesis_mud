/*      Created by:     Lord Charok, 15'th of July 2001 for Clay Valley.
 *                      This sword is magically enchanted to be more solid
 *                      and endure hits longer, thus the likely_dull and
 *                      likely_break will be modified.
 *
 *                      Copyright(c) Charok @ Clay Valley, T Windahl.
 *
 *                      Copy given to Stralle to use on Genesis, no major 
 *                      changes allowed. (Balance is naturally ok!)
 *      Purpose:        
 *      Modified by:    Lord Charok, 19'th of August.
 *				Added the emote 'lower'
 *                      Mercade, 2002-Oct-30. Added phurt == -2 dodging.
 *                      Cotillion, 2004-Oct-13. Fixed ::did_hit
 *                      Arman, 2021-Dec-25. Added as a magic enhancer
 *                             as part of the updated magic system.
 *
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <options.h>
#include <composite.h>
#include <cmdparse.h>

inherit "/std/weapon";
inherit "/lib/keep"; // making it keepable and will default it to keepable
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

int gHit = 38 + random(4);
int gPen = 33 + random(3);

int gTmpHit, gTmpPen;

void
create_weapon()
{
   set_name("flail");
   set_pname("flails");

   set_short("three-headed iron flail");
   set_pshort("three-headed iron flails");
   set_long("This is a nicely crafted three-headed iron flail. The handle, which is a bit " +
   	"longer than two feet, is very smooth and the grip is lined with soft leather to give " +
   	"the wielder a strong, firm grip. From the top of the handle three two-foot long, " +
   	"chains extend. In the end of each chain a small spiked steel ball is fastened. The " +
   	"spikes are about an inch long and very sharp, and the balls have a diameter of " +
   	"approximately two inches.\n");

   add_cmd_item( ({"flail","iron flail", "three-headed iron flail","three-headed flail"}),({"touch","feel"}),
        "The iron flail is cold to the touch.\n");

   add_item("handle", "Studying the handle more closely you notice some fine inscriptions on it.\n");
   add_item( ({"inscription","fine inscription","inscriptions","fine inscriptions"}), 
   	"You study the inscriptions on the handle closly and they read: \n" +
   	"When wielding this flail you can do the following: \n" +
   	"  - 'swing flail' \n" +
   	"  - 'lower flail <target>' \n" +
   	"    <target> is optional \n");

   set_keep(1);
    
   set_likely_dull(3);
   set_likely_break(3);
    
   set_hit(gHit);
   set_pen(gPen);
   set_magic_spellpower(10); // 45 to cleric style guilds when wielded.

   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_ANYH);
   set_wf(this_object());

   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(gHit,gPen)+100);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(gPen,W_CLUB)+10);   
   add_prop(OBJ_I_WEIGHT, query_prop(OBJ_I_WEIGHT)/4);
   
   add_prop(MAGIC_AM_MAGIC,({55, "enchantment"}));
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(MAGIC_AM_ID_INFO,({
     "The " + short() + " appears to be magical in some way. ",1,
     "The " + short() + " provides enhanced spell power to those of strong faith. ",25,
     "The " + short() + " emit strong protection magic. ", 45,
     "It appears the magic imbued in this weapon is made to make it last longer. ", 60,
     "You notice that the magic is extra strong in the spikes. ", 70,
     "The spikes on the " +short() + " will create extra damage on bare skin. ", 85,
     "It seems that this fine weapon would not break very easily due to the strong " +
    	"magic protecting it. ", 90}));
   add_prop(OBJ_S_WIZINFO,"The " + short() + " is magically enchanted to " +
  	"endure hard use for a longer period of time than regular clubs. Also " +
  	"it will not break very easily. It also provides 45 spellpower to " +
        "those in an occupational or layman cleric style guild.\n");

}


void
decide_spellpen()
{
    int spellpen;
    object who = query_wielded();

    if (!objectp(who))
	return;

    if(who->query_guild_style_lay() == "cleric" ||
        who->query_guild_style_occ() == "cleric")
    {
        who->catch_tell("The " + short() + " seems to respond to " +
            "your strong faith, enhancing your spell abilities.\n");

        spellpen = 45;
    }
    else
    {
        spellpen = 10;
    }

    set_magic_spellpower(spellpen);
    who->update_weapon(this_object());
}

mixed
wield(object what)
{
    set_alarm(1.0, 0.0, &decide_spellpen());
    return 0;
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

int
lower_flail(string str) 
{
   object target, *a, me;
   string who;
   
    if(!str)
    {
	notify_fail("Lower what? The flail?\n");
	return 0;
    }

    if(!query_wielded())
    {
	notify_fail("You must wield the " + query_short()+ " first!\n");
	return 0;
    }
   
   me = query_wielded();
   sscanf(str, "flail %s", who);

   if(str == "flail")
   {
     write("You lower your " +short()+ " and let the spiked balls touch the ground in a " +
	"gesture of peace, yet you remain alert should the situation turn hostile.\n");
     say(QCTNAME(me) + " lowers " +me->query_possessive()+ " "+
        short() + ", letting the spiked balls touch the ground in a gesture of peace. " +
        "A watchful glint remains in " +me->query_possessive()+ " eyes.\n");
              
      return 1;
   }
        
   a = PARSE_THIS(str, "[flail] [the flail] %l");
   
   if (!CAN_SEE_IN_ROOM(this_player()))
   {
     notify_fail("You can not see in this darkness.\n");
     return 0;
   }

   if (sizeof(a) > 1)
   {
        notify_fail("Please be more specific! Not more than one target at a time.\n");
	return 0;
   }
   else if (!sizeof(a))
   {
	notify_fail("You find no such living creature.\n");
	return 0;
   }
   
   target = a[0];

   if (!objectp(target))
   {
     write("You lower your " +short()+ " and let the spiked balls touch the ground in a " +
	"gesture of peace, yet you remain alert should the situation turn hostile.\n");
     say(QCTNAME(me) + " lowers " +me->query_possessive()+ " "+
        short() + ", letting the spiked balls touch the ground in a gesture of peace. " +
        "A watchful glint remains in " +me->query_possessive()+ " eyes.\n");
     
     return 1;
   }
   
   if (!living(target))
   {
     write("You lower your " +short()+ " and let the spiked balls touch the ground in a " +
	"gesture of peace, yet you remain alert should the situation turn hostile.\n");
     say(QCTNAME(me) + " lowers " +me->query_possessive()+ " "+
        short() + ", letting the spiked balls touch the ground in a gesture of peace. " +
        "A watchful glint remains in " +me->query_possessive()+ " eyes.\n");
        
	return 1;
   }
   if (target == me)
   {
	notify_fail("There is no meaning in that, you should know yourself pretty well.\n");
	return 0;
   }
   
   if ((target->query_real_name() == who) && (!me->query_met(who)))
   {
     notify_fail("Whip who? You do not know anyone with that name!\n");
     return 0;
   }
   
   if(target)
   { 
     me->catch_msg("You look at " +QTNAME(target)+ " and lower your " +short()+ 
     	" and let the spiked balls touch the ground in a " +
	"gesture of peace, yet you remain alert should the situation turn hostile.\n");
     target->catch_msg(QCTNAME(me) + " looks at you and lowers " +
     	me->query_possessive()+ " " +short()+ ", letting the spiked balls " +
     	"touch the ground in a gesture of peace. A watchful glint remains in " +
     	this_player()->query_possessive()+ " eyes.\n");
     say(QCTNAME(me) + " looks at " +QTNAME(target)+ " and lowers " + 
     	me->query_possessive()+ " " +short()+ ", letting the spiked balls touch " +
     	"the ground in a gesture of peace. A watchful glint remains in " +
     	me->query_possessive()+ " eyes.\n", ({me, target}) );
      
     return 1;	
   }

   notify_fail("Something seems to be wrong with this command, please make a bug report.\n " +
   	"     Hint: 'bug flail'\n");
   return 0;
}


int
swing_flail(string str) 
{
    int skill;

    notify_fail("Swing what? The flail?\n");
    if(!str)
	return 0;

    if(!query_wielded())
    {
	notify_fail("You must wield the " + query_short()+ " first!\n");
	return 0;
    }

   skill = this_player()->query_skill(SS_WEP_CLUB);

   if(str == "flail")
   {
      switch(skill)
      {
      	case 70 .. 200:
      	 write("You swing your " +short()+ " in a perfect arc " +
      	 	"through the air.\n");
         say(QCTNAME(this_player()) + " swings " +this_player()->query_possessive()+ " "+
	   short() + " in a perfect arc through the air.\n");
	 break;
      	
      	case 60 .. 69:
      	  write("You swing your " +short()+ " in a nice arc " +
      	 	"through the air.\n");
         say(QCTNAME(this_player()) + " swings " +this_player()->query_possessive()+ " "+
	   short() + " in a nice arc through the air.\n");
	 break;
	 
	case 50 .. 59:
	 write("You swing your " +short()+ " in an arc " +
      	 	"through the air.\n");
         say(QCTNAME(this_player()) + " swings " +this_player()->query_possessive()+ " "+
	   short() + " in an arc through the air.\n");
	 break;
	
	case 40 .. 49:
	 write("You swing your " +short()+ " through the air.\n");
         say(QCTNAME(this_player()) + " swings " +this_player()->query_possessive()+ " "+
	   short() + " through the air.\n");
	 break;
      	
      	case 30 .. 39:
         write("You swing your " +short()+ " clumbily in the air.\n");
         say(QCTNAME(this_player()) + " swings " +this_player()->query_possessive()+ " "+
	   short() + " clumbily in the air.\n");
	 break;
	
	default:
	 write("You try to swing your " +short()+ " clumbily in the air. " +
	 	"The result is devastating, you hit yourself with it and it hurts!\n");
         say(QCTNAME(this_player()) + " tries to swing " +this_player()->query_possessive()+ " "+
	   short() + " clumbily in the air. The result is devastating. " +
	   QCTNAME(this_player()) + " hits " +this_player()->query_objective()+
	   "self in the attempt and it must hurt with those spikes digging into the flesh.\n");
	   
	 this_player()->heal_hp( -(40-skill) );
	 this_player()->add_panic(random(4)+1);
	 
	 if(this_player()->query_hp() <= 0)
	 {
	    this_player()->command("wince");
	    this_player()->do_die();
	 }
	 break;
      }
              
      return 1;
   }

   return 0;
}

/*
 * Function name : query_hitloc_id
 * Description   : Will extract hitloc_id from object enemy, based on
 *                 the hdesc of the hitloc. We need this function since
 *                 this info is not available directly from within hit_me()
 *		   It gives us the hitloc_id regardless of humanoid.
 * Returns	 : hitloc_id 	if found
 *		          -1	if no hitloc_id is found
 */
int
query_hitloc_id(string hdesc, object enemy)
{
  int i, *hitloc_id;
  int a;
  object co;
  mixed hitloc;

  co = enemy->query_combat_object();
  hitloc_id = co->query_hitloc_id();

  a = sizeof(hitloc_id);
  
  for (i = 0; i < a; i++)
  {
    hitloc = co->query_hitloc(hitloc_id[i]);
    
    if (hitloc[2] == hdesc)
      return hitloc_id[i];
  }
  return -1;
}

/*
 * Function name: did_hit
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. This is supposed to be
 *                replaced by a more intelligent routine in creature and
 *                humanoid combat. (called from heart_beat)
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
 *                       If this is negative, it indicates fail
 *                dam:   Damage we did in hit points
 *
 * I mask this funtion to give my own descriptions to hits.
 * 
 * The flail will increase damage if there is no armour
 * where it hit, as the spikes will tear into the flesh.
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
           int phit, int dam)
{
    string how;
    string what;
    string owhat;
    string with;
    string where;
    object armour, me = query_wielded();
    int x, i_am_real = !(me->query_npc());
    int hitloc_id;
    string wound_desc = ({"nasty wounds", "bleeding wounds", "bloody scratches", 
             "open wounds", "gaping wounds", "torn flesh", "shredded skin",
             "deep cuts", "vicious wounds", "chunks of gore on the spikes and blood " +
             "gushing from the wounds", "chunks of flesh on the spikes"})[random(10)];

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    
    hitloc_id = query_hitloc_id(hdesc, enemy);
    armour = enemy->query_armour(hitloc_id);

    if(!armour)
    {
      phurt = phurt * 125 / 100;
    }

    if ((!objectp(enemy)) || (!objectp(me)))
    {
        return 0;
    }

    with = query_short();

    if (phurt == -2)
    {
        enemy->add_panic(1);

        if (i_am_real && !me->query_option(OPT_GAG_MISSES))
        {
            me->catch_msg("You aim for the " + hdesc + " of " +
                enemy->query_the_name(me) + " with your " + with +
                " but " + enemy->query_pronoun() + " dodges succesfully.\n");
        }
        if (interactive(enemy) && !enemy->query_option(OPT_GAG_MISSES))
        {
            enemy->catch_msg(me->query_The_name(enemy) + " aims for your " +
                hdesc + " with " + me->query_possessive() + " " + with +
                ", but you successfully dodge.\n");
        }
        me->tell_watcher(QCTNAME(me) + " aims for the " + hdesc + " of " +
            QTNAME(enemy) + " with " + me->query_possessive() + " " +
            with + ", but the target successfully dodges.\n", enemy, 0, 1);
        return 1;
    }

    if (phurt == -1)
    {
        enemy->add_panic(1);

        if (i_am_real && !me->query_option(OPT_GAG_MISSES))
        {
            me->catch_msg("You aim for the " + hdesc + " of " +
                enemy->query_the_name(me) + " with your " + with +
                " but miss.\n");
        }
        if (interactive(enemy) && !enemy->query_option(OPT_GAG_MISSES))
        {
            enemy->catch_msg(me->query_The_name(enemy) + " aims for your " +
                hdesc + " with " + me->query_possessive() + " " + with +
                ", but misses.\n");
        }
        me->tell_watcher(QCTNAME(me) + " aims for the " + hdesc + " of " +
            QTNAME(enemy) + " with " + me->query_possessive() + " " +
            with + ", but misses.\n", enemy, 0, 1);
        return 1;
    }

    enemy->add_panic(-3 - (phurt / 5));
    where = " the " + hdesc + " of ";

    switch (phurt)
    {
    case 0..4:
        how = ". ";
        what = "tickle";
        owhat = "tickles";
        break;
    case 5..9:
        how = ". ";
        what = "graze";
        owhat = "grazes";
        break;
    case 10..19:
        how = ". ";
        what = "hurt";
        owhat = "hurts";
        break;
    case 20..29:
        how = ", rather badly. ";
        what = "hurt";
        owhat = "hurts";
        break;
    case 30..49:
        how = ", very bad. ";
        what = "hurt";
        owhat = "hurts";
        break;
    case 50..69:
        how = ", very hard. ";
        what = "smash";
        owhat = "smashes";
        break;
    case 70..89:
        how = ", with a bone crushing sound. ";
        what = "smash";
        owhat = "smashes";
        where = " ";
        break;
    default:
        how = ". ";
        what = "massacre";
        owhat = "massacres";
        where = " ";
    }

    if(hdesc == "arms")
      if(random(1))
        hdesc = "left arm";
      else
        hdesc = "right arm";
      
    if(hdesc == "legs")
      if(random(1))
      	hdesc = "left leg";
      else
        hdesc = "right leg";

    if (i_am_real && !armour)
    {
        me->catch_msg("You " + what + where + enemy->query_the_name(me) +
            " with your " + with + how + "The steel spikes on your " + with +
            " tears into the naked flesh of your enemy's " + hdesc + ", leaving " +
             wound_desc + ".\n" );
    }
    else if (i_am_real)
    {
        me->catch_msg("You " + what + where + enemy->query_the_name(me) +
            " with your " + with + how + "\n");
    }
    
    if (interactive(enemy) && !armour)
    {
        enemy->catch_msg(QCTNAME(me) + " " + owhat + " your " + hdesc +
            " with " + me->query_possessive() + " " + with + how + "The " +
            "steel spikes on " + me->query_possessive() + with + 
            " tears into your naked flesh, leaving " + wound_desc + ".\n" );
    }
    else if (interactive(enemy))
    {
        enemy->catch_msg(QCTNAME(me) + " " + owhat + " your " + hdesc +
            " with " + me->query_possessive() + " " + with + how + "\n");
    }    
    
    if (!armour)
    {
      me->tell_watcher(QCTNAME(me) + " " + owhat + where + QTNAME(enemy) +
        " with " + me->query_possessive() + " " + with + how + "The spikes " +
        "on " + me->query_possessive() + " " + with + " tears into the naked " +
        "flesh on " + QTNAME(enemy) + "'s " + hdesc + ", leaving " +
        wound_desc + ".\n", enemy);
    }
    else
    {
      me->tell_watcher(QCTNAME(me) + " " + owhat + where + QTNAME(enemy) +
        " with " + me->query_possessive() + " " + with + how + "\n", enemy);
    }

    return 1;
}

/*
 * Function name: query_recover
 * Description  : Called to check whether this weapon is recoverable.
 *                If you have variables you want to recover yourself,
 *                you have to redefine this function, keeping at least
 *                the filename and the weapon recovery variables, like
 *                they are queried below.
 *                If, for some reason, you do not want your weapon to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "#gHit#" + gHit + "#gPen#" + gPen + " ";
}

/*
 * Function name: init_recover
 * Description  : When the object recovers, this function is called
 *                to set the necessary variables. If you redefine the
 *                function, you must add a call to init_wep_recover
 *                with the string that you got after querying
 *                query_wep_recover.
 * Arguments    : string argument - the arguments to parse
 */
public void
init_recover(string arg)
{
    int tmp;
    string misc;
    
    init_wep_recover(arg);
    
    tmp = sscanf(arg, "%s#gHit#%d#gPen#%d %s", misc, gTmpHit, gTmpPen, misc);

    set_hit(gTmpHit);
    set_pen(gTmpPen);
}

void
init()
{
   /*******************************************
    *  PLEASE ADD EMOTES IN ALPHABETIC ORDER  *
    *******************************************/
    
   ::init();
   add_action(lower_flail,"lower");
   add_action(swing_flail,"swing");
}

