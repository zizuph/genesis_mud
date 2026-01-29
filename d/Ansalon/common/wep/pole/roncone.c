/* 20.5.2000 by Torqual */
/* Pole for auraks - a bit of red-herring for players */

#pragma strict_types		//  lest keep it clean

#include "/d/Ansalon/common/defs.h"

inherit "/std/weapon";
inherit "/lib/keep.c";

/* includes */

#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>

/* defines */
#define BASE_HIT 45		/* it is magical */
#define BASE_PEN 45		/* it is magical */

/* variables */
int gW_pen, gD_type;		/* for unarmed  */
int debug;			/* debug mode on/off */
string color = "blue";   /* for dragonarmy colouring */

/* prototypes */

void set_color(string new_color);
string query_color();
string my_long();
string query_enemy_weapon(object attacker, object enemy);
void set_debug(int debug_level);
int query_debug();

void
create_weapon()
{

    set_name("roncone");
    set_pname("roncones");
    add_name("polearm");
    set_keep();
    set_adj(({"dragon-bladed", "short"}));
    set_short("dragon-bladed roncone");
    set_pshort("dragon-bladed roncones");
    set_long("@@my_long@@");

    add_item(({"blades", "ears"}), "Blades or 'ears' are set at the "+
        "base of the spear-head. Pointed backwards, they protect " +
        "it from being cut off. Each of the blades is shaped to " +
        "resemble one of wings of a dragon and painted in " +
        query_color() + ".\n");

    add_item(({"shaft","short shaft"}), "The shaft is made of single " +
        "piece of polished oak-wood. Half of it is wrapped with "+
        "leather to improve the grip on the weapon.\n");

    add_item(({"spear-head", "broad spear-head", "iron spear-head"}),
        "The head is set at the end of the shaft, with two 'ears' " +
        "at its base. Someone has put a lot of work to shape it " +
        "after the dragon's head, although only in general.\n");


    /* Now we want to set the 'to hit' value and 'penetration value'
     * Due to shape of the 'ears' it makes a bit more damage.
     */
    
      set_hit(BASE_HIT);
      set_pen(BASE_PEN);


    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_POLEARM); 		/* It's polearm */
    set_dt(W_IMPALE | W_SLASH); /* Impaling and slashing */

    set_hands(W_BOTH); /* in both hands */

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(BASE_PEN,W_POLEARM));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(BASE_HIT, BASE_PEN));
    add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_WEAPON(BASE_PEN, W_POLEARM)/2);

    /* Weapon can be colored */
    add_prop(OBJ_I_COLORABLE, 1);

    set_wf(TO); /* this object defines its own wield() function */
    set_likely_break(1); /* very sturdy */
    set_likely_dull(1); /* stays sharp for long */


    /* lets make it magic with all the info needed */
    
    add_prop(MAGIC_AM_MAGIC,({70,"death"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);	/* it is magic wep */
    add_prop(OBJ_M_NO_BUY, 1);		/* not to be resold */
    add_prop(MAGIC_AM_ID_INFO, ({
        "When you concentrate upon the nature of the weapon " +
	    "the scent of death and decay can almost be felt hovering " +
	    "above the the weapon.", 1,
	"Suddenly the phantom face of a beautiful yet evil woman " +
 	    "materializes before your very eyes. \" Aahhh so it has " +
	    "been taken from my servant. So be it. I hope you will find "+
	    "this weapon ... amusing\". With a mocking laugh the face "+
	    "withdraws.", 5,
	"Upon the further examination you discover that a curse has "+
	    "been laid on the weapon.", 10,
	"As you try to investigate the curse, words appear on one of the "+
	    "blades of the "+ short() +" \" Skilled shall fall as " +
	    "had fallen the servant of mine. This weapon shall be their " +
	    "weakness and doom\". The words fade slowly away.", 35,
	"With the vanishing of these words, others appear on the other " +
	    "blade: \"The more skilled you are the less helpful I " +
	    "am - until my Lady commands me otherwise.\" The words fade " +
	    "slowly away.", 60,
	"Finally the true nature of the weapon dawns on you. The "+ short() +
	    "will become worse the more skilled in the art of " +
	    "using polearms the wielder is.", 85 }) );

    add_prop(OBJ_S_WIZINFO, "The weapon is given to auraks by their queen " +
	"and for them it will be of superior quality. When player will "+
	"decide to use it - it will be better for less skilled " +
	"in polearm and getting worst for more skilled players."+
	"From 100 to 0, each 20 skillpoints one hit/pen bonus point " +
	"will be decreased so in the end no bonus is given.\n" +
	"Also high skilled players will be forced " +
	"to make mistakes allowing their opponent to have an extra hit "+
	"on them. Very unskilled players will simply miss but penalty " +
	"will be rather small.\n");
}
string
my_long()
{
    string str;

    str = "You take a closer look at the " + short() + ".\n" +
       "Quite short, the polished shaft of this weapon ends with a " +
       "broad spear-head made of tempered iron. On both sides of " +
       "the shaft are two curved blades, shaped to resemble dragon wings, " +
       "set to not only give extra protection for the wielder's hands " +
       "but also to deal deep and painful wounds with its jagged edges. " +
       "The weapon looks as if it would be deadly in skilled " +
       "hands, but could cause problems to those who are less "+
       "able.\n";

    return str;
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "&&" + color;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_color(a[1]);
    init_wep_recover(a[0]);
}

void
set_color(string col)
{
    color = col;
}

string
query_color()
{
    return color;
}

/* After we tried to hit something this function is called with the result. */
/* Function name:       did_hit()
 * Description:         We managed to swing our weapon at enemy. Now we
 *			must give a curse time to work. Player will
 *			suffer either when they have no skill and miss by
 * 			a mile or when they are skilled but the hit was
 *			really strong. For smaller players the penalty
 *			will be rather symbolic, big guns will ... *grin*
 *                      SS_ELEMENT_DEATH is used here since those skilled
 *                      will have better chance to resist effect
 *			SS_ELEMENT_LIFE is used here since those skilled
 *			will suffer more from opposite element
 * Arguments:           object enemy - the one we try to hit
 * Returns:             0 - if we cannot hit
 *                      1 - if we can hit
 */
varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
	int phit, int dam)
{
    int     skill_lev, i;
    string  short_weapon_wielded = "",
   	    my_hdesc; // where they hit wielder
    string *my_hitlocs=({"head", "leg", "arm", "back", "body"});
    object *weapons_wielded;
    object  attacker = query_wielded(); /* the one that holds the weapon */

    /* Draconians are not affected by the curse */
  
    if (attacker->query_race_name() == "draconian")
    {
        return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }


    short_weapon_wielded = query_enemy_weapon(attacker, enemy);

    /* half of the skills is taken against the player */
    skill_lev = attacker->query_skill(SS_WEP_POLEARM);

    /* DEBUG MESSAGE */
    if (query_debug())
     find_player("torqual")->catch_msg("DEBUG: phurt " + phurt +
         " damage " + dam + "\n");

    my_hdesc=my_hitlocs[random(sizeof(my_hitlocs))];

    switch(phurt)
    {
    case -1:
    case -2:

	if (wielder->resolve_task(TASK_ROUTINE,
            ({wielder->query_prop(MAGIC_I_RES_DEATH), SKILL_MIN, TS_DEX,
              TS_WIS, SS_DEFENCE, SKILL_END }),
	    enemy, ({skill_lev }) ) <0)
        {
            attacker->catch_msg("You thrust your " +
			 short() + " at " + QTNAME(enemy) +" but the force " +
			 "of the blow carries you forward past the enemy. " +
			 "Seeing your mistake, "+ HE(enemy) +" hits your " +
			 my_hdesc +" hard"+ short_weapon_wielded +".\n");

             enemy->catch_msg(QCTNAME(attacker) + " thrusts " +
			 HIS(attacker) + " " + short() + " at you but " +
			 HE(attacker) + " misses and " +
			 "the strength of the blow sends " + HIM(attacker) +
			 " flying by. You exploit the mistake and strike " + 
			 HIS(attacker) + " " + my_hdesc + " hard" +
			 short_weapon_wielded + ".\n");

	     attacker->tell_watcher(QCTNAME(attacker) + " thrusts " +
		  HIS(attacker) + " " + short() + " at " + QCNAME(enemy) +
		  " but does it too hard, leaving an opening in " + 
		  HIS(attacker) + " defence. " + QCTNAME(enemy) +
		  " hits "+ QTNAME(attacker) + "'s " + my_hdesc + " hard" +
		  short_weapon_wielded + ".\n", enemy,
                  ({attacker,enemy}));

		/* 
		 * reduction of wielders HP
		 */
                if (query_debug())
                {
	        find_player("torqual")->catch_msg("DEBUG : lets hit him \n");
		    find_player("torqual")->catch_msg("DEBUG : it has "+
                    attacker->query_hp() +" " +  gW_pen + " "+ gD_type +
                    "\n");
                }
	               /* hit_me(wpen, dtype, enemy, attack_id) */
        	attacker->hit_me(gW_pen, gD_type, enemy, -1);

                if (query_debug())
                {
                  find_player("torqual")->catch_msg("DEBUG : Now it has "+
		    attacker->query_hp() +"\n");
		  find_player("torqual")->catch_msg("DEBUG : After the " +
		    "hit_me\n");
                }
        }
	else
        {
            query_wielded()->catch_msg("You thrust your " + short() +
                " at " + QTNAME(enemy) +" but "+ HE(enemy) +
                " manages to jump aside and your attack narrowly " +
                "misses.\n");

            enemy->catch_msg(QCTNAME(query_wielded()) + " thrusts " +
                HIS(query_wielded()) + " " + short() +
                " at you, but you narrowly avoid the blow.\n");

            enemy->tell_watcher(QCTNAME(query_wielded()) +
                " thrusts " + HIS(query_wielded()) + " " + short() +
                " at "+ QTNAME(enemy) + " but the blow narrowly misses.\n",
                enemy, ({query_wielded(), enemy}));
                                 /* The last arg say who shall not hear */ 
        }

	break;

    case 20..MAXINT :

        if (wielder->resolve_task(TASK_DIFFICULT,
            ({wielder->query_prop(MAGIC_I_RES_DEATH), SKILL_AVG, TS_DEX,
              TS_INT, TS_WIS, SS_DEFENCE, SKILL_END }),
            enemy, ({skill_lev }) ) <0)
        {
            attacker->catch_msg("You swing your " +
	        short() + " at " + QCTNAME(enemy) +". The weapon " +
 	        "shakes and twists in your hands and your attack "+
	        "misses. The strength of the blow turns you around, " + 
	        "exposing your side and back for an easy blow. " +
	        "Seeing this " + QTNAME(enemy) + " hits you " +  
	        "hard" + short_weapon_wielded + ".\n");

	    enemy->catch_msg(QCTNAME(attacker) + " swings " +
	        HIS(attacker) + " " + short() + " at you. " +
	        "As the weapon advances toward your body it twists " +
	        "and shakes in " + QTNAME(attacker) + "'s hands and " +
	        HE(attacker) + " misses. The force of the blow turns " +
	        HIM(attacker) + " around. Seeing the chance, you hit " +
	        HIS(attacker) + " " + my_hdesc + " hard" +
	        short_weapon_wielded + ".\n");

 	    enemy->tell_watcher(QCTNAME(attacker) + " swings " +
	        HIS(attacker) + " " + short() + " at " + QCNAME(enemy) +
	        " with full force but unexpectedly misses, leaving " +
	        "an opening in " + HIS(attacker) + " defence. " + 
	        QCTNAME(enemy) + " hits " + HIS(attacker) + " " + 
	        my_hdesc + " hard" + short_weapon_wielded + ".\n", enemy,
                ({enemy,attacker}));

            /*
             * reduce HP  
             */
             if (query_debug())
             {
		find_player("torqual")->catch_msg("DEBUG : lets hit " +
		    "him good\n");
		find_player("torqual")->catch_msg("DEBUG : Raa has "+
		    attacker->query_hp() + "\n");
             }

		attacker->hit_me(gW_pen, gD_type, enemy, -1);

             if (query_debug())
             {
		find_player("torqual")->catch_msg("DEBUG : He got what " +
		    "he deserved\n");
		find_player("torqual")->catch_msg("DEBUG : Raa has "+
		    attacker->query_hp() + "\n");
             }
        }

	break;
    }

    /* Kill the target, if appropriate */
    if (attacker->query_hp() <= 0)
    {
	attacker->catch_msg("The last blow was fatal. "+
	    "In amusement you observe the ground closing in on " +
	    "you... or it is you who falls down?\n");

	enemy->catch_msg("You hit "+ QCNAME(attacker) +
	   " in the " + hdesc + ", piercing it through. " +
	   C(HE(attacker)) + " falls on the ground straight into "+
	    "a puddle of " + HIS(attacker) + " own blood.\n");

	enemy->tell_watcher(QCTNAME(enemy) + " hits "+
	    QCNAME(attacker) + " " + query_enemy_weapon(attacker, enemy) +
	    " dealing a gruesome blow. The corpse " +
	    "falls on the ground, straight into a puddle of " +
	    "red blood.\n", enemy, ({enemy, attacker})); 

        attacker->command("unwield all");

	attacker->do_die(enemy);
    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

/*
* Function name: wield
* Description:     Wield a weapon. 
* Arguments:       wep - The weapon to wield.
* Returns:         true -  if can be wielded 
*                  "string" - String with failure message if not wielded.
*/
mixed
wield(object what)
{
    object wielder;

    wielder = E(TO);

    if (!living(wielder))
    return -1;

    /* weapon is given to auraks by DQueen, they got bonus */
    if (wielder->query_race_name() == "draconian")
    {
	set_hit(BASE_HIT + 5);
	set_pen(BASE_PEN + 5);

        write("The " +short() + "'s curved blades start gleaming slightly " +
	    "as you wield the weapon. The brief presence of your " +
	    "Queen assures you about her support.\n");

	say("The " + short() + "'s curved blades start gleaming slightly "+
	    "as " + QCNAME(wielder) + " wields " + HIS(wielder) + " " +
	    "weapon.\n");
	return 1;
    }

    if (wielder->query_base_stat(SS_STR) < 20)
    {
       write("As you try to wield it, the " + short() +
             " trembles violently in your hands. You fail to " +
             "handle the weapon and drop it on the ground.\n");
       say(QCTNAME(wielder) + " tries to wield the " + short() +
           " but for some reason " + HE(wielder) + " drops it on " +
           "the ground.\n"); 

       wielder->add_fatigue(-20);
       TO->move(E(wielder));

       return "";
    }


    switch (wielder->query_skill(SS_WEP_POLEARM) +
              ( wielder->query_skill(SS_ELEMENT_LIFE)/2 -
                wielder->querry_skill(SS_ELEMENT_DEATH)
               )
            )
    {
	case 0..20:
	    /* newbies */
		    set_hit(BASE_HIT -0); /* we decrease hit by 0 */
		    set_pen(BASE_PEN -0); /* we decrease pen by 0 */

		break;

	case 21..40:
	    /* better skilled newbies and some layman members */
		    set_hit(BASE_HIT -1);
		    set_pen(BASE_PEN -1);

		break;

	case 41..60:
	    /* max skilled layman and first steps in occ */ 
		    set_hit(BASE_HIT -2);
		    set_pen(BASE_PEN -2);

		break;

	case 61..75:
	    /* medium skilled occ */
		    set_hit(BASE_HIT -3);
		    set_pen(BASE_PEN -3);

		break;

	case 76..90:
	    /* skill above average, for some guilds top level of skill */
		    set_hit(BASE_HIT -4);
		    set_pen(BASE_PEN -4);

		break;
	case 91..100:
	    /* from 90 to 100 - guru level - no bonus for skill */
		    set_hit(BASE_HIT -5);
		    set_pen(BASE_PEN -5);
		    
		break;
    }

    write("The " +short() + "'s curved blades start gleaming slightly as you "+
          "wield the weapon.\n");
    say("The " + short() + "'s curved blades start gleaming slightly " +
          "as " + QCNAME(wielder) + " wields " + HIS(wielder) + " " +
          "weapon.\n");

    wielder->add_fatigue(-10);  // tired a bit
    wielder->add_mana(-20);	// mind reels a bit
    wielder->update_weapon(TO);	// this should update combat object
    return 1; /* we handled wielding and no standard message */
}

/*
* Function name:   unwield
* Description:     Unwield a weapon.
* Arguments:       what: The weapon to unwield.
* Returns:         None.
*/
int
unwield(object what)
{
   if (!random(2))
   {

     /* we make the weapon as it was at the beginning */

    query_wielded()->catch_msg("For a brief moment you struggle to " +
        "release the " + short() + " from your hands. When finally " +
        "you manage to unwield it, the blades slowly stop glowing.\n");

    say("As " + QCNAME(query_wielded()) + " releases " +
	HIS(query_wielded()) + " grip on the shaft of the " + short() +
	" and the blades slowly stop glowing.\n");

    query_wielded()->add_mana(-20);
    query_wielded()->add_fatigue(-10);
	
	set_hit(BASE_HIT);
	set_pen(BASE_PEN); 

    return 1;	// no standard wield/unwield message 
   }

    set_hit(BASE_HIT);
    set_pen(BASE_PEN);

    return 0;   // standard message
}

/* FUNCTION: query_enemy_weapon
 * Description:  this function checks if enemy wields something and
 *               returns damage and weapon type values
 *               it is used to make additional damage to the wielder of
 *               the weapon
 * Arguments  :
 * Returns    :  returns string that is added to the damage message
 * ADDITION   :  to make damage a bit bigger I added 10 to gW_pen
*/
string
query_enemy_weapon(object wielder, object enemy)
{
    string short, return_string;

    object *weapons_wielded;

    weapons_wielded = enemy->query_weapon(-1);


    if (sizeof(weapons_wielded))
    {

        short = weapons_wielded[0]->query_short();
        return_string = " with " + HIS(enemy) + " " + short;
	gW_pen = weapons_wielded[0]->query_pen();
	gD_type = weapons_wielded[0]->query_dt();

   /* to make damage a bit bigger */
        gW_pen += 10;

    }
    else
    {
       return_string = "";

       gW_pen = F_UNARMED_PEN(enemy->query_skill(SS_UNARM_COMBAT),
                             enemy->query_stat(SS_STR));
       gD_type = W_BLUDGEON; /* we hit with hands */

  /* to make damage a bit bigger */
        gW_pen += 10;

    }

	return return_string;
}

void
set_debug(int debug_level)
{
    debug = debug_level;
}

int
query_debug()
{
    return debug;
}
