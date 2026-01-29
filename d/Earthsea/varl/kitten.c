inherit "/std/object";
#include "/sys/macros.h"
#include <stdproperties.h>      /* All prop definitions */
#include <cmdparse.h>           /* The FIND_STR_IN_OBJECT macro */
#include "/d/Roke/common/defs.h"
#include "/d/Roke/common/qbits.h"

string str;
object girl;

create_object()
{
	seteuid(getuid());
	set_name("kitten");
	add_name("rokekitten");
	set_short("cute kitten");
	set_long("Its a small, cute kitten which cries softly.\n");
	set_adj("small");
	add_adj("cute");
 	add_prop(OBJ_I_WEIGHT, 10);
   	add_prop(OBJ_I_VOLUME, 2);
    	add_prop(OBJ_I_VALUE, 0);

}

init(){
	::init();
	add_action("stroke_kitten","stroke");
	add_action("kill_kitten","kill");
	add_action("give_kitten","give");
}

stroke_kitten(str)
{
if ((str == "kitten") || (str == "cute kitten")){
write(BS("You stoke the little kitten. It looks into"
	+ " your eyes and purrs softly.",70));
say(BS(QCTNAME(TP) + " strokes a kitten softly and it begins to purr.",70));
}
return 1;
}

kill_kitten(str)
{
if ((str == "kitten") || (str == "cute kitten")){
write (BS("You violently smash the kitten's head off the ground"
	+ " killing it instantly.",70));
say(QCTNAME(TP) + " smashes the cute kitten off the ground,\n"
	+ " blood splashes everywhere.\n");
remove_object();
return 1;
}
return 0;
}

give_kitten(str)
{

object kitty;

girl = clone_object(ATUAN + "gar/monsters/alena");

if((str == "kitten to alena") || (str == "cute kitten to alena")){

   if(!QDONE(GROUP0,KITTENQUEST))
    {
      write(BS("Alena says: Thank you......and then wanders away.",70));      
      TP->catch_msg("You feel more experienced.\n");
      TP->add_exp(250);
      TP->set_bit(0,18); 
	QLOG("kittenquest");

	if(girl=present("rokealena",environment(TP)))
	{
	girl->remove_object();
	}
	if(kitty = present("rokekitten",TP))
		kitty->remove_object();

  
      return 1;
    }
  else
    {
      write(BS("Alena thanks you again and wanders off humming merrily.",70));	
	if(girl=present("rokealena",environment(TP)))
	{
	girl->remove_object();
	}
	remove_object();
      return 1;
    }
}

return 0;
}
