/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <state_desc.h>
#include <living_desc.h>
#include <stdproperties.h>

#define STD_SOUL      "/cmd/std/soul_cmd"
#define SOULS         ({"social", "state", "things", "info"})

object npc_link;
string animal_soul;

void   set_player_link(object player, object control);
void   set_animal_soul(string soul);
string query_animal_soul();
void   set_up_player_values();
object query_player_link();

public void
create_creature()
{
    set_tell_active(1);
}

/*
 * Function name: set_player_link
 * Description:   Links a player to the output of the mobile
 * Arguments:     player: Player to link mobile to
 *                control: Object controlling the link
 */
void
set_player_link(object player, object control)
{
    if (!living(player) || npc_link) return;

    control->set_npc(this_object());
    npc_link = control;
    control->move(player);
    set_alarm(1.0, -1.0, "set_up_player_values");
}

/*
 * Function name: set_animal_soul
 * Description:   Sets the soul to use for a particular animal
 * Arguments:     soul: path name of the soul
 */
void
set_animal_soul(string soul)
{
    animal_soul = soul;
}

/*
 * Function name: query_animal_soul
 * Description:   returns the soul in use for this particular animal
 * Returns:       soul: string path name of the soul
 */
string
query_animal_soul()
{
    return animal_soul;
}

/*
 * Description: Return the pointer to the current controller
 */
object
query_player_link() { return npc_link; }

/*
 *  Description: For monster link purposes
 */
void
catch_tell(string str)
{
    if (npc_link) npc_link->link_intext(str);
    ::catch_tell(str);
}

/*
 * Description: set up some values depending on player
 */
void
set_up_player_values()
{
    int i;
    object player;

    if (!npc_link) return;
    player = environment(npc_link);
    if (!living(player)) return;

    set_gender(player->query_gender());
    set_alignment(player->query_alignment());
    remove_cmdsoul(STD_SOUL);
    for (i=0; i<sizeof(SOULS); i++) remove_cmdsoul("/cmd/live/" + SOULS[i]);
    add_cmdsoul(animal_soul);
    for (i=0; i<sizeof(SOULS); i++) add_cmdsoul("/cmd/live/" + SOULS[i]);
    update_hooks();
}

public void
do_die(object killer)
{
    if (query_hp() > 0) return;
    if (npc_link) npc_link->link_monster_died(killer);
    ::do_die(killer);
}

public int
query_met(mixed name)
{
    return 0;
}

public int
query_see_special_msg()
{
    return 1;
}

/*
 * Function name: do_glance
 * Description  : This is the routine describing rooms to livings. It will
 *                print the long or short description of the room, the
 *                possible exits, all visible non-living and living objects
 *                in the room (but not this_object() itself) and then it
 *                will print possible attacks going on. Note that this
 *                function performs a write(), so this_player() will get the
 *                descriptions printed to him/her.
 * Arguments    : int brief - if true, write the short-description,
 *                            else write the long-description.
 * Returns      : int 1 - always.
 */
public int
do_glance(int brief)
{
    object env;
    object *ob_list;
    object *lv;
    object *dd;
    string item;

    /* Don't waste the long description on NPC's. Yes, we'll waste it.
    if (!interactive(this_object()))
    {
        return 0;
    }
     */

    /* Wizard gets to see the filename of the room we enter and a flag if
     * there is WIZINFO in the room.
     */
    env = environment();
    if (query_wiz_level())
    {
        if (stringp(env->query_prop(OBJ_S_WIZINFO)))
        {
            write("Wizinfo ");
        }

        write(file_name(env) + "\n");
    }

    /* It is dark. */
    if (!CAN_SEE_IN_ROOM(this_object()))
    {
        if (!stringp(item = env->query_prop(ROOM_S_DARK_LONG)))
            write(LD_DARK_LONG);
        else
            write(item);
        return 1;
    }

    /* Describe the room and its contents. */
#ifdef DAY_AND_NIGHT
    if (!env->query_prop(ROOM_I_INSIDE) &&
        ((HOUR > 21) ||
         (HOUR < 5)) &&
        ((env->query_prop(OBJ_I_LIGHT) +
         query_prop(LIVE_I_SEE_DARK)) < 2))
    {
        write(LD_IS_NIGHT(env));
    }
    else
#endif
    {
        if (brief)
        {
            write(capitalize(env->short()) + ".\n");

            if (!env->query_noshow_obvious())
            {
                write(env->exits_description());
            }
        }
        else
        {
            write(env->long());
        }
    }

    ob_list = all_inventory(env) - ({ this_object() });
    lv = FILTER_LIVE(ob_list);
    dd = FILTER_SHOWN(ob_list - lv);

    item = COMPOSITE_FILE->desc_dead(dd, 1);
    if (stringp(item))
    {
        write(break_string(capitalize(item) + ".", 76) + "\n");
    }
    item = COMPOSITE_FILE->desc_live(lv, 1);
    if (stringp(item))
    {
        write(break_string(capitalize(item) + ".", 76) + "\n");
    }

    /* Give a nice description of the combat that is going on. */
    describe_combat(lv);

    return 1;
}
