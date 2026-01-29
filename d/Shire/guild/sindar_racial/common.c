
#include "sindar_racial.h" 

 
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
   
   if (file_size(SINDAR_RACE_GUILD_LOG) > LOG_SIZE)
      {
      rename(SINDAR_RACE_GUILD_LOG, (SINDAR_RACE_GUILD_LOG + ".old"));
   }
   
   write_file(SINDAR_RACE_GUILD_LOG, text);
}
