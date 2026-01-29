/**
 * Navarre December 30th 2007.
 * Poison Arrow made for the Archer guild, designed to be used only for the archers layman and occ branch.
 * All others will be permitted to use it, but will not get any special benefit from it.
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
    set_adj("serrated");
    add_adj("oakwood");
    set_projectile_id("serrated_oakwood_arrow");
    set_hit(48);
    set_pen(48);
    set_keep(1);
    
    add_item(({"feathers",
               "green feathers",
               "dyed feathers"}), "The feathers making up the fins have been dyed green.\n");
   
    add_item("shaft", "The shaft is made out of wood from oak trees, and has a snake decorated on it.\n");

    add_item(({"snake", "tip"}), "The tip of the arrow has a snake head carved on it. Small onyx gems are " +
             "used for its eyes, and its mouth open with fangs sticking out ready to strike its victim.\n");
    
        add_prop(MAGIC_AM_ID_INFO, 
        ({ "This arrow is magically embrued to be able to poison its victims.", 60}));
        
    add_prop(MAGIC_AM_MAGIC, ({ 70, "enchantment" }));
    
    add_prop(OBJ_S_WIZINFO, "This arrow poison its targets, if fired " +
                            "by the hands of the elven archers in Krynn. The arrow is used as a " +
                            "guild special, which is the reason others can not use it, and the " +
                            "reason for it being allowed to be as good as it is.\n");
}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This arrow is made out of wood from " +
            "oak trees, and has a small snake head carved at the tip. " +
            "Along the serrated shaft, the arrow is decorated with carvings "+
            "that makes it appear to have a snake slittering across it. "+
            "With this unusual design and the rough green feathers " +
            "making up the fins, this arrow is most likely not intended for "+
            "precision.\n" :
            "These arrows are made out of wood from oak trees, and each has "+
            "a small snake head carved at the tip. Along the serrated "+
            "shafts, the arrows are decorated with carvings that make  "+
            "them appear to have a snake slittering across them. "+
            "With this unusual design and the rough green feathers making up "+
            "the fins, these arrows aren't intended for precision.\n");
 }

public varargs
void
projectile_hit_target(object archer,
                      int aid,
                      string hdesc,
                      int phurt,
                      object enemy,
                      int dt,
                      int phit,
                      int dam,
                      int hid)
{
    object poison;


    ::projectile_hit_target(archer, aid, hdesc, phurt, enemy, dt, phit, dam, hid);
    if(archer->query_wiz_level() ||
       archer->query_guild_name_occ() == "Ansalon Elvish Archers" ||
       archer->query_guild_name_layman() == "Ansalon Elvish Archers")
    {
        if(phurt > 1)
        {
            tell_room(environment(enemy), QCTNAME(enemy) +" appears to shudder at the impact of the arrow.\n", enemy);
        
            enemy->catch_tell("The carved snake arrow leaves behind a sickly green residue from where it pierced your skin.\n");

            /*
             * Clone poison and give to enemy.
             *
             * All combat aid (50%) is used for the poison given by these arrows.
             *
             * The goal was to hit about 50% combat aid for this arrow.
             * Tests were performed with regular 40/40 weapons.
             * Regular weapons wielded by person with 100 in all stats against a foe with
             * 100 in skills and wearing 40 ac armour full body coverage.
             * The regular weapons yielded about 15 damage per second. Calculated from the average
             * of 1 hour fights. A 40/40 bow with this arrow performing the same tests yielded
             * about 22 damage per second.
             *
             * If 15 damage per second is the normal damage (0% combat aid).
             * Then 30 damage per second would be 100% combat aid.
             * 50% combat aid would be:
             *
             * (30-15)/2 + 15 = 22.5 ~ 23
             * Since 22 < 23 we are just below 50% combat aid.
             *
             * Combat done over : 3600 seconds.
             * Total damage done to me : 81504
             * Damage per second : 22.
             */
            poison = clone_object("/std/poison_effect");
            poison->set_interval(10);
            poison->set_time(120);
            poison->set_damage(({POISON_FATIGUE, 30, POISON_HP, 100}));
            poison->set_strength(20+random(40));
            poison->set_poison_type("snake");
            poison->move(enemy, 1);
            poison->start_poison(archer);
        }
    }
}
