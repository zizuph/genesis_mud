/**
 * Navarre December 30th 2007.
 * Fire Arrow made for the Archer guild, designed to be used only for the archers layman and occ branch.
 * All others will be permitted to use it, but will not get any special benefit from it.
 */

#include </stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/arrow";
inherit "/lib/keep";


public void
create_arrow()
{
    set_adj("fiery");
    add_adj("black-feathered");
    set_projectile_id("fiery_black_feathered_arrow");
    set_hit(48);
    set_pen(48);
    set_keep(1);
    
    add_item(({"feathers", "raven feathers"}), "These black raven feathers are incredible " +
                                               "smooth, allowing the wind to pass over them " +
                                               "without hindrance.\n");
    add_item(({"thin runes", "runes", "delicate runes", "thin and delicate runes", "delicate " +
               "and thin runes"}), "They run across the shaft of the arrow, but you have no " +
               "idea what they mean.\n");
    add_item(({"shaft", "ebony shaft"}), "The shaft is made of light ebony making this arrow " +
                                         "very well balanced.\n");
    add_item(({"crystal", "crystal tip", "tip"}), "It is some sort of crystal. Since the runes " +
                                                  "appears to flow towards the tip, it might be " +
                                                  "the place where the power of the runes come together.\n");
    add_item(({"glow", "red glow"}), "The red glow seems to come from the crystal tip and " +
                                     "envelopes the rest of the arrow.\n");

        add_prop(MAGIC_AM_ID_INFO, 
        ({ "This arrow is magically embrued to be able to cause fire damage in the right hands.", 60}));
        
    add_prop(MAGIC_AM_MAGIC, ({ 70, "enchantment" }));
    
    add_prop(OBJ_S_WIZINFO, "This arrow cause magical fire damage on the target if it is fired " +
                            "by the hands of the elven archers in Krynn. The arrow is used as a " +
                            "guild special, which is the reason others can not use it, and the " +
                            "reason for it being allowed to be as good as it is.\n");
}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This arrow has" : "These arrows have") + 
        " fins made from the finest raven feathers, from which " +
        "thin and delicate runes stretch out along the ebony shaft " +
        "ending at a crystal tip. A red glow " +
        ((num == 1) ? "emanates from the arrow and pervades its" : "emanates from the arrows and pervade their") +
        " presense by a radiating warmth.\n";
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
    string you_burnt;
    string they_burnt;
    int extra_dam = 0;

    ::projectile_hit_target(archer, aid, hdesc, phurt, enemy, dt, phit, dam, hid);
    if(archer->query_wiz_level() ||
       archer->query_guild_name_occ() == "Ansalon Elvish Archers" ||
       archer->query_guild_name_layman() == "Ansalon Elvish Archers")
    {
        
        if(phurt > 1 && (random(100) > enemy->query_magic_res(MAGIC_I_RES_FIRE)))
        {
            switch(dam)
            {
                case 1..99:
                    you_burnt = "You feel burnt by the fire.\n";
                    they_burnt = " seems burnt by the fire.\n";
                    break;
                case 100..175:
                    you_burnt = "You are badly hurt by the fire.\n";
                    they_burnt = " seems badly hurt by the fire.\n";
                    break;
                default:
                    you_burnt = "You are engulfed in flames.\n";
                    they_burnt = " is engulfed in flames.\n";
            }
            
            tell_room(environment(enemy), "A burst of fire emits from the fiery black-feathered " +
                                          "arrow as it hits " +
                                          QTNAME(enemy)+".\n", enemy);
            tell_room(environment(enemy), QCTNAME(enemy)+they_burnt, enemy);
            enemy->catch_tell("A burst of fire emits from the fiery black-feathered arrow as it hits you.\n");
            enemy->catch_tell(you_burnt);

            // The value used in the hit_me is PEN damage and not straight up damage.
            // PEN/4 + random(PEN/4) + random(PEN/4) + random(PEN/4),
            // so 100 dam becomes 25 + 12 + 12 + 12 in average = 51.
            // Bow only shoots every 2 rounds, so we allow a bit more damage per shot to reach the 50% combat aid.
            // so 2*dam ~ 50% combat aid.
            // Also not taking into the account that a miss counts for a lot more with the arrows, because
            // they only shoot every second round.
            enemy->hit_me(375, MAGIC_DT, archer, -1);  // W_IMPALE instead of MAGIC_DT? 
        }
    }
}
