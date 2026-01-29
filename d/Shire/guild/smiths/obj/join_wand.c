/*
 * Wand will let you make players join Smiths
 * Palmer  16-July-2006
 *
 */


inherit "/std/object";
#include <stdproperties.h>
#include "/config/sys/local.h"
#include "/d/Shire/guild/smiths/smiths.h"




public void
add_soul(string player_name) 
{
    object shadow, player, necklace;
    int result;

    player = find_player(player_name);
    shadow = clone_object(SMITHSDIR + "shadow");

     if ((result = shadow->shadow_me(player, "craft", GUILD_STYLE, GUILD_NAME)) != 1)
     {
          shadow->remove_shadow();
          write("There was an error transferring the Smith soul to craft slot."+
                "\nPlease make a bug report, error: " + result +
                " on shadowing.\n");
          return;
     }

     //player->clear_guild_stat(SS_CRAFT);
     player->add_cmdsoul("/d/Shire/guild/smiths/soul");
     player->update_hooks();
     //player->set_guild_stat(SS_CRAFT, guild_exp);


}



create_object()
{
    set_name("wand");
    set_short("Smith join wand.");
    set_long("The wand will let you smjoin the Smiths guild.\n");
    
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 700);
    add_prop(OBJ_I_VALUE, 50);
    seteuid(getuid(this_object()));
    set_alarm(2.0, 0.0, &add_soul("paljr"));
}
