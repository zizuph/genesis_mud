/*
 * Guild Object for the PoTs.
 *
 * Created by Navarre, February 2010.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "../defs.h"

void
create_object()
{
    set_name("cross");
    add_adj(({"steel", "holy"}));
    add_name("pot_guild_object");
    set_long("This is a holy steel cross.\n");
    add_prop(OBJ_M_NO_INS, 1); 
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_M_NO_STEAL,1);
}

int get_spells(string str)
{
  if (str == "for spells")
  {
    setuid();
    seteuid(getuid());

    object guild_shadow = clone_object(GUILD_SHADOW);
    int shadow_result = guild_shadow->shadow_me(this_player(), GUILD_TYPE,GUILD_STYLE, GUILD_NAME);
    find_player("navarre")->catch_msg(this_player()->query_real_name()+" got shadowed with a result of: "+shadow_result+".\n");
    
    // Make sure the command soul gets added
    this_player()->add_cmdsoul(GUILD_SOUL);
    this_player()->add_cmdsoul(SPELL_MANAGER_SOUL);

    this_player()->update_hooks();
    
    // Every caster guild using the new Genesis magic system will
    // use the mana shadow to get the new regeneration rates for mana.
    if (!this_player()->query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(this_player());
    }
    this_player()->catch_tell("\nWelcome, Potter.\n");
  }
  return 1;
}

public void init()
{
  ::init();
  add_action(get_spells, "pray");
}

