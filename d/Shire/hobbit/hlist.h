//Stolen ruthlessly from the Rangers' rcomm.h!
#include "hobbit.h"
#define JOINROOM (HOBGLD_DIR + "join")

int
list_active_hobbits()
{
   string g_name, g_short;
   int i;
   int cnt = 0;
   object stick;
   object *list;
   write("These Adventuresome Hobbits are adventuring now:\n");
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
         if ((stick = present("_hobbit_race_guild_pipe_", list[i])) &&
               (list[i]->short())) 
         {
            if (list[i]->query_ghost())
               write(" *deceased*");
            if(list[i]->query_is_birthday())
               write("<BIRTHDAY!>");
          }
         else {
            if (list[i]->short())
               write(" <no pipe>");
          }
         if (!list[i]->query_invis() || TP->query_wiz_level())
            write("\n");
        }
   }

  if(cnt > 1)
  {
   write("There are now "+cnt+" Adventuresome Hobbits adventuring.\n");
   return 1;
  }

   write("You are the only Adventuresome Hobbit around.\n");
   return 1;
}
