// /d/Avenir/common/obj/skin
// creator(s):   Achdram & Lilith
// last update:  Nov 2004
// 		 Lucius 2006 - Cleaned up and made working.
// purpose:      the skin produced by the skinning knife
// note:	
// bug(s):
// to-do:        

inherit "/std/object";

#include <macros.h>
#include <language.h>
#include <stdproperties.h>

private static string skin;

public string
query_skin_race(void)		{ return skin; }

public void
set_skin_race(string str)	{ skin = str; }

public void
init_the_skin(void)
{
    string skin_str;

    if (!strlen(skin))
	skin = "troloby";

    skin_str = "skin of "+ LANG_ADDART(skin);

    set_short(skin_str);
    set_pshort(LANG_PSENT(skin_str));
    set_long("This is the "+ short() +". It appears to "+
        "have been removed by skilled hands and has been hardened "+
	"so as to be used as leather for wrapping the hilts of weapons "+
	"and in the making of armours.\n");

    set_adj(({ skin }));
}

/*************** Creation ************/
public void
create_object(void)
{
   add_name(({"skin","leather","smiths_leather","_avenir_skin"}));

   add_prop(OBJ_I_VOLUME, 100);   
   add_prop(OBJ_I_WEIGHT, 100);   
   add_prop(OBJ_I_VALUE, 100 + (random(100)));
}             

public void 
init_arg(string arg)
{
    sscanf(arg, "%s#skn#%s*%s", arg, skin, arg);
    init_the_skin();
}

public string
query_auto_load(void)
{
    return MASTER + ":#skn#"+ skin +"*";
}
