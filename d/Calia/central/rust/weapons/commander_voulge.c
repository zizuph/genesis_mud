/* Coded the 27/11/98 by Bishop of Calia. This is a polearm
for use by the commander of the gnome forces */

inherit "/std/weapon";


#include <filter_funs.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <options.h>
#include "defs.h"


#define WHIT 55
#define WPEN 55 

object wielder;

public void
create_weapon()
{
    set_name("voulge");
    add_name("polearm");
    set_adj("heavy");
    set_adj("black");

    set_long("This powerful polearm bears resemblance to a giant" +
        " axe. At the end of a black wooden shaft, almost the length" +
        " of two gnomes, is a massive, broad axe-head. The metal of" +
        " the blade has also been blackened. This voulge could clearly" +
        " serve as an executioner's weapon.\n");

    set_hit(WHIT);
    set_pen(WPEN);
    set_wt(W_POLEARM);
    set_dt(W_SLASH);
    set_hands(W_BOTH);
    set_wf(TO);


    add_prop(OBJ_I_WEIGHT, 16000);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({	35, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This polearm has been enchanted to" +
        " easily slice through flesh.", 15, "This polearm has been" +
        " enchanted to be able to lop a wounded foe's head off, though" +
        " it comes at a price.",30, "This weapon has been enchanted" +
        " in such a way that it easily can behead a foe. The price" +
        " however, is the weapons slowness.",50}));
    add_prop(OBJ_S_WIZINFO,"This polearm reduces the LIVE_I_QUICKNESS" +
        " prop in the wielder by 80. Also, if the foe's hp drop below" +
        " 50%, there's a chance with each blow that" +
        " foe will be beheaded, and die regardless of his/her remaining" +
        " hp.\n");

    seteuid(getuid(TO));
}

// Called in case of a fumble.

void
lose_control()
{
    object *targ;
    mixed *hitresult;
    string how, onlooker;
    int i, x;

    wielder = query_wielded();

    targ = wielder->query_team_others();
    x = sizeof(targ);

    if (targ != 0)
    {
        tell_room(environment(wielder), QCTNAME(wielder) + 
            " loses control of " + wielder->query_possessive() + 
            " black heavy voulge, and carves a swath through " + 
            wielder->query_possessive() + " own team!\n", wielder);

        wielder->catch_msg("You lose control of the powerful" +
            " weapon and carve a swath through your own team!\n");

        for(i=0 ; i < x ; i++)
            {
                hitresult = targ[i]->hit_me(50+random(500), W_SLASH,
                    wielder , -1);
                switch (hitresult[0])
                {
                    case 0:
                        how = "You are unharmed, fortunately";
                        onlooker = "is unharmed";
                        break;
                    case 1..5:
                        how = "You suffer only a mild cut";
                        onlooker = "suffers only a mild cut";
                        break;
                    case 6..13:
                        how = "You are gashed painfully";
                        onlooker = "is gashed painfully";
                        break;
                    case 14..40:
                        how =  "You are badly hurt as the voulge" +
                            " slices through your flesh";
                        onlooker = "is badly hurt as the voulge" +
                            " slices" +
                            " through " + targ[i]->query_possessive() +
                            " flesh";
                        break;
                    default:
                        how = "You are devastated as the blade of" +
                            " the voulge digs deep into your flesh" +
                            " and finds your vital organs";
                        onlooker = "is devastated as the blade of" +
                            " the voulge digs deep into " +
                            targ[i]->query_possessive() +" flesh and" +
                            " finds " + targ[i]->query_possessive() +
                            " vital organs";
                        break;
                }
                
                if (targ[i]->query_hp() <= 0)
                {
                    how = "You are decapitated by the stray blow!" +
                        " Your last feeling is the sensation of" +
                        " spinning round and round through the air";
                    onlooker = "is decapitated by" +
                        " the stray blow from the voulge! " +
                        capitalize(targ[i]->query_possessive()) + 
                        " head rolls around on the ground, the face" +
                        " frozen in an expression of shock and horror";
                }

                targ[i]->catch_msg(how + ".\n");
                tell_room(environment(wielder), QCTNAME(targ[i]) + " " +
                    onlooker + ".\n", targ[i]);
                targ[i]->stop_fight(wielder);

                if (targ[i]->query_hp() <= 0)
                {
                    targ[i]->do_die(TO);
                }
                
            } 
    }
}

// Checks for a fumble.

void
check_fumble()
{
    int likely_fumble;

    likely_fumble = wielder->query_stat(SS_STR) + 
        wielder->query_stat(SS_DEX) +
        wielder->query_skill(SS_WEP_POLEARM) - 300;

    if(likely_fumble < 15)
    {
        likely_fumble = 15;
    }
 
    if(random(likely_fumble) == 0)
    {
        lose_control();
    }
    
}

 
// Implements the beheading special.

int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, 
        int phit, int dam)
{
    wielder = query_wielded();

    if (phurt < 1)
        {
         check_fumble();
        } 

    if (hdesc=="head" &&
        100 * enemy->query_hp() / enemy->query_max_hp() < 50)  
    {
        if (random (50 * enemy->query_hp() / enemy->query_max_hp())==0)
        {
            wielder->catch_msg("You cleanly decapitate " + QTNAME(enemy) +
                " with your heavy voulge, " +
                "" + enemy->query_possessive() + " head falling to the" +
                " ground and rolling around a few times before becoming still,"
                + " " + enemy->query_possessive() + " face contorted in a" +
                " grotesque mask of death.\n");
            enemy->catch_msg(QCTNAME(enemy) + " decapitates you with " +
                enemy->query_possessive() + " heavy voulge! Your last" +
                " feeling is of your head spinning round and round through" +
                " the air.\n");
            wielder->tell_watcher(QCTNAME(wielder) + " cleanly decapitates " +
                QTNAME(enemy) + " with " + wielder->query_possessive() +
                " heavy voulge, causing " + QTNAME(enemy) + "'s head" +
                " to fall to the ground, rolling around a few times" +
                " before becoming still, " + enemy->query_possessive() +
                " face contorted in a grotesque mask of death.\n",enemy);

            enemy->set_hp(0);
            enemy->do_die(wielder);
            ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
            return 1;
        }
        else
        {
        ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
        return 0;
        }
    }
    else
    {
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    return 0;
    }
}

mixed
wield(object ob)
{
    wielder = TP;

    wielder->add_prop(LIVE_I_QUICKNESS, 
        (int)wielder->query_prop(LIVE_I_QUICKNESS) -80);
    wielder->catch_tell("You grasp the heavy voulge in your hands," +
        " eager to test its razor-sharp blade against soft skin.\n");
    tell_room(environment(wielder), QCTNAME(wielder) + " grasps" +
        " the heavy voulge in his hands.\n", wielder);

    return 1;
}

mixed
unwield(object ob)
{
    wielder = query_wielded();

    wielder->add_prop(LIVE_I_QUICKNESS, 
        (int)wielder->query_prop(LIVE_I_QUICKNESS) +80);
    wielder->catch_tell("You let go of the heavy voulge.\n");
    tell_room(environment(wielder), QCTNAME(wielder) + " lets go" +
        " of the heavy voulge.\n", wielder);

    return 1;
}

