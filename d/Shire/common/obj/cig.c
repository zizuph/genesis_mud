inherit "/std/object";
#include <stdproperties.h>
#include "/sys/macros.h"

#define TP this_player()

//   Prototypes
void branch_me();

int alarm_id;

void
create_object()
{
   set_name("cigar");
   set_pname("cigars");
   set_adj(({"blood dried", "red"}));

   set_long("YOu can smoke it by <smoke cigar> \n");


   set_short("cigar");
   set_pshort("cigars");

   alarm_id = set_alarm(1.0,0.0,&branch_me());
}

string query_auto_load() {return "/d/Shire/briaeros/island/cig.c";}

void
init()
{
    ::init();



   add_action("smoke_cigar","smoke");

}

int
smoke_cigar(string str)
{
   if (str == "cigar")
    {
    write("As you inhale from the cigar, you feel very relaxed.\n");
   say(QCTNAME(TP) + " smokes a cigar and becomes very relaxed.\n");
        return 1;
    }
    return 0;
}

void
branch_me()
{
   return;
}
