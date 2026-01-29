 // Liege Book     (/d/Genesis/postmaster/private/liege/book.c)
 // creator(s):    Tepisch February 1996
 // last update:                                                            
 // purpose:       Primarily for New Lieges, to provide easy access
 //                to information they need to know.
 // note:                                                                   
 // bug(s):                                                                 
 // to-do:                                                                  

inherit "/std/book";                                                        
                                                                                                                                                       
#include <stdproperties.h>                                                  
#include <std.h>                                                                            
#include <macros.h>

#define CANDIDATE "_liege_candidate"
#define DCREATE   "/doc/man/Genesis/domain_creation"
#define DGUILD    "/doc/man/Genesis/domain_guilds"
#define DINFO     "/doc/man/Genesis/domain_info"
#define LIEGEBK   "/d/Genesis/postmaster/private/liege/"
#define DOPEN     "/doc/man/Genesis/domain_opening"
#define DPOLICY   "/d/Genesis/doc/rules/wizard/domain_policy"
#define DTHEME    "/doc/man/Genesis/domain_theme"

private void reject_me(object ob);
private void do_remind(object ob);

string
query_auto_load() { return MASTER + ":"; }

void                                                                             
create_book()                                                               
{                    
   set_short("liege manual");                                                       
   set_long("A lightweight booklet with a royal purple cover and "+
       "pale gray silk lining the edges. In gilded letters are "+
       "the words: A Guide for Lieges.\n");
   set_name("book");                                                        
   add_adj(({"lightweight", "liege"}));
   add_name(({"booklet","manual"}));
   add_item(({"lettering", "words"}),"The golden letters read: " +
            "A Guide for Lieges.\n");
   set_max_pages(15);
                                                                            
   add_prop(OBJ_M_NO_DROP, "The liege manual clings to your hands.\n");
   add_prop(OBJ_M_NO_GIVE, "The leige manual cannot be given.\n");
   add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it uninteresting.\n");
   add_prop(OBJ_M_NO_STEAL, 1);
 
   seteuid(getuid());                                                       
}                                                                           
                                                                            
void                                                                        
read_book_at_page(int which)                                                
{                                                                           
   switch(which)                                                            
   {                                                                        
     case 1:                                                                
         cat(LIEGEBK + "contents");                                              
         break;                                                             
      case 2:                              
         cat(LIEGEBK + "liege1");             
         break;                            
      case 3:                              
         cat(LIEGEBK + "liege2");             
         break;                            
      case 4 :                             
         cat(LIEGEBK + "liege3");             
         break;                            
      case 5:                              
         cat(LIEGEBK + "liege4");             
         break;                            
      case 6:
         cat(LIEGEBK + "liege5");
         break;
      case 7:                              
         cat(DCREATE);             
         break;                            
      case 8:                              
         cat(DGUILD);             
         break;                            
      case 9:                              
         cat(DINFO);             
         break;   
      case 10:
         cat(DOPEN);
         break;
      case 11:
         cat(DPOLICY);
         break;
      case 12:
         cat(DTHEME);
         break;                                                             
      case 13:
         cat(LIEGEBK + "blank");
         break;                            
      case 14:
          cat(LIEGEBK + "blank");
         break;                            
      case 15:
         cat(LIEGEBK + "blank");
         break;                                               
      default:                             
         cat(LIEGEBK + "contents");     
   }                                       
   return;                                 
}                                          

void
enter_env(object dest, object old) 
{ 
  string name = dest->query_real_name();
  if ( (SECURITY->query_wiz_rank(name) >= WIZ_LORD) ||     
    (dest->query_prop(CANDIDATE)) )
    set_alarm(4.0, 0.0, &do_remind(dest));
  else 
    set_alarm(4.0, 0.0, &reject_me(dest)); 
  
  ::enter_env(dest, old);    
}
private void
reject_me(object ob) {
  
  ob->catch_msg("This manual is not intended for your eyes.\n" +
                "The manual turns into a bird and flies away.\n");
  remove_object();
}


private void
do_remind(object ob)
{
    ob->catch_msg("You have a liege manual in your inventory.\n");
}
