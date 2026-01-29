// This is a dwarf bane weapon, adapted from the goblin slayer.

inherit "/std/weapon";
inherit "/lib/keep";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define HIT 48
#define PEN 48
 
#define HIT2 34
#define PEN2 30
 
#define EQRN enemy->query_race_name()

int enemy_type = 0;

void
create_weapon()
{
    set_name("dwarfbane");
    add_name("club");
    add_adj("red-spiked");
    add_adj("steel");
    set_short("red-spiked steel club");
    set_long("This red-spiked steel club seems to be made out of " +
             "steel that has had red colouring added in the molding phase. "+
             "The spikes appear to be unusually sharp ready to tear through " +
             "even the toughest leathery skin.\n");
    
    set_hit(HIT2);
    set_pen(PEN2);
    set_wt(W_CLUB);
    set_hands(W_RIGHT);
    set_dt(W_BLUDGEON);

    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This weapon is magically enchanted.\n", 5,
        "The club was crafted long ago to be used " +
        "against the fiery dwarf warriors.\n",25,
        "The enchantment makes it easier to penetrate the tough hide " +
        "that the dwarves are known for. " +
        "The club can generally not be wielded by dwarves, unless they " +
        "are one of the rare dwaves who has turned against his kin, and " +
        "walks the path of pure evil.\n", 55}));
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,35) + 500 + random(500)); 
}

mixed
wield(object what)
{
    if(TP->query_race_name() == "dwarf" && TP->query_alignment() > -1200)
    {
        return "The " + short() + " refuses you. You cannot wield it.\n";
    }
    return 0;
}

void
state_change(int hit, int pen)
{
 
    set_hit(hit);
    set_pen(pen);
 
    if (wielded && wielder)
        wielder->update_weapon(this_object());
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam)
{
    int r;
 
    if ((EQRN == "dwarf") || (EQRN == "hill dwarf"))
    {
        r = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, 2*dam);       

        if(!random(4))
        {
            wielder->catch_tell("The red spikes on your " + short() +
                                " pulse as if the club has a life of its own.\n");

            tell_room(E(wielder), "The red spikes on the " + short() + " wielded by " +
                QTNAME(wielder) + " pulse as if the club has a life of its own.\n", wielder);
        }

        /* Switch to high power */
        if (!enemy_type)
        {
            state_change(HIT, PEN);
            enemy_type = 1;
        }
 
    }
    else
    {
        r = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
        
        /* Switch to low power */
        if (enemy_type)
        {
            state_change(HIT2, PEN2);
            enemy_type = 0;
        }
    }
    return r;
}
