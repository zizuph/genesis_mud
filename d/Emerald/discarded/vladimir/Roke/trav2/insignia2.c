inherit "/std/object";
#include "/sys/macros.h"
#include <stdproperties.h>      
#include <cmdparse.h>           
#include "/d/Roke/common/defs.h"
#include "/d/Roke/varl/atuan/cape/guild/default.h"


string str;
object ob;
object someone;

create_object()
{
	seteuid(getuid());
	set_name("insignia");
	set_short("insignia");
	set_long(BS("This is the insignia of the Travellers guild. It"
		+ " consists of two crossed axes over a map of the"
		+ " world.",70));
 	add_prop(OBJ_I_WEIGHT, 10);
   	add_prop(OBJ_I_VOLUME, 2);
    	add_prop(OBJ_I_VALUE, 0);
	add_prop(OBJ_M_NO_DROP,1);

}

init(){
	::init();
	call_out("soul",1,TP);
}

query_auto_load() { return MASTER_OB(this_object()) + ":" ; }


void
soul(object ob)
{
        object spells;
        int i;
        string *souls;
        seteuid(getuid(TO));
        souls = ob->query_cmdsoul_list();
        for (i = 0; i < sizeof(souls); i++)
                ob->remove_cmdsoul(souls[i]);
        ob->add_cmdsoul(TRAV_SOUL);
        for (i = 0; i < sizeof(souls); i++)
                if (souls[i] != TRAV_SOUL)
                        ob->add_cmdsoul(souls[i]);
        ob->update_hooks();    
}

