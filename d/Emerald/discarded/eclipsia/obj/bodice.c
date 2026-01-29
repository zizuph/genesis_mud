inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/d/Emerald/defs.h"

string color;
string colorfun();

void set_color(string str)
{
	color = str;
}

void init_bodice()
{
    if (!color) color = colorfun();
    set_short( color + " shell bodice");
    set_long("This beautiful, yet simple piece of clothing is "+
	"very common with the female merfolk of Coral Requiem. "+
	"it consists of a pair of " + color + " shells " +
	"with a strap that goes around the body"+
	".\n");
    add_adj( ({ color, "shell" }) );
    return;
}
	

void
create_armour()
{
    init_bodice();
    set_name("bodice");
    add_prop(OBJ_I_VALUE, 50 + random(100));
    set_ac(5);
    set_at(A_TORSO);

    set_af(TO);
}

string colorfun()
{
    string str;

    switch(random(9))
      {
      case 0: str = "turquoise"; break;
      case 1: str = "aquamarine"; break;
      case 2: str = "ocean-blue"; break;
      case 3: str = "soft-pink"; break;
      case 4: str = "tangerine-orange"; break;
      case 5: str = "pearly-white"; break;
      case 6: str = "cobolt-black"; break;
      case 7: str = "ruby-red"; break;
      case 8: str = "speckled-grey"; break;
      }
    return str;
}

public int
wear(object arm)
{
    if(TP->query_gender() != 1)
      {
	write("You hold the " + TO->query_short() + " up in front "+
	"of your body and realize that you just don't have the build "+
	"for it.\n");
	
	say(QTNAME(TP) + " holds the " + TO->query_short() +
	" up in front of " +TP->query_possessive()+ " body, but "+
	"decides that "+TP->query_pronoun()+ " doesn't have the "+
	"body to wear it.\n");

	return -1;
      }
    write("You hold the " + TO->query_short() + " up in front "+
	"of your body, admiring it's beauty just before you put "+
	"it on.\n");

    say(QTNAME(TP) + " holds the " + TO->query_short() +
	" up in front of " +TP->query_possessive()+ " body, "+
	"admiring it's beauty just before "+TP->query_pronoun()+
	" puts it on.\n");
    return 0;
}
	
void
init_recover(string arg)
{
    string *a = explode(arg, "&&");;
    set_color(a[1]);
    init_bodice();
    ::init_recover(arg);
    return;
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + color;
}
