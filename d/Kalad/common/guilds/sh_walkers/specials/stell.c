inherit "/std/object";
#include "/d/Kalad/defs.h"

void
create_object()
{
    set_name("box");
    set_adj("black");
    set_long("This is used to communicate with all Shadow Walkers.\n"+
    "Use shadowtell (text) to use it.\n");
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,5);
}

void
init()
{
    ::init();
    AA(do_shadowtell,shadowtell);
}


int
do_shadowtell(string str)
{
   object *obs;
   int i;
   obs = users();
   for(i=0;i<sizeof(obs);i++)
   {
       if (obs[i]->query_guild_member("Shadow Walkers"))
       {
           obs[i]->catch_msg("Sarr tells all the Shadow "+
           "Walkers: "+str+"\n");
       }
    }   
           write("You tell all the Shadow Walkers: "+str+"\n");
    return 1;
}
