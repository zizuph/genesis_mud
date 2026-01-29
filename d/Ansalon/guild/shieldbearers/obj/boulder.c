/*
 * File name  : boulder.c
 * Description: The large granite boulder, on which Shieldbearers train
 *              their shield slam, charging at it ;)
 *
 * Blizzard, 29.09.2003
 *
 */

#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include "/d/Ansalon/common/defs.h"

#define  BOULDER_CHARGE_PROP  "_charging_at_the_boulder"
#define  GUILD_DIR            "/d/Ansalon/guild/shieldbearers/"

public string  LongDesc();
public int     DoCharge(string str);
public void    ChargeMessages(object who);
public void    ChargeResult(object who);
public int     query_cracks();

public int     charge_alarm_id_1, charge_alarm_id_2;
public int     cracks = 0;
public object  trainer;

public void
create_object()
{
    set_name("_neidar_boulder_");
    add_name("boulder");
    set_adj("large");
    add_adj("granite");
    set_short("large granite boulder");
    set_long(LongDesc);
    
    add_prop(OBJ_M_NO_GET, "The " + short() +  
        " is firmly set in the ground.\n");
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_WEIGHT, 400000);
    add_prop(OBJ_I_VOLUME, 350000);
}

public string
LongDesc()
{
    string str;
    
    str = "This is a massive piece of hard grey rock. It is firmly " +
        "set in the ground and seems to be impossible to move.";
    
    switch ( query_cracks() )
    {
        case 0:
            str += "";
        break;
        case 1..19:
            str += " There are a few small cracks on its surface.";
        break;
        case 20..49:
            str += " There are several cracks on its surface.";
        break;
        case 50..140:
            str += " Its surface is heavily cracked.";
        break;
        default:
            str += " It is so heavily cracked that it may collapse " +
                "any moment.";
        break;
    }
    
    str += " If you have a shield you may try to charge at it.\n";

    return str;

}

public int
query_trainer()
{
    if ( trainer = present("gorrthaur", E(TO)) )
        return 1;
    else
        return 0;
}

public void
init()
{
    ::init();
    
    add_action(DoCharge, "charge");
    add_action(DoCharge, "rush");
}

public int
query_cracks()
{
    return cracks;
}

public void
add_cracks(int cr)
{
    cracks += cr;
}

public int
check_boulder_condition()
{
    object rubble;
    
    if ( cracks > (140 + random(40)) )
    {
        tell_room(E(TO), "The " + short() + " staggers for a while and " +
            "then suddenly crumbles, leaving a heap of rumbble.\n");
        
        setuid();
        seteuid(getuid());
         
        rubble = clone_object(GUILD_DIR + "obj/rubble")->move(E(TO), 1);     
        
        if ( query_trainer() )
        {
            trainer->command("say Damn ye! I will have to find a new one!");
            trainer->command("curse");
        }
        
        TO->remove_object();
        
        return 1;
    }
    
    return 0;
}
 
public void
ChargeMessages(object who)
{
    int success, num = random(6);
    
    success = who->resolve_task(TASK_ROUTINE + 150, ({ TS_INT, TS_DIS }));
    
    if ( !present(who, E(TO)) )
    {
        who->catch_msg("You scratch your head, wondering where did " +
            "that " + short() + " go.\n");
        remove_alarm(charge_alarm_id_2);
        return;
    }
    
    success -= random(30);
    
    if ( success > 70 )
    {
        who->catch_msg("\nYou legs pump hard as you approach the " + short() +
            "... But suddenly, you realize it is not too smart to " +
            "continue that! You slow down.\n\n");
        tell_room(E(who), "\n" + QCTNAME(who) + "'s legs pump hard as " +
            HE(who) + " approaches the " + short() + "... " +
            "But suddenly " + HE(who) + " slows down!\n\n", who);
        
        who->remove_prop(BOULDER_CHARGE_PROP);     
        remove_alarm(charge_alarm_id_2);
 
        if ( query_trainer() )
        {
            switch (num)
            {
            case 0:
                trainer->command("say Ha ha, smart move!");
            break;
            case 1:
                trainer->command("giggle");
            break;
            case 2:
                trainer->command("say Com' on! Dont be a coward!");
            break;
            case 3:
                trainer->command("say Coward! Ye afraid of the rock!?");
            break;
            case 4:
                trainer->command("say Heh. Anyone else wanna try?");
            break;
            case 5:
                trainer->command("smirk");
            break;
            }
        }
        
        return;
    }
    
    who->catch_msg("\nYour legs pump hard as you approach the " +
        short() + "...\n\n");
    tell_room(E(who), "\n" + QCTNAME(who) + "'s legs pump hard as " +
        HE(who) + " approaches the " + short() + "...\n\n", who);
    
    if ( !query_trainer() )
        return;
        
    switch (num)
    {
    case 0:
        trainer->command("say Chaaarge!");
    break;
    case 1:
        trainer->command("say Ye! Keep yer head low!");
    break;
    case 2:
        trainer->command("tingle");
    break;
    case 3:
        trainer->command("say Go! Ye can do it!");
    break;
    case 4:
        trainer->command("say Yea! Be ready fer contact!");
        trainer->command("giggle");
    break;
    case 5:
        trainer->command("say Try to imagine it's an ogre!");
    break;
    }
    
}

public void
ChargeResult(object who)
{
    int success, skill, num = random(5);
    
    success = who->resolve_task(TASK_DIFFICULT, ({ TS_INT, TS_DIS }));
   
    if ( !present(who, E(TO)) )
    {
        who->catch_msg("You scratch your head, wondering where did " +
            "that " + short() + " go.\n");
        return;
    }
    
    if ( (who->query_armour(W_RIGHT)->query_at() != A_SHIELD ) &&
        ( who->query_armour(W_LEFT)->query_at() != A_SHIELD ) )
    {
        tell_room(E(who), QCTNAME(who) + " stops suddenly, realizing " +
            "that " + HIS(who) + " shield is gone!\n", who);
        who->catch_msg("You stop when you realize that your shield is gone!\n");
        return;
    }

    if ( who->query_guild_member("Shieldbearers of Iron Delving") )
    {
       /* Shieldslam skill */
        skill = who->query_skill(143014);
        success += 20;
    }
            
    who->remove_prop(BOULDER_CHARGE_PROP);
    
    if ( !random(6) )
    {
        who->catch_msg("In the last moment you manage to stop, " +
            "realizing that confrontation with the " + short() +
            " may not be too healthy.\n");
        tell_room(E(who), "In the last moment " + QTNAME(who) +
            " decides to stop, probably realizing the consequences " +
            "of such confrontation.\n", who);

        if ( query_trainer() )
        {
            switch (num)
            {
            case 0:
                trainer->command("say Ha ha, smart move!");
            break;
            case 1:
                trainer->command("giggle");
            break;
            case 2:
                trainer->command("say Com' on! Dont be a coward!");
            break;
            case 3:
                trainer->command("say Phef! Coward.");
            break;
            case 4:
                trainer->command("gasp");
            break;
            }
        }
        
        return;
    }
       
    if ( who->query_guild_member("Shieldbearers of Iron Delving") )
    {
        switch ( random(skill) )
        {
        case 0..8:
            who->catch_msg("You charge past the " + short() + ", missing " +
                "it totally. You hang in shame.\n");
            tell_room(E(who), QCTNAME(who) + " charges past the " + short() +
                ", missing it totally. " + C(HE(who)) + " hangs in shame.\n", who);
        break;                                        
        case 9..25:
            who->catch_msg("And you hit it with a loud thump! Your feel a " +
                "strong pain in your head and feel a bit dizzy.\n\n");
            tell_room(E(who), "And suddenly " + QTNAME(who) + " hits it with " +
                "a loud thump! " + capitalize(HE(who)) + " bounces off the " +
                "boulder, staggering slightly.\n", who);

            add_cracks(1);
            who->heal_hp(-150);
            check_boulder_condition();
                        
        break;
        case 26..50:
            who->catch_msg("You slow down just before hitting the " +
                short() + " and quickly bring your shield up " +
                "slamming it neatly, leaving a small crack on the " +
                "boulder's surface.\n");
            tell_room(E(who), QCTNAME(who) + " slows down just before " +
                "hitting the " + short() + ", quickly brings " + 
                HIS(who) + " shield up and slams it neatly into the " +
                short() + " leaving a small crack on the surface.\n", who);

            add_cracks(1);
            check_boulder_condition();

        break;
        case 51..75:
            who->catch_msg("You charge into the " + short() + 
                " at full speed, bashing it with your shield. The " +
                "boulder staggers dangerously and a long crack appears " +
                "on its surface.\n");
            tell_room(E(who), QCTNAME(who) + " charges into the " +
                short() + " at full speed, bashing it with " + HIS(who) +
                " shield. The boulder staggers dangerously and a long " +
                "crack appears on its surface.\n", who);
            
            add_cracks(2);
            check_boulder_condition();
                        
        break;
        default:
            who->catch_msg("As you bash the " + short() + " mightily, it " +
                "trembles for a moment and you are sure you managed to " +
                "push it back a few inches. Or maybe it is just your " +
                "imagination.\n");
            tell_room(E(who), "As " + QTNAME(who) + " bashes the " +
                short() + " mightily, it trembles for a moment and " +
                "seems to be pushed back a few inches.\n", who);
            add_cracks(2);
            check_boulder_condition();
        break;
        }
       
        if ( query_trainer() )
        {
            switch (num)
            {
            case 0:
                trainer->command("say Not bad! Ye almost killed it!");
                trainer->command("giggle");
            break;
            case 1:
                trainer->command("say Neat!");
                trainer->command("say Almost like I show'd ye!");
            break;
            case 2:
                trainer->command("say Soon ye will smash that rock with " +
                    "one hit!");
                trainer->command("grin");
            break;
            case 3:
                trainer->command("jump");
                trainer->command("say That was good!");
            break;
            case 4:
                trainer->command("say If it was an ogre, ye would kill it!");
            break;
            }
        }

        if ( who->query_hp() <= 0 )
        {
            who->catch_msg("What a pain. You collapse to the ground.\n");
            tell_room(E(TO), QCTNAME(who) + " collapses to the ground.\n", who);
        
            who->do_die(TO);
        
            if ( query_trainer() )
                trainer->command("say Ooops.");
            
            return;
        }    
        
        return;

    }
          
    switch (success)
    {
    case 0..10:
        who->catch_msg("You run straight into the " + short() +
            ", but then suddenly you panic and turn back, leaving " +
            "the boulder behind you.\n");
        tell_room(E(who), QCTNAME(who) + " runs straight into the " +
            short() + ", but suddenly " + HE(who) + " panics and turns " +
            "back, leaving the boulder behind " + HIM(who) + ".\n", who);
    break;
    case 11..20:
        who->catch_msg("You charge past the " + short() + ", missing " +
            "it totally. You hang in shame.\n");
        tell_room(E(who), QCTNAME(who) + " charges past the " + short() +
            ", missing it totally. " + C(HE(who)) + " hangs in shame.\n", who);
    break;
    case 21..40:
        who->catch_msg("And you hit it with a loud thump! Your feel a " +
            "strong pain in your head and feel a bit dizzy.\n\n");
        tell_room(E(who), "And suddenly " + QTNAME(who) + " hits it with " +
            "a loud thump! " + capitalize(HE(who)) + " bounces off the " +
            "boulder, staggering slightly.\n", who);

        add_cracks(1);
        who->heal_hp(-150);
        check_boulder_condition();
        
    break;
    case 41..65:
        who->catch_msg("You close your eyes and run straight into the " +
            short() + " expecting the worst! Suddenly you feel a " +
            "terrible pain in your head. You open your eyes and notice " +
            "a small crack on the boulder's surface.\n");
        tell_room(E(who), QCTNAME(who) + " closes " + HIS(who) + " eyes " +
            "and runs straight into the " + short() + " probably expecting " +
            "the worst. Instead of a shield, " + HE(who) + " hits the " +
            "boulder with " + HIS(who) + " head, leaving a small " +
            "crack on the granite surface, however.\n", who);

        add_cracks(1);
        who->heal_hp(-200);
        check_boulder_condition();
        
    break;
    default:
        who->catch_msg("You slow down a bit just before hitting the " +
            short() + ", and then slam your shield hard into the stone. " +
            "To your surprise it waggles slightly.\n");
        tell_room(E(who), QCTNAME(who) + " slows down a bit just before " +
            "hitting the " + short() + " and then slams " + HIS(who) +
            " shield hard into the stone. " + C(HE(who)) + " seems to " +
            "be surprised when it waggles slightly " +
            "after this hit.\n", who);

        add_cracks(1);
        check_boulder_condition();
        
    break;
    }
       
    if ( query_trainer() )
    {
        switch (num)
        {
        case 0:
            trainer->command("say Not bad! Ye almost killed it!");
            trainer->command("giggle");
        break;
        case 1:
            trainer->command("say Neat!");
            trainer->command("laugh");
        break;
        case 2:
            trainer->command("say Soon ye will smash that rock with one hit!");
            trainer->command("wink");
        break;
        case 3:
            trainer->command("say Ye should train here more!");
        break;
        case 4:
            trainer->command("say Ye have a talent fer that! Keep chargin'.");
        break;
        }
    }
    
    if ( who->query_hp() <= 0 )
    {
        who->catch_msg("What a pain. You collapse to the ground.\n");
        tell_room(E(TO), QCTNAME(who) + " collapses to the ground.\n", who);
        
        who->do_die(TO);
        
        if ( query_trainer() )
            trainer->command("say Ooops.");
            
        return;
    }    
    
}

public int
DoCharge(string str)
{
    object who = TP;
    int    num = random(3);
    
    if ( !strlen(str) || !parse_command(str, ({}),
        "'at' [a] [the] [large] [granite] 'boulder' / 'rock' / 'stone' ")  )
    {
        notify_fail(capitalize(query_verb()) + " at the boulder?\n", 0);
        return 0;
    }
    
    if ( (who->query_armour(W_RIGHT)->query_at() != A_SHIELD ) &&
        ( who->query_armour(W_LEFT)->query_at() != A_SHIELD ) )
    {
        notify_fail("You can not charge without a shield!\n");
        return 0;
    }
    
    if ( who->query_prop(BOULDER_CHARGE_PROP) )
    {
        write("You are already charging at the boulder!\n");
        return 1;
    }
    
    write("You lower your head and with a roar charge at the " + short() +
        ", trying to bash it with your shield.\n");
    tell_room(E(who), QCTNAME(who) + " lowers " + HIS(who) + " head " +
        "and with a roar charges at the " + short() + 
        ", trying to bash it with " + HIS(who) + " shield.\n", who);
        
    TP->add_prop(BOULDER_CHARGE_PROP, 1);
    
    charge_alarm_id_1 = set_alarm(2.0, 0.0, &ChargeMessages(who));
    charge_alarm_id_2 = set_alarm(5.0, 0.0, &ChargeResult(who));
    
    if ( !query_trainer() )
        return 1;
        
    switch (num)
    {
    case 0:
        trainer->command("laugh");
    break;
    case 1:
        trainer->command("say Show 'em, bastards!");
        trainer->command("giggle");
    break;
    case 2:
        trainer->command("say Aim fer the legs!");
        trainer->command("chuckle");
    break;
    } 
   
    return 1;
     
}


