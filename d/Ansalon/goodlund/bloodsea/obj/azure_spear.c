
inherit "/std/weapon";
inherit "/lib/keep";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define HIT 45
#define PEN 40
 
#define HIT2 45
#define PEN2 55
 
#define EQRN enemy->query_race_name()

/* Kender prop, allow alter ability to change the descriptions of the weapon */
#define OBJ_I_CONVERT_HOOPAK "_obj_i_convert_hoopak"

int enemy_type = 0;

void
create_weapon()
{
    set_name("spear");
    add_adj("azure");
    add_adj("azure-steel");
    add_adj("steel");
    set_short("azure-steel spear");
    set_long("This long and heavy spear has been crafted from enchanted steel that " +
        "glows a bright azure-blue. Carvings have been elaborately crafted along " +
        "the length of the weapon, making it resemble a long sinuous eel.\n");

    add_item(({"elaborate carvings","carvings"}),"@@read_runes");


    set_hit(HIT2);
    set_pen(PEN2);
    set_wt(W_POLEARM);
    set_hands(W_BOTH);
    set_dt(W_IMPALE);
    
/* Kender prop, allow alter ability to change the descriptions of the weapon */
    add_prop(OBJ_I_CONVERT_HOOPAK, 1);

    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This weapon is magically enchanted.\n", 5,
	"This spear has been crafted by elves, and dates back to the Age of " +
        "Light.\n",25,
        "Forged for the Kinslayer War, this spear is enchanted with the sole " +
        "purpose of slaying humans, doing much greater damage to them.\n",55}));
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    add_prop(OBJ_I_VOLUME, 3500);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(55,45) + 500 + random(500)); 
}


int
read_runes2()
{
    write("These beautifully engraved carvings resemble a long sinuous eel.\n");
    return 1;
}

string
read_runes()
{

    return "These beautifully engraved carvings resemble a long sinuous eel.\n";
}


mixed
wield(object what)
{
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
    int damage;

    r = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
 
    if ((EQRN == "human"))
    {

        if(!random(4))
        {
            wielder->catch_tell("Your " + short() + " blazes like lightning!\n");
            tell_room(E(wielder), "The " + short() + " wielded by " +
                QTNAME(wielder) + " blazes like lightning!\n", wielder);


	    damage = random(150)+
                     wielder->query_stat(SS_STR) +
                     wielder->query_stat(SS_DEX);
	    damage = MIN(450, damage);
	    enemy->hit_me(damage, W_IMPALE, wielder, -1);
        }

        /* Switch to high power */
        if (!enemy_type)
        {
            state_change(HIT2, PEN2);
            enemy_type = 1;
        }
 
    }
    else
    {
        /* Switch to low power */
        if (enemy_type)
        {
            state_change(HIT, PEN);
            enemy_type = 0;
        }
 
    }
 
    return r;
}
