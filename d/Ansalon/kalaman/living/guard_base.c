/*
 * This was originally a .h file which was included in all Kalaman guards.
 *
 * That's not a very nice coding practice so it's been turned into a base file.
 *
 * Cotillion
 */
#include "/d/Ansalon/kalaman/local.h"
#include "/d/Ansalon/common/defs.h"

#include <const.h>
#include <macros.h>
#include <wa_types.h>

inherit AM_FILE
inherit AUTO_TEAM
inherit "/d/Krynn/std/equip";

/* Only do 1 greeting ever 15 seconds */
static int greet_time;
#define GREET_INTERVAL 15

/* Mask this */
public void create_guard()
{
    set_race_name("human");

    set_adj(({ "strangely", "undescript" }));
}

void
create_krynn_monster()
{
    set_name("guard");
    set_race_name("human");
    
    set_pick_up_team(({"guard"}));
    set_max_team_size_auto_join(6);
    
    create_guard();
    
}

public void
action_greet(object target)
{
    if (!objectp(target) || environment(target) != environment())
        return;
    
    if (!CAN_SEE_IN_ROOM(this_object()) || !CAN_SEE(this_object(), target))
        return;

    /* Swordmasters are honoured */
    if (P("ansalon_sword_object", target) && !random(10))
    {

        if (target->query_alignment() < 0 || target->query_attack())
        {
            command("say Be wary of this one, " +HE(target)+
                " wears the insignia of " +
                "the crimson kestrel!");
            return;
        }
        
        if (target->query_gender() == G_FEMALE)
        {
            command("say She wears the insignia of the crimson kestrel!");
            command("say I swear, I have never seen anyone so fair wearing it.");
        }
        else
        {
            command("say to " + OB_NAME(target) + " Greetings " +
                "swordsmaster! Welcome to Kalaman!");
        }
        
        command("bow " + OB_NAME(target));
    }

    /* The guards like Knights */
    if (!random(6) && target->query_knight_level())
    {
        switch (target->query_knight_level())
        {
        case 0:
            /* Not a knight */
            break;
            
        case 1:
            /* Black Rose */
            command("shout " + capitalize(target->query_pronoun()) +
                " is of the Black Rose! Slay " + HIM(target) + "!");
            action_attack(target);
            break;
        case 2:
            /* Squire */
            if (random(2))
                command("say to " + OB_NAME(target) + " Greetings squire");
            else
                command("nod at " + OB_NAME(target));
            break;
        default:
            /* Something else, probably full knight */
            if(target->query_knight_sublevel() == 11)
            {
                command("say Greetings " + target->query_knight_subtitle() +
                    "! " +
                    "This is an unexpected visit! Welcome to Kalaman!");
                command("shout Alert Lord Calof! The " +
                    target->query_knight_subtitle() + " has come to Kalaman!");
                command("bow " + target->query_real_name());
                break;
            }
            
            if (target->query_gender() == G_FEMALE)
            {
                command("say to " + OB_NAME(target) +
                    " Greetings milady Knight of Solamnia! Enjoy your stay in " +
                    "Kalaman!");
            }
            else
            {
                command("say to " + OB_NAME(target) +
                    " Greetings sir Knight of Solamnia! Welcome to Kalaman!");
            }
            break;
        }
    }

    /* Neidars are not so well liked */
    if (TP->query_guild_member("Dwarven Warriors of the Neidar Clan") &&
        !random(10))
    {
        if (random(2))
        {
            command("glare . " + OB_NAME(target));
            command("spit");
        } else {
            command("frown . " + OB_NAME(target));
        }
    }

}

void
init_living()
{
    ::init_living();

    init_team_pickup();
    
    if (TP->id("guard"))
        return;
    
    if ((time() - greet_time) > GREET_INTERVAL)
    {
        greet_time = time();
        set_alarm(rnd() * 3.0, 0.0, &action_greet(TP));
    }
}
