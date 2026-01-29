/* 
 * shelf_shadow.c 
 * 
 * This is a shadow added to containers being placed within 
 * the shelf located at the alcove in the Halls of Shadow. 
 * 
 * It is necessary to work around a mudlib bug which allows 
 * you to put and take things from containers within containers 
 * even if you are prevented from accessing the parent container. 
 */ 
inherit "/std/shadow"; 

public void 
remove_union_shelf_shadow(void) 
{ 
    remove_shadow(); 
} 

public int 
prevent_enter(object ob) 
{ 
    return environment(shadow_who)->prevent_enter(ob); 
} 

public int 
prevent_leave(object ob) 
{ 
    return environment(shadow_who)->prevent_leave(ob); 
}