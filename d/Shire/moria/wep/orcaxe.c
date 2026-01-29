/*   Created by: ???
 *
 *   Purpose: ???
 *
 *   Modifications: Finwe, 24-Sept-2007:
 *
 *                  Toby, 24-Sept-2007 : Added if(wielder->query_npc())
 *                                       just to make sure no player can 
 *                                       get the bonus.
 */


#include "defs.h"

inherit "/std/weapon";
inherit "/lib/keep";

inherit "/d/Shire/moria/lib/hit_msg";

void
create_weapon()
{
    set_name("axe");
    add_name("_orc_axe_");
    add_name("waraxe");
    set_short("bloodstained mithril waraxe");
    set_pshort("bloodstained mithril waraxes");
    add_adj(({"bloodstained", "stained", "mithril", "war", "orcish", "orc"}));
    set_long("This is a bloodstained mithril waraxe originally of dwarven design, "
           + "but miskept by orcish hands, designed to fit these evil creatures' "
           + "foul limbs.\n");
    set_hit(30);
    set_pen(40);
    set_wt(W_AXE);
    set_wf(TO);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_ANYH);
}

/*
 * This, for one, seems totally inappropriate. However, on top of the changes
 * we have been making to normal combat, this has hideous effects to players,
 * and I don't think it works at all. If you want a tough weapon, code a
 * tough weapon. Not some weapon that shifts based on whether or not it is
 * wielded by your npcs.
 *
 *   - Gorboth (May 2008)
mixed
wield(object to)
{
    object wielder = ENV(to);

    if(wielder->query_npc())
    {
        if (wielder->query_race() == "orc")
        {
            set_hit(60);
            set_pen(80);
        }
        if (wielder->query_race() == "uruk")
        {
            set_hit(60);
            set_pen(80);
        }
        if (wielder->query_race() == "troll")
        {
            set_hit(60);
            set_pen(80);
        }
    }
}
*/

mixed
unwield()
{
    set_hit(30);
    set_pen(40);
}

int
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{     
    produce_msg(enemy, hdesc, phurt, dt);
    return 1;
}
 
string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}
 
void
init_recover(string arg)
{
    init_wep_recover(arg);
 
    init_keep_recover(arg);
}
