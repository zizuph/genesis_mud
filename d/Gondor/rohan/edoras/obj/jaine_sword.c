/*
 * Rohirrim shortsword
 * Last mod: Olorin, 14-jul-1994
 * Modification log: 
 * 14-jul-94: Changed WC to follow new weapon_guide,
 *            changed into shortsword,
 *            added GONDOR_M_ROHIRRIM_NO_SELL prop
 *            Olorin
 *
 * Stole for a sword for Jaine, a quest NPC
 * in the Sleeping Stallion
 *
 * Raymundo, Spring 2020
 */
inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Gondor/defs.h"
int is_jewel = 1;
void
create_weapon()
{
    set_name(({"rapier","sword"}));
    set_short("@@my_short@@");
    
    set_adj(({"thin", "jewel-hilted", "jewel", "hilted"}));
    set_long("@@my_long@@");
    add_item( ({"jewel", "gem", "hilt"}), "@@check_jewel@@");
    add_item( ({"thread", "threads", "gold thread", "gold threads"}),
        "The gold threads are twisted together in a decorative fashion. "
        + "They seem to be designed to hold things in place in the "
        + "hilt.\n");
    
    set_default_weapon(22, 18, W_SWORD, W_IMPALE, W_RIGHT,0);
    add_prop(OBJ_I_WEIGHT,(F_WEIGHT_DEFAULT_WEAPON(22, W_SWORD)/2   ));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 7);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(22, 18) + random(300));
    add_prop(GONDOR_M_ROHIRRIM_NO_SELL, 1);
}

string
my_long()
{
    if(is_jewel == 1)
    {
        return("This is a thin, light weight rapier. Its blade is "
        + "long, but still thin and light. On the hilt of the sword, "
        + "you see a jewel.\n");
    }
    else
    {
        return("This is a thin, light weight rapier. Its blade is "
        + "long, but still thin and light. On the hilt of the sword, "
        + "you see a gap where a jewel used to be.\n");
    }
}
    
string
my_short()
{
    if(is_jewel == 1)
    {
        return("thin jewel-hilted rapier");
    }
    else
    {
        return("thin unjeweled rapier");
    }
}
/*
query_recover()  { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
*/
string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "#p_u#" + is_jewel + "#";
}

void
init_recover(string  arg)
{
    string dummy;
    init_wep_recover(arg);
    sscanf(arg, "%s#p_u#%d#%s", dummy, is_jewel, dummy);
}
void
init()
{
    ::init();
    add_action("pry_jewel", "pry");
}

string
check_jewel()
{
    if(is_jewel == 1)
    {
        return("You see a beautiful pearl set in the hilt. It's held in "
            + "place by gold threads, but you could probably pry it out.\n");
    }
    else
    {
        return("You see a gaping opening in the hilt of the sword. Maybe "
            + "there used to be a jewel there.\n");
    }
}

int
pry_jewel(string str)
{
    if(!strlen(str))
    {
        notify_fail("Pry what? The jewel? From the hilt?\n");
        return 0;
    }
    if (parse_command(str, TO, "[the] [jewel] [pearl] [from] [the] 'hilt' [of] [the] [sword] ") )
    {
        setuid();
        seteuid(getuid());
        object gem;
        gem = clone_object("/d/Genesis/gems/obj/pearl");
        gem->move(TP);
        write("You pry the pearl from the hilt of the sword!\n");
        say(QCTNAME(TP) + " pries a pearl from the hilt of the sword!\n");
        is_jewel = 0;
        set_short("thin unjeweled rapier");
        set_long("This is a thin, light weight rapier. Its blade is "
        + "long, but still thin and light. On the hilt of the sword, "
        + "you see a gap where a jewel used to be.\n");
        return 1;
    }
    else
    {
        notify_fail("Pry what? The jewel? from the hilt?\n");
        return 0;
    }
}
