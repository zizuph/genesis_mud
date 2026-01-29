/**
 * Arman 2020 - poison arrow from the quill of a Baron Sahuagin.
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
    set_adj("barbed");
    add_adj("long");
    add_name("quill");
    set_short("long barbed quill");
    set_projectile_id("sahuagin_poison_arrow");
    set_hit(40);
    set_pen(50);
    set_keep(1);
    set_heap_size(1);
   
    add_item( ({"hollow tip", "tip", "poison"}),
        "The tip of the long barbed quill is hollow and filled " +
        "with a nasty fatiguing poison.\n");
    
    add_prop(MAGIC_AM_ID_INFO, ({ "This long quill comes from a " +
        "Baron sahuagin, a creature mutated by the wild magic of " +
        "the Greygem of Gargath. The lingering wild magic makes " +
        "this quill able to pierce the hardest of armours, making " +
        "it a powerful arrow. Adding to its potency is a natural " +
        "fatiguing poison.\n", 60}));
        
    add_prop(MAGIC_AM_MAGIC, ({ 10, "transmutation" }));
    
    add_prop(OBJ_S_WIZINFO, "This arrow poisons its target on a hit:\n"+
                            "      interval 10\n      time 120\n" +
                            "      damage   fatigue 15, hp 50\n" +
                            "      strength 20 + random 40.\n");

}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This long barbed quill has been cut " +
            "from the body of a Baron sahuagin, a monstrous creature " +
            "of the deep that long ago had been mutated by the wild " +
            "magic of the Greygem of Gargath. Unnaturally sharp " +
            "with a hollow tip filled with poison, this quill makes " +
            "for a deadly arrow.\n" :
            "These long barbed quills have been cut " +
            "from the body of a Baron sahuagin, a monstrous creature " +
            "of the deep that long ago had been mutated by the wild " +
            "magic of the Greygem of Gargath. Unnaturally sharp " +
            "with a hollow tip filled with poison, these quills makes " +
            "deadly arrows.\n");
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
                "shudder at the impact of the long barbed quill.\n", enemy);
        
            enemy->catch_tell("The long barbed quill leaves behind a " +
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
