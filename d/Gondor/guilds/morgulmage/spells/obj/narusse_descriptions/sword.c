#include "../../../morgulmage.h"
#include <macros.h>

inherit MORGUL_SPELL_OBJ_DIR + "narusse_descriptions/description_base";

void display_ignite_message(object wielder, object weapon)
{
    object env = environment(wielder);
    tell_room(env, "Bright sparks flare suddenly from the hilt of the "
        + weapon->short() + ". With a swift gesture, " + QTNAME(wielder)
        + " causes the sparks to engorge into an engulfling flame "
        + "around " + weapon->short() + ".\n", wielder);

    wielder->catch_msg("Bright sparks flare suddenly from the hilt of "
        + "the " + weapon->short() + ". You gesture swiftly causing the "
        + "flickering sparks to engorge into an engulfing flame around "
        + "the " + weapon->short() + ".\n");
}

int display_death_message(object wielder, object enemy, object weapon) 
{
    wielder->tell_watcher(QCTNAME(wielder) + " suddenly grabs " 
        + QTNAME(enemy) + " by the shoulder and plunges the "
        + weapon->short() + " through " + enemy->query_possessive()
        + " sternum. As the blade protrudes through " + QTPNAME(enemy)
        + " back, a smouldering scent of death permeates the area.\n",
        enemy, ({ wielder, enemy }));

    wielder->catch_msg("You deftly grab " + QTPNAME(enemy) + " shoulder "
        + "and plunge your flaming blade through " 
        + enemy->query_possessive() + " chest. The smell of raw death "
        + "permiates from the smouldering carcass on your blade.\n");
        
    enemy->catch_msg("A crushing pain overwhelms your senses as " 
        + QTNAME(wielder) + " grabs your shoulder with the strength of "
        + "Mordor. With a rasp of triumph, you are pulled forward and "
        + "overcome with a searing doom as the " + weapon->short()
        + "plunges into your breast.\n");

    return 1;
}