#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/magic.h"
#include "/d/Kalad/common/guilds/khiraa/default.h"
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <state_desc.h>
#include <stdproperties.h>

inherit "/d/Kalad/std/monster";

/* The spectre for the lich spell 'summon spectre' */
/* Sarr 28.Mar.97 */

object gMaster;

void
create_monster()
{
    ::create_monster();
    set_name("spectre");
    set_adj("ghostly");
    add_adj("black");
    set_short("ghostly black spectre");
    set_long("A horrid image of a black humanoid floats in the air "+
    "here. It is translucent, and you can see behind it. It hovers "+
    "in the air, its arms at its sides, and two red blazing orbs "+
    "in its ghostly head. It looks like it is just watching.\n");
    set_stats(({1,1,1,1,1,1}));
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(LIVE_I_SEE_DARK,5);
    add_prop(OBJ_M_NO_ATTACK,"It doesn't seem to be on this "+
    "plane of existance, and so you cannot attack it.\n");

    set_tell_active(1);
}

void
attack_object(object ob)
{
    ::attack_object(ob);
    tell_room(E(ob),"The "+short()+" fades away!\n");
    remove_object();
}

public void
catch_msg(mixed str, object from_player)
{
    ::catch_msg(str, from_player);
    
    if ((from_player == TO) || !objectp(gMaster))
        return;

    gMaster->catch_msg("*");
    gMaster->catch_msg(str, from_player);
}

int
query_met(mixed ob)
{
    return gMaster->query_met(ob);
}

void
set_sp_master(object ob)
{
    gMaster = ob;
}

public int
do_glance(int brief)
{
    object env;
    object *ob_list;
    object *lv;
    object *dd;
    string item;
 
 
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
            write("damn");
        else
            write(item);
        return 1;
    }
 
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
