//Stolen ruthlessly from the Rangers' rcomm.h!
#include "noldor.h"
#define JOINROOM (NOLGLD_DIR + "join")

int
list_active_noldor()
{
   string g_name, g_short;
   int i;
   int cnt = 0;
   object circlet;
   object *list;
   write("These Noldor are now awake:\n" +
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
         if ((circlet = present(NOLDOR_RACE_GUILD_CIRCLET, list[i])) &&
               (list[i]->short())) 
         {
            if (list[i]->query_ghost())
               write(" *deceased*");
          }
         else {
            if (list[i]->short())
//               write(" <no circlet>");
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
   write("There are "+cnt+" Noldor in Arda.\n");
   return 1;
  }

   write("You are the only Noldo in Arda.\n");
   return 1;

}
