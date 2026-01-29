inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
    set_name("instrument");
    add_name("club");
    set_adj("strange");
    set_adj("string");
    set_short("strange string instrument");
    set_long("A string instrument. No matter how you look" +
        " at it you cant figure out how to play the blasted" +
        " thing. But it somehow you feel it would make a" +
        " decent club.\n");

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,30) + random(20) -10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(30,W_CLUB) + random(50) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);

    set_hit(35);
    set_pen(30);

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);

    set_hands(W_BOTH);

}

int
did_hit(int aid, string hdesc, int phurt,
        object enemy, int dt, int phit, int dam)
{
    object wielder = query_wielded();
    string w,e,b,sound;
    
        if(enemy->query_hp()<=0)
    {
        wielder->catch_msg("The " + short() + " gives off" +
            " a perfect D-minor as it puts a permanent dent in " +
            enemy->query_the_possessive_name(wielder) +
            " head. Now thats music to you!\n");
        wielder->tell_watcher(enemy->query_The_possessive_name(wielder) +
            " " + short() + "gives off a perfect D-minor" +
            " as it puts a permanent dent in " +
            enemy->query_the_possessive_name(wielder) +
            " head. Now thats some brutal music!\n");
        enemy->do_die(wielder);
        return 1;
    }

    switch(phit)
    {
    	
    case -600..-1:
        sound = ("swoooosssssh!");
    break;
    
    case 0..30:
        sound = ("Pling!");
    break;
    
    case 31..80:
        sound = ("Boink!");
    break;
    
    case 81..150:
        sound = ("Sprong!");
    break;

    case 151..250:
        sound = ("KA-BOING!");
    break;

    case 251..499:
        sound = ("SPROING-DING!!");
    break;
    
    default:
        sound = (" SpRiOiOiOiNgh!!!");
    break;

    }

    switch(phurt)
    {
    	
    case -1:
        w = "You swing the " + short() + " at " +
            enemy->query_the_possessive_name(wielder) +
            " " + hdesc + " but miss with a " + sound +
            " Dang!\n";
            
        e = wielder->query_The_name(enemy) +
            " swing " + wielder->query_possessive()+
            " " + short() + " at your " + hdesc +
            " but misses with a " + sound + " Dang!\n";
            
        b = QCTNAME(wielder) + " swings " +
            wielder->query_possessive() + " " + short() +
            " at " + QTPNAME(enemy) + " " + hdesc +
            " but misses with a "  + sound + 
            " Both looked suprised it missed.\n";
    break;
    
    case 0..6:
        w = "You swing the " + short() + " at " +
            enemy->query_the_possessive_name(wielder) +
            " " + hdesc + " and hit with a " + sound +
            " " + capitalize(enemy->query_pronoun()) +
            " looks barely scratched.\n";
            
        e = wielder->query_The_name(enemy) + " swing " +
            wielder->query_possessive()+ " " + short() +
            " at your " + hdesc + " and hits with a " +
            sound + " You feel barely scratched.\n";
            
        b = QCTNAME(wielder) + " swings " +
            wielder->query_possessive() + " " + short() +
            " at " + QTPNAME(enemy) + " " + hdesc +
            " and hits with a "  + sound + "\n";
    break;
    
    case 7..15:
        w = "You swing the " + short() + " at " +
            enemy->query_the_possessive_name(wielder) +
            " " + hdesc + " and hit with a " + sound +
            " " + capitalize(enemy->query_pronoun()) +
            " looks slightly hurt.\n";
            
        e = wielder->query_The_name(enemy) + " swing " +
            wielder->query_possessive()+ " " + short() +
            " at your " + hdesc + " and hits with a " +
            sound + " You feel slightly hurt.\n";
            
        b = QCTNAME(wielder) + " swings " +
            wielder->query_possessive() + " " + short() +
            " at " + QTPNAME(enemy) + " " + hdesc +
            " and hits with a "  + sound + "\n";
    break;
    
    case 16..27:
        w = "You swing the " + short() + " at " +
            enemy->query_the_possessive_name(wielder) +
            " " + hdesc + " and hit with a " + sound +
            " " + capitalize(enemy->query_pronoun()) +
            " looks hurt.\n";
            
        e = wielder->query_The_name(enemy) + " swing " +
            wielder->query_possessive()+ " " + short() +
            " at your " + hdesc + " and hits with a " +
            sound + " You feel hurt.\n";
            
        b = QCTNAME(wielder) + " swings " +
            wielder->query_possessive() + " " + short() +
            " at " + QTPNAME(enemy) + " " + hdesc +
            " and hits with a "  + sound + "\n";
    break;

    case 28.. 42:
        w = "You swing the " + short() + " at " +
            enemy->query_the_possessive_name(wielder) +
            " " + hdesc + " and hit with a " + sound +
            " " + capitalize(enemy->query_pronoun()) +
            " looks badly hurt.\n";
            
        e = wielder->query_The_name(enemy) + " swing " +
            wielder->query_possessive()+ " " + short() +
            " at your " + hdesc + " and hits with a " +
            sound + " You feel badly hurt.\n";
            
        b = QCTNAME(wielder) + " swings " +
            wielder->query_possessive() + " " + short() +
            " at " + QTPNAME(enemy) + " " + hdesc +
            " and hits with a "  + sound + "\n";
    break;

    case 43..60:
        w = "You swing the " + short() + " at " +
            enemy->query_the_possessive_name(wielder) +
            " " + hdesc + " and hit with a " + sound +
            " " + capitalize(enemy->query_pronoun()) +
            " looks severely hurt.\n";
            
        e = wielder->query_The_name(enemy) + " swing " +
            wielder->query_possessive()+ " " + short() +
            " at your " + hdesc + " and hits with a " +
            sound + " You feel severely hurt.\n";
            
        b = QCTNAME(wielder) + " swings " +
            wielder->query_possessive() + " " + short() +
            " at " + QTPNAME(enemy) + " " + hdesc +
            " and hits with a "  + sound + "\n";
    break;
    
    default:
        w = "An extremly loud " + sound +
            " is heard as your " + short() + " crushes into " +
            enemy->query_the_possessive_name(wielder) + " " +
            hdesc + ", sending " + capitalize(enemy->query_pronoun()) +
            " into a near fatal tailspin!\n";
            
        e = "An extremly loud " + sound + " is heard as " +
            wielder->query_the_possessive_name(enemy) + " " +
            short() + " crushes into your " + " " + hdesc +
            ", sending you into a near fatal tailspin!\n";
            
        b = "An extremly loud " + sound + " is heard as " +
            QTPNAME(wielder) + " " + short() + " crushes into " +
            QTPNAME(enemy) + " " + hdesc + ", sending " +
            capitalize(enemy->query_pronoun()) +
            " twirling in circles!\n";
        
    break;

    }

    wielder->catch_msg(w);
    enemy->catch_tell(e);
    wielder->tell_watcher(b, enemy);

    return 1;
}