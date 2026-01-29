#pragma strict_types
#pragma save_binary

#include <macros.h>
#include <options.h>
#include "../../morgulmage.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "stun_obj";

object  caster;
int     active, cooldown;

public void 
create_effect()
{
    set_name("_faugoroth_object_");
    set_short("stun spell object");    
    set_long("A spell stun object. One should not be able to see it "
           + "in their inventory.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object "
        + "created by the morgul mage faugoroth spell.\n");
}

private void
write_to_player(object player, object enemy, int fighting_caster) 
{
    switch(fighting_caster ? random(5) : random(3)) 
    {
        case 0: 
            player->catch_msg("You struggle to attack " + QTNAME(enemy)
                + ", yet you are so overcome with fear that you cannot "
                + "move.\n");
            break;
        case 1: 
            player->catch_msg("You attempt to attack " + QTNAME(enemy) 
                + ", but instead your muscles remain frozen in terror "
                + "while your mind succumbs to despair.\n");
            break;
        case 2: 
            player->catch_msg("Your arm quivers as you struggle to "
                + "attack " + QTNAME(enemy) + " but another rush of "
                + "pure terror grips your heart leaving you helpless.\n");
            break;
        case 3: 
            player->catch_msg("You struggle to attack " + QTNAME(enemy)
                + " but a wave of terror grips your heart, leaving you "
                + "unable to move a muscle as you stare into the eyes " 
                + " of " + QTNAME(enemy) + ".\n");
            break;
        case 4: 
            player->catch_msg("You struggle to regain your composure "
                + "until you look into the eyes of " 
                + QTNAME(enemy) + " and then you freeze as you know all "
                + "is truly lost.\n");
            break;                
    }
}

private void 
write_to_caster(object player) 
{
    if (query_effect_caster()->query_option(OPT_GAG_MISSES)) return;

    switch(random(5)) {
        case 0:
            query_effect_caster()->catch_msg(QCTNAME(player) + ", the "
                + "lowly worm, almost seems as if it wants to do "
                + "something. However the pathetic wretch is too frozen "
                + "with fear to move!\n");
            break;
        case 1:
            query_effect_caster()->catch_msg("You laugh in contempt as you "
                + "watch the feeble attempts of " + QTNAME(player) 
                + ", that worthless insect, to master its obvious fear "
                + "of you.\n");
            break;
        case 2:
            query_effect_caster()->catch_msg("An intense feeling of hatred "
                + "and disdain fills you while you watch " + QTNAME(player)
                + " attempt to struggle against your wishes, instead of "
                + "cowering before you like the frightened worm it truly "
                + "is.\n");
            break;
        case 3:
            query_effect_caster()->catch_msg("The maggot before you, " 
                + QTNAME(player) + ", feebly struggles with no success "
                + "against the iron grip of fear that you have inspired "
                + "in it.\n");
            break;
        case 4:
            query_effect_caster()->catch_msg(QCTNAME(player) + ", the useless "
                + "piece of dung, is obviously struggling to raise their hand "
                + "against you. Only their proper fear of you "
                + "prevents such a disrespectful action.\n");
            break;
    }
}

private void
write_to_enemy(object player, object enemy) 
{
    caster = query_effect_caster();

    if (enemy->query_option(OPT_GAG_MISSES)) return;

    switch(random(5)) {
        case 0:
            enemy->catch_msg("You watch with malicious amusement as " 
                + QTNAME(player) + " struggles helplessly, attempting "
                + "to attack you. However, it is clear that they "
                + "are too terrified of " + QTNAME(caster) + " to do "
                + "more than soil themselves.\n");
            break;
        case 1:
            enemy->catch_msg("You laugh in contempt as you watch the "
                + "feeble attempts of " + QTNAME(player) + " to master "
                + player->query_possessive() + " fear of " + QTNAME(caster)
                + ".\n");
            break;
        case 2: 
            enemy->catch_msg("It is obvious that despite the fear of " 
                + QTNAME(caster) + " that is dominating " 
                + player->query_objective() + ", " + QTNAME(player) 
                + " is attempting to fight back against you.\n");
            break;
        case 3:
            enemy->catch_msg(QCTNAME(player) + " is struggling in vain to "
                + "raise " + player->query_possessive() + " hand against you, "
                + "but it is obvious that the fearful presence of " 
                + QTNAME(caster) + " prevents them from doing anything more "
                + "profound than sobbing in terror.\n");
            break;
        case 4:
            enemy->catch_msg("You feel an almost uncontrollable urge to spit "
                + "upon " + QTNAME(player) + ", as the worthless scum is "
                + "unable to do anything but cower before you while in the "
                + "presence of " + QTNAME(caster) + ".\n");
            break;
    }                
}

private
void write_to_room_for_caster(object player) 
{
    caster = query_effect_caster();

    switch(random(5)) {
        case 0:
            caster->tell_watcher_miss("You watch as " + QTNAME(player) 
                + " struggles helplessly to master " 
                + player->query_possessive() + " fear of "
                + QTNAME(caster) + " and fight back.\n", 
                player, ({ player, caster }));
            break;
        case 1:
            caster->tell_watcher_miss(QCTNAME(player) + " gives a feeble attempt "
                + "to fight back and master " + player->query_possessive() 
                + " fear of " + QTNAME(caster) + ", but fails miserably.\n",
                player, ({ player, caster }));
            break;
        case 2:
            caster->tell_watcher_miss("The dread presence of " + QTNAME(caster) 
                + " has so completely terrorized " + QTNAME(player) + " that "
                + "every attempt to fight back and defend " 
                + player->query_objective() + "self ends in failure.\n",
                player, ({ player, caster }));
            break;
        case 3:
            caster->tell_watcher_miss("You watch as " + QTNAME(player) 
                + " struggles in vain to strike back at " + QTNAME(caster) 
                + ", but " + player->query_pronoun() + " seems so overcome "
                + "with fear as " + player->query_pronoun() + " sobs in "
                + "terror.\n", 
                player, ({ player, caster }));
            break;
        case 4:
            caster->tell_watcher_miss(QCTNAME(player) + " looks as if " 
                + player->query_pronoun() + " would like to do nothing more "
                + "than strike back against " + QTNAME(caster) + ", yet "
                + "instead they only cower in fear.\n",
                player, ({ player, caster }));
            break;
    }
}

private
void write_to_room_for_non_caster(object player, object enemy) 
{
    caster = query_effect_caster();

    switch(random(5)) {
        case 0:
            enemy->tell_watcher_miss("You watch as " + QTNAME(player) 
                + " struggles uselessly to fight back against " 
                + QTNAME(enemy)  + ", but it is clear that the fearful "
                + "presence of " + QTNAME(player) + " has left " 
                + player->query_objective() + " helpless.\n",
                player, ({ player, enemy, caster }));
            break;
        case 1:
            enemy->tell_watcher_miss(QCTNAME(player) + " gives a feeble attempt "
                + "to fight back against " + QTNAME(enemy) + " and master "
                + "their fear of " + QTNAME(caster) + ", but fails "
                + "miserably.\n",
                player, ({ player, enemy, caster }));
            break;
        case 2:
            enemy->tell_watcher_miss("The dread presence of " + QTNAME(caster) 
                + " has so completey terrorized " + QTNAME(player) + " that "
                + "every attempt to fight back against " + QTNAME(enemy)
                + " and defend " + player->query_objective() + "self ends "
                + "in failure.\n",
                player, ({ player, enemy, caster }));
            break;
        case 3:
            enemy->tell_watcher_miss("You watch as " + QTNAME(player) 
                + " struggles in vain to strike back at " + QTNAME(enemy) 
                + ", but " + player->query_pronoun() + " seems so overcome "
                + "with fear in the presence of " + QTNAME(caster) + " that "
                + "they only sob in terror.\n",
                player, ({ player, enemy, caster }));
            break;
        case 4:
            enemy->tell_watcher_miss(QCTNAME(player) + " looks as if they would "
                + "like to do nothing more than strike back against "
                + QTNAME(enemy) + ", yet instead they do nothing except cower "
                + "in fear of " + QTNAME(caster) + ".\n",
                player, ({ player, enemy, caster }));
            break;
    }    
}

public int
query_faugoroth_active()
{
    return active;
}

public int
query_faugoroth_cooldown()
{
    return cooldown;
}

public string 
query_faugoroth_stun() 
{
    return caster->query_real_name();
}

public void
attack_blocked(object player)
{
    object enemy;
    
    enemy = player->query_attack();
    if (enemy)
    {
        write_to_player(player, enemy, (query_effect_caster() == enemy));
        write_to_caster(player);

        if (query_effect_caster() != enemy) {
            write_to_enemy(player, enemy);
            write_to_room_for_non_caster(player, enemy);
        } else {
            write_to_room_for_caster(player);
        }
    } 
}


public void
hook_stun_cooldown_in_effect(object player)
{
    player->catch_msg("You feel the dread gaze of " 
        + QTNAME(query_effect_caster()) + " fall upon you, but you gather "
        + "your resolve and battle on.\n");
    player->tell_watcher(QCTNAME(player) + " takes an involuntary step away "
        + "from " + QTNAME(query_effect_caster()) + ", the fear evident upon "
        + player->query_possessive() + " face before continuing to battle "
        + "on.\n", ({ query_effect_caster() }));
    query_effect_caster()->catch_msg(QCTNAME(player) + " takes an involuntary "
        + "step away from you, the fear evident upon " 
        + player->query_possessive() + " face before continuing to battle "
        + "on.\n");
}

public void
hook_stun_ended(object player)
{
    active = 0;
    cooldown = 1;

    if(player->query_ghost())
        return;

    player->catch_msg("Slowly you struggle to master the feeling  " +
        "of terror as you are once again able to control your limbs.\n");
    player->tell_watcher(QCTNAME(player) + " seems to recover from " 
        + "the fear which had gripped " + player->query_possessive() 
        + " as " + player->query_pronoun() + " is now able to move "
        + "once again.\n", ({ }));
}

public void
hook_stun_begin(object player, object target)
{
    caster = player;
    active = 1;

    target->catch_msg("An overwhelming fear freezes you in place as an "
        + "unbearable terror grips your heart.\n");
    target->tell_watcher(QCTNAME(target) + " freezes in panic, "
        + "unable to move as " + target->query_pronoun() + " gazes in "
        + "pure terror while looking into the face of " 
        + QTNAME(caster) + ".\n", ({ caster }));
    caster->catch_msg(QCTNAME(target) + " freezes in panic, unable "
        + "to move as " + target->query_pronoun() + " gazes in pure "
        + "terror while looking into your face.\n");
}
