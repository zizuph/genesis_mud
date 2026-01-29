/**
 * Arman 2017 - poison arrow originally designed for the elven archers 
 *              guild by Navarre in 2007, re-purposed.
 */

#include </stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include <poison_types.h>

inherit "/std/arrow";
inherit "/lib/keep";

public void
create_arrow()
{
    set_adj("cruel");
    add_adj("oakwood");
    set_projectile_id("hobgoblin_poison_arrow");
    set_hit(30);
    set_pen(30);
    set_keep(1);
    
    add_item(({"feathers","black feathers","dyed feathers"}), 
        "The feathers making up the fins have been dyed black.\n");
   
    add_item("shaft", "The shaft is made out of wood from oak trees, " +
        "and has a crudely burnt image of a snake on it.\n");
    
    add_prop(MAGIC_AM_ID_INFO, ({ "This arrow has been alchemically " +
        "enhanced to poison its victims.", 60}));
        
    add_prop(MAGIC_AM_MAGIC, ({ 10, "transmutation" }));
    
    add_prop(OBJ_S_WIZINFO, "This arrow poisons its target on a hit:\n"+
                            "      interval 10\n      time 120\n" +
                            "      damage   fatigue 15, hp 50\n" +
                            "      strength 20 + random 40.\n");

    setuid();
    seteuid(getuid());
}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This crudely made arrow is made from " +
            "oak wood, and sports a cruelly-barbed iron head. " +
            "Along the serrated shaft, the image of a snake has been " +
            "burnt into it. " +
            "With this unusual design and the rough black feathers " +
            "making up the fins, this arrow is most likely not intended " +
            "for precision.\n" :
            "These crudely made arrows are from oak wood, and each " +
            "sports a cruelly-barbed iron head. Along the " +
            "shafts the image of a snake has been burnt. " +
            "With this unusual design and the rough black feathers " +
            "making up the fins, these arrows aren't intended for " +
            "precision.\n");
 }

public varargs
void
projectile_hit_target(object archer, int aid, string hdesc, int phurt,object enemy,
                      int dt, int phit, int dam, int hid)
{    
    object poison;

    ::projectile_hit_target(archer, aid, hdesc, phurt, enemy, dt, phit, dam, hid);

    if(phurt > 1)
    {
            tell_room(environment(enemy), QCTNAME(enemy) +" appears to " +
                "shudder at the impact of the arrow.\n", enemy);
        
            enemy->catch_tell("The cruel oakwood arrow leaves behind a " +
                "sickly green residue from where it pierced your skin.\n");


            poison = clone_object("/std/poison_effect");
            poison->set_interval(10);
            poison->set_time(120);
            poison->set_damage(({POISON_FATIGUE, 15, POISON_HP, 50}));
            poison->set_strength(20+random(40));
            poison->set_poison_type("snake");
            poison->move(enemy, 1);
            poison->start_poison(archer);
    }
}
