inherit "/std/key";
#include <stdproperties.h>

int handle_with_care;

create_key()
{
    set_name("key");
    set_pname("keys");
    set_adj("rusty");
    add_adj("small");
    set_short("small rusty key");
    set_pshort("small rusty keys");
    set_long("This key is very rusty. In fact it is only piece of rust. So "+
             "you must handle it with extreme care otherwise it can easily "+
             "broke.\n");
    add_prop(OBJ_I_WEIGHT,5); /* 5 grams */
    add_prop(OBJ_I_VOLUME,1); /* 1 ml    */
    add_prop(OBJ_I_VALUE,5);  /* 5 cc    */
    
    handle_with_care = 0;
}

void
enter_env(object dest, object old)
{
  handle_with_care += 1;
  if(handle_with_care == 2)
    call_out("destruct_key",30+random(60));
  return;
}

void
destruct_key()
{
 object room; 

  room = this_object();
  while(!(room=environment(room))->query_prop(ROOM_I_IS));
  tell_room(room, "The small rusty key sudenly turns into dust.\n");
  call_out("remove_object",0);
}

