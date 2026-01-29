/*
 * Developed and made by Arren. 961003
 *
 *    What is this? Olorin, April 1997
 */
inherit "/std/weapon";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("hobbit");
    add_name("hublert");
    add_pname("hobbits");
    set_adj("small");
    set_short("small hobbit"); 
    set_long(
       "A small sulking hobbit with a flat face. He is trying to "
     + "ignore you, standing with his hands in his pockets.\n"
     + "He looks hideous.\n");

    set_default_weapon(7, 7, W_CLUB, W_BLUDGEON, W_ANYH, TO);

    set_likely_corr(0); 
    set_likely_break(20);
    set_likely_dull(20);
    
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 10000);  
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, "You can't sell your friend.\n");
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
        int phit, int dam)
{
    string str;

    if (!dam)
        return 0;

    if (random(3))
        return 0;

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    switch(random(10))
    {
        case 0 :
            str = " says: Ouch!";
            break;
        case 1 :
            str = " says: Put me down!";
            break;
        case 2 :
            str = " says: You give me a headache.";
            break;
        case 3 :
            str = " says: Help! Help!";
            break;
        case 4 :
            str = " says: Ouch! That hurt!";
            break;
        case 5 :
            str = " says: I didn't feel that.";
            break;
        case 6 :
            str = " says: I think I lost a teeth.";
            break;
        case 7 :
            str = " says: Stop that, or I'll beat you to pulp!";
            break;
        case 8 :
            str = "'s face became even more flat.";
            break;
        case 9 :
            str = " flails wildly with his arms.";
            break;
        default :              // error msg
            str = " goes duh.";
            break;
    }
    tell_room(ENV(query_wielded()), "The small hobbit" + str + "\n");
    return 1;
}

public mixed
wield(object wep)
{
    object tp = TP;
    
/*  During debugging
    if (tp->query_race() == "hobbit")
        return "You can't do that to a fellow hobbit.\n";
 */
    tp->catch_msg("You grab the small hobbit by one leg.\n");
    return 1;
}
     
void
enter_env(object dest, object old)
{
    string str;

    if (!living(dest))
    {
        ::enter_env(dest, old);
        return;
    }
    tell_room(ENV(dest), "The small hobbit tries to run away but fails.\n");
    ::enter_env(dest, old);
    set_long(
       "A small sulking hobbit with a flat face. He is trying to "
     + "ignore you, but without any success.\nHe looks hideous.\n");
    switch(random(4))
    {
        case 0 :
            str = "Put me down you oaf!";
            break;
        case 1 :
            str = "Let go of me immediately.";
            break;
        case 2 :
            str = "I don't have to stand this.";
            break;
        case 3 :
            str = "Help! I'm being kidnapped.";
            break;
        default :      // error msg
            str = "something incomprehensible.";
     }
     tell_room(ENV(dest), "The small hobbit says: " + str + "\n");
}

void
leave_env(object old, object dest) 
{
    if (living(dest))
    {
        ::leave_env(old, dest);
        return;
    }
    ::leave_env(old, dest);
    set_long(
       "A small sulking hobbit with a flat face. He is trying to "
     + "ignore you, standing with his hands in his pockets.\n"
     + "He looks hideous.\n");
}

/*
 * Function name: wep_condition_desc
 * Description:   Returns the description of the condition of the weapon
 */
string
wep_condition_desc()
{
    string hand2;

    if (query_prop(OBJ_I_BROKEN))
        return "He is dead.\n";

    switch (dull - repair_dull)
    {
        case 0:
            hand2 = "feeling very well"; break;
        case 1:
            hand2 = "somewhat hurt"; break;
        case 2:
            hand2 = "rather hurt"; break;
        case 3:
            hand2 = "in a bad shape"; break;
        case 4:
        case 5:
            hand2 = "terribly hurt"; break;
        case 6:
        case 7:
        case 8:
            hand2 = "barely alive"; break;
        default:
            hand2 = "at death's door"; break;
    }

    return "He seems to be " + hand2 + ".\n";
}

/*
 * Function name: remove_broken
 * Description:   The weapon got broken
 */
void
remove_broken()
{
    object corpse;

    ::remove_broken();

    corpse = clone_object("/std/corpse");
    corpse->set_name(query_name());
    corpse->change_prop(CONT_I_WEIGHT, query_prop(CONT_I_WEIGHT));
    corpse->change_prop(CONT_I_VOLUME, query_prop(CONT_I_VOLUME));
    corpse->add_prop(CORPSE_S_RACE, "hobbit");
    corpse->add_prop(CONT_I_TRANSP, 1);
    corpse->change_prop(CONT_I_MAX_WEIGHT, query_prop(CONT_I_WEIGHT));
    corpse->change_prop(CONT_I_MAX_VOLUME, query_prop(CONT_I_VOLUME));
    corpse->move(ENV(TO), 1);
    remove_object();
}

int
do_swing(string str)
{
    object tp = TP;

    str = LOW(str);

    if (!strlen(str))
        NFN0("Swing what?");
    if (parse_command(str, ENV(tp), "[the] [small] 'hobbit'"))
    {
        tp->catch_msg("You swing the hobbit around you.\n");
        SAY(" swings the small hobbit around " + OBJECTIVE(tp) + ".");
        tell_room(ENV(tp), "The small hobbit says: Faster! Faster!\n");
        return 1;
    }
    else if (parse_command(str, ENV(tp), "[the] [small] 'hobbit' 'fast'"))
    {
        tp->catch_msg("You swing the hobbit wildly around you.\n");
        SAY(" swings the small hobbit wildly around " + OBJECTIVE(tp) + ".");
        tell_room(ENV(tp), "The small hobbit says: I think I'm going "
         + "to puke.\n");
        return 1;
    }
    NFN0("Swing what?");
}

void
init()
{
    ::init();

    add_action(do_swing, "swing");
}
