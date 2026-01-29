//Stolen ruthlessly from the Rangers' rcomm.h!
#include "orc.h"
#define JOINROOM (ORCGLD_DIR + "join")

int
list_active_orcs()
{
   string g_name, g_short;
   int i;
   int cnt = 0;
   object stick;
   object *list;
   write("These Orcs are in the service of the Dark Lord:\n");
   list = users();
   for (i = 0; i < sizeof(list); i++)
   {
      g_name = capitalize(list[i]->query_real_name());
      if (IS_MEMBER(list[i]))
         {
         /* Don't want a jr's name on the guildlist */
         if ((extract(g_name, -2) == "jr") && (!(TP->query_wiz_level())))
            continue;
         if(!list[i]->query_invis())
            {
            if (list[i]->query_wiz_level())
            {
              g_short = list[i]->query_title();
              write("o " + g_name + " " + g_short);
            }
            else
            {
              g_short = list[i]->query_title();
              write("- " + g_name + " " + g_short);
              }
            cnt++;
          }
         if (list[i]->query_invis() && TP->query_wiz_level())
            {
            write("@ (" + g_name + ")");
            cnt++;
          }
         if ((stick = present("_orc_race_guild_armband_", list[i])) &&
               (list[i]->short())) 
         {
            if (list[i]->query_ghost())
               write(" *deceased*");
//            if(list[i]->query_is_birthday())
//               write("<BIRTHDAY!>");
          }
         else {
            if (list[i]->short())
               write(" <no armband>");
          }
         if (!list[i]->query_invis() || TP->query_wiz_level())
            write("\n");
        }
   }

  if(cnt > 1)
  {
   write("There are now "+cnt+" Fearsome Orcs in the service of the Dark Lord.\n");
   return 1;
  }

   write("You are the only Fearsome Orc in the service of the Dark Lord.\n");
   return 1;
}
