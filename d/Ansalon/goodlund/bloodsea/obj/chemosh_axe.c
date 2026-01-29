/*
 * Louie Aug 29 2005 - Reduced healing and capped align decrease.
 * Louie Nov 27 2005 - Healing drains all the souls, capped at 700.
 * 
 * Navarre September 13th 2006, Cleaned up the code a little.
 * Navarre January 20th 2008, Changed the dull/break chance. Its a two handed
 * weapon using speed, it dulled and broke way too eays for it to be of any use.
 * Two handed weapons in general are never used, with this change there should
 * be some usability with the weapon.
 *
 * Navarre April 25th 2009, Added timer so healing can only be done once
 *                          every 30 minutes.
 *                          Changed it from 3 to 10 souls in the axe for a heal.
 *                          A heal reverts the axe back to original state with
 *                          low stats.
 * Cotillion 2015-02-14:    LIVE_I_QUICKNESS 75 -> 40
 * Carnak 2016-09-08:       Added a check for IS_CORPSE_OBJECT to prevent abuse
 *
 */

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"

inherit "/lib/keep";
inherit "/std/weapon";

object wielder;
int wielded = 0;
int souls_collected = 0;
int set_axe_souls(int num);
int has_speed = 0; // Flag that checks to see if the wielder has speed.
string old_short = "blunted long-handled axe";

#define SPEED 40 
#define LAST_TIME_I_HEALED "_chemosh_axe_last_heal_time_"

void
create_weapon()
{
    set_name("axe");
    set_adj("blunted");
    add_adj("long-handled");
    set_short("@@short_descr@@");
    set_long("@@long_descr@@");
    set_default_weapon(15, 15, W_AXE, W_SLASH, W_BOTH);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 50, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"While deceptively innane, this axe is a powerful "+
	"weapon from the Pits of the Abyss. Embued with the unholy blessings of " +
	"Chemosh, Lord of Death, it has the power to draw the souls from the newly "+
	"departed when commanded to, empowering itself in the process and making " +
        "the wielder deceptively quick with the big weapon. With enough "+
	"slain souls captured within it, the wielder may 'feed' upon the souls, " +
	"healing themselves. But be warned, the more one uses these dark blessings, " +
	"the more one falls under the taint of Chemosh... you have been warned!" +
	"\n",15}));

    add_item(({"symbol","sickly yellow symbol","skull"}),
        "The symbol looks like that which once adorned the weapons and armour of " +
        "warrior-priests of the ancient and dark god of death, Chemosh. Rumour " +
        "has it that during the evil times following the Cataclysm, these warriors " +
        "would terrorise the land with steel and black magic, drawing the souls " +
        "from their fallen foes, and even feeding upon these captured spirits to " +
        "heal their wounds.\n");  

    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 14000);
    add_prop(OBJ_I_VALUE, 1650);
 
    set_wf(TO);
    seteuid(getuid(TO));
}

int
query_axe_souls()
{
    return souls_collected;
}

int
set_axe_souls(int num)
{
    if((num > 30) || (num < 0))
    {
        return 0;
    }

    if (!objectp(wielder))
    {
        return 0;
    }

    souls_collected = num;

    if(old_short != TO->short())
    {
        switch(num)
        {
          case 4..10:
              set_hit(35);
              set_pen(45);
              write("The " +old_short+ " morphs into a gleaming long-handled axe!\n");
              say("The " +old_short+ " wielded by "+QTNAME(wielder)+ 
                  " morphs into a gleaming long-handled axe!\n");
              set_likely_dull(1);
              set_likely_corr(1);
              set_likely_break(1);
              break;

          case 11..20:
              set_hit(45);
              set_pen(55);
              write("The " +old_short+ " morphs into a flaming long-handled axe!\n");
              say("The " +old_short+ " wielded by "+QTNAME(wielder)+ 
          	  " morphs into a flaming long-handled axe!\n");
              set_likely_dull(1);
              set_likely_corr(1);
              set_likely_break(1);
              break;

          case 21..30:
              set_hit(50);
              set_pen(60);
              write("The " +old_short+ " morphs into a Reaper of Souls!\n");
              say("The " +old_short+ " wielded by "+QTNAME(wielder)+ 
                  " morphs into a Reaper of Souls!\n");
              set_likely_dull(1);
              set_likely_corr(1);
              set_likely_break(1);
        }
    }         
    wielder->update_weapon(TO);
    return 1;    
}


string
short_descr()
{
    switch(souls_collected)
    {
      case 4..10:
	return "gleaming long-handed axe";         
      case 11..20:
	return "flaming long-handled axe";    
      case 21..30:
	return "long-handled reaper of souls";
    }
    return "blunted long-handled axe";
}

string
long_descr()
{
    switch(souls_collected)
    {
      case 4..10:
	return "This is a long-handled axe, its single blade " +
	"gleaming with a dull grey aura. A sickly yellow symbol " +
	"of a skull has been branded onto the handle's base.\n";
      case 11..20:
	return "This is a long-handled axe, its single blade burning with " +
	"the unholy fires of the Abyss! Its sturdy six foot long handle is " +
	"covered with intricate carvings of tortured souls, which seem " +
	"to writhe in the malevolent glow of the axe blade. A sickly yellow symbol " +
	"of a skull has been branded onto the handle's base.\n";

      case 21..30:
	return "This axe was obviously forged and imbued with malevolent " +
	"powers by some dark and powerful being.  Its six foot long handle " +
	"is covered with intricately carved skulls that seem to lear at you from " +
	"every angle. A skull of what looks like a screaming " +
	"elven child has been fastened to the base of the handle. However " +
	"neither the carvings or the child's skull are as disturbing as " +
	"the single blade of this axe, an unholy shard of blackness " +
	"that pulses with the tortured souls of those slain by this " +
	"mighty weapon.\n";

    }
    return "This is a blunted long-handled axe. The blackened axe head " +
    "looks like it has been ruined by fire, although the handle " +
    "seems to be in good condition still. A sickly yellow symbol " +
    "of a skull has been branded onto the handle's base.\n";
}

void
wield_message()
{
    if(E(TO) != wielder)
	return;
    wielder->catch_msg("A slight chill runs through you as you " +
       "wrap your hands around this axe, as if someone had just " +
       "walked over your grave...\n");
}

mixed
wield(object what)
{
    /*
	wield_message();
    */
    wielder = TP;
    wielded = 1;

    if (has_speed == 0)
     {
         wielder->change_prop(LIVE_I_QUICKNESS, wielder->
                  query_prop(LIVE_I_QUICKNESS) + SPEED);
         has_speed = 1;
     }

    set_alarm(1.0, 0.0, wield_message);

    return 0;
}

mixed
unwield(object what)
{
    if(souls_collected > 3)
    {
	write("The "+TO->short()+ " reverts to a blunted long-handled axe again.\n");
	say("The "+TO->short()+ " wielded by "+ QTNAME(wielder)+ " reverts to a blunted "+
	  "long-handled axe again.\n");
    }

    set_axe_souls(0);
    set_hit(15);
    set_pen(15);
    wielder->update_weapon(TO);

    if ((has_speed == 1))
    {
        wielder->change_prop(LIVE_I_QUICKNESS, wielder->
                  query_prop(LIVE_I_QUICKNESS) - SPEED);
    }

    has_speed = 0;
    wielder = 0;
    wielded = 0;

    return 0;
}

int
feed_soul(string str)
{

    if(!str)
    {
	notify_fail("Feed on what? Souls?\n");
	return 0;
    }

    if(str != "on souls")
    {
	notify_fail("Feed on what? Souls?\n");
	return 0;
    }

    if (!wielded)
    {
	notify_fail("You need to be wielding the weapon to be " +
	            "able to feed upon the souls captured by your axe!\n");
	return 0;
    }

    if(wielder->query_alignment() > -200)
    {
	notify_fail("You feel squeamish attempting to feed upon the " +
	            "souls within the axe. You just aren't dark hearted " +
                    "enough for such evil practises!\n");
	return 0;
    }

    if(TO->query_axe_souls() < 30)
    {
	notify_fail("There are not enough souls captured within the " +
	            "axe to feed upon!\n");
	return 0;
    } 
    
    if(time() - TP->query_prop(LAST_TIME_I_HEALED) < 1800)
    {
      notify_fail("You need to recover from your last soul feeding " +
                  "before you are ready to do it again.\n");
      return 0;
    }

    write("You grip your " +TO->short()+ " closely, "+
          "feeling the captured souls of your fallen foes " +
          "rejuvenate you!\nYou feel healthier, however tainted " +
          "by your deed.\n");
    say(QCTNAME(TP) + " grips " +HIS(TP)+ " " +TO->short()+
        " closely with a malevolently grin, and suddenly " +
        "looks healthier!\n");
 
    TP->heal_hp(MIN(70*(query_axe_souls()), 700));
    TP->add_prop(LAST_TIME_I_HEALED, time());
    old_short = TO->short();
    TO->set_axe_souls(0);

    return 1;
}

int
draw_soul(string str)
{
    object ob = P("corpse",E(TP));
    string corpse_desc;

    if(!str)
    {
	notify_fail("Draw soul from which corpse?\n");
	return 0;
    }

    if (!wielded)
    {
	notify_fail("You need to be wielding the weapon to be " +
	            "able to draw souls!\n");
	return 0;
    }

    if(wielder->query_alignment() > -200)
    {
	notify_fail("You feel squeamish attempting to draw the " +
	            "soul from the corpse. You just aren't dark hearted " +
                    "enough for such evil practises!\n");
	return 0;
    }

    if(ob && E(ob) && E(ob) == E(TP))
    {

        corpse_desc = ob->short_func();

        if (!IS_CORPSE_OBJECT(ob))
        {
            notify_fail("The soul has already left the corpse.\n");
            return 0;
        }
    
	write("You raise your " +TO->short()+ " above "+
              "the " +corpse_desc+ ", calling upon the Lord of the "+
              "Dead to grant you its soul!\n");
	say(QCTNAME(TP) + " raises " +HIS(TP)+ " " +TO->short()+
	    " above the " +corpse_desc+ ", calling upon the Lord " +
	    "of the Dead to grant " +HIM(TP)+ " its soul!\n");

	old_short = TO->short();
	TO->set_axe_souls(TO->query_axe_souls() + 1);

	/*
	ob->set_decay(0);
	ob->decay_fun();
	*/
	ob->decay_remove();

	return 1;
    }
    notify_fail("Draw soul from what corpse?\n");
    return 0;
}

void
init()
{
    ::init();

    add_action(draw_soul,"draw");
    add_action(feed_soul,"feed");
}
