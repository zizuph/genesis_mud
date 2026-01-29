inherit "/std/mobile";
#include "/d/Kalad/defs.h"


object offender;


/**********************************************************
 *   Prototypes
 *********************************************************/
 void set_offender(object who);
 string watch_offender();
 string query_offender_name();

create_mobile()
{
   set_name("detachment");
   add_name("soldiers");
   add_name("detachment of soldiers");
   set_gender(G_NEUTER);
   
   set_short("detachment of soldiers");
   set_long(
      "This is a small detachment of soldiers, numbering around twelve\n" +
      "men. They are dressed entirely in black, with the sole exception\n" +
      "of green arm bands they wear proudly on their left arms. By their\n" +
      "rigid stance, you get the feeling they are much more disciplined\n" +
      "than the typical militia man that you have seen around the city.\n" +
      "@@watch_offender@@");
      
   add_prop(OBJ_M_NO_GET, "They would probably hurt you if you tried.\n");
   set_offender(find_player("ashbless"));
}


string
query_offender_name()
{
   if (!offender)
      return "nobody";
      
   return offender->query_real_name();
}


void
set_offender(object who)
{
   offender = who;
}


string
watch_offender()
{
   if (!offender || ! (P(offender,E(TO))) )
      return "";

   if (TP == offender)
      return BS("They are walking slowly towards you, with determined " +
         "looks on their faces.\n");
   
   return BS("They are walking slowly towards " + check_call(QTNAME(offender),TP) +
      ", with determined looks on their faces.\n");
}