#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../nov.h";

inherit "/std/shadow";

int invis_level1;
int invis_level2;

void
remove_glitterdust_shadow()
{
	
    //invis_level2 = shadow_who->query_prop(OBJ_I_INVIS);
	
    shadow_who->tell_watcher("The glitterdust on "+QCTNAME(shadow_who)+"'s body fades away.\n");
    shadow_who->add_prop(OBJ_I_INVIS, shadow_who->query_prop(OBJ_I_INVIS) + 50);
    //shadow_who->add_prop(OBJ_I_INVIS, invis_level2);
    shadow_who->remove_prop(IHAVEGLITTERDUST);
    tell_object(shadow_who, "The glitterdust fades away.\n");
    
    remove_shadow();
}


int
query_glitterdust_shadow()
{
    return 1;
}


void
init_glitterdust_shadow(int i)
{
      
      //invis_level1 = shadow_who->query_prop(OBJ_I_INVIS);
      
      shadow_who->add_prop(OBJ_I_INVIS, shadow_who->query_prop(OBJ_I_INVIS) - 50);
      //shadow_who->add_prop(OBJ_I_INVIS, invis_level - invis_level);
      tell_object(shadow_who,"You are visible as the sparkling glitterdust reveals your position!\n");
      shadow_who->tell_watcher(QCTNAME(shadow_who)+"'s body glitters nicely.\n");      
      shadow_who->add_prop(IHAVEGLITTERDUST, 1);
    
      set_alarm(itof(i),0.0,&remove_glitterdust_shadow());
}