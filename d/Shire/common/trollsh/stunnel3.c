#include "/d/Shire/common/defs.h" 
inherit "/d/Shire/common/lib/rom";

create_rom()
{
	set_short("Secret tunnel");
	set_long("You are in a dark and humid tunnel under the "
		+"trollshaws. Blood and guts is laying all over the floor "
		+"and it looks like there has been a lots of fighting in "
		+"here. The path is going downwards, quite steep infact. "
		+"On the wall is a torchstand with an outburned torch in it.\n");
		
	add_item(("torch"),"The torch looks like it has been here for ages.\n");
	add_item(({"guts"}),"there is guts laying on the floor, and most of it is "
			+"dried out. It must have been here for a long time...\n");

	add_prop(ROOM_I_LIGHT, -1);
	add_prop(ROOM_I_INSIDE,1);
	
	add_exit(TROLLSH_DIR + "stunnel0", "west" ,0,2);
   	add_exit(TROLLSH_DIR + "stunnel4", "south" ,0,2);
   	add_exit(TROLLSH_DIR + "stunnel5", "north" ,0,2);
	
}
