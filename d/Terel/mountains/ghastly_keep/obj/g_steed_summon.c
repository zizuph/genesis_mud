/*
 * /d/Terel/mountains/ghastly_keep/obj/g_steed_summon.c
 *
 *  Ghastly skeletal skull.
 *
 *  Znafsnuf
 *
 * - Language tweak complete (Gorboth)
 */

inherit "/std/object";

#include "defs.h";
#include <stdproperties.h>
#include <macros.h>

int do_lift(string str);
int can_summon;

void
create_object()
{
    set_name("skull");
    add_name("_ghastly_steed_summon");
    set_adj("ghastly");
    add_adj("skeletal");

    set_short("ghastly skeletal skull");

    set_long("This skeleton skull looks fresh. In some places there "
            + "is a pink sheen where flesh newly and inexpertly removed "
            + "has been torn away. There are tool marks gauged into recently "
            + "living bone and a round hole in the skull. At the rear the "
            + "head has been cleaved open with a sharp knife and it is now "
            + "hollow.\n"
            + "You contemplating on lifting this skeletal skull towards the "
            + "air. @@see_skull@@\n");

    add_prop(OBJ_I_VALUE, 2550);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);

    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));

    // Only possible with one summon.
    can_summon = 0;

    add_prop(MAGIC_AM_ID_INFO, ({
        "You sense a restless spirit trapped inside this " + TO->short() + "."
        + "\n", 20,
        "This " +TO->short()+ " has been running tireless around in Terel "
        + "for many moons.\n", 50,
        "Only the brave might harness the powers trapped with in this "
        + "skull.\n", 70 }));
    
    add_prop(OBJ_S_WIZINFO, "This " +TO->short()+ " is used for summoning the "
                           + "ghastly skeletal charger. Who can run tireless "
                           + "around in Terel.\n");    

}

/*
 * Function name: see_skull()
 * Description  : See if the horse is still inside the skull
 */
public string
see_skull()
{

    if (!can_summon)
    {
        return "\nYou can sense a restless spirit trapped inside this "
              + "skull";
    }

    return "";
}

void
init()
{
    ::init();
    add_action(do_lift, "lift");
}

/*
 * Function name: do_lift()
 * Description  : Summon the horse trapped inside this skull.
 */
int do_lift(string str)
{

    object steed, summoner;

    if (!strlen(str))
    {
        notify_fail("Lift what?\n");
        return 0;
    }

    notify_fail("Lift what?\n");
    if (!parse_command(str, ({}), "[the] [ghastly] [skeletal] 'skull'"))
        return 0; 
   
    if(!can_summon)
    {

        if (ENV(TP)->query_prop(ROOM_I_INSIDE))
        {
            write("You cannot summon this creature indoors.\n");
            return 1;
        }
        else
        {   

            seteuid(getuid(TO));

            summoner = TP;

            // Preparing the steed.
            steed = clone_object(GKEEP_OBJ + "g_skeletal_charger");

            // Moving it to the room of the summoner.
            steed -> move_living("M", ENV(TP) , 0, 0);

            // Setting an owner, only one can mount this.
            steed -> set_ghastly_owner(summoner->query_name());

            // Div. desc.
            write("You lift the " +short(TO)+ " high into the air, signaling "
                 + "for someone.\n");
            say(QCTNAME(TP) + " lifts the " +short(TO)+ " high into the air, "
                + "signaling for someone.\n");

            summoner->catch_msg("\nIn the distance you hear a trampling "
                                + "sound getting closer, and closer. And "
                                + "suddenly a " +steed->short()+ " is standing "
                                + "proud and majestic before you.\n");

            // Notify the room.
            tell_room(ENV(TP), "\nThe " +steed->short()+ " summoned by "
                     +QCTNAME(summoner)+ " arrives with a dashing speed."
                     + "\n\n", summoner);

            // Mount it
            summoner->command("$mount _ghastly_skeletal_steed");

            // Can only be summoned 1 time.
            can_summon = 1;

            return 1;
        }
        return 1;
    }

    write("You lift the " +short(TO)+ " high into the air, but nothing "
        + "happens.\n");
    say(QCTNAME(TP) + " lifts the " +short(TO)+ " high into the air, but "
        + "nothing happens.\n");

    return 1;
}