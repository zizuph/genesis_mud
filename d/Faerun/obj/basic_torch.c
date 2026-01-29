/*
 * /d/Faerun/obj/basic_torch.c
 *
 * Created June 14, 2016 by Twire
 * 
*/
 
 inherit "/std/torch";
 #include <macros.h>
 /*
  * Function name: create_object
  * Description:   The standard create routine.
  */
 void
 create_torch()
 {
     set_name("torch");
     set_pname("torches");	   /* The plural name. */
     set_adj("small");
     set_long("A small, basic torch, useful for illuminating dark places.\n");
     set_strength(2);
     set_short("small torch");
     set_pshort("small torches");
 }
 string
 query_recover()
 {
     return MASTER + ":" + query_torch_recover();
 }
 void
 init_recover(string arg)
 {
     init_torch_recover(arg);
 }