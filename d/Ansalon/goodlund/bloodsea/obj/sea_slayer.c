
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
    set_name("slayer");
    add_name("sword");
    add_name("sabre");
    add_adj("elaborate");
    set_short("elaborate sabre");
    set_long("This heavy-bladed sabre has had elaborate carvings engraved into it depicting " +
       "the wild and temperamental sea. You find this most apt, as both are as beautiful as " +
       "they are deadly! The sabre seems to pulse in your hand, sending your senses tingling " +
       "as if you were being engulfed by a gentle wave of water.\n");

    add_item(({"elaborate carvings","carvings"}),"@@read_runes");


    set_hit(HIT2);
    set_pen(PEN2);
    set_wt(W_SWORD);
    set_hands(W_ANYH);
    set_dt(W_SLASH);

    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This weapon is magically enchanted.\n", 5,
	"The sabre was crafted by the sea wizards of Saifhum.\n",25,
        "This blade has been enchanted to slay monsters of the sea, " +
        "particularly minotaurs and sea serpents.\n",55}));
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    add_prop(OBJ_I_VOLUME, 3500);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,35) + 500 + random(500)); 
}


int
read_runes2()
{
    write("These beautifully engraved carvings depict the wild and temperamental " +
       "sea. You notice various sea monsters - minotaurs, sea serpents, and others " +
       "you do not recognise - struggling within the wake.\n");
    return 1;
}

string
read_runes()
{

    return "These beautifully engraved carvings depict the wild and temperamental " +
       "sea. You notice various sea monsters - minotaurs, sea serpents, and others " +
       "you do not recognise - struggling within the wake.\n";
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
 
    r = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
 
    if ((EQRN == "minotaur") || (EQRN == "sea-elf") ||
        (EQRN == "dragon turtle") || (EQRN == "serpent") || 
        (EQRN == "triton") || (EQRN == "squid") ||
        (EQRN == "sea lion") || (EQRN == "octopus") ||
        (EQRN == "shark" || (EQRN == "sahuagin")))
    {

        if(!random(4))
        {
            wielder->catch_tell("Your " + short() + " darkens like an oncoming " +
                "storm on the high seas!\n");
            tell_room(E(wielder), "The " + short() + " wielded by " +
                QTNAME(wielder) + " darkens like an oncoming storm on the high seas.\n",
                wielder);
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
        /* Switch to low power */
        if (enemy_type)
        {
            state_change(HIT2, PEN2);
            enemy_type = 0;
        }
 
    }
 
    return r;
}
