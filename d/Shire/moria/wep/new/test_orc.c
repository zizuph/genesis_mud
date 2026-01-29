/*
 *
 *
 * Znagsnuf
 *
 *
 */
inherit "/std/monster";

#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>

#define BALROG_ROOM "/d/Shire/moria/wep/new/lair6_balrog"
// How many kills is needed to wake the Balrog.
#define awake_balrog 10

/*
 * Function name: create_monster()
 * Description  : Constructor, redefine this to configure your monster
 */
void create_monster()
{
    seteuid(getuid());

    set_race_name("orc");
    set_name("orc");
    add_name("_moria__orc_npc");
    add_name("test");

    set_adj("test");
    set_adj("testing");
    add_adj("orc");

    set_short("black hairy orc");

    set_long("This black hairy spider is no larger than a tooth. "
            + "She's rushing in seemingly random directions. Her "
            + "face is covered with eight eyes shining like blackened "
            + "pin heads, and her mandibles are making a clicking sound.\n");

    add_prop(CONT_I_WEIGHT, 1100);
    add_prop(CONT_I_HEIGHT, 10);

    default_config_creature(30 + random(15));

    add_prop(LIVE_I_SEE_DARK,      1);
    add_prop(LIVE_I_NEVERKNOWN,    1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

}

/*
* Function name: do_die()
* Description  : This is called when the npc is slain.
*/
public void
do_die(object killer)
{
    int k;

    // With each orc killed inside of Moria, the higher the chance of summoning
    // the Balrog.
    if(wildmatch("/d/Shire/moria/*", file_name(environment(this_object()))))
    {
        k = (BALROG_ROOM)->query_balrog_spawn() + 1;
        (BALROG_ROOM)->set_balrog_spawn(k);

        if (k > awake_balrog)
            (BALROG_ROOM)->add_balrog();
    }
       
    ::do_die(killer);
}