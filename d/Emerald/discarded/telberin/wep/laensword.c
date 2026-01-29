/* laensword.c created by Shiva@Genesis.
 * A holy longsword.
 * Notes:
 *   Blade fashioned from light laen, an extremely hard, resistant glass.
 *
 *   When wielded by "worthy" creatures (see is_worthy() below):
 *       - creates 1 level of light for 2 seconds when evil
 *         (alignment < -500) or undead creatures arrive.
 *       - heals 18 hitpoints per minute.
 *       - provides armour protection for both arms and body.
 *         
 *   When wielded by good creatures (alignment >= 100):
 *       - has greatly increased hit/pen
 *  
 *   When wielded by evil creatures (alignment <= -100):
 *       - has hit/pen of -100
 *       - has no chance to hit
 *       - can damage wielder and cause wielder to drop weapon
 *
 *  Healing and light are implemented through a shadow (laensword_sh.c)
 */

inherit "/std/weapon";
inherit "/d/Genesis/magic/resist";

#include "/d/Emerald/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <tasks.h>

#define DEBUG_WHO find_player("shiva")
#include DEBUGFILE

#define SWORD_SHADOW "/d/Emerald/telberin/wep/laensword_sh"
#define SWORD_ARMOUR "/d/Emerald/telberin/wep/laensword_arm"

#define UNDEAD(x) (x->query_prop(LIVE_I_UNDEAD))
#define ALIGN(x)  x->query_alignment()

#define EVIL_HIT  -100
#define NTRL_HIT   20
#define GOOD_HIT   30
#define WORTHY_HIT 47
#define EVIL_PEN  -100
#define NTRL_PEN   15
#define GOOD_PEN   25
#define WORTHY_PEN 45

int is_worthy(object who);

void create_weapon()
{
    set_name(({ "sword", "longsword", "laensword" }));
    set_adj(({ "light-laen", "laen" }));
    set_short("longsword");
    set_long("A fine, elven-made weapon, the longsword's blade " +
        "is made of a smokey, amber glass, and its hilt is " +
        "fashioned from mithril.\n");
  
    add_item("blade", "@@blade_desc@@");
    add_item("hilt", "The hilt looks to be made of fine " +
        "white mithril.  There is a large emerald set into " +
        "its base, and an image of an angel set into it.\n");
    add_item("emerald", "A very large emerald securely set into " +
        "the base of the sword.\n");
    add_item("angel", "@@angel_desc@@");
  
    set_wt(W_SWORD);
    set_hands(W_RIGHT);
    set_dt(W_SLASH | W_IMPALE);
    set_wf(this_object());
  
    set_likely_dull(1);
    set_likely_break(1);
    set_likely_corr(0);
  
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 7500);
    add_prop(OBJ_I_VALUE, 4200);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_STEAL, "The sword glows with a dull, blue aura, " +
        "and your hand is forced back!\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 70, "life" }));
    add_prop(MAGIC_AM_ID_INFO, ({ 
        "The sword possesses a holy aura.\n", 10,
        "It will resist being used by evil creatures, but aids " +
        "those worthy of its holy power.\n", 50,
        "It's magic seems primarily defensive in nature.\n", 75,
        "When wielded by a truly powerful, holy warrior, the " +
        "longsword will aid its possessor in defense and " +
        "accelerate healing as well as warn of the presence of " +
        "evil creatures.\n", 90 }));
    add_prop(OBJ_S_WIZINFO, "This sword's hit/pen vary according " +
        "to the alignment of the wielder (higher for higher " +
        "alignment).  It will resist being used by very evil/undead " +
        "creatures, causing them damage when they try to hit with it. " +
        "If the wielder is worthy, it adds ac to both arms and body, " +
        "heals at a regular rate, and notifies of the arrival of " +
        "evil/undead livings.\n");
}

string
blade_desc()
{
    if (this_player()->query_skill(SS_APPR_OBJ) < 50)
    {
      return "The blade is made of some type of amber-colored glass.  " +
          "The edge is quite sharp, without a single nick or blemish.\n";
    }
  
    return "You recognize the amber-colored glass from which the blade " +
        "is fashioned as light laen, an extremely strong and resistant " +
        "volcanic glass.  The edge it quite sharp, without a single " +
        "nick or blemish.\n";
}

string
angel_desc()
{
    if (UNDEAD(this_player()) || (ALIGN(this_player()) <= -100))
    {
    	this_player()->add_panic(10);
    	return "The angel seems to be looking back at you, his " +
    	    "eyes filled with wrath that pierces you, sending a " +
    	    "shiver through your very soul.\n";
    }
  
    if (ALIGN(this_player()) >= 100)
    {
    	if (!is_worthy(this_player()))
    	{
      	    return "The angel seems to be looking back at you with " +
    	        "a reassuring look in his eyes.\n";
    	}
    
    	return "The angel seems to be looking back at you, his eyes " +
    	    "filled with holy resolve and reassurance.\n";
    }
  
    return "The angel seems to be looking back at you, beckoning to " +
        "with his gaze, his eyes filled with hope.\n";
}

// True if "who" is able to use all of the sword's powers
int
is_worthy(object who)
{
    if (!who)
    {
        return 0;
    }
  
    if (IS_WIZ(who) || !(interactive(who)))
    {
        return 1;
    }
  
    if (UNDEAD(who))
    {
        return 0;
    }
  
    if (ALIGN(who) < 900)
    {
        return 0;
    }
  
    if (who->query_average_stat() < 120)
    {
        return 0;
    }
  
    if (who->query_stat(SS_WIS) < 100 || who->query_stat(SS_DIS) < 100)
    {
        return 0;
    }
  
    return 1;
}

/* Set the current hit and pen of this weapon depending on the
 * owner's alignment and bonus_val (if wielder is good)
 */
varargs void
update_sword(int no_rewield)
{
    int al, hit, pen;
    object sh;
  
    hit = query_hit();
    pen = query_pen();
  
    if (!this_player())
    {
        DEBUG("No this_player()");
        // no owner, use values for neutral owner
        set_hit(NTRL_HIT);
        set_pen(NTRL_PEN);
        return;
    }
    else if ((al = ALIGN(this_player())) <= -100 || UNDEAD(this_player()))
    {
        DEBUG("Evil || Undead");
        // owner is evil or undead...minus values
        set_hit(EVIL_HIT);
        set_pen(EVIL_PEN);
    }
    else if (ABS(al) < 100)
    {
        DEBUG("Neutral");
        // neutral owner
        set_hit(NTRL_HIT);
        set_pen(NTRL_PEN);
    }
    else 
    {
        DEBUG("Good");
        // good owner...add bonus_val modifier
        set_hit(GOOD_HIT);
        set_pen(GOOD_PEN);
    }
  
    // Invoke various abilities of the sword implemented through a shadow
    if (is_worthy(this_player()))
    {
        DEBUG("Worthy");
    
        set_hit(WORTHY_HIT);
        set_pen(WORTHY_PEN);
    
        setuid();
        seteuid(getuid());

        if (!this_player()->query_laensword_sh())
        {
            clone_object(SWORD_SHADOW)->add_sword_sh(this_player(), this_object());
        }
  
        if (!present("laensword_arm", this_player()))
        {
            clone_object(SWORD_ARMOUR)->add_laensword_armour(this_player(),
                (this_player()->id("prince_curan") ? 20 : 
                random(20, atoi(OB_NUM(this_player())))));
        }
    }
    else
    {
        this_player()->remove_laensword_sh();
        all_inventory(this_player())->remove_laensword_armour();
    }
  
    if (((hit != query_hit()) || (pen != query_pen())) && !no_rewield)
    {
        this_player()->update_weapon(this_object());
    }
}

// Called when this weapon is wielded
int wield(object ob)
{
    update_sword();
    return 0;
}

// Called when this weapon is unwielded
int
unwield(object ob)
{
    this_player()->remove_laensword_sh();
    all_inventory(this_player())->remove_laensword_armour();
    return 0;
}

void
leave_env(object to, object from)
{
    ::leave_env(to, from);
  
    if (from && living(from))
    {
        from->remove_laensword_sh();
        all_inventory(this_player())->remove_laensword_armour();
    }
}

/* Called before we make an attack with this weapon to see
 * if the attack has a chance to succeed
 */
int
try_hit(object who)
{
    mixed *attack, wielder = query_wielded();
    int pen;
  
    if (!wielder)
    {
        return 1;
    }
  
    // if the wielder is undead or very evil, nasty things happen
    if (UNDEAD(wielder) || ALIGN(wielder) < -500)
    {
          // chance that the sword will attack wielder
        if (random(100) > random(wielder->query_stat(SS_DIS) * 2))
        {
            DEBUG("OUCH!");
            wielder->catch_tell("Magical energy surges from the sword, " +
                  "sending wave of pain radiating through your body.\n");     
            pen = 600 * (100 - 
                spell_resist(this_object(), wielder, SS_ELEMENT_LIFE,
                TASK_FORMIDABLE));
        
            wielder->hit_me(pen, MAGIC_DT, this_object(), -1);
            if (wielder->query_hp() <= 0)
            {
                  wielder->do_die(this_object());
                  return 0;
            }
        
            if (wielder->resolve_task(TASK_DIFFICULT + pen / 3, 
                  ({ TS_DEX, TS_DIS })) <= 0)
            {
                  wielder->catch_tell("You lose your grip on the longsword!\n");
                  tell_room(environment(wielder), ({ 
                      wielder->query_met_name() + " loses " + POS(wielder) + 
                      " grip on " + POS(wielder) + " longsword.\n", 
                      "The " + wielder->query_nonmet_name() + " loses " + 
                      POS(wielder) + " grip on " + POS(wielder) + " longsword.\n",
                    "" }), wielder);
                  move(environment(wielder));
            }
        }
  
        // No chance to hit
        return 0;
    }
  
    // if wielder is evil, there is no chance to hit
    if (ALIGN(wielder) <= -100)
    {
        return 0;
    }
  
    return 1;
}
