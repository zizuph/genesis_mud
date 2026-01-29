/*
 * ob_sword.c
 * An obsidian sword.
 * Written by Trenix@Genesis, 8-16-93
 *
 */

#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#define GOBLINLORD "/d/Rhovanion/common/npcs/goblins/goblin_lord"

create_weapon()
{
    set_name(({ "sword", "blade" }));
    set_pname(({ "swords", "blades" }));
    set_adj("obsidian");  /* Still not sure about the spelling. */
    add_adj("black");
    set_short("black obsidian sword");
    set_pshort("black obsidian swords");
    set_long("@@query_long");
    set_hit(30);
    set_pen(30);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);  /* Bitwise or inclusive */
    set_hands(W_ANYH);
    set_wf(this_object());
    add_prop(OBJ_I_LIGHT,0);
    update_prop_settings();  /* Fix up the value, weight, and other stuff. */
}

string query_long()
{
    object player;

    player = this_object()->query_wielded();

    if ( objectp(player) )
    {
        if ( player->query_mana() >= 50 )
        {
            player->add_mana(-50);  /* Nasty trick isn't it. */
        }
        return (break_string("As you stare into the blackness of the "+
                "obsidian blade you lose touch with the world around "+
                "you. You feel somewhat drained as you pull your eyes "+
                "away.\n",65));
    }
    return (break_string("This sword has a black obsidian blade as dark "+
            "as the night itself. It looks like it could slice through "+
            "the strongest of armours.\n",65));
}

wield()
{
    object env, player;

    player = this_player();
    env = environment(player);

    if ( this_player()->query_skill(SS_WEP_SWORD) < 35 )
    {

        write("You are not worthy of such a weapon.\n");
        if ( objectp(env) )
        {
            tell_room(env,capitalize(QTNAME(player))+
            " tried to wield the black obsidian sword but failed.\n",player);
        }
        return -1;
    }
    write("The darkness from within the blade escapes into the room.\n");
    if ( objectp(env) )
    {
        tell_room(env,"The darkness within "+QTNAME(this_player())+
                  "'s blade escapes into the room.\n",player);
    }
    add_prop(OBJ_I_LIGHT,-1);  /* Adds darkness */
    return 1;
}

unwield()
{
    object env, player;

    add_prop(OBJ_I_LIGHT,0);
    write("As you let go, the darkness is pulled back into the blade.\n");
    player = query_wielded();
    env = environment(player);
    if ( objectp(env) && !player->query_ghost() )
    {
        tell_room(env,capitalize(QTNAME(player))+" releases "+
                  player->query_possessive()+" obsidian blade.\n",player);
    }
    return 1;
}

did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
        int dam)
{
    int mana;

    if ( interactive(enemy) )
    {
        mana = enemy->query_mana();

        /* If damage is more than the mana it will take it all. */
        /* However, if it's less than or equal to, only take an */
        /* appropriate amount.                                  */

        if ( dam <= mana )
        {
            mana = dam;
        }
        enemy->add_mana(-mana);

        /* Tell the goblin lord if his enemy ran out of mana. */

        if ( explode( file_name( query_wielded() ), "#" )[0] == GOBLINLORD &&
             enemy->query_mana() < 1 )
             /* Mana may be zero or less if we missed. */
        {
            query_wielded()->attacker_out_of_mana(enemy);
        }
    }
    return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
}
 
query_recover()
{
    return MASTER+":"+query_wep_recover();
}

init_recover(str)
{
    init_wep_recover(str);
}

/* EOF */
