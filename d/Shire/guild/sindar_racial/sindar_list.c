#include "/d/Shire/sys/defs.h"
#include "sindar_racial.h"

int
list_active_sindar()
{
   string g_name, g_short;
   int i;
   int cnt = 0;
   object guild_obj;
   object *list;
   write("These Sindar are now awake:\n" +
   "------------------------------------------------------------" + "------------------\n\n");
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
         if ((guild_obj = present(SINDAR_RACE_GUILD_OBJ, list[i])) &&
               (list[i]->short())) 
         {
            if (list[i]->query_ghost())
               write(" *deceased*");
          }
         else {
            if (list[i]->short())
//               write(" <no guild_obj>");
                write("");
          }
         if (!list[i]->query_invis() || TP->query_wiz_level())
            write("\n");
        }
   }
    write("\n==================================================="+
        "===========================\n");

  if(cnt > 1)
  {
   write("There are "+cnt+" Sindar in Arda.\n");
   return 1;
  }

   write("You are the only Sindar in Arda.\n");
   return 1;

}
