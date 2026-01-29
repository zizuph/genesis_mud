/*
 *  /d/Gondor/clubs/nisse/obj/feather.c
 *
 *  The club item of Nisse Ohtar, the fighters club for females.
 *
 *  Deagol, February 2003
 *  ?, 2003/11/10  Last update?
 *  Lavellan, 2022/02/28  Fixed "remove" messages
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object.c";
inherit "/lib/wearable_item";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

/*
 *  Global variables
 */
string	birthmark_colour = TP->query_nisse_rank();

/*
 *  Prototypes
 */
void	add_soul();
void	remove_soul();

void
create_object()
{
    set_name("feather");
    add_name(NISSE_FEATHER_ID);
    set_adj(({birthmark_colour, "hawk"}));
    set_short(birthmark_colour + " hawk feather");
    set_long("You look closer at the @@short@@. It is a typical " +
             "flight feather with a perfect contour and a branching " +
             "structure. It reminds you of your membership in the " +
             "Nisse Ohtar. Type \"help nisse\" to get more informations.\n");
    
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_M_NO_DROP, "The hawk feather cannot be dropped.\n");
    add_prop(OBJ_M_NO_GIVE, "You cannot give your feather away, it is " +
             "a club item.\n");
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_MAGIC, "whatever");

    setuid();
    seteuid(getuid());

    config_wearable_item(A_HEAD, 1, 3);
    set_wf(this_object());
}

/*
 *  Function name: enter_env
 *  Description  : When we enter an interactive environment, add a subloc to
 *                 indicate that the person is writing something.
 *  Arguments    : object to - the object we are entering.
 *                 object from - the object we come from.
 */
void
enter_env(object dest, object from)
{
    ::enter_env(dest, from);
    if (!birthmark_colour && objectp(dest))
    {
        birthmark_colour = dest->query_nisse_rank();
        create_object();
    }
}

/*
 *  Function name: leave_env
 *  Description  : When you inherit /lib/holdable_item.c you MUST also define
 *                 the function leave_env() as copy of this function. It MUST
 *                 make the call to holdable_item_leave_env(from, to) as well.
 *                 If you omit this, then the item will not be automatically
 *                 released when the player drops it, for instance.
 *  Arguments    : object from - the environment we are leaving.
 *                 object to   - the environment we are entering.
 */
void
leave_env(object dest, object from)
{
    ::leave_env(dest, from);
    
    wearable_item_leave_env(from, dest);
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

/*
 *  Function name: wear
 *  Description  : Gives a message when a player wears the feather.
 *  Returns      : always 1
 */
int
wear()
{
    write("You braid your " + short() + " into your hair, making sure it " +
          "is tightly secured.\n");
    say(QCTNAME(TP) + " braids a single " + short() + " into " +
        POSSESSIVE(TP) + " hair. It falls softly against " + POSSESSIVE(TP) +
        " hair.\n");
    return 1;
}

/*
 *  Function name: remove
 *  Description  : Gives a message when a player removes the feather.
 *  Returns      : always 1
 */
int
remove()
{
    //This makes it appear in /lplog or to random players (sometimes.. when?)
    //write("You carefully unwind your " + short() + " from your hair and " +
    //      "store it in your belongings.\n");
    //say(QCTNAME(TP) + " carefully unwinds " + POSSESSIVE(TP) + " " + short() +
    //    " and stores it in " + POSSESSIVE(TP) + " belongings.\n");
    wearer->catch_tell("You carefully unwind your " + short() +
        " from your hair and store it in your belongings.\n");
    tell_room(environment(wearer), QCTNAME(wearer) + " carefully unwinds " +
        POSSESSIVE(wearer) + " " + short() + " and stores it in " +
        POSSESSIVE(wearer) + " belongings.\n", wearer);
    return 1;
}

/*
 *  Function name: add_soul
 *  Description  : Original intention was that the feather should add the
 *                 command soul when enters an inventory. So this routine
 *                 is a bit obsolete.
 */
void
add_soul()
{
    object player = ENV(TO);
    
    if (!interactive(player))
    {
        remove_object();
    }
    
    player->add_cmdsoul(NISSE_SOUL);
    player->update_hooks();
}

/* 
 *  Function name: remove_soul
 *  Description  : Original intention was that the feather should remove the
 *                 command soul when leaves an inventory. So this routine
 *                 is a bit obsolete.
 */
void
remove_soul()
{
    object player = ENV(TO);
    
    player->remove_cmdsoul(NISSE_SOUL);
    player->update_hooks();
}

/*
 *  Function name: query_recover
 *  Description  : This function is here to prevent the feather from 
 *                 cloning twice into the nisse inventory.
 *  Returns      : always 0
 */
string
query_recover()
{
    return 0;
}

void
init()
{
    ::init();
}
