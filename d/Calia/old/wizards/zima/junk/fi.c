inherit  "/std/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Roke/common/defs.h"

string long;

ship_leave();

create_room() 
{
 ::create_room();

set_short("Dock");
set_long("@@slong");

add_item(({"port","dock"}),"The dragon port of Re Albi.\n");

add_item(({"berth"}),"The stone docks are big enough for a small galley.\n");
add_item(({"fish","fishes"}),"As you watch, one jumps from the water sending a rainbow of colour\n"
                + "sparkling off its skin.\n");
add_item(({"bell"}),"The bell is large and made of brass.\nThere is a hammer"
        + " connected to it by a chain.\n");
add_item(({"hammer"}),"The brass hammer is connected to the bell by a long chain.\n");


add_exit(REDIR + "a1","west",0);

}
init()
{
  ::init();
        add_action("ring","ring");
}

ring(str)
{
        if (str != "bell"){
                write("Ring what?");
        }
        else{
                write("You sound the bell with all your might.\n");
                say(QCTNAME(this_player()) + " rings the bell.\n");

		if(!(ATUAN+"dship")->query_prop("ship_is_busy"))
		  {
		    call_out("ship_arrive",15);
		    (ATUAN+"dship")->add_prop("ship_is_busy",1);
		  }
		else
		  tell_room(TO,"It seems like noone hears it.\n");
		return 1;
	      }
      }

slong()
{ 
        long = (BS("You are in a large muddy field east of Re Albi. "+
		   "It looks exactly like a harbour here, except that"+
		   " there is no water at all, just docks."
                + " There is a large brass bell and hammer here.\n",70));
        return long;
}
ca()
{
  if(find_call_out("snorgurka")<=0)
    {
      remove_call_out("ship_leave");
  
      call_out("snorgurka",5);
    }
}
snorgurka()
{
  set_long(slong());

  (ATUAN+"dship")->take_off(GAR+"gardock");
  ship_leave();
}
ship_arrive()
{
        tell_room(TO,"A massive dragonship swoops into the harbour.\n");
        add_exit(ATUAN + "dship","board","@@ca");
        set_long(BS("You are in a large muddy field east of Re Albi."+
		    " It looks exactly like a harbour here, except that"+
		    " there is no water at all, just docks. One of"+
		    " the huge docks is occupied by a massive dragon"+
		    " ship."
                + " There is a large brass bell and hammer here.\n",70));
        call_out("ship_leave",10);
       
	(ATUAN+"dship")->arrive(REDIR+"f1");
}

ship_leave()
{
        tell_room(TO,"The massive dragonship spreads its wings and takes to the air.\n");
        remove_exit("board");
        set_long(BS("You are in a large muddy field east of Re Albi."+
		    " It looks exactly like a harbour here, except that"+
		    " there is no water at all, just docks."
                + " There is a large brass bell and hammer here.\n",70));
	(ATUAN+"dship")->remove_exit("leave");
	(ATUAN+"dship")->remove_prop("ship_is_busy");
} 

