//Stolen ruthlessly from the Rangers' rcomm.h!
#include "orcr.h"
#define JOINROOM (ORCRGLD_DIR + "join")

int
list_active_orcsr()
{
   string g_name, g_short;
   int i;
   int cnt = 0;
   object stick;
   object *list;
   write("These orcs are ravaging the world now:\n");
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

         if (!list[i]->query_invis() || TP->query_wiz_level())
            write("\n");
        }
   }

  if(cnt > 2)
  {
   write("There are "+cnt+" orcs ravaging the world.\n");
   return 1;
  }

   write("You are the orc awake now.\n");
   return 1;
}
