/**
 * Navarre December 30th 2007.
 * Ice Arrow made for the Archer guild, designed to be used
 * only for the archers layman and occ branch.
 * All others will be permitted to use it, but will not
 * get any special benefit from it.
 */

#include </stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../guild.h"

inherit "/std/arrow";
inherit "/lib/keep";

#define SLOW_OBJ GUILD_OBJ + "slow"

public void
create_arrow()
{
    set_adj("blue");
    add_adj("crystal-tipped");
    set_projectile_id("blue_crystal-tipped_arrow");
    set_hit(48);
    set_pen(48);
    set_keep(1);
    
    add_item(({"feathers",
               "griffon feathers",
                "white feathers",
                "white griffon feathers"}), "The white griffons feathers make up " +
                "the fins and are responsible for making the arrow fly straight.\n");

    add_item("shaft", "The shaft is made of wood from the finest vallenwood trees.\n");

    add_item(({"crystal", "crystal tip", "tip"}), "The crystal is bright-blue " +
             "and shared liked a small leaf.\n");

    add_prop(MAGIC_AM_ID_INFO, 
             ({ "This arrow is magically embrued to be able to cause frost damage in the right hands.", 60}));
        
    add_prop(MAGIC_AM_MAGIC, ({ 70, "enchantment" }));
    
    add_prop(OBJ_S_WIZINFO, "This arrow cause magical a little frost damage on the target if it is fired " +
                            "by the hands of the elven archers in Krynn. The arrow is used as a " +
                            "guild special, which is the reason others can not use it, and the " +
                            "reason for it being allowed to be as good as it is. The arrow also " +
                            "adds an attack delay to the enemy.\n");
}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This elegant arrow is tipped with a " +
                         "leaf shaped bright-blue crystal, yet " +
                         "it remains very light and perfectly " +
                         "balanced. It has been carved from the " +
                         "finest of vallenwood trees, and the " +
                         "fins are made from white griffon " +
                         "feathers. The blue crystal shimmers " +
                         "slightly as skin touches its cold " +
                         "surface.\n" : "These elegant arrows " +
                         "are tipped with a leaf shaped " +
                         "bright-blue crystal, yet they remain " +
                         "very light and perfectly balanced. " +
                         "They have been carved from the finest " +
                         "of vallenwood trees, and the fins are " +
                         "made from white griffon feathers. The " +
                         "blue crystal shimmers slightly as skin " +
                         "touches its cold surface.\n");
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
    string you_frozen;
    string they_frozen;
    int delay = 0;
    int stunned_timer;
    
    ::projectile_hit_target(archer, aid, hdesc, phurt, enemy, dt, phit, dam, hid);
    if(archer->query_wiz_level() ||
       archer->query_guild_name_occ() == "Ansalon Elvish Archers" ||
       archer->query_guild_name_layman() == "Ansalon Elvish Archers")
    {
        
        if(phurt > 1 && (random(100) > enemy->query_magic_res(MAGIC_I_RES_COLD)))
        {
            switch(dam)
            {
                case 1..99:
                    you_frozen = "You feel frozen from the ice.\n";
                    they_frozen = " seems frozen from the ice.\n";
                    break;
                case 100..175:
                    you_frozen = "You are badly frozen from the ice.\n";
                    they_frozen = " seems badly frozen from by the ice.\n";
                    break;
                default:
                    you_frozen = "You are chilled to the bone from the ice.\n";
                    they_frozen = " appears chilled to the bone from the ice.\n";
            }
            
            tell_room(environment(enemy), "A cloud of ice errupts from the blue crystal-tipped arrow " +
                                          "as it hits "+QTNAME(enemy)+".\n", enemy);
            tell_room(environment(enemy), QCTNAME(enemy)+they_frozen, enemy);
            enemy->catch_tell("A cloud of ice errupts from the blue crystal-tipped arrow as it hits you.\n");
            enemy->catch_tell(you_frozen);

            /*
             * We calculated in the fire arrow that 380 was 50% combat aid.
             * Since we split it here to have half damage half stun, the damage
             * is half.
             *
             * 25% combat aid damage.
             */
            enemy->hit_me(190, MAGIC_DT, archer, -1);


            /*
             * The bow only shoots once every 10 seconds.
             * So we will give the player a 25 slowness per arrow.
             * But arrows don't overlap.
             *
             * 100 value in LIVE_I_QUICKNESS is 100% combat aid.
             * 50 value is 50%
             * 25 value is 25%.
             * So we use 25% to do damage and slow the enemy using our last 25%.
             */
            seteuid(getuid(this_object()));
            clone_object(SLOW_OBJ)->move(enemy, 1);
        }
    }
}
