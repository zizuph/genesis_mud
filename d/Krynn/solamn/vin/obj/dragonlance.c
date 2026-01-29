/*
* The Dragonlance, by Morrigan
*/

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/weapon";


/* Gl(wielder)al Variables */
int gRecognized = 0;


/*
* Function name: create_weapon
* Description  : Create the weapon. You must define this function to
*                construct the weapon.
*/
create_weapon()
{
    set_name("dragonlance");
    add_name(({"lance", "dragonlance"}));
    add_adj(({"dragon", "silver", "dragonsilver", "footman's"}));
    set_short("@@short_desc");
    set_long("@@long_desc");
    set_default_weapon(45, 55, W_POLEARM, W_BLUDGEON | W_IMPALE, W_BOTH);
    add_item(({"silver", "metal", "dragonsilver"}), "The lance is crafted "+
      "of a metal which gleams with a brighter, purer, silver than you "+
      "have ever seen.  It feels warm to the touch, and emits a bright "+
      "silver glow.\n");
    add_item(({"hilt", "dragon hilt", "visage"}), "The hilt of the lance is "+
      "sculpted to resemble the fearsome visage of an attacking dragon.  So "+
      "realistic is it, so detailed, that the shaft of the lance appears to "+
      "be a river of silver fire spewing from its mouth.\n");
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 11500);
    add_prop(OBJ_I_VALUE, 17280000);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({100, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"The "+short()+" is quite (wielder)viously "+
	"magical.\n", 1, "You feel an extremely strong enchantmentment "+
	"emanating from the lance, and realize that it is the legendary "+
	"Dragonlance, blessed by Paladine!\n", 35, "You feel that the "+
	"the lance is not only enchanted to be a weapon of unequalled "+
	"quality, but also that it would endow it's wielder with resistant "+
	"to various evil magics, and the breath of dragons.\n", 50, "Those " +
        "of true faith shall wield the dragonlance with the blessing of " +
        "Paladine, the Platinum Draco.\n", 70}));
    add_prop(OBJ_S_WIZINFO, "This is the Dragonlance, the weapon on "+
      "which the Dragonlance saga was based.  It is very holy, only "+
      "those of holy alignment may wield it.  Only those of greater "+
      "than neutral may even touch it, evil players who try to touch "+
      "it are burned.  It inflicts double damage on draconians and "+
      "dragons.  If the player attacks a good aligned dragon, the "+
      "Dragonlance explodes and breaks, causing the wielder harm. "+
      "It adds resistance to fire/cold/electricity/acid props to the "+
      "wielder, and glows all the time.  One must also have fairly "+
      "good wisdom to wield it.  It will not do damage to any creature "+
      "who is above 0 alignment.  Also, this is the footman's dragonlance, "+
      "lesser in strength then the true dragonlance.\n");
    set_wf(TO);
    seteuid(getuid(TO));
}


/*
* Function name: init
* Description  : Initialize some weapon related actions. If you want to
*                mask this function to add some actions for yourself, you
*                _must_ make a call to ::init();
*/
init()
{
    add_action("do_rejoice", "rejoice");
    add_action("do_balance", "test");
    add_action("do_metal", "touch");
    ::init();
}


/*
* Function name: do_metal
* Description  : Emote.
*/
int
do_metal(string s)
{
    if (!s)
    {
	NF("Touch what?\n");
	return 0;
    }

    if (s != "metal" && s != "silver" && s != "dragonsilver")
    {
	NF("Touch what?\n");
	return 0;
    }

    TP->catch_msg("You reach out and touch the gleaming silver metal of "+
      "the lance.  Strangely, the metal is warm to the touch.\n");
    return 1;
}


/*
* Function name: do_balance
* Description  : Emote.
*/
int
do_balance(string s)
{
    if (gRecognized != 1)
    {
	NF("What ?\n");
	return 0;
    }

    if (s != "dragonlance" && s != "lance")
    {
	NF("What ?\n");
	return 0;
    }

    wielder->catch_msg("You regard the Dragonlance thoughtfully, testing its "+
      "balance.  It seems to be amazingly light, and perfectly balanced.\n");
    tell_room(E(wielder), QCTNAME(wielder)+" regards the dragonlance "+
      "thoughtfully, testing its balance.\n", wielder);
    return 1;
}


/*
* Function name: do_rejoice
* Description  : Emote.
*/
int
do_rejoice(string s)
{

    if (gRecognized != 1)
    {
	NF("What ?\n");
	return 0;
    }

    if (s)
    {
	NF("Rejoice how?\n");
	return 0;
    }

    wielder->catch_msg("You hold the Dragonlance high and cry out in joy!\n");
    tell_room(E(wielder), QCTNAME(wielder)+" holds the Dragonlance high and "+
      "cries out in joy!\n", wielder);
    return 1;
}


/*
* Function name: long_desc
* Description  : Long description of the lance.
*/
string
long_desc()
{
    string str = "";

    if (gRecognized == 1)
	str = "You look upon the famed Dragonlance!\n";

    return str + "Long, sleek, narrow, the lance stands about one and a half "+
    "times as long as a man.  The tip seems to taper off to a point so "+
    "sharp that nothing would bar its path.  Behind the head, nearly a "+
    "foot from the tip, sharp barbs arise on each side, assuring that "+
    "any strike would be costly to the foe.  The back end of the lance "+
    "ends with a hilt carved to resemble the fearsome visage of an "+
    "attacking dragon, with the shaft emerging like a river of flame "+
    "from the leviathan's maw.  The metal, purest of any that you "+
    "have ever seen, casts a healthy, powerful glow of silver all "+
    "around you.\n";
}

varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{

    if (protectee == query_wielded())
      {
      if (prop == MAGIC_I_RES_FIRE)
        return ({ 35, 1}); /* additive */
      if (prop == MAGIC_I_RES_COLD)
        return ({ 35, 1}); /* additive */
      if (prop == MAGIC_I_RES_ACID)
        return ({ 35, 1}); /* additive */
      if (prop == MAGIC_I_RES_ELECTRICITY)
        return ({ 35, 1}); /* additive */
      if (prop == MAGIC_I_RES_POISON)
        return ({ 35, 1}); /* additive */
      }
    else
      return ::query_magic_protection(prop, protectee);
}



/*
* Function name: no_take
* Description  : Fail function for those unworthy who try to touch
*                the dragonlance.
* Arguments    : (wielder)ject new = new environment
*/
void
no_take(object new)
{
    new->catch_msg("You try to take the sleek silver lance, but it "+
      "burns your hand!\nYou drop the "+short()+".\n");
    tell_room(E(new), QCTNAME(new)+" tries to take the sleek silver "+
      "lance, but it burns "+POSSESSIVE(new)+" hand!\n"+QCTNAME(new)+
      " drops the "+short()+".\n", new);
    move(E(new));
}


/*
* Function name: enter_env
* Description  : Remasked to not allow evils to touch the dragonlance.
*/
void
enter_env(object new, object old)
{
    if (new->query_alignment() <= 0)
	set_alarm(0.1, 0.0, "no_take", new);
}


/*
* Function name: short_desc
* Description  : Short description of lance.
*/
string
short_desc()
{
    if (gRecognized == 1)
	return "footman's dragonlance";
    else
	return "sleek silver lance";
}


/*
* Function name: wield_message(1-7)
* Description  : The wield messages.
*/
int wield_message_poor1()
{
    wielder->catch_msg("\nAs you grip the sleek silver lance, your vision "+
      "blurs in a strange fashion... But you quickly regain your "+
      "composure.\n\n\nThis must be the famouse dragonlance...\n\n"+
      "You do not feel the mystic presence of a God about the weapon, " +
      "but it appears to be a powerful artifact in its own right.\n");
    tell_room(E((wielder)), QCTNAME((wielder))+"'s eyes glaze over, as "+
      PRONOUN((wielder))+" grips the silver sleek lance in both hands, "+
      "but "+PRONOUN((wielder))+" quickly manages to shake off whatever tugged "+
      "at " + HIS((wielder)) + " consciousness.\n", (wielder));

    wielder->add_magic_effect(TO);

    gRecognized = 1;

    return 1;
}

int wield_message1()
{
    wielder->catch_msg("\nAs you grip the sleek silver lance, you see a "+
      "vision...\n\n\n");
    tell_room(E((wielder)), QCTNAME((wielder))+"'s eyes glaze over, as "+
      PRONOUN((wielder))+" grips the silver sleek lance in both hands, "+
      "and "+PRONOUN((wielder))+" stands motionless, staring into the "+
      "distance with a blank look...\n", (wielder));

    wielder->add_magic_effect(TO);
    wielder->set_skill_extra(1, 25);


    if (E(TO) == wielder)
	set_alarm(5.0, 0.0, "wield_message2");
    return 1;
}

void wield_message2()
{
    wielder->catch_msg("You see a charging stallion, armoured in purest "+
      "platinum and snorting as it raced the winds.  A rider sits "+
      "astride the stallion, also clad in platinum.  On his chest he "+
      "wears a breastplate with the symbol of the Triumvirate:  The "+
      "Crown, the Sword, and the Rose...\n\n");

    if (query_wielded() == wielder)
	set_alarm(5.0, 0.0, "wield_message3");
}

void wield_message3()
{
    wielder->catch_msg("Within the visor that covers his face is light, "+
      "brilliant and life-giving.\n\n");

    if (query_wielded() == wielder)
	set_alarm(5.0, 0.0, "wield_message4");
}

void wield_message4()
{
    wielder->catch_msg("The great charger leaps into the air, and massive "+
      "wings sprout from its sides.  It head elongates, and its neck "+
      "twists and grows, losing none of it's majesty or beauty.  From "+
      "platinum-clad steed, it becomes a platinum dragon, and together "+
      "knight and companion drive the darkness before them with the "+
      "aid of the lance held by the rider!\n\n");

    if (query_wielded() == wielder)
	set_alarm(5.0, 0.0, "wield_message5");
}

void wield_message5()
{
    wielder->catch_msg("The lance shines with a life, a purpose of it's own,"+
      " and the darkness falls before it.  Born of the world and the "+
      "heavens, it has the true power, the true good.\n\n");

    if (query_wielded() == wielder)
	set_alarm(5.0, 0.0, "wield_message6");
}

void wield_message6()
{
    wielder->catch_msg("The darkness destroyed, the dragon lands before you, "+
      "and you fall to your knees in awe and reverance.  The Knight "+
      "releases the lance from his grasp, and holds it towards you...\n\n");

    if (query_wielded() == wielder)
	set_alarm(5.0, 0.0, "wield_message7");
}

void wield_message7()
{
    wielder->catch_msg("With some hesitation you reach out and take the lance.\n"+
      "The rider and the knight vanish, and in your hand is the Dragonlance.\n");

    gRecognized = 1;

    if (query_wielded() == wielder)
	set_alarm(2.0, 0.0, "do_rejoice");
}


/*
* Function name: wield
* Description:     Wield a weapon.
* Arguments:       wep - The weapon to wield.
* Returns:         True if wielded.
*                  String with failure message if not wielded.
*/
mixed
wield(object what)
{

    if (TP->query_alignment() < 910)
    {
	return "The "+short()+" resists you as you try to wield it.\n";
    }

    if (TP->query_stat(4) < 100)
    {
	return "The "+short()+" resists you as you try to wield it.\n";
    }

//    wielder = TP;
    if (wielder->query_guild_member("Solamnian Knights"))
         return wield_message1();
    else
         return wield_message_poor1();
}


/*
* Function name:   unwield
* Description:     Unwield a weapon.
* Arguments:       wep: The weapon to unwield.
* Returns:         None.
*/
int
unwield(object what)
{
    wielder->catch_msg("You unwield the footman's dragonlance, and feel "+
      "its warmth retreat from your body.\n");
    tell_room(E(wielder), QCTNAME(wielder)+" unwields the "+
      "footman's dragonlance.\n", wielder);

    TP->remove_magic_effect(TO);

    if (wielder->query_guild_member("Solamnian Knights"))
       {
        wielder->set_skill_extra(1, 0);
       }

    gRecognized = 0;
    return 1;
}


/*
* Function name: did_hit
* Description:   Tells us that we hit something. Should produce combat
*                messages to all relevant parties. If the weapon
*                chooses not to handle combat messages then a default
*                message is generated.
* Arguments:     aid:   The attack id
*                hdesc: The hitlocation description.
*                phurt: The %hurt made on the enemy
*                enemy: The enemy who got hit
*                dt:    The current damagetype
*                phit:  The %success that we made with our weapon
*                dam:   The actual damage caused by this weapon in hit points
* Returns:       True if it handled combat messages, returning a 0 will let
*                the normal routines take over
*/
public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    string dam_descr;

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if(QRACE(enemy) == "dragon" && enemy->query_alignment() > 0)
    {
	wielder->catch_msg("Fear wrenches your body as you feel an intense "+
	  "pain tearing up your arm...\n");
	wielder->catch_msg("The "+short()+" erupts in a violent explosion of "+
	  "silver flames, burning you badly!\n");
	tell_room(E(wielder), QCTNAME(wielder)+"'s "+short()+" erupts in a "+
	  "violent explosion of silver flames, burning "+OBJECTIVE(wielder)+
	  " badly!\n", wielder);
	TO->add_prop("_(wielder)j_i_broken", 1);
	move(E(wielder));
	wielder->heal_hp(-700 + random(500));
	if (wielder->query_hp() <= 0)
	{
	    tell_room(E(wielder), QCTNAME(wielder)+"'s body is engulfed in the "+
	      "bright silver flames, leaving only charred remains.\n", wielder);
	    wielder->do_die(TO);
	}
    }

    if(QRACE(enemy) == "dragon" || QREALRACE(enemy) == "draconian")
    {
	if(phurt > 0)
	{
	    switch(phurt)
	    {
	    case 0..30:
		dam_descr = " slides effortlessly into "+QTNAME(enemy)+"'s "+
		hdesc+".\n";
		break;

	    case 31..60:
		dam_descr = " plunges deeply into "+QTNAME(enemy)+"'s "+
		hdesc+".\n";
		break;

	    default:
		dam_descr = " impales "+QTNAME(enemy)+"'s "+hdesc+", "+
		"driving through flesh and bone with unimaginable ease.\n";
		break;
	    }

	    wielder->catch_msg("Your "+short()+" feels warm in your grasp "+
	      "as it"+dam_descr);
	    wielder->tell_watcher("The "+short()+" wielded by "+
	      QCTNAME(wielder) + dam_descr, enemy);
	    enemy->heal_hp(-dam);

            return 1;
	}
    }
    return 0;
}

