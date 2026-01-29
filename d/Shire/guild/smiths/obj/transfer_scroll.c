/*
 * This log transfers a person removed from the Smiths layman guild to the craft slot
 * when they login.
 *
 * Palmer  16-July-2006
 *
 */


inherit "/std/scroll";
#include <stdproperties.h>
#include "/config/sys/local.h"
#include "/d/Shire/guild/smiths/smiths.h"
#define NECKLACE SMITHSDIR_OBJ + "necklace"

/*
* Function name: log_guild
* Description  : This function logs some actions of members of the guild.
*                It uses a larger cycle than basically coded.
* Arguments    : string text - the message to log.
*/
nomask private void
log_guild(string text)
{
   setuid();
   seteuid(getuid());

   if (file_size(SMITH_MEMBERSHIP_LOG) > MAX_MEMBERSHIP_LOG_SIZE)
      {
      rename(SMITH_MEMBERSHIP_LOG, (SMITH_MEMBERSHIP_LOG + ".old"));
   }

   write_file(SMITH_MEMBERSHIP_LOG, text);
}



public void transfer_soul() 
{
    object shadow, necklace;
    int guild_exp, result;
    string player_name;

    player_name = TP->query_name();
    guild_exp = SMITHS_TRANSFER_OBJ->query_player(player_name);
    if (SMITHS_TRANSFER_OBJ->query_player(player_name) == 0)
    {
        write("You can't transfer. You aren't in the Smith lay guild.\n");
        write("Please mail Palmer with a bug report.\n");
        return;
    }

     shadow = clone_object(SMITHSDIR + "smiths_craft_shadow");

     if ((result = shadow->shadow_me(TP, "craft", GUILD_STYLE, GUILD_NAME)) != 1)
     {
          shadow->remove_shadow();
          write("There was an error transferring the Smith soul to craft slot."+
                "\nPlease make a bug report, error: " + result +
                " on shadowing.\n");
          return;
     }

     TP->clear_guild_stat(SS_CRAFT);
     TP->add_cmdsoul("/d/Shire/guild/smiths/smiths_craft_soul");
     TP->update_hooks();
     // Transfer layman guild experience to craft slot
     TP->set_guild_stat(SS_CRAFT, guild_exp);

     seteuid(getuid(this_object()));

     necklace = clone_object(NECKLACE);
     necklace->set_short("smith necklace");
     if (necklace->move(TP)!=0) {
        TO->command("say It seems you cannot carry your necklace."+
           " I will keep it for you, just come back and <get"+
           " necklace> whenever you want to.");
     }

    // Remove from transfer list so they can't do it again.
    SMITHS_TRANSFER_OBJ->remove_player(player_name);
    log_guild(extract(ctime(time()), 4, 15) + " " +extract(ctime(time()), 21, 4)+" " + WRITE_NAME(TP) + " transfered to the Craft Blacksmiths.\n");

}



create_scroll()
{
    seteuid(getuid(this_object()));
    set_name("scroll");
    set_short("scroll labeled 'READ ME!'");
    set_long("The scroll is held rolled up with a blue and yellow band tied " +
	"around it.\nOn the band the text 'READ ME!' is written in golden " +
	"letters.\n");
    set_file("/d/Shire/guild/smiths/obj/transfer.txt");
    set_alarm(2.0, 0.0, &transfer_soul(TP));
}
