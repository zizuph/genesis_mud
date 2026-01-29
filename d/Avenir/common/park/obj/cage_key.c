inherit "/std/key";

create_key()
{
  ::create_key();
  set_adj("tiny");
  set_adj("silver");
  set_short("tiny silver key");
  set_long("This tiny key is so small that you can barely hold it. It "
          +"is attached to a thread-like silver chain that seems like "
          +"it would break if you looked at it too hard.\n");
  add_item(("chain"),"It is a long silver chain with links so small "
          +"that you can barely see them.\n");
  set_key("Golden_Cage_Key");
//  add_prop(OBJ_I_WEIGHT, 1);    // told you it was small      
//  add_prop(OBJ_I_VOLUME, 1);    // ditto         
//  add_prop(OBJ_I_VALUE, 300);   // its silver, tho

}
