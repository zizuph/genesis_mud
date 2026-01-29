/* embrace_death_sh.c created by Shiva@Genesis
 * This object handles most of the creation of a vampire.
 */

/*
 * This code makes a few assumptions about the workings
 * of the death sequence.  Should the death sequence change
 * this should be updated accordingly.
 */
/*
 * Louie 2006 - Moved the shadowing of the vampire to the embrace_room
 *       object to fix a shadowing bug.
 *
 * Lucius 2008:  Changed Sire penalty to be temporary instead.
 */
inherit "/std/shadow";
inherit "/cmd/std/command_driver";

#include "../guild.h"
#include "/d/Genesis/room/death/death.h"
#include <macros.h>
#include <ss_types.h>

#define DEBUG_WHO find_player("louie")
#define DEBUG_ON

#define KEEP_GOING(biter, bitten) \
    (biter && bitten && interactive(biter) && interactive(bitten) && \
    (environment(biter) == environment(bitten)))
                                    
#include "/d/Emerald/sys/debug.h"

static int alarm1, alarm2, offset, fail;
static object return_room, bitten, biter_paralysis, bitten_paralysis;
static mixed biter;
static string coven;

void response(int answer, object respondant, object asker);
static void continue1();
static void continue2();
static void continue3();
static void continue4();
static void continue5();
static void continue6();
static void continue7();

void log_embrace(string str)
{
    setuid();
    seteuid(getuid());

    write_file(VAMP_LOG_DIR + "embrace.log", 
        (objectp(biter) ? biter->query_real_name() : biter) + " -> " +
        bitten->query_real_name() + " " + (strlen(str) ? str + " " : "") +
        ctime(time()) + "\n");
}

void clean_up()
{
    if (bitten_paralysis)
    {
        bitten_paralysis->remove_object();
    }
  
    if (biter_paralysis)
    {
        biter_paralysis->remove_object();
    }
}

void remove_object()
{
    clean_up();
    ::remove_object();
}

void remove_shadow()
{
    clean_up();
  
    if (shadow_who)
    {
        shadow_who->remove_autoshadow(this_object());
    }
  
    ::remove_shadow();
}

void remove_embrace_sh()
{
    remove_shadow();
}

void autoload_shadow(string arg)
{
    if (!strlen(arg) || (sscanf(arg, "%s,%d,%d,%s", biter, offset, fail, coven) != 4))
    {
        remove_embrace_sh();
        return;
    }
}

public void
start_player()
{
    shadow_who->start_player();

    if (!alarm1)
    {    
    	bitten = shadow_who;
    	set_alarm(0.0, 0.0, continue5);
    }
}

/* Function name: response
 * Description:   This is called from a yes_no object once the
 *                target is asked if he/she wishes to become a
 *                vampire.  If the response is "yes", the vampire
 *                creation sequence begins.
 * Arguments:     int answer -  1 "yes"
 *                              0 "no"
 *                             -1 no answer
 */
void response(int answer, object respondant, object asker)
{
    if (!KEEP_GOING(asker, respondant))
    {
        remove_embrace_sh();
        return;
    }
  
    if (answer < 0)
    {
        asker->catch_tell(respondant->query_The_name(asker) + " failed to " +
            "respond.\n");
        remove_embrace_sh();
        return;
    }
  
    if (answer == 0)
    {
        asker->catch_tell(respondant->query_The_name(asker) + " declined your " +
            "offer.\n");
        remove_embrace_sh();
        return;
    }
  
    bitten = respondant;
    biter = asker;
    
    coven = biter->query_vamp_coven();
  
    if (IS_WIZ(bitten))
    {
        bitten->catch_tell("\nThis wasn't meant for wizards...we'll have " +
            "to see how well it works.\n");
    }
  
    set_this_player(bitten);
    actor("\nYou bend your head to the side, exposing your " +
        "neck for", ({ biter }), ".");
    biter->catch_tell("\n");
    allbb(" bends " + POS(bitten) + " head to the side, exposing " +
        POS(bitten) + " neck.");
  
    alarm1 = set_alarm(2.0, 0.0, continue1);
}

/* Function name: continue1
 * Description:   Part one of the vampire creation sequence.
 *                Sire and new vampire are paralyzed.
 *                New vampire is drained of blood.
 *                New vampire is paralyzed; hps, mana, fatigue set to 0
 */
static void continue1()
{
    if (!KEEP_GOING(biter, bitten))
    {
        remove_embrace_sh();
        return;
    }
  
    if (!IS_WIZ(biter) && 
        (biter_paralysis = clone_object(VAMP_OBJ_DIR + "biter_paralysis")))
    {
        biter_paralysis->move(biter, 1);
    }
  
    if (!IS_WIZ(bitten) &&
        (bitten_paralysis = clone_object(VAMP_OBJ_DIR + "bitten_paralysis")))
    {
        bitten_paralysis->move(bitten, 1);
    }
  
    biter->catch_tell("\nYou grasp " + bitten->query_the_name(biter) +
        " gently, supporting " + OBJ(bitten) + " as you quickly " +
        "drain " + OBJ(bitten) + " to the brink of death.\n");
    bitten->catch_tell("\n" + biter->query_The_name(bitten) + " grasps you " +
        "gently; you feel a rush of ecstacy as " + POS(biter) +
        " fangs pierce your skin, and " + PRO(biter) + " drains " +
        "you to the brink of death.\n");
  
    bitten->heal_hp(-(bitten->query_hp()));
    bitten->set_mana(0);
    bitten->set_fatigue(0);
  
    alarm1 = set_alarm(4.0, 0.0, continue2);
}

/* Function name: continue2
 * Description:   Part two of the vampire creation sequence.
 *                New vampire drinks the blood of the sire.
 *                Sire is drained of hps.
 */
static void continue2()
{
    if (!KEEP_GOING(biter, bitten))
    {
        remove_embrace_sh();
        return;
    }
  
    set_this_player(biter);
    biter->catch_tell("\n");
    actor("You slash at your own neck with your claws and press", 
        ({ bitten }) ,"'s lips to the bleeding wound.\nWaves of pain " +
        "rip through your body as " + PRO(bitten) + " greedily " +
        "swallows down the blood streaming from the deep cut; " + 
        PRO(bitten) + " gasps and moans from fatigue and delirium " +
        "as he sucks at the gash.");
    bitten->catch_tell("\n");
    target(" slashes at " + POS(biter) + " own neck with " + POS(biter) + 
        " claws and presses your lips to the bleeding wound.  Without " +
        "a thought, you greedily drink down the blood, which is like " +
        "nothing you have experienced before; you feel each drop flow " +
        "down your throat, instantly diffusing through the rest of your " +
        "body like energy racing through your flesh.", ({ bitten }));
    all2actbb(" slashes at " + POS(biter) + " own neck with " + POS(biter) +
        " claws and presses", ({ bitten }),  "'s lips to the bleeding " +
        "wound.");
  
    alarm2 = set_alarm(1.0, 1.0, &biter->heal_hp(-500));
    alarm1 = set_alarm(5.0, 0.0, continue3);
}

/* Function name: continue3
 * Description:   Part three of the vampire creation sequence
 *                Sire releases new vampire.
 *                Sire is permanently weakened.
 *                Sire is released from paralysis effects.
 *                Creation process cannot be aborted after this point.
 */
void continue3()
{
    int t;
  
    remove_alarm(alarm2);
  
    if (!KEEP_GOING(biter, bitten))
    {
        DEBUG("HERE!\n");
        remove_embrace_sh();
        return;
    }
  
    biter->heal_hp(-(biter->query_hp()));
    if ((t = biter->query_max_thirst() - 20) > biter->query_thirst())
    {
        biter->set_thirst(t);
    }
  
    setuid();
    seteuid(getuid());
  
    offset = biter->query_embrace_offset();
    
    fail = !random(100 + ((offset < 0) ? offset * 2 : offset / 2)); 
    if (this_player()->query_wiz_level())
    {
        fail = 0;
    }
  
    MANAGER->set_tmp_power_offset(biter,
        MANAGER->query_tmp_power_offset(biter) - 7);
    biter->update_power_offset();
  
    MANAGER->set_last_embrace_time(biter, time());
  
    biter->catch_tell("\nThe pain overwhelms you, and you push " +
        bitten->query_the_name(biter) + " away.\n" + 
        capitalize(PRO(bitten)) + " falls to the ground, paralyzed.\n\n");
    bitten->catch_tell("\n" + biter->query_The_name(bitten) + 
        " pushes you away, and you feel your mind and body " +
        "paralyzed instantly.\n\n");
  
    if (biter_paralysis)
    { 
        biter_paralysis->remove_object();
    }
  
    bitten->add_autoshadow(MASTER + ":" + biter->query_real_name() + "," +
        offset + "," + fail + "," + coven);
  
    log_embrace("");
  
    alarm1 = set_alarm(3.0, 0.0, continue4);
}

/* Function name: continue4
 * Description:   Part four of the vampire creation sequence.
 *                New vampire released from paralysis.
 */
static void continue4()
{
    if (bitten_paralysis)
    {
        bitten_paralysis->remove_object();
    }
  
    /* note the new vampire's current environment so that he/she
     * can be returned here  
     */
    return_room = environment(bitten);
  
    if (!shadow_me(bitten))
    {
        remove_embrace_sh();
    }
  
    continue5();
}

/* Function name: continue5
 * Description:   Part five of the vampire creation sequence
 *                New vampire dies.
 */
static void continue5()
{
    /* This bit relies on there being a short delay between the
     * addition of the death_mark and the start of the death
     * routine (start_death() in the death_mark object).  It
     * is only important, though, if the player had logged out
     * during the death sequence and is now reentering the game.
     */
  
    /* We don't want to get the short version of the death sequence */
    DEATH_ROOM->set_deaths(bitten->query_real_name(), 0);
  
    /* Check to see if the new vampire is already dead;
     * if not, kill him/her.
     */
    if (!bitten->query_ghost())
    {  
        bitten->heal_hp(-(bitten->query_hp()));
        bitten->do_die((objectp(biter) ? biter : 0));  
    }
  
    alarm1 = set_alarm(0.5, 0.0, continue6);
}

/* Function name: continue6
 * Description:   Part six of the vampire creation sequence.
 *                The new vampire has entered the death sequence.
 *                Test to see if transformation into a vampire fails.
 */
void continue6()
{
    // make sure that the death sequence is started. 
    if (!present(DEATH_MARK_NAME, bitten))
    {
        remove_embrace_sh();
        return;
    }
  
    bitten->catch_tell(
        "\nYour soul begins to slip away, but you sense something " +
        "within you fighting against death's powerful grip...racing " +
        "against mortality.\n\n");
  
    /* There is a small chance that the process will fail.
     * In that case, the embraced player simply dies without
     * becoming a vampire.
     */
    if (fail)
    {  
        DEBUG("Embrace failed!");
        //vamp_log("failed_embrace");
        log_embrace("FAILED (offset: " + offset + ")");
        remove_embrace_sh();
        return;
    }
  
    alarm1 = set_alarm(30.0, 0.0, continue7);
} 

/* Function name: continue7
 * Description:   Part seven of the vampire creation sequence.
 *                New vampire is removed from the death sequence,
 *                reincarnated, and officially becomes a vampire.
 */
static void continue7()
{
    object sh, death_mark, corpse;
  
    if ((!bitten && !(bitten = shadow_who)) || (!bitten->query_ghost() &&
        !IS_WIZ(bitten)))
    {
        remove_object();
        return;
    }
  
    bitten->remove_ghost(1);
  
    
    if (interactive(bitten))
    {  
        bitten->move_living("M", (return_room ? return_room :
            bitten->query_default_start_location()), 1, 1);
    }
  
    while (death_mark = present(DEATH_MARK_NAME, bitten))
    {
        death_mark->remove_object();
    }
  
    if (corpse = present("corpse of " + lower_case(bitten->query_name()),
        return_room))
    {
        all_inventory(corpse)->move(bitten, 1);
        corpse->remove_object();
    }
  
    set_this_player(bitten);
    write(
        "\nYour eyes flick open suddenly, focusing instantly.\n" +
        "Looking around, you realize that you are somehow alive, or at " +
        "least not dead.\nYou behold your surroundings...marvelling at " +
        "the strange clarity of each minute detail.\nStrange and intense " +
        "sensations wash over you, their power overwhelming and dimming " +
        "the memory of every moment before now.\nAt last you rise to your " +
        "feet, feeling a new power flowing through your body--the power " +
        "of the immortal blood of a vampire.\n\n");
    allbb(" suddenly opens " + POS(bitten) + " eyes and pulls " +
        OBJ(bitten) + "self to " + POS(bitten) + " feet.");
  
    setuid();
    seteuid(getuid());

    //The actual embrace takes place in the embrace_room object, on
    //a tiny delay.
    EMBRACE_ROOM->make_new_vamp_delayed(bitten, biter, offset, coven);

    log_embrace("COMPLETED (offset: " + offset + ")");
  
    remove_embrace_sh();
}

/* Function name: reincarnate
 * Description:   Normally this prepares the player to choose a new
 *                body.  We disable that here, though.
 */
void reincarnate() {}
